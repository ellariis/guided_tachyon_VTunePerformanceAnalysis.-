
//==============================================================
//
// SAMPLE SOURCE CODE - SUBJECT TO THE TERMS OF SAMPLE CODE LICENSE AGREEMENT,
// http://software.intel.com/en-us/articles/intel-sample-source-code-license-agreement/
//
// Copyright Intel Corporation
//
// THIS FILE IS PROVIDED "AS IS" WITH NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS.
//
// =============================================================



/*
    The original source for this example is
    Copyright (c) 1994-2008 John E. Stone
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. The name of the author may not be used to endorse or promote products
       derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/

/******************************************************************************
The tachyon sample program is for use with
 NAME OF TUTORIAL HERE

Please refer to the tutorial for build instructions.
*******************************************************************************/


#include "machine.h"
#include "types.h"
#include "macros.h"
#include "vector.h"
#include "tgafile.h"
#include "trace.h"
#include "light.h"
#include "shade.h"
#include "camera.h"
#include "util.h"
#include "intersect.h"
#include "global.h"
#include "ui.h"
#include "tachyon_video.h"
#include <tbb/tbb.h>


// Initialize the mutex to be used later:
tbb::spin_mutex mtx;

// shared but read-only so could be private too
static thr_parms *all_parms;
static scenedef scene;
static int startx;
static int stopx;
static int starty;
static int stopy;
static flt jitterscale;
static int totaly;

// This function is shared among all implementations:

static color_t render_one_pixel (int x, int y, unsigned int *local_mbox, unsigned int &serial,
                                 int startx, int stopx, int starty, int stopy)
{
    /* private vars moved inside loop */
    ray primary, sample;
    color col, avcol;
    int R,G,B;
    intersectstruct local_intersections;
    int alias;
    /* end private */

    primary = camray(&scene, x, y);
    primary.intstruct = &local_intersections;
    primary.flags = RT_RAY_REGULAR;

    serial++;
    primary.serial = serial;
    primary.mbox = local_mbox;
    primary.maxdist = FHUGE;
    primary.scene = &scene;
    col = trace(&primary);
    serial = primary.serial;

    /* Handle overexposure and underexposure here... */
    R = (int)(col.r * 255);
    if ( R > 255 ) R = 255;
    else if ( R < 0 ) R = 0;

    G = (int)(col.g * 255);
    if ( G > 255 ) G = 255;
    else if ( G < 0 ) G = 0;

    B = (int)(col.b * 255);
    if ( B > 255 ) B = 255;
    else if ( B < 0 ) B = 0;

    return video->get_color(R, G, B);
}

#if DO_ITT_NOTIFY
#include"ittnotify.h"
#endif

//// This application will be multi-threaded with the use of Intel Threading Building
//// Blocks library. In order to do that we need to include the Intel TBB header file
//// and link against tbb.lib (in release mode) or tbb_debug.lib (in debug mode)
//todo: uncomment following line  in Intel TBB implementation

//// It's quite easy to convert serial function with a loop that is to be parallelised
//// to a function object that Intel TBB algorithms (in this case parallel_for) will use
//// The function body needs to be moved into a C++11 lambda function passed to 
//// the Intel TBB parallel_for
//// We move out of the loop the iteration-independent value of mboxsize.
//// We also no longer check for the validity of video->next_frame.
//// Exiting a loop in the middle of a parallelized loop is not permitted.
//// And the iterations we save from this check will be distributed 
//// Without affecting the result.
//todo: uncomment the following routine for the Intel TBB implementation
///*

static void parallel_thread(void)
{
   
    unsigned int mboxsize = sizeof(unsigned int) * (max_objectid() + 20);

     tbb::parallel_for(starty, stopy, [mboxsize] (int y)
    {
        tbb::spin_mutex::scoped_lock lock(mtx);
             
        unsigned int serial = 1;
        unsigned int local_mbox[mboxsize];
        memset(local_mbox, 0, mboxsize);
        drawing_area drawing(startx, totaly - y, stopx - startx, 1);
        for ( int x = startx; x < stopx; x++ ) {
            color_t c = render_one_pixel(x, y, local_mbox, serial, startx, stopx, starty, stopy);
            drawing.put_pixel(c);
        }
        video->next_frame();
    }
	);
}

// This function is shared among all implementations:

void * thread_trace(thr_parms * parms)
{
    // shared but read-only so could be private too
    all_parms = parms;
    scene = parms->scene;
    startx = parms->startx;
    stopx = parms->stopx;
    starty = parms->starty;
    stopy = parms->stopy;
    jitterscale = 40.0*(scene.hres + scene.vres);
    totaly = parms->scene.vres - 1;

#if DO_ITT_NOTIFY
    __itt_resume();
#endif
    parallel_thread();
#if DO_ITT_NOTIFY
    __itt_pause();
#endif

    return(NULL);
}
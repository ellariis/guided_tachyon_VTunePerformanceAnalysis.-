# Threading Your Application - Tachyon

Tachyon is a parallel raytracer / renderer used in combination with the
**Intel® C++ Compiler Tutorial \"Threading Your Application\"** on using
different threading technologies. The tutorial in this package shows how
to thread an application step-by-step.

Tachyon is a 2-D raytracer/renderer that visually shows different
parallel scheduling methods and their resulting speedup. The code was
parallelized by speculating that each pixel could be rendered in
parallel. Minimal synchronization was inserted into the parallel code.
The resulting parallel code, using either OpenMP\*, or Intel® oneAPI Threading
Building Blocks (oneTBB) exhibits good speedup.


### The following versions of the example are provided:

-   **serial**:
    -   Original sequential version.
-   **openmp**: Parallel version that uses OpenMP\* and an omp parallel
    for to parallelize over tasks that are rectangular sub-areas.
    -   By default, this version uses one thread per available
        processor. To change this default, set the OMP\_NUM\_THREADS
        environment variable to the desired number of threads before
        running.
-   **tbb**: Parallel version that uses oneTBB and blocked\_range2d
    to parallelize over tasks that are rectangular sub-areas.
    -   By default, this version uses one thread per available
        processor. To change this default, set the TBB\_NUM\_THREADS
        environment variable to the desired number of threads before
        running.
    -   This version uses a reasonable task grain size by default. To
        change this default, set the TBB\_GRAINSIZE environment variable
        to the desired grain size before running. The grain size
        corresponds to the number of pixels (in the X or Y direction,
        for a rectangular sub-area) in each parallel task.


## System Requirements:

-   Hardware:
    -   Any Intel® processor like Intel® Core™ processor family or higher,\
Intel® Xeon® processor family, or Intel® Xeon® Scalable processor family
-   For Microsoft\* Windows\*:
    -   Microsoft Visual Studio 2017\*, 2019\*, or 2022\* Professional
        Edition or above
    -   Intel® oneAPI Base Toolkit 2022.2 for Windows\*or newer
    -   Intel® oneAPI HPC Toolkit 2022.2 for Windows* or newer
-   For Linux\*:
    -   GNU\* GCC 4.5 or newer
    -   Intel® oneAPI Base Toolkit 2022.2 for Linux\*
        or newer
    -   Intel® oneAPI HPC Toolkit 2022.2 for Linux* or newer


## Build Instructions:

### For Microsoft Visual Studio\* users:
<details>
  <summary>Click to expand</summary>

The samples package contains a Visual Studio solution named
tachyon\_samples.sln configured to use the Intel® C++ Compiler. The
solution promotes common use cases for Visual Studio projects such as
building, running, or debugging an application. Below are the
instructions for key tasks which can be done with the samples.

#### To Compile All of the Projects in the Solution

-   Click **Build \> Rebuild Solution**

#### To Compile a Project in the Solution

-   Right-click the project in **Solution Explorer** and then click
    **Rebuild**

#### To Run a Project in the Solution

-   Right-click the project in **Solution Explorer** and then click
    **Set as Startup Project**
-   Click **Debug \> Start Without Debugging** and then click **Yes** in
    the resulting dialog

#### To Debug a Project in the Solution

-   Set a breakpoint in the source code.
-   Click **Debug \> Start Debugging** and then click **Yes** in the
    resulting dialog
</details>

---

### For Microsoft Windows\* Command Line users:
<details>
  <summary>Click to expand</summary>

The samples package also contains a command line script to build the
sample.


Enable your particular compiler environment for the Intel® C++ Compiler:

#### To Compile all configurations

Run `build.bat`

-   The resulting sample executables are placed in the tachyon\_release
    directory.

#### To Compile all configurations\' solutions

-   Run `build.bat solution`

    -   The resulting sample executables are placed in the
        tachyon\_release directory.

#### To Run

-   Run `tachyon_<keyword>` where keyword is the version of the
    sample as described at the top (either serial, openmp, or tbb).
    To run the solution, add `_solution`.
  
</details>

---

### For Linux\* command-line users:
<details>
  <summary>Click to expand</summary>

The samples package is CMake driven and will generate a Makefile configured to use the Intel® C++
Compiler. The generated Makefile promotes common use cases such as building,
running, or debugging an application. Below are the instructions for key
tasks which can be done with the samples.


Enable your particular compiler environment for the Intel® C++ Compiler:

#### To Build:

Create a directory `build` at the root of the project

In the `build` directory, run `cmake ..`
    
Run `make` to accomplish the various steps of the tutorial. 
To build solutions, run:
    
`make solution`

#### To Run
-   Run all using the default .dat file with
    `make run` or `make solution`
    
-   Run any using the default .dat file with
    `make <keyword>` or `make <keyword>_solution`, where keyword is the version of the sample
    as described at the top (either serial, openmp, or tbb).
    
-   Running `./<exe> ../dat/<dat file>` will also run an individual version of the project. 

#### To Debug

Debug the code by setting breakpoints in gdb\* and then running the
application.

</details>

---

#### [Go To Threading Your Application tutorial (English language)](./tutorial/en/index.htm)

#### [Go To Threading Your Application tutorial (Japanese language)](./tutorial/ja/index.htm)

*This example includes software developed by John E. Stone. See
[here](http://software.intel.com/en-us/articles/intel-sample-source-code-license-agreement/)
for license information.*

### Troubleshooting
If an error occurs, troubleshoot the problem using the Diagnostics Utility for Intel® oneAPI Toolkits.
[Learn more](https://www.intel.com/content/www/us/en/develop/documentation/diagnostic-utility-user-guide/top.html)

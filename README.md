# `Guided Tachyon Sample` for Use with Vtune

The `guided Tachyon` sample demonstrates how to use the Intel Vtune Profiler to find and fix hotspots and threading issues in your program. This particular sample includes a Tachyon application executed 5 ways, in order to compare strategies for performance improvement.  

This sample follows the workflow found in [link here](https://www.intel.com/content/www/us/en/developer/tools/oneapi/gpu-optimization-workflow.html#gs.101gmt2).

For comprehensive instructions, see the [Intel&reg; oneAPI Programming Guide](https://software.intel.com/en-us/oneapi-programming-guide) and search based on relevant terms noted in the comments.

| Property                       | Description
|:---                               |:---
| What you will learn               | How to use Vtune to find hotspots and bottlenecks in a graphics application and how to fix common threading issues, particularly in reference to CPU usage
| Time to complete                  | 15 minutes

## Purpose

Tachyon is a 2-D raytracer/renderer that visually shows different parallel scheduling
        methods and their resulting speedup.  The code was parallelized by speculating
        that each pixel could be rendered in parallel.  Minimal synchronization was
        inserted into the parallel code.  The resulting parallel code, using either
        OpenMP*, or Intel&reg; Threading Building Blocks
        (Intel&reg; TBB) exhibits good speedup, which can be further investigated using Intel&reg; Vtune Profiler.

This application produces the following image over varying lengths of time and parallelization.

The sample includes five different versions of the Tachyon project.

- `build_serial.cpp`: basic serial implementation.
- `build_with_openmp.cpp`: "broken" version that uses OpenMP ineffectively, with issues to be demonstrated by Vtune.
- `build_with_openmp_solution.cpp`: OpenMP version that fixes all the issues seen with `build_with_openmp.cpp`.
- `build_with_tbb.cpp`: similar to `build_with_openmp.cpp`, uses TBB ineffectively with issues to be discovered by Vtune.
- `build_with_tbb_solution.cpp`: TBB version that fixes all the issues found in `build_with_tbb.cpp`.

The performance number tabulation is shown below. (needed?)

| iso3dfd sample                      | Performance data
|:---                               |:---
| Scalar baseline -O2               | 1.0
| SYCL                              | 8x speedup

## Prerequisites
| Optimized for                       | Description
|:---                               |:---
| OS                                | Linux* Ubuntu* 18.04 <br>Windows* 10
| Hardware                          | Any Intel&reg; processor like 2nd Generation Intel&reg; Core&#8482; i3, i5, or i7 processors and Intel&reg; Xeon&reg; E3 or E5 processor family
| Software                          | For Microsoft* Windows*: Microsoft Visual Studio 2013*, 2015* or 2017* Professional Edition or above. <br>For Linux*: GNU* GCC 4.5 or newer


## Key Implementation Details NOT SURE WHAT TO PUT HERE

The basic SYCL* standards implemented in the code include the use of the following:

- SYCL* local buffers and accessors (declare local memory buffers and accessors to be accessed and managed by each workgroup)
- Code for Shared Local Memory (SLM) optimizations
- SYCL* kernels (including parallel_for function and nd-range<3> objects)
- SYCL* queues (including exception handlers)

> **Note**: If you have not already done so, set up your CLI
> environment by sourcing  the `setvars` script located in
> the root of your oneAPI installation.
>
> Linux:
> - For system wide installations: `. /opt/intel/oneapi/setvars.sh`
> - For private installations: `. ~/intel/oneapi/setvars.sh`
>
> Windows:
> - `C:\Program Files(x86)\Intel\oneAPI\setvars.bat`
>
>For more information on environment variables, see Use the setvars Script for [Linux or macOS](https://www.intel.com/content/www/us/en/develop/documentation/oneapi-programming-guide/top/oneapi-development-environment-setup/use-the-setvars-script-with-linux-or-macos.html), or [Windows](https://www.intel.com/content/www/us/en/develop/documentation/oneapi-programming-guide/top/oneapi-development-environment-setup/use-the-setvars-script-with-windows.html).

## Build Instructions for Windows
The samples package contains 3 Visual Studio solutions for Visual Studio 2013, 2015, and 2022. The solutions are named tachyon_samples_<year>.sln. They are all configured to use the Intel&reg; C++ Compiler. The solution promotes common use cases for Visual Studio projects such as building, running, or debugging an application. Below are the instructions for key tasks which can be done with the samples.
	<h4>To Compile All of the Projects in the Solution</h4>
			<ul>
			<li> Click <strong>Build > Rebuild Solution</strong></li>
			</ul>
			<h4>To Compile a Project in the Solution</h4>
			<ul>
			<li> Right-click the project in <strong>Solution Explorer</strong> and then click <strong>Rebuild</strong></li>
			</ul>
			<h4>To Run a Project in the Solution</h4>
			<ul>
			<li> Right-click the project in <strong>Solution Explorer</strong> and then click <strong>Set as Startup Project</strong></li>
			<li> Click <strong>Debug > Start Without Debugging</strong> and then click <strong>Yes</strong> in the resulting dialog
			</ul>
			<h4>To Debug a Project in the Solution</h4>
			<ul>
			<li> Set a breakpoint in the source code.</li>
			<li> Click <strong>Debug > Start Debugging</strong> and then click <strong>Yes</strong> in the resulting dialog</li>
			</ul>
  
  <h4>To Compile all configurations</h4>
			<ul>
        <li> Run <code>build.bat</code> </li>
			<ul>
			<li> The resulting sample executables are placed in the tachyon_release directory.
			</ul>
			<h4>To Compile all configurations' solutions</h4>
			<ul>
        <li> Run <code>build.bat solution</code> </li>
			<ul>
        <li> The resulting sample executables are placed in the tachyon_release directory. </li>
			</ul>
			<h4>To Run</h4>
			<ul>
			<li> Run tachyon_*keyword* where keyword is the version of the sample as described at the top (either serial, openmp, or tbb). To run the solution, add "_solution". </li>
			</ul>
        
        ### On Windows* Using Visual Studio* Version 2019 or Newer

- Build the program using VS2019 or VS2022
    - Right-click on the solution file and open using either VS2019 or VS2022 IDE.
    - Right-click on the project in Solution Explorer and select Set as Startup Project
    - Right-click on the project in Solution Explorer and select Rebuild.
    - From the top menu, select Debug -> Start without Debugging.
> **Note**: Remember to use Release mode for better performance.

- Build the program using MSBuild DOES THIS WORK????
     - Open "x64 Native Tools Command Prompt for VS2019" or "x64 Native Tools Command Prompt for VS2022"
     - Run the following command: `MSBuild "guided_iso3dfd.sln" /t:Rebuild /p:Configuration="Release"`
  
## Build Instructions for Linux
To be completed once I have the Linux version out, because right now I can't check if this is right.
        Perform the following steps:
1. Build the program using the following `cmake` commands.
   ```
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make
   ```

2. Run the program.
   ```
   $ make run_all WHAT IS THE EXECUTABLE CALLED
   ```
   > **Note**: the following run commands are also available and correspond to the specific build targets. You can run all the versions with the run_all or select specific executable with one of the targets, additionally there are targets to run in addition the verify step. THESE TARGETS ALL HAVE DIFFERENT NAMES AND THERE IS NO GPU STUFF

| Basic Invocation                       | Additional versions                 | Verification
|:---                                    |:---                                 |:---
|                                        | make clean                          |
| make run_all                           |                                     | make run_verify_all
| make run_cpu                           |                                     | 
| make run_gpu_basic_offload             |                                     | run_verify_gpu_basic
| make run_gpu_linear                    |                                     | run_verify_gpu_linear
| make run_gpu_private_I                 | make run_gpu_private_K              | run_verify_gpu_private
| make run_gpu_optimized                 | make run_gpu_optimized_good_params  | run_verify_gpu_optimized 
|                                        | make run_gpu_optimized_wrong_params |
 

`run_all` and `run_verify_all` execute all basic commands. Verification commands compares GPU and CPU execution and compares results to ensure accurate calculation.

If an error occurs, you can get more details by running `make` with
the `VERBOSE=1` argument:
```
make VERBOSE=1
```

### Troubleshooting
If you receive an error message, troubleshoot the problem using the Diagnostics Utility for Intel&reg; oneAPI Toolkits, which provides system checks to find missing
dependencies and permissions errors. See [Diagnostics Utility for Intel&reg; oneAPI Toolkits User Guide](https://www.intel.com/content/www/us/en/develop/documentation/diagnostic-utility-user-guide/top.html).

### Running Samples in Intel&reg; DevCloud SHOULD I GET RID OF THIS

If running a sample in the Intel&reg; DevCloud, you must specify the compute node (CPU, GPU, FPGA) and whether to run in batch or interactive mode. For more information, see the Intel&reg; oneAPI Base Toolkit [Get Started Guide](https://devcloud.intel.com/oneapi/get_started/).


## License
<p>
    <I>        
        This example includes software developed by John E. Stone.  See
        <A HREF="http://software.intel.com/en-us/articles/intel-sample-source-code-license-agreement/">here</A> for license information.
    </I>
</p>
<div id="footer">
    <p>
        Intel, Intel logo, Intel386, Intel486, Atom, Core, Itanium, MMX, Pentium, VTune, 
        Xeon Phi, and Xeon are trademarks of Intel Corporation in the U.S. and/or other countries<br>
        * Other names and brands may be claimed as the property of others <br>
        Copyright &copy; Intel Corporation. All Rights Reserved<br>
</div>

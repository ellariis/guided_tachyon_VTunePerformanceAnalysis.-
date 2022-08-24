# `Guided Tachyon Sample` for Use with Vtune

The `guided Tachyon` sample demonstrates how to use the Intel&reg; Vtune Profiler to find and fix hotspots and threading issues in your program. This particular sample includes a Tachyon application executed 5 ways, in order to compare strategies for performance improvement.  

For comprehensive instructions, see the [Intel&reg; oneAPI Programming Guide](https://software.intel.com/en-us/oneapi-programming-guide) and search based on relevant terms noted in the comments.

This sample is meant to be used with the Intel&reg; Vtune Profiler. For VTune Profiler downloads and product support, visit https://software.intel.com/en-us/vtune. All the Vtune samples and Cookbook recipes are scalable and can be applied to Intel&reg; VTune Amplifier 2018 and higher. Slight version-specific configuration changes are possible. Intel® VTune™ Amplifier has been renamed to Intel® VTune™ Profiler starting with its version for Intel® oneAPI Base Toolkit (Beta). You can still use a standalone version of the VTune Profiler, or its versions integrated into Intel Parallel Studio XE or Intel System Studio.

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

## Prerequisites
| Optimized for                       | Description
|:---                               |:---
| OS                                | Linux* Ubuntu* 18.04 <br>Windows* 10
| Hardware                          | Any Intel&reg; processor like 2nd Generation Intel&reg; Core&#8482; i3, i5, or i7 processors and Intel&reg; Xeon&reg; E3 or E5 processor family
| Software                          | For Microsoft* Windows*: Microsoft Visual Studio 2013*, 2015* or 2017* Professional Edition or above. <br>For Linux*: GNU* GCC 4.5 or newer


## Key Implementation Details

The fundamental takeaways from this guided sample include:

- How to use Intel&reg; Vtune Profiler Hotspots and Threading analysis
- How threading can improve runtime and CPU efficiency
- How to use OpenMP and/or TBB threading effectively

## Build Instructions

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
The samples package contains a Visual Studio solution named `tachyon_samples_2022.sln`. It is configured to use the Intel&reg; C++ Compiler. The solution promotes common use cases for Visual Studio projects such as building, running, or debugging an application. Below are the instructions for key tasks which can be done with the samples.
- ## Build the program using Visual Studio 2019 or newer:
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
> **Note**: Remember to use Release mode for better performance.

-  ## Build the program using MSBuild
     - Open "x64 Native Tools Command Prompt for VS2019" or "x64 Native Tools Command Prompt for VS2022"
     - Run the following command: `MSBuild "tachyon_samples_2022.sln" /t:Rebuild /p:Configuration="Release"`
  
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

### Running Samples in Intel&reg; DevCloud

If running a sample in the Intel&reg; DevCloud, you must specify the compute node (CPU, GPU, FPGA) and whether to run in batch or interactive mode. For more information, see the Intel&reg; oneAPI Base Toolkit [Get Started Guide](https://devcloud.intel.com/oneapi/get_started/).

## Guided Builds

### Setup
1. Ensure that the solution and project files are updated for your version of Visual Studio.
2. Build the solution with default settings.
3. Add the path to balls.dat as a command argument for running through the debugger. ![image](https://user-images.githubusercontent.com/111458217/186287484-62e6e199-ff9f-40ea-8f55-4a973ce3761f.png)

### Serial Build
1. Set `build_serial` as your startup project and open Vtune. If using the integrated version of Vtune with Visual Studio, you can click this button to open the Vtune GUI: ![image](https://user-images.githubusercontent.com/111458217/186288369-4e9b60a9-fc1e-47af-bee9-97d3e9964b8c.png)
2. Run Hotspots Analysis with User Mode Sampling: ![image](https://user-images.githubusercontent.com/111458217/186289835-301afe7e-48f0-4c54-a8bc-f99d59870753.png)
3. Vtune will display a `Summary` tab that should show results similar to this: ![image](https://user-images.githubusercontent.com/111458217/186290141-c37763a8-2825-42e0-a900-34325cf9bbc1.png) ![image](https://user-images.githubusercontent.com/111458217/186290205-97e98c66-15f3-401c-800e-14727cd9eebc.png) Clearly, the CPU utilization is pretty ineffective with this build. 
4. The `Bottom-up` tab shows a list of all functions, sorted by descending CPU time. Call Stacks are also shown on the right, indicating that the starting point for function grid_intersection is in the draw_task object. The bottom pane shows a chart of thread performance over the duration of the collection, and provides a visualization of the serial nature of this build; only one thread is doing work for the duration of the program. ![image](https://user-images.githubusercontent.com/111458217/186290539-a5352226-c061-4cb4-a085-82373b9a3fb4.png)
5. Now, navigate back to the `Intel Vtune Profiler` tab and select `Configure Analysis`. 
6. Run Threading Analysis with User Mode Sampling.
7. The `Summary` tab will display results similar to the ones found with the Hotspots Analysis. The Threading Analysis will provide further detailed results concerning the wait time for different threads. Compare your results to this example screenshot: ![image](https://user-images.githubusercontent.com/111458217/186291190-655ef875-0d6f-472b-8a86-365d543c2cc7.png)
8. Clearly, this serial build is not making effective use of the available CPUs and threading capabilities. Let's move on to the OpenMP build and see how we can improve this implementation.

### OpenMP Build
1. Before running this, take a look at the code in `tachyon.openmp.cpp`. Compare this code to `tachyon.serial.cpp`. As you can see, this code uses the OpenMP library to divide the work among threads. 
2. Set `build_with_openmp` as your startup project and open Vtune. See the "Serial Build" instructions for more detail on how to open and use Vtune.
3. Run Hotspots Analysis with User Mode Sampling. Compare your results with the example results here: ![image](https://user-images.githubusercontent.com/111458217/186293812-73d21821-062c-4ed3-8d44-72b431e35b0a.png) Some things to notice here are, there are 10 threads in use here. However, most of the CPU time seems to be spin time. In other words, the CPU is spending a lot of time doing nothing. The Hotspots Analysis shows that the function `_kmpc_set_lock` is taking up 83.3% of the CPU time!
4. Navigate to the `Bottom-up` tab to investigate this further. Click on the arrow next to the `_kmpc_set_lock` function to find more detail on where this function is being called. It appears this hotspot can be found in the `parallel_thread` function in `tachyon.openmp.cpp`. ![image](https://user-images.githubusercontent.com/111458217/186295413-8abf2e5a-942a-418b-92df-cd4ddc26b01d.png)
5. Run Threading Analysis with User Mode Sampling. Threading Analysis provides a similar conclusion: `_kmpc_set_lock` is causing a big problem. ![image](https://user-images.githubusercontent.com/111458217/186295765-4966c338-ba3a-40d4-a172-efdea1ae0ea9.png) ![image](https://user-images.githubusercontent.com/111458217/186295795-8e6c7cc4-699d-44f8-a2d8-e805adf11e44.png)
6. Navigate back to `tachyon.openmp.cpp`. What improvements do you think can be made? Try for yourself and run with Vtune to check how your efforts worked.
7. You may have noticed that the `_kmpc_set_lock` is part of the OpenMP mutex lock functionality. There is a mutex lock in this code which is preventing multiple threads from doing work at the same time. If you haven't already, remove the mutex lock and profile the application again using Hotspots Analysis and Threading Analysis.
8. The `build_with_openmp_solution` project contains the optimized use of OpenMP with this application. Set `build_with_openmp_solution` as your startup project and run the Hotspots Analysis and Threading Analysis on this version. As you can see, the solution removes the mutex lock to allow all threads to freely work concurrently, and introduces dynamic scheduling to ensure that no threads are waiting for others to finish. The results should look something like this: ![image](https://user-images.githubusercontent.com/111458217/186296962-52fe8e56-a094-47bc-a526-629b491a0a56.png) As you can see, this runs much faster than the serial build and the broken OpenMP build, and makes much better use of the CPU. Now, let's see how Intel's TBB library can perform in comparison to OpenMP.

### TBB Build
1. As with the OpenMP build, take a look at the code in `tachyon.tbb.cpp`. Compare this to the versions we have looked at previously. Instead of the OpenMP library, this code uses the Intel&reg; TBB library to divide the work among threads.
2. Set `build_with_tbb` as your startup project and open Vtune. See the "Serial Build" instructions for more detail on how to open and use Vtune. 
3. Run Hotspots Analysis with User Mode Sampling. Compare your results with the example results here: ![image](https://user-images.githubusercontent.com/111458217/186297710-a9a788d2-50c6-49c6-b325-2f143250db1d.png) Similar to the OpenMP build, it looks like we have a function here taking up 83.7% of the CPU time. 
4. Navigate to the `Bottom-up` tab for more information. Click on the arrow next to the top function `tbb::detail::d1::unique etc`. Like the OpenMP build, this problematic function seems to be called in the `parallel_thread` function in `tachyon.tbb.cpp`. ![image](https://user-images.githubusercontent.com/111458217/186298109-06c611ee-cb37-4803-b39e-6462a8ef78a7.png)
5. Run Threading Analysis with User Mode Sampling. This analysis indicates that most of the thread time is spin time: ![image](https://user-images.githubusercontent.com/111458217/186298580-c7792722-aded-4c6e-9c4b-60eebe6d2fa0.png) This confirms that there is a problematic area in the `parallel_thread` function.
6. Navigate back to `tachyon.tbb.cpp` and see if you can fix the issue. Hint: it is very similar to the issue found in the OpenMP build! Check how effective your changes are by running Vtune.
7. As you may have guessed, all that spin time is due to the `tbb::spin_mutex::scoped_lock::lock()` function. This is the TBB version of the mutex lock, which prevents multiple threads from working on that code at a time. If you haven't already, remove the mutex lock and profile the application again using Hotspots and Threading Analyses. 
8. The `build_with_tbb_solution` project contains the optimized use of TBB with this application. Set `build_with_tbb_solution` as your startup project and run the Hotspots and Threading analyses on this version. Like the OpenMP solution build, this solution removes the mutex lock to allow all threads to freely work concurrently. The results should look something like this: ![image](https://user-images.githubusercontent.com/111458217/186299374-15c7aa31-0580-4a86-8bb4-9c640ad91b38.png) ![image](https://user-images.githubusercontent.com/111458217/186299426-6a57a961-7bc8-4ca4-84c0-2bef72b51df8.png) ![image](https://user-images.githubusercontent.com/111458217/186299660-d9e641ab-d978-4dd3-8536-c0f9ba299691.png) Much faster and more effective!

### Conclusion
As you can see, Vtune can be very helpful in finding hotspots and threading issues, especially with large applications that use parallelism. There are always more improvements to be made, and you are encouraged to explore this sample more deeply with Vtune to see what changes you can make!

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

# ECEN5813 Project 2 Readme
# Tristan Duenas
This repository contains the source/include files, makefile, linker file, and WBS for ECEN5813 Project 2.
The project is based on the initial project generated for the MKL25Z128xxx4.
I implemented main.c, LED_control.c/LED_control.h, timing_control.c/timing_control.h, 
which are located in the source folder.
The main.c module contains the cycle loop setup/iteration process.
The LED_control.c module contains the functionality for turning on/off the LED and outputs the appropriate
debug output depending on the build. Refer to LED_control.h for more information.
The timing_control.c module contains the functionality for delaying processing. Different clock frequencies are used
depending on the build. Refer to timing_control.h for more information
I wrote the makefile by hand. The makefile has the ability to build 4 different targets.
fb_run, fb_debug, pc_run, and pc_debug.
Depending on the target built, different sections of the source files I implemented will be used.
- The fb_run target builds with the FB_RUN build flag.
- The fb_debug target builds with the FB_DEBUG build flag.
- The pc_run target builds with the PC_RUN build flag.
- The pc_debug target builds with the PC_DEBUG build flag.

# All build targets will generate their final .AXF/.exe file in the debug folder in ECEN5813_Project_2

Building the fb_run target requires the following steps:

- Right click on ECEN5813_Project_2 and click Clean Project
- Right click on ECEN5813_Project_2 and go to properties
- In properties navigate to the C/C++ Build tab
- Under Builder Settings, Builder, uncheck Use Default Build Command
- In the Build Command option use "make fb_run -j12"
- Under Builder Settings, Makefile generation uncheck Generate Makefile Automatically
- Under Builder Settings, Build location, Build directory enter ECEN5813_Project_2 workspace path
- My current path for my PC is C:\Users\trist\Documents\MCUXpressoIDE_11.0.1_2563\workspace\ECEN5813_Project_2, as an example
- Click Apply, and Apply and Close buttons on Builder Settings Tab
- Right click on ECEN5813_Project_2 and click Build Project
- Verify in Console perspective, the fb_run target build completed successfully

#ECEN5813_Project_2.axf for fb_run target can be found in debug\ECEN5813_Project_2.axf

Running the fb_run target requires the following steps:

- Create run/debug configuration for loading debug\ECEN5813_Project_2.axf, and run/debug on board.

Building the fb_debug target requires the following steps:

- Right click on ECEN5813_Project_2 and click Clean Project
- Right click on ECEN5813_Project_2 and go to properties
- In properties navigate to the C/C++ Build tab
- Under Builder Settings, Builder, uncheck Use Default Build Command
- In the Build Command option use "make fb_debug -j12"
- Under Builder Settings, Makefile generation uncheck Generate Makefile Automatically
- Under Builder Settings, Build location, Build directory enter ECEN5813_Project_2 workspace path
- My current path for my PC is C:\Users\trist\Documents\MCUXpressoIDE_11.0.1_2563\workspace\ECEN5813_Project_2, as an example
- Click Apply, and Apply and Close buttons on Builder Settings Tab
- Right click on ECEN5813_Project_2 and click Build Project
- Verify in Console perspective, the fb_run target build completed successfully

# ECEN5813_Project_2.axf for fb_debug target can be found in debug\ECEN5813_Project_2.axf

Running the fb_debug target requires the following steps:

- Create run/debug configuration for loading debug\ECEN5813_Project_2.axf, and run/debug on board.
- Observe terminal serial port for outputs.

Building the pc_run target requires the following steps:

- Right click on ECEN5813_Project_2 and click Clean Project
- Right click on ECEN5813_Project_2 and go to properties
- In properties navigate to the C/C++ Build tab
- Under Builder Settings, Builder, uncheck Use Default Build Command
- In the Build Command option use "make pc_run -j12"
- Under Builder Settings, Makefile generation uncheck Generate Makefile Automatically
- Under Builder Settings, Build location, Build directory enter ECEN5813_Project_2 workspace path
- My current path for my PC is C:\Users\trist\Documents\MCUXpressoIDE_11.0.1_2563\workspace\ECEN5813_Project_2, as an example
- Click Apply Builder Settings Tab
- Under C/C++ Build, Enviornment, select Variable PATH and edit
- Append path to gcc compiler. I am using the path C:\MinGW\bin since I'm running gcc on Windows.
- In the Enviornment tab click Apply, and the Apply and Close
- Right click on ECEN5813_Project_2 and click Build Project
- Verify in Console perspective, the pc_run target build completed successfully

# pc_run.exe for pc_run target can be found in debug\pc_run.exe

Running the pc_run target requires the following steps:

- Create run C run configuration for debug\pc_run.exe and run locally in IDE. 
- Observe Console for outputs.

Building the pc_debug target requires the following steps:
- Right click on ECEN5813_Project_2 and click Clean Project
- Right click on ECEN5813_Project_2 and go to properties
- In properties navigate to the C/C++ Build tab
- Under Builder Settings, Builder, uncheck Use Default Build Command
- In the Build Command option use "make pc_debug -j12"
- Under Builder Settings, Makefile generation uncheck Generate Makefile Automatically
- Under Builder Settings, Build location, Build directory enter ECEN5813_Project_2 workspace path
- My current path for my PC is C:\Users\trist\Documents\MCUXpressoIDE_11.0.1_2563\workspace\ECEN5813_Project_2, as an example
- Click Apply Builder Settings Tab
- Under C/C++ Build, Enviornment, select Variable PATH and edit
- Append path to gcc compiler. I am using the path C:\MinGW\bin since I'm running gcc on Windows.
- In the Enviornment tab click Apply, and the Apply and Close
- Right click on ECEN5813_Project_2 and click Build Project
- Verify in Console perspective, the pc_debug target build completed successfully

# pc_debug.exe for pc_debug target can be found in debug\pc_debug.exe

Running the pc_debug target requires the following steps:

- Create run C run configuration for debug\pc_debug.exe and run locally in IDE. 
- Observe Console for outputs.
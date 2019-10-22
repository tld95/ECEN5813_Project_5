# ECEN5813 Project 3 Readme
# Tristan Duenas
# Project Demonstration YouTube Video Link https://youtu.be/nHP0Cdw7QX0

This repository contains the source/include files, makefile, linker file, UML Activity Diagram, and UML Sequence Diagram for ECEN5813 Project 3.
The project is based on the initial project generated for the MKL25Z128xxx4.
I implemented main.c, allocate_words.c/.h, display_memory.c/.h, free_words.c/.h, gen_pattern.c/.h, get_address.c/.h, invert_block.c/.h, led_control.c/.h,
logger.c/.h, timing_control.c/.h, verify_pattern.c/.h, write_pattern.c/.h, and mem_status.h
which are located in the source folder.
The main.c module contains the full execution sequence of the memory tests.
The allocate_words.c module contains the functionality for allocating dynamic memory on the heap. I use malloc for both the PC/Board versions.
The display_memory.c module contains the functionality for copying a peice of memory from a block of memory, and will display the copied memory in
log enabled mode.
The free_words.c module frees dynamically allocated memory from the heap using the free function. I use free for both the PC/Board versions.
The gen_pattern.c module takes a seed and XORs each byte memory block provided with that seed to create a deterministic pseudo random pattern.
The get_address.c module takes a base address and offet, and returns a new address with the comibined base address and offset.
The invert_block.c module takes a block of memory and inverts a designated amount of bytes by XORing with 0xFF.
The led_control.c module provides the functionality of commanding the board's LED to GREEN, RED, BLUE, or OFF.
the logger.c module provides the functionality of logginc blocks of memory/messages.
The timing_control.c module provides the ability to delay through waiting clock cycles between test runs, to allow the LED/log 
prints to be visible.
The verify_pattern.c module generates a pattern based on a seed, and verifies it matches a block of memory. The pattern generated to verify 
is output when logging is enabled. If the verification fails, the addresses and values at those addresses will be logged as well.
The write_pattern.c module writes a generated pattern based on a seed to a block of memory.
The mem_status.h header includes the enum definition for the mem_status return type.
I wrote the makefile by hand. The makefile has the ability to build 4 different targets.
I had difficulty with doing the bound checks.
fb_run (LED enabled and logging disabled), fb_debug (LED and logging enabled), pc_run (LED and logging disabled), and pc_debug (LED disabled and logging enabled).
Depending on the target built, different sections of the source files I implemented will be used.
- The fb_run (LED enabled and logging disabled) target builds with the FB_RUN build flag.
- The fb_debug (LED and logging enabled) target builds with the FB_DEBUG build flag.
- The pc_run (LED and logging disabled) target builds with the PC_RUN build flag. Nothing really outputs for this one, but the test runs in the background.
- The pc_debug (LED disabled and logging enabled) target builds with the PC_DEBUG build flag.

# All build targets will generate their final .AXF /.exe file in the debug folder in ECEN5813_Project_3

Building the fb_run target requires the following steps:

- Right click on ECEN5813_Project_3 and click Clean Project
- Right click on ECEN5813_Project_3 and go to properties
- In properties navigate to the C/C++ Build tab
- Under Builder Settings, Builder, uncheck Use Default Build Command
- In the Build Command option use "make fb_run -j12"
- Under Builder Settings, Makefile generation uncheck Generate Makefile Automatically
- Under Builder Settings, Build location, Build directory enter ECEN5813_Project_3 workspace path
- My current path for my PC is C:\Users\trist\Documents\MCUXpressoIDE_11.0.1_2563\workspace\ECEN5813_Project_3, as an example
- Click Apply, and Apply and Close buttons on Builder Settings Tab
- Right click on ECEN5813_Project_3 and click Build Project
- Verify in Console perspective, the fb_run target build completed successfully
- ECEN5813_Project_3.axf for fb_run target can be found in debug\ECEN5813_Project_3.axf

Running the fb_run target requires the following steps:

- Create run/debug configuration for loading debug\ECEN5813_Project_3.axf, and run/debug on board.

Building the fb_debug target requires the following steps:

- Right click on ECEN5813_Project_3 and click Clean Project
- Right click on ECEN5813_Project_3 and go to properties
- In properties navigate to the C/C++ Build tab
- Under Builder Settings, Builder, uncheck Use Default Build Command
- In the Build Command option use "make fb_debug -j12"
- Under Builder Settings, Makefile generation uncheck Generate Makefile Automatically
- Under Builder Settings, Build location, Build directory enter ECEN5813_Project_3 workspace path
- My current path for my PC is C:\Users\trist\Documents\MCUXpressoIDE_11.0.1_2563\workspace\ECEN5813_Project_3, as an example
- Click Apply, and Apply and Close buttons on Builder Settings Tab
- Right click on ECEN5813_Project_3 and click Build Project
- Verify in Console perspective, the fb_run target build completed successfully
- ECEN5813_Project_3.axf for fb_debug target can be found in debug\ECEN5813_Project_3.axf

Running the fb_debug target requires the following steps:

- Create run/debug configuration for loading debug\ECEN5813_Project_3.axf, and run/debug on board.
- Observe terminal serial port for outputs.

Building the pc_run target requires the following steps:

- Right click on ECEN5813_Project_3 and click Clean Project
- Right click on ECEN5813_Project_3 and go to properties
- In properties navigate to the C/C++ Build tab
- Under Builder Settings, Builder, uncheck Use Default Build Command
- In the Build Command option use "make pc_run -j12"
- Under Builder Settings, Makefile generation uncheck Generate Makefile Automatically
- Under Builder Settings, Build location, Build directory enter ECEN5813_Project_3 workspace path
- My current path for my PC is C:\Users\trist\Documents\MCUXpressoIDE_11.0.1_2563\workspace\ECEN5813_Project_3, as an example
- Click Apply Builder Settings Tab
- Under C/C++ Build, Enviornment, select Variable PATH and edit
- Append path to gcc compiler. I am using the path C:\MinGW\bin since I'm running gcc on Windows.
- In the Enviornment tab click Apply, and the Apply and Close
- Right click on ECEN5813_Project_3 and click Build Project
- Verify in Console perspective, the pc_run target build completed successfully
- pc_run.exe for pc_run target can be found in debug\pc_run.exe

Running the pc_run target requires the following steps:

- Create run C run configuration for debug\pc_run.exe and run locally in IDE. 
- Observe Console for outputs.

Building the pc_debug target requires the following steps:
- Right click on ECEN5813_Project_3 and click Clean Project
- Right click on ECEN5813_Project_3 and go to properties
- In properties navigate to the C/C++ Build tab
- Under Builder Settings, Builder, uncheck Use Default Build Command
- In the Build Command option use "make pc_debug -j12"
- Under Builder Settings, Makefile generation uncheck Generate Makefile Automatically
- Under Builder Settings, Build location, Build directory enter ECEN5813_Project_3 workspace path
- My current path for my PC is C:\Users\trist\Documents\MCUXpressoIDE_11.0.1_2563\workspace\ECEN5813_Project_3, as an example
- Click Apply Builder Settings Tab
- Under C/C++ Build, Enviornment, select Variable PATH and edit
- Append path to gcc compiler. I am using the path C:\MinGW\bin since I'm running gcc on Windows.
- In the Enviornment tab click Apply, and the Apply and Close
- Right click on ECEN5813_Project_3 and click Build Project
- Verify in Console perspective, the pc_debug target build completed successfully
- pc_debug.exe for pc_debug target can be found in debug\pc_debug.exe

Running the pc_debug target requires the following steps:

- Create run C run configuration for debug\pc_debug.exe and run locally in IDE. 
- Observe Console for outputs.

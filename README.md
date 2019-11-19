# ECEN5813 Project 5 Readme
# Tristan Duenas
# Project Demonstration YouTube Video Link https://www.youtube.com/watch?v=st7tk26AP1k&feature=share

# Bruce Montgomery has approved not needing to submit an oscilloscope trace due to distance learning
resource limitations

# Project Files
The source folder of the ECEN5813_Project_5 repository contains all of the files created by hand for this project.
# The FMEA is located in the main project directory, and is called ECEN 5813 Project 5 FMEA.xlsx

uart0_control.c/.h: Contains implementation for UART0 initialization for polling/interrupt driven approaches
at a baud rate of 115200, UART0 transmit for polling/interrupt driven approaches, and UART0 receiving for 
polling/interrupt driven approaches. UART0 echo functionality for both polling/interrupt driven approaches is 
also defined. In the interrupt driven approach the UART0 IRQ handler is triggered upon receiving a character, 
transmitting a character, or if an error occurs, upon which it will either transmit, receive, 
or handle the error.

circular_buffer.c/.h: Contains definition for circular buffer, which includes a statically defined array of
1024 characters, a head, a tail, and a count. The functionality for adding an item, removing and item, 
checking if the buffer is full, checking if the buffer is empty, checking if the buffer is initialized,
and checking if the buffer pointer is valid is also defined. Once buffer is full characters can only be 
added once characters are removed. Both the head and tail indices wrap arround the buffer successfully, 
and are tested in the uCUNIT tests.

application.c/.h: Contains definitions for running the application mode functionality, including producing 
statistics on words entered through the terminal, outputting the ASCII character counts in order. I created an
array called asciiTracker that is large enough to fit a count for each type of ASCII character, as a character 
is received the count at its respective index is incremented. # Once the carriage return character has been received
# the application mode will output the current ASCII statistics for what has been entered through the terminal.
Contains definitions for application mode initialization, process and display received character statistics, 
update ASCII tracker, and display ASCII tracker.

timing_control.c/.h: Contains new definition for SysTick initialization, time count incrementing the SysTick 
interrupt handler, and getting a time stamp that shows how much time has passed since the program started in 
"HH:MM:SS:n" format.

logger.c/.h: Contains new function definitions for Project 5, as well as time stamps in logging integer/string 
messages, which are received from timing_control.c.

project_5_tests.c/.h: Contains 6 test cases with 23 checks, including, circular buffer initialization test, circular buffer data access test,
circular buffer, wrap remove test, circular buffer wrap add test, circular buffer over fill test, and circular buffer over empty test.
# In video demonstration all 23 check cases were included but it only displayed 4 test cases since I was missing UCUNIT_TestcaseEnd() 
at the end of the last 2 test cases, but they all passed.

# Observations
I experienced issues with using dynamic memory with the global rx/tx circular buffers, and when debugging the memory addresses could not be found.
I instead used a static buffer in the definition of the circular buffer since I did not do the extra credit which requires re-allocating memory.
I was unable to get an oscilloscope trace of the UART communication because I don't have a lab nearby where I can use one. Bruce Montgomery gave 
me approval to not have to use one and not get a grade penalty since I'm a distance learner.
I found it difficult at first to find out when to enable the UART0 transmit/receive interrupts. I enabled the receive interrupt during 
initialization in the interrupt driven mode, and enabled the transmit interrupt only when needing to transmit.

# Installation/Execution Notes
I used the auto-generated makefile for this project.
Building requires performing a clean, then rebuild.
Building for the ECHO build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the ECHO_MODE
ECHO mode can be run with polling or interrupt driven builds. DEBUG adds debugging output.
Building for the APPLICATION build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the APPLICATION_MODE
Application mode should be run with the interrupt driven builds. DEBUG adds debugging output.
Building for the INTERRUPT build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the UART_INTERRUPT_DRIVEN
Building for the POLLING build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the UART_POLLING_DRIVEN
Building for the TEST build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the TEST_FLAG
Building for the DEBUG build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the DEBUG_FLAG
Building for the STATUS build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the STATUS_FLAG
ECEN5813_Project_5.axf is stored in the Debug folder of the repository and can be run through the GDB PEMicro Interface Debugging Debug configurations using the axf file generated.
# ECEN5813 Project 4 Readme
# Tristan Duenas
# Project Demonstration YouTube Video Link 

# Bruce Montgomery has approved late submission of Project 4 without any grade penalty due to distance learning resource limitations.

# Due to distance learning resource limitations Bruce Montgomery has excluded me from having to provide an Oscilloscope trace of I2C traffic between KL25Z and TMP102 sensor.
# The TCS3472 Color Light-To-Digital Converter with IR Filter was used in place of the Temp102 Temperature Sensor due to issues with connectivity to board.
# Due to distance learning resource limitations Bruce Montgomery has excluded me from having to use the Temp102 sensor, and I have used the TCS3472 Color Sensor in its place (https://cdn-shop.adafruit.com/datasheets/TCS34725.pdf). As a result I was also excluded from having to complete the alert functionality that was required of the Temp102 sensor.

# Project Files
The source folder of the ECEN5813_Project_4 repository contains all of the files created by hand for this project.

color_sensor.c/.h: Defines color_sensor_init for TCS3472 I2C initialization, color_sensor_POST_Test for performing a POST test on the color sensor by checking that the device ID is 0x44, getColorSensorRegisterValue for requesting a register value such as color from the color sensor.

i2c_control.c/.h: Defines i2c_wait that waits until either the I2C1 Status register is in a successful state after being masked/shifted or if a timeout of 50 mSec occurs. For instance, flags such as I2C_S_BUSY, I2C_IICIF, I2C_RXAK, and I2C_S_IAAS are checked. Also defines i2c_transmit for transmitting data from the master to the slave device. 
The process for transmitting data is make sure line isn't busy, switch to transmit mode, set start bit if start is specified, set restart bit if specified, set data register, wait for IICIF bit to be true, clear IICIF bit, make sure arbitration bit isn't set, wait for acknowledgemnt from slave device or for the slave device to be in IAAS mode.
I noticed when IAAS is true there are cases where the RXAK is not true.

state_machines.c/.h: Defines run_state_machines, run_state_machine_one, and run_state_machine_two. The run_state_machine_one function performs a red color reading of the color sensor red color register, over 4 iterations, averaging the red color read in on each iteration. 
If the I2C read from the color sensor times out while waiting or fails, the state machine jumps to the disconnected state. Once 4 successful color sensor readings occur, state machine two will be jumped two where it will perform the same functionality. Once state machine two
completes 4 successful color sensor readings then the state machine completed state is jumped to and the state machines will stop running. The run_state_machines function runs state machine one and state machine two.

logger.c/.h: Includes logger functionality from project 3, with the extended functionality required of project 4. 
The function enum list has been defined in functions_enum_list.c/.h. The functions enum has been used to provide a string with a function name when 
a function logs a message. Build flags TEST_FLAG, DEBUG_FLAG, and STATUS_FLAG are used in logger.c to determine when to log a message.

functions_enum_list.c/.h: Defines an enum list of all of the functions I've defined in project 4, as well as a function to lookup a functions name string based on its enum.

led_control.c/.h: Defines LED control functionality, same as what was defined in previous projects.

timing_control.c/.h: Defines ability to delay clock cycles, same as what was defined in previous projects.

main.c: Runs Project 4 uCUnit tests, TCS3472 Color Sensor POST test, and runs TCS3472 Color sensor state machines.

project_4_tests.c/.h: Defines 10 uCUnit tests.

# Observations
Sensor connectivity and hardware debugging was a major issue for me as a distance learner. I don't have the lab resource that on-campus students do. I did not have a multi-meter or an oscilloscope. I was lucky enough to have a soldering iron. 
I had to purchase the pin connectors online which took a few days to acquire. I have experience soldering which helped, but if I didn't this project would have been even more difficult.
When using the Temp102 sensor I did not receive acknowledgement back. When testing the same code with my spare TCS3472 color sensor I did receive acknowledgements, which is why I used it instead to demonstrate my codes I2C capability.
I discussed this with Bruce Montgomery.
One of the difficulties I faced with using the TCS3472 sensor was that the I2C line would stay busy even when there wasn't any communication. This result in unexpected timeouts.
POST test on the TCS3472 sensor runs successfully but a few timeouts occur first due to the line being busy when it shouldn't be.
I also noticed that when sending the address to the TCS3472 in its 7 bit write format instead of 8 bit format, the IAAS bit was set more consistently than the RXACK bit when transmitting. I'm not sure why that is.

# Installation/Execution Notes
# There are warnings while building due to the inclusion of the uCUnit library. There are static variables defined that the compiler claims aren't being used even though they are.
# The color sensor is wired ground to ground, Vin to 3v3 volts, SCL to SCL I2C1 PTE1, SDA to SDA I2C1 PTE0. 
I used the auto-generated makefile for this project.
Building requires performing a clean, then rebuild.
Building for the TEST build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the TEST_FLAG
Building for the DEBUG build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the DEBUG_FLAG
Building for the STATUS build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the STATUS_FLAG
ECEN5813_Project_4.axf is stored in the Debug folder of the repository and can be run through the GDB PEMicro Interface Debugging Debug configurations using the axf file generated.


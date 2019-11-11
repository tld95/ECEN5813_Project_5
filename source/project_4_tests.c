#include "project_4_tests.h"

void runProject4Tests()
{
	UCUNIT_Init();

	// Test 1
	status deviceStatus = i2c_wait(I2C_C1_IICEN_MASK, I2C_C1_IICEN_SHIFT, 1);
	UCUNIT_CheckIsEqual(deviceStatus, PASSED);

	// Test 2
	deviceStatus = i2c_wait(I2C_S_RXAK_MASK, I2C_S_RXAK_SHIFT, 1);
	UCUNIT_CheckIsEqual(deviceStatus, FAILED);

	// Test 3
	char nameOne[100];
	getFunctionName(COLOR_SENSOR_INIT, nameOne);
	UCUNIT_CheckIsEqual(nameOne, "Color Sensor Init");

	// Test 4
	char nameTwo[100];
	getFunctionName(I2C_WAIT, nameTwo);
	UCUNIT_CheckIsEqual(nameTwo, "I2C Wait");

	// Test 5
	char nameThree[100];
	getFunctionName(RUN_STATE_MACHINES, nameThree);
	UCUNIT_CheckIsEqual(nameThree, "Run State Machines");

	// Test 6
	char nameFour[100];
	getFunctionName(RUN_STATE_MACHINE_TWO, nameFour);
	UCUNIT_CheckIsEqual(nameFour, "Run State Machine Two");

	// Test 7
	char nameFive[100];
	getFunctionName(I2C_TRANSMIT, nameFive);
	UCUNIT_CheckIsEqual(nameFive, "I2C Transmit");

	// Test 8
	char nameSix[100];
	getFunctionName(GET_COLOR_SENSOR_REGISTER_VALUE, nameSix);
	UCUNIT_CheckIsEqual(nameSix, "Get Color Sensor Register Value");

	// Test 9
	char nameSeven[100];
	getFunctionName(LED_CONTROL, nameSeven);
	UCUNIT_CheckIsEqual(nameSeven, "LED Control");

	// Test 10
	char nameEight[100];
	getFunctionName(MAIN, nameEight);
	UCUNIT_CheckIsEqual(nameEight, "Main");

	UCUNIT_WriteSummary();
	UCUNIT_Shutdown();
}

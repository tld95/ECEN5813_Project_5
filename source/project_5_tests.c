#include <project_5_tests.h>

void runProject5Tests()
{
	UCUNIT_Init();

	circularBufferInitTest();
	circularBufferDataAccessTest();
	circularBufferWrapRemoveTest();
	circularBufferWrapAddTest();
	circularBufferOverfillTest();
	circularBufferOverEmptyTest();

	UCUNIT_WriteSummary();
	UCUNIT_Shutdown();
}

void circularBufferInitTest()
{
	UCUNIT_TestcaseBegin("Circular Buffer Init");
	circularBuffer testBuffer;
	circularBufferErrors status = NO_ERROR;
	status = initializeBuffer(&testBuffer);
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	UCUNIT_TestcaseEnd();
}

void circularBufferDataAccessTest()
{
	UCUNIT_TestcaseBegin("Circular Buffer Test Data Access");
	circularBuffer testBuffer;
	circularBufferErrors status = NO_ERROR;
	status |= initializeBuffer(&testBuffer);
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	uint8_t dataAdded = 'A';
	status |= addItem(&testBuffer, dataAdded);
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	uint8_t dataRemoved;
	status |= removeItem(&testBuffer, &dataRemoved);
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	UCUNIT_CheckIsEqual(dataAdded, dataRemoved);
	UCUNIT_TestcaseEnd();
}

void circularBufferWrapRemoveTest()
{
	UCUNIT_TestcaseBegin("Circular Buffer Wrap Remove Test");
	circularBuffer testBuffer;
	circularBufferErrors status = NO_ERROR;
	status |= initializeBuffer(&testBuffer);
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	uint8_t dataAdded = 'A';

	// Fill Circular Buffer
	for (uint32_t index = 0; index < MAX_BUFFER_SIZE; index++)
	{
		status |= addItem(&testBuffer, dataAdded);
	}
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	UCUNIT_CheckIsEqual(testBuffer.count, MAX_BUFFER_SIZE);

	// Remove all elements from Circular Buffer
	uint8_t dataRemoved;
	for (uint32_t index = 0; index < MAX_BUFFER_SIZE; index++)
	{
		status |= removeItem(&testBuffer, &dataRemoved);
	}
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	UCUNIT_CheckIsEqual(testBuffer.tail, 0);
	UCUNIT_TestcaseEnd();
}

void circularBufferWrapAddTest()
{
	UCUNIT_TestcaseBegin("Circular Buffer Wrap Add Test");
	circularBuffer testBuffer;
	circularBufferErrors status = NO_ERROR;
	status |= initializeBuffer(&testBuffer);
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	uint8_t dataAdded = 'A';

	// Fill Circular Buffer
	for (uint32_t index = 0; index < MAX_BUFFER_SIZE; index++)
	{
		status |= addItem(&testBuffer, dataAdded);
	}
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	UCUNIT_CheckIsEqual(testBuffer.count, MAX_BUFFER_SIZE);

	uint8_t dataRemoved;
	status |= removeItem(&testBuffer, &dataRemoved);
	UCUNIT_CheckIsEqual(status, NO_ERROR);

	UCUNIT_CheckIsEqual(testBuffer.head, 0);
	status |= addItem(&testBuffer, dataAdded);
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	UCUNIT_CheckIsEqual(testBuffer.head, 1);
	UCUNIT_TestcaseEnd();
}

void circularBufferOverfillTest()
{
	UCUNIT_TestcaseBegin("Circular Buffer Overfill Test");
	circularBuffer testBuffer;
	circularBufferErrors status = NO_ERROR;
	status |= initializeBuffer(&testBuffer);
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	uint8_t dataAdded = 'B';

	// Fill Circular Buffer
	for (uint32_t index = 0; index < MAX_BUFFER_SIZE; index++)
	{
		status |= addItem(&testBuffer, dataAdded);
	}
	UCUNIT_CheckIsEqual(status, NO_ERROR);
	UCUNIT_CheckIsEqual(testBuffer.count, MAX_BUFFER_SIZE);

	status |= addItem(&testBuffer, dataAdded);
	UCUNIT_CheckIsEqual(status, BUFFER_FULL);
}

void circularBufferOverEmptyTest()
{
	UCUNIT_TestcaseBegin("Circular Buffer Over Empty Test");
	circularBuffer testBuffer;
	circularBufferErrors status = NO_ERROR;
	status |= initializeBuffer(&testBuffer);
	UCUNIT_CheckIsEqual(status, NO_ERROR);

	uint8_t dataRemoved;
	status |= removeItem(&testBuffer, &dataRemoved);
	UCUNIT_CheckIsEqual(status, BUFFER_EMPTY);
}

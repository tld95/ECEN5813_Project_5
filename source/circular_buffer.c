/*
 *  PES Project Five Circular Buffer Control source code implementation
 *	Tristan Duenas
 *	Refereneces:
 *	PES CL19-L21 Data Handling.pdf
 */

#include "circular_buffer.h"

circularBufferErrors initializeBuffer(circularBuffer *cBuffer)
{
	cBuffer->length = MAX_BUFFER_SIZE;
	cBuffer->head = 0;
	cBuffer->tail = 0;
	cBuffer->count = 0;
	return checkIfBufferIsInitialized(cBuffer);
}

circularBufferErrors destroyBuffer(circularBuffer *cBuffer)
{
	free(cBuffer->buffer);
	return NO_ERROR;
}

circularBufferErrors addItem(circularBuffer *cBuffer, uint8_t data)
{
	// Referenced PES CL19-L21 Data Handling.pdf
	circularBufferErrors status = NO_ERROR;
	status = checkIfBufferPointerIsValid(cBuffer);
	if (status != NO_ERROR)
	{
		return status;
	}
	status = checkIfBufferIsFull(cBuffer);
	if (status != NO_ERROR)
	{
		return status;
	}
	cBuffer->buffer[cBuffer->head] = data;
	cBuffer->head = (cBuffer->head + 1) & (cBuffer->length-1);
	cBuffer->count++;
	return status;
}

circularBufferErrors removeItem(circularBuffer *cBuffer, uint8_t *data)
{
	// Referenced PES CL19-L21 Data Handling.pdf
	circularBufferErrors status = NO_ERROR;
	status = checkIfBufferPointerIsValid(cBuffer);
	if (status != NO_ERROR)
	{
		return status;
	}
	status = checkIfBufferIsEmpty(cBuffer);
	if (status != NO_ERROR)
	{
		return status;
	}
	*data = cBuffer->buffer[cBuffer->tail];
	cBuffer->tail = (cBuffer->tail + 1) & (cBuffer->length-1);
	cBuffer->count--;
	return status;
}

circularBufferErrors checkIfBufferIsFull(circularBuffer *cBuffer)
{
	if (cBuffer->count == cBuffer->length)
	{
		return BUFFER_FULL;
	}
	return NO_ERROR;
}

circularBufferErrors checkIfBufferIsEmpty(circularBuffer *cBuffer)
{
	if (cBuffer->count == 0)
	{
		return BUFFER_EMPTY;
	}
	return NO_ERROR;
}

circularBufferErrors checkIfBufferIsInitialized(circularBuffer *cBuffer)
{
	if (checkIfBufferPointerIsValid(cBuffer) != NO_ERROR)
	{
		return BUFFER_UNINITIALIZED;
	}
	return NO_ERROR;
}

// Checks if buffer pointer is valid
circularBufferErrors checkIfBufferPointerIsValid(circularBuffer *cBuffer)
{
	if ((cBuffer == NULL) || (cBuffer->buffer == NULL))
	{
		return BUFFER_POINTER_INVALID;
	}
	return NO_ERROR;
}


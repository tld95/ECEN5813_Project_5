#ifndef PROJECT_4_TESTS
#define PROJECT_4_TESTS

#include "System.h"
#include "uCUnit.h"
#include "MKL25Z4.h"
#include "circular_buffer.h"

void runProject5Tests();
void circularBufferInitTest();
void circularBufferDataAccessTest();
void circularBufferWrapRemoveTest();
void circularBufferWrapAddTest();
void circularBufferOverfillTest();
void circularBufferOverEmptyTest();
void circularBufferDestroyTest();

#endif

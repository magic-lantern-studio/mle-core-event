// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2019 Wizzer Works
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  For information concerning this header file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

// Include Google Test header files.
#include "gtest/gtest.h"

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"
#include "mle/MleEventDispatcher.h"

enum {
    EVENT_ONE = 1,
    EVENT_TWO = 2,
    EVENT_THREE = 3,
    EVENT_FOUR = 4,
    EVENT_FIVE = 5
};

// Callback event handler.
int eventHndlr(MleEvent event,void *callData,void *clientData)
{
    // Declare local variables.
    char *clientStr = (char *)clientData;
    char *callStr = (char *)callData;

    fprintf(stdout,"Received event %ld: processing data %s, %s\n",event,clientStr,callStr);

    return(0);
}

TEST(MleEventDispatcherTest, DefaultConstructor) {
    // This test is named "DefaultConstructor", and belongs to the "MleEventDispatcherTest"
    // test case.

    MleEventDispatcher *eventMgr = new MleEventDispatcher();
    EXPECT_TRUE(eventMgr != NULL);
}

TEST(MleEventDispatcherTest, Destructor) {
    // This test is named "Destructor", and belongs to the "MleEventDispatcherTest"
    // test case.

    MleEventDispatcher *eventMgr = new MleEventDispatcher();
    EXPECT_TRUE(eventMgr != NULL);

    delete eventMgr;
}

TEST(MleEventDispatcherTest, InstallEvent) {
    // This test is named "InstallEvent", and belongs to the "MleEventDispatcherTest"
    // test case.

    MleEventDispatcher *eventMgr = new MleEventDispatcher();
    EXPECT_TRUE(eventMgr != NULL);

    // Install an event.
    MleCallbackId cbId[5];
    for (int i = 0; i < 5; i++) cbId[i] = 0;
    cbId[0] = eventMgr->installEventCB(EVENT_ONE,eventHndlr,(void *)"test");
    EXPECT_TRUE(cbId[0] != 0);

    delete eventMgr;
}

TEST(MleEventDispatcherTest, UninstallEvent) {
    // This test is named "UninstallEvent", and belongs to the "MleEventDispatcherTest"
    // test case.

    MleEventDispatcher *eventMgr = new MleEventDispatcher();
    EXPECT_TRUE(eventMgr != NULL);

    // Install an event.
    MleCallbackId cbId[5];
    for (int i = 0; i < 5; i++) cbId[i] = 0;
    cbId[0] = eventMgr->installEventCB(EVENT_ONE,eventHndlr,(void *)"test");
    EXPECT_TRUE(cbId[0] != 0);

    // Remove event.
    MlBoolean status = eventMgr->uninstallEvent(EVENT_ONE);
    EXPECT_TRUE(status);

    delete eventMgr;
}

TEST(MleEventDispatcherTest, DispatchEvent) {
    // This test is named "DispatchEvent", and belongs to the "MleEventDispatcherTest"
    // test case.

    MleEventDispatcher *eventMgr = new MleEventDispatcher();
    EXPECT_TRUE(eventMgr != NULL);

    // Install an event with callback used for dispatching.
    MleCallbackId cbId[5];
    for (int i = 0; i < 5; i++) cbId[i] = 0;
    cbId[0] = eventMgr->installEventCB(EVENT_ONE,eventHndlr,(void *)"test");
    EXPECT_TRUE(cbId[0] != 0);

    // Test for successful dispatch.
    int cbRetValue = eventMgr->dispatchEvent(EVENT_ONE,(void *)"Unit test.");
    EXPECT_TRUE(cbRetValue == 0);

    // Remove event and test for unsuccessful dispatch.
    MlBoolean status = eventMgr->uninstallEvent(EVENT_ONE);
    EXPECT_TRUE(status);
    cbRetValue = eventMgr->dispatchEvent(EVENT_ONE,(void *)"Unit test.");
    EXPECT_TRUE(cbRetValue != 0);

    delete eventMgr;
}

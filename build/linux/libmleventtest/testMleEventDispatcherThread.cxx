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

// Include system header files.
#include <pthread.h>

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
    EVENT_FIVE = 5,
    EVENT_SIX = 6,
    EVENT_SEVEN = 7,
    EVENT_EIGHT = 8,
    EVENT_NINE = 9,
    EVENT_TEN = 10
};

// Callback event handler.
static int eventHndlr(MleEvent event,void *callData,void *clientData)
{
    // Declare local variables.
    char *clientStr = (char *)clientData;
    char *callStr = (char *)callData;

    fprintf(stdout,"Received event %ld: processing data %s, %s\n",event,clientStr,callStr);

    return(0);
}

// Array of thread identifiers.
static pthread_t tid[2];

// Thread function for event installation.
static void *installevent(void *arg)
{
    MleEventDispatcher *eventMgr = (MleEventDispatcher *)arg;
    EXPECT_TRUE(eventMgr != NULL);

    //printf("installevent thread.\n");

    MleCallbackId cbId[10];
    for (int i = 0; i < EVENT_TEN; i++) {
        // Install an event.
        cbId[i] = eventMgr->installEventCB(i+1,eventHndlr,(void *)"test");
        EXPECT_TRUE(cbId[i] != 0);
    }

    pthread_exit(NULL);
}

TEST(MleEventDispatcherThreadTest, InstallEvent) {
    // This test is named "InstallEvent", and belongs to the "MleMleEventDispatcherThreadTest"
    // test case.

    MleEventDispatcher *eventMgr = new MleEventDispatcher();
    EXPECT_TRUE(eventMgr != NULL);

    int i = 0;
    while(i < 2)
    {
        int error = pthread_create(&(tid[i]), NULL, &installevent, eventMgr);
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));
        i++;
    }

    // Make sure to wait for thread completion before exiting test.
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    // Validate that all 10 events were installed twice, once by each thread,
    // by dispatching them.
    for (int i = 1; i <= EVENT_TEN; i++)
    {
        int cbRetValue = eventMgr->dispatchEvent(i,(void *)"Unit test.");
        EXPECT_TRUE(cbRetValue == 0);
    }

    delete eventMgr;
}


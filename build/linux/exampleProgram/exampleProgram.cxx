// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2015-2019 Wizzer Works
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
//  For information concerning this source file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

//
// Unit test for Event Dispatch Manager.
//

// Include system header files.
#include <stdio.h>

// Include Magic Lantern header files.
#include "mle/mlMalloc.h"
#include "mle/mlAssert.h"
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
    EVENT_TEN = 10,
    NUM_EVENTS = 10
};


MleEventDispatcher *g_evMgr;


int eventHndlr(MleEvent event,void *callData,void *clientData)
{
    // Declare local variables.
    char *clientStr = (char *)clientData;
    char *callStr = (char *)callData;

    fprintf(stdout,"Received event %d: processing data %s, %s\n",event,clientStr,callStr);

    return(0);
}


int mleRTMainLoop()
{
    /* Declare local variable. */
    int i;
    static char msg[] = "Hello World!";

    for (i = 0; i <= NUM_EVENTS; i++) {
        g_evMgr->dispatchEvent(i,(void *)msg);
    }

    return(0);
}


int main(int argc,char **argv)
{
    // Declare local variables.
    MleCallbackId cbId[14];

    // Initialize event manager.
    g_evMgr = new MleEventDispatcher();
    MLE_ASSERT(evMgr);

    // Install event callbacks.
    cbId[0] = g_evMgr->installEventCB(EVENT_ONE,eventHndlr,(void *)"one");
    cbId[1] = g_evMgr->installEventCB(EVENT_TWO,eventHndlr,(void *)"two");
    cbId[2] = g_evMgr->installEventCB(EVENT_THREE,eventHndlr,(void *)"three");
    cbId[3] = g_evMgr->installEventCB(EVENT_FOUR,eventHndlr,(void *)"four");
    cbId[4] = g_evMgr->installEventCB(EVENT_FIVE,eventHndlr,(void *)"five");
    cbId[5] = g_evMgr->installEventCB(EVENT_SIX,eventHndlr,(void *)"six");
    cbId[6] = g_evMgr->installEventCB(EVENT_SEVEN,eventHndlr,(void *)"seven");
    cbId[7] = g_evMgr->installEventCB(EVENT_EIGHT,eventHndlr,(void *)"eight");
    cbId[8] = g_evMgr->installEventCB(EVENT_NINE,eventHndlr,(void *)"nine");
    cbId[9] = g_evMgr->installEventCB(EVENT_TEN,eventHndlr,(void *)"ten");

    cbId[10] = g_evMgr->installEventCB(EVENT_ONE,eventHndlr,(void *)"one A");
    cbId[11] = g_evMgr->installEventCB(EVENT_ONE,eventHndlr,(void *)"one B");
    cbId[12] = g_evMgr->installEventCB(EVENT_THREE,eventHndlr,(void *)"three A");
    cbId[13] = g_evMgr->installEventCB(EVENT_THREE,eventHndlr,(void *)"three B");

    // Disable some events.
    g_evMgr->disableEvent(EVENT_SIX);
    g_evMgr->disableEvent(EVENT_SEVEN);
    g_evMgr->disableEvent(EVENT_EIGHT);
    g_evMgr->disableEvent(EVENT_NINE);

    // Execution cycle.
    fprintf(stdout,"Executing Test 1.\n");
    mleRTMainLoop();

    // Uninstall some events.
    g_evMgr->uninstallEvent(EVENT_SIX);
    g_evMgr->uninstallEvent(EVENT_SEVEN);
    g_evMgr->uninstallEvent(EVENT_EIGHT);
    g_evMgr->uninstallEvent(EVENT_NINE);

    // Execution cycle.
    fprintf(stdout,"Executing Test 2.\n");
    mleRTMainLoop();

    // Uninstall/disable some specific event callbacks.
    g_evMgr->uninstallEventCB(EVENT_THREE,cbId[12]);
    g_evMgr->uninstallEventCB(EVENT_THREE,cbId[13]);
    g_evMgr->disableEventCB(EVENT_ONE,cbId[10]);
    g_evMgr->disableEventCB(EVENT_ONE,cbId[11]);

    // Execution cycle.
    fprintf(stdout,"Executing Test 3.\n");
    mleRTMainLoop();

    // reset the priority of an event callback
    g_evMgr->changeEventCBPriority(EVENT_ONE,cbId[0],2);
    g_evMgr->changeEventCBPriority(EVENT_ONE,cbId[10],1);
    g_evMgr->changeEventCBPriority(EVENT_ONE,cbId[11],0);
    g_evMgr->enableEventCB(EVENT_ONE,cbId[10]);
    g_evMgr->enableEventCB(EVENT_ONE,cbId[11]);

    // execution cycle
    fprintf(stdout,"Executing Test 4.\n");
    mleRTMainLoop();

    return(0);
}

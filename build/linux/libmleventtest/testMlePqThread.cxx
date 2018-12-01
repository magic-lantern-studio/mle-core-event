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
#include "mle/MlePq.h"

// Array of thread identifiers.
static pthread_t tid[2];

// Thread function for reading queue.
static void *readqueue(void *arg)
{
    MlePQ *q = (MlePQ *)arg;
    EXPECT_TRUE(q != NULL);

    //printf("readqueue thread.\n");

    for (int i = 0; i < MLE_INC_QSIZE; i++) {
        int index = q->findItem(i);
        EXPECT_TRUE(index > 0); // '0' indicates failure to find item.
    }

    pthread_exit(NULL);
}

// Thread function for writing queue.
static void *writequeue(void *arg)
{
    MlePQ *q = (MlePQ *)arg;
    EXPECT_TRUE(q != NULL);

    //printf("writequeue thread.\n");

    MlePQItem testItem;
    for (int i = 0; i < MLE_INC_QSIZE; i++) {
        testItem.m_key = i;
        testItem.m_data = (void *)i;
        q->insert(testItem);
    }

    pthread_exit(NULL);
}

// Thread function for examining queue.
static void *peekqueue(void *arg)
{
    MlePQ *q = (MlePQ *)arg;
    EXPECT_TRUE(q != NULL);

    //printf("peekqueue thread.\n");

    int count = 100;
    while (count > 0) {
        MlePQItem testItem;
        int nItems = q->getNumItems();
        for (int i = 1; i <= nItems; i++) {
            int exists = q->peek(i, testItem);
            EXPECT_TRUE(exists);
        }
        count--;
    }

    pthread_exit(NULL);
}

TEST(MlePqThreadTest, ReadQueue) {
    // This test is named "ReadQueue", and belongs to the "MlePqThreadTest"
    // test case.

    MlePQ *q = new MlePQ();
    EXPECT_TRUE(q != NULL);

    MlePQItem testItem;
    for (int i = 0; i < MLE_INC_QSIZE; i++) {
        testItem.m_key = i;
        testItem.m_data = (void *)i;
        q->insert(testItem);
    }
    EXPECT_EQ(q->getNumItems(), MLE_INC_QSIZE);

    int i = 0;
    while(i < 2)
    {
        int error = pthread_create(&(tid[i]), NULL, &readqueue, q);
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));
        i++;
    }

    // Make sure to wait for thread completion before exiting test.
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    delete q;
}

TEST(MlePqThreadTest, WriteQueue) {
    // This test is named "WriteQueue", and belongs to the "MlePqThreadTest"
    // test case.

    MlePQ *q = new MlePQ();
    EXPECT_TRUE(q != NULL);

    int i = 0;
    while(i < 2)
    {
        int error = pthread_create(&(tid[i]), NULL, &writequeue, q);
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));
        i++;
    }

    // Make sure to wait for thread completion before exiting test.
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    EXPECT_EQ(q->getNumItems(), 2*MLE_INC_QSIZE);

    delete q;
}

TEST(MlePqThreadTest, PeekQueue) {
    // This test is named "PeekQueue", and belongs to the "MlePqThreadTest"
    // test case.

    MlePQ *q = new MlePQ();
    EXPECT_TRUE(q != NULL);

    int error = pthread_create(&(tid[0]), NULL, &writequeue, q);
    if (error != 0)
        printf("\nThread can't be created : [%s]", strerror(error));
    error = pthread_create(&(tid[1]), NULL, &peekqueue, q);
    if (error != 0)
        printf("\nThread can't be created : [%s]", strerror(error));

    // Make sure to wait for thread completion before exiting test.
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    EXPECT_EQ(q->getNumItems(), MLE_INC_QSIZE);

    delete q;
}

// COPYRTIGH_BEGIN
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
#include "mle/MlePq.h"

TEST(MlePqTest, DefaultConstructor) {
    // This test is named "DefaultConstructor", and belongs to the "MlePqTest"
    // test case.

    MlePQ *q = new MlePQ();
    EXPECT_TRUE(q != NULL);
}

TEST(MlePqTest, InitSizeConstructor) {
    // This test is named "InitSizeConstructor", and belongs to the "MlePqTest"
    // test case.

    unsigned int size = 100;

    MlePQ *q = new MlePQ(size);
    EXPECT_TRUE(q != NULL);
    EXPECT_EQ(q->getNumItems(), 0);
}

TEST(MlePqTest, Insert) {
    // This test is named "Insert", and belongs to the "MlePqTest" test case.

    MlePQ *q = new MlePQ();
    EXPECT_TRUE(q != NULL);

    MlePQItem testItem;
    for (int i = 0; i < MLE_INC_QSIZE; i++) {
        testItem.m_key = i;
        testItem.m_data = (void *)i;
        q->insert(testItem);
    }
    EXPECT_EQ(q->getNumItems(), MLE_INC_QSIZE);

    delete q;
}

TEST(MlePqTest, Remove) {
    // This test is named "Remove", and belongs to the "MlePqTest" test case.

    MlePQ *q = new MlePQ();
    EXPECT_TRUE(q != NULL);

    MlePQItem testItem;
    for (int i = 0; i < MLE_INC_QSIZE; i++) {
        testItem.m_key = i;
        testItem.m_data = (void *)i;
        q->insert(testItem);
    }
    EXPECT_EQ(q->getNumItems(), MLE_INC_QSIZE);

    for (int i = 0; i < MLE_INC_QSIZE; i++) {
        q->remove(testItem);
    }
    EXPECT_EQ(q->getNumItems(), 0);

    delete q;
}

TEST(MlePqTest, InsertAndTest) {
    // This test is named "InsertAndTest", and belongs to the "MlePqTest" test case.

    MlePQ *q = new MlePQ();
    EXPECT_TRUE(q != NULL);

    MlePQItem testItem;
    testItem.m_key = 350;
    testItem.m_data = mlMalloc(1024);
    q->insert(testItem);
    EXPECT_EQ(q->getNumItems(), 1);

    q->remove(testItem);
    EXPECT_EQ(testItem.m_key, 350);
    EXPECT_TRUE(testItem.m_data != NULL);
    EXPECT_EQ(q->getNumItems(), 0);

    mlFree(testItem.m_data);
    delete q;
}

TEST(MlePqTest, Delete) {
    // This test is named "Delete", and belongs to the "MlePqTest" test case.

    MlePQ *q = new MlePQ();
    EXPECT_TRUE(q != NULL);

    MlePQItem testItem;
    for (int i = 0; i < MLE_INC_QSIZE; i++) {
        testItem.m_key = i;
        testItem.m_data = (void *)i;
        q->insert(testItem);
    }
    EXPECT_EQ(q->getNumItems(), MLE_INC_QSIZE);

    q->destroy();
    EXPECT_EQ(q->getNumItems(), MLE_INC_QSIZE-1);

    delete q;
}

TEST(MlePqTest, FindItem) {
    // This test is named "FindItem", and belongs to the "MlePqTest" test case.

    MlePQ *q = new MlePQ();
    EXPECT_TRUE(q != NULL);

    MlePQItem testItem;
    for (int i = 0; i < MLE_INC_QSIZE; i++) {
        testItem.m_key = i;
        testItem.m_data = (void *)i;
        q->insert(testItem);
    }
    EXPECT_EQ(q->getNumItems(), MLE_INC_QSIZE);

    for (int i = 0; i < MLE_INC_QSIZE; i++) {
        int index = q->findItem(i);
        EXPECT_TRUE(index > 0);  // '0' indicates failure to find item.
    }

    delete q;
}

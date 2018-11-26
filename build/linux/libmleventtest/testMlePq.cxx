// COPYRTIGH_BEGIN
// COPYRIGHT_END

// Include Google Test header files.
#include "gtest/gtest.h"

// Include Magic Lantern header files.
#include "mle/MlePq.h"

TEST(MlePqTest, DefaultConstrutor) {
    // This test is named "DefaultConstructor", and belongs to the "MlePqTest"
    // test case.

    MlePQ *q = new MlePQ();

    EXPECT_TRUE(q != NULL);
}

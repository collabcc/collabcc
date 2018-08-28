#include "driver/driver.h"

#if !BUILD_UNITTEST_ASSERTIONS
#error "test_assertions: BUILD_UNITTEST_ASSERTIONS is not defined true-like"
#endif

namespace common
{
    int assertion_failure_count = 0;
}
using common::assertion_failure_count;

static int expect_assertion_failure_count = 0;


#define SHOULD_FAIL(_Assertion) \
    do { \
        _Assertion; \
        TEST_ASSERT_EQ(assertion_failure_count, ++expect_assertion_failure_count); \
    } while(false)

#define SHOULD_SUCCEED(_Assertion) \
    do { \
        _Assertion; \
        TEST_ASSERT_EQ(assertion_failure_count, expect_assertion_failure_count); \
    } while(false)


void TestAssertionsShouldSucceed()
{
    assertion_failure_count = expect_assertion_failure_count = 0;

    //
    // Successful assertions
    //
    SHOULD_SUCCEED((ASSERT_LT(-1, 1)));
    SHOULD_SUCCEED((ASSERT_LE(1, 1)));
    SHOULD_SUCCEED((ASSERT_GT(10.0f, 2u)));
    SHOULD_SUCCEED((ASSERT_GE(1, 1)));
    SHOULD_SUCCEED((ASSERT_EQ(16.0, 16.0)));
    SHOULD_SUCCEED((ASSERT_NE(2u, (int)1)));

    SHOULD_SUCCEED((ASSERT_STR_LT("a", "b")));
    SHOULD_SUCCEED((ASSERT_STR_LE("a", (std::string)"a")));
    SHOULD_SUCCEED((ASSERT_STR_GT((char*)"b", (std::string)"a")));
    SHOULD_SUCCEED((ASSERT_STR_GE((char*)"bc", (char*)"basdf")));
    SHOULD_SUCCEED((ASSERT_STR_EQ((std::string)"emmm", (std::string)"emmm")));
    SHOULD_SUCCEED((ASSERT_STR_NE((std::string)"asdf", (char*)"emmm")));

    const void* const p1 = nullptr;
    const void* const p2 = &p1;
    SHOULD_SUCCEED((ASSERT_IS_NULL(p1)));
    SHOULD_SUCCEED((ASSERT_NOT_NULL(p2)));
}

void TestAssertionsShouldFail()
{
    assertion_failure_count = expect_assertion_failure_count = 0;

    SHOULD_FAIL((PANIC("There will be some 'Panic!'s (including this one)")));
    SHOULD_FAIL((PANIC("This **IS** expected! (including this one)")));

    //
    // Failed assertions
    //
    SHOULD_FAIL((ASSERT_LT(18, 2)));
    SHOULD_FAIL((ASSERT_LE(5.5, 1)));
    SHOULD_FAIL((ASSERT_GT(1, 2)));
    SHOULD_FAIL((ASSERT_GE(1, 1.1)));
    SHOULD_FAIL((ASSERT_EQ(true, false)));
    SHOULD_FAIL((ASSERT_NE(1u, (int)1)));

    SHOULD_FAIL((ASSERT_STR_LT("b", "a")));
    SHOULD_FAIL((ASSERT_STR_LE("b", (std::string)"a")));
    SHOULD_FAIL((ASSERT_STR_GT((char*)"ab", (std::string)"ac")));
    SHOULD_FAIL((ASSERT_STR_GE((char*)"ba", (char*)"basdf")));
    SHOULD_FAIL((ASSERT_STR_EQ((std::string)"asdf", (std::string)"emmm")));
    SHOULD_FAIL((ASSERT_STR_NE((std::string)"emmm", (char*)"emmm")));

    const void* const p1 = nullptr;
    const void* const p2 = &p1;
    SHOULD_FAIL((ASSERT_NOT_NULL(p1)));
    SHOULD_FAIL((ASSERT_IS_NULL(p2)));
}



DECLARE_UNITTEST(TestAssertionsShouldSucceed);
DECLARE_UNITTEST(TestAssertionsShouldFail);

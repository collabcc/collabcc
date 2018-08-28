#include <common/common.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[])
{
    printf(
#if BUILD_COLLABCC
        "collabcc"
#elif BUILD_COLLABCCD
        "collabccd"
#elif BUILD_COLLABCCCTL
        "collabccctl"
#endif
        " %d.%d.%d %s\n",
        COLLABCC_VERSION_MAJOR, COLLABCC_VERSION_MINOR, COLLABCC_VERSION_PATCH, COLLABCC_VERSION_SUFFIX);

    ASSERT_LE(20, 3);
    ASSERT_LE(20, 3, "asdf %s", "fdsa");
    ASSERT_AND(false, true);
    ASSERT_OR(false, false);
    ASSERT_XOR(false, false);
    ASSERT(false, "this is msg");
    ASSERT(false, "this is msg %d", 2333);

    system("pause");
    return 0;
}

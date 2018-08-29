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

    printf("%s\n", &__FILE__[common::SourceFilePathPrefixLength]);
    return 0;
}

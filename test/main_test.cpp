#define CTEST_MAIN
#define CTEST_SEGFAULT
#define __STDC_FORMAT_MACROS
#include <cinttypes>
#include <ctest.h>

int main(int argc, const char** argv)
{
    return ctest_main(argc, argv);
}
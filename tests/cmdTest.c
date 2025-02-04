#include <stdio.h>
#include <string.h>
#include "../src/utils/cmdUtil/cmdUtil.h"

/// @brief Test if the cmd runs correctly
/// @return test success: 0, test failed !0
int main()
{
    int appFlags;

    char* fileName = "cmdInput.txt";

    FILE* fptr = fopen(fileName, "w");

    fprintf(fptr, "1\n4\n2\n4\n3\n4\n4\n");

    fclose(fptr);

    fptr = freopen(fileName, "rw", stdin);

    CmdLaunch(&appFlags);

    fclose(fptr);

    remove(fileName);

    return 0;
}
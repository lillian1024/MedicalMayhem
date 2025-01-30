#include <stdio.h>
#include "config.h"

int main(int argc, char* argv[])
{
    printf("Hello from %s %d.%d\n", PROJECT_NAME, PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR);

    return 0
}
#include <stdio.h>
#include "config.h"
#include "utils/patientUtil/patientUtil.h"

int main(int argc, char* argv[])
{
    (void)argc; (void)argv;
    printf("Hello from %s %d.%d\n", PROJECT_NAME, PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR);

    return 0;
}

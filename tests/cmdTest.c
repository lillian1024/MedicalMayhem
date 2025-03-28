#include <stdio.h>
#include <string.h>
#include "../src/utils/cmdUtil/cmdUtil.h"
#include "../src/utils/saveUtil/saveUtil.h"

/// @brief Test if the cmd runs correctly
/// @return test success: 0, test failed !0
int main()
{
    int appFlags = 0;

    //FILE* file = fopen("build/save.txt", "r");

    LL_Sentinel* patientList;
    LL_Sentinel* doctorList;

    ReadSaveFile("build/save.txt", &patientList, &doctorList);

    WriteSaveFile("build/testSaveFile.txt", patientList, doctorList);

    return appFlags & APP_FLAG_ERROR;
}
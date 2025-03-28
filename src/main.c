#include <stdio.h>
#include "config.h"
#include "utils/patientUtil/patientUtil.h"
#include "doctorUtil.h"
#include "doctorScheduleUtil.h"
#include "saveUtil.h"
#include "cmdUtil.h"

void LoadData(void)
{
    LL_Sentinel* patientList;
    LL_Sentinel* doctorList;

    ReadSaveFile(saveDataPath, &patientList, &doctorList);

    LoadPatientList(patientList);
    LoadDoctorList(doctorList);
}

void InitilizeData(void)
{
    InitializePatientList();
    InitializeDoctorList();
}

void InitializeProgram(void)
{
    if (CanLoad(saveDataPath))
    {
        LoadData();
    }
    else
    {
        InitilizeData();
    }
}

void SaveData(void)
{
    WriteSaveFile(saveDataPath, GetAllPatientsRecords(), GetDoctorList());
}

void CloseProgram(void)
{
    SaveData();

    DisposePatientList();
    DisposeDoctorList();
}

void LoadSaveFilesPath(const char* appPath)
{
    LoadSavePaths(appPath);
}

int main(int argc, char* argv[])
{
    (void)argc;

    LoadSaveFilesPath(argv[0]);

    InitializeProgram();

    int appFlags = 0;
    CmdLaunch(&appFlags);

    CloseProgram();

    return 0;
}

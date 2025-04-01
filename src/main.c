#include <stdio.h>

#include "backupUtil.h"
#include "config.h"
#include "utils/patientUtil/patientUtil.h"
#include "doctorUtil.h"
#include "doctorScheduleUtil.h"
#include "saveUtil.h"
#include "cmdUtil.h"

void InitilizeData(void)
{
    InitializePatientList();
    InitializeDoctorList();
}

void LoadData(void)
{
    LL_Sentinel* patientList;
    LL_Sentinel* doctorList;

    if (!ReadSaveFile(saveDataPath, saveSchedulePath, &patientList, &doctorList))
    {
        InitilizeData();

        return;
    }

    LoadPatientList(patientList);
    LoadDoctorList(doctorList);
}

void InitializeProgram(void)
{
    StartBackupThread();
    if (CanLoad(saveDataPath) && CanLoad(saveSchedulePath))
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
    WriteSaveFile(saveDataPath, saveSchedulePath, GetAllPatientsRecords(), GetDoctorList());
}

void CloseProgram(void)
{
    SaveData();

    DisposePatientList();
    DisposeDoctorList();
}

void LoadSaveFilesPath(const char* appPath)
{
    LoadAppDirectory(appPath);
    LoadSavePaths(appPath);
}

int main(int argc, char* argv[])
{
    (void)argc, (void)argv;

    LoadSaveFilesPath(argv[0]);

    InitializeProgram();

    int appFlags = 0;
    CmdLaunch(&appFlags);

    CloseProgram();

    return 0;
}

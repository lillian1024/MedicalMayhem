#include "../llistUtil/llist.h"
#include "../patientUtil/patientUtil.h"
#include "../doctorUtil/doctorUtil.h"
#include "../doctorUtil/doctorScheduleUtil.h"

#ifndef SAVE_UTIL_H
#define SAVE_UTIL_H

extern char* saveDataPath;
extern char* saveSchedulePath;

extern const char* backupDataSubPath;
extern const char* backupScheduleSubPath;

void LoadSavePaths(const char* appPath);

int CanLoad(char* filepath);

int WriteSaveFile(char* dataFilePath, char* scheduleFilePath, LL_Sentinel* patientList, LL_Sentinel* doctorList);

int ReadSaveFile(char* dataFilePath, char* scheduleFilePath, LL_Sentinel** patientList, LL_Sentinel** doctorList);

#endif
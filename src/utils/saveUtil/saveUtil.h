#include "../llistUtil/llist.h"
#include "../patientUtil/patientUtil.h"
#include "../doctorUtil/doctorUtil.h"

#ifndef SAVE_UTIL_H
#define SAVE_UTIL_H

extern char* saveDataPath;

void LoadSavePaths(const char* appPath);

int CanLoad(char* filepath);

int WriteSaveFile(char* filepath, LL_Sentinel* patientList, LL_Sentinel* doctorList);

int ReadSaveFile(char* filepath, LL_Sentinel** patientList, LL_Sentinel** doctorList);

#endif
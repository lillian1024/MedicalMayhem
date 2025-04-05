//
// Created by perra on 3/31/2025.
//

#include "backupUtil.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "saveUtil.h"
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#include <dirent.h>
#endif


const char * directoryBackupPath = "/automatic";
char* backupSubPath = "/automatic/backup";
int backupInterval = 30; // Default: 3 minutes
int backupEnabled = 1;    // Backup is enabled by default
pthread_mutex_t backupMutex = PTHREAD_MUTEX_INITIALIZER;

void make_directory()
{
    int appDirLen1 = strlen(appDirectory);
    int pathLength1 = strlen(directoryBackupPath);
    char* dataPath = calloc(pathLength1 + appDirLen1 + 1, sizeof(char));
    strcpy(dataPath, appDirectory);
    strcat(dataPath, directoryBackupPath);
#if defined(_WIN32)
    _mkdir(dataPath);
#else
    mkdir(dataPath, 0700);
#endif
    free(dataPath);
}


void* PeriodicBackup(void* ) {


    while (1) {
        sleep(backupInterval); // Sleep for the current backup interval

        pthread_mutex_lock(&backupMutex);
        if (backupEnabled) { // Only back up if enabled
            writeBackupToFile();
        }
        pthread_mutex_unlock(&backupMutex);
    }
    return NULL;
}

void StartBackupThread() {
    pthread_t backupThread;
    if (pthread_create(&backupThread, NULL, PeriodicBackup, (void*) NULL) != 0) {
        perror("Failed to create backup thread");
        return;
    }
    pthread_detach(backupThread); // Detach so it runs independently
}

void SetBackupInterval(int seconds) {

    pthread_mutex_lock(&backupMutex);
    backupInterval = seconds;
    pthread_mutex_unlock(&backupMutex);

    printf("Backup interval updated to %d seconds.\n", seconds);
}

void EnableBackup() {
    pthread_mutex_lock(&backupMutex);
    backupEnabled = 1;
    pthread_mutex_unlock(&backupMutex);
    printf("Automatic backup ENABLED.\n");
}

void DisableBackup() {
    pthread_mutex_lock(&backupMutex);
    backupEnabled = 0;
    pthread_mutex_unlock(&backupMutex);
    printf("Automatic backup DISABLED.\n");
}

void writeBackupToFile() {
    int pathLength = strlen(backupSubPath);

    char* path = calloc(pathLength + 1, sizeof(char));

    strcpy(path, backupSubPath);

    int appDirLen = strlen(appDirectory);

    char* dataPath = calloc(appDirLen + pathLength + strlen(backupDataSubPath) + 1, sizeof(char));
    char* schedulePath = calloc(appDirLen + pathLength + strlen(backupScheduleSubPath) + 1, sizeof(char));

    strcpy(dataPath, appDirectory);
    strcpy(schedulePath, appDirectory);

    strcat(dataPath, path);
    strcat(schedulePath, path);

    strcat(dataPath, backupDataSubPath);
    strcat(schedulePath, backupScheduleSubPath);

    LL_Sentinel* list = GetAllPatientsRecords();
    if (!WriteSaveFile(dataPath, schedulePath, list, DoctorList))
    {
        fprintf(stderr,"Unable to save backup!\n");
    }


    free(dataPath);
    free(schedulePath);
    free(path);
}
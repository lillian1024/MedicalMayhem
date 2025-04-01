//
// Created by perra on 3/31/2025.
//

#ifndef BACKUPUTIL_H
#define BACKUPUTIL_H


void SetBackupInterval(int seconds);
void EnableBackup();
void  DisableBackup();
void StartBackupThread();
void writeBackupToFile();
#endif //BACKUPUTIL_H

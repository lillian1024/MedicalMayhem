#ifndef DOCTORUTIL_H
#define DOCTORUTIL_H

#if !defined(__MINGW32__)
#include <err.h>
#else

#define errx(retval, ...) do { \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "Undefined error: %d\n", errno); \
    exit(retval); \
} while(0)

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../llistUtil/llist.h"

#define DAYS 7
#define SHIFTS 3
#define MAX_NAME_LEN 20

typedef struct doctor {
    int id;
    char* name;
    int nbShift[SHIFTS]; // Use an array instead of a pointer to avoid segmentation faults
} doctor;

extern LL_Sentinel* DoctorList;

void InitializeDoctorList();
void LoadDoctorList(LL_Sentinel* list);
void DisposeDoctorList();

int addDoctor(const char *name, int nbMorningShift, int nbAfternoonShift, int nbEveningShift);
extern const char *weekdays[DAYS];
extern const char *shiftNames[SHIFTS];
void showAllDoctor();

doctor* GetDoctorById(int id);
doctor* GetDoctorByName(char* name);

LL_Sentinel* GetDoctorList();

int doctorHasId(doctor* doctor, int* id);
int doctorhasName(doctor* doctor, char* name);

#endif // DOCTORUTIL_H

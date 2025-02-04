#ifndef DOCTORUTIL_H
#define DOCTORUTIL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

#define DAYS 7
#define SHIFTS 3
#define MAX_NAME_LEN 20

typedef struct doctor {
    int id;
    char name[MAX_NAME_LEN]; // Use a fixed-size array to avoid memory issues
    int nbShift[SHIFTS]; // Use an array instead of a pointer to avoid segmentation faults
    struct doctor *next; // For linked list usage
} doctor;

typedef struct doctorList {
    doctor *head;
} doctorList;

void addDoctor(doctorList *list, const char *name, int nbMorningShift, int nbAfternoonShift, int nbEveningShift);
extern const char *weekdays[DAYS];
extern const char *shiftNames[SHIFTS];

#endif // DOCTORUTIL_H

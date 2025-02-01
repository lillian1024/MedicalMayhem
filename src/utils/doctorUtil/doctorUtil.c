﻿//
// Created by perra on 1/31/2025.
//
#include "doctorUtil.h"

const char *weekdays[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const char *shiftNames[SHIFTS] = {"Morning", "Afternoon", "Evening"};

void validateName(const char *name) {
    if (name == NULL || name[0] == '\0') {
        errx(1, "Invalid doctor name provided");
    }
}

void validateShift(int shift) {
    if (shift < 0 || shift > 10) { // Assuming doctors cannot have more than 10 shifts per week
        errx(1, "Invalid shift count: %d", shift);
    }
}

void addDoctor(doctorList *list, const char *name, int nbMorningShift, int nbAfternoonShift, int nbEveningShift) {
    validateName(name);
    validateShift(nbMorningShift);
    validateShift(nbAfternoonShift);
    validateShift(nbEveningShift);

    doctor *newDoctor = malloc(sizeof(doctor));
    if (!newDoctor) {
        err(1, "Failed to allocate memory for new doctor");
    }

    strncpy(newDoctor->name, name, MAX_NAME_LEN - 1);
    newDoctor->name[MAX_NAME_LEN - 1] = '\0'; // Ensure null termination

    newDoctor->nbShift[0] = nbMorningShift;
    newDoctor->nbShift[1] = nbAfternoonShift;
    newDoctor->nbShift[2] = nbEveningShift;
    newDoctor->next = list->head;
    list->head = newDoctor;
}
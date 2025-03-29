//
// Created by perra on 1/31/2025.
//
#include "doctorUtil.h"

#include "../cmdUtil/cmdUtil.h"

LL_Sentinel* DoctorList;

const char *weekdays[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const char *shiftNames[SHIFTS] = {"Morning", "Afternoon", "Evening"};

/// @brief Initialize the doctor list. This function must be called before any other functions in doctorUtil.
void InitializeDoctorList()
{
    DoctorList = LL_Create();
}

/// @brief Assigned the Doctor list to an already created list.
/// @param list The list to assign DoctorList to
void LoadDoctorList(LL_Sentinel* list)
{
    DoctorList = list;
}

void disposeDoctor(doctor* doctorStruct)
{
    free(doctorStruct->name);
    free(doctorStruct);
}

/// @brief Free a specified patient data.
/// @param patient The patient data to free
/// @param data Unsuded parameter to be compilante for LL_ForEach() function.
void disposeDoctorForEach(void* doctorData, void* data) 
{
    (void)data;

    disposeDoctor((doctor*)doctorData);
};

/// @brief Dispose of the doctor list. The InitializeDoctorList function must be called before calling any docotr function after this function.
void DisposeDoctorList()
{
    LL_ForEach(DoctorList, disposeDoctorForEach, NULL);

    LL_Dispose(DoctorList);
}

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

int doctorHasId(doctor* doctor, int* id)
{
    return doctor->id == *id;
}

int doctorhasName(doctor* doctor, char* name)
{
    return strcmp(doctor->name, name) == 0;
}

void addDoctor(const char *name, int nbMorningShift, int nbAfternoonShift, int nbEveningShift) {
    validateName(name);
    validateShift(nbMorningShift);
    validateShift(nbAfternoonShift);
    validateShift(nbEveningShift);

    doctor *newDoctor = malloc(sizeof(doctor));
    if (!newDoctor) {
        err(1, "Failed to allocate memory for new doctor");
    }

    char* newName = malloc((strlen(name)+1) * sizeof(char));

    if (!newName)
    {
        err(1, "Failed to allocate memory for new doctor's name");
    }

    strncpy(newName, name, MAX_NAME_LEN - 1);

    int id;
    for (id = 0; LL_Contains(DoctorList, (int(*)(void*, void*))&doctorHasId, &id); id++) { }
    
    newDoctor->id = id;
    newDoctor->name = newName;

    newDoctor->nbShift[0] = nbMorningShift;
    newDoctor->nbShift[1] = nbAfternoonShift;
    newDoctor->nbShift[2] = nbEveningShift;

    LL_Append(DoctorList, newDoctor);
}

void showDoctor(doctor* doctor, void* data)
{
    (void)data;
    printf("%sDoctor number %d:%s \n",TTYUNDER,doctor->id,TTYNUND);
    printf("Name: %s\n", doctor->name);
    printf("Morning Shift: %d\n", doctor->nbShift[0]);
    printf("Afternoon Shift: %d\n", doctor->nbShift[1]);
    printf("Evening Shift: %d\n\n", doctor->nbShift[2]);
}

LL_Sentinel* GetDoctorList()
{
    return DoctorList;
}

void showAllDoctor()
{
    clrscr();

    LL_ForEach(DoctorList, (void(*)(void*, void*))showDoctor, NULL);

    getchar();
}

doctor* GetDoctorById(int id)
{
    int index = LL_IndexOf(DoctorList, (int(*)(void*, void*))&doctorHasId, &id);

    if (index < 0)
    {
        return NULL;
    }

    return (doctor*)LL_Get(DoctorList, index);
}

doctor* GetDoctorByName(char* name)
{
    int index = LL_IndexOf(DoctorList, (int(*)(void*, void*))&doctorhasName, name);

    if (index < 0)
    {
        return NULL;
    }

    return (doctor*)LL_Get(DoctorList, index);
}

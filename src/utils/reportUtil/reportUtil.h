#ifndef REPORT_UTIL_H
#define REPORT_UTIL_H



char* GetDoctorReport();
char* GetEquipmentReport();
char* GetHospitalReport(char* username);
void GenerateDoctorReport(char** reportBuffer, int* count);
void GenerateObservations(int count, char *observationBuffer);

void GeneratePatientsReport(char* patientBuffer);

#endif
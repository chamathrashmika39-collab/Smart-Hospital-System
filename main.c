#include <stdio.h>
#include <stdlib.h>
#define MAX_PATIENTS 100

void displayHospitalInformation();
void displayBeds(int bedOccupancy[4][20], int wardCapacity[4]);
int allocateBed(int bedOccupancy[4][20], int wardCapacity[4], int ward);

int main()
{
    int specialtyFee[4] = {1500, 2500, 4500, 5000};
    int specialtyTime[4] = {15, 20, 30, 30};
    int specialtyCapacity[4] = {30, 20, 12, 10};
    int wardRate[4] = {3000, 6000, 12000, 25000};
    int wardCapacity[4] = {20, 10, 10, 5};
    int bedOccupancy[4][20] = {0};
    int bedNumber = allocateBed(bedOccupancy, wardCapacity, 3);
    char patientName[MAX_PATIENTS][50];
    int patientAge[MAX_PATIENTS];
    int patientUrgency[MAX_PATIENTS];
    int patientSpecialty[MAX_PATIENTS];
    int patientAdmitted[MAX_PATIENTS];
    int patientWard[MAX_PATIENTS];
    int patientDays[MAX_PATIENTS];
    int patientBed[MAX_PATIENTS];
    int patientWaitingTime[MAX_PATIENTS];
    float patientBaseFee[MAX_PATIENTS];
    float patientSurcharge[MAX_PATIENTS];
    float patientWardCost[MAX_PATIENTS];
    float patientDiscount[MAX_PATIENTS];
    float patientFinalBill[MAX_PATIENTS];
    int patientCount = 0;
    printf("----------------------------------SMART HOSPITAL PATIENT & RESOURCE ALLOCATION SYSTEM----------------------------------\n");
    displayHospitalInformation();
    displayBeds(bedOccupancy, wardCapacity);
    if (bedNumber != -1)
    {
        printf("Allocated ICU Bed %d\n", bedNumber);
    }
    else
    {
        printf("No beds available in ICU\n");
    }
    return 0;
}

void displayHospitalInformation()
{
    printf("\nSPECIALTIES\n");

    for (int i = 0; i < 4; i++)
    {
        printf("%d. ", i + 1);

        if (i == 0)
            printf("General Practice\n");
        else if (i == 1)
            printf("Paediatrics\n");
        else if (i == 2)
            printf("Cardiology\n");
        else
            printf("Neurology\n");

    }

    printf("\nWARDS\n");

    for (int i = 0; i < 4; i++)
    {
        printf("%d. ", i + 1);

        if (i == 0)
            printf("General Ward\n");
        else if (i == 1)
            printf("Paediatric Ward\n");
        else if (i == 2)
            printf("Surgical Ward\n");
        else
            printf("ICU\n");
    }
}

void displayBeds(int bedOccupancy[4][20], int wardCapacity[4])
{
    char *wardNames[4] = {
        "GENERAL WARD",
        "PAEDIATRIC WARD",
        "SURGICAL WARD",
        "ICU"
    };

    for (int i = 0; i < 4; i++)
    {
        printf("\n%s\n", wardNames[i]);

        for (int j = 0; j < wardCapacity[i]; j++)
        {
            printf("Bed %d: ", j + 1);

            if (bedOccupancy[i][j] == 0)
            {
                printf("Available\n");
            }
            else
            {
                printf("Occupied\n");
            }
        }
    }
}

int allocateBed(int bedOccupancy[4][20], int wardCapacity[4], int ward)
{
    for (int i = 0; i < wardCapacity[ward]; i++)
    {
        if (bedOccupancy[ward][i] == 0)
        {
            bedOccupancy[ward][i] = 1;
            return i + 1;
        }
    }

    return -1;
}

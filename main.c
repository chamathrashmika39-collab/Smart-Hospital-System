#include <stdio.h>
#include <stdlib.h>
#define MAX_PATIENTS 100

void displayHospitalInformation();
void displayBeds(int bedOccupancy[4][20], int wardCapacity[4]);
int allocateBed(int bedOccupancy[4][20], int wardCapacity[4], int ward);
void registerPatient(char patientName[][50], int patientAge[], int patientUrgency[], int patientSpecialty[], int patientAdmitted[], int patientWard[], int patientDays[], int *patientCount, int bedOccupancy[4][20], int patientBed[], int wardCapacity[4]);
int calculateWaitingTime(int specialty, int queueCount[], int specialtyTime[]);
float calculateSurcharge(float baseFee, int urgency);
float calculateWardCost(int ward, int days, int wardRate[]);
float calculateDiscount(float grossTotal, int age);
float calculateFinalBill(float grossTotal, float discount);

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
    int queueCount[4] = {0};
    int index;
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

    registerPatient(patientName, patientAge, patientUrgency, patientSpecialty, patientAdmitted, patientWard, patientDays, &patientCount, bedOccupancy, patientBed, wardCapacity);
    patientWaitingTime[index] = calculateWaitingTime(patientSpecialty[index], queueCount, specialtyTime);
    queueCount[patientSpecialty[index]]++;
    patientBaseFee[index] =
    specialtyFee[patientSpecialty[index]];

    patientSurcharge[index] = calculateSurcharge(patientBaseFee[index],patientUrgency[index]);

    patientWardCost[index] = calculateWardCost(patientWard[index], patientDays[index], wardRate);

    float grossTotal = patientBaseFee[index] + patientSurcharge[index] + patientWardCost[index];

    patientDiscount[index] = calculateDiscount(grossTotal, patientAge[index]);

    patientFinalBill[index] = calculateFinalBill(grossTotal, patientDiscount[index]);
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

void registerPatient( char patientName[][50], int patientAge[], int patientUrgency[], int patientSpecialty[], int patientAdmitted[], int patientWard[], int patientDays[], int *patientCount, int bedOccupancy[4][20], int patientBed[], int wardCapacity[4])
{
    int index = *patientCount;

    printf("\n========================================\n");
    printf("       PATIENT REGISTRATION\n");
    printf("========================================\n");

    printf("Enter patient name: ");
    scanf(" %49[^\n]", patientName[index]);

    do
    {
        printf("Enter age: ");
        scanf("%d", &patientAge[index]);

        if (patientAge[index] < 0)
        {
            printf("Invalid age. Please try again.\n");
        }

    } while (patientAge[index] < 0);

    do
    {
        printf("\nUrgency\n");
        printf("1. Normal\n");
        printf("2. Urgent\n");
        printf("3. Critical\n");
        printf("Enter urgency: ");
        scanf("%d", &patientUrgency[index]);

        if (patientUrgency[index] < 1 || patientUrgency[index] > 3)
        {
            printf("Invalid urgency.\n");
        }

    } while (patientUrgency[index] < 1 || patientUrgency[index] > 3);

    do
    {
        printf("\nSpecialties\n");
        printf("1. General Practice\n");
        printf("2. Paediatrics\n");
        printf("3. Cardiology\n");
        printf("4. Neurology\n");
        printf("Enter specialty: ");
        scanf("%d", &patientSpecialty[index]);

        if (patientSpecialty[index] < 1 || patientSpecialty[index] > 4)
        {
            printf("Invalid specialty.\n");
        }

    } while (patientSpecialty[index] < 1 || patientSpecialty[index] > 4);

    do
    {
        printf("\nAdmitted?\n");
        printf("0. No\n");
        printf("1. Yes\n");
        printf("Enter choice: ");
        scanf("%d", &patientAdmitted[index]);

        if (patientAdmitted[index] != 0 && patientAdmitted[index] != 1)
        {
            printf("Enter 0 or 1.\n");
        }

    } while (patientAdmitted[index] != 0 &&
             patientAdmitted[index] != 1);

    patientWard[index] = -1;
    patientDays[index] = 0;
    patientBed[index] = -1;

    if (patientAdmitted[index] == 1)
    {
        do
        {
            printf("\nWards\n");
            printf("1. General Ward\n");
            printf("2. Paediatric Ward\n");
            printf("3. Surgical Ward\n");
            printf("4. ICU\n");
            printf("Enter ward: ");
            scanf("%d", &patientWard[index]);

            if (patientWard[index] < 1 ||
                patientWard[index] > 4)
            {
                printf("Invalid ward.\n");
            }

        } while (patientWard[index] < 1 ||
                 patientWard[index] > 4);

        patientWard[index]--;

        do
        {
            printf("Enter number of days: ");
            scanf("%d", &patientDays[index]);

            if (patientDays[index] <= 0)
            {
                printf("Days must be greater than 0.\n");
            }

        } while (patientDays[index] <= 0);

        patientBed[index] = allocateBed(bedOccupancy, wardCapacity, patientWard[index]);

        if (patientBed[index] == -1)
        {
            printf("No beds available in selected ward.\n");
            patientAdmitted[index] = 0;
            patientWard[index] = -1;
            patientDays[index] = 0;
        }
        else
        {
            printf("Patient allocated Bed %d.\n",
                   patientBed[index]);
        }
    }

    (*patientCount)++;

    printf("\nPatient registered successfully.\n");
}

int calculateWaitingTime(int specialty, int queueCount[], int specialtyTime[])
{
    return queueCount[specialty] * specialtyTime[specialty];
}

float calculateSurcharge(float baseFee, int urgency)
{
    if (urgency == 3)
    {
        return baseFee * 0.50;
    }
    else if (urgency == 2)
    {
        return baseFee * 0.20;
    }
    else
    {
        return 0;
    }
}

float calculateWardCost(int ward, int days, int wardRate[])
{
    if (ward == -1) return 0;
    return wardRate[ward] * days;
}

float calculateDiscount(float grossTotal, int age)
{
    if (age < 5 || age > 65)
    {
        return grossTotal * 0.15;
    }

    return 0;
}

float calculateFinalBill(float grossTotal, float discount)
{
    return grossTotal - discount;
}

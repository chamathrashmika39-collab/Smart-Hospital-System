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
void displayPatientBill(int index, char patientName[][50], int patientAge[], int patientUrgency[], int patientSpecialty[], int patientWard[], int patientWaitingTime[], float patientBaseFee[], float patientSurcharge[], float patientWardCost[], float patientDiscount[], float patientFinalBill[]);
void displayMenu();
void sortPatientsByPriority(int patientOrder[], int patientCount,int patientUrgency[]);
void displayReports(int patientCount,int patientUrgency[],float patientFinalBill[],float patientDiscount[],int bedOccupancy[4][20], int wardCapacity[4]);
void saveBeds(int bedOccupancy[4][20], int wardCapacity[4]);
void loadBeds(int bedOccupancy[4][20], int wardCapacity[4]);
void savePatientRecord(int index,char patientName[][50],int patientAge[],int patientUrgency[],int patientSpecialty[]);

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
    int patientOrder[MAX_PATIENTS];
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

    int choice;

    do
    {
    displayMenu();
    scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            /* Registration */
            break;

            case 2:
            /* Display Patients */
            break;

            case 3:
            displayBeds(bedOccupancy, wardCapacity);
            break;

            case 4:
            /* Priority Sorting */
            break;

            case 5:
            /* reports */
            break;

            case 6:
            printf("Exiting system...\n");
            break;

            default:
            printf("Invalid choice.\n");
        }

    }while (choice != 6);

    patientOrder[patientCount - 1] = patientCount - 1;
    sortPatientsByPriority(patientOrder,patientCount,patientUrgency);
    savePatientRecord(patientCount - 1,patientName,patientAge,patientUrgency,patientSpecialty);
    saveBeds(bedOccupancy, wardCapacity);

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
    char *wardNames[4] = {"GENERAL WARD", "PAEDIATRIC WARD", "SURGICAL WARD", "ICU"};

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

void displayPatientBill(int index, char patientName[][50], int patientAge[], int patientUrgency[], int patientSpecialty[], int patientWard[], int patientWaitingTime[], float patientBaseFee[], float patientSurcharge[], float patientWardCost[], float patientDiscount[], float patientFinalBill[])
{
    char *specialtyNames[4] = {"General Practice", "Paediatrics", "Cardiology", "Neurology"};

    char *wardNames[4] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};

    char *urgencyNames[3] = {"Normal", "Urgent", "Critical"};

    printf("\n==================================\n");
    printf("          PATIENT BILL\n");
    printf("==================================\n");

    printf("Patient ID: PAT-%04d\n", 1001 + index);
    printf("Name: %s\n", patientName[index]);
    printf("Age: %d\n", patientAge[index]);

    printf("Specialty: %s\n",
           specialtyNames[patientSpecialty[index]]);

    printf("Urgency: %s\n",
           urgencyNames[patientUrgency[index] - 1]);

    if (patientWard[index] != -1)
    {
        printf("Ward: %s\n",
               wardNames[patientWard[index]]);
    }
    else
    {
        printf("Ward: Outpatient\n");
    }

    printf("\nBase Fee:       %.2f\n",
           patientBaseFee[index]);

    printf("Surcharge:      %.2f\n",
           patientSurcharge[index]);

    printf("Ward Cost:      %.2f\n",
           patientWardCost[index]);

    printf("Gross Total:    %.2f\n",
           patientBaseFee[index] +
           patientSurcharge[index] +
           patientWardCost[index]);

    printf("Discount:       %.2f\n",
           patientDiscount[index]);

    printf("Final Payable:  %.2f\n",
           patientFinalBill[index]);

    printf("Waiting Time:   %d min\n",
           patientWaitingTime[index]);

    printf("=================================\n");
}

void displayMenu()
{
    printf("\n===================================\n");
    printf("       SMART HOSPITAL SYSTEM\n");
    printf("===================================\n");
    printf("1. Register Patient\n");
    printf("2. Display Patients\n");
    printf("3. Display Bed Status\n");
    printf("4. Display Patients by Priority\n");
    printf("5. Hospital Reports\n");
    printf("6. Exit\n");
    printf("===================================\n");
    printf("Enter your choice: ");
}

void sortPatientsByPriority(int patientOrder[], int patientCount,int patientUrgency[])
{
    for (int i = 0; i < patientCount - 1; i++)
    {
        for (int j = 0; j < patientCount - i - 1; j++)
        {
            if (patientUrgency[patientOrder[j]]
                < patientUrgency[patientOrder[j + 1]])
            {
                int temp = patientOrder[j];

                patientOrder[j] =
                    patientOrder[j + 1];

                patientOrder[j + 1] = temp;
            }
        }
    }
}

void displayReports(int patientCount,int patientUrgency[],float patientFinalBill[],float patientDiscount[],int bedOccupancy[4][20], int wardCapacity[4])
{
    int critical = 0;
    int urgent = 0;
    int normal = 0;

    float totalRevenue = 0;
    float totalDiscounts = 0;

    int highestPatient = -1;
    float highestBill = 0;

    for (int i = 0; i < patientCount; i++)
    {
        if (patientUrgency[i] == 3)
        {
            critical++;
        }
        else if (patientUrgency[i] == 2)
        {
            urgent++;
        }
        else
        {
            normal++;
        }

        totalRevenue += patientFinalBill[i];
        totalDiscounts += patientDiscount[i];

        if (patientFinalBill[i] > highestBill)
        {
            highestBill = patientFinalBill[i];
            highestPatient = i;
        }
    }

    printf("\n===================================\n");
    printf("       HOSPITAL REPORTS\n");
    printf("===================================\n");

    printf("Total Critical: %d\n", critical);
    printf("Total Urgent:   %d\n", urgent);
    printf("Total Normal:   %d\n", normal);

    printf("\nTotal Revenue:   %.2f\n", totalRevenue);
    printf("Total Discounts: %.2f\n", totalDiscounts);

    printf("\nWARD OCCUPANCY\n");

    printf("General Ward:    ");
    for (int i = 0; i < wardCapacity[0]; i++)
    {
        if (bedOccupancy[0][i] == 1)
        {
            printf("1");
        }
    }
    printf("\n");

    printf("Paediatric Ward: ");
    for (int i = 0; i < wardCapacity[1]; i++)
    {
        if (bedOccupancy[1][i] == 1)
        {
            printf("1");
        }
    }
    printf("\n");

    printf("Surgical Ward:   ");
    for (int i = 0; i < wardCapacity[2]; i++)
    {
        if (bedOccupancy[2][i] == 1)
        {
            printf("1");
        }
    }
    printf("\n");

    printf("ICU:             ");
    for (int i = 0; i < wardCapacity[3]; i++)
    {
        if (bedOccupancy[3][i] == 1)
        {
            printf("1");
        }
    }
    printf("\n");

    if (highestPatient != -1)
    {
        printf("\nHighest Paying Patient: PAT-%04d\n",
               1001 + highestPatient);

        printf("Highest Bill: %.2f\n",
               highestBill);
    }
    else
    {
        printf("\nNo patients registered.\n");
    }

    printf("===================================\n");
}

void saveBeds(int bedOccupancy[4][20],int wardCapacity[4])
{
    FILE *file = fopen("beds_status.txt", "w");

    if (file == NULL)
    {
        printf("Unable to open beds_status.txt\n");
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < wardCapacity[i]; j++)
        {
            fprintf(file, "%d ", bedOccupancy[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}

void loadBeds(int bedOccupancy[4][20], int wardCapacity[4])
{
    FILE *file = fopen("beds_status.txt", "r");

    if (file == NULL)
    {
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < wardCapacity[i]; j++)
        {
            fscanf(file, "%d", &bedOccupancy[i][j]);
        }
    }

    fclose(file);
}

void savePatientRecord(int index,char patientName[][50],int patientAge[],int patientUrgency[],int patientSpecialty[])
{
    FILE *file = fopen("patient_records.txt", "a");

    if (file == NULL)
    {
        printf("Unable to open patient_records.txt\n");
        return;
    }

    fprintf(
        file,
        "PAT-%04d | %s | Age: %d | Urgency: %d | Specialty: %d\n",
        1001 + index,
        patientName[index],
        patientAge[index],
        patientUrgency[index],
        patientSpecialty[index]
    );

    fclose(file);
}


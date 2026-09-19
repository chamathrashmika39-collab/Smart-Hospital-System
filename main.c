#include <stdio.h>
#include <stdlib.h>

void displayHospitalInformation();
void displayBeds(int bedOccupancy[4][20]);

int main()
{
    int specialtyFee[4] = {1500, 2500, 4500, 5000};
    int specialtyTime[4] = {15, 20, 30, 30};
    int specialtyCapacity[4] = {30, 20, 12, 10};
    int wardRate[4] = {3000, 6000, 12000, 25000};
    int wardCapacity[4] = {20, 10, 10, 5};
    int bedOccupancy[4][20] = {0};
    printf("----------------------------------SMART HOSPITAL PATIENT & RESOURCE ALLOCATION SYSTEM----------------------------------\n");
    displayHospitalInformation();
    displayBeds(bedOccupancy);
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

void displayBeds(int bedOccupancy[4][20])
{
    char *wardNames[4] = {
        "GENERAL WARD",
        "PAEDIATRIC WARD",
        "SURGICAL WARD",
        "ICU"
    };

    int wardCapacity[4] = {20, 10, 10, 5};

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

#include <stdio.h>
#include <stdlib.h>
//ISTANBUL MEDENIYET UNIVERSITY 01.12.2019(DD-MM-YYYY) - Decision Tree Algorithm By NECATI SENEL
typedef struct {
    int LeftYellow;
    int LeftRed;
    int LeftGreen;
    int RightYellow;
    int RightRed;
    int RightGreen;
    float Coordinates;
    int Axis;
}fNode;
typedef struct {
    int LeftYellow;
    int LeftRed;
    int LeftGreen;
    int RightYellow;
    int RightRed;
    int RightGreen;
    float Coordinates;
    int Axis;
}sNode;
typedef struct {
    float Coordinates;
    int Axis;
    int LineCount;
}root;
float X = 0;
float Y = 0;
int Lines = 0;
int getCounts () {
    fNode fNodeC;
    sNode sNodeC;
    root rootC;
    fNodeC.LeftRed = fNodeC.LeftYellow = fNodeC.LeftGreen = 0;
    char answer;
    char goVoid[100];
    FILE *ptr;
    ptr = fopen("calculated_data.txt", "r");
    if (ptr == NULL) {
        printf("The algorithm seems never trained before.\n");
        printf("Would you like to train algorithm?(Y/N): ");
        scanf(" %c", &answer);
        switch (answer) {
        case 'Y':
        case 'y':
            getData();
            getCounts();
            break;
        case 'N':
        case 'n':
            exit(-1);
        }
    }
    fclose(ptr);
    FILE *FTB;
    FTB = fopen("counts.txt", "r");
    if (FTB == NULL) {
        printf("Unexpected error: Please check counts.txt\n");
        exit(-1);
    }
    fscanf(FTB, "%s %d %d %d", goVoid, &fNodeC.LeftYellow, &fNodeC.LeftRed, &fNodeC.LeftGreen);
    fseek(FTB, 0, '\n');
    fscanf(FTB, "%s %d %d %d", goVoid, &fNodeC.RightYellow, &fNodeC.RightRed, &fNodeC.RightGreen);
    fseek(FTB, 0, '\n');
    fscanf(FTB, "%s %d %d %d", goVoid, &sNodeC.LeftYellow, &sNodeC.LeftRed, &sNodeC.LeftGreen);
    fseek(FTB, 0, '\n');
    fscanf(FTB, "%s %d %d %d", goVoid, &sNodeC.RightYellow, &sNodeC.RightRed, &sNodeC.RightGreen);
    fseek(FTB, 0, '\n');
    fscanf(FTB, "%s %f", goVoid, &rootC.Coordinates);
    fseek(FTB, 0, '\n');
    fscanf(FTB, "%s %d", goVoid, &rootC.Axis);
    fseek(FTB, 0, '\n');
    fscanf(FTB, "%s %f", goVoid, &fNodeC.Coordinates);
    fseek(FTB, 0, '\n');
    fscanf(FTB, "%s %d", goVoid, &fNodeC.Axis);
    fseek(FTB, 0, '\n');
    fscanf(FTB, "%s %f", goVoid, &sNodeC.Coordinates);
    fseek(FTB, 0, '\n');
    fscanf(FTB, "%s %d", goVoid, &sNodeC.Axis);
    fseek(FTB, 0, '\n');
    fscanf(FTB, "%s %d", goVoid, &rootC.LineCount);
    fclose(FTB);
    Lines = rootC.LineCount;
    FILE *ptrc;
    int linec = 0;
    int ch;
    ptrc = fopen("data.txt", "r");
    while ((ch=fgetc(ptrc)) != EOF) {
        if (ch=='\n')
            ++linec;
    }
    fclose(ptrc);
    if (Lines != linec) {
        printf("Looks like data.txt edited. Algorithm will retrain.\n");
        getData();
    }
    ProbabilityCalc(&fNodeC, &sNodeC, &rootC);
}
int ProbabilityCalc (fNode *fNodeC, sNode *sNodeC, root *rootC) {
    if (rootC->Axis == 1) {
        if (X<rootC->Coordinates) {
            if (fNodeC->Axis == 1) {
                if (X<fNodeC->Coordinates) {
                    if (fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                        printf("Probability of being Yellow: %f\n", ((float)fNodeC->LeftYellow/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                        printf("Probability of being Red: %f\n", ((float)fNodeC->LeftRed/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                        printf("Probability of being Green: %f\n", ((float)fNodeC->LeftGreen/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                    }
                }
                else {
                    if (fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)fNodeC->RightYellow/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)fNodeC->RightRed/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)fNodeC->RightGreen/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    }
                }
            }
            else {
                if (Y<fNodeC->Coordinates) {
                    if (fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)fNodeC->LeftYellow/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)fNodeC->LeftRed/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)fNodeC->LeftGreen/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                    }
                }
                else {
                    if (fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)fNodeC->RightYellow/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)fNodeC->RightRed/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)fNodeC->RightGreen/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    }
                }
            }
        }
        else {
            if (sNodeC->Axis == 1) {
                if (X<sNodeC->Coordinates) {
                    if (sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)sNodeC->LeftYellow/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)sNodeC->LeftRed/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)sNodeC->LeftGreen/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    }
                }
                else {
                    if (sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)sNodeC->RightYellow/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)sNodeC->RightRed/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)sNodeC->RightGreen/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    }
                }
            }
            else {
                if (Y<sNodeC->Coordinates) {
                    if (sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)sNodeC->LeftYellow/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)sNodeC->LeftRed/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)sNodeC->LeftGreen/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    }
                }
                else {
                    if (sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)sNodeC->RightYellow/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)sNodeC->RightRed/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)sNodeC->RightGreen/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    }
                }
            }
        }
    }
    else {
        if (Y<rootC->Coordinates) {
            if (fNodeC->Axis == 1) {
                if (X<fNodeC->Coordinates) {
                    if (fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)fNodeC->LeftYellow/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)fNodeC->LeftRed/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)fNodeC->LeftGreen/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                    }
                }
                else {
                    if (fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)fNodeC->RightYellow/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)fNodeC->RightRed/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)fNodeC->RightGreen/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    }
                }
            }
            else {
                if (Y<fNodeC->Coordinates) {
                    if (fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)fNodeC->LeftYellow/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)fNodeC->LeftRed/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)fNodeC->LeftGreen/(fNodeC->LeftYellow+fNodeC->LeftRed+fNodeC->LeftGreen))*100);
                    }
                }
                else {
                    if (fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)fNodeC->RightYellow/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)fNodeC->RightRed/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)fNodeC->RightGreen/(fNodeC->RightYellow+fNodeC->RightRed+fNodeC->RightGreen))*100);
                    }
                }
            }
        }
        else {
            if (sNodeC->Axis == 1) {
                if (X<sNodeC->Coordinates) {
                    if (sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)sNodeC->LeftYellow/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)sNodeC->LeftRed/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)sNodeC->LeftGreen/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    }
                }
                else {
                    if (sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)sNodeC->RightYellow/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)sNodeC->RightRed/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)sNodeC->RightGreen/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    }
                }
            }
            else {
                if (Y<sNodeC->Coordinates) {
                    if (sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)sNodeC->LeftYellow/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)sNodeC->LeftRed/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)sNodeC->LeftGreen/(sNodeC->LeftYellow+sNodeC->LeftRed+sNodeC->LeftGreen))*100);
                    }
                }
                else {
                    if (sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen == 0) {
                        printf("Inefficient data. Please add more data for better calculation.\n");
                    }
                    else {
                    printf("Probability of being Yellow: %f\n", ((float)sNodeC->RightYellow/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    printf("Probability of being Red: %f\n", ((float)sNodeC->RightRed/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    printf("Probability of being Green: %f\n", ((float)sNodeC->RightGreen/(sNodeC->RightYellow+sNodeC->RightRed+sNodeC->RightGreen))*100);
                    }
                }
            }
        }
    }
}
int main ()
{
    printf("\033[1;31m");
    printf("Enter the Coordinates(X-Y)\n");
    printf("X-Axis: ");
    scanf("%f", &X);
    printf("Y-Axis: ");
    scanf("%f", &Y);
    getCounts();
    printf("\033[0m");
    return 0;
}

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
float rootI = 0;
float rootCoords = 0;
int rootAXIS = 0;
float tempC;
float nodeLI = 0;
float nodeLCoords = 0;
int nodeLAxis = 0;
float nodeRI = 0;
float nodeRCoords = 0;
int nodeRAxis = 0;
int FNLR = 0;
int FNLY = 0;
int FNLG = 0;
int FNRR = 0;
int FNRY = 0;
int FNRG = 0;
int SNLR = 0;
int SNLY = 0;
int SNLG = 0;
int SNRR = 0;
int SNRY = 0;
int SNRG = 0;
int linecount = 0;
int getData () {
    FILE *ptr;
    int lines = 0;
    int ch;
    ptr = fopen("data.txt", "r");
    while ((ch=fgetc(ptr)) != EOF) {
        if (ch=='\n')
            ++lines;
    }
    linecount = lines;
    fclose(ptr);
    float mainAppleCordsX[lines];
    float mainAppleCordsY[lines];
    int mainAppleCordsC[lines];
    float x1;
    float x2;
    int x3;
    ptr = fopen("data.txt", "r");
    for (int i=0;i<lines;i++) {
        fscanf(ptr, "%f %f %d", &mainAppleCordsX[i], &mainAppleCordsY[i], &mainAppleCordsC[i]);
        printf("%f %f %d\n", mainAppleCordsX[i], mainAppleCordsY[i], mainAppleCordsC[i]);
        fseek(ptr, 0, '\n');
    }
    fclose(ptr);
    ROOT(mainAppleCordsX, mainAppleCordsY, mainAppleCordsC, lines);
}
int ROOT (float *x, float *y, int *c, int lines) {
    float randomNum;
    float leftAppleCordsX[lines];
    float leftAppleCordsY[lines];
    int leftAppleCordsC[lines];
    float rightAppleCordsX[lines];
    float rightAppleCordsY[lines];
    int rightAppleCordsC[lines];
    int LCV = 0;
    int RCV = 0;
    float tempI = 0;
    int LR = 0;
    int LY = 0;
    int LG = 0;
    int RR = 0;
    int RY = 0;
    int RG = 0;
    int AI = 100;
    int s = 0;
    srand((unsigned int)time(NULL));
    for (int i=0;i<AI;i++) {
        randomNum = (((float)rand())/RAND_MAX * (float)7);
        s = 1 + rand() % 2;
        switch (s) {
        case 1://X-Axis
            printf("R: Is value of X lower than %f\n", randomNum);
            for (int j=0;j<lines;j++) {
                if (x[j]<=randomNum) {
                    if (c[j] == 1) {
                        LY++;
                    }
                    else if (c[j] == 2) {
                        LR++;
                    }
                    else if (c[j] == 3) {
                        LG++;
                    }
                }
                else {
                        if (c[j] == 1) {
                            RY++;
                        }
                        else if (c[j] == 2) {
                            RR++;
                        }
                        else if (c[j] == 3) {
                            RG++;
                        }
                }
            }
            break;
        case 2://Y-Axis
            printf("R: Is value of Y lower than %f\n", randomNum);
            for (int j=0;j<=lines;j++) {
                if (y[j]<=randomNum) {
                    if (c[j] == 1) {
                        LY++;
                    }
                    else if (c[j] == 2) {
                        LR++;
                    }
                    else if (c[j] == 3) {
                        LG++;
                    }
                }
                else {
                        if (c[j] == 1) {
                            RY++;
                        }
                        else if (c[j] == 2) {
                            RR++;
                        }
                        else if (c[j] == 3) {
                            RG++;
                        }
                }
            }
            break;
        }
     printf("Left Side = Yellow: %d Red: %d Green: %d\n", LY, LR, LG);
     printf("Right Side = Yellow: %d Red: %d Green: %d\n", RY, RR, RG);
     calculationROOT(LY, LR, LG, RY, RR, RG, lines);
     printf("tempC: %f\n", tempC);
     if (tempC > tempI) {
         tempI = tempC;
         rootI = tempI;
         rootAXIS = s;
         rootCoords = randomNum;
     }
     LR = LY = LG = RR = RY = RG = 0;
    }
    if (rootAXIS == 1) {
       for (int k=0;k<lines;k++) {
           if (x[k]<=rootCoords) {
               leftAppleCordsX[LCV] = x[k];
               leftAppleCordsY[LCV] = y[k];
               leftAppleCordsC[LCV] = c[k];
               LCV++;
           }
           else {
               rightAppleCordsX[RCV] = x[k];
               rightAppleCordsY[RCV] = y[k];
               rightAppleCordsC[RCV] = c[k];
               RCV++;
           }
       }
    }
    else {
        for (int k=0;k<lines;k++) {
            if (y[k]<=rootCoords) {
                leftAppleCordsX[LCV] = x[k];
                leftAppleCordsY[LCV] = y[k];
                leftAppleCordsC[LCV] = c[k];
                LCV++;
            }
            else {
                rightAppleCordsX[RCV] = x[k];
                rightAppleCordsY[RCV] = y[k];
                rightAppleCordsC[RCV] = c[k];
                RCV++;
            }
        }
        tempC = 0;
    }
    NODE(leftAppleCordsX, leftAppleCordsY, leftAppleCordsC, rightAppleCordsX, rightAppleCordsY, rightAppleCordsC,LCV,RCV);
    finalProbability(leftAppleCordsX, leftAppleCordsY, leftAppleCordsC, rightAppleCordsX, rightAppleCordsY, rightAppleCordsC, LCV, RCV);
}
int calculationROOT (int ly, int lr, int lg, int ry, int rr, int rg, int lines) {
    float HS;
    float HSL;
    float HSR;
    float I;
    float yellow = (float)(ly+ry)/lines;
    float red = (float)(lr+rr)/lines;
    float green = (float)(lg+rg)/lines;
    float a1 = (float)ly/lines;
    float b1 = (float)lr/lines;
    float c1 = (float)lg/lines;
    float a2 = (float)ry/lines;
    float b2 = (float)rr/lines;
    float c2 = (float)rg/lines;
    if ((ly+ry) == 0) {
        yellow = 1;
    }
    if ((lr+rr) == 0) {
        red = 1;
    }
    if ((lg+rg) == 0) {
        green = 1;
    }
    HS = -1*((red*log2f(red)) + (yellow*log2f(yellow)) + (green*log2f(green)));
    if (ly == 0) {
    a1 = 1;
    }
    if (lr == 0) {
    b1 = 1;
    }
    if (lg == 0) {
    c1 = 1;
    }
    if (ry == 0) {
    a2 = 1;
    }
    if (rr == 0) {
    b2 = 1;
    }
    if (rg == 0) {
    c2 = 1;
    }
    HSL = a1*log2f(a1) + b1*log2f(b1) + c1*log2f(c1);
    HSR = a2*log2f(a2) + b2*log2f(b2) + c2*log2f(c2);
    I = (HS + ((float)(ly+lr+lg)/lines)*HSL + ((float)(ry+rr+rg)/lines)*HSR);
    printf("HS'nın değeri %f\n", HS);
    printf("HSL'nın değeri %f\n", HSL);
    printf("HSR'nın değeri %f\n", HSR);
    printf("I'nın değeri %f\n", I);
    tempC = I;
}
int calculationNODE (int ly, int lr, int lg, int ry, int rr, int rg, int lines) {
    float HS;
    float HSL;
    float HSR;
    float I;
    float yellow = (float)(ly+ry)/lines;
    float red = (float)(lr+rr)/lines;
    float green = (float)(lg+rg)/lines;
    float a1 = (float)ly/lines;
    float b1 = (float)lr/lines;
    float c1 = (float)lg/lines;
    float a2 = (float)ry/lines;
    float b2 = (float)rr/lines;
    float c2 = (float)rg/lines;
    if ((ly+ry) == 0) {
        yellow = 1;
    }
    if ((lr+rr) == 0) {
        red = 1;
    }
    if ((lg+rg) == 0) {
        green = 1;
    }
    HS = -1*((red*log2f(red)) + (yellow*log2f(yellow)) + (green*log2f(green)));
    if (ly == 0) {
    a1 = 1;
    }
    if (lr == 0) {
    b1 = 1;
    }
    if (lg == 0) {
    c1 = 1;
    }
    if (ry == 0) {
    a2 = 1;
    }
    if (rr == 0) {
    b2 = 1;
    }
    if (rg == 0) {
    c2 = 1;
    }
    HSL = a1*log2f(a1) + b1*log2f(b1) + c1*log2f(c1);
    HSR = a2*log2f(a2) + b2*log2f(b2) + c2*log2f(c2);
    I = (HS + ((float)(ly+lr+lg)/lines)*HSL + ((float)(ry+rr+rg)/lines)*HSR);
    printf("HS'nın değeri %f\n", HS);
    printf("HSL'nın değeri %f\n", HSL);
    printf("HSR'nın değeri %f\n", HSR);
    printf("I'nın değeri %f\n", I);
    tempC = I;
}
int NODE (float *lx, float *ly, int *lc, float *rx, float *ry, int *rc, int lsc, int rsc) {
    tempC = 0;
    float randomNum;
    int s;
    int AI = 10000;
    int LLY, LLR, LLG, LRY, LRR, LRG;
    int RLY, RLR, RLG, RRY, RRR, RRG;
    float tempI = 0;
    LLY = LLR = LLG = LRY = LRR = LRG = 0;
    RLY = RLR = RLG = RRY = RRR = RRG = 0;
    srand((unsigned int)time(NULL));
    for (int i=0;i<AI;i++) {
        randomNum = (((float)rand())/RAND_MAX * (float)7);
        s = 1 + rand() % 2;
        switch (s) {
        case 1://X-Axis
            printf("NL: Is value of X lower than %f\n", randomNum);
            for (int j=0;j<lsc;j++) {
                if (lx[j]<=randomNum) {
                    if (lc[j] == 1) {
                        LLY++;
                    }
                    else if (lc[j] == 2) {
                        LLR++;
                    }
                    else if (lc[j] == 3) {
                        LLG++;
                    }
                }
                else {
                        if (lc[j] == 1) {
                            LRY++;
                        }
                        else if (lc[j] == 2) {
                            LRR++;
                        }
                        else if (lc[j] == 3) {
                            LRG++;
                        }
                }
            }
            break;
        case 2:
            printf("NL: Is value of Y lower than %f\n", randomNum);
            for (int j=0;j<lsc;j++) {
                if (ly[j]<=randomNum) {
                    if (lc[j] == 1) {
                        LLY++;
                    }
                    else if (lc[j] == 2) {
                        LLR++;
                    }
                    else if (lc[j] == 3) {
                        LLG++;
                    }
                }
                else {
                        if (lc[j] == 1) {
                            LRY++;
                        }
                        else if (lc[j] == 2) {
                            LRR++;
                        }
                        else if (lc[j] == 3) {
                            LRG++;
                        }
                }
            }
            break;
        }
        printf("Left Side = Yellow: %d Red: %d Green: %d\n", LLY, LLR, LLG);
        printf("Right Side = Yellow: %d Red: %d Green: %d\n", LRY, LRR, LRG);
        calculationNODE(LLY, LLR, LLG, LRY, LRR, LRG, (lsc));
        printf("tempC: %f\n", tempC);
        if (tempC > tempI) {
            tempI = tempC;
            nodeLI = tempI;
            nodeLAxis = s;
            nodeLCoords = randomNum;
        }
            LLY = LLR = LLG = LRY = LRR = LRG = 0;
    }
    tempC = 0;
    for (int i=0;i<AI;i++) {
        randomNum = (((float)rand())/RAND_MAX * (float)7);
        s = 1 + rand() % 2;
        switch (s) {
        case 1://X-Axis
            printf("NR: Is value of X lower than %f\n", randomNum);
            for (int j=0;j<rsc;j++) {
                if (rx[j]<=randomNum) {
                    if (rc[j] == 1) {
                        RLY++;
                    }
                    else if (rc[j] == 2) {
                        RLR++;
                    }
                    else if (rc[j] == 3) {
                        RLG++;
                    }
                }
                else {
                        if (rc[j] == 1) {
                            RRY++;
                        }
                        else if (rc[j] == 2) {
                            RRR++;
                        }
                        else if (rc[j] == 3) {
                            RRG++;
                        }
                }
            }
            break;
        case 2:
            printf("NR: Is value of Y lower than %f\n", randomNum);
            for (int j=0;j<rsc;j++) {
                if (ry[j]<=randomNum) {
                    if (rc[j] == 1) {
                        RLY++;
                    }
                    else if (rc[j] == 2) {
                        RLR++;
                    }
                    else if (rc[j] == 3) {
                        RLG++;
                    }
                }
                else {
                        if (rc[j] == 1) {
                            RRY++;
                        }
                        else if (rc[j] == 2) {
                            RRR++;
                        }
                        else if (rc[j] == 3) {
                            RRG++;
                        }
                }
            }
            break;
        }
        printf("Left Side = Yellow: %d Red: %d Green: %d\n", RLY, RLR, RLG);
        printf("Right Side = Yellow: %d Red: %d Green: %d\n", RRY, RRR, RRG);
        calculationNODE(RLY, RLR, RLG, RRY, RRR, RRG, (rsc));
        printf("tempC: %f\n", tempC);
        if (tempC > tempI) {
            tempI = tempC;
            nodeRI = tempI;
            nodeRAxis = s;
            nodeRCoords = randomNum;
        }
        RLY = RLR = RLG = RRY = RRR = RRG = 0;
        }
    if (nodeRAxis == 0) {
        getData();
    }
    finalResults();
}
int finalProbability (float *lx, float *ly, int *lc, float *rx, float *ry, int *rc, int lsc, int rsc) {
    FNLR = FNLY = FNLG = FNRR = FNRY = FNRG = SNLR = SNLY = SNLG = SNRR = SNRY = SNRG = 0;
    if (nodeLAxis == 1) {
        for (int i=0;i<lsc;i++) {
            if (lx[i]<=nodeLCoords) {
                if (lc[i] == 1) {
                    FNLY++;
                }
                else if (lc[i] == 2) {
                    FNLR++;
                }
                else if (lc[i] == 3) {
                    FNLG++;
                }
            }
            else {
                if (lc[i] == 1) {
                    FNRY++;
                }
                else if (lc[i] == 2) {
                    FNRR++;
                }
                else if (lc[i] == 3) {
                    FNRG++;
                }
            }
        }
    }
    else if (nodeLAxis == 2) {
        for (int i=0;i<lsc;i++) {
            if (ly[i]<=nodeLCoords) {
                if (lc[i] == 1) {
                    FNLY++;
                }
                else if (lc[i] == 2) {
                    FNLR++;
                }
                else if (lc[i] == 3) {
                    FNLG++;
                }
            }
            else {
                if (lc[i] == 1) {
                    FNRY++;
                }
                else if (lc[i] == 2) {
                    FNRR++;
                }
                else if (lc[i] == 3) {
                    FNRG++;
                }
            }
        }
    }
    if (nodeRAxis == 1) {
        for (int i=0;i<rsc;i++) {
            if (rx[i]<=nodeRCoords) {
                if (rc[i] == 1) {
                    SNLY++;
                }
                else if (rc[i] == 2) {
                    SNLR++;
                }
                else if (rc[i] == 3) {
                    SNLG++;
                }
            }
            else {
                if (rc[i] == 1) {
                    SNRY++;
                }
                else if (rc[i] == 2) {
                    SNRR++;
                }
                else if (rc[i] == 3) {
                    SNRG++;
                }
            }
        }
    }
    else if (nodeRAxis == 2) {
        for (int i=0;i<lsc;i++) {
            if (ry[i]<=nodeRCoords) {
                if (rc[i] == 1) {
                    SNLY++;
                }
                else if (rc[i] == 2) {
                    SNLR++;
                }
                else if (rc[i] == 3) {
                    SNLG++;
                }
            }
            else {
                if (rc[i] == 1) {
                    SNRY++;
                }
                else if (rc[i] == 2) {
                    SNRR++;
                }
                else if (rc[i] == 3) {
                    SNRG++;
                }
            }
        }
    }
}
int finalResults () {
    FILE *ptr;
    ptr = fopen("calculated_data.txt", "w");
    fprintf(ptr ,"--------------------------------------------------------\n");
    fprintf(ptr, "Perfect Root I : %f\n", rootI);
    fprintf(ptr, "Perfect Root Axis: %d\n", rootAXIS);
    fprintf(ptr, "Perfect Root Coordinates: %f\n", rootCoords);
    fprintf(ptr ,"--------------------------------------------------------\n");
    fprintf(ptr, "Perfect L-Node I: %f\n", nodeLI);
    fprintf(ptr, "Perfect L-Node Axis: %d\n", nodeLAxis);
    fprintf(ptr, "Perfect L-Node Coordinates: %f\n", nodeLCoords);
    fprintf(ptr, "L-Counts: %d %d %d\n", FNLY, FNLR, FNLG);
    fprintf(ptr, "R-Counts: %d %d %d\n", FNRY, FNRR, FNRG);
    fprintf(ptr, "--------------------------------------------------------\n");
    fprintf(ptr, "Perfect R-Node I: %f\n", nodeRI);
    fprintf(ptr, "Perfect R-Node Axis: %d\n", nodeRAxis);
    fprintf(ptr, "Perfect R-Node Coordinates: %f\n", nodeRCoords);
    fprintf(ptr, "L-Counts: %d %d %d\n", SNLY, SNLR, SNLG);
    fprintf(ptr, "R-Counts: %d %d %d\n", SNRY, SNRR, SNRG);
    fprintf(ptr, "--------------------------------------------------------\n");
    fclose(ptr);
    ptr = fopen("counts.txt", "w");
    fprintf(ptr, "FNL-Counts: %d %d %d\n", FNLY, FNLR, FNLG);
    fprintf(ptr, "FNR-Counts: %d %d %d\n", FNRY, FNRR, FNRG);
    fprintf(ptr, "SNL-Counts: %d %d %d\n", SNLY, SNLR, SNLG);
    fprintf(ptr, "SNR-Counts: %d %d %d\n", SNRY, SNRR, SNRG);
    fprintf(ptr, "RootCoordinates: %f\n", rootCoords);
    fprintf(ptr, "RootAxis: %d\n", rootAXIS);
    fprintf(ptr, "FNodeCoordinates: %f\n", nodeLCoords);
    fprintf(ptr, "FNodeAxis: %d\n", nodeLAxis);
    fprintf(ptr, "SNodeCoordinates: %f\n", nodeRCoords);
    fprintf(ptr, "SNodeAxis: %d\n", nodeRAxis);
    fprintf(ptr, "LineCount: %d\n", linecount);
    fclose(ptr);
    system("clear");
    printf("\033[1;31m");
    printf("--------------------------------------------------------\n");
    printf("Perfect Root I: %f\n", rootI);
    printf("Perfect Root Axis: %d\n", rootAXIS);
    printf("Perfect Root Coordinates: %f\n", rootCoords);
    printf("--------------------------------------------------------\n");
    printf("Perfect L-Node I: %f\n", nodeLI);
    printf("Perfect L-Node Axis: %d\n", nodeLAxis);
    printf("Perfect L-Node Coordinates: %f\n", nodeLCoords);
    printf("Left Side = Yellow Apple: %d - Red Apple: %d - Green Apple: %d\n", FNLY, FNLR, FNLG);
    printf("Right Side = Yellow Apple: %d - Red Apple: %d - Green Apple: %d\n", FNRY, FNRR, FNRG);
    printf("--------------------------------------------------------\n");
    printf("Perfect R-Node I: %f\n", nodeRI);
    printf("Perfect R-Node Axis: %d\n", nodeRAxis);
    printf("Perfect R-Node Coordinates: %f\n", nodeRCoords);
    printf("Left Side = Yellow Apple: %d - Red Apple: %d - Green Apple: %d\n", SNLY, SNLR, SNLG);
    printf("Right Side = Yellow Apple: %d - Red Apple: %d - Green Apple: %d\n", SNRY, SNRR, SNRG);
    printf("--------------------------------------------------------\n");
    printf("\033[0m");
}

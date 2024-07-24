#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAXRANDOMVALUE 3
#define MAXPREV 500

int arr[4][4] = {0}, c[4], temp = 0, len = 0, score = 0, highscore = 0, count = 0, ch = 0;

int findlen(int n) {
    int length = 0;
    while (n != 0) {
        n /= 10;
        length++;
    }
    return length;
}

void print() {
    int i, j, k, len1;
    printf("\n\t\t\t\t\t===============2048==============\n");
    printf("\t\t\t\t\tYOUR SCORE=%d\n\t\t\t\t\t", score);
    if (score < highscore) {
        printf("HIGH SCORE=%d\t\t\t\t\t\n", highscore);
    } else {
        highscore = score;
        printf("HIGH SCORE=%d\t\t\t\t\t\n", highscore);
    }
    printf("\t\t\t\t\t---------------------------------\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (j == 0) {
                printf("\t\t\t\t\t|");
            }
            if (arr[i][j] != 0) {
                len1 = findlen(arr[i][j]);
                for (k = 0; k < 4 - len1; k++) {
                    printf(" ");
                }
                printf("%d", arr[i][j]);
                for (k = 0; k < 4 - len1; k++) {
                    printf(" ");
                }
                for (k = 0; k < len1 - 1; k++) {
                    printf(" ");
                }
                printf("|");
            } else {
                for (k = 0; k < 8 - 2 * len1 - 1; k++) {
                    printf(" ");
                }
                printf("|");
            }
        }
        if (i != 3) {
            printf("\n");
            printf("\t\t\t\t\t---------------------------------\n");
        }
    }
    printf("\n\t\t\t\t\t---------------------------------\n");
    printf("\t\t\t\t\tPREV-> P\t\t\t\t\t\n");
    printf("\t\t\t\t\tRESTART-> R\t\t\t\t\t\n");
    printf("\t\t\t\t\tEXIT-> U\t\t\t\t\t\n");
    printf("\t\t\t\t\tENTER YOUR CHOICE -> W,S,A,D\n\t\t\t\t\t");
}

void movevalue(int k) {
    int i;
    if (k == 3) {
        return;
    }
    for (i = k; i < 4; i++) {
        if (c[i] != 0) {
            movevalue(i + 1);
            for (; i < 4; i++) {
                if (c[i + 1] != 0) {
                    break;
                }
                c[i + 1] = c[i];
                c[i] = 0;
            }
        }
    }
}

void addrandomno() {
    int no;
    srand(time(NULL));
    int i, j; // RANDOM INDEX
    do {
        i = (rand()) % (MAXRANDOMVALUE + 1);
        j = (rand()) % (MAXRANDOMVALUE + 1);
    } while (arr[i][j] != 0);
    no = 2 * ((rand() % 10) + 1);
    if (no == 3 || no == 2) {
        arr[i][j] = 4;
    } else {
        arr[i][j] = 2;
    }
}

void rupdate() {
    int i, j;
    for (i = 3; i > 0; i--) {
        if (c[i] == c[i - 1]) {
            c[i] += c[i - 1];
            score = score + c[i];
            if (score > highscore) {
            }
            temp = 1;
            c[i - 1] = 0;
        } else if (c[i - 1] == 0 && c[i] != 0) {
            c[i - 1] = c[i];
            c[i] = 0;
            temp = 1;
        } else if (c[i] == 0) {
            temp = 1;
        }
    }
    movevalue(0);
}

void createprev(int ***p) {
    int i, j, k;
    FILE *ptr;
    ptr = fopen("hstr.txt", "a");
    fprintf(ptr, "%d ", score);
    fclose(ptr);
    if (count == MAXPREV + 1) {
        for (i = MAXPREV; i > 0; i--) {
            for (j = 0; j < 4; j++) {
                for (k = 0; k < 4; k++) {
                    p[i][j][k] = p[i - 1][j][k];
                }
            }
        }
        count = MAXPREV;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            p[MAXPREV - count][i][j] = arr[i][j];
        }
    }
}

void updatearrtoprev(int ***p) {
    int data, i, j;
    if (count == 0) {
        printf("\n\t\t\t\t\t******FURTHER MORE PREV NOT POSSIBLE********");
        return;
    }
    FILE *ptr = fopen("hstr.txt", "r+");
    for (i = 0; i < count; i++) {
        fscanf(ptr, "%d ", &data);
    }
    score = data;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            arr[i][j] = p[MAXPREV - count][i][j];
        }
    }
    count--;
}

void resetgame() {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            arr[i][j] = 0;
        }
    }
    system("clear"); // Changed from "cls" to "clear"
    score = 0;
    addrandomno();
}

int main() {
    int i, j, k, m, n, same = 0;
    char choice, s = -33, reschk;
    printf("\n\t\t\t\t\t===============2048==============\n");
    printf("\n\t\t\t\t\tWELCOME TO PUZZLE 2048");
    printf("\n\t\t\t\t\t> DEVELOPED BY :- AKSHAY METHANIYA");
    printf("\n\t\t\t\t\t> CONTROLS");
    printf("\n\t\t\t\t\t  FOR MOVES:- 'W','S','A','D'");
    printf("\n\t\t\t\t\t  GO BACKWARD:- 'P'");
    printf("\n\t\t\t\t\t  RESTAT THE GAME:- 'R'");
    printf("\n\t\t\t\t\t  EXIT:-'U'");
    printf("\n\n\t\t\t\t\tPRESS ANY KEY TO START THE GAME....\n\t\t\t\t\t");
    getchar();
    system("clear"); // Changed from "cls" to "clear"
    printf("\n\t\t\t\t\t===============2048==============\n");
    printf("\n\n\t\t\t\t\tLOADING...\n\n\t\t\t\t\t");
    for (int i = 0, j; i < 35; i++) {
        printf("%c", s);
        j = i;
        if (i % 2 != 0 && i < 20) {
            sleep(1);
        }
    }
    sleep(1);
    system("clear"); // Changed from "cls" to "clear"
    int ***p;
    p = (int ***)malloc(sizeof(int *) * (MAXPREV + 1));
    for (int i = 0; i < MAXPREV + 1; i++) {
        *(p + i) = (int **)malloc(sizeof(int *) * 4);
    }
    for (int i = 0; i < MAXPREV + 1; i++) {
        for (int j = 0; j < 4; j++) {
            p[i][j] = (int *)malloc(sizeof(int) * 4);
        }
    }
    createprev(p);
    FILE *ptr;
    ptr = fopen("highscore.txt", "r");
    if (ptr) {
        fscanf(ptr, "%d", &highscore);
        fclose(ptr);
    }
    addrandomno();
    while (1) {
        same = 0;
        print();
        choice = getchar();
        system("clear"); // Changed from "cls" to "clear"
        switch (choice) {
            case 'W':
            case 'w':
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < 4; j++) {
                        c[j] = arr[j][i];
                    }
                    rupdate();
                    for (j = 0; j < 4; j++) {
                        arr[j][i] = c[j];
                    }
                }
                createprev(p);
                count++;
                break;
            case 'S':
            case 's':
                for (i = 0; i < 4; i++) {
                    for (j = 3; j >= 0; j--) {
                        c[3 - j] = arr[j][i];
                    }
                    rupdate();
                    for (j = 3; j >= 0; j--) {
                        arr[j][i] = c[3 - j];
                    }
                }
                createprev(p);
                count++;
                break;
            case 'A':
            case 'a':
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < 4; j++) {
                        c[j] = arr[i][j];
                    }
                    rupdate();
                    for (j = 0; j < 4; j++) {
                        arr[i][j] = c[j];
                    }
                }
                createprev(p);
                count++;
                break;
            case 'D':
            case 'd':
                for (i = 0; i < 4; i++) {
                    for (j = 3; j >= 0; j--) {
                        c[3 - j] = arr[i][j];
                    }
                    rupdate();
                    for (j = 3; j >= 0; j--) {
                        arr[i][j] = c[3 - j];
                    }
                }
                createprev(p);
                count++;
                break;
            case 'P':
            case 'p':
                updatearrtoprev(p);
                break;
            case 'R':
            case 'r':
                resetgame();
                break;
            case 'U':
            case 'u':
                ptr = fopen("highscore.txt", "w");
                fprintf(ptr, "%d", highscore);
                fclose(ptr);
                return 0;
            default:
                printf("\n\t\t\t\t\t  INVALID ENTRY\n\t\t\t\t\t  TRY AGAIN\n");
                break;
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (arr[i][j] == 0) {
                    same = 1;
                }
            }
        }
        if (temp == 1 || same == 0) {
            addrandomno();
        }
        temp = 0;
    }
}

#include <stdio.h>
#include <string.h>

void Print (char * state);
char* Trans (char * state, int x);
void CheckWin (char * state, int * win);
void CheckTie (char * state, int * tie);
void play ();

int main () {
    printf("===============================================================================================\n");
    printf("===============================================================================================\n");
    printf("######## ####  ######          ########    ###     ######          ########  #######  ######## \n");
    printf("   ##     ##  ##    ##            ##      ## ##   ##    ##            ##    ##     ## ##       \n");
    printf("   ##     ##  ##                  ##     ##   ##  ##                  ##    ##     ## ##       \n");
    printf("   ##     ##  ##       #######    ##    ##     ## ##       #######    ##    ##     ## ######   \n");
    printf("   ##     ##  ##                  ##    ######### ##                  ##    ##     ## ##       \n");
    printf("   ##     ##  ##    ##            ##    ##     ## ##    ##            ##    ##     ## ##       \n");
    printf("   ##    ####  ######             ##    ##     ##  ######             ##     #######  ######## \n");
    printf("===============================================================================================\n");
    printf("===============================================================================================\n");

    printf("\nHello, there! I'm O.\nI'm a smart computer that knows how to play tic-tac-toe, and I'll be playing one with you! :)\n");
    play();
    return 0;
}

void play () {
    char CState[5] = "q000";
    char history[100] = "q000";
    char first, dump[100];
    int move;
    int win, tie = 0;

    printf("\nLet's go!\n");
    printf("\nFirst player (x = you, o = O): "); scanf(" %c", &first);
    
    while ((first != 'x') && (first != 'o')) {
        printf("Your input is not 'x' or 'o'. Also, I can only read one word at a time. Please don't tease me.\n");
        printf("Re-input: "); scanf(" %c", &first);
    }
    printf("\nFirst move is filling the middle slot.\n");
    if (first == 'x') {
        printf("Here, let me put it for you.\n\n");
        strcpy(CState, Trans(CState, -1));
    }
    if (first == 'o') {
        printf("Here I go!\n\n");
        strcpy(CState, Trans(CState, 0));
    }
    Print(CState);
    strcat(history, " -> "); strcat(history, CState);
    
    while ((win == 0) && (tie == 0)) {
        printf("Your next move (1-9): ");
        if (scanf("%d", &move)) {
            if ((move >= 1) && (move <= 9)) {
                strcpy(CState, Trans(CState, move));
                printf("\n"); Print(CState);
                strcat(history, " -> "); strcat(history, CState);
                CheckWin(CState, &win);
                CheckTie(CState, &tie);
            } else {
                printf("You inserted %d. You can only input numbers 1-9.\n\n", move);
            }
        } else {
            printf("You've input (a) letter(s)! That's dangerous! But hang on, I've got it under control, one word at a time...\n\n");
            scanf("%s", dump);
        }
    }

    if (win) {
        printf("\nI win!\nLet's try again if you're up for it.\n");
    } else if (tie) {
        printf("\nIt's a tie.\nFun fact: If we're both smart, tic-tac-toes will always end in a tie!\n");
    } else {
        printf("\nDefintely an error... I wasn't programmed to lose.\n");
    }

    printf("\nStates history: %s\n", history);

    
}

void Print (char * state) {
    FILE *fp;
    char MARK[6], label[5], content[10];

    fp = fopen("file.txt", "r");

    fscanf(fp, "%s", MARK);
    while (strcmp(MARK, "KAMUS") != 0) {
        fscanf(fp, "%s", MARK);
    }

    fscanf(fp, "%s", label);
    while (strcmp(label, state) != 0) {
        fscanf(fp, "%s", label);
        fscanf(fp, "%s", label);
    }
    fscanf(fp, "%s", content);
    printf("%c %c %c\n", content[0], content[1], content[2]);
    printf("%c %c %c\n", content[3], content[4], content[5]);
    printf("%c %c %c\n", content[6], content[7], content[8]);
};

char* Trans (char * state, int x) {
    FILE *fp;
    char MARK[9], skip[2], s[5], to[5], *final;

    fp = fopen("file.txt", "r");
    fscanf(fp, "%s", MARK);
    while (strcmp(MARK, "TRANSISI") != 0) {
        fscanf(fp, "%s", MARK);
    }

    for (int i = 1; i <= 11; i++) {
        fscanf(fp, "%s", skip);
    }

    fscanf(fp, "%s", s);
    while (strcmp(s, state) != 0) {
        fscanf(fp, "%s", s); //transisi p
        fscanf(fp, "%s", s); //transisi c
        fscanf(fp, "%s", s); //transisi 1
        fscanf(fp, "%s", s); //transisi 2
        fscanf(fp, "%s", s); //transisi 3
        fscanf(fp, "%s", s); //transisi 4
        fscanf(fp, "%s", s); //transisi 5
        fscanf(fp, "%s", s); //transisi 6
        fscanf(fp, "%s", s); //transisi 7
        fscanf(fp, "%s", s); //transisi 8
        fscanf(fp, "%s", s); //transisi 9
        fscanf(fp, "%s", s); //state berikutnya
    }

    for (int i = 1; i <= x+2; i++) {
        fscanf(fp, "%s", to);
    }
    if (strcmp(to, "----") != 0) {
        final = to;
    } else {
        printf("But that spot is occupied! See?\n");
        final = state;
    }
    return final;
}

void CheckWin (char * state, int * win) {
    FILE *fp;
    char MARK[9], s[5];

    fp = fopen("file.txt", "r");

    fscanf(fp, "%s", MARK);
    while (strcmp(MARK, "MENANG") != 0) {
        fscanf(fp, "%s", MARK);
    }

    fscanf(fp, "%s", s);
    while (strcmp(s, "END") != 0) {
        if (strcmp(s, state) == 0) {
            *win = 1;
            break;
        } else {
            fscanf(fp, "%s", s);
        }
    }
};

void CheckTie (char * state, int * tie) {
    FILE *fp;
    char MARK[9], s[5];

    fp = fopen("file.txt", "r");

    fscanf(fp, "%s", MARK);
    while (strcmp(MARK, "SERI") != 0) {
        fscanf(fp, "%s", MARK);
    }

    fscanf(fp, "%s", s);
    while (strcmp(s, "END") != 0) {
        if (strcmp(s, state) == 0) {
            *tie = 1;
            break;
        } else {
            fscanf(fp, "%s", s);
        }
    }
};
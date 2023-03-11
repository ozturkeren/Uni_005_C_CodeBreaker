// Eren Öztürk METU NCC 140 PA4
// A single-player game that tries to find the secret code combination of colors
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void Create_code(char**);
void player_guess(char**);
void find_score(char**, char**, char**);
int display_score(char**);
void display_winner(int, int, char**);

int main(){
    printf("CODEBREAKER IS STARTING!\n");
    srand(time(NULL));
    int round, counter, breakedCode;
    char wantContinue;

    char** listOfSecretColours;
    listOfSecretColours=(char**)malloc(4*sizeof(char*));//Takes 4 color
    for(counter=0;counter<4;counter++){
        listOfSecretColours[counter]=malloc(7*sizeof(char));//Size of colors is 7
    }
    if(listOfSecretColours == NULL){
        printf("Couldn't create the string!");
        return -1;
    }

    char** listOfScore;
    listOfScore=(char**)malloc(4*sizeof(char*));//Takes 4 color
    for(counter=0;counter<4;counter++){
        listOfScore[counter]=malloc(6*sizeof(char));//Size of colors is 6
    }
    if(listOfScore == NULL){
        printf("Couldn't create the string!");
        return -1;
    }

    char** listOfPlayersColours;
    listOfPlayersColours=(char**)malloc(4*sizeof(char*));//Takes 4 color
    for(counter=0;counter<4;counter++){
        listOfPlayersColours[counter]=malloc(7*sizeof(char));//Size of colors is 7
    }
    if(listOfPlayersColours == NULL){
        printf("Couldn't create the string!");
        return -1;
    }


    do{
        Create_code(listOfSecretColours);

        for(round=1;round<9;round++){

            printf("%d.",round);
            player_guess(listOfPlayersColours);
            find_score(listOfSecretColours, listOfPlayersColours, listOfScore);
            breakedCode=display_score(listOfScore);
            display_winner(breakedCode, round, listOfSecretColours);

            if(breakedCode==1)
                break;
        }

        printf("\nDo you want to play again (Y/N)?");
        fflush(stdin);
        scanf("%c",&wantContinue);
    }while(wantContinue=='Y');

    for(counter=0;counter<4;counter++){
        free(listOfPlayersColours[counter]);
    }
    free(listOfPlayersColours);//2D array which name is listOfPlayersColours getting its freedom

    for(counter=0;counter<4;counter++){
        free(listOfScore[counter]);
    }
    free(listOfScore);//2D array which name is listOfScore getting its freedom

    for(counter=0;counter<4;counter++){
        free(listOfSecretColours[counter]);
    }
    free(listOfSecretColours);//2D array which name is listOfSecretColours getting its freedom

    printf("BYEE!!");

    return 0;
}

void Create_code(char** list){
    int counter, guess;
    for(counter=0;counter<4;counter++){
        guess=rand()%5 +2;//2->red 3->green 4->orange 5->blue 6->yellow
        if(guess==2){
            list[counter]="Red";
        }
        else if(guess==3){
            list[counter]="Green";
        }
        else if(guess==4){
            list[counter]="Orange";
        }
        else if(guess==5){
            list[counter]="Blue";
        }
        else{
            list[counter]="Yellow";
        }
    }
    printf("Secret Code Generated!\n");
}

void player_guess(char** playersList){
    printf("Enter your guess: ");
    fflush(stdin);
    scanf("%s %s %s %s",playersList[0], playersList[1], playersList[2], playersList[3]);
}

void find_score(char** secretList, char** playersGuess, char** scoreList){
    int counter;
    for(counter=0;counter<4;counter++){
        if(strcmp(secretList[counter], playersGuess[counter])==0){
            scoreList[counter]="Black";
        }
        else if(strcmp(playersGuess[counter], secretList[0])==0){
            scoreList[counter]="White";
        }
        else if(strcmp(playersGuess[counter], secretList[1])==0){
            scoreList[counter]="White";
        }
        else if(strcmp(playersGuess[counter], secretList[2])==0){
            scoreList[counter]="White";
        }
        else if(strcmp(playersGuess[counter], secretList[3])==0){
            scoreList[counter]="White";
        }
        else{
            scoreList[counter]="_";
        }
    }
}

int display_score(char** scoreList){
    int counter;
    printf("Your score: ");
    for(counter=0;counter<4;counter++){
        printf("%s ",scoreList[counter]);
    }
    printf("\n");
    if((strcmp(scoreList[0], "Black")==0) && (strcmp(scoreList[1], "Black")==0) && (strcmp(scoreList[2], "Black")==0) && (strcmp(scoreList[3], "Black")==0)){
        return 1;
    }
    return 0;
}

void display_winner(int breaked, int round, char** codeList){
    int counter;
    if(round==8 && breaked==0){
        printf("You LOST!\nSecret Code: ");
        for(counter=0;counter<4;counter++){
            printf("%s ",codeList[counter]);
        }
        printf("\nCODEMAKER WINS!\n");
    }
    else if(breaked==1){
        printf("You win the game!\nSecret code= ");
        for(counter=0;counter<4;counter++){
            printf("%s ",codeList[counter]);
        }
        printf("\nYou found it after %d guesses!\n",round);
    }
}

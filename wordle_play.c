#include <stdio.h>
#include <string.h>

#include <stdio.h>  // For printf
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time() to seed the generator
#include "hashmap.h"
#define WORD_LENGTH 5
#define MAX_TRIES 6
#define GREEN "\033[0;32m"
  #define YELLOW "\033[0;33m"
  #define BLUE "\033[0;34m"
  #define RESET "\033[0m"
FILE* fpALL; 
FILE* fpSol;
void colorize(char* a, char*b);
FILE* fpView;
int ifValidWord(char* a, FILE *fp);
void toLower(char* a);
void gameScreen(FILE* fp, int count, char* a, char* color);
void startingScreen();
char* chooseTarget(FILE* fp);
void resultScreen(int i, char*b);
void wordCheck(char* a,char* guess, char* correct);
void receiveWord(char* guessedWord, FILE *fp);
static void die(const char *s) { perror(s); exit(0); }
int main(int argc, char** argv){
    if (argc != 1){
        fprintf(stderr, "usage: <filename>\n");
        exit(1);}
    startingScreen();
    fpALL = fopen("allWords.txt","rb");
    fpSol = fopen("solutionWords.txt","rb");

    char *targetWord = chooseTarget(fpSol);
    char* temp = targetWord;
    receiveWord(targetWord, fpALL);



    free(temp);
    fclose(fpALL);
    fclose(fpSol);
}

void startingScreen(){
    printf("+-------------------+\n");
    printf("| WELCOME TO WORDLE |\n");
    printf("+-------------------+\n");
    fflush(stdout);
}

void gameScreen(FILE* fp, int count, char* word, char* color){
    char* a = "+-------------------+\n";
    char* b = "|   |   |   |   |   |\n";
    char buf[70];
    if(count == 0){
    fputs(a,fp);}
        
    if (count != 0) {
      fseek(fp, 0, SEEK_END);
    
    for(int i = 0; i < 5; i++){
        if(color[i] =='g'){
                sprintf(buf, "| \033[0;32m%c\033[0m ", word[i]);

        }
        else if(color[i] == 'y'){
                sprintf(buf, "| \033[0;33m%c\033[0m ", word[i]);
        }
        else{
         sprintf(buf, "| \033[0;90m%c\033[0m ", word[i]);
        }
        fputs(buf, fp);
    }
    fputs("|\n", fp);
    fputs(a, fp); 
    }
    fseek(fp, 0, SEEK_SET);
    while(fgets(buf, sizeof(buf),fp)){
         printf("%s", buf);
            }
    
    for (int i = 0; i < 6-count; i++){
        printf("%s",b);
        printf("%s",a);

}
}
void receiveWord(char* guessedWord, FILE *fp){
    int count = 0;
    int guessed = 0;
    char word[7];
    char* screenStorage = "gamegrind";
    FILE* fpView = fopen(screenStorage, "w+b");
    gameScreen(fpView, count, "", "");
    while(count < MAX_TRIES && guessed == 0){
        printf("Type 5 letter word: \n");
        if (fgets(word, sizeof(word), stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            continue;
        }
        size_t len = strlen(word);
        if (len > 0 && word[len-1] == '\n') {
            word[len-1] = '\0';
        }

        // Validate word length
        if (strlen(word) != 5) {
            fprintf(stderr, "Word must be exactly 5 letters. Try again.\n");
            continue;
        }

        toLower(word);

        // Check if word is in dictionary
        if (ifValidWord(word, fp) == 0) {
            fprintf(stderr, "Invalid word '%s', try again: \n", word);
            continue;
        }

        count++;
        char* color = malloc(6);
        char* temp = color;
        wordCheck(color, word, guessedWord);
        gameScreen(fpView, count, word, color);
        
        
        if(strcmp(word,guessedWord)== 0){
            guessed = 1;
            break;}
        free(temp);
    }
    fclose(fpView);
    resultScreen(guessed, guessedWord);
}

void wordCheck(char* res,char* guess, char* correct){
        strcpy(res, "eeeee");
        Map * complementMap = Map_create( 26 );
        for(int i = 0; i < strlen(correct); i++){
            if(Map_contains(complementMap, correct[i], 26) != 0){
                Map_add(complementMap, correct[i], Map_get(complementMap, correct[i], 26)+1, 26);
            }
            else{
                Map_add( complementMap, correct[i], 1, 26);
            }
        }
        for(int i = 0; i < strlen(guess); i++){
             if(guess[i] == correct[i]){
                res[i] = 'g';
                 Map_add(complementMap, correct[i], Map_get(complementMap, correct[i], 26)-1, 26);
             }
        }
        for(int i = 0; i <strlen(guess); i++)
        {
            if(res[i] != 'g'){
                if(Map_contains(complementMap, guess[i], 26) != 0 &&  Map_get(complementMap, guess[i], 26) > 0){
                    res[i] = 'y';
                    Map_add(complementMap, guess[i], Map_get(complementMap, correct[i], 26)-1, 26);
                }
                else{
                    res[i] = 'b';
                }
            }
        }
        Map_destroy(complementMap, 26);
}

void resultScreen(int guessed, char *guessedWord){

    if (guessed){

        printf("+-------------------+\n");
        printf("|     YOU WON!!!    |\n");
        printf("+-------------------+\n");
        printf("+-------------------+\n");
        printf("| %c | %c | %c | %c | %c |\n", guessedWord[0], guessedWord[1],guessedWord[2],guessedWord[3],guessedWord[4]);
        printf("+-------------------+\n");
        fflush(stdout);
    }
    else{

        printf("+-------------------+\n");
        printf("|     YOU LOST!!!   |\n");
        printf("+-------------------+\n");

        printf("+-------------------+\n");
        printf("| %c | %c | %c | %c | %c |\n", guessedWord[0], guessedWord[1],guessedWord[2],guessedWord[3],guessedWord[4]);
        printf("+-------------------+\n");
        fflush(stdout);
    }
}

char* chooseTarget(FILE* fp){
    srand(time(NULL));
    int randomLine = rand() % 2315;  // 0 to 2314 inclusive

    fseek(fp, 0, SEEK_SET);
    fseek(fp, 6 * randomLine, SEEK_SET);

    char* word = malloc(6);
    if (word == NULL) {
        die("Memory allocation failed!\n");
        return NULL;
    }
    if (fread(word, 1, 6, fp) == 6) {
        word[5] = '\0';
        return word;
    } else {
        free(word);
        die("Failed to read word from file");
        return NULL;
    }
    // close both files
}


int ifValidWord(char *word, FILE* fp){
    if (strlen(word) != 5){
        return 0;}
    char test[6];
    while(fread(test, 6,1 , fp)){
        test[5] = '\0';
        if(strcmp(test,word) == 0){
            fseek(fp,0,SEEK_SET);
            return 1;}



    }

    fseek(fp,0, SEEK_SET);
    return 0;
}


void toLower(char * str) {
    int i = 0;
    while (str[i]) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] |= 0x20; //Make lowercase
        }
        ++i;
    }
} 

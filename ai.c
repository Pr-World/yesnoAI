#include "ai.h"

int main() {
    AImodel ai;

    printf("Enter your question ( `end` to end ) :\n");
    start:
    printf("\n Q) ");
    resetAI(ai);
    ai = inputAI();
    if ( strcmp(ai.data, "end") == 0 ) { return 0; }
    ai = AskAI(ai);
    if ( ai.result == 1 ) {
        printf(" Ans) Yes !\n");
    } else if ( ai.result == 2 ) {
        printf(" Ans) No !\n");
    } else {
        printf(" Ans) Not a proper question to ask !\n");
    }
    goto start;
}
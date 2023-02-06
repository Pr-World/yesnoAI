#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

#ifdef __linux__
#include <unistd.h>
#include <termios.h>
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

#elif _WIN32

#include<conio.h>

#endif

typedef struct AI {
    char * data;
    size_t size;
    int result;
    bool _alloc;
} AImodel;

void resetAI(AImodel ai) {
    if ( ai._alloc ) {
        free(ai.data);
    }
}

AImodel NewAI(size_t size) {
    AImodel ai = { (char*)malloc(size), size, false, true};
    return ai;
}

AImodel renewAI(AImodel pai, size_t size) {
    AImodel ai = { (char*)realloc(pai.data, size), size, false, true};
    return ai;
}

AImodel AskAI(AImodel ai) {
    bool spc = false;
    AImodel newAi;
    size_t len = strlen(ai.data);
    if (
        (ai.data[0] == ' ' && ai.data[1] == ' ')
        || (ai.data[0] == ' ' && ai.data[len - 1] == ' ')
        || (ai.data[len-1] == ' ' && ai.data[len-2] == ' ')
    ) {
        newAi.result = 3;
        goto ret;
    }
    for ( size_t i = 0; i <= len; i++ ) {
        if ( ai.data[i] == ' ') {
            spc = !spc;
        }
    }

    newAi.result = spc+1;
    
    ret:
    newAi.data = ai.data;
    newAi.size = ai.size;
    newAi._alloc = ai._alloc;
    return newAi;
}

AImodel inputAI() {
    char c;
    AImodel ai = NewAI(3);
    size_t pos = 0;
    int spc = 0;
    printf("\n Q) ");
    while((c = getch())) {
        if ( (c == '\b' || c == 127)) {
            if (!pos) { continue; }
            ai.data[--pos] = '\0';
            printf("\r     ");
            for(size_t i = 0; i < strlen(ai.data); i++) {
                putchar(' ');
            }
            printf("\r Q) ");
            int spc = 0;
            for(size_t i = 0; i < strlen(ai.data); i++) {
                if ( ( i == 0 || spc ) && ai.data[i] == ' ' ) {
                    spc = 1;
                } else {
                    putchar(ai.data[i]);
                    spc = 0;
                }
            }
            continue;
        }
        if ( (!pos || spc) && c == ' ') {
            spc = 1;
        } else {
            spc = 0;
            printf("%c", c);
        }
        if ( c == '\n' ) {
            break;
        }
        ai.data[pos] = c;
        ai.data[++pos] = '\0';
        ai = renewAI(ai, ai.size+1);
    }
    return ai;
}
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

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
    if ( ai.data[strlen(ai.data)-1] == ' ' ) {
        newAi.result = 3;
        goto ret;
    }
    for ( size_t i = 0; i <= ai.size; i++ ) {
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
    while((c = getchar())) {
        if ( c == '\n' ) {
            break;
        }
        ai.data[pos] = c;
        ai.data[++pos] = '\0';
        ai = renewAI(ai, ai.size+1);
    }
    return ai;
}
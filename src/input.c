#include "input.h"

#include "util/memset.h"
#include "util/string.h"

#include <stdlib.h> // for malloc, realloc, free only!

void userinput_init() {
    input_length = 0;
    num_tokens = 0;
}

void userinput_reset() {
    for(int i = 0; i < input_length; i++){
        input_buffer[i] = '\0';
    }
    for(int i = 0; i < num_tokens; i++){
        tokens[i] = memset(tokens[i], sizeof(char) * 2, '\0');
    }
    input_length = 0;
    num_tokens = 0;
}


void userinput_cleanup() {
    for(int i = 0; i < input_length; i++){
        input_buffer[i] = '\0';
    }
    for(int i = 0; i < num_tokens; i++){
        free(tokens[i]);
    }
    free(tokens);
    input_length = 0;
    num_tokens = 0;
}


long handle_user_input(const char *user_input, long str_len, char **command) {
    if(command == NULL){
        return -1;
    }
    userinput_reset();
    strncat(input_buffer, user_input, str_len);
    for(long i = str_len - 1; i >= 0; i--){
        if(input_buffer[i] == ' ' || input_buffer[i] == '\n'){
            input_buffer[i] = '\0';
        }
        else{
            break;
        }
    }
    *command = input_buffer;
    input_length = str_len;
    return strlen(input_buffer);
}

long tokenize_input(char *str, long strlen, char ***user_tokens) {
    if (str == NULL) {
        return -1;
    }

    long words = 1;

    for (int i = 0; i < strlen; i++) {
        if (str[i] == ' ') {
            words++;
        }
    }

    tokens = (char **) realloc(tokens, (words + 1) * sizeof(char *));

    char word[strlen];
    int str_i = 0;
    int word_i = 0;
    int i = 0;

    while (str[str_i] != '\0') {
        if (str[str_i] != ' ') {
            word[word_i] = str[str_i];
            word_i++;
        }
        else {
            tokens[i] = malloc(sizeof(char) * (word_i + 1));

            for (int j = 0; j < word_i; j++) {
                tokens[i][j] = word[j];
            }

            tokens[i][word_i] = '\0';

            word_i = 0;
            i++;
        }

        str_i++;
    }

    if (word_i != 0) {
        tokens[i] = malloc(sizeof(char) * (word_i + 1));

        for (int j = 0; j < word_i; j++) {
            tokens[i][j] = word[j];
        }

        tokens[i][word_i] = '\0';
    }

    tokens[words] = NULL;

    *user_tokens = tokens;
    num_tokens = words + 1;

    return num_tokens;
}



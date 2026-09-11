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
        input_buffer[i] = '\0'; // clear the raw input buffer
    }
    for(int i = 0; i < num_tokens; i++){
        // clear the whole token, not just 2 bytes of it
        tokens[i] = memset(tokens[i], strlen(tokens[i]), '\0');
    }
    input_length = 0;
    num_tokens = 0;
}


void userinput_cleanup() {
    for(int i = 0; i < input_length; i++){
        input_buffer[i] = '\0';
    }
    for(int i = 0; i < num_tokens; i++){
        free(tokens[i]); // free each token string
    }
    free(tokens); // free the token array itself
    input_length = 0;
    num_tokens = 0;
}


long handle_user_input(const char *user_input, long str_len, char **command) {
    if(command == NULL){
        return -1;
    }
    userinput_reset();
    strncat(input_buffer, user_input, str_len);

    // trim trailing spaces/newlines, walking back from the buffer's real
    // length so newlines at the end always get stripped
    long buf_len = strlen(input_buffer);
    for(long i = buf_len - 1; i >= 0; i--){
        if(input_buffer[i] == ' ' || input_buffer[i] == '\n'){
            input_buffer[i] = '\0';
        }
        else{
            break;
        }
    }
    *command = input_buffer;
    input_length = strlen(input_buffer);
    return strlen(input_buffer);
}

long tokenize_input(char *str, long strlen_, char ***user_tokens) {
    if (str == NULL) {
        return -1;
    }

    // free tokens from any previous call so we don't leak them
    for (int i = 0; i < num_tokens; i++) {
        free(tokens[i]);
    }

    // count words by counting spaces that are actually followed by a new
    // word, so consecutive spaces don't inflate the count
    long words = 0;
    int in_word = 0;
    for (int i = 0; i < strlen_; i++) {
        if (str[i] != ' ') {
            if (!in_word) words++;
            in_word = 1;
        } else {
            in_word = 0;
        }
    }

    tokens = (char **) realloc(tokens, (words + 1) * sizeof(char *));

    char word[strlen_ + 1];
    int str_i = 0;
    int word_i = 0;
    int i = 0;

    while (str[str_i] != '\0') {
        if (str[str_i] != ' ') {
            word[word_i] = str[str_i]; // accumulate current word
            word_i++;
        }
        else if (word_i != 0) {
            // only flush a token when we've actually built up a word,
            // so runs of spaces don't create empty tokens
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
        // flush the final word (no trailing space to trigger it above)
        tokens[i] = malloc(sizeof(char) * (word_i + 1));

        for (int j = 0; j < word_i; j++) {
            tokens[i][j] = word[j];
        }

        tokens[i][word_i] = '\0';
        i++;
    }

    tokens[i] = NULL;

    *user_tokens = tokens;
    num_tokens = i + 1;

    return num_tokens;
}
/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tokenizer.h"


char is_escape_character(char character) {
  char* escape_sequence = "ntvbrfa\\?'\"";
  char* escape_characters = "\n\t\v\b\r\f\a\\\?\'\"";
  int offset = 0;

  for(offset = 0; offset < strlen(escape_sequence); offset++) {
    if(*(escape_sequence + offset) == character) {
      return *(escape_characters + offset);
    }
  }

  return 0;
}

int char_to_hex(char character) {
  if(isdigit(character))
    return character - '0';

  if (islower(character))
    return character - 'a' + 10;

  return character - 'A' + 10;
}


int char_to_oct(char character) {
  return character - '0';
}


int is_oct_digit(char oct_digit) {
  if(oct_digit >= '0' && oct_digit <= '7')
    return 1;

  return 0;
}


char* unescape_string(char* string) {
  char* unescaped_string = malloc(strlen(string) + 1);
  int hex_count;
  int oct_count;
  int current_position = 0;
  int unescaped_string_position = 0;
  unsigned char escape_character = 0;

  for(current_position = 0; current_position < strlen(string); current_position++) {
    escape_character = *(string + current_position);
    if(*(string + current_position) == '\\') {
      if(*(string + current_position + 1) == 'x') {
        current_position++;
        escape_character = 0;
        for(hex_count = 1; hex_count <= MAX_HEX_CHARS; hex_count++) {
          if(!isxdigit(*(string + current_position + hex_count))) {
            break;
          }
          escape_character = escape_character * 16 + char_to_hex(*(string + current_position + hex_count));
        }
        hex_count--;
        current_position += hex_count;
      } else if(is_oct_digit((*(string + current_position + 1))) == 1) {
        escape_character = 0;
        for(oct_count = 1; oct_count <= MAX_OCT_CHARS; oct_count++) {
          if(is_oct_digit(*(string + current_position + oct_count)) == 0) {
            break;
          }
          escape_character = escape_character * 8 + char_to_oct(*(string + current_position + oct_count));
        }
        current_position += oct_count;
      } else {
        escape_character = is_escape_character(*(string + current_position + 1));

        if(escape_character == 0) {
          escape_character = *(string + current_position);
        } else {
          current_position++;
        }
      }
    }

    *(unescaped_string + unescaped_string_position) = escape_character;
    unescaped_string_position++;
    escape_character = 0;
  }

  *(unescaped_string + unescaped_string_position) = '\0';

  return unescaped_string;
}




TokenizerT *TKCreate(char *separators, char *ts) {
  TokenizerT* tokenizer;

  if(separators == NULL || ts == NULL){
    return NULL;
  }

  tokenizer = malloc(sizeof(TokenizerT));

  if(tokenizer == NULL){
    return NULL;
  }

  tokenizer->delimiters = unescape_string(separators);
  tokenizer->copied_string = unescape_string(ts);
  tokenizer->current_position = tokenizer->copied_string;

  return tokenizer;
}


void TKDestroy(TokenizerT *tk) {
  free(tk->copied_string);
  free(tk->delimiters);
  free(tk);

  return;
}


char is_delimiter(char character, char* delimiters) {
  char* current;

  for(current = delimiters; current - delimiters < strlen(delimiters); current++) {
    if(character == *current) {
      return 1;
    }
  }

  return 0;
}


char *TKGetNextToken(TokenizerT *tk) {
  char* token = NULL;
  char* token_start = NULL;

  while(tk->current_position - tk->copied_string < strlen(tk->copied_string)) {
    if(!is_delimiter(*tk->current_position, tk->delimiters)) {

      token_start = tk->current_position;
      break;
    }
    tk->current_position++;
  }

  if(token_start == NULL) {
    return NULL;
  }

  while(tk->current_position - tk->copied_string < strlen(tk->copied_string)) {
    if(is_delimiter(*tk->current_position, tk->delimiters)) {
      break;
    }
    tk->current_position++;
  }

  token = malloc(sizeof(tk->current_position - token_start + 1));
  strncpy(token, token_start, tk->current_position - token_start);
  token[(tk->current_position - token_start)] = '\0';

  return token;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.


 int main(int argc, char **argv) {

 if(argc != 3){
 printf("Error: invalid number of arguments\n");
 return -1;
 }

 TokenizerT* tokenizer = TKCreate(argv[1], argv[2]);

 if(tokenizer == NULL) {
 printf("Error: unable to create tokenizer\n");
 }

 char* token = NULL;

 while((token = TKGetNextToken(tokenizer)) != NULL) {
 printf("%s\n", token);
 free(token);
 }

 TKDestroy(tokenizer);

 return 0;
 }
 */

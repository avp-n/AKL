#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "include/lexer.h"

lexer_T* init_lex(char* contents) {
  lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
  lexer->contents = contents;
  lexer->i = 0;
  lexer->c = contents[lexer->i];
}

void lex_adv(lexer_T* lexer) {
  if (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
    lexer->i += 1;
    lexer->c = lexer->contents[lexer->i];
  }
}

/*skip whitespace characters including newline*/
void lex_whitespace(lexer_T* lexer) {
  while (lexer->c == ' ' || lexer->c == 10) {
    lex_adv(lexer);
  }
}

token_T* lex_get_n_token(lexer_T* lexer) {
  while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
    if (lexer->c == ' ' || lexer->c == 10)
      lex_whitespace(lexer);

    if (isalnum(lexer->c))
      return lex_get_id(lexer);

    if (lexer->c == '"')
      return lex_get_str(lexer);

    switch (lexer->c) {
      case '+': return lex_adv_token(lexer,
				     init_token(TOKEN_ADD, lex_get_char_str(lexer))); break;
      case '-': return lex_adv_token(lexer,
				     init_token(TOKEN_SUB, lex_get_char_str(lexer))); break;
      case '*': return lex_adv_token(lexer,
				     init_token(TOKEN_MUL, lex_get_char_str(lexer))); break;
      case '/': return lex_adv_token(lexer,
				     init_token(TOKEN_DIV, lex_get_char_str(lexer))); break;
      case '^': return lex_adv_token(lexer,
				     init_token(TOKEN_POW, lex_get_char_str(lexer))); break;
      case '=': return lex_adv_token(lexer,
				     init_token(TOKEN_EQUALS, lex_get_char_str(lexer))); break;
      case '>': return lex_adv_token(lexer,
				     init_token(TOKEN_GTR, lex_get_char_str(lexer))); break;
      case '<': return lex_adv_token(lexer,
				     init_token(TOKEN_LESS, lex_get_char_str(lexer))); break;
      case ';': return lex_adv_token(lexer,
				     init_token(TOKEN_SEMI, lex_get_char_str(lexer))); break;
      case ':': return lex_adv_token(lexer,
				     init_token(TOKEN_COLON, lex_get_char_str(lexer))); break;
      case '?': return lex_adv_token(lexer,
				     init_token(TOKEN_IF, lex_get_char_str(lexer))); break;
      case ',': return lex_adv_token(lexer,
				     init_token(TOKEN_COMMA, lex_get_char_str(lexer))); break;
      case '|': return lex_adv_token(lexer,
				     init_token(TOKEN_PIPE, lex_get_char_str(lexer))); break;
      case '(': return lex_adv_token(lexer,
				     init_token(TOKEN_LPAREN, lex_get_char_str(lexer))); break;
      case ')': return lex_adv_token(lexer,
				     init_token(TOKEN_RPAREN, lex_get_char_str(lexer))); break;
      case '{': return lex_adv_token(lexer,
				     init_token(TOKEN_LBRACE, lex_get_char_str(lexer))); break;
      case '}': return lex_adv_token(lexer,
				     init_token(TOKEN_RBRACE, lex_get_char_str(lexer))); break;
    }
  }

  /*return init_token(TOKEN_EOF, "\0");*/
}

token_T* lex_get_str(lexer_T* lexer) {
  lex_adv(lexer);

  char* value = calloc(1, sizeof(char));
  value[0] = '\0';

  while (lexer->c != '"') {
    char* s = lex_get_char_str(lexer);
    value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
    strcat(value, s);

    lex_adv(lexer);
  }

  lex_adv(lexer);

  return init_token(TOKEN_STR, value);
}

token_T* lex_get_id(lexer_T* lexer) {
  char* value = calloc(1, sizeof(char));
  value[0] = '\0';

  while (isalnum(lexer->c)) {
    char* s = lex_get_char_str(lexer);
    value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
    strcat(value, s);

    lex_adv(lexer);
  }

  return init_token(TOKEN_ID, value);
}

token_T* lex_adv_token(lexer_T* lexer, token_T* token) {
  lex_adv(lexer);

  return token;
}

char* lex_get_char_str(lexer_T* lexer) {
  char* s = calloc(2, sizeof(char));
  s[0] = lexer->c;
  s[1] = '\0';

  return s;
}

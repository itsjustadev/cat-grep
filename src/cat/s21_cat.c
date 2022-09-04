#include "s21_cat.h"

int is_nnn(char symbol, char pre_symbol, char pre_pre_symbol, size_t counter_s);
int flags_parser(int argc, char *argv[], options_t *options);
void open_file(char *argv[], options_t options);
int string_num = 0;
int counter = 1;

int main(int argc, char *argv[]) {
  /* code */
  if (argc > 1) {
    options_t options = {0};

    for (; counter < argc; counter++) {
      if (argv[counter][0] == '-') {
        char arguments[1000] = "";
        for (size_t i = 0; i < strlen(argv[counter]); i++)
          arguments[i] = argv[counter][i + 1];
        for (size_t i = 1; i < (strlen(arguments) + 1); i++) {
          if (strspn(arguments, "benstvET") == strlen(argv[counter]) - 1) {
            flags_parser(argc, argv, &options);
          } else if (strcmp(arguments, "-number-nonblank") == 0) {
            options.b = 1;
          } else if (strcmp(arguments, "-number") == 0) {
            options.n = 1;
          } else if (strcmp(arguments, "-squeeze-blank") == 0) {
            options.s = 1;
          }
        }

      } else {
        if (argv[counter][0] == '-') {
          printf("arguments are not valid\n");
        }
        open_file(argv, options);
        exit(0);
      }
    }
  }

  return 0;
}

int is_nnn(char three, char two, char one, size_t counter) {
  return ((three == '\n' && two == '\n' && one == '\n') ||
          (counter == 2 && three == '\n' && two == '\n'))
             ? 0
             : 1;
}

int flags_parser(int argc, char *argv[], options_t *options) {
  int c;
  int value = 0;

  while ((c = getopt(argc, argv, "bnsETvet")) != -1) {
    switch (c) {
      case 'b':
        options->b = 1;
        break;

      case 'E':
        options->e = 1;
        options->v = 1;
        break;

      case 'n':
        options->n = 1;
        break;

      case 's':
        options->s = 1;
        break;

      case 'T':
        options->t = 1;
        options->v = 1;
        break;

      case 'v':
        options->v = 1;
        break;

      case 'e':
        options->e = 1;
        options->v = 1;
        break;

      case 't':
        options->t = 1;
        options->v = 1;
        break;

      case '?':
        value = -1;
        break;
    }
  }
  return value;
}

void open_file(char *argv[], options_t options) {  // open file;
  FILE *text = fopen(argv[counter], "r");
  char symbol = '\0';
  char symbol_new = ' ';
  char symbol_first = '\n';
  size_t counter = 0;
  if (options.b) options.n = 0;
  while (symbol != EOF) {
    symbol_new = fgetc(text);
    counter++;
    if (options.s && is_nnn(symbol_new, symbol, symbol_first, counter) == 0) {
    } else if (symbol_new != EOF) {
      if (options.n && (string_num == 0 || symbol == '\n')) {
        printf("%6d\t", ++string_num);
      }
      // if (options.n && symbol_new == '\n' && !options.b) {
      //   printf("%6d\t", ++string_num);
      //   continue;
      // }
      if ((options.b && symbol == '\n' && symbol_new != '\n') ||
          (options.b && counter == 1 && symbol_new != '\n')) {
        printf("%6d\t", ++string_num);
      }
      if (options.e && symbol_new == '\n') {
        printf("$");
      }

      if (options.t && symbol_new == '\t') {
        // printf("^I");
        printf("^%c", symbol_new + 64);
        symbol_first = symbol;
        symbol = symbol_new;
        continue;
      }

      if (options.v && symbol_new != 9 && symbol_new != 10 && symbol_new < 32) {
        printf("^%c", symbol_new + 64);
        symbol_first = symbol;
        symbol = symbol_new;
        continue;
      }
      if (options.v && symbol_new != 9 && symbol_new != 10 &&
          symbol_new > 126) {
        printf("^%c", symbol_new - 64);
        symbol_first = symbol;
        symbol = symbol_new;
        continue;
      }

      printf("%c", symbol_new);
    }

    symbol_first = symbol;
    symbol = symbol_new;
  }
  fclose(text);
  // open file
}

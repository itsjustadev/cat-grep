#include "./s21_grep.h"

void switchFlags(int argc, char *argv[], options_t *options);
void grep(char *argv[], options_t options);
void *to_lower(const char *str);
char pattern[512][512];
int n = 1;

int main(int argc, char *argv[]) {
  if (argc > 1) {
    options_t options = {0};
    switchFlags(argc, argv, &options);
    pattern[0][0] = n;
    pattern[0][1] = '\0';
    grep(argv, options);
    return 0;
  }
}

void grep(char *argv[], options_t options) {
  FILE *f;
  size_t l = 1;
  bool few_files = 0;
  if (options.e) l = 0;
  char *file_name = argv[optind + l];
  if (argv[optind + l + 1]) few_files = 1;

  while (file_name) {
    file_name = argv[optind + l];
    f = fopen(file_name, "r");

    if (f != NULL && argv[optind] != NULL) {
      int is_string_found = 0;
      int number_of_strings = 0;
      int index = 0;
      bool flag = 0;
      char s[1050];

      while (fgets(s, 1050, f)) {
        // fgets(s, 1050, f);
        number_of_strings++;
        if (options.e) {
          for (int i = 1; i < n; i++) {
            if (strstr(s, pattern[i])) flag = 1;
          }
        }
        if (flag && few_files) printf("%s:", file_name);
        if (flag) printf("%s", s);
        flag = 0;
        if (options.i) {
          char a[2048] = "";
          char b[2048] = "";
          char *temp = NULL;
          char *temp2 = NULL;
          if (argv[optind]) temp = to_lower(argv[optind]);
          temp2 = to_lower(s);
          if (temp) strcpy(b, temp);
          if (temp2) strcpy(a, temp2);

          if (temp) free(temp);
          if (temp2) free(temp2);

          if (strstr(a, b) && few_files) printf("%s:", file_name);
          if (strstr(a, b)) printf("%s", s);
        }
        if (optind == 1 && strstr(s, argv[optind])) {
          printf("%s", s);
        }
        if (options.v && !strstr(s, argv[optind])) {
          if (few_files) printf("%s:", file_name);
          printf("%s", s);
        }
        if (options.c && strstr(s, argv[optind])) {
          if (few_files) printf("%s:", file_name);
          index++;
        }

        if (options.n && strstr(s, argv[optind]))
          printf("%d:%s", number_of_strings, s);
        if (strstr(s, argv[optind])) is_string_found++;
        if (options.v && feof(f) && !strstr(s, argv[optind])) printf("\n");
        if (!options.v && feof(f) && strstr(s, argv[optind])) printf("\n");
        //
      }

      if (options.l && is_string_found) printf("%s\n", file_name);
      if (options.c) printf("%i\n", index);
      fclose(f);
    }
    l++;
  }
}

void *to_lower(const char *str) {
  /*
  Возвращает копию строки (str), преобразованной в нижний регистр.
  В случае какой-либо ошибки возвращает значение S21_NULL.
  */
  size_t size = strlen(str);
  char *fin = (char *)calloc(size + 1, sizeof(char));
  if (fin != NULL) {
    for (size_t i = 0; str[i] != 0; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        fin[i] = str[i] + ('a' - 'A');
      } else {
        fin[i] = str[i];
      }
    }
  }
  return fin;
}

void switchFlags(int argc, char *argv[], options_t *options) {
  int rez = 0;
  while ((rez = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (rez) {
      case 'e':
        options->e = 1;
        strcpy(pattern[n], optarg);
        // printf("found argument \"e = %s\".\n", optarg);
        // *optstr = optarg;
        // printf("%s", pattern[n]);
        n++;
        break;

      case 'i':
        options->i = 1;
        // printf("found argument \"i\".\n");
        break;

      case 'v':
        options->v = 1;
        // printf("found argument \"v\"\n");
        break;

      case 'c':
        options->c = 1;
        // printf("found argument \"c\"\n");
        break;

      case 'l':
        options->l = 1;
        // printf("found argument \"l\"\n");
        break;

      case 'n':
        options->n = 1;
        // printf("found argument \"n\"\n");
        break;

      case 'h':
        options->h = 1;
        // printf("found argument \"h\"\n");
        break;

      case 's':
        options->s = 1;
        // printf("found argument \"s\"\n");
        break;

      case 'f':
        options->f = 1;
        // printf("found argument \"f = %s\".\n", optarg);
        break;

      case 'o':
        options->o = 1;
        // printf("found argument \"o\"\n");
        break;

      case '?':
        // printf("Check your arguments broooou.\n"); c
        break;
    }
  }
}

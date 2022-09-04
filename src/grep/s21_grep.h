#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} options_t;

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#endif  //  SRC_GREP_S21_GREP_H_

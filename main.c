#include <stdlib.h>
#include <stdio.h>

#include "index.h"

int main(int argc, char **argv) {
  FILE *index_fp;
  ifile thing_to_be_indexed;


  if (argc != 3) {
    usage();
  }

  index_fp = fopen(argv[1], "r");

  fclose(index_fp);

  return 0;
}

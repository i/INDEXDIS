#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ftw.h>

#include "index.h"

int main(int argc, char **argv) {
  /*  struct dirent *ep;*/
  FILE *fp;
  /* char *fpath = malloc(129); */
  /*  char *buff;*/
  node trie = createTree();
  struct stat s;

  /* if (argc != 3) { */
  /* return usage(1); */
  /* } */

  stat(argv[1], &s);

  /* Is a file */
  if (S_ISREG(s.st_mode)) {
    /* is a file */
    fp = fopen(argv[1], "r");
    hangOrnaments(fp, trie);
  }

  else if (S_ISDIR(s.st_mode)) {
    /* TODO: */

  } 

  else {
    usage(2);
  }

  printTree(trie);
  destroyTree(trie);
  return 0;
}

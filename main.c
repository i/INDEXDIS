#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <ftw.h>

#include "tokenizer.h"
#include "index.h"

int main(int argc, char **argv) {
/*  struct dirent *ep;*/
  FILE *fp;
/*  char *path = malloc(128);*/
  char *buff;
  node trie = createTree();
/*  TokenizerT *tok;*/

/*  if (argc != 3) {*/
/*    return usage();*/
/*  }*/


  /* Try opening as a file first. */
  if ((fp = fopen(argv[1], "r"))) {
    buff = calloc(1, 256);
    while(fscanf(fp, "%s\n", buff) != EOF) {
      addToTree(buff, trie);
    }
    free(buff);
    fclose(fp);
  }

  printTree(trie);
  destroyTree(trie);
  return 0;
}

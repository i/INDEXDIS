#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "tokenizer.h"
#include "index.h"

int main(int argc, char **argv) {
/*  struct dirent *ep;*/
/*  DIR *dp;*/
/*  FILE *fp;*/
/*  char *path = malloc(128);*/
/*  char *buff, *s;*/
  node trie = createTree();
/*  TokenizerT *tok;*/

/*  if (argc != 3) {*/
/*    return usage();*/
/*  }*/

  /* Try opening as a file first. */
/*  if ((fp = fopen(argv[1], "r"))) {*/
/*    buff = malloc(256);*/
/*    while(fscanf(fp, "%s\n", buff) != EOF) {*/
/*      tok = TKCreate(" ", buff);*/
/*      while ((s = TKGetNextToken(tok))) {*/
/*        addToTree(s, trie);*/
/*      }*/
/*    }*/
/*    fclose(fp);*/
/*  }*/

  /* If it wasn't a file, hopefully it's a directory. */
/*  else if ((dp = opendir(argv[1]))) {*/
/**/
/*  }*/
/**/
  /* If it was neither, we can't open it. */
/*  else {*/
/*    perror ("Couldn't open the directory");*/
/*    free(path);*/
/*    return 1;*/
/*  }*/

  char * buff;
  char foo[] = "FOO";
  char testicle[] = "balls";

  addToTree(foo, trie);
  addToTree(testicle, trie);


  buff = malloc(trie->height);
  printTree(trie, buff);
  destroyTree(trie);

  free(buff);
  return 0;
}

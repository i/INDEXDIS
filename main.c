#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#include "tokenizer.h"
#include "index.h"

int main(int argc, char **argv) {
/*  DIR *dp;*/
/*  FILE *fp;*/
/*  struct dirent *ep;*/
/*  TokenizerT tokenizer;*/

  node trie = createTree();
  char *buff;

  /*
  if (argc != 3) {
    return usage();
  }
  */

/*  if (fp = fopen(argv[1], "r")) {*/
/*    */
/*  }*/
/**/
/**/
/*  if ((dp = opendir(argv[1]))) {*/
/*    while ((ep = readdir (dp)))*/
/*      puts (ep->d_name);*/
/**/
/*    closedir (dp);*/
/*  }*/
/**/
/**/
/*  else*/
/*    perror ("Couldn't open the directory");*/
/**/


  addToTree("cat", trie);
  buff = malloc(trie->height);
  printTree(trie, buff);

  return 0;
}

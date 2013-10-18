#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ftw.h>

#include "index.h"

int menorahTime(const char *name, const struct stat *status, int type);

lnode FILES = NULL;

int main(int argc, char **argv) {
  /*  struct dirent *ep;*/
  FILE *fp;
  /* char *fpath = malloc(129); */
  /*  char *buff;*/
  tnode trie = createTree();
  struct stat s;
  lnode ptr;

  /* if (argc != 3) { */
  /* return usage(1); */
  /* } */

  stat(argv[1], &s);

  /* Is a file */
  if (S_ISREG(s.st_mode)) {
    fp = fopen(argv[1], "r");
    hangOrnaments(fp, trie, argv[1]);
  }

  else if (S_ISDIR(s.st_mode)) {
    /* TODO: */
    ftw(argv[1], menorahTime, 7);
    ptr = FILES->next;

    while (ptr->next != NULL) {
      fp = fopen(ptr->filename, "r");
      hangOrnaments(fp, trie, ptr->filename);
      ptr = ptr->next;
    }
  } 

  else {
    usage(2);
  }

  printTree(trie);
  destroyTree(trie);
  return 0;
}

int menorahTime(const char *name, const struct stat *status, int type) {
  lnode ptr;

  if (FILES == NULL) {
    FILES = create_lnode(strstr((char *)name, ""));
  } else {
    ptr = create_lnode(strstr((char *)name, ""));
    ptr->next = FILES;
    FILES = ptr;
  }
  return 0;
}

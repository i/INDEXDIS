#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ftw.h>

#include "index.h"

int main(int argc, char **argv) {
  FILE *rf; /*  write file, read file*/
  struct stat s;

  tnode trie = createTree();
  lnode ptr;

  /* if (argc != 3) { */
  /* return usage(1); */
  /* } */

  stat(argv[1], &s);

  /* Is a file */
  if (S_ISREG(s.st_mode)) {
    rf = fopen(argv[1], "r");
    hangOrnaments(rf, trie, argv[1]);
    fclose(rf);
  }

  else if (S_ISDIR(s.st_mode)) {
    /* TODO: */
    ftw(argv[1], menorahTime, 7);
    ptr = FILES;

    while (ptr->next != NULL) {
      rf = fopen(ptr->filename, "r");
      hangOrnaments(rf, trie, ptr->filename);
      fclose(rf);
      ptr = ptr->next;
    }
  }

  else {
    usage(2);
  }

  printTree(trie);
  destroyTree(trie);
  destroy_list(FILES);

  return 0;
}

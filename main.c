#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ftw.h>

#include "index.h"

int main(int argc, char **argv) {
  FILE *rf; /* read file */
  FILE *wf; /* write file */
  struct stat s;
  char overwrite;

  tnode trie = createTree();
  lnode ptr;

  if (argc != 3) {
    return usage(1);
  }

  /* Check if file exists */
  if (access(argv[1], F_OK) != -1) {
    while (overwrite != 'y' && overwrite != 'n') {
      printf("Output file already exists. Overwrite? (y/n)\n");
      overwrite = getc(stdin);
      if (overwrite == 'n') {
        return 1;
      } 
    }
  }

  wf = fopen(argv[1], "w");

  stat(argv[2], &s);

  /* Is a file */
  if (S_ISREG(s.st_mode)) {
    rf = fopen(argv[2], "r");
    hangOrnaments(rf, trie, argv[2]);
    fclose(rf);
  }

  /* Is a dir */
  else if (S_ISDIR(s.st_mode)) {
    ftw(argv[2], menorahTime, 7);
    ptr = FILES;

    while (ptr->next != NULL) {
      rf = fopen(ptr->filename, "r");
      hangOrnaments(rf, trie, ptr->filename);
      fclose(rf);
      ptr = ptr->next;
    }
  }

  /* Does not exist or is bad */
  else {
    usage(2);
  }

  printTree(trie, wf);
  fclose(wf);
  destroyTree(trie);
  destroy_list(FILES);

  return 0;
}

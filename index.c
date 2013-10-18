#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "index.h"

tnode create_tnode() {
  tnode new = calloc(1, sizeof(struct tnode_));
  new->count = 0;
  new->height = 0;
  new->files = NULL;

  return new;
}


lnode create_lnode(char *filename) {
  lnode new = malloc(sizeof(struct lnode_));
  strcpy(new->filename, filename);
  new->count = 0;

  return new;
}

tnode createTree() {
  tnode root = create_tnode();
  root->count = -1;
  root->files = NULL;
  root->height = 0;
  return root;
}

void destroyTree(tnode root) {
  int i;

  for (i = 0; i < 36; i++) {
    if (root->alphabet[i]) {
      destroyTree(root->alphabet[i]);
    }
  }

  free(root);
}

void addToTree(char *word, tnode root, char *filename) {
  int height = strlen(word);
  lnode p;
  lowerString(word);

  /* Check if this is longest word */
  if (height > root->height)
    root->height = height;

  /* We are given the empty string, meaning the whole word
     should be in the tree by now and we should mark the tnode. */
  if (strcmp(word, "") == 0) {
    if (root->count == -1) {
      /* We should not get here */
      printf("Sending empty string to root. YOU CRAZY\n");
      return;
    }
    root->count++;
    if (root->files == NULL) {
      root->files = create_lnode(filename);
    } else {
      for (p = root->files; p != NULL; p = p->next) {
        if (strcmp(p->filename, filename) == 0) {
          p->count++;
          return;
        } else if (p->next == NULL) {
          p->next = create_lnode(filename);
          return;
        }
      }
    }

    return;
  }

  /* We do not have a tnode for the character
   * and need to make one here. */
  if (root->alphabet[getIndex(*word)] == 0)
    root->alphabet[getIndex(*word)] = create_tnode();

  addToTree(word + 1, root->alphabet[getIndex(*word)], filename);
}


void pt(tnode root, char *buff) {
  int i;

  if (root->count > 0)
    printf("%s : %d\n", buff, root->count);

  for (i = 0; i < 36; i++) {
    if (root->alphabet[i]) {
      buff[strlen(buff)] = getChar(i);
      buff[strlen(buff)] = 0;
      pt(root->alphabet[i], buff);
      buff[strlen(buff) - 1] = 0;
    }
  }
}

void printTree(tnode root) {
  char *buff = calloc(1, root->height);
  pt(root, buff);
  free(buff);
}


void hangOrnaments(FILE *fp, tnode trie, char *filename) {
  char *buff = calloc(1, 256);
  while (fscanf(fp, "%255[a-zA-Z0-9]", buff) == 1) {
    addToTree(buff, trie, filename);
    fscanf(fp, "%255[^a-zA-Z0-9]", buff);
  }
  free(buff);
}

/*
 * Converts the letter to an index of our array
 */
int getIndex(int c) {
  if (isdigit(c))
    return c - (int)'0';
  return c - (int)'a' + 10;
}

char getChar(int i) {
  if (i >= 0 && i < 10)
    return i + '0';

  if (i >= 10 && i < 36)
    return i + 'a' - 10;

  return 0;
}

void lowerString(char *s) {
  for(; *s; ++s) {
    if (isalpha(*s))
      *s = tolower(*s);
  }
}

int usage(int i) {
  switch(i) {
    case 1:
      printf("Use it like disssssss\n");
      break;
    case 2:
      printf("INVALID FILE NAME\n");
      break;
    default:
      printf("fuck!\n");
  }

  return 1;
}

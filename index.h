#ifndef INDEX_H
#define INDEX_H

struct lnode_ {
  char filename[256];
  int count;
  struct lnode_ *next;
};

typedef struct lnode_ *lnode;

/*Creates a new node with a string as its argument*/
lnode create_lnode(char *);

/*
 * Trie node structure. Represents a single character
 */
struct tnode_ {
  struct tnode_ *alphabet[36];
  int height;
  int count;
  lnode files;
};

typedef struct tnode_ *tnode;

/*
 *  Creates a new trie node.
 *  Takes no arguments.
 */
tnode create_tnode();


/*
 * Creates a new tree.
 */
tnode createTree();

/*
 * Recursively adds a word to the tree.
 */
void addToTree(char *, tnode, char *);

/*
 * Recursively destroys prefix tree.
 */
void destroyTree(tnode);

/*
 * Recursive part of printTree 
 */
void pt(tnode, char *);

/*
 * Print dat tree.
 */
void printTree(tnode);

/*
 * Adds every word in a file to a tire
 */
void hangOrnaments(FILE *, tnode, char *);

/*
 *  Gets index for char.
 */
int getIndex(int);

/*
 * Gets char for index.
 */
char getChar(int);

/*
 * Makes a string lowercase.
 */
void lowerString(char *);

/*
 *  Prints usage information and returns error code.
 */
int usage(int);

#endif

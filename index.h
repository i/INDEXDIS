#ifndef INDEX_H
#define INDEX_H



struct node_ {
  struct node_ **alphabet;
  int count;
  int height;
};

typedef struct node_ *node;

/*
 *  Creates a new node.
 *  Takes no arguments.
 */
node create_node();

node createTree();

/*
 * Adds a word to the tree.
 */
void addToTree(char *, node);


/*
 * Print dat tree.
 */
void printTree(node, char*);

/*
 *  Prints usage information and returns error code.
 */
int usage();

/*
 *  Gets index for char.
 */
int getIndex(int);

/*
 * Gets char for index.
 */
char getChar(int);

#endif

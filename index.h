#ifndef INDEX_H
#define INDEX_H



struct node_ {
  struct node_ *alphabet[36];
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
 * Recursively adds a word to the tree.
 */
void addToTree(char *, node);


/*
 * Recursively destroys prefix tree.
 */
void destroyTree(node);

/*
 * Recursive part of printTree 
 */
void pt(node, char *);


/*
 * Print dat tree.
 */
void printTree(node);

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
int usage();

#endif

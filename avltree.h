#ifndef AVLTREE_H_
#define AVLTREE_H_

#define MAX_INFO_LENGTH 200

//This header file defines all of the functions associated with the AVL tree

typedef struct entry{
  char titleOrig[MAX_INFO_LENGTH];
  char title[MAX_INFO_LENGTH];
  char titleMod[MAX_INFO_LENGTH];
  char releaseDate[MAX_INFO_LENGTH];
  char acquireDate[MAX_INFO_LENGTH];
  char mediaType[MAX_INFO_LENGTH];
  char genres[MAX_INFO_LENGTH];
  char runtimeMinutes[MAX_INFO_LENGTH];
} entry;


typedef struct node {
  struct entry movieInfo;
  struct node*  left;
  struct node*  right;
  int height;
} node;


void dispose(node* t);
entry find( char* search, node *t );
node* findNode(char* search, node *t);
node* returnExactNode(node* t, entry movie);
node* insert( struct entry movieEntry, node *t );
node* delete(node* library, entry movieToDelete );
void displayMatches(entry *matches, int* counter, node* t, char* query);
node* minItem(node* tree);
void printTree(node* library);
void printMovie(entry movie);
void copyMovie(entry* dest, entry src);

#endif

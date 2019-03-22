#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "avltree.h"

typedef struct entry{
  char garbage[15];
  char movie[10];
  char titleOrig[100];
  char title[100];
  char isAdult[2];
  char releaseDate[15];
  char endDate[15];
  char acquireDate[15];
  char mediaType[15];
  char genres[50];
  char runtimeMinutes[10];
} entry;

typedef struct node
{
  char title[150];
  char titleOrig[150];
  char releaseDate[15];
  char genres[50];
  char runtimeMinutes[10];
  struct node*  left;
  struct node*  right;
  int height;
} node;


void dispose(node* t);
struct entry find( char* search, node *t );
node* insert( struct entry movieEntry, node *t );
node* delete( int data, node *t );
void display_avl(node* t);

/*
    remove all nodes of an AVL tree
*/
void dispose(node* t)
{
  if( t != NULL )
    {
      dispose( t->left );
      dispose( t->right );
      free( t );
    }
}

/*
    find a specific node's key in the tree
*/

struct entry find(char* query, node* t )
{
  struct entry movie = {0};
  if( t == NULL )
    return movie;
  if( strcmp(query, t->title) < 0)//e < t->data )
    return find( query, t->left );
  else if( strcmp(query, t->title) > 0)//e > t->data )
    return find( query, t->right );
  else{
    strcpy(movie.title, t->title);
    strcpy(movie.titleOrig, t->titleOrig);
    strcpy(movie.releaseDate, t->releaseDate);
    strcpy(movie.runtimeMinutes, t->runtimeMinutes);
    strcpy(movie.genres, t->genres);
    return movie;
  }
}


/*
    get the height of a node
*/
static int height( node* n )
{
  if( n == NULL )
    return -1;
  else
    return n->height;
}

/*
    get maximum value of two integers
*/
static int max( int l, int r)
{
  return l > r ? l: r;
}

/*
    perform a rotation between a k2 node and its left child
 
    note: call single_rotate_with_left only if k2 node has a left child
*/

static node* single_rotate_with_left( node* k2 )
{
  node* k1 = NULL;

  k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;

  k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
  k1->height = max( height( k1->left ), k2->height ) + 1;
  return k1; /* new root */
}

/*
    perform a rotation between a node (k1) and its right child
 
    note: call single_rotate_with_right only if
    the k1 node has a right child
*/

static node* single_rotate_with_right( node* k1 )
{
  node* k2;

  k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;

  k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
  k2->height = max( height( k2->right ), k1->height ) + 1;

  return k2;  /* New root */
}

/*
 
    perform the left-right double rotation,
 
    note: call double_rotate_with_left only if k3 node has
    a left child and k3's left child has a right child
*/

static node* double_rotate_with_left( node* k3 )
{
  /* Rotate between k1 and k2 */
  k3->left = single_rotate_with_right( k3->left );

  /* Rotate between K3 and k2 */
  return single_rotate_with_left( k3 );
}

/*
    perform the right-left double rotation
 
   notes: call double_rotate_with_right only if k1 has a
   right child and k1's right child has a left child
*/



static node* double_rotate_with_right( node* k1 )
{
  /* rotate between K3 and k2 */
  k1->right = single_rotate_with_left( k1->right );

  /* rotate between k1 and k2 */
  return single_rotate_with_right( k1 );
}

/*
    insert a new node into the tree
*/
node* insert(struct entry movie/*int e*/, node* t)
{
  if( t == NULL )
    {
      /* Create and return a one-node tree */
      t = (node*)malloc(sizeof(node));
      if( t == NULL )
	{
	  fprintf (stderr, "Out of memory!!! (insert)\n");
	  exit(1);
	}
      else
	{
	  //t->title = e;
	  strcpy(t->title, movie.title);
	  strcpy(t->titleOrig, movie.titleOrig);
	  strcpy(t->releaseDate, movie.releaseDate);
	  strcpy(t->runtimeMinutes, movie.runtimeMinutes);
	  strcpy(t->genres, movie.genres);
	  t->height = 0;
	  t->left = t->right = NULL;
	}
    }
  else if( strcmp(movie.title, t->title)<0)//e < t->data )
    {
      t->left = insert(movie, t->left );
      if(height(t->left)-height(t->right) == 2){
	if( strcmp(movie.title, t->left->title) < 0)//e < t->left->data )
	  t = single_rotate_with_left( t );
	else
	  t = double_rotate_with_left( t );
      }
    }
  else if( strcmp(movie.title, t->title) > 0)//e > t->data )
    {
      t->right = insert(movie, t->right );
      if(height(t->right)-height(t->left) == 2){
	if( strcmp(movie.title, t->right->title) > 0)//e > t->right->data )
	  t = single_rotate_with_right( t );
	else
	  t = double_rotate_with_right( t );
      }
    }
  /* Else X is in the tree already; we'll do nothing */

  t->height = max( height( t->left ), height( t->right ) ) + 1;
  return t;
}

/*
    remove a node in the tree
*/
node* delete( int e, node* t )
{
  printf( "Sorry; Delete is unimplemented; %d remains\n", e );
  return t;
}

void display_avl(node* t)
{
  if (t == NULL)
    return;
  printf("%s",t->title);

  if(t->left != NULL)
    printf("(L:%s)",t->left->title);
  if(t->right != NULL)
    printf("(R:%s)",t->right->title);
  printf("\n");

  display_avl(t->left);
  display_avl(t->right);
}

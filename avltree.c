
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "avltree.h"

void dispose(struct node* t)
{
  if( t != NULL )
    {
      dispose( t->left );
      dispose( t->right );
      free( t );
    }
}


entry find(char* query, struct node* t )
{
  struct entry movie = {0};
  if( t == NULL ){
    printf("Could not find any matches. Please edit or refine your search: ");
    return movie;
  }
  
  if( strncmp(query, t->movieInfo.titleMod, strlen(query)) < 0)
    return find( query, t->left );
  else if( strncmp(query, t->movieInfo.titleMod, strlen(query)) > 0)
    return find( query, t->right );
  else{
    int counter = 1;
    int *cnt = &counter;
    struct entry matches[30];
    printf("\n---SEARCH RESULTS---\n\n");
    displayMatches(matches, cnt, t, query);
    printf("\n---FINISH SEARCH RESULTS---\n\n");
    printf("Please enter the number of the movie you'd like to add to your library (or '0' to search again): ");
    int choice;
    scanf("%d", &choice);
    getchar();
    if (choice == 0){
      printf("\nPlease search the name of the movie you would like to add to your library (or '!' to quit): ");
      return movie;
    }else if (choice < 0 || choice > counter){
      printf("Sorry, that was not a valid option. Exiting command.\n\n");
      return movie;
    }
    return matches[choice - 1];
  }
}


node* findNode(char* query, struct node* t )
{

  //struct node* temp = NULL;
  struct node* temp = {0};
  if( t == NULL ){
    printf("Could not find any matches\n");
    return temp;
  }
  
  if( strncmp(query, t->movieInfo.titleMod, strlen(query)) < 0)
    return findNode( query, t->left );
  else if( strncmp(query, t->movieInfo.titleMod, strlen(query)) > 0)
    return findNode( query, t->right );
  else if( (strcmp(query, t->movieInfo.titleMod) == 0  && (strlen(query) == strlen(t->movieInfo.titleMod)))){
    return t;
  }else{
    int counter = 1;
    int *cnt = &counter;
    //struct entry *movie = {0};
    struct entry matches[30];
    printf("\n---SEARCH RESULTS---\n\n");
    displayMatches(matches, cnt, t, query);
    printf("\n---FINISH SEARCH RESULTS---\n\n");
    printf("Please enter the number of the movie you'd like to add to your library (or '0' to search again): ");
    int choice;
    scanf("%d", &choice);
    getchar();
    if (choice == 0){
      printf("\nPlease search the name of the movie you would like to add to your library (or '!' to quit): ");
      return NULL;
    } else if (choice > 30){
      printf("Sorry, that was not a valid option. Exiting command.\n\n");
      return NULL;
    }
    return returnExactNode(t, matches[choice - 1]);
  }
}

node* returnExactNode(struct node* t, struct entry exactMovie){
  if( t == NULL ){
    printf("Could not find any matches. Please edit or refine your search: \n");
    return t;
  }
  
  if( strncmp(exactMovie.titleMod, t->movieInfo.titleMod, strlen(exactMovie.titleMod)) < 0)//e < t->data )
    return returnExactNode( t->left, exactMovie );
  else if( strncmp(exactMovie.titleMod, t->movieInfo.titleMod, strlen(exactMovie.titleMod)) > 0)//e > t->data )
    return returnExactNode( t->right, exactMovie );
  else if( (strcmp(exactMovie.titleMod, t->movieInfo.titleMod) == 0  && (strlen(exactMovie.titleMod) == strlen(t->movieInfo.titleMod)))){
    return t;
  } 
  return t;
}


/*
    get the height of a node
*/
static int height( struct node* n )
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

  return k2;
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


//Insert a new node into the tree
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
	  copyMovie(&t->movieInfo, movie);
	  t->height = 0;
	  t->left = t->right = NULL;
	}
    }
  else if( strcmp(movie.titleMod, t->movieInfo.titleMod)<0)//e < t->data )
    {
      t->left = insert(movie, t->left );
      if(height(t->left)-height(t->right) == 2){
	if( strcmp(movie.titleMod, t->left->movieInfo.titleMod) < 0)//e < t->left->data )
	  t = single_rotate_with_left( t );
	else
	  t = double_rotate_with_left( t );
      }
    }
  else if( strcmp(movie.titleMod, t->movieInfo.titleMod) > 0)//e > t->data )
    {
      t->right = insert(movie, t->right );
      if(height(t->right)-height(t->left) == 2){
	if( strcmp(movie.titleMod, t->right->movieInfo.titleMod) > 0)//e > t->right->data )
	  t = single_rotate_with_right( t );
	else
	  t = double_rotate_with_right( t );
      }
    }
  /* Else X is in the tree already; we'll do nothing */

  t->height = max( height( t->left ), height( t->right ) ) + 1;
  return t;
}


void displayMatches(entry *matches, int *count, node* t, char *query)
{
  static bool max = false;
  if (*count == 31){
    return;
  }
  
  if (t == NULL)
    return;

  if (strstr(t->movieInfo.titleMod, query) != NULL){
    if (strcmp(t->movieInfo.titleOrig, t->movieInfo.title) != 0)
      printf("%d) %s (%s)\t[%s]\n", *count, t->movieInfo.title, t->movieInfo.titleOrig, t->movieInfo.releaseDate);
    else
      printf("%d) %s\t[%s]\n", *count, t->movieInfo.title, t->movieInfo.releaseDate);
    matches[*count-1] = t->movieInfo;
    (*count)++;
     if (*count == 31)
       max = true;
  }
  
  displayMatches(matches, count, t->left, query);
  displayMatches(matches, count, t->right, query);

  if (max == true){
    printf("\n\nThere are more than 30 results! If you don't see the movie you want, enter '0' and then please refine your search.\n\n");
    max = false;
  }
  
}
void displayTree(node* t){

  if (t == NULL)
    return;
  printf("%s",t->movieInfo.title);

  displayTree(t->left);
  displayTree(t->right);
}


void printTree(node *library){
  if (library == NULL){
    return;
  }
 
  printMovie(library->movieInfo);
  printTree(library->left);
  printTree(library->right);
}

void printMovie(entry movie){
  printf("\nTitle: %s\n\tRelease Date: %s\n\tRuntime (m): %s\n\tMedia Type: %s\n\tDate Acquired: %s\n\tGenres: %s\n\n", movie.title, movie.releaseDate, movie.runtimeMinutes, movie.mediaType, movie.acquireDate, movie.genres);
  return;
}


node* delete(node *library, struct entry movieToDelete)
{
    if(library == NULL)
        return library;
    if(strcmp(movieToDelete.titleMod, library->movieInfo.titleMod) < 0)
        library->left = delete(library->left, movieToDelete);
    else
      if(strcmp(movieToDelete.titleMod, library->movieInfo.titleMod) > 0)
            library->right = delete(library->right, movieToDelete);
      else{  
	node *tmp = library;
	if ((library->left) && (library->right))
	  {
	    node *parent = library->right;
	    library = parent->left;
	    if (library)
	      {
		while(library->left)
		  {
		    parent = library;
		    library = library->left;
		  }
		parent->left = library->right;
		library->right = tmp->right;
	      }
	    else
	      library = parent;
	    library->left = tmp->left;
	  }
	else
	  if(library->left)
	    library = library->left;
	  else
	    library = library->right;
	free(tmp);
      }
    return library;   
}



node* minItem(node* tree){

  if (tree->left)
    tree = tree->left;
  
  return tree;
}

void copyMovie(struct entry *dest, struct entry src){
  strncpy(dest->title, src.title, sizeof(dest->title));
  strncpy(dest->titleOrig, src.titleOrig, sizeof(dest->titleOrig));
  strncpy(dest->titleMod, src.titleMod, sizeof(dest->titleMod));
  strncpy(dest->releaseDate, src.releaseDate, sizeof(dest->releaseDate));
  strncpy(dest->runtimeMinutes, src.runtimeMinutes, sizeof(dest->runtimeMinutes));
  strncpy(dest->genres, src.genres, sizeof(dest->genres));
  //USER INFO
  strncpy(dest->acquireDate, src.acquireDate, sizeof(dest->acquireDate));
  strncpy(dest->mediaType, src.mediaType, sizeof(dest->mediaType));
  return;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "avltree.h"


//This recursive functions searches through the AVL tree to find the title (query) entered by the user
//It returns the entry containing the movie's information
entry find(char* query, struct node* t )
{
  
  //Create an initially null movie entry to edit/return
  struct entry movie = {0};

  //If we reach the end of the AVL tree without finding a match, return null and let the user know that it couldn't find anything
  if( t == NULL ){
    printf("Could not find any matches!");
    return movie;
  }

  //If the query is lower, alphabetically, than the current node's titleMod, recurse left
  if( strncmp(query, t->movieInfo.titleMod, strlen(query)) < 0)
    return find( query, t->left );
  //Else, if the query is greater, alphabetically, than the current node's titleMod, recurse right
  else if( strncmp(query, t->movieInfo.titleMod, strlen(query)) > 0)
    return find( query, t->right );
  else{
    //Create an array to contain up to 30 partial matches
    int counter = 1;
    int *cnt = &counter;
    struct entry matches[30];

    //Print up to 30 partial matches
    printf("\n---SEARCH RESULTS---\n\n");
    displayMatches(matches, cnt, t, query);
    printf("\n---FINISH SEARCH RESULTS---\n\n");

    //Let the user know they can select a displayed item
    printf("Please enter the number of the movie you'd like to add to your library (or '!' to quit): ");

    //Get the numbered option that the user selected
    int choice;
    scanf("%d", &choice);
    getchar();

    //If they selected '0' or '!', exit
    if (choice == '!'){
      return movie;
      //Else if they selected something outside the bounds of the matches array, let them know their input was invalid  
    }else if (choice <= 0 || choice > counter){
      printf("\nSorry, that was not a valid option. Exiting command.");
      return movie;
    }
    //If neither of these conditions were met, return the chosen item from the matches array
    return matches[choice - 1];
  }
}


//This recursive functions searches through the AVL tree to find the title (query) entered by the user.
//It returns the AVL node containing the movie entry.
node* findNode(char* query, struct node* t )
{

  //Create an initially null AVL node to edit/return
  struct node* temp = {0};

  //If we reach the end of the AVL tree without finding a match, return null and let the user know that it couldn't find anything
  if( t == NULL ){
    printf("Could not find any matches!");
    return temp;
  }

  //If the query is lower, alphabetically, than the current node's titleMod, recurse left
  if( strncmp(query, t->movieInfo.titleMod, strlen(query)) < 0)
    return findNode( query, t->left );
  //Else, if the query is greater, alphabetically, than the current node's titleMod, recurse right
  else if( strncmp(query, t->movieInfo.titleMod, strlen(query)) > 0)
    return findNode( query, t->right );
  else{
    //Create an array to contain up to 30 partial matches
    int counter = 1;
    int *cnt = &counter;
    struct entry matches[30];

    //Print up to 30 partial matches
    printf("\n---SEARCH RESULTS---\n\n");
    displayMatches(matches, cnt, t, query);
    printf("\n---FINISH SEARCH RESULTS---\n\n");

    //Let the user know they can select a displayed item
    printf("Please enter the number of the movie you'd like to add to your library (or '!' to quit): ");

    //Get the numbered option that the user selected
    int choice;
    scanf("%d", &choice);
    getchar();

    //If they selected '0' or '!', exit
    if (choice == '!'){
      return NULL;
      //Else if they selected something outside the bounds of the matches array, let them know their input was invalid  
    } else if (choice <= 0 || choice > counter){
      printf("\nSorry, that was not a valid option. Exiting command.");
      return NULL;
    }
    //If neither of these conditions were met, return the exact node of the chosen item from the matches array
    return returnExactNode(t, matches[choice - 1]);
  }
}

//This function returns an AVL node when given an exact title match
//This is only called once the exact information of the node has been selected in the findNode function
node* returnExactNode(struct node* t, struct entry exactMovie){

  //If we reach the end of the AVL tree without finding a match, return null and let the user know that it couldn't find anything
  if( t == NULL ){
    printf("Could not find any matches. Please edit or refine your search: \n");
    return t;
  }

  //If the query is lower, alphabetically, than the current node's titleMod, recurse left
  if( strncmp(exactMovie.titleMod, t->movieInfo.titleMod, strlen(exactMovie.titleMod)) < 0)
    return returnExactNode( t->left, exactMovie );
  //Else, if the query is greater, alphabetically, than the current node's titleMod, recurse right
  else if( strncmp(exactMovie.titleMod, t->movieInfo.titleMod, strlen(exactMovie.titleMod)) > 0)
    return returnExactNode( t->right, exactMovie );
  //Once it finds an exact match, return the node
  else if( (strcmp(exactMovie.titleMod, t->movieInfo.titleMod) == 0  && (strlen(exactMovie.titleMod) == strlen(t->movieInfo.titleMod)))){
    return t;
  } 
  return t;
}


//This (borrowed) function gets the height of the node in the AVL tree
static int height( struct node* n )
{
  if( n == NULL )
    return -1;
  else
    return n->height;
}

//This function returns the max of two integers
static int max( int l, int r)
{
  return l > r ? l: r;
}


//This (borrowed) function performs a single left rotation within the AVL tree to balance itself
static node* single_rotate_with_left( node* k2 )
{
  node* k1 = NULL;

  k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  
  k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
  k1->height = max( height( k1->left ), k2->height ) + 1;
  return k1; 
}


//This (borrowed) function performs a single right rotation within the AVL tree to balance itself
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


//This (borrowed) function performs a double left rotation within the AVL tree to balance itself
static node* double_rotate_with_left( node* k3 )
{
  k3->left = single_rotate_with_right( k3->left );
  return single_rotate_with_left( k3 );
}


//This (borrowed) function performs a double right rotation within the AVL tree to balance itself
static node* double_rotate_with_right( node* k1 )
{
  k1->right = single_rotate_with_left( k1->right );
  return single_rotate_with_right( k1 );
}


//This (heavily modified to suit this program, but still borrowed) function inserts a movie entry into a new node in the AVL tree
node* insert(struct entry movie, node* t)
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
	  //Once we find a new node, copy the movie entry information into the node
	  copyMovie(&t->movieInfo, movie);
	  t->height = 0;
	  t->left = t->right = NULL;
	}
    }
  else if( strcmp(movie.titleMod, t->movieInfo.titleMod)<0)
    {
      t->left = insert(movie, t->left );
      if(height(t->left)-height(t->right) == 2){
	if( strcmp(movie.titleMod, t->left->movieInfo.titleMod) < 0)
	  t = single_rotate_with_left( t );
	else
	  t = double_rotate_with_left( t );
      }
    }
  else if( strcmp(movie.titleMod, t->movieInfo.titleMod) > 0)
    {
      t->right = insert(movie, t->right );
      if(height(t->right)-height(t->left) == 2){
	if( strcmp(movie.titleMod, t->right->movieInfo.titleMod) > 0)
	  t = single_rotate_with_right( t );
	else
	  t = double_rotate_with_right( t );
      }
    }
  //Else X is in the tree already; we'll do nothing
  t->height = max( height( t->left ), height( t->right ) ) + 1;
  return t;
}

//This recursive function displays all of the partial (or exact) matches of a query found in the tree
void displayMatches(entry *matches, int *count, node* t, char *query)
{
  //Create flag to help limit the displayed results to 30
  static bool max = false;

  //Don't continue working if we reach the max count
  if (*count == 31)
    return;
  

  //Return when we reach the end of the tree 
  if (t == NULL)
    return;

  //Only display the numbered movie if it is a substring of the modified title in the AVL node
  if (strstr(t->movieInfo.titleMod, query) != NULL){

    //Display both the original title and the primary title, if they're different
    if (strcmp(t->movieInfo.titleOrig, t->movieInfo.title) != 0)
      printf("%d) %s (%s)\t[%s]\n", *count, t->movieInfo.title, t->movieInfo.titleOrig, t->movieInfo.releaseDate);
    //Else, just display the primary title
    else
      printf("%d) %s\t[%s]\n", *count, t->movieInfo.title, t->movieInfo.releaseDate);

    //Insert the current movie into the matches array
    matches[*count-1] = t->movieInfo;

    //Increment the counter to keep track of indexing for the array
    (*count)++;

    //If we reach 31 movies, set the flag indicating that we hit the max we can insert
    if (*count == 31)
      max = true;
  }

  //Keep recursing down from the node we started at
  displayMatches(matches, count, t->left, query);
  displayMatches(matches, count, t->right, query);

  //If we hit our max, notify the user
  if (max == true){
    printf("\n\nThere are more than 30 results! If you don't see the movie you want, please enter '!' and try again with a more specific search!\n\n");
    max = false;
  }
  
}


//This function recursively prints all of the contents of an AVL tree
void printTree(node *library){

  //If we reach the end of the AVL tree, return
  if (library == NULL)
    return;
  
  //Print the movie
  printMovie(library->movieInfo);

  //Recurse through the tree
  printTree(library->left);
  printTree(library->right);
}


//This function prints all of the contents of a movie entry
void printMovie(entry movie){
  printf("\nTitle: %s\n\tRelease Date: %s\n\tRuntime (m): %s\n\tMedia Type: %s\n\tDate Acquired: %s\n\tGenres: %s\n\n", movie.title, movie.releaseDate, movie.runtimeMinutes, movie.mediaType, movie.acquireDate, movie.genres);
  return;
}


//This (borrowed) function deletes a node from an AVL tree
node* delete(node *library, struct entry movieToDelete)
{
  //If we reach the end of the AVL tree, return
  if(library == NULL)
    return library;

  //Find the movie to delete in the AVL tree
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


//This function is used to copy all of the contents from one movie entry struct into another
void copyMovie(struct entry *dest, struct entry src){

  //Copy all of the non-user-specified data into the destination entry
  strncpy(dest->title, src.title, sizeof(dest->title));
  strncpy(dest->titleOrig, src.titleOrig, sizeof(dest->titleOrig));
  strncpy(dest->titleMod, src.titleMod, sizeof(dest->titleMod));
  strncpy(dest->releaseDate, src.releaseDate, sizeof(dest->releaseDate));
  strncpy(dest->runtimeMinutes, src.runtimeMinutes, sizeof(dest->runtimeMinutes));
  strncpy(dest->genres, src.genres, sizeof(dest->genres));

  //Copy all of the user-specified data into the destination entry
  strncpy(dest->acquireDate, src.acquireDate, sizeof(dest->acquireDate));
  strncpy(dest->mediaType, src.mediaType, sizeof(dest->mediaType));
  
  return;
}


//This (borrowed) recursive function frees the memory used for the AVL tree
void dispose(struct node* t)
{
  //If we haven't reached the end of the AVL tree, keep recursing
  if( t != NULL ){
      dispose( t->left );
      dispose( t->right );
      free( t );
  }
}

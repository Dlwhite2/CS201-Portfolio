//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdbool.h>

#ifndef AVLTREE_H_
#define AVLTREE_H_

#define MAX_TITLE_LENGTH 200
#define MAX_INFO_LENGTH 50

typedef struct entry{
  char titleOrig[MAX_TITLE_LENGTH];
  char title[MAX_TITLE_LENGTH];
  char titleMod[MAX_TITLE_LENGTH];
  char releaseDate[MAX_INFO_LENGTH];
  char acquireDate[MAX_INFO_LENGTH];
  char mediaType[MAX_INFO_LENGTH];
  char genres[MAX_INFO_LENGTH];
  char runtimeMinutes[10];
} entry;


typedef struct node
{
  struct entry movieInfo;
  struct node*  left;
  struct node*  right;
  int height;
} node;


void dispose(node* t);
entry find( char* search, node *t );
node* findNode(char* search, node *t);
node* insert( struct entry movieEntry, node *t );
node* delete(node* library, entry movieToDelete );
void displayMatches(entry *matches, int* counter, node* t, char* query);
void displayTree(node* t);
node* minItem(node* tree);
void printTree(node* library);
void printMovie(entry movie);
void copyMovie(entry* dest, entry src);
entry search(node*);
node* searchNode(node*);

/*

    remove all nodes of an AVL tree

*/
/*
void dispose(node* t)
{
  if( t != NULL )
    {
      dispose( t->left );
      dispose( t->right );
      free( t );
    }
}


struct entry find(char* query, node* t )
{
  struct entry movie = {0};
  if( t == NULL ){
    printf("Could not find any matches. Please edit or refine your search.\n");
    return movie;
  }
  
  if( strncmp(query, t->movieInfo.titleMod, strlen(query)) < 0)//e < t->data )
    return find( query, t->left );
  else if( strncmp(query, t->movieInfo.titleMod, strlen(query)) > 0)//e > t->data )
    return find( query, t->right );
  else if( (strcmp(query, t->movieInfo.titleMod) == 0  && (strlen(query) == strlen(t->movieInfo.titleMod)))){
    copyMovie(&movie, t->movieInfo);
    return movie;
  }else{
    int counter = 1;
    int *cnt = &counter;
    entry matches[30];
    printf("\n---SEARCH RESULTS---\n\n");
    displayMatches(matches, cnt, t, query);
    printf("\n---FINISH SEARCH RESULTS---\n\n");
    printf("Please enter the number of the movie you'd like to add to your library: ");
    int choice;
    scanf("%d", &choice);
    getchar();
    if (choice == 0){
      printf("\nPlease search the name of the movie you would like to add to your library: ");
      return movie;
    } else if (choice > 30){
      printf("Sorry, that was not a valid option. Exiting command.\n\n");
      return movie;
    }
    return matches[choice - 1];
  }
}


struct node* findNode(char* query, node* t )
{
  struct node* temp = NULL;
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
    entry matches[30];
    displayMatches(matches, cnt, t, query);
    return t;
  }
}



static int height( node* n )
{
  if( n == NULL )
    return -1;
  else
    return n->height;
}


static int max( int l, int r)
{
  return l > r ? l: r;
}



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


static node* double_rotate_with_left( node* k3 )
{

  k3->left = single_rotate_with_right( k3->left );


  return single_rotate_with_left( k3 );
}


static node* double_rotate_with_right( node* k1 )
{
  k1->right = single_rotate_with_left( k1->right );


  return single_rotate_with_right( k1 );
}


node* insert(struct entry movie, node* t)
{
  if( t == NULL )
    {
      
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
  

  t->height = max( height( t->left ), height( t->right ) ) + 1;
  // printf("TitleOrig: %s \t TitleOrigMod: %s\n", t->movieInfo.titleOrig, t->movieInfo.titleOrigMod);
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
  printf("\nTitle: %s\n\tRelease Date: %s\n\tRuntime (m): %s\n\tMedia Type: %s\n\tDate Acquired: %s\n\n", movie.title, movie.releaseDate, movie.runtimeMinutes, movie.mediaType, movie.acquireDate);
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
  strcpy(dest->title, src.title);
  strcpy(dest->titleOrig, src.titleOrig);
  strcpy(dest->titleMod, src.titleMod);
  strcpy(dest->releaseDate, src.releaseDate);
  strcpy(dest->runtimeMinutes, src.runtimeMinutes);
  strcpy(dest->genres, src.genres);
  //USER INFO
  strcpy(dest->acquireDate, src.acquireDate);
  strcpy(dest->mediaType, src.mediaType);
  return;
}*/

#endif

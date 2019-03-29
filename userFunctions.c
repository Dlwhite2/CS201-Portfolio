#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userFunctions.h"
//#include "avltree.h"


node* createEntry(node *tree, node *library){
  getchar();
  printf("Creating entry\n");
  printf("Search the name of the movie you would like to add to your library (or '!' to quit): ");
  entry movie = search(tree);
  if (strcmp(movie.title, "") == 0){
    printf("\nAborting adding movie to the library!\n\n");
    return library;
  }
  printf("\nAdding \"%s\" to your library!\n\n", movie.title);
  //Ask about other info
  char acquireDate[50];
  char mediaType[50];
  printf("When did you buy the movie? MM/YYYY = ");
  scanf("%[^\n]s", acquireDate);
  getchar();
  printf("Acquire date is: %s\n", acquireDate);
  printf("\nWhat type of media is the movie?\n\tOptions:\n\t\t\"DVD\"\n\t\t\"BR\" for BluRay\n\t\t\"VCR\"\n\t\t\"DC\" for Digital Copy\nMedia Type: ");
  scanf("%[^\n]s", mediaType);
  getchar();
  
  strcpy(movie.acquireDate, acquireDate);
  strcpy(movie.mediaType, mediaType);

  library = insert(movie, library);
  printf("\n\"%s\" has been added to your movie library!\n\n", movie.title);

  return library;
}

void retrieveEntry(node *library){
  getchar();
  printf("Reading entry\n");
  printf("Search the name of the movie in your movie library that you would like to know about (or '!' to quit): ");
  struct entry movie = search(library);
  if (strcmp(movie.title, "") == 0){
    printf("\nAborting movie retrieval!\n\n");
    return;
  }
  printf("\nTitle: %s\n\tRelease Date: %s\n\tRuntime (m): %s\n\tMedia Type: %s\n\tDate Acquired: %s\n\n", movie.title, movie.releaseDate, movie.runtimeMinutes, movie.mediaType, movie.acquireDate);
  return;
}


void updateEntry(node *library){
  printf("Updating entry\n");
  char newInfo[200];
  getchar();
  printf("Enter the name of the movie in your library that you would like to update (or '!' to quit): ");
  struct node* movieNode = searchNode(library);
  if(movieNode == NULL){
    printf("\nAborting update!\n\n");
    return;
  }
  getchar();
  int choice;
  printf("Please select the number of the object you would like to update:\n\t1) Title\n\t2) Release Date\n\t3) Acquire Date\n\t4) Media Type\n\t5) Genres\n\t6) Quit\n\nOption: ");
  scanf("%d", &choice);
  getchar();
    switch(choice){
    case 0:
      break;
    case 1:
      printf("Please enter the new Title: ");
      scanf("%[^\n]s", newInfo);
      strcpy(movieNode->movieInfo.title, newInfo);
      strlwr(newInfo);
      removeArticles(newInfo);
      strcpy(movieNode->movieInfo.titleMod, newInfo);
      break;
    case 2:
      printf("Please enter the new Release Date: ");
      scanf("%[^\n]s", newInfo);
      strcpy(movieNode->movieInfo.releaseDate, newInfo);
      break;
    case 3:
      printf("Please enter the new Acquire Date: ");
      scanf("%[^\n]s", newInfo);
      strcpy(movieNode->movieInfo.acquireDate, newInfo);
      break;
    case 4:

      printf("Please enter the new Media Type: ");
      scanf("%[^\n]s", newInfo);
      strcpy(movieNode->movieInfo.mediaType, newInfo);
      break;
    case 5:
      printf("Please enter the new Genre(s): ");
      scanf("%[^\n]s", newInfo);
      strcpy(movieNode->movieInfo.genres, newInfo);
      break;
    default:
      choice = 0;
    }
    getchar();
  return;
}

node* deleteEntry(node *library){
  printf("Deleting entry\n");
  printf("Search the name of the movie you would like to delete from your library (or '!' to quit): ");
  getchar();
  entry movieToDelete = search(library);
  //printf("The genres for the node to delete are: %s\n", movieToDelete.genres);
  if (strcmp(movieToDelete.title, "") == 0){
      printf("\nAborting deletion!\n\n");
      return library;
    }
  library = delete(library, movieToDelete);
  printf("\n\"%s\" has been deleted from your library!\n\n", movieToDelete.title);

  return library;
}


void removeArticles (char *string) {
  char *match;
  char *articles[] = {"the ", "a ", "an ", ", ", ": ", "; ", ". ", "'"};
  int i;
  for (i = 0; i < 8; i++){
    int len = strlen(articles[i]);
    while ((match = strstr(string, articles[i]))) {
      *match = '\0';
      strcat(string, match+len);
    }
  }
}

void printNode(entry movie){
    printf("\nTitle: %s\n\tRelease Date: %s\n\tRuntime (m): %s\n\tMedia Type: %s\n\tDate Acquired: %s\n\n", movie.title, movie.releaseDate, movie.runtimeMinutes, movie.mediaType, movie.acquireDate);
    return;
  }

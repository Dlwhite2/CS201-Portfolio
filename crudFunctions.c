#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crudFunctions.h"
#include "utilityFunctions.h"

//This file contains the implementations of the 4 CRUD functions that the program performs



//This is the function that creates an entry in the user's library
node* createEntry(node *tree, node *library){

  //Display initial prompts
  printf("Creating entry\n");
  printf("Search the name of the movie you would like to add to your library (or '!' to quit): ");

  //Search for the movie
  entry movie = search(tree);
  if (strcmp(movie.title, "") == 0){
    printf("\nAborting adding movie to the library!\n\n");
    return library;
  }
  printf("\nAdding \"%s\" to your library!\n\n", movie.title);
  
  //Ask about other info
  char acquireDate[50];
  printf("When did you buy the movie? MM/YYYY = ");
  scanf("%50[^\n]s", acquireDate);
  flush();
  strncpy(movie.acquireDate, acquireDate, sizeof(movie.acquireDate));
  
  char mediaType[50];
  printf("Acquire date is: %s\n", acquireDate);
  printf("\nWhat type of media is the movie?\n\tOptions:\n\t\t\"DVD\"\n\t\t\"BR\" for BluRay\n\t\t\"VCR\"\n\t\t\"DC\" for Digital Copy\nMedia Type: ");
  scanf("%50[^\n]s", mediaType);
  flush();
  strncpy(movie.mediaType, mediaType, sizeof(movie.mediaType));

  library = insert(movie, library);
  printf("\n\"%s\" has been added to your movie library!\n\n", movie.title);

  return library;
}

void retrieveEntry(node *library){
  printf("Reading entry\n");
  printf("Search the name of the movie in your movie library that you would like to know about (or '!' to quit): ");
  struct entry movie = search(library);
  if (strcmp(movie.title, "") == 0){
    printf("\nAborting movie retrieval!\n\n");
    return;
  }
  printf("\nTitle: %s\n\tRelease Date: %s\n\tRuntime (m): %s\n\tMedia Type: %s\n\tDate Acquired: %s\n\tGenres: %s\n\n", movie.title, movie.releaseDate, movie.runtimeMinutes, movie.mediaType, movie.acquireDate, movie.genres);
  return;
}


void updateEntry(node *library){
  printf("Updating entry\n");
  char newInfo[200];
  
  printf("Enter the name of the movie in your library that you would like to update (or '!' to quit): ");
  struct node* movieNode = searchNode(library);
  if(movieNode == NULL){
    printf("\nAborting update!\n\n");
    return;
  }
  int choice;
  printf("Please select the number of the object you would like to update:\n\t1) Title\n\t2) Release Date\n\t3) Acquire Date\n\t4) Media Type\n\t5) Genres\n\t6) Quit\n\nOption: ");
  scanf("%d", &choice);
  flush();
    switch(choice){
    case 0:
      break;
    case 1:
      printf("Please enter the new Title: ");
      scanf("%200[^\n]s", newInfo);
      flush();
      strncpy(movieNode->movieInfo.title, newInfo, sizeof(movieNode->movieInfo.title));
      strlwr(newInfo);
      removeArticles(newInfo);
      strncpy(movieNode->movieInfo.titleMod, newInfo, sizeof(movieNode->movieInfo.titleMod));
      break;
    case 2:
      printf("Please enter the new Release Date: ");
      scanf("%200[^\n]s", newInfo);
      flush();
      strncpy(movieNode->movieInfo.releaseDate, newInfo, sizeof(movieNode->movieInfo.releaseDate));
      break;
    case 3:
      printf("Please enter the new Acquire Date: ");
      scanf("%200[^\n]s", newInfo);
      flush();
      strncpy(movieNode->movieInfo.acquireDate, newInfo, sizeof(movieNode->movieInfo.acquireDate));
      break;
    case 4:
      printf("Please enter the new Media Type: ");
      scanf("%[^\n]s", newInfo);
      flush();
      strncpy(movieNode->movieInfo.mediaType, newInfo, sizeof(movieNode->movieInfo.mediaType));
      break;
    case 5:
      printf("Please enter the new Genre(s): ");
      scanf("%200[^\n]s", newInfo);
      flush();
      strncpy(movieNode->movieInfo.genres, newInfo, sizeof(movieNode->movieInfo.genres));
      break;
    default:
      choice = 0;
    }
  return;
}

node* deleteEntry(node *library){
  printf("Deleting entry\n");
  printf("Search the name of the movie you would like to delete from your library (or '!' to quit): ");
  entry movieToDelete = search(library);

  if (strcmp(movieToDelete.title, "") == 0){
      printf("\nAborting deletion!\n\n");
      return library;
    }
  library = delete(library, movieToDelete);
  printf("\n\"%s\" has been deleted from your library!\n\n", movieToDelete.title);

  return library;
}




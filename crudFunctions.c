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

  //Check to see if the user quit the command before proceding
  if (strcmp(movie.title, "") == 0){
    printf("\n\nAborting adding movie to the library!\n\n");
    return library;
  }

  //Let the user know what's happening
  printf("\nAdding \"%s\" to your library!\n\n", movie.title);
  
  //Get the date the movie was acquired
  char acquireDate[50];
  printf("When did you buy the movie? MM/YYYY = ");
  scanf("%50[^\n]s", acquireDate);
  flush();
  strncpy(movie.acquireDate, acquireDate, sizeof(movie.acquireDate));

  //Get the type of media that the movie is 
  char mediaType[50];
  printf("Acquire date is: %s\n", acquireDate);
  printf("\nWhat type of media is the movie?\n\tOptions:\n\t\t\"DVD\"\n\t\t\"BR\" for BluRay\n\t\t\"VCR\"\n\t\t\"DC\" for Digital Copy\nMedia Type: ");
  scanf("%50[^\n]s", mediaType);
  flush();
  strncpy(movie.mediaType, mediaType, sizeof(movie.mediaType));

  //Insert the movie into the user's library
  library = insert(movie, library);

  //Let the user know that the movie was added to the library
  printf("\n\"%s\" has been added to your movie library!\n\n", movie.title);

  return library;
}


//This function retrieves and displays the information for a movie in the user's library
void retrieveEntry(node *library){
  //Let the user know what's happening
  printf("Retrieving entry\n");
  printf("Search the name of the movie in your movie library that you would like to know about (or '!' to quit): ");

  //Find the movie in the user's library
  struct entry movie = search(library);

  //Check to see if the user quit the command before proceding
  if (strcmp(movie.title, "") == 0){
    printf("\n\nAborting movie retrieval!\n\n");
    return;
  }

  //Display all of the information about the movie
  printMovie(movie);
  
  return;
}


//This function updates the information about a specific movie in the user's library
void updateEntry(node *library){

  //Let the user know what's going on
  printf("Updating entry\n");
  printf("Enter the name of the movie in your library that you would like to update (or '!' to quit): ");

  //Search for the movie in the user's library to update and return the AVL node
  struct node* movieNode = searchNode(library);
  if(movieNode == NULL){
    printf("\nAborting update!\n\n");
    return;
  }

  //Prompt the user to select the information they want to update
  printf("Please select the number of the object you would like to update:\n\t1) Title\n\t2) Release Date\n\t3) Acquire Date\n\t4) Media Type\n\t5) Genres\n\t6) Quit\n\nOption: ");

  //Get the choice from the user
  int choice;
  scanf("%d", &choice);
  flush();

  //Create object to store the updated information
  char newInfo[200];
  
  switch(choice){
  case 1://Update the Title
    printf("Please enter the new Title: ");
    scanf("%200[^\n]s", newInfo);
    flush();
    strncpy(movieNode->movieInfo.title, newInfo, sizeof(movieNode->movieInfo.title));
    //Also update the modified title
    strlwr(newInfo);
    removeArticles(newInfo);
    strncpy(movieNode->movieInfo.titleMod, newInfo, sizeof(movieNode->movieInfo.titleMod));
    break;
  case 2://Update the release date
    printf("Please enter the new Release Date: ");
    scanf("%200[^\n]s", newInfo);
    flush();
    strncpy(movieNode->movieInfo.releaseDate, newInfo, sizeof(movieNode->movieInfo.releaseDate));
    break;
  case 3://Update the Acquire Date
    printf("Please enter the new Acquire Date: ");
    scanf("%200[^\n]s", newInfo);
    flush();
    strncpy(movieNode->movieInfo.acquireDate, newInfo, sizeof(movieNode->movieInfo.acquireDate));
    break;
  case 4://Update the Media Type
    printf("Please enter the new Media Type: ");
    scanf("%[^\n]s", newInfo);
    flush();
    strncpy(movieNode->movieInfo.mediaType, newInfo, sizeof(movieNode->movieInfo.mediaType));
    break;
  case 5://Update the Genres
    printf("Please enter the new Genre(s): ");
    scanf("%200[^\n]s", newInfo);
    flush();
    strncpy(movieNode->movieInfo.genres, newInfo, sizeof(movieNode->movieInfo.genres));
    break;
  default:
    break;
  }
  return;
}


//This function deletes a movie entry from the user's library
node* deleteEntry(node *library){

  //Let the user know what's going on
  printf("Deleting entry\n");
  printf("Search the name of the movie you would like to delete from your library (or '!' to quit): ");

  //Search for the movie to delete
  entry movieToDelete = search(library);

  //Check to see if the user quit the command before proceding
  if (strcmp(movieToDelete.title, "") == 0){
      printf("\n\nAborting deletion!\n\n");
      return library;
  }

  //Delete the movie from the user's library
  library = delete(library, movieToDelete);

  //Let the user know that we finished
  printf("\n\"%s\" has been deleted from your library!\n\n", movieToDelete.title);

  return library;
}

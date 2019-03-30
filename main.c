#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"
#include "crudFunctions.h"
#include "utilityFunctions.h"


int main(void){
  
  //Open file containing database
  FILE * db;
  db = fopen("movie_records.txt", "r");

  //Load database into AVL tree
  node *tree = NULL;
  tree = createTree(db, tree);
  if (tree == NULL)
    printf("There was an error loading the database.\n");

  //Welcome message asking for username
  printf("Welcome to your home theater library.\n\nPlease enter in a user name: ");

  //Get username
  char userName[50];
  scanf("%46s", userName);
  flush();
  printf("\nHello there, %s\n", userName);

  //Append username for creating log file
  strncat(userName, ".txt", 4);

  //Check to see if  log exists. If so, load the information inside it into memory
  node *library = NULL;
  FILE * log;
  log = fopen(userName, "r");
  if (log){
    library = createTree(log, library);
    if (library == NULL)
      printf("The library was empty!\n");
    fclose(log);
  }
 
  //This is a standard command message that will be printed several times
  char cmdMsg[] = "Please enter a command: \n\t'c' to create an entry in your library\n\t'r' to retrieve an entry in your library\n\t'u' to update an entry in your library\n\t'd' to delete an entry in your library\n\t'p' to print out all of the movies in your library\n\t'e' to exit\n";

  //Get the command from the user
  char state[50];
  printf("%s", cmdMsg);
  scanf("%50s", state);
  flush();

  //Verify the correct command formatting
  while (!commandFormatIsCorrect(state)){
    scanf("%50s", state);
    flush();
  }

  //Continuously get the user's command until exiting the program
  while(state[0] != 'e'){
    switch(state[0]){
    case 'c':
      //Create an entry in the user's library
      library = createEntry(tree, library);
      break;
    case 'r':
      //Retrieve an entry from the user's library
      retrieveEntry(library);
      break;
    case 'u':
      //Update an entry in the user's library
      updateEntry(library);
      break;
    case 'd':
      //Delete an entry from the user's library
      library = deleteEntry(library);
      break;
    case 'p':
      //Print the entire user's library
      printf("\n---PRINTING USER LIBRARY---\n\n");
      printTree(library);
      printf("\n---FINISHED PRINTING USER LIBRARY---\n\n");
      break;
    default:
      //Display help prompt
      helpMsg(state);
      break;
    }

    //After a command is completed, get another command from the user
    printf("%s", cmdMsg);
    scanf("%50s", state);
    flush();

    //Again, verify that it's format is correct
    while (!commandFormatIsCorrect(state)){
      scanf("%50s", state);
      flush();
    }
  }

  
  printf("Your log is being saved in %s in the directory where this program is installed.\n", userName);

  //Once the user decides to exit, save their library into [userName].txt 
  log = fopen(userName, "w");
  saveLog(log, library);
  fclose(log);
  
  return 0;
}

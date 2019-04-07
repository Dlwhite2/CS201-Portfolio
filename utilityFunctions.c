#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avltree.h"
#include "utilityFunctions.h"



struct entry search(node *tree){

  //Get the search query
  char search[MAX_INFO_LENGTH];
  scanf("%200[^\n]s", search);
  flush();

  //Check to make sure the user didn't quit before proceding
  struct entry movieSearch = {0};
  if (strcmp(search, "!") == 0)
    return movieSearch;

  //Modify the search query to match the modified titles in the avl tree
  toLower(search);
  removeArticles(search);

  //Return the movie entry from the AVL tree
  movieSearch = find(search, tree);

  return movieSearch;
}


struct node* searchNode(node *library){

  //Get search query
  char search[MAX_INFO_LENGTH];
  struct node* t = {0};
  scanf("%200[^\n]s", search);
  flush();

  //Check to make sure the user didn't quit before proceding
  if (strcmp(search, "!") == 0)
    return t;

  //Modify the search query to match the modified titles in the avl tree
  toLower(search);
  removeArticles(search);

  //Return the node from the AVL tree
  t = findNode(search, library);
  
  return t;
}


//This is a function that removes all of the articles and a lot of common punctuation
void removeArticles (char *string) {

  char *match;
  char *articles[] = {"the", "a", "an", ",", ":", ";", ".", "'"};
  int i;
  for (i = 0; i < 8; i++){
    int len = strlen(articles[i]);
    while ((match = strstr(string, articles[i]))) {
      *match = '\0';
      strcat(string, match+len);
    }
  }
  return;
}


//This function is used to print out all of the information about a single movie
void printNode(entry movie){

  printf("\nTitle: %s\n\tRelease Date: %s\n\tRuntime (m): %s\n\tMedia Type: %s\n\tDate Acquired: %s\n\n", movie.title, movie.releaseDate, movie.runtimeMinutes, movie.mediaType, movie.acquireDate);
  return;
}


//This function ensures that the command given at the main menu is a single letter
int commandFormatIsCorrect(char state[]){
  
  //Check to see if the input was 1 character long
  if (state[1] == '\0'){
    return 1;
  }else {
    printf("Invalid format. Please enter the command as a single character.\n");
    return 0;
  }
}


//This is called when a command is formatted incorrectly
void helpMsg(char state[]){

  printf("Sorry, %s is not a valid command. Please try one of the commands above.\n", state);

  return;
}

//This function recurses through the user library and prints the information to a text file to be act as a database for the user's library upon the next run of the program
void saveLog(FILE *log, node *library){

  //Stop when you reach the end of the AVL tree
  if (library == NULL)
    return;

  //Print the information at that node
  fprintf(log, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t\n", library->movieInfo.titleOrig, library->movieInfo.title, library->movieInfo.releaseDate, library->movieInfo.runtimeMinutes,
	 library->movieInfo.genres, library->movieInfo.acquireDate, library->movieInfo.mediaType);

  //Recurse
  saveLog(log, library->left);
  saveLog(log, library->right);
}


//This function fills an AVL tree from a properly formatted text file containing movie information
node* createTree(FILE *log, node *library){

  //Let the user know what is happening
  printf("\nLoading your movie library...\n");

  //Load a single line into memory
  char line[MAX_INFO_LENGTH];  
  while(fgets(line, sizeof(line), log) != NULL){
    
    //Use this object to hold all of the information to be inserted in the AVL tree
    struct entry movieEntry;

    //Use this counter to keep track of how many tabs have been processed down the line
    int counter = 0;

    //Use this to remove the newline character from the last piece of data in the line
    char *pos;

    //Parse the line by tabs
    char * data;
    data = strtok (line,"\t"); 

    //Loop through the line until we reach the end
    while (data != NULL)
      {
	switch(counter){
	case 0://Original Title -> titleOrig
	  strcpy(movieEntry.titleOrig, data);
	  break;
	case 1://Primary title -> title. Modify title -> titleMod
	  strcpy(movieEntry.title, data);
	  //Save lowercase/article-less copy -> titleMod
	  toLower(data);
	  removeArticles(data);
	  strcpy(movieEntry.titleMod, data);
	  break;
	case 2://startDate -> releaseDate (also append date to titleMod)
	  strcpy(movieEntry.releaseDate, data);
	  strcat(movieEntry.titleMod, " [");
	  strcat(movieEntry.titleMod, movieEntry.releaseDate);
	  strcat(movieEntry.titleMod, "]");
	  break;
	case 3://runtime -> runtimeMinutes
	  strcpy(movieEntry.runtimeMinutes, data);
	  break;
	case 4://genres -> genres (and remove newline character)
	  if ((pos=strchr(data, '\n')) != NULL)
	    *pos = '\0';
	  strcpy(movieEntry.genres, data);
	  break;
	case 5://Save acquireDate
	  strcpy(movieEntry.acquireDate, data);
	  break;
	case 6://Save mediaType
	  strcpy(movieEntry.mediaType, data);
	  break;
	default:
	  break;
	}
	//Increment tab counter
	counter++;

	//Grab next piece of information in the line
	data = strtok(NULL, "\t");
      }
    //Once all of the information has been added into the entry, insert the entry into the AVL tree
    library = insert(movieEntry, library);
  }

  //Let the user know that the data was loaded
  printf("Your movie library was loaded!\n");
  printf("**Limit input to 200 characters**\n\n");
  return library;
}

//This function clears out the rest of the information in stdin
void flush(){

  int c;
  //Loop through the rest of stdin and discard whatever we find
  while ((c = getchar()) != '\n' && c != EOF);
  
  return;
}

void toLower(char* word){

  int i;
  
  for (i = 0; i < strlen(word); i++){
    word[i] = tolower(word[i]);
  }
  
  return;
}

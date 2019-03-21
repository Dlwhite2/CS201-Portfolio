#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

void createEntry();
void readEntry();
void updateEntry();
void deleteEntry();
void loadDatabase(node*);
void loadLog();
void saveLog();
void helpMsg(char*);
int commandFormatIsCorrect(char*);



int main(void){
  node *tree = NULL;
  loadDatabase(tree);
  char state[50];
  char userName[50];
  printf("Welcome to your home theater library.\nPlease enter in your user name in the form [first_last]\n");
  scanf("%s", userName);
  printf("\nHello there, %s\n", userName);

  FILE * log;
  log = fopen(userName, "r");
  if (log){
    loadLog();
    fclose(log);
    log = fopen(userName, "w");
  } else {
    log = fopen(userName, "w");
  }

  char cmdMsg[] = "Please enter a command or 'e' to exit: \n\t'c' to create an entry in your library\n\t'r' to read an entry in your library\n\t'u' to update an entry in your library\n\t'd' to delete an entry in your library\n";
  printf("%s", cmdMsg);

  scanf("%s", state);
  while (!commandFormatIsCorrect(state)){
    scanf("%s", state);
  }
  while(state[0] != 'e'){
    switch(state[0]){
    case 'c':
      createEntry();
      break;
    case 'r':
      readEntry();
      break;
    case 'u':
      updateEntry();
      break;
    case 'd':
      deleteEntry();
      break;
    default:
      helpMsg(state);
      break;
    }

    printf("%s", cmdMsg);
    scanf("%s", state);
    while (!commandFormatIsCorrect(state)){
      scanf("%s", state);
    }
  }
  printf("Your log is being saved in %s in the directory where this program is installed.\n", userName);
  saveLog();

  return 0;
}

int commandFormatIsCorrect(char state[]){
  if (state[1] == '\0'){
    return 1;
  }else {
    printf("Invalid format. Please enter the command as a single character.\n");
    return 0;
  }
}

void createEntry(){
  printf("Creating entry\n");
  return;
}


void readEntry(){
  printf("Reading entry\n");
  return;
}

void updateEntry(){
  printf("Updating entry\n");
  return;
}

void deleteEntry(){
  printf("Deleting entry\n");
  return;
}

void helpMsg(char state[]){
  printf("Sorry, %s is not a valid command. Please try one of the commands above.\n", state);
  return;
}

void loadLog(){
  printf("The existing log should bew loaded into memory here.\n");
  return;
}

void saveLog(){
  printf("The log that was created in memory should be written to the log file here.\n");
  return;
}

void loadDatabase(node* tree){
  printf("Loading the database...\n");
  FILE * db;
  char line[200];
  db = fopen("movie_records.txt", "r");
  //head = getNewTrieNode();
  int i;
  int tabNum = 0;


  while (fgets(line, sizeof(line), db) != NULL) {
    //struct entry movieEntry;
    char * data;
    struct entry movieEntry;
    int counter = 0;
    data = strtok (line,"\t");
    while (data != NULL)
      {
	switch(counter){
	case 0:
	  strcpy(movieEntry.garbage, data);
	  break;
	case 1:
	  strcpy(movieEntry.movie, data);
	  break;
	case 2:
	  strcpy(movieEntry.titleOrig, data);
	  break;
	case 3:
	  strcpy(movieEntry.title, data);
	  break;
	case 4:
	  strcpy(movieEntry.isAdult, data);
	  break;
	case 5:
	  strcpy(movieEntry.releaseDate, data);
	  break;
	case 6:
	  strcpy(movieEntry.endDate, data);
	  break;
	case 7:
	  strcpy(movieEntry.runtimeMinutes, data);
	  break;
	case 8:
	  strcpy(movieEntry.genres, data);
	  break;
	default:
	  break;
	}
	counter++;
	data = strtok (NULL, "\t");
      }
    //printf("%s\n%s\n%s\n\n\n", movieEntry.garbage, movieEntry.title, movieEntry.genres);
    tree = insert(movieEntry, tree);
  }
  printf("The database was loaded...\n");
  //display_avl(tree);
  char search[150];
  printf("Search: \n");
  scanf("%[^\n]s", search);
  struct entry movieSearch = find(search, tree);
  printf("The genre(s) of %s is(are): %s\n", search, movieSearch.genres);


  fclose(db);
  return;
}



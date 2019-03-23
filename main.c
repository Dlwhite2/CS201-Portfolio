#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

void createEntry(node*, node*);
void readEntry(node*, node*);
void updateEntry(node*, node*);
void deleteEntry(node*, node*);
node* loadDatabase(node*);
void loadLog();
void saveLog();
void helpMsg(char*);
int commandFormatIsCorrect(char*);
char* strlwr(char*);
void removeArticles(char*);
struct entry search(node*);


int main(void){
  node *tree = NULL;
  tree = loadDatabase(tree);
  if (tree == NULL)
    printf("tree is null after being loaded\n");
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

  node *library = NULL;

  char cmdMsg[] = "Please enter a command or 'e' to exit: \n\t'c' to create an entry in your library\n\t'r' to read an entry in your library\n\t'u' to update an entry in your library\n\t'd' to delete an entry in your library\n";
  printf("%s", cmdMsg);

  scanf("%s", state);
  while (!commandFormatIsCorrect(state)){
    scanf("%s", state);
  }
  while(state[0] != 'e'){
    switch(state[0]){
    case 'c':
      createEntry(tree, library);
      break;
    case 'r':
      readEntry(tree, library);
      break;
    case 'u':
      updateEntry(tree, library);
      break;
    case 'd':
      deleteEntry(tree, library);
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

void createEntry(node *tree, node *library){
  getchar();
  printf("Creating entry\n");
  printf("Search the name of the movie you would like to add to your library: ");
  struct entry movie = search(tree);
  struct entry temp = {0};
  while(strcmp(movie.title, temp.title) == 0){
    getchar();
    movie = search(tree);
  }
  getchar();
  printf("The movie it thinks it found is %s.\n", movie.title);
  //Ask about other info
  char aquireDate[10];
  char mediaType[10];
  printf("When did you buy the movie? MM/YYYY = ");
  scanf("%[^\n]s", aquireDate);
  getchar();
  printf("\nWhat type of media is the movie?\n\tOptions:\n\t\t\"DVD\"\n\t\t\"BR\" for BluRay\n\t\t\"VCR\"\n\t\t\"DC\" for Digital Copy\nMedia Type: ");
  scanf("%[^\n]s", mediaType);
  getchar();
  library = insert(movie, library);
  printf("\n\n%s has been added to your movie library!\n\n", movie.title);
  return;
}


void readEntry(node *tree, node *library){
  printf("Reading entry\n");
  return;
}

void updateEntry(node *tree, node *library){
  printf("Updating entry\n");
  return;
}

void deleteEntry(node *tree, node *library){
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

node* loadDatabase(node* tree){
  printf("Loading the database...\n");
  FILE * db;
  char line[200];
  db = fopen("movie_records.txt", "r");

  while (fgets(line, sizeof(line), db) != NULL) {
    //struct entry movieEntry;
    char * data;
    struct entry movieEntry;
    int counter = 0;
    data = strtok (line,"\t");
    while (data != NULL)
      {
	char *newInfo;
	switch(counter){
	case 0:
	  //strcpy(movieEntry.garbage, data);
	  break;
	case 1:
	  //strcpy(movieEntry.movie, data);
	  break;
	case 2:
	  strcpy(movieEntry.titleOrig, data);
	  break;
	case 3:
	  newInfo = (char*)malloc(strlen(data));
	  //Save a copy of the unmodified title
	  strcpy(movieEntry.title, data);
	  
	  strcpy(newInfo, strlwr(data));
	  removeArticles(newInfo);
	  strcpy(movieEntry.titleMod, newInfo);
	  //printf("title: %s \tmod: %s\n", movieEntry.title, movieEntry.titleMod);
	  free(newInfo);
	  break;
	case 4:
	  //strcpy(movieEntry.isAdult, data);
	  break;
	case 5:
	  strcpy(movieEntry.releaseDate, data);
	  break;
	case 6:
	  //strcpy(movieEntry.endDate, data);
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

  fclose(db);
  return tree;
}

struct entry search(node *tree){
  char search[150];
  scanf("%[^\n]s", search);
  memcpy(search, strlwr(search), sizeof(strlwr(search)));
  removeArticles(search);
  printf("%s\n", search);
  struct entry movieSearch = find(search, tree);
  return movieSearch;
}

char *strlwr(char *string){
  char *newString = (char*)malloc(strlen(string));
  int i;
  for(i = 0; i < strlen(string); i++){
    if(string[i] >= 'A' && string[i] <= 'Z' && string[i] != '\0'){
      newString[i] = string[i] + 32;
    } else {
      newString[i] = string[i];
    }
  }
  //if (strcmp(string, "Edge of Tomorrow") == 0)
  //printf("Right before \"return newString;\", newString is: %s\n", newString);
  return newString;
}

void removeArticles (char *string) {
  char *match;
  char *articles[] = {"the ", "a ", "an ", ", ", ": ", "; ", ". "};
  int i;
  for (i = 0; i < 7; i++){
    int len = strlen(articles[i]);
    while ((match = strstr(string, articles[i]))) {
      *match = '\0';
      strcat(string, match+len);
    }
  }
}

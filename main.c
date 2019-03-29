#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

node* createEntry(node*, node*);
void retrieveEntry(node*);
void updateEntry(node*);
node* deleteEntry(node*);
node* createTree(FILE*, node*);
void saveLog(FILE*, node*);
void helpMsg(char*);
int commandFormatIsCorrect(char*);
void removeArticles(char*);
entry search(node*);
node* searchNode(node*);
void printMovie(entry);

int main(void){
  node *tree = NULL;
  FILE * db;
  db = fopen("movie_records.txt", "r");

  tree = createTree(db, tree);
  if (tree == NULL)
    printf("There was an error loading the database.\n");
  char state[50];
  char userName[50];
  printf("Welcome to your home theater library.\n\nPlease enter in your user name in the form [first_last]\n");
  scanf("%s", userName);
  printf("\nHello there, %s\n", userName);

  strcat(userName, ".txt");
  
  node *library = NULL;
 
  FILE * log;
  log = fopen(userName, "r");
  if (log){
    library = createTree(log, library);
    if (library == NULL)
      printf("The library was empty!\n");
    fclose(log);
  }
 
 
  char cmdMsg[] = "Please enter a command: \n\t'c' to create an entry in your library\n\t'r' to retrieve an entry in your library\n\t'u' to update an entry in your library\n\t'd' to delete an entry in your library\n\t'p' to print out all of the movies in your library\n\t'e' to exit\n";

  printf("%s", cmdMsg);
  scanf("%s", state);
  while (!commandFormatIsCorrect(state)){
    scanf("%s", state);
  }
  while(state[0] != 'e'){
    switch(state[0]){
    case 'c':
      library = createEntry(tree, library);
      break;
    case 'r':
      retrieveEntry(library);
      break;
    case 'u':
      updateEntry(library);
      break;
    case 'd':
      library = deleteEntry(library);
      break;
    case 'p':
      printf("\n---PRINTING USER LIBRARY---\n\n");
      printTree(library);
      printf("\n---FINISHED PRINTING USER LIBRARY---\n\n");
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

  log = fopen(userName, "w");
  saveLog(log, library);
  fclose(log);
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

void helpMsg(char state[]){
  printf("Sorry, %s is not a valid command. Please try one of the commands above.\n", state);
  return;
}


void saveLog(FILE *log, node *library){
  if (library == NULL){// && library->left == NULL && library->right == NULL){
    //fclose(log);
    return;
  }

 fprintf(log, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t\n", library->movieInfo.titleOrig, library->movieInfo.title, library->movieInfo.releaseDate, library->movieInfo.runtimeMinutes,
	 library->movieInfo.genres, library->movieInfo.acquireDate, library->movieInfo.mediaType);

    saveLog(log, library->left);
    saveLog(log, library->right);
}

struct entry search(node *tree){
  char search[150];
  //getchar();
  struct entry movieSearch = {0};
  scanf("%[^\n]s", search);
  if (strcmp(search, "!") == 0)
    return movieSearch;
  getchar();
  strlwr(search);
  removeArticles(search);
  movieSearch = find(search, tree);
  while (strcmp(movieSearch.title, "") == 0 && strcmp(search, "!") != 0){
    scanf("%[^\n]s", search);
    getchar();
    strlwr(search);
    removeArticles(search);
    movieSearch = find(search, tree);
  }
  return movieSearch;
}

struct node* searchNode(node *library){

  char search[150];
  struct node* t = {0};
  scanf("%[^\n]s", search);
  if (strcmp(search, "!") == 0)
    return t;
  getchar();
  strlwr(search);
  removeArticles(search);
  t = findNode(search, library);
  while(t == NULL && strcmp(search, "!")){
    scanf("%[^\n]s", search);
    getchar();
    strlwr(search);
    removeArticles(search);
    t = findNode(search, library);
  }
    
  return t;
}


node* createTree(FILE *log, node *library){
  printf("\nLoading your movie library...\n");
  char line[200];  
  while(fgets(line, sizeof(line), log) != NULL){
    char * data;
    struct entry movieEntry;
    int counter = 0;
    char *pos;
    data = strtok (line,"\t"); 
    while (data != NULL)
      {
	//printf("data = %s s\n", data);
	switch(counter){
	case 0:
	  strcpy(movieEntry.titleOrig, data);
	  break;
	case 1:
	  strcpy(movieEntry.title, data);
	  strlwr(data);
	  removeArticles(data);
	  strcpy(movieEntry.titleMod, data);
	  break;
	case 2:
	  strcpy(movieEntry.releaseDate, data);
	  strcat(movieEntry.titleMod, " [");
	  strcat(movieEntry.titleMod, movieEntry.releaseDate);
	  strcat(movieEntry.titleMod, "]");
	  break;
	case 3:
	  strcpy(movieEntry.runtimeMinutes, data);
	  break;
	case 4:
	  if ((pos=strchr(data, '\n')) != NULL)
	    *pos = '\0';
	  strcpy(movieEntry.genres, data);
	  break;
	case 5:
	  strcpy(movieEntry.acquireDate, data);
	  break;
	case 6:
	  strcpy(movieEntry.mediaType, data);
	  break;
	default:
	  break;
	}
	counter++;
	data = strtok(NULL, "\t");
      }
    
    library = insert(movieEntry, library);
  }
  
  printf("Your movie library was loaded!\n\n");
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

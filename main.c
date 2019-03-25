#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

node* createEntry(node*, node*);
void retrieveEntry(node*);
node* updateEntry(node*);
node* deleteEntry(node*);
node* loadDatabase(node*);
node* loadUserLibrary(FILE*, node*);
void saveLog(FILE*, node*);
void helpMsg(char*);
int commandFormatIsCorrect(char*);
void removeArticles(char*);
entry search(node*);
node* searchNode(node*);
void printMovie(entry);

int main(void){
  node *tree = NULL;
  tree = loadDatabase(tree);
  if (tree == NULL)
    printf("There was an error loading the database.\n");
  char state[50];
  char userName[50];
  printf("Welcome to your home theater library.\nPlease enter in your user name in the form [first_last]\n");
  scanf("%s", userName);
  printf("\nHello there, %s\n", userName);

  strcat(userName, ".txt");
  
  node *library = NULL;
 
  FILE * log;
  log = fopen(userName, "r");
  if (log){
    library = loadUserLibrary(log, library);
    if (library == NULL)
      printf("The library was empty!\n");
    //fclose(log);
    log = fopen(userName, "w");
  } else {
    log = fopen(userName, "w");
  }
 
 
  char cmdMsg[] = "Please enter a command or 'e' to exit: \n\t'c' to create an entry in your library\n\t'r' to retrieve an entry in your library\n\t'u' to update an entry in your library\n\t'd' to delete an entry in your library\n\t'p' to print out all of the movies in your library\n";

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
      library = updateEntry(library);
      break;
    case 'd':
      library = deleteEntry(library);
      break;
    case 'p':
      printTree(library);
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
  printf("Search the name of the movie you would like to add to your library: ");
  entry movie = search(tree);
  //getchar();
  entry temp = {0};
  while(strcmp(movie.title, temp.title) == 0){
    //getchar();
    movie = search(tree);
    //getchar();
  }
  
  //Ask about other info
  char acquireDate[10];
  char mediaType[10];
  printf("When did you buy the movie? MM/YYYY = ");
  scanf("%[^\n]s", acquireDate);
  getchar();
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
  printf("Search the name of the movie in your movie library that you would like to know about: ");
  struct entry movie = {0}; 
  movie = search(library);
  //getchar();
  printf("\nTitle: %s\n\tRelease Date: %s\n\tRuntime (m): %s\n\tMedia Type: %s\n\tDate Acquired: %s\n\n", movie.title, movie.releaseDate, movie.runtimeMinutes, movie.mediaType, movie.acquireDate);
  return;
}


struct node* updateEntry(node *library){
  printf("Updating entry\n");
  char newInfo[200];
  getchar();
  printf("Enter the name of the movie in your library that you would like to update: ");
  struct node* movieNode = searchNode(library);
  struct entry temp = {0};
  while (strcmp(movieNode->movieInfo.title, temp.title) == 0){
    movieNode = searchNode(library);
  }
  //printf("The found movie was %s\n", movieNode->movieInfo.title);
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
  return movieNode;
}

node* deleteEntry(node *library){
  printf("Deleting entry\n");
  printf("Search the name of the movie you would like to delete from your library: ");
  getchar();
  entry movieToDelete = search(library);
  printf("The genres for the node to delete are: %s\n", movieToDelete.genres);
  library = delete(library, movieToDelete);
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

 fprintf(log, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t\n", library->movieInfo.titleOrig, library->movieInfo.title, library->movieInfo.releaseDate, library->movieInfo.acquireDate,
	 library->movieInfo.runtimeMinutes, library->movieInfo.mediaType, library->movieInfo.genres);

 //printf("Just Printed: %s\t%s\t%s\t%s\t%s\t%s\t%s\t\n", library->movieInfo.titleOrig, library->movieInfo.title, library->movieInfo.releaseDate, library->movieInfo.acquireDate,
 //	 library->movieInfo.runtimeMinutes, library->movieInfo.mediaType, library->movieInfo.genres);

    saveLog(log, library->left);
    saveLog(log, library->right);
}


node* loadDatabase(node* tree){
  printf("Loading IMDB's movie database...\n");
  FILE * db;
  char line[200];
  db = fopen("movie_records.txt", "r");

  while (fgets(line, sizeof(line), db) != NULL) {
    char * data;
    struct entry movieEntry;
    int counter = 0;
    data = strtok (line,"\t");
    while (data != NULL)
      {
	switch(counter){
	case 0:
	  break;
	case 1:
	  break;
	case 2:
	  strcpy(movieEntry.titleOrig, data);
	  break;
	case 3:
	  strcpy(movieEntry.title, data);
	  strlwr(data);
	  removeArticles(data);
          strcpy(movieEntry.titleMod, data);
	  break;
	case 4:
	  break;
	case 5:
	  strcpy(movieEntry.releaseDate, data);
	  break;
	case 6:
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
    tree = insert(movieEntry, tree);
  }
  printf("The IMDB movie database was loaded!\n");

  fclose(db);

  return tree;

}


struct entry search(node *tree){
  char search[150];
  //getchar();
  scanf("%[^\n]s", search);
  getchar();
  strlwr(search);
  removeArticles(search);
  struct entry movieSearch = find(search, tree);
  
  return movieSearch;
}

struct node* searchNode(node *library){

  char search[150];
  scanf("%[^\n]s", search);
  getchar();
  strlwr(search);
  removeArticles(search);
  struct node* t = findNode(search, library);
  
  return t;
}


node* loadUserLibrary(FILE *log, node *library){
  printf("\nLoading your movie library...\n");
  char line[200];  
  while(fgets(line, sizeof(line), log) != NULL){
  char * data;
  struct entry movieEntry;
  int counter = 0;
  data = strtok (line,"\t"); 
  while (data != NULL)
   {
     //printf("data = %s\n", data);
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
	break;
      case 3:
	strcpy(movieEntry.acquireDate, data);
	break;
      case 4:
	strcpy(movieEntry.runtimeMinutes, data);
	break;
      case 5:
	strcpy(movieEntry.mediaType, data);
	break;
      case 6:
	strcpy(movieEntry.genres, data);
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"
#include "utilityFunctions.h"



struct entry search(node *tree){
  char search[150];
  //getchar();
  struct entry movieSearch = {0};
  scanf("%150[^\n]s", search);
  flush();
  if (strcmp(search, "!") == 0)
    return movieSearch;
  //getchar();
  strlwr(search);
  removeArticles(search);
  movieSearch = find(search, tree);
  //while (strcmp(movieSearch.title, "") == 0 && strcmp(search, "!") != 0){
  //  scanf("%150[^\n]s", search);
  //  flush();
    //getchar();
  //  strlwr(search);
  //  removeArticles(search);
  //  movieSearch = find(search, tree);
  // }
  return movieSearch;
}


struct node* searchNode(node *library){

  char search[150];
  //struct node* t = {0};
  struct node* t = {0};
  scanf("%150[^\n]s", search);
  flush();
  if (strcmp(search, "!") == 0)
    return t;
  //getchar();
  strlwr(search);
  removeArticles(search);
  t = findNode(search, library);
  while(t == NULL && strcmp(search, "!")){
    scanf("%150[^\n]s", search);
    flush();
    //getchar();
    strlwr(search);
    removeArticles(search);
    t = findNode(search, library);
  }
  return t;
}

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
}

void printNode(entry movie){
    printf("\nTitle: %s\n\tRelease Date: %s\n\tRuntime (m): %s\n\tMedia Type: %s\n\tDate Acquired: %s\n\n", movie.title, movie.releaseDate, movie.runtimeMinutes, movie.mediaType, movie.acquireDate);
    return;
}



int commandFormatIsCorrect(char state[]){
  if (state[1] == '\0'){
    return 1;
  }else {
    printf("Invalid format. Please enter the command as a single character.\n");
    return 0;
  }
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
  if (library == NULL)
    printf("Library was null after insertions\n");
  printf("Your movie library was loaded!\n\n");
  return library;
}

void flush(){

  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  
  return;
}

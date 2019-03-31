#ifndef UTILITYFUNCTIONS_H_
#define UTILITYFUNCTIONS_H_

//This header file defines all of the miscellaneous functions that aren't CRUD-related or AVL tree-related

node* createTree(FILE*, node*);
void saveLog(FILE*, node*);
void helpMsg(char*);
int commandFormatIsCorrect(char*);
void removeArticles(char*);
void printMovie(entry);
entry search(node*);
node* searchNode(node*);
void flush();

#endif

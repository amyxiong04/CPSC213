#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void notString(element_t* rv, element_t str) {
  char* string = (char*) str;
  char *endp;
  int** r = (int**) rv;
  /* strtol returns a pointer to the first non-numeric character in endp.
     If it gets to the end of the string, that character will be the null terminator. */
  int value = strtol(string, &endp, 10);
  if (*r == NULL)
    *r = malloc(sizeof(int));
  if(string[0] != '\0' && endp[0] == '\0') {
    /* String was non-empty and strtol conversion succeeded - integer */
    **r = value;
  } else {
    **r = -1;
  }
}

void notInt(element_t* rv, element_t str0, element_t str1) {
    char** r = (char**) rv;
    char* string = (char*) str1;
    int* num = (int*) str0;
    if (*num == -1) {
        *r = string;
    } else {
        *r = NULL;
    }
}

int notNegativeOne(element_t av) {
    int *a = av;
    return *a != -1;
}

int notNull(element_t av) {
    char *a = (char*) av;
    return a != NULL;
}

void shorten(element_t* rv, element_t str0, element_t str1) {
    char** r = (char**) rv;
    char* string = (char*) str0;
    int* len = (int*) str1;

    if (*r == NULL)
        *r = malloc((*len + 1) * sizeof(char));
    for (int i = 0; i < *len; i++) {
        (*r)[i] = string[i];
    }
    (*r)[*len] = '\0';
}

void printStr (element_t ev) {
  char* e = (char*) ev;
  if (e != NULL) {
    printf ("%s\n", e);
  } else {
    printf("was int\n");
  }
}

void max(element_t* rv, element_t av, element_t bv) {
    int *a = av, *b = bv, **r = (int**) rv;
  if (*r == NULL)
    *r = malloc(sizeof(int));
  if (*a > *b) {
    **r = *a;
  } else {
    **r = *b;
  }
}

void concatenate(element_t* rv,  element_t av, element_t bv) {
    char* curr = *((char**)av);
    char* next = bv;
    char*** currPointer = ((char***) rv);
    char** currVal = *currPointer;

    if (curr == NULL) {
        curr = malloc(sizeof(char));
    }
    strcat(curr, next);
    strcat(curr, " ");
}


int main(int argc, char **argv) {

  struct list* argsList = list_create();
  for (int i=0; i<argc-1; i++) {
    char * pEnd;
    element_t e = malloc(strlen(argv[i+1])*sizeof(e)); 
    memcpy(e, argv[i+1], strlen(argv[i+1])+1);
    list_append(argsList, e);
  }
  
  struct list* numList = list_create();
  list_map1(notString, numList, argsList);

  struct list* stringList = list_create();
  list_map2(notInt, stringList, numList, argsList);

  struct list* intsList = list_create();
  list_filter(notNegativeOne, intsList, numList);

  struct list* stringsList = list_create();
  list_filter(notNull, stringsList, stringList);

  struct list* shortenedList = list_create();
  list_map2(shorten, shortenedList, stringsList, intsList);

  int s = 0, *sp = &s;
  list_foldl (max, (element_t*) &sp, intsList);
  
  char* d = malloc(sizeof(*d)* 1000);
  char **dp = &d;
  list_foldl(concatenate, (element_t*) &dp, shortenedList);

  list_foreach(printStr, shortenedList);
  printf("%s\n", d);
  printf("%i\n", s);

  list_foreach(free, argsList);
  list_foreach (free, shortenedList);  // free elements allocated by add in map2
  list_foreach (free, numList);  // free elements allocated by add in map2

  list_destroy(argsList);
  list_destroy(numList);
  list_destroy(stringList);
  list_destroy(intsList);
  list_destroy(stringsList);
  list_destroy(shortenedList);
  free(d);
}

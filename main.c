#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "helpers.c"
#include "finder.c"
#include "okml.h"



void print_tree(okml_array* arr, int x){
  int N = arr->count;
  for (int i = 0; i < N; ++i) {
    okml* cur = arr->items[i];
    if(cur == NULL){
      return;
    }

    if(cur->key == NULL){
      return;
    }
    for(int i =0; i<=x;i++){
      printf("\t");
    }
    printf("key %s | type %s\n", cur->key, cur->type);
    if(cur->type != NULL && strcmp(cur->type, "list") == 0){
      print_tree(cur->child_list, x+1);
    }
  }
  printf("\n");
}

okml_array* okml_load(char* filename){
  okml_array* arr = okml_array_create();
  FILE* file = fopen(filename, "r");
  char line[256];
  if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {

	  if(has_char(line,':')){
	    find_key_value(line,arr);
	  }
	  
	  if(has_char(line, '{')){
	    char* key = get_name(line, "{");
	    remove_whitespace(key);
	    find_child(file,arr, key);
	  }
        }
        fclose(file);
  }
  else {
      fprintf(stderr, "Unable to open file!\n");
    }
  
  return arr;
}

void okml_find(okml_array* arr,  char* key){
  if (!arr || !arr->items) return;
  int N = arr->count;
  for (int i = 0; i < N; ++i) {
    okml *it = arr->items[i];
    if (!it) continue;

    if (it->key && strcmp(it->key, key) == 0) {
      if (it->type && strcmp(it->type, "string") == 0 && it->val_string) {
        printf("%s\n", it->val_string);
      } else if (it->type && strcmp(it->type, "bool") == 0) {
        printf("%s\n", it->val_bool ? "true" : "false");
      } else if (it->type && strcmp(it->type, "int") == 0) {
        printf("%d\n", it->val_int);
      }
      return;
    }

    if (it->type && strcmp(it->type, "list") == 0 && it->child_list) {
      okml_find(it->child_list, key);
    }
  }
}



int main(int argc, char *argv[])
{

  if(argc > 1){
    printf("[IO] opening file %s\n\n", argv[1]);
  } 

  okml_array* okml = okml_load(argv[1]);
  okml_find(okml, "this_has");
  okml_find(okml, "baz");
  return 0;
}



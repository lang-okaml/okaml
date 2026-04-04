#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "okml.h"


bool find_key_value(char* line, okml* arr){

  okml* parsed_data;
  
  
  bool found = false;
  int len = strlen(line);
  char* ss = malloc(sizeof(char) * len);

  for (int i = 0; i < len; ++i) {
    if(line[i] == ':'){
      found = true;
      strncpy(ss, line, i);
      char* key = (strdup(ss));

      remove_whitespace(key);
      parsed_data->key = key;

      parse_line(parsed_data,strncpy(ss, line+i+1, len));
      
      printf("%s -> ", parsed_data->key );
      if(parsed_data->val_string != NULL){
	printf("%s", parsed_data->val_string);
      } else {
	printf("%b", parsed_data->val_bool );
      }
      printf(" || Type -> %s\n", parsed_data->type);
    }
  }

  okml_array_push(arr, parsed_data);
  return found;
}

bool has_char(char* line, char delim) {
    return strchr(line, delim) != NULL;
}

FILE* find_child(FILE* file, okml* root) {
  okml child_new;
  char line[256];

  /* Read the File line by line */
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';

    /* CHECK FOR NESTED LISTS */
    if (has_char(line, '{')) {
      find_child(file, &child_new);
    }

    /* EXIT IF NEST END */
    if (has_char(line, '}')) {
      return file;
    }

    /* Send the line to find the key-value pair */
    find_key_value(line, child_new);
  
  }
  return file;
}


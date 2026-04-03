#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "typecheck.c"
#include "helpers.c"

typedef struct okml {
  char* key;
  char* type;
  
  char* val_string;
  int val_int;
  bool val_bool;
  
  struct okml* children;
} okml;

okml pair;

void parse(char* filename){
  FILE* file = fopen(filename, "r");
  char line[256];
  if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
	  find_key_value(line,pair);
        }
        fclose(file);
    }
    else {
        fprintf(stderr, "Unable to open file!\n");
    }
}

int main()
{

  parse("syntax.okml");
  return 0;
}


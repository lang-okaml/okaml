#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "okml.h"

void remove_whitespace(char *str) {
    char *read = str;
    char *write = str;
    
    while (*read) {
        if (!isspace((unsigned char)*read)) {
            *write = *read;
            write++;
        }
        read++;
    }
    *write = '\0';
}

void parse_line(okml* node, const char* line) {
    if (node == NULL || line == NULL) return;
    
    // Trim whitespace
    while (isspace((unsigned char)*line)) line++;
    if (*line == '\0') {
        node->val_string = NULL;
        return;
    }
    
    const char* end = line + strlen(line) - 1;
    while (end > line && isspace((unsigned char)*end)) end--;
    
    int len = end - line + 1;
    char* trimmed = (char*)malloc(len + 1);
    strncpy(trimmed, line, len);
    trimmed[len] = '\0';
        
    // Default: treat as string

    node->val_string = trimmed; // trimmed will be freed elsewhere
}


bool has_char(char* line, char delim) {
  if(delim == '`') return strstr(line, "```") != NULL;
  return strchr(line, delim) != NULL;
}



char* get_name(const char* str, const char* delim) {
    char* copy = strdup(str);           // Copy to modifiable memory
    if (!copy) return NULL;
    
    char* token = strtok(copy, delim);  // Get first token
    char* result = token ? strdup(token) : NULL;  // Duplicate token
    
    free(copy);  // Free the copy
    return result;  // Return the token (caller must free)
}

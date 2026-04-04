// okml.c
#include "okml.h"
#include <stdlib.h>
#include <string.h>

okml_array* okml_array_create(void) {
    okml_array* arr = (okml_array*)malloc(sizeof(okml_array));
    if (!arr) return NULL;
    
    arr->count = 0;
    arr->capacity = 4;
    arr->items = (okml**)malloc(sizeof(okml*) * arr->capacity);
    
    if (!arr->items) {
        free(arr);
        return NULL;
    }
    
    return arr;
}

void okml_array_push(okml_array* arr, okml* element) {
    if (!arr) return;
    
    if (arr->count >= arr->capacity) {
        arr->capacity *= 2;
        arr->items = (okml**)realloc(arr->items, sizeof(okml*) * arr->capacity);
    }
    arr->items[arr->count++] = element;
}

okml* okml_array_get(okml_array* arr, size_t index) {
    if (!arr || index >= arr->count) return NULL;
    return arr->items[index];
}

void okml_array_pop(okml_array* arr) {
    if (arr && arr->count > 0) {
        arr->count--;
    }
}

void okml_array_remove_at(okml_array* arr, size_t index) {
    if (!arr || index >= arr->count) return;
    
    for (size_t i = index; i < arr->count - 1; i++) {
        arr->items[i] = arr->items[i + 1];
    }
    arr->count--;
}

void okml_array_free(okml_array* arr) {
    if (arr) {
        free(arr->items);
        free(arr);
    }
}

okml* okml_create_node(void) {
    return (okml*)calloc(1, sizeof(okml));
}

void okml_free_node(okml* node) {
    if (!node) return;
    
    free(node->key);
    free(node->type);
    free(node->val_string);
    
    // Free children
    for (size_t i = 0; i < node->children_count; i++) {
        okml_free_node(node->child[i]);
    }
    free(node->child);
    
    free(node);
}

void okml_add_child(okml* parent, okml* child) {
    if (!parent || !child) return;
    
    if (parent->children_count >= parent->children_capacity) {
        parent->children_capacity = parent->children_capacity == 0 ? 4 : parent->children_capacity * 2;
        parent->child = (okml**)realloc(parent->child, sizeof(okml*) * parent->children_capacity);
    }
    parent->child[parent->children_count++] = child;
}

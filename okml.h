typedef struct okml {
  char* key;
  char* type;
  
  char* val_string;
  int val_int;
  bool val_bool;
  
  struct okml* children;
} okml;

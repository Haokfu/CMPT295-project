#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <table_string.h>
#include <vector_char.h>
int main(int argc, char **argv) {
  char *source = NULL;

  if (argc != 2) {
    printf("./wordcount.bin [FILE PATH]");
    exit(1);
  }
  /**
   * @brief Read file into source.
   * source is a character array with file contents
   * It is null terminated
   */
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) { /* Error */
    printf("Error reading file");
    exit(1);
  }
  if (fp != NULL) {
    /* Go to the end of the file. */
    if (fseek(fp, 0L, SEEK_END) == 0) {
      /* Get the size of the file. */
      long bufsize = ftell(fp);
      if (bufsize == -1) { /* Error */
        printf("Error reading file");
      }
      /* Allocate our buffer to that size. */
      source = malloc(sizeof(char) * (bufsize + 1));
      /* Go back to the start of the file. */
      if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */
      }
      /* Read the entire file into memory. */
      size_t newLen = fread(source, sizeof(char), bufsize, fp);
      if (ferror(fp) != 0) {
        printf("Error reading file");
      } else {
        source[newLen++] = '\0'; /* Just to be safe. */
      }
    }
  }
  fclose(fp);

  /** Start processing file and separate into words */
  table_string *ts = table_string_allocate(2);
  vector_char_t *v_c = vector_char_allocate();
  int line_num = 1;
  for(int i=0; source[i] != '\0'; i++){
    if(source[i] >= 65 && source[i] <= 122){
      vector_char_add(v_c,source[i]);
    }
    else{
      if(v_c->len != 0){ 
        vector_char_add(v_c,'\0');
        char* token = vector_char_get_array(v_c);
        table_string_insert_or_add(ts,token,line_num);
        vector_char_delete(v_c);
        v_c = vector_char_allocate();
      }
      if(source[i] == '\n') line_num++;
    }
  }
  table_string_print(ts);
  table_string_deallocate(ts);
  vector_char_delete(v_c);
  free(source);
  // TODO: Write linecount
  return 0;
}
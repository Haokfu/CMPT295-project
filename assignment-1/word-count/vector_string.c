#include "vector_string.h"
#include "str_cmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
/////////////////////////////////////////

*/
/**
 * @brief Memory allocate a vector string so that we can start inserting entries
 * into it.
 *
 */
vector_string *vector_string_allocate() {
  vector_string* v_s = (vector_string*)malloc(sizeof(vector_string));
  //for safety
  v_s->head = NULL;
  v_s->tail = NULL;
  return v_s;
}

/**
 * @brief Search the vector string pointed to by vs and return true if the
 * vs_entry.value == key, else return false.
 * TODO:
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */


bool vector_string_find(vector_string *vs, char *key) { 
  //check if head of vs is null?
  if(!vs->head) return false;
  vs_entry_t *it_start = vs->head;
  vs_entry_t *it_end = vs->tail;
  vs_entry_t *it = it_start;
  while(it != it_end){
    if(!my_str_cmp(it->value, key)) return true;
    else it = it->next;
  }
  if(!my_str_cmp(it_end->value, key)) return true;
  else return false;

  
  
  
  return true; 
  
}

/**
 * @brief TODO: Insert the string pointed to by key into the vector string.
 *  char* is externally allocated. You do not have to allocate internally
 *
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
void vector_string_insert(vector_string *vs, char *key) {
  // Insert the string into the tail of the list.
  //create a vs_entry
  vs_entry_t *data = (vs_entry_t*)malloc(sizeof(vs_entry_t));
  //copy key into data->value
  int key_len = 0;
  for(int i=0; key[i] != '\0'; i++) key_len++;
  data->value = (char*)malloc(sizeof(char) * (key_len+1));
  for(int i=0; i<key_len; i++) data->value[i] = key[i];
  data->value[key_len] = '\0';
  ////
  data->next = NULL;
  //now import data to tail 
  //if there is vs_entry in string:
  if(vs->tail){
    vs->tail->next = data;
    vs->tail = data;
  }
  //if not:
  else{
    vs->head = data;
    vs->tail = data;
  }

}
/**
 * @brief Remove all entries and cleanup vector string
 * TODO: Remove all entries. Remember head and tail are pointers.
 * Remember to remove vs as well; not just entries. or you will have memory
 * leaks.
 * @param vs: Pointer to vector_string struct
 */
void vector_string_deallocate(vector_string *vs) {
  //check if vs has value
  if(vs){
    //get head and tail
    vs_entry_t *it_head = vs->head;
    vs_entry_t *it_tail = vs->tail;
    vs_entry_t *it = it_head;
    while(it != it_tail){
      if(it->value) free(it->value);
      it = it->next;
      free(it_head);
      it_head = it;
    }
    //when it == it_tail
    if(it_tail->value)free(it_tail->value);
    free(it_tail);
  }
  free(vs);
}

/**
 * @brief Print all value in each entry of the vector string, in the following
 * format. In this case hello and world are the unique words in the file.
 * 1. hello
 * 2. world
 * @param vs
 */
void vector_string_print(vector_string *vs) {

  int count = 0;
  vs_entry_t *it = vs->head;
  while(it != NULL){
    count++;
    printf("%d. %s\n", count, it->value);
    it = it->next;
  }
}
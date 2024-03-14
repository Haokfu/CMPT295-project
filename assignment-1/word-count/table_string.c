#include "table_string.h"
#include "str_cmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS
// DO NOT ADD ANY NEW FUNCTIONS BEFORE djb2
// Hash a character array to integer value between 0 and buckets-1.
// See here for more details: https://theartincode.stanis.me/008-djb2/
unsigned int djb2_word_to_bucket(char *word, int buckets) {
  if (!word) {
    printf("Invoked with null string");
    exit(EXIT_FAILURE);
  }
  unsigned long hash = 5381;
  uint32_t i;

  for (i = 0; i < strlen(word); i++)
    hash = ((hash << 5) + hash) + word[i];

  return hash & (buckets - 1);
}
// ADD YOUR HELPER FUNCTIONS AFTER djb2
/**
 * @brief Instantiate a table string
 *
 * @param buckets
 * @return table_string*
 */
table_string *table_string_allocate(unsigned int buckets) {
  // Instantiate a bucket number of heads
  table_string *ts = (table_string*)malloc(sizeof(table_string));
  ts->buckets = 8;
  ts->heads = (vs_entry_t**)malloc(sizeof(vs_entry_t*) * 8);
  for(int i=0; i<8; i++){
    ts->heads[i] = NULL;
  }

  return ts;
}

/**
 * @brief Insert the string pointed to by word into the table string.
 *   If word is already found increment count.
 *   If word is not found insert at the end of the corresponding bucket
 * @param ts - Pointer to table_string datastructure
 * @param word - Pointer to string to search for
 * @return * Find*
 */
void table_string_insert_or_add(table_string *ts, char *word, int line) {
  // Find the bucket for word. djb2 will return a value between 0-buckets-1.
  // Rule: buckets can only be power of 2.
  int bucket = djb2_word_to_bucket(word, ts->buckets);
  int word_len = 0;
  for(int i=0; word[i] != '\0'; i++) word_len++;

  // TODO:
  // Case head == NULL: bucket hasn't been initialized yet
  if(!ts->heads[bucket]){
    ts->heads[bucket] = (vs_entry_t*)malloc(sizeof(vs_entry_t));
    ts->heads[bucket]->value = (char*)malloc(sizeof(char) * (word_len+1));
    for(int i=0; word[i] != '\0'; i++) ts->heads[bucket]->value[i] = word[i];
    ts->heads[bucket]->value[word_len] = '\0';
    ts->heads[bucket]->size_of_lines = 1;
    ts->heads[bucket]->lines = malloc(sizeof(int));
    ts->heads[bucket]->lines[0] = line;
    ts->heads[bucket]->next = NULL;
  }
  
  else{
    bool is_found = false;
    vs_entry_t* track = ts->heads[bucket];
    while(track->next){
      // Case word already in list, add to line array.
      if(!my_str_cmp(track->value, word)){
        //realloc lines with new size +1
        track->size_of_lines++;
        track->lines = realloc(track->lines, sizeof(int) * track->size_of_lines);
        track->lines[track->size_of_lines-1] = line;
        is_found = true;
        break;
      }
      track = track->next;
    }
  // Case word not found, insert word and return.
    if(!is_found){
      if(!my_str_cmp(track->value,word)){
        track->size_of_lines++;
        track->lines = realloc(track->lines, sizeof(int) * track->size_of_lines);
        track->lines[track->size_of_lines-1] = line;
      }
      else{
        track->next = (vs_entry_t*)malloc(sizeof(vs_entry_t));
        track = track->next;
        track->value = (char*)malloc(sizeof(char) * (word_len+1));
        for(int i=0; word[i] != '\0'; i++) track->value[i] = word[i];
        track->value[word_len] = '\0';
        track->lines = (int*)malloc(sizeof(int));
        track->lines[0] = line;
        track->size_of_lines = 1;
        track->next = NULL;
      }
    }
  }
}

void table_string_deallocate(table_string *ts) {
  // TODO:
    vs_entry_t *track = NULL;
    vs_entry_t *parent = NULL;
  // Free the linked list of each bucket
  for(int i=0; i<ts->buckets; i++){
    track = ts->heads[i];
    while(track){
      parent = track;
      free(track->value);
      free(track->lines);
      track->size_of_lines = 0;
      track = track->next;
      free(parent);
    }
  }
  
  // Free the array of head pointers
  free(ts->heads);
  // Free the structure itself
  free(ts);
  return;
}

void table_string_print(table_string *ts) {
  /** TODO:
   for each bucket
   
    for each entry in bucket
      print entry->word: line line line
  */
  vs_entry_t *track = NULL;
  for(int i=0; i<ts->buckets; i++){
    track = ts->heads[i];
    while(track){
      printf("%s: ", track->value);
      for(int j = 0; j< track->size_of_lines; j++){
        printf("%d ", track->lines[j]);
      }
      printf("\n");
      track = track->next;
    }
  }
}

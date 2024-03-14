#include "str_cmp.h"

/**
 * @brief Compare two strings
 *
 * @param s1
 * @param s2
 * @return int
 */
int my_str_cmp(const char *s1, const char *s2) {
  // TODO: Compare two character arrays. return 0 if they match, 1 otherwise
  // You can assume that s1 and s2 are null terminated strings.
  // WARNING: strings could potentially be of different lengths
  // e.g., "apple" does not match "apple " (which includes the extra space).
  // Value to be returned will be 1.
  // You cannot use any of the string helper functions including strlen and
  // strncmp, strcmp.

  //get strlen of s1
  int s1_len = 0;
  for(int i=0; s1[i] != '\0'; i++){
    s1_len ++;
  }
  //get strlen of s2
  int s2_len = 0; 
  for(int i=0; s2[i] != '\0'; i++){
    s2_len++;
  }
  //1. check if two len are equal
  if(s1_len != s2_len){
    return 1;
  }
  //2. reaching here, two length are equal
  //go over two strings to check chars are equal
  for(int i=0; i<s1_len; i++){
    if(s1[i] != s2[i]){
      return 1;
    }
  }
  //when getting out of loop, two strings are equal
  return 0;

}

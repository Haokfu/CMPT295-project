#include "dogfault.h"
#include "print.h"
#include <assert.h>
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Line {
  unsigned long long block;
  short valid;
  unsigned long long tag;
  int lru_clock;
} Line;

typedef struct Set {
  Line *lines;
  int lru_clock;
} Set;

typedef struct Cache {

  // Parameters
  int setBits;     // s
  int linesPerSet; // E
  int blockBits;   // k

  // Core data structure
  Set *sets;

  // Cache statistics
  int eviction_count;
  int hit_count;
  int miss_count;

  // Used for verbose prints
  short displayTrace;
} Cache;

/**
 * @brief Return the tag of the address
 *
 * @param address
 * @param cache
 * @return unsigned long long
 */
unsigned long long cache_tag(const unsigned long long address,
                             const Cache *cache) {
  // TODO:
  unsigned long long tag;
  int s = cache->setBits;
  int b = cache->blockBits;
  tag = address >> (s+b);
  return tag;
}

/**
 * @brief return the set index of the address
 *
 * @param address
 * @param cache
 * @return unsigned long long
 */
unsigned long long cache_set(const unsigned long long address,
                             const Cache *cache) {
  // TODO:
  unsigned long long set;
  int s = cache->setBits;
  int b = cache->blockBits;
  unsigned long long temp = address >> b;
  set = temp & ((1<<s)-1);
  return set;
}

/**
 * @brief Check if the block of the address is in the cache.
 *  If yes, return true. Else return false
 * @param address
 * @param cache
 * @return true
 * @return false
 */
bool probe_cache(const unsigned long long address, const Cache *cache) {
  /*
   TODO: 1. calculate tag and set values
         2. Iterate over all lines in set
         3. If line is valid and tag matches return true
         4. Set lru clock
  */
  unsigned long long tag = cache_tag(address,cache);
  unsigned long long set_index = cache_set(address,cache);
  Set* target_set = &(cache->sets[set_index]);
  int num = cache->linesPerSet;
  for(int i=0; i<num; i++){
    if(target_set->lines[i].valid && target_set->lines[i].tag == tag){
      target_set->lines->lru_clock ++;
      target_set->lru_clock++;
      return true;
    }
  }
  return false;
}

/**
 * @brief Insert block in cache
 *
 * @param address
 * @param cache
 */
void allocate_cache(const unsigned long long address, const Cache *cache) {
  /*
 TODO: 1. calculate tag and set values
       2. Iterate over all lines in set and find empty set.
       3. Insert block. If you do not find an empty block panic as this method
 will always be called in conjunction with avail_cache which verifies there is
 space.
       4. Set lru clock
*/
  int s = cache->blockBits;
  int b = cache->setBits;
  unsigned long long tag = cache_tag(address,cache);
  unsigned long long set_index = cache_set(address,cache);
  Set* target_set =&(cache->sets[set_index]);
  int num = cache->linesPerSet;
  int index = 0;
  while(index < num){
    if(!target_set->lines[index].valid){
      target_set->lines[index].tag = tag;
      target_set->lines[index].block = address & ((1 << s) - 1);
      target_set->lines[index].valid = 1;
      target_set->lines[index].lru_clock = 1;
      target_set->lru_clock ++;
      return;
    }
    index++;
  }
  assert("fail to find empty set");
}

/**
 * @brief Check if empty way available. if yes, return true, else return false.
 *
 * @param address
 * @param cache
 * @return true
 * @return false
 */
bool avail_cache(const unsigned long long address, const Cache *cache) {

  /*
TODO: 1. calculate tag and set values
     2. Iterate over all lines in set and find empty set.
     3. Insert block. If you do find an empty block return true;
     4. If you did not find empty block return false.
*/
  int s = cache->blockBits;
  int b = cache->setBits;
  unsigned long long tag = cache_tag(address,cache);
  unsigned long long set_index = cache_set(address,cache);
  Set* target_set = &cache->sets[set_index];
  int num = cache->linesPerSet;
  int index = 0;
  while(index < num){
    if(!target_set->lines[index].valid){
      return true;
    }
    index++;
  }
  return false;
}

/**
 * @brief Find the victim line to be removed from the set
 *      if you run out of space. Return the index/way of the block
 * @param address
 * @param cache
 * @return unsigned long long
 */
unsigned long long victim_cache(const unsigned long long address,
                                Cache *cache) {

  /*
TODO: 1. calculate tag and set values
     2. Iterate over all lines in set and sort them based on lru clock.
     3. Return the way/index of the block with the smallest lru clock
*/
  int s = cache->blockBits;
  int b = cache->setBits;
  unsigned long long tag = cache_tag(address,cache);
  unsigned long long set_index = cache_set(address,cache);
  Set* target_set = &cache->sets[set_index];
  int num = cache->linesPerSet;
  int index = 0;
  int min = 10000;
  int store_index;
  while(index < num){
    if(target_set->lines[index].valid){
      if(min>target_set->lines[index].lru_clock){
        min = target_set->lines[index].lru_clock;
        store_index=index;
      } 
    }
    index++;
  }
  return store_index;

}

/**
 * @brief Remove/Invalidate the cache block in corresponding set and way.
 *
 * @param address
 * @param index
 * @param cache
 */
void evict_cache(const unsigned long long address, int index, Cache *cache) {

  // TODO:
   int s = cache->blockBits;
  int b = cache->setBits;
  unsigned long long tag = cache_tag(address,cache);
  unsigned long long set_index = cache_set(address,cache);
  Set target_set = cache->sets[set_index];
  //find index
  Line *victim = &target_set.lines[index];
  victim->valid = 0;
}

/**
 * @brief Invoked for each memnory access in the memory trace.
 *
 * @param address
 * @param cache
 */
void operateCache(const unsigned long long address, Cache *cache) {

  /** TODO:
   * Use the method above to run the cache.
   * To ensure that your results match against the reference simulator.
   * We provide you the statements to print in each condition. Use them.
   * You should display them only when displayTrace is activated
   */
    bool h = probe_cache(address,cache);
    bool m = false;
    bool m_e = false;
    
    if(!h){
      //check if there is empty sets
      if((m = avail_cache(address, cache)) == true) allocate_cache(address, cache);
      else{
        int index = victim_cache(address, cache);//find victim index
        evict_cache(address, index, cache);
        allocate_cache(address, cache);
        m_e = true;
      }
    }
  if (cache->displayTrace){
    // If access hit in the cache
    if(h == true){
      cache->hit_count++;
      printf(" hit ");
    }
  // If access misses in the cache and we needed to evict an entry to insert the
  // block.
    else if(m_e == true){
      cache->eviction_count++;
      cache->miss_count++;
      printf(" miss eviction ");
    }
  // If access misses in the cache we did not
    else if(m == true){
      cache->miss_count++;
      printf(" miss ");
    }
  }
  return;
}

// DO NOT MODIFY LINES HERE. OTHERWISE YOUR PROGRAM WILL FAIL
// get the input from the file and call operateCache function to see if the
// address is in the cache.
void operateFlags(char *traceFile, Cache *cache) {
  FILE *input = fopen(traceFile, "r");
  int size;
  char operation;
  unsigned long long address;
  while (fscanf(input, " %c %llx,%d", &operation, &address, &size) == 3) {
    if (cache->displayTrace)
      printf("%c %llx,%d", operation, address, size);

    switch (operation) {
    case 'M':
      operateCache(address, cache);
      // Incrementing hit_count here to account for secondary access in M.
      cache->hit_count++;
      if (cache->displayTrace)
        printf("hit ");
      break;
    case 'L':
      operateCache(address, cache);
      break;
    case 'S':
      operateCache(address, cache);
      break;
    }
    if (cache->displayTrace)
      printf("\n");
  }
  fclose(input);
}

/**
 * @brief Initialize the cache. Allocate the data structures on heap and return
 * ptr.
 *
 * @param cache
 */
void cacheSetUp(Cache *cache) {
  // TODO:
  int S = pow(2,cache->setBits);
  cache->sets = (Set*)malloc(S * sizeof(Set));
  int l = cache->linesPerSet;
  for(int i=0; i<S; i++){
    cache->sets[i].lru_clock = 0;
    cache->sets[i].lines = (Line*)malloc(l * sizeof(Line));
    for(int j=0; j<l; j++){
      cache->sets[i].lines[j].valid = 0;
    }
  }
  cache->hit_count = 0;
  cache->miss_count = 0;
  cache->eviction_count = 0;
}

/** Free up cache memory */
void deallocate(Cache *cache) {
  // TODO:
  int S = pow(2,cache->setBits);
  for(int i=0; i<S ; i++){
    free(cache->sets[i].lines);
  }
  free(cache->sets);
}

int main(int argc, char *argv[]) {
  Cache cache;

  opterr = 0;
  cache.displayTrace = 0;
  int option = 0;
  char *traceFile;
  // accepting command-line options
  // "assistance from"
  // https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt
  while ((option = getopt(argc, argv, "s:E:b:t:LFv")) != -1) {
    switch (option) {
    // select the number of set bits (i.e., use S = 2s sets)
    case 's':
      cache.setBits = atoi(optarg);
      break;
    // select the number of lines per set (associativity)
    case 'E':
      cache.linesPerSet = atoi(optarg);
      break;
    // select the number of block bits (i.e., use B = 2b bytes / block)
    case 'b':
      cache.blockBits = atoi(optarg);
      break;
    case 't':
      traceFile = optarg;
      break;
    case 'v':
      cache.displayTrace = 1;
      break;
    }
  }
  // initializes the cache
  cacheSetUp(&cache);
  // check the flag and call appropriate function
  operateFlags(traceFile, &cache);
  // prints the summary
  printSummary(cache.hit_count, cache.miss_count, cache.eviction_count);
  // deallocates the memory
  deallocate(&cache);
  return 0;
}

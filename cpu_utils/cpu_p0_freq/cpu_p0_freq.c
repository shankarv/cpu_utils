/*****************************************************************
 * Calculate the PState P0 frequency of current Intel/AMD 64-bit
 * processors using RDTSCP 
 * This works for CPUs that support rdtscp and constant_tsc flags
 * in CPUID (see /proc/cpuinfo in Linux)
 *
 * Author: Shankar Viswanathan
 *
 ****************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long long int 	uint64_t;
uint64_t get_rdtscp(void);

// Call RDTSCP instruction as inline assembly
// Return 64-bit counter value
inline uint64_t get_rdtscp(void) {
  unsigned int lo, hi;
  asm volatile (
     "rdtscp"
     : "=a"(lo), "=d"(hi)); /* outputs */
  return ((uint64_t)lo) | (((uint64_t)hi) << 32);
}

int main(int argc, char* argv[]) {
  uint64_t start, end, delta, delta_strm;
  unsigned int sl_time, sl_ret;   // argument and return of sleep() call

  // We expect one argument which is the number of seconds that we
  // should sleep for. Total RDTSC ticks is counted over this interval
  if (2 != argc) {
    printf("Usage: %s <seconds to sleep> \n", argv[0]);
    exit(-1);
  } else {
    sl_time = strtol(argv[1], NULL, 0);
    if (0 >= sl_time) {
      printf("Argument to sleep(): %d should be greater than 0\n", sl_time);
      exit(-1);
    }
  }

  start = get_rdtscp();
  sl_ret = sleep(sl_time);
  end = get_rdtscp();

  if (0 == sl_ret) {
    delta = end - start;
    printf("Time Delta %d seconds =  %llu ticks. Ticks per second = %llu\n", sl_time, delta, (uint64_t) delta/sl_time);
  } else {
    printf("sleep() function returned %d\n", sl_ret);
    exit(-1);
  }

  exit(0);
}
  

  
  
  
  
  

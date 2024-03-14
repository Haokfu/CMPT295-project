## ********************FAILED********************

****************************************
## ********************SUCCESS********************
#### *****timeout 60 ./Arraylist/arraylist.bin --verbose*****
 ```Test Test 0:
  Case Add:1-5:
    main.c:90: Check !strcmp(vec->output, output)... ok
  SUCCESS: All conditions have passed.

Test Test 1:
  Case Add:1-3,Insert:100:0-3:
    main.c:127: Check !strcmp(vec->output, output)... ok
  SUCCESS: All conditions have passed.

Test Test 2:
  Case Add:1-5,Insert:100:0-6,Free:
    main.c:60: Check !strcmp(vec->output, output)... ok
  SUCCESS: All conditions have passed.

Summary:
  Count of all unit tests:        3
  Count of run unit tests:        3
  Count of failed unit tests:     0
  Count of skipped unit tests:    0
SUCCESS: All unit tests have passed.


```
#### *****timeout 60 ./word-count/test_strcmp.bin --verbose*****
 ```Test Test:
  test_strcmp.c:24: Check result == test_vectors[i].expected... ok
  test_strcmp.c:24: Check result == test_vectors[i].expected... ok
  test_strcmp.c:24: Check result == test_vectors[i].expected... ok
  test_strcmp.c:24: Check result == test_vectors[i].expected... ok
  test_strcmp.c:24: Check result == test_vectors[i].expected... ok
  SUCCESS: All conditions have passed.

Summary:
  Count of all unit tests:        1
  Count of run unit tests:        1
  Count of failed unit tests:     0
  Count of skipped unit tests:    0
SUCCESS: All unit tests have passed.


```
#### *****timeout 60 ./word-count/tokenize.bin ./word-count/txt/input.txt > ./word-count/out/input.txt.tokenize; diff  ./word-count/out/input.txt.tokenize ./word-count/reference/input.txt.tokenize*****
 ```
```
#### *****timeout 60 ./word-count/dictionary.bin ./word-count/txt/input.txt > ./word-count/out/input.txt.dictionary; diff  ./word-count/out/input.txt.dictionary ./word-count/reference/input.txt.dictionary*****
 ```
```
#### *****timeout 60 ./word-count/linecount.bin ./word-count/txt/input.txt > ./word-count/out/input.txt.linecount; diff  ./word-count/out/input.txt.linecount ./word-count/reference/input.txt.linecount*****
 ```
```
#### *****timeout 240 valgrind --leak-check=full ./word-count/tokenize.bin ./word-count/txt/input.txt*****
 ```==1935== Memcheck, a memory error detector
==1935== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1935== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==1935== Command: ./word-count/tokenize.bin ./word-count/txt/input.txt
==1935== 
==1935== 
==1935== HEAP SUMMARY:
==1935==     in use at exit: 0 bytes in 0 blocks
==1935==   total heap usage: 384 allocs, 384 frees, 11,760 bytes allocated
==1935== 
==1935== All heap blocks were freed -- no leaks are possible
==1935== 
==1935== For counts of detected and suppressed errors, rerun with: -v
==1935== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```
#### *****timeout 240 valgrind --leak-check=full ./word-count/dictionary.bin ./word-count/txt/input.txt*****
 ```==1948== Memcheck, a memory error detector
==1948== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1948== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==1948== Command: ./word-count/dictionary.bin ./word-count/txt/input.txt
==1948== 
==1948== 
==1948== HEAP SUMMARY:
==1948==     in use at exit: 0 bytes in 0 blocks
==1948==   total heap usage: 499 allocs, 499 frees, 13,061 bytes allocated
==1948== 
==1948== All heap blocks were freed -- no leaks are possible
==1948== 
==1948== For counts of detected and suppressed errors, rerun with: -v
==1948== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```
#### *****timeout 240 valgrind --leak-check=full ./word-count/linecount.bin ./word-count/txt/input.txt*****
 ```==1951== Memcheck, a memory error detector
==1951== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1951== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==1951== Command: ./word-count/linecount.bin ./word-count/txt/input.txt
==1951== 
==1951== 
==1951== HEAP SUMMARY:
==1951==     in use at exit: 0 bytes in 0 blocks
==1951==   total heap usage: 576 allocs, 576 frees, 14,445 bytes allocated
==1951== 
==1951== All heap blocks were freed -- no leaks are possible
==1951== 
==1951== For counts of detected and suppressed errors, rerun with: -v
==1951== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```

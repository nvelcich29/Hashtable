# Hashtable
A hashtable data structure designed using the C programming language. 
## Overview
A hashtable data structure was designed using the C programming language. This data structure allows for the dynamic allocation of memory for the data stored in the hashtable structure. The data structure offers all necessary functions to create a hashtable, put values into the hashtable, retrieve values from hashtable, delete values from hashtable, and re-hash the table to a new size. The structure has been tested for functionality as well as tested using Valgrind to verify no memory leaks possible. The hashtable stores it's key/value pairs in "buckets". If two distinct keys are hashed to the same value then the "buckets" are used to create a linked list data structure.

## Usage
In order to use the custom hashtable data structure the hashtable.h header file should be included with an include statement:
```C
#include "hashtable.h"
```
The functions one can use with this hashtable data structure are:
```C
hashtable_t *make_hashtable(unsigned long size);
void  ht_put(hashtable_t *ht, char *key, void *val);
void *ht_get(hashtable_t *ht, char *key);
void  ht_del(hashtable_t *ht, char *key);
void  ht_iter(hashtable_t *ht, int (*f)(char *, void *));
void  ht_rehash(hashtable_t *ht, unsigned long newsize);
void  free_hashtable(hashtable_t *ht);
```
* make_hashtable: Creates a hashtable object of size "size", allocates memory for it, then returns a pointer to that object.
* ht_put: Inserts Key/Value pair into given hashtable.  Will replace value with new value if there is a key match.
* ht_get: Returns a pointer to the value stored in the hashtable under the given key.  Returns NULL if the key is not found.  
* ht_del: Removes a key/value pair from the hashtable and frees it from memory.
* ht_iter: Calls f with all key/value mappings in the hashtable.  Iteration can be terminated early if f returns 0.  
* ht_rehash: Takes a pointer to a hashtable and resizes it to "newsize" rearranging the contentes to match the new size of the hashtable.
* free_hashtable: Frees hashtable and all substructures in memory. 

## Testing
Included are the tests that were used to validate the functionality of the hashtable data structure.  These tests were intended to be performed from a Linux terminal.  The tracefiles are used to test the hashtable and can be tested using make commands "make test{01-06} e.g.:
```
make test01
```
The rtrace files are used to compare the output of the hashtable data structure against the expected output using the command "make diff{01-06}" e.g.:
```
make diff01
```
If there is no output from running this command then the output of the tests matches the expected output, meaning it runs as expected.

Finally, running:
```
make leakcheck
```
Performs a leak check of data structure using Valgrind while running the hashtable through test06.  

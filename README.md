# Hashtable
A hashtable data structure designed using the C programming language. 

A hashtable data structure was designed using the C programming language. This data structure allows for the dynamic allocation of memory for the data stored in the hashtable structure. The data structure offers all necessary functions to create a hashtable, put values into the hashtable, retrieve values from hashtable, delete values from hashtable, and re-hash the table to a new size. The structure has been tested for functionality as well as tested using Valgrind to verify no memory leaks possible. The hashtable stores it's key/value pairs in "buckets". If two distinct keys are hashed to the same value then the "buckets" are used to create a linked list data structure.

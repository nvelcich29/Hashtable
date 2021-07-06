#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include <stdio.h>

void ll_destroy(bucket_t *b,int check);

//Hashes key and returns unsigned long to be used as index to hashtable
unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

//Creates a hashtable object of size 'size' and allocates memory for it. 
hashtable_t *make_hashtable(unsigned long size) {
  hashtable_t *ht = malloc(sizeof(hashtable_t));
  ht->size = size;
  ht->buckets = calloc(sizeof(bucket_t *), size);
  return ht;
}

//Inserts Key/Value Pair into given hashtable
//Will replace value with new value if keys match
void ht_put(hashtable_t *ht, char *key, void *val) {
  unsigned int idx = hash(key) % ht->size;
  bucket_t *c = ht->buckets[idx]; 
  //This while loop looks for matching key in hashtable.
  //If found, the value is updated with value at *val and returns.
  while(c){
  	if(strcmp(c->key,key)==0){
		free(c->val);
		free(c->key);
		c->key=key;
		c->val=val;		
		/*printf(c ? "true":"false");*/
		return;
	}
	c=c->next;
  }
  //If the key value was not found then a new bucket is created, assigned the 
  //given key/value pair, and added to the hash table.  
  bucket_t *b = malloc(sizeof(bucket_t));
  b->key = key;
  b->val = val;
  b->next = ht->buckets[idx];
  ht->buckets[idx] = b;
  return;
}

//Returns value stored in hash table under given key.
//Returns NULL if key not found
void *ht_get(hashtable_t *ht, char *key) {
  unsigned int idx = hash(key) % ht->size;
  bucket_t *b = ht->buckets[idx];
  while (b) {
    if (strcmp(b->key, key) == 0) {
      return b->val;
    }
    b = b->next;
  }
  return NULL;
}

//Calls f with all key/value mappings in the hashtable; iteration can be terminated early if f returns 0
void ht_iter(hashtable_t *ht, int (*f)(char *, void *)) {
  bucket_t *b;
  unsigned long i;
  for (i=0; i<ht->size; i++) {
    b = ht->buckets[i];
    while (b) {
      if (!f(b->key, b->val)) {
        return ; // abort iteration
      }
      b = b->next;
    }
  }
}

//Frees hashtable and all substructures in memory
void free_hashtable(hashtable_t *ht) {
	unsigned long i;
	for(i=0;i<ht->size;i++){
		ll_destroy(ht->buckets[i], 1);
	}
	free(ht->buckets);
	free(ht);
}

//Removes a key/value pair from the hashtable and frees it from memory
void  ht_del(hashtable_t *ht, char *key) {

	unsigned int idx = hash(key) % ht->size;
	bucket_t *b;
	bucket_t *pb=NULL;
	bucket_t *nb;
	b=ht->buckets[idx];
	while(b){
		if(strcmp(b->key,key)==0){
			if(b->next){
				if(pb){			//This is the in between case.
		
					nb=b->next;
					pb->next=nb;
					free(b->val);
					free(b->key);
					free(b);
				}
				else{                  //This is the first bucket case

					
					pb=b->next;
					ht->buckets[idx]=pb;
					free(b->val);
					free(b->key);
					free(b);
					
				}
			}else if(pb){			//This is the last bucket in list case

				ll_destroy(pb->next,1);
				pb->next=NULL;
				
			}else{				//This is the no list case.  

				ll_destroy(ht->buckets[idx],1);
				ht->buckets[idx]=NULL;

			}
			
			break;
		
		}

		//record previous bucket in 'pb' and cycle through linked list
		pb=b;
		b=b->next;
	}
	return;
}

//Frees the buckets from memory.  Uses Recursion to free buckets in a Linked List
//The int check is used to determine if the key/value pair should be made free (check=1)
//or if the key/value pair should not be made free (check=0)
void ll_destroy(bucket_t *b, int check){
	if(b){
		
		ll_destroy(b->next,check);
		if(check){
			free(b->val);
			free(b->key);
		}
		free(b);
		return;
	}
	return;

}

//Takes a pointer to a hashtable and resizes it to 'newsize' rearanging the contents
//to match the new size of the hashtable
void  ht_rehash(hashtable_t *ht, unsigned long newsize) {
	
	hashtable_t *htTemp=make_hashtable(ht->size);
	int i;
	bucket_t *b;
	
	//copy the hash table to be re-hashed into a temporary hashtable
	for(i=0;i<ht->size;i++){
		b=ht->buckets[i];
		if(b){
			do{

				ht_put(htTemp,b->key,b->val);
				b=b->next;

			}while(b);
		}
	}

	//Free ht->buckets and resize ht to newsize
	for(i=0;i<ht->size;i++){
		ll_destroy(ht->buckets[i], 0);
	}
	free(ht->buckets);
	ht->size=newsize;	
	ht->buckets=calloc(sizeof(bucket_t *),newsize);
	
	//load the re-hashed hashtable with it's previously held contents
	for(i=0;i<htTemp->size;i++){
		b=htTemp->buckets[i];
		if(b){
			do{
				ht_put(ht,b->key,b->val);
				b=b->next;
			}while(b);
		}	
	}

	//Free memory of the tempory hashtable htTemp
	for(i=0;i<htTemp->size;i++){
		ll_destroy(htTemp->buckets[i], 0);
	}
	free(htTemp->buckets);
	free(htTemp);
	return;
}

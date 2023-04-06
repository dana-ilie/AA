#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#include "Hashtable.h"

#define MAX_BUCKET_SIZE 64

/*
 * Functii de comparare a cheilor:
 */
int
compare_function_ints(void *a, void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b) {
		return 0;
	} else if (int_a < int_b) {
		return -1;
	} else {
		return 1;
	}
}

int
compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

/*
 * Functii de hashing:
 */
unsigned int
hash_function_int(void *a)
{
	/*
	 * Credits: https://stackoverflow.com/a/12996028/7883884
	 */
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

unsigned int
hash_function_string(void *a)
{
	/*
	 * Credits: http://www.cse.yorku.ca/~oz/hash.html
	 */
	unsigned char *puchar_a = (unsigned char*) a;
	unsigned long hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*))
{
	unsigned i;
    hashtable_t *ht = malloc(sizeof(hashtable_t));
    DIE(ht == NULL, "ht malloc failed");

    ht->buckets = malloc(hmax * sizeof(linked_list_t *));
    DIE(ht->buckets == NULL, "buckets malloc failed");

    for (i = 0; i < hmax; i++)
        ht->buckets[i] = ll_create(sizeof(struct info));

    ht->size = 0;
    ht->hmax = hmax;
    ht->hash_function = hash_function;
    ht->compare_function = compare_function;
    
    return ht;
}

void
ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{   
	unsigned int index = ht->hash_function(key) % ht->hmax;

    if (ht_has_key(ht, key)) {
        ll_node_t *head;
   
        for (head = ht->buckets[index]->head; head; head = head->next)
            if (ht->compare_function(((struct info *)head->data)->key, key) == 0) {
                memcpy(((struct info *)head->data)->value, (struct info *)value, value_size);

            }
    }
    else {
        struct info new_data;
        new_data.key = malloc(key_size);
        new_data.value = malloc(value_size);
        memcpy(new_data.key, key, key_size);
        memcpy(new_data.value, value, value_size);
        ll_add_nth_node(ht->buckets[index], 0, &new_data);
        ht->size++;
    }
    
}

void *
ht_get(hashtable_t *ht, void *key)
{   
	unsigned int index;
    ll_node_t *head;
   
    index = ht->hash_function(key) % ht->hmax;

    if (ht->buckets[index]->head == NULL)
        return NULL;

    for (head = ht->buckets[index]->head; head; head = head->next) {
        if (ht->compare_function(((struct info *)head->data)->key, key) == 0)
            return ((struct info *)head->data)->value;
    }

	return NULL;
}

/*
 * Functie care intoarce:
 * 1, daca pentru cheia key a fost asociata anterior o valoare in hashtable folosind functia put
 * 0, altfel.
 */
int
ht_has_key(hashtable_t *ht, void *key)
{
    unsigned int index;
    ll_node_t *head;
   
    index = ht->hash_function(key) % ht->hmax;

    if (ht->buckets[index]->head == NULL)
        return 0;

    for (head = ht->buckets[index]->head; head; head = head->next) {
        if (ht->compare_function(((struct info *)head->data)->key, key) == 0)
            return 1;
    }

	return 0;
}

/*
 * Procedura care elimina din hashtable intrarea asociata cheii key.
 */
void
ht_remove_entry(hashtable_t *ht, void *key)
{   
    ll_node_t *tmp;
    unsigned int index = ht->hash_function(key) % ht->hmax;
    ll_node_t *head = ht->buckets[index]->head;
    int count = 0;

    while (head != NULL) {
        if(ht->compare_function(((struct info *)head->data)->key, key) == 0)
            break;

        count++;
        head = head->next;
    }

    tmp = ll_remove_nth_node(ht->buckets[index], count);
    free(((struct info *)tmp->data)->key);
    free(((struct info *)tmp->data)->value);
    free(((struct info *)tmp->data));
    free(tmp);
    ht->size--;
    
}

/*
 * Procedura care elibereaza memoria folosita de toate intrarile din hashtable, dupa care elibereaza si memoria folosita
 * pentru a stoca structura hashtable.
 */
void
ht_free(hashtable_t *ht)
{
    for (unsigned int i = 0; i < ht->hmax; i++) {
        ll_node_t *curr = ht->buckets[i]->head;
        while (curr != NULL) {
            struct info *data = (struct info *)curr->data;
            ht_remove_entry(ht, data->key);
            curr = ht->buckets[i]->head;
        }
        free(ht->buckets[i]);
    }
    free(ht->buckets);
    free(ht);

}

unsigned int
ht_get_size(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->size;
}

unsigned int
ht_get_hmax(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->hmax;
}
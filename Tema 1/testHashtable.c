#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.c"
#include "LinkedList.c"

#define MAX_STRING_SIZE		256
#define MAX_INPUT_LINE_SIZE 300
#define DELIM "\n "

int
main()
{   
    hashtable_t *ht_set = ht_create(100, hash_function_int, compare_function_ints);;

    do
    {
        char *arg;
        char input[MAX_INPUT_LINE_SIZE];
        int current_key;

        fgets(input, MAX_INPUT_LINE_SIZE, stdin);
        arg = strtok(input, DELIM);

        if (strcmp(arg, "add") == 0) {
            current_key = atoi(strtok(NULL, DELIM));

            if (ht_has_key(ht_set, &current_key)) {
                printf("%d is already in the set\n", current_key);
            } else {
                ht_put(ht_set, &current_key, sizeof(current_key), &current_key, sizeof(current_key));
                if (ht_has_key(ht_set, &current_key)) {
                    printf("%d is now in the set\n", current_key);
                } else {
                    printf("Add to the set failed\n");
                }
            } 
        } else if (strcmp(arg, "del") == 0) {
            current_key = atoi(strtok(NULL, DELIM));
            if (ht_has_key(ht_set, &current_key) == 0) {
                printf("%d is not in the set\n", current_key);
            } else {
                ht_remove_entry(ht_set, &current_key);
                if (ht_has_key(ht_set, &current_key) == 0) {
                    printf("%d was removed from the set\n", current_key);
                } else {
                    printf("Remove failed\n");
                }
            }
        } else if (strcmp(arg, "modify") == 0) {
            int old_key, new_key;
            old_key = atoi(strtok(NULL, DELIM));
            new_key = atoi(strtok(NULL, DELIM));
            if (!ht_has_key(ht_set, &old_key)) {
                printf("%d is not in the set\n", old_key);
            } else if (ht_has_key(ht_set, &new_key)) {
                printf("%d is already in the set\n", new_key);
            } else {
                ht_remove_entry(ht_set, &old_key);
                ht_put(ht_set, &new_key, sizeof(new_key), &new_key, sizeof(new_key));
                if (ht_has_key(ht_set, &new_key) == 1 && ht_has_key(ht_set, &old_key) == 0) {
                    printf("%d was replaced with %d\n", old_key, new_key);
                } else {
                    printf("Modify failed\n");
                }
            }
        } else if (strcmp(arg, "stop") == 0) {
            ht_free(ht_set);
            exit(0);
        }
    } while (1);

	return 0;
}
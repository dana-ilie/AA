#include "treap.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100000
#define MAX_INPUT_LINE_SIZE 300
#define DELIM "\n "

int
compar(void* value1, void* value2)
{

    int* a = (int*)value1;
    int* b = (int*)value2;
    if ((*a) > (*b)) {
        return 1;
    } else if ((*a) < (*b)) {
        return -1;
    }
    return 0;
}

/* Obtinerea cheilor sortate crescator.
 *
 * @param1: Nodul curent in parcurgerea recursiva.
 * @param2: Array-ul prin care se intorc cheile sortate crescator.
 * @param3: Numarul de chei adaugate in array.
 */
void
ascending_nodes(Node* node, int* keys, int* num_keys)
{
    if (node == NULL)
        return;
    ascending_nodes(node->left, keys, num_keys);
    //add in v
    keys[*num_keys] = *(int*)node->data;
    *num_keys = *num_keys + 1;
    ascending_nodes(node->right, keys, num_keys);
}

int
main()
{
    Treap_tree* tree = treap_create((int (*)(void*, void*))(compar));


    do
    {
        char *arg;
        char input[MAX_INPUT_LINE_SIZE];
        int value;

        fgets(input, MAX_INPUT_LINE_SIZE, stdin);
        arg = strtok(input, DELIM);

        if (strcmp(arg, "add") == 0) {
            value = atoi(strtok(NULL, DELIM));
            if (get_key(tree->root, &value, sizeof(int), tree->compar)) {
                    printf("%d %s\n", value, "is already in the Treap.");
            } else {
                treap_insert(&tree->root, &value, sizeof(int), tree->compar);
            }
        } else if (strcmp(arg, "del") == 0) {
            value = atoi(strtok(NULL, DELIM));
            if (!get_key(tree->root, &value, sizeof(int), tree->compar)) {
                printf("%d is not in the set\n", value);
            } else {
                treap_delete(&tree->root, &value, sizeof(int), tree->compar);
            }
        } else if (strcmp(arg, "modify") == 0) {
            int old_value, new_value;
            old_value = atoi(strtok(NULL, DELIM));
            new_value = atoi(strtok(NULL, DELIM));
            if (!get_key(tree->root, &old_value, sizeof(int), tree->compar)) {
                printf("%d is not in the set\n", old_value);
            } else if (get_key(tree->root, &new_value, sizeof(int), tree->compar)) {
                printf("%d is already in the set\n", new_value);
            } else {
                treap_delete(&tree->root, &old_value, sizeof(int), tree->compar);
                treap_insert(&tree->root, &new_value, sizeof(int), tree->compar);
            }
        } else if (strcmp(arg, "stop") == 0) {
            if (check_treap(tree->root, tree->compar) > 0) {
                printf("The set is a treap and has %d nodes.\n",
                       check_treap(tree->root, tree->compar));
                printf("Nodes in ascending order: \n");
                int keys[MAX_NODES] = { 0 };
                int num_keys = 0;
                ascending_nodes(tree->root, keys, &num_keys);
                for (int i = 0; i < num_keys; ++i) {
                    printf("%d\n", keys[i]);
                }
            } else if(check_treap(tree->root, tree->compar) == 0) {
                printf("The set is empty\n");
            } else {
                printf("%s\n", "The set is not a treap");
            }
            treap_free(tree);
            exit(0);
        }
    } while (1);

    return 0;
}
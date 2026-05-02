#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 3
#define P 0.5

// Node structure
struct Node {
    int key;
    struct Node* forward[MAX_LEVEL + 1];
};

// Skip List structure
struct SkipList {
    int level;
    struct Node* header;
};

// Create node
struct Node* createNode(int key, int level) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->key = key;

    for (int i = 0; i <= MAX_LEVEL; i++)
        n->forward[i] = NULL;

    return n;
}

// Create skip list
struct SkipList* createSkipList() {
    struct SkipList* list = (struct SkipList*)malloc(sizeof(struct SkipList));
    list->level = 0;
    list->header = createNode(-1, MAX_LEVEL);
    return list;
}

// Random level generator
int randomLevel() {
    int level = 0;
    while ((rand()/(double)RAND_MAX) < P && level < MAX_LEVEL)
        level++;
    return level;
}

// INSERT
void insert(struct SkipList* list, int key) {
    struct Node* update[MAX_LEVEL + 1];
    struct Node* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] &&
               current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current == NULL || current->key != key) {
        int rlevel = randomLevel();

        if (rlevel > list->level) {
            for (int i = list->level + 1; i <= rlevel; i++)
                update[i] = list->header;

            list->level = rlevel;
        }

        struct Node* n = createNode(key, rlevel);

        for (int i = 0; i <= rlevel; i++) {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }

        printf("Inserted: %d\n", key);
    }
}

// SEARCH
void search(struct SkipList* list, int key) {
    struct Node* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] &&
               current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];

    if (current && current->key == key)
        printf("Found %d\n", key);
    else
        printf("%d not found\n", key);
}

// DELETE
void deleteNode(struct SkipList* list, int key) {
    struct Node* update[MAX_LEVEL + 1];
    struct Node* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] &&
               current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current && current->key == key) {
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != current)
                break;

            update[i]->forward[i] = current->forward[i];
        }

        free(current);

        // Adjust level
        while (list->level > 0 &&
               list->header->forward[list->level] == NULL) {
            list->level--;
        }

        printf("Deleted: %d\n", key);
    } else {
        printf("%d not found for deletion\n", key);
    }
}

// DISPLAY
void display(struct SkipList* list) {
    printf("\nSkip List:\n");
    for (int i = 0; i <= list->level; i++) {
        struct Node* node = list->header->forward[i];
        printf("Level %d: ", i);
        while (node != NULL) {
            printf("%d ", node->key);
            node = node->forward[i];
        }
        printf("\n");
    }
}

// MAIN
int main() {
    srand(time(NULL));

    struct SkipList* list = createSkipList();

    insert(list, 3);
    insert(list, 6);
    insert(list, 7);
    insert(list, 9);
    insert(list, 12);
    insert(list, 19);

    display(list);

    search(list, 9);

    deleteNode(list, 9);
    deleteNode(list, 15);

    display(list);

    return 0;
}

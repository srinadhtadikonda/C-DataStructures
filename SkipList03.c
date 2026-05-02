#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 4
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
struct Node* createNode(int key) {
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
    list->header = createNode(-1);
    return list;
}

// Random level
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
               current->forward[i]->key < key)
            current = current->forward[i];

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

        struct Node* n = createNode(key);

        for (int i = 0; i <= rlevel; i++) {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }

        printf("Inserted %d\n", key);
    }
}

// SEARCH
void search(struct SkipList* list, int key) {
    struct Node* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] &&
               current->forward[i]->key < key)
            current = current->forward[i];
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
               current->forward[i]->key < key)
            current = current->forward[i];

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

        while (list->level > 0 &&
               list->header->forward[list->level] == NULL)
            list->level--;

        printf("Deleted %d\n", key);
    } else {
        printf("%d not found\n", key);
    }
}

// DISPLAY
void display(struct SkipList* list) {
    printf("\nSkip List:\n");
    for (int i = list->level; i >= 0; i--) {
        struct Node* node = list->header->forward[i];
        printf("Level %d: ", i);
        while (node) {
            printf("%d ", node->key);
            node = node->forward[i];
        }
        printf("\n");
    }
}

// MAIN MENU
int main() {
    srand(time(NULL));

    struct SkipList* list = createSkipList();
    int choice, value;

    while (1) {
        printf("\n===== SKIP LIST MENU =====\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert(list, value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                search(list, value);
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteNode(list, value);
                break;

            case 4:
                display(list);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

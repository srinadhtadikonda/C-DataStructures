#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Display function
void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* temp = head;
    printf("List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Delete from beginning
void delete_begin(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* temp = *head;
    *head = (*head)->next;
    printf("Deleted: %d\n", temp->data);
    free(temp);
}

// Delete from end
void delete_end(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node* temp = *head;

    // Only one node
    if (temp->next == NULL) {
        printf("Deleted: %d\n", temp->data);
        free(temp);
        *head = NULL;
        return;
    }

    // Traverse to second last node
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    printf("Deleted: %d\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
}

// Delete at position
void delete_position(struct Node** head, int pos) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node* temp = *head;

    // Delete first node
    if (pos == 1) {
        *head = temp->next;
        printf("Deleted: %d\n", temp->data);
        free(temp);
        return;
    }

    // Traverse to (pos-1) node
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position\n");
        return;
    }

    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    printf("Deleted: %d\n", nodeToDelete->data);
    free(nodeToDelete);
}

// Helper: insert at end (to build list)
void insert_end(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Main function
int main() {
    struct Node* head = NULL;
    int choice, data, pos, n;

    while (1) {
        printf("\n--- Deletion Menu ---\n");
        printf("1. Create List\n");
        printf("2. Delete from Beginning\n");
        printf("3. Delete from End\n");
        printf("4. Delete at Position\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of nodes: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Enter data %d: ", i + 1);
                    scanf("%d", &data);
                    insert_end(&head, data);
                }
                break;

            case 2:
                delete_begin(&head);
                break;

            case 3:
                delete_end(&head);
                break;

            case 4:
                printf("Enter position: ");
                scanf("%d", &pos);
                delete_position(&head, pos);
                break;

            case 5:
                display(head);
                break;

            case 6:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}

#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to display list
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

// Insert at beginning
void insert_begin(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

// Insert at end
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

// Insert at position
void insert_position(struct Node** head, int data, int pos) {
    if (pos == 1) {
        insert_begin(head, data);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;

    struct Node* temp = *head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid position\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Create list
void create_list(struct Node** head, int n) {
    int data;
    for (int i = 0; i < n; i++) {
        printf("Enter data %d: ", i + 1);
        scanf("%d", &data);
        insert_end(head, data);
    }
}

// Main function
int main() {
    struct Node* head = NULL;
    int choice, data, pos, n;

    while (1) {
        printf("\n--- Singly Linked List Menu ---\n");
        printf("1. Create List\n");
        printf("2. Insert at Beginning\n");
        printf("3. Insert at End\n");
        printf("4. Insert at Position\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of nodes: ");
                scanf("%d", &n);
                create_list(&head, n);
                break;

            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                insert_begin(&head, data);
                break;

            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                insert_end(&head, data);
                break;

            case 4:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &pos);
                insert_position(&head, data, pos);
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

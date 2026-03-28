//delete first node
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void deleteFirstNode(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = *head;
    *head = (*head)->next;
    int deletedData = temp->data;
    free(temp);
    printf("Deleted first node with data: %d\n", deletedData);
}

int main() {
    // Create first node
    struct Node* head = malloc(sizeof(struct Node));
    head->data = 10;

    // Create second node
    head->next = malloc(sizeof(struct Node));
    head->next->data = 20;

    // Create third node (30)
    head->next->next = malloc(sizeof(struct Node));
    head->next->next->data = 30;

    // Create fourth node (40)
    head->next->next->next = malloc(sizeof(struct Node));
    head->next->next->next->data = 40;

    // Last node points to NULL
    head->next->next->next->next = NULL;

    // Print initial list
    printf("Initial list: ");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    // Delete first node
    deleteFirstNode(&head);

    // Print list after deletion
    printf("List after deletion: ");
    temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    // Free remaining nodes
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

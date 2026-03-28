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
    struct Node* head = malloc(sizeof(struct Node));
    head->data = 10;
    head->next = malloc(sizeof(struct Node));
    head->next->data = 20;
    head->next->next = NULL;

    printf("Initial list: %d -> %d\n", head->data, head->next->data);
    deleteFirstNode(&head);
    printf("List after deletion: ");
    if (head != NULL) {
        printf("%d\n", head->data);
    } else {
        printf("List is empty.\n");
    }

    // Free remaining nodes
    free(head);
    return 0;
}
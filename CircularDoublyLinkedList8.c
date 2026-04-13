#include <stdio.h>
#include <stdlib.h>

// 🔹 Node structure
struct node {
    int data;
    struct node *prev;
    struct node *next;
};

struct node *head = NULL;

// 🔹 Create node
struct node* createNode(int data) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// 🔹 Display forward
void displayForward() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct node *temp = head;
    printf("Forward: ");
    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(HEAD)\n");
}

// 🔹 Display backward
void displayBackward() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct node *temp = head->prev; // last node
    printf("Backward: ");
    do {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    } while (temp != head->prev);
    printf("(LAST)\n");
}

// 🔹 Insert at beginning
void insertBeginning(int data) {
    struct node *newNode = createNode(data);

    if (head == NULL) {
        newNode->next = newNode->prev = newNode;
        head = newNode;
        return;
    }

    struct node *last = head->prev;

    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;

    head = newNode;
}

// 🔹 Insert at end
void insertEnd(int data) {
    struct node *newNode = createNode(data);

    if (head == NULL) {
        newNode->next = newNode->prev = newNode;
        head = newNode;
        return;
    }

    struct node *last = head->prev;

    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;
}

// 🔹 Insert at position
void insertPosition(int data, int pos) {
    if (pos == 1) {
        insertBeginning(data);
        return;
    }

    struct node *newNode = createNode(data);
    struct node *temp = head;

    for (int i = 1; i < pos - 1 && temp->next != head; i++)
        temp = temp->next;

    struct node *nextNode = temp->next;

    newNode->next = nextNode;
    newNode->prev = temp;

    temp->next = newNode;
    nextNode->prev = newNode;
}

// 🔹 Delete from beginning
void deleteBeginning() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    if (head->next == head) {
        free(head);
        head = NULL;
        return;
    }

    struct node *last = head->prev;
    struct node *temp = head;

    head = head->next;
    head->prev = last;
    last->next = head;

    free(temp);
}

// 🔹 Delete from end
void deleteEnd() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    if (head->next == head) {
        free(head);
        head = NULL;
        return;
    }

    struct node *last = head->prev;
    struct node *secondLast = last->prev;

    secondLast->next = head;
    head->prev = secondLast;

    free(last);
}

// 🔹 Delete from position
void deletePosition(int pos) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    if (pos == 1) {
        deleteBeginning();
        return;
    }

    struct node *temp = head;

    for (int i = 1; i < pos && temp->next != head; i++)
        temp = temp->next;

    struct node *prevNode = temp->prev;
    struct node *nextNode = temp->next;

    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    free(temp);
}

// 🔹 Main Menu
int main() {
    int choice, data, pos;

    while (1) {
        printf("\n--- Doubly Circular Linked List Menu ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from End\n");
        printf("6. Delete from Position\n");
        printf("7. Display Forward\n");
        printf("8. Display Backward\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insertBeginning(data);
                break;

            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                insertEnd(data);
                break;

            case 3:
                printf("Enter data and position: ");
                scanf("%d %d", &data, &pos);
                insertPosition(data, pos);
                break;

            case 4:
                deleteBeginning();
                break;

            case 5:
                deleteEnd();
                break;

            case 6:
                printf("Enter position: ");
                scanf("%d", &pos);
                deletePosition(pos);
                break;

            case 7:
                displayForward();
                break;

            case 8:
                displayBackward();
                break;

            case 9:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

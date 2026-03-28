#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;

// Function to insert a node at the beginning
void insert_begin(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = head;
    head = new_node;
}

// Function to insert a node at the end
void insert_end(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (head == NULL) {
        head = new_node;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// Function to insert a node at a given position
void insert_at_position(int data, int position) {
    if (position == 0) {
        insert_begin(data);
        return;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    Node* temp = head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds\n");
        free(new_node);
    } else {
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

// Function to delete a node at the end
void delete_end() {
    if (head == NULL) return;
    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }
    Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

// Function to delete a node at a given position
void delete_at_position(int position) {
    if (head == NULL) return;
    Node* temp = head;
    if (position == 0) {
        head = temp->next;
        free(temp);
        return;
    }
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds\n");
        return;
    }
    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

// Function to print the linked list
void print_list() {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function with test cases
int main() {
    insert_begin(10);
    insert_end(20);
    insert_end(30);
    printf("Initial list: ");
    print_list();
    insert_at_position(15, 1);
    printf("After inserting 15 at position 1: ");
    print_list();
    delete_end();
    printf("After deleting the last element: ");
    print_list();
    delete_at_position(1);
    printf("After deleting at position 1: ");
    print_list();
    return 0;
}
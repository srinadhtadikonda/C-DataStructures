#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Top pointer
struct Node* top = NULL;

// PUSH operation
void push(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Stack Overflow\n");
        return;
    }

    newNode->data = data;
    newNode->next = top;
    top = newNode;

    printf("%d pushed into stack\n", data);
}

// POP operation
void pop() {
    if (top == NULL) {
        printf("Stack Underflow\n");
        return;
    }

    struct Node* temp = top;
    printf("%d popped from stack\n", top->data);
    top = top->next;
    free(temp);
}

// PEEK operation
void peek() {
    if (top == NULL) {
        printf("Stack is Empty\n");
    } else {
        printf("Top element is: %d\n", top->data);
    }
}

// CHANGE operation (change element at position)
void change(int pos, int value) {
    struct Node* temp = top;
    int i;

    if (temp == NULL) {
        printf("Stack is Empty\n");
        return;
    }

    for (i = 1; i < pos; i++) {
        temp = temp->next;
        if (temp == NULL) {
            printf("Invalid Position\n");
            return;
        }
    }

    temp->data = value;
    printf("Element at position %d changed to %d\n", pos, value);
}

// COUNT operation
void count() {
    int c = 0;
    struct Node* temp = top;

    while (temp != NULL) {
        c++;
        temp = temp->next;
    }

    printf("Total elements in stack: %d\n", c);
}

// DISPLAY operation
void display() {
    struct Node* temp = top;

    if (temp == NULL) {
        printf("Stack is Empty\n");
        return;
    }

    printf("Stack elements:\n");
    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

// MAIN MENU
int main() {
    int choice, value, pos;

    while (1) {
        printf("\n===== STACK MENU =====\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Change\n");
        printf("5. Count\n");
        printf("6. Display\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
                break;

            case 3:
                peek();
                break;

            case 4:
                printf("Enter position: ");
                scanf("%d", &pos);
                printf("Enter new value: ");
                scanf("%d", &value);
                change(pos, value);
                break;

            case 5:
                count();
                break;

            case 6:
                display();
                break;

            case 7:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

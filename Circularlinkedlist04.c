#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

// Create new node
struct Node* createNode(int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Insert at end (for initial creation)
void insertEnd(int value)
{
    struct Node *newNode = createNode(value);

    if(head == NULL)
    {
        head = newNode;
        newNode->next = head;
    }
    else
    {
        struct Node *temp = head;

        while(temp->next != head)
            temp = temp->next;

        temp->next = newNode;
        newNode->next = head;
    }
}

// Insert at required position
void insertAtPosition(int value, int pos)
{
    struct Node *newNode = createNode(value);

    // Insert at beginning
    if(pos == 1)
    {
        if(head == NULL)
        {
            head = newNode;
            newNode->next = head;
        }
        else
        {
            struct Node *temp = head;

            while(temp->next != head)
                temp = temp->next;

            newNode->next = head;
            temp->next = newNode;
            head = newNode;
        }
        return;
    }

    struct Node *temp = head;
    int i;

    for(i=1; i<pos-1 && temp->next!=head; i++)
        temp = temp->next;

    if(i != pos-1)
    {
        printf("Invalid Position\n");
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Display circular linked list
void display()
{
    struct Node *temp;

    if(head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    temp = head;

    printf("Circular Linked List: ");
    do
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }while(temp != head);

    printf("(Back to Head)\n");
}

// Main function
int main()
{
    int n,i,value,pos;

    printf("Enter number of nodes: ");
    scanf("%d",&n);

    printf("Enter elements:\n");
    for(i=1;i<=n;i++)
    {
        scanf("%d",&value);
        insertEnd(value);
    }

    display();

    printf("Enter element to insert: ");
    scanf("%d",&value);

    printf("Enter position to insert: ");
    scanf("%d",&pos);

    insertAtPosition(value,pos);

    printf("After Insertion:\n");
    display();

    return 0;
}

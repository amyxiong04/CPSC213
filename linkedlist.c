#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    // if (newNode == NULL) {
    //     printf("Memory allocation failed\n");
    //     exit(1);
    // }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printLinkedList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void insertAtBeginning(struct Node** head, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head;
    *head = new_node;
}


int main() {
    struct Node* head = createNode(1);
    struct Node* second = createNode(2);
    struct Node* third = createNode(3);

    head->next = second;
    second->next = third;

    printf("Linked List: ");
    insertAtBeginning(&head, 4);
    printLinkedList(head);

    free(head);
    free(second);
    free(third);

    return 0;
}

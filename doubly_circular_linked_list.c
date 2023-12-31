#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
}Node;

void add_node(Node **start, int value);
void insert_node(Node **start, int insert_after_value, int value);
void delete_node(Node **start, int value);
void print_list(Node *node);
void inverse_print_list(Node *node);
void free_list(Node *node);

int main()
{
    Node *head = NULL;

    add_node(&head, 5);
    add_node(&head, 128);
    add_node(&head, 41);

    insert_node(&head, 45, 62);
    insert_node(&head, 5, 23);
    insert_node(&head, 128, 57);
    insert_node(&head, 41, 30);

    delete_node(&head, 5);
    delete_node(&head, 128);
    delete_node(&head, 30);

    print_list(head);

    inverse_print_list(head);

    free_list(head);

    return 0;
}

void add_node(Node **start, int value)
{
    Node *new_node = (Node*)malloc(sizeof(Node));

    new_node->data = value;
    new_node->next = new_node;
    new_node->prev = new_node;

    if(*start == NULL) {
        *start = new_node;
        return;
    }
    else {
        Node *current;
        current = *start;
        while(current->next != *start) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
        new_node->next = *start;
        (*start)->prev = new_node;
    }
}

void insert_node(Node **start, int insert_after_value, int value)
{
    Node *current = *start;

    do {
        if(insert_after_value == current->data) {
            Node *new_node = (Node*)malloc(sizeof(Node));
            new_node->data = value;
            new_node->next = current->next;
            current->next->prev = new_node;
            current->next = new_node;
            new_node->prev = current;
            break;
        }
        current = current->next;
    }while(current!=*start);
}

void delete_node(Node **start, int value)
{
    Node *current = *start;
    Node *temp;
    Node *ori_start = *start;

    if(value == current->data) {
        *start = current->next;
        do {
            current = current->next;
        }while(current->next !=ori_start);
        current->next = *start;
        (*start)->prev = current;
        free(ori_start);
        return;
    }


    do {
        if(current->next->data == value) {
            temp = current->next;
            current->next = current->next->next;
            current->next->prev = current;
            free(temp);
            return;
        }
        current = current->next;
    }while(current != *start);
}

void print_list(Node *node)
{
    Node *first_node = node;
    printf("%d ", node->data);
    node = node->next;

    while(node != NULL) {
        if(node == first_node) break;
        printf("%d ", node->data);
        node = node->next;
    }
    printf("%d\n", node->data);
}

void inverse_print_list(Node *node)
{
    Node *last_node = node;
    printf("%d ", node->data);
    node = node->prev;

    while(node != NULL) {
        if(node == last_node) break;
        printf("%d ", node->data);
        node = node->prev;
    }
    printf("%d\n", node->data);
}

void free_list(Node *node)
{
    int total_node = 1;
    Node *first = node;
    node = node->next;
    while(node != first) {
        node = node->next;
        total_node++;
    }

    Node *current = first;
    Node *temp;
    int i;

    for(i = 0; i < total_node; i++) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

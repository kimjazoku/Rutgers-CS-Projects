#include <stdio.h>
#include <stdlib.h>

int lineNum = 0;
struct node
{
    int id;            // id of the node
    struct node *next; // points to the next node
};

void insert(struct node **head, int id)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->id = id;
    newNode->next = NULL;

    // if the list is empty, insert the new node as the head
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    struct node *ptr = *head;
    struct node *prev = NULL;

    while (ptr != NULL)
    {
        if (ptr->id == id)
        {
            free(newNode);
            return;
        }
        if (id < ptr->id)
        {
            if (prev == NULL)
            {
                // insert at the head
                newNode->next = *head;
                *head = newNode;
            }
            else
            {
                // insert between prev and ptr
                prev->next = newNode;
                newNode->next = ptr;
            }
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }


    prev->next = newNode; //insert at the end
}

int delete(struct node **head, int n)
{
    // if list is empty, do nothing
    if (*head == NULL)
        return 0;

    struct node *ptr = *head;
    struct node *prev = NULL;

    // if the delete node is the head node
    if (ptr != NULL && ptr->id == n)
    {
        *head = ptr->next;
        free(ptr);
        return 1;
    }

    // otherwise we traverse the list to find the node to be deleted
    while (ptr != NULL && ptr->id != n)
    {
        prev = ptr;
        ptr = ptr->next;
    }

    // if node to be deleted is not found, do nothing
    if (ptr == NULL)
    {
        return 0;
    }
    // unlink the node from the list
    prev->next = ptr->next;
    free(ptr);
    return 1;
}

void printList(struct node *head, int line_number)
{
    if (head == NULL)
    {
        line_number = 0;
        printf("%d :\n", line_number);
    }
    else
    {
        printf("%d : ", line_number);
        struct node *ptr = head;
        while (ptr != NULL)
        {
            if (ptr->next == NULL)
            {
                printf("%d", ptr->id);
                break;
            }
            printf("%d ", ptr->id);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

void freeList(struct node *head)
{
    struct node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char *argv[])
{
    // allocate memory for the head node
    struct node *head = NULL;
    char c;
    int id;
    while (scanf("%c %d", &c, &id) != EOF) // read id and character from file
    {
        if (c == 'i')
        {
            insert(&head, id);
            lineNum += 1;
            printList(head, lineNum);
        }
        else if (c == 'd')
        {
            int check = delete (&head, id);
            if(check == 1)
            {
            lineNum -= 1;    
            }
            printList(head, lineNum);
        }
    }

    // fclose(fptr); // close the file
    freeList(head);
    return 0;
}

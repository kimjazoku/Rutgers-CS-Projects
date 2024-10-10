#include <stdio.h>
#include <stdlib.h>

struct BstNode
{
    int id; //id of the node node
    struct BstNode *left;
    struct BstNode *right;
};

void freeBst(struct BstNode *node)
{
    if (node == NULL)
        return;
    
    // Recursively free left and right subtrees
    freeBst(node->left);
    freeBst(node->right);
    
    // Free the current node
    free(node);
}


struct BstNode *insertBst(struct BstNode *node, int id)
{
    //if the tree is empty, return a new node
    if (node == NULL)
    {
        struct BstNode *newNode = (struct BstNode *)malloc(sizeof(struct BstNode));
        newNode->id = id;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    //otherwise, recur down the tree
    if (id < node->id)
    {
        node->left = insertBst(node->left, id);
    }
    else if (id > node->id)
    {
        node->right = insertBst(node->right, id);
    }

    //return the (unchanged) node pointer
    //printf("not inserted\n");
    return node;
}

struct BstNode *searchBst(struct BstNode *node, int id)
{
    //base case: tree is empty or id is found
    if (node == NULL)
    {
        printf("absent\n");
        return NULL;
    }
    if (id == node->id)
    {
        return node;
    }
    // otherwise, recur down the tree
    if (id < node->id)
    {
        return searchBst(node->left, id);
    }
    else
    {
        return searchBst(node->right, id);
    }
}

struct BstNode *minValueNode(struct BstNode *node)
{
    struct BstNode *current = node;
    while (current && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

struct BstNode* deleteBst(struct BstNode *root, int id)
{
    //base case: tree is empty or id is not found
    if (root == NULL)
    {
        printf("absent\n");
        return root;
    }

    //otherwise, recur down the tree
    if (id < root->id)
    {
        root->left = deleteBst(root->left, id);
    }
    else if (id > root->id)
    {
        root->right = deleteBst(root->right, id);
    }
    else
    {
        //node with only one child or no child
        if (root->left == NULL)
        {
            struct BstNode *temp = root->right;
            free(root);
            printf("deleted\n");
            return temp;
        }
        else if (root->right == NULL)
        {
            struct BstNode *temp = root->left;
            free(root);
            printf("deleted\n");
            return temp;
        }

        //node with two children: get the inorder successor (smallest in the right subtree)
        struct BstNode *temp = minValueNode(root->right);
        root->id = temp->id;
        root->right = deleteBst(root->right, temp->id);
    }
    return root;
}

void printBst(struct BstNode *node)
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        printf("(");
        printBst(node->left);
        printf("%d", node->id);
        printBst(node->right);
        printf(")");
    }
}

int main()
{
    struct BstNode *root = NULL; //create an empty tree

    //FILE *fptr;
    //fptr = fopen("input.txt", "r"); //open file input.txt

    int id;
    char c;

    //proper error message if file fails to open
    // if (!fptr)
    // {
    //     printf("Error opening file\n");
    //     return 1;
    // }

    //process commands from the input file
    while (scanf( " %c", &c) != EOF) //notice the space before %c to handle newlines
    {
        if (c == 'i')
        {
            scanf( "%d", &id);
            root = insertBst(root, id); //insert node only once
            if(root == NULL){
                printf("not inserted\n");
            }
            else
            {
                printf("inserted\n");
            }
        }
        else if (c == 's')
        {
            scanf("%d", &id);
            struct BstNode* check = searchBst(root, id); //search for node
            if(check != NULL)
            {
            printf("present\n");
            }
        }
        else if (c == 'd')
        {
            scanf("%d", &id);
            root = deleteBst(root, id); //delete node, update root
        }
        else if (c == 'p')
        {
            printBst(root); //print the entire tree, no need for an ID
            printf("\n");
        }
    }

    //fclose(fptr); //close the file
    freeBst(root); //free all nodes when done with the tree
    return 0;
}
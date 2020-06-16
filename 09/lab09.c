#include <stdio.h>
#include <stdlib.h>

//Declaração de estruturas
typedef struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
} tree;

//Prototipagem de funções
tree *CreateFromInput(int amount);
int Height(tree *root);
void Kill(tree *root);

int main()
{
    int N;
    scanf("%d", &N);

    tree *DNTree = CreateFromInput(N);
    int DNHeight = Height(DNTree);
    Kill(DNTree);

    tree *mentirinhaTree = CreateFromInput(N);
    int mentirinhaHeight = Height(mentirinhaTree);
    Kill(mentirinhaTree);

    printf("%d %d\n", DNHeight, mentirinhaHeight);

    return 0;
}

//Funções
void Insert(tree **root, tree *node) //**root is a reference to true root
{
    if (*root == NULL)
    {
        *root = node;
        return;
    }
    Insert(((*root)->data > node->data ? &((*root)->left) : &((*root)->right)), node);
}

tree *CreateFromInput(int amount)
{
    tree *root = NULL;
    int value;
    while (amount > 0)
    {
        //Create node
        tree *node = malloc(sizeof(tree));
        scanf("%d", &value); //number by number from line
        node->data = value;
        node->left = node->right = NULL;
        Insert(&root, node); //insert node into the tree
        amount--;
    }
    return root;
}

int Height(tree *root)
{
    if (root == NULL)
        return 0;
    int hLeft = Height(root->left);               //height of left subtree
    int hRight = Height(root->right);             //height of right subtree
    return 1 + (hLeft > hRight ? hLeft : hRight); //root + taller subtree
}

void Kill(tree *root)
{
    if (root != NULL)
    {
        Kill(root->left);
        Kill(root->right);
        free(root);
    }
}
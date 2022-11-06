#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

//------------------------ ASSIGNMENT ---------------------------//

typedef struct NODE Node;

struct NODE{
    int key;

    Node *smaller_keys;
    Node *larger_keys;

};

typedef struct{
    Node *root;
}Tree;

Tree *tree_create();
void tree_insert_key(Tree *tree, int key);
int tree_find_key_recursive(Tree *tree, int key);
int tree_find_key_iterative(Tree *tree, int key);
int tree_is_valid(Tree *tree);
Tree* tree_deep_copy(Tree *tree);
void tree_delete(Tree *tree);
//------------------------ ASSIGNMENT ---------------------------//


//------------------------Auxiliary Functionality-----------------//

int* traverse_tree_inorder(Node *node, int *ret_pointer);
int validity_checker(Node *node);
int recursive_finder(Node *tree_root, int key);
int check_node_and_children(Node *node);
void iterative_inorder_traversal(Tree *tree);

//-------------------------Auxiliary Functionality---------------//

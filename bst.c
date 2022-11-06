#include "bst.h"
//-----------------------IMPLEMENTATION------------------------//


//create empty tree structure
Tree *tree_create()
{
    printf("Creating tree\n");
    Tree *tree;
    tree = (Tree *)malloc(sizeof(Tree));
    Node *node;
    node = NULL;
    (*tree).root = node; 
    printf("Created tree at %p, with root node at %p\n", tree, node);
    return tree;
}



//insert key according to rules of BST 
void tree_insert_key(Tree *tree, int key)
{
    printf("\n\nCalling Insert Function\n");

    //Beim Abzählen, der zuletzt besuchte noch gültige Knoten
    Node *trailing_pointer;
    trailing_pointer = NULL;

    //Zum Zählen der schon vorhandenen Knoten
    Node *temp_node;
    temp_node = tree->root;

    //neu einzufügender Knoten 
    Node *inserted_node;
    inserted_node = (Node *)malloc(sizeof(Node));
    inserted_node->key = key;
    inserted_node->larger_keys = NULL;
    inserted_node->smaller_keys = NULL;
    //printf("I should be NULL, I am: %p\n", temp_node);

    //Hier wird der Baum durchlaufen 
    while (temp_node != NULL)
    {
        //printf("I should be called now since temp_node: %p, temp_node_key: %d and new key: %d\n",temp_node, temp_node->key, inserted_node->key);
        //Angefangen bei Wurzel, dann vergleichen mit neuem Key und so den neuen Pfad legen
        trailing_pointer = temp_node; 
        if(inserted_node->key < temp_node->key)
        {
            //printf("called because %d is less than %d\n", inserted_node->key, temp_node->key);
            temp_node = temp_node->smaller_keys;
        }
        else if(inserted_node->key > temp_node->key)
        {
            //printf("called because %d is greater than %d\n", inserted_node->key, temp_node->key);
            temp_node = temp_node->larger_keys;
        }
        else
        {
            printf("Skipped, %d is already in BST\n", inserted_node->key);
            break;
        }
    }

    //Hier wird der neue Knoten tatsächlich eingefügt
    if(trailing_pointer == NULL)
    {
        //printf("I AM BEING CALLED ONCE\n");
        tree->root = inserted_node;
        printf("Now root node is %p with key: %d\n", tree->root, inserted_node->key);
        
    }
    else if (inserted_node->key < trailing_pointer->key)
    {
        //printf("I am being called because %d is less than %d\n", inserted_node->key, trailing_pointer->key);
        //(*trailing_pointer->smaller_keys).key = key;
        trailing_pointer->smaller_keys = inserted_node;
        printf("Trailing pointer key: %d with address: %p\n", trailing_pointer->key, trailing_pointer);
    }
    else if (inserted_node->key > trailing_pointer->key)
    {
        //printf("I am being called because %d is greater than %d\n", inserted_node->key, trailing_pointer->key);
        //(*trailing_pointer->larger_keys).key = key; 
        trailing_pointer->larger_keys = inserted_node;
        printf("Trailing pointer key: %d with address: %p\n", trailing_pointer->key, trailing_pointer);
    }
    //
}



//check whether key is already in tree structure (recurisvely) 
int tree_find_key_recursive(Tree *tree, int key)
{
    int result = recursive_finder(tree->root, key);
    if(result == 1 || result == 0)
    {
        printf("The tree %p contains the key %d\n", tree->root, key);
    }
    else
    {
        printf("%d is apparently not contained within %p");
    }
    return result;
}



//check whether key is already in tree structure, iteratively
int tree_find_key_iterative(Tree *tree, int key)
{
    Node *temp_node = tree->root;

    while (temp_node != NULL)
    {
        //printf("I should be called now since temp_node: %p, temp_node_key: %d and new key: %d\n",temp_node, temp_node->key, inserted_node->key);
        //Angefangen bei Wurzel, dann vergleichen mit neuem Key und so den neuen Pfad legen

        if(key < temp_node->key)
        {
            //printf("called because %d is less than %d\n", inserted_node->key, temp_node->key);
            temp_node = temp_node->smaller_keys;
        }
        else if(key > temp_node->key)
        {
            //printf("called because %d is greater than %d\n", inserted_node->key, temp_node->key);
            temp_node = temp_node->larger_keys;
        }
        else
        {
            printf("%d is contained within in BST\n", key);
            return 1;
        }
        //printf("temp %d at: %p\n", temp_node->key, temp_node);
    }
    //printf("I am terminating at %p, probably because of: %p, %p\n", temp_node, temp_node->larger_keys, temp_node->smaller_keys);
    printf("Key %d is not within BST\n", key);
}



//check for legitimateness of tree structure 
int tree_is_valid(Tree *tree)
{
    int result = validity_checker(tree->root);
    printf("%d\n",result);
    if(result == -1)
    {
        printf("The tree at %p is broken\n", tree->root);
    }
    else
    {
        printf("The tree at %p is fine\n", tree->root);
    }
    return result;
    printf("Finished traversion\n");
}


//create deep copy of tree structure 
Tree* tree_deep_copy(Tree *tree)
{
    Tree *copied_tree;
    copied_tree = tree_create();
    printf("SEEEEEEEERS\n");
    int *pointer_to_key;
    int *pointer_topkek;
    pointer_topkek = traverse_tree_inorder(tree->root, pointer_to_key);
    for(int i = 0; i < 11; i++)
    {
        printf("Got Key: %d at: %p\n", *(pointer_topkek + 8*i), pointer_topkek + 8 * i);
        tree_insert_key(copied_tree, *pointer_topkek);
    }
    return copied_tree;
}


//delete tree structure together with all nodes
void tree_delete(Tree *tree)
{
    int *pointer_to_key;
    pointer_to_key = &(*tree->root).key; 
    printf("%d at %p\n", *pointer_to_key, pointer_to_key);
    for(int i = 0; i < 11; i++)
    {
        *(pointer_to_key + i*8) = 0;
        printf("%d at %p\n", *(pointer_to_key + i*8), pointer_to_key + i*8);
    }
    free(tree);
    printf("Successfully deleted\n");
}


//-------------------------------Implementation of auxiliary functions ---------------//


//working subroutine for tree_is_valid(..) wrapper
int validity_checker(Node *node)
{
    Node *temp_node;
    temp_node = node;
    printf("Node: %d\n", temp_node->key);
    if(temp_node == NULL)
    {
        printf("Root can't be NULL, no tree specified\n");
        return -1;
        
    }

    else
    {

        
        if((*temp_node->smaller_keys).key > temp_node->key | (*temp_node->larger_keys).key < temp_node->key)
        {
            printf("There is a fault in the tree at parent node: %p, with key: %d whose smaller child has key: %d and larger child has key: %d", temp_node, temp_node->key, (*temp_node->smaller_keys), (*temp_node->larger_keys));
            return -1;
        }
        else //if((*temp_node->smaller_keys).key < temp_node->key & (*temp_node->larger_keys).key > temp_node->key)
        {
            printf("Subdivision at key: %d with l_kid %d and s_kid %d\n", temp_node->key, (*temp_node->larger_keys).key, (*temp_node->smaller_keys).key);
            
            if(temp_node->larger_keys != NULL)
            {
                printf("Looking for larger keys\n");
                int l = validity_checker(temp_node->larger_keys);
            }
                

            else if(temp_node->smaller_keys != NULL)
            {
                printf("Looking for smaller keys\n");
                int s = validity_checker(temp_node->smaller_keys);
            }
                
            return 0;
        }

    }
    return 0;
}


//working subroutine for tree_find_recursive(..) wrapper 
int recursive_finder(Node *tree_root, int key)
{
    //return 1 if element was found
    if(key == tree_root->key)
    {
        printf("Key %d is contained within tree [REC]\n", key);
        return 1;
    }
    else if(tree_root->key == NULL)
    {
        //printf("Key %d is apparently not contained within the BST at %p\n", key, tree_root);
        return -1;
    }
    else
    {
        //printf("I am being called at key %d\n", key);
        if(key > tree_root->key)
        {
            tree_find_key_recursive(tree_root->larger_keys, key);
        }
        else if (key < tree_root->key)
        {
            tree_find_key_recursive(tree_root->smaller_keys, key);
        }
    }
    //return 0 if it wasn't found by the time of reaching the base case
    return 0;
}

//traversing the tree recursively
int* traverse_tree_inorder(Node *node, int* ret_pointer)
{
    int * return_pointer;
    if(node != NULL)
    {
       //can't return befor recursive calls and not afterwars, so store key in pointer
        return_pointer = &(node->key);
         
        printf("Address %p has key: %d\n", return_pointer, *return_pointer);
        printf("Traversing, at node: %p with key %d now\n", node, node->key);
        ret_pointer = return_pointer;
        return_pointer += 5;
        
        //left child
        //printf("Calling left kid\n");
        traverse_tree_inorder(node->smaller_keys, return_pointer);

        int result = check_node_and_children(node);

        //right child
        //printf("Calling right kid\n");
        traverse_tree_inorder(node->larger_keys, return_pointer);
        return ret_pointer;
    }
    else
    {
        return -1;
    }
}

//visit the node
int check_node_and_children(Node *node)
{
    //printf("Node: %p\n", node);
    if((node == NULL) || ((node->larger_keys == NULL) || (node->smaller_keys == NULL)))
    {
        return -1;
    }
    else
    {
        printf("hold up checking rn at: %p\n", node);
        if(node->key > (*node->larger_keys).key || node->key < (*node->smaller_keys).key)
        {
            printf("There is a fault in the tree at key: %d\n", node->key);
            return -1;
        }
    }
    
    return 0;
}

//traversing the tree iteratively
void iterative_inorder_traversal(Tree *tree)
{
    //Array functioning as stack to store in-between values
    Node **stack_of_nodes;
    stack_of_nodes = (Node *)malloc(11 * sizeof(Node));
    //lowest symbol in the stack, like in the kellerautomat
    Node *keller_node;
    keller_node->key = 1000000;
    *stack_of_nodes = keller_node;
    //trailng node 
    Node *trailing_node; 
    trailing_node = tree->root;
    int i = 0;
    int current_key = trailing_node->key;
    //while( !((trailing_node->key == keller_node->key) || (trailing_node != NULL)) )
    //while( !(trailing_node->key == keller_node->key) || (trailing_node != NULL) )
    while(((current_key != keller_node->key) || (trailing_node != NULL)))
    {
        if(trailing_node != NULL)
        {
            *(stack_of_nodes + i) = trailing_node;
            //printf("[UP] At address: %p, with key: %d\n", *(stack_of_nodes + i), (**(stack_of_nodes + i)).key);
            if(trailing_node->smaller_keys == NULL)
            {
                //just some arbitrary value to prevent seg fault
                current_key = 1000;
                
                trailing_node = trailing_node->smaller_keys;
            
                i++;
                //printf("[UP] i: %d with trailing node: %p and key: %d\n", i, trailing_node, trailing_node->key);
                continue;
            }
            else
            {
                current_key = trailing_node->key;
                
            }
            check_node_and_children(trailing_node);
            trailing_node = trailing_node->smaller_keys;
            
            i++;
            printf("[UP] i: %d with trailing node: %p\n", i, trailing_node);
        }
        
        else if(trailing_node == NULL)
        {
            printf("WIESO KOM ICH NICHT ASL HERI REIN\n");
            
            trailing_node = *(stack_of_nodes + i); 
            printf("[DOWN] At address: %p, with key: \n", trailing_node);//, trailing_node->key);
            
            trailing_node = trailing_node->larger_keys;
            i--;
            printf("[DOWN] i: %d", i);
            
        }
        
    }
    printf("Last test for while loop: stack: %d node: %d \n", (trailing_node->key != keller_node->key), (trailing_node != NULL));
}
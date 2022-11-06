#include "bst.h"

//____________________________________________________
//Main function 
//____________________________________________________

int main()
{
    //Setup timer for random seeds
    printf("Starting\n");
    time_t t;
    unsigned int seed = (unsigned) time(&t);
    srand(seed);

    // I

    //create tree structure
    Tree *example_tree;
    example_tree = tree_create();

    //initialize array of random values
    int random_key = 0;
    int *arr_of_random_keys;
    arr_of_random_keys = (int *)malloc(10 * sizeof(int));

    for(int i = 0; i < 10; i++)
    {
        //setup up to 10 different numbers from 1 to 100 
        random_key = rand() % 100;
        random_key += 1;
        arr_of_random_keys[i] = random_key;

        printf("\n-------------");
        printf("\nRandom key generated: %d\n", random_key);

        // II

        //insert keys iteratively and let the insert-method handle correct placement 
        tree_insert_key(example_tree, random_key);
    }
    printf("\n\n\n");

    // III

    //create new tree to test the deep copy functionality
    Tree *new_tree;
    new_tree = tree_deep_copy(example_tree);

    // IV

    //check tree for validity
    tree_is_valid(example_tree);


    //Test the functions that check for availability of keys 
    for(int j = 0; j < 10; j++)
    {
        int random_number = arr_of_random_keys[j];
        
        // V

        //All keys need to be contained
        int is_contained_rec = tree_find_key_recursive(example_tree, random_number );

        //The first key is definitely contained
        int is_contained_iter = tree_find_key_iterative(example_tree, random_number + j);
        
        //printf("Key: %d is contained at: %p\n", (start_of_tree + 1 * j), (start_of_tree  + 1 * j)->key);
    }



    // VI

    //test delete functionality
    printf("Deleting\n");
    tree_delete(example_tree);

    return 0;
}
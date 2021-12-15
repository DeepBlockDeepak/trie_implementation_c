// Trie implementation in C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM_CHAR 256

struct trienode_t{
    struct trienode_t *children[NUM_CHAR]; // points to children of node; set to NULL if no child exists


    bool terminal; // checks if a node is the last char of a word

};


/**
 * @brief		mallocs nodes
 * 
 * 
 * @return		trienode_t* - pointer to newly created node
 * 
 */
struct trienode_t *createnode(){
    struct trienode_t *newnode = malloc(sizeof(*newnode));

    for(int i = 0; i < NUM_CHAR; i++){
        newnode->children[i] = NULL;
        // *(*(newnode).children + i) = NULL; //Equivalent?
    }

    newnode->terminal= NULL;

    return newnode;

}


/**
 * @brief		Inserting into the array
 * 
 * 
 * @param		root
 * 
 * @param		signedtext on some machines, 'char's are signed, and for this application
 *                          negative values are not wanted.
 *                          We will typcast it within the function explicitly
 * 
 * @return		true -> new word was inserted
 * 
 * @return		false -> word is already in the trie
 * 
 */
bool trie_insert(struct trienode_t **root, char *signedtext){

    // check if root is NULL; if it is, then create it
    if(!*root){
        *root = createnode();
    }

    // force the potential negative values to be positive with a type cast
    unsigned char *text = (unsigned char*)signedtext;
    int length = strlen(signedtext);
    struct trienode_t *tmp = *root; // used for traversal


    // new node required 
    for(int i = 0; i < length; i++){
        if(tmp->children[text[i]] == NULL){
            tmp->children[text[i]] = createnode();
        }
        // traverse tmp to it's child
        tmp = tmp->children[text[i]];
    }


    // if the current node is the terminal node, then it already is in the trie
    //      - so return false because it's already in the trie
    if(tmp->terminal){
        return false;
    }
    else{   // insertion worked
        tmp->terminal = true;
        return true;
    }

}


void print_trie_rec(struct trienode_t *node, unsigned char *prefix, int length){
    unsigned char newprefix[length + 2];
    memcpy(newprefix, prefix, length);
    newprefix[length + 1] = 0;

    if(node->terminal){
        printf("WORD: %s\n", prefix);
    } 

    for(int i = 0; i < NUM_CHAR; i++){
        if(node->children[i] != NULL){
            newprefix[length] = i;
            print_trie_rec(node->children[i], newprefix, length + 1);
        }
    }
}

void printer(struct trienode_t *root){
    if(root == NULL){
        printf("TRIE EMPTY!\n");
        return;
    }

    print_trie_rec(root, NULL, 0);
    
}


int main(){

    struct trienode_t *root = NULL;

    trie_insert(&root, "KIT");
    trie_insert(&root, "CATTLE");
    trie_insert(&root, "KIN");
    trie_insert(&root, "CAT");
    trie_insert(&root, "HAPPY");


    printer(root);

    return 1;
}
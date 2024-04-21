//
// Created by Alex on 19.04.2024.
//

#ifndef VECTOR_TREE_H
#define VECTOR_TREE_H

#include "vector.h"
#include "stdio.h"

#include "float.h"

typedef struct tree_node_t tree_node_t;
typedef tree_node_t* tree_t;

#define STACK_TYPE tree_t*
#include "stack.h"

/**
 * Initializes empty tree
 * @return Empty tree
 */
tree_t tree_init();
/**
 * Destroys all tree nodes
 * @param tree pointer to tree to destroy
 */
void tree_destroy(tree_t* tree);
/**
 * Adds node to tree at given path
 * @param tree Pointer to tree
 * @param value value to add
 * @param path path to node to add
 * @return true if success
 */
bool tree_add(tree_t* tree, double value, char* path);
/**
 * Deletes node at given path at tree
 * @param tree Pointer to tree
 * @param path
 * @return
 */
bool tree_delete(tree_t *tree, char *path);
/**
 * Prints tree
 * @param tree Tree to print
 */
void tree_print(tree_t tree);
/**
 * Checks if tree is empty
 * @return true if tree is empty
 */
bool tree_is_empty(tree_t);
/**
 * Gets value from tree node
 * @param node Tree node to get value from
 * @return
 */
double tree_get_value(tree_node_t *node);
/**
 * Find max non terminating node
 * @param tree pointer to tree
 */
double tree_find_max_non_terminating(tree_t *tree);


#endif //VECTOR_TREE_H

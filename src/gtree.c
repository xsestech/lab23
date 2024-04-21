//
// Created by Alex on 20.04.2024.
//
#include "gtree.h"

#define tree_ptr_get_attr_ptr(t, attr) \
  &((*t)->attr)
#define tree_ptr_get_attr(t, attr) \
((*t)->attr)

struct tree_node_t {
  double value;
  tree_node_t *child;
  tree_node_t *brother;
};

tree_t tree_init() {
  return NULL;
}
bool tree_add(tree_t *tree, double value, char *path) {
  if (*path != '\0' && *tree == NULL) {
    return false;
  }
  if (*path == '\0') {
    tree_node_t *temp = malloc(sizeof(tree_node_t));
    temp->child = NULL;
    temp->value = value;
    temp->brother = *tree;
    *tree = temp;
    return true;
  }
  if (*path == 'c') {
    return tree_add(tree_ptr_get_attr_ptr(tree, child), value, path + 1);
  }
  if (*path == 'b') {
    return tree_add(tree_ptr_get_attr_ptr(tree, brother), value, path + 1);
  }

  return false;
}

bool tree_delete_recursive(tree_t *tree, tree_t *last_node, char *path) {
  if (tree == NULL) return false;
  if (*path != '\0' && *tree == NULL) {
    return false;
  }
  if (*path == '\0') {
    tree_t tmp = *tree;
    if (last_node != NULL) {
      tree_ptr_get_attr(last_node, child) = tree_ptr_get_attr(tree, brother);
    }
    tree_destroy(&tmp->child);
    *tree = NULL;
    free(tmp);
    tmp = NULL;
    return true;
  }
  if (*path == 'c') {
    return tree_delete(tree_ptr_get_attr_ptr(tree, child), path + 1);
  }
  if (*path == 'b') {
    return tree_delete(tree_ptr_get_attr_ptr(tree, brother), path + 1);
  }

  return false;
}

bool tree_delete(tree_t *tree, char *path) {
  return tree_delete_recursive(tree, NULL, path);
}

void tree_print_recursive(tree_t tree, int h) {
  if (tree == NULL) {
    return;
  }
  for (int i = 0; i < h; i++) {
    printf("\t");
  }
  printf("%.2f", tree->value);
  if (tree->child != NULL) {
    printf(":");
  }
  printf("\n");
  tree_print(tree->child);
  tree_print(tree->brother);
}

void tree_print(tree_t tree) {
  tree_print_recursive(tree, 0);
}

void tree_destroy(tree_t *tree) {
  if (tree == NULL) return;
  if (*tree == NULL) return;
  tree_destroy(tree_ptr_get_attr_ptr(tree, child));
  tree_destroy(tree_ptr_get_attr_ptr(tree, brother));
  free(*tree);
}
double tree_find_max_non_terminating(tree_t *tree) {
  if (*tree == NULL) return DBL_MIN;
  double max_value = DBL_MIN;
  stack_handle_t stack = stack_init();
  stack_push(stack, tree);
  while(!stack_is_empty(stack)) {
    tree_t* tree_tmp = stack_pop(stack);
    if(tree_ptr_get_attr(tree_tmp, child) != NULL) {
      stack_push(stack, tree_ptr_get_attr_ptr(tree_tmp, child));
    }
    if(tree_ptr_get_attr(tree_tmp, brother) != NULL) {
      stack_push(stack, tree_ptr_get_attr_ptr(tree_tmp, brother));
    }
    if (tree_ptr_get_attr(tree_tmp, value) > max_value && (tree_ptr_get_attr(tree_tmp, child) != NULL ||
    tree_ptr_get_attr(tree_tmp, brother) != NULL)) {
      max_value = tree_ptr_get_attr(tree_tmp, value);
    }
  }
  stack_destroy(stack);
  return max_value;

  // tree_find_max_non_terminating(tree_ptr_get_attr_ptr(tree, child), max_value);
  // tree_find_max_non_terminating(tree_ptr_get_attr_ptr(tree, brother), max_value);
  // if (tree_ptr_get_attr(tree, value) > *max_value && (tree_ptr_get_attr(tree, child) != NULL ||
  //   tree_ptr_get_attr(tree, brother) != NULL)) {
  //   *max_value = tree_ptr_get_attr(tree, value);
  // }
}

bool tree_is_empty(tree_t tree) {
  return tree == NULL;
}
double tree_get_value(tree_node_t *node) {
  return node->value;
}

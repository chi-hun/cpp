// 15-2 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fuc.h"

struct Node *create_Node(int data);
struct Node *insert_node(struct Node *befor_node, int data);
void destroy_node(struct Node *de_node,  struct Node *first_node);
void print_Node(struct Node *node);

struct Node {
  int data;
  struct Node *nextNode;
};

int main(int argc, char **argv) {
  struct Node *node_1 = create_Node(109);
  struct Node *node_2 = insert_node(node_1, 110);
  struct Node *node_3 = insert_node(node_2, 210);
  struct Node *node_4 = insert_node(node_3, 410);

  print_Node(node_1);

  destroy_node(node_3, node_1);
  print_Node(node_1);

  free(node_1);
  free(node_2);
  free(node_3);
  free(node_4);

  return 0;
}

struct Node *create_Node(int data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode -> data = data;
  newNode -> nextNode = NULL;
  return newNode;
}

struct Node *insert_node(struct Node *befor_node, int data) {
  struct Node *newNode = create_Node(data);
  newNode -> nextNode = befor_node -> nextNode;
  befor_node -> nextNode = newNode;
  
  return newNode;
}

void destroy_node(struct Node *de_node,  struct Node *first_node) {
  struct Node *next = first_node;
  if (de_node == first_node) {
    free(de_node);
    return;
  }
  
  while (next) {
    if (next == de_node) {
      next -> nextNode = de_node -> nextNode;
      free(de_node);
      return;
    }
    next = next -> nextNode;
  }

}

void print_Node(struct Node *node) {
  while (node) {
    printf("%d\n", node->data);
    node = node -> nextNode;
  }
}


#include <stdio.h>
#include <stdlib.h>

struct linked_list {
  int value;
  struct linked_list *next;
};

struct node {
  int value;
  struct node *next;
  struct linked_list *edges;
};

struct graph {
  struct node *nodes;
};

struct linked_list *make_linked_list(int value) {
  struct linked_list *new_linked_list = malloc(sizeof(struct linked_list));
  new_linked_list->value = value;
  new_linked_list->next = NULL;
  return new_linked_list;
}

struct node *make_node(int value, int edge) {
  struct node *new_node = malloc(sizeof(struct node));
  new_node->value = value;
  new_node->next = NULL;
  new_node->edges = make_linked_list(edge);
  return new_node;
}

void add_node(struct graph *mod_graph, int head, int edge) {
  if (mod_graph->nodes == NULL) {
    mod_graph->nodes = make_node(head, edge);
  } else {
    struct node *current_node = mod_graph->nodes;
    while (current_node->next != NULL) {
      if (current_node->value == head) {
        struct linked_list *current_edge = current_node->edges;
        while (current_edge->next != NULL) {
          current_edge = current_edge->next;
        }
        current_edge->next = make_linked_list(edge);
        break;
      }
      current_node = current_node->next;
    }
    if (current_node->next == NULL) {
      if (current_node->value == head) {
        struct linked_list *current_edge = current_node->edges;
        while (current_edge->next != NULL) {
          current_edge = current_edge->next;
        }
        current_edge->next = make_linked_list(edge);
      } else {
        current_node->next = make_node(head, edge);
      }
    }
  }
}

void print_all(struct graph *graph_to_print) {
  struct node *current_node = graph_to_print->nodes;
  while (current_node->next != NULL) {
    printf("%d : ", current_node->value);
    struct linked_list *current_edge = current_node->edges;
    while (current_edge->next != NULL) {
      printf("%d->", current_edge->value);
      current_edge = current_edge->next;
    }
    printf("%d\n", current_edge->value);
    current_node = current_node->next;
  }
  if (current_node->next == NULL) {
    printf("%d : ", current_node->value);
    struct linked_list *current_edge = current_node->edges;
    while (current_edge->next != NULL) {
      printf("%d->", current_edge->value);
      current_edge = current_edge->next;
    }
    printf("%d\n", current_edge->value);
  }
}

struct node *find_node(struct graph *graph_to_search, int value) {
  struct node *start_node = graph_to_search->nodes;
  while (start_node != NULL) {
    if (start_node->value == value) {
      break;
    } else {
      start_node = start_node->next;
    }
  }
  return start_node;
}

int is_visited(struct linked_list *search_list, int value) {
  struct linked_list *current_search = search_list;
  if (current_search == NULL) {
    return 0;
  }
  while (current_search->next != NULL) {
    if (current_search->value == value) {
      return 1;
    }
    current_search = current_search->next;
  }
  if (current_search->value == value) {
    return 1;
  }
  return 0;
}

void add_search(struct linked_list *search_list, int value) {
  struct linked_list *current_search = search_list;
  while (current_search->next != NULL) {
    current_search = current_search->next;
  }
  current_search->next = make_linked_list(value);
}

void dfs(struct graph *main_graph, int from, struct linked_list *search_list) {
  
  if (search_list == NULL) {
    search_list = make_linked_list(from);
    printf("-> %d ", from);
  } else {
    if (is_visited(search_list, from) == 1) {
      return;
    }
    printf("%d ", from);
    add_search(search_list, from);
  }
  
  struct node *current_node = find_node(main_graph, from);
  struct linked_list *edges = current_node->edges;
  while (edges != NULL) {
    dfs(main_graph, edges->value, search_list);
    edges = edges->next;
  }
}

void bfs(struct graph *main_graph, int from, struct linked_list *search_list) {
  if (search_list == NULL) {
    
  }
}

int main() {
  struct graph *main_graph = malloc(sizeof(struct graph));
  main_graph->nodes = NULL;
  add_node(main_graph, 0,1);
  add_node(main_graph, 0,2);
  add_node(main_graph, 1,2);
  add_node(main_graph, 2,0);
  add_node(main_graph, 2,3);
  add_node(main_graph, 3,3);
  print_all(main_graph);
  
  printf("\nsearch DFS");
  struct linked_list *search_list = NULL;
  dfs(main_graph, 2, search_list);
  
  printf("\nsearch BFS");
  printf("\n");
  return 0;
}

#ifndef __GRAPH__
#define __GRAPH__

#include "gluethread/glthread.h"
#include "net.h"

/* global constant values*/
#define GRAPH_NAME_SIZE 32
#define NODE_NAME_SIZE 16
#define INTF_NAME_SIZE 16
#define MAX_INTF_PER_NODE 10

typedef struct node_ Node;
typedef struct link_ Link;

typedef struct graph_ {
	char topology_name[GRAPH_NAME_SIZE];
	glthread list;
} Graph;

typedef struct interface_ {
	char intf_name[INTF_NAME_SIZE];
	Node *src_node;
	Link *link;
	IntfNetProp intf_net_prop;

} Interface;

struct node_ {
	char node_name[NODE_NAME_SIZE];
	Interface *intf[MAX_INTF_PER_NODE];
	glthread glue;
	NodeNetProp node_net_prop;
};

struct link_ {
	Interface intf1;
	Interface intf2;
	unsigned int cost;
};

GLTHREAD_TO_STRUCT(glue_to_node, Node, glue)

int
ret_empty_intf_slot(Node *node);

Node *
get_other_node(Interface *intf);

Interface *
get_intf_from_intf_name(Node *node, char *intf);

Node *
get_node_from_node_name(Graph *graph, char *node);

Graph *
create_graph(char *topo_name);

Node *
create_node(Graph *graph, char *node_name);

void
insert_link(Node* n1, Node* n2, char *from_if,
		char *to_if, unsigned int cost);

void
dump_graph(Graph *graph);

void
dump_node(Node *node);

void
dump_interface(Interface *intf);

#endif

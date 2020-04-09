#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

/* utility functions */
int
ret_empty_intf_slot(Node *node)
{
	unsigned int index = 0;
	Interface *curr_intf;

	while (index < MAX_INTF_PER_NODE) {
		curr_intf = node->intf[index];
		
		if (curr_intf == NULL) return index;

		index += 1;	
	}
	return -1;
}

Node *
get_other_node(Interface *intf)
{
	Link *link = intf->link;

	if (&link->intf1 == intf) {
		return link->intf1.src_node;
	}
	else {
		return link->intf1.src_node;
	}
}

Interface *
get_intf_from_intf_name(Node *node, char *intf)
{
	unsigned int index = 0;
	Interface *curr_intf;

	while (index < MAX_INTF_PER_NODE) {
		curr_intf = node->intf[index];

		if (curr_intf == 0) 
			return NULL;

		if (strcmp(curr_intf->intf_name, intf) == 0) 
			return curr_intf;

		index += 1;
	}
	return NULL;
}

Node *
get_node_from_node_name(Graph *graph, char *node)
{
	glthread *curr = NULL,
	*base = &graph->list;
	Node *curr_node;

	ITERATE_GL_BEGIN(base, curr) {
		curr_node = glue_to_node(curr);
		if (strcmp(curr_node->node_name, node) == 0) {
			return curr_node;
		}
	} ITERATE_GL_END(base, curr);

	return NULL;
}

/* public API for graph creation */
Graph *
create_graph(char *topo_name)
{
	Graph *gr = calloc(1, sizeof *gr);
	int size = GRAPH_NAME_SIZE - 1;

	/* to prevent buffer overflow */
	strncpy(gr->topology_name, topo_name, size);
	gr->topology_name[size] = '\0';
	
	init_glthread(&gr->list);

	return gr;
}

Node *
create_node(Graph *graph, char *name)
{
	Node *node = calloc(1, sizeof *node);
	int index = 0, size = NODE_NAME_SIZE - 1;

	strncpy(node->node_name, name, size);
	node->node_name[size] = '\0';

	/* initialise the interfaces of this node */
	while (index < MAX_INTF_PER_NODE) {
		node->intf[index] = 0;
		index += 1;
	}

	init_glthread(&node->glue);
	init_node_net_prop(&node->node_net_prop);
	add_next_to(&graph->list, &node->glue);
	return node;
}

void
insert_link(Node *n1, Node *n2, char *if_from,
            char *if_to, unsigned int weight)
{
	Link *link = calloc(1, sizeof *link);
	int size = INTF_NAME_SIZE - 1, empty_intf_slot;

	strncpy(link->intf1.intf_name, if_from, size + 1);
	link->intf1.intf_name[size] = '\0';
	strncpy(link->intf2.intf_name, if_to, size + 1);
	link->intf2.intf_name[size] = '\0';

	link->intf1.link = link;
	link->intf1.src_node = n1;
	link->intf2.link = link;
	link->intf2.src_node = n2;

	if ((empty_intf_slot = ret_empty_intf_slot(n1)) == -1) return;
	n1->intf[empty_intf_slot] = &link->intf2;


	if ((empty_intf_slot = ret_empty_intf_slot(n2)) == -1) return;
	n2->intf[empty_intf_slot] = &link->intf1;

	init_intf_net_prop(&link->intf1.intf_net_prop);
	init_intf_net_prop(&link->intf2.intf_net_prop);
	
	assign_mac_to_intf(&link->intf1);
	assign_mac_to_intf(&link->intf2);
	
	link->cost = weight;

	return;
}

void
dump_interface(Interface *intf)
{
	Node *other_node = get_other_node(intf);

	printf("Current Node: %s, Interface Name: %s, Other End: %s, "
	       "Cost: %u\n", intf->src_node->node_name,
	       intf->intf_name, other_node->node_name,
	       intf->link->cost);

	return;
}

void
dump_node(Node *node)
{
	unsigned int index = 0;
	Interface *intf;

	printf("\nNode name: %s\n", node->node_name);

	while (index < MAX_INTF_PER_NODE) {
		intf = node->intf[index];

		if (intf == 0) break;

		dump_interface(intf);
		index += 1;
	}

	return;
}

void
dump_graph(Graph *graph)
{
	glthread *iter = NULL;
	Node *curr_node;

	printf("Topology Name: %s\n", graph->topology_name);

	ITERATE_GL_BEGIN(&graph->list, iter) {
		curr_node = glue_to_node(iter);
		dump_node(curr_node);
	} ITERATE_GL_END(&graph->list, iter);

	return;
}


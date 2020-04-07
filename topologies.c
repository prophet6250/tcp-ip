#include "graph.h"

Graph *
build_topo_example()
{
	/* initialise the graph */
	Graph *gr = create_graph("Example");
	
	/* create the nodes of the graph */
	Node *R0 = create_node(gr, "R0"),
	     *R1 = create_node(gr, "R1"),
	     *R2 = create_node(gr, "R2");

	/* insert bidirectional links between
	 * the nodes */
	insert_link(R0, R1, "eth0/0", "eth0/1", 1);
	insert_link(R1, R2, "eth0/1", "eth0/3", 1);
	insert_link(R0, R2, "eth0/4", "eth0/5", 1);

	return gr;
}


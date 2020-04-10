#include "net.h"
#include "graph.h"

Graph *
build_topo_example()
{
#if 0

                          +----------+
                      0/4 |          |0/0
         +----------------+   R0     +---------------------------+
         |     	 40.1.1.1 | 122.1.1.0| 20.1.1.1               	 |
         |                +----------+                           |
         |                                                       |
         |                                                       |
         |                                                       |
         |40.1.1.                                            |20.1.1.
         |0/5                                                    |0/1
     +---+---+                                              +----+-----+
     |       |0/3                                        0/2|          |
     |   R2  +----------------------------------------------+    R1    |
     |	     |30.1.1.                                30.1.1.|          |
     +-------+                                              +----------+

#endif
	Graph *topo = create_graph("Example");
	Node *R0 = create_node(topo, "Dev0"),
	     *R1 = create_node(topo, "Dev1"),
	     *R2 = create_node(topo, "Dev2");

	insert_link(R0, R1, "eth0/0", "eth0/1", 1);
	insert_link(R1, R2, "eth0/2", "eth0/3", 1);
	insert_link(R0, R2, "eth0/4", "eth0/5", 1);

	set_node_loopb_addr(R0, "122.1.1.0");
	set_node_loopb_addr(R1, "122.1.1.1");
	set_node_loopb_addr(R2, "122.1.1.2");

	set_node_intf_ip_addr(R0, "eth0/0", "40.1.1.1", 24);
	set_node_intf_ip_addr(R1, "eth0/1", "20.1.1.1", 24);

	set_node_intf_ip_addr(R1, "eth0/2", "20.1.1.2", 24);
	set_node_intf_ip_addr(R2, "eth0/3", "30.1.1.1", 24);

	set_node_intf_ip_addr(R0, "eth0/4", "30.1.1.2", 24);
	set_node_intf_ip_addr(R2, "eth0/5", "40.1.1.2", 24);

	return topo;
}


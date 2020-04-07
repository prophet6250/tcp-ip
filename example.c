#include "graph.h"

extern Graph *build_topo_example();

int main()
{
	Graph *graph = build_topo_example();
	dump_graph(graph);

	return 0;
}

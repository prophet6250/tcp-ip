#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "net.h"
#include "utils.h"

void
init_intf_net_prop(IntfNetProp *intf_net_prop)
{
	memset(intf_net_prop->MAC.mac_addr, 0, 8);
	memset(intf_net_prop->IP.ip_addr, 0, 16);

	intf_net_prop->is_IP_config = 0;
	intf_net_prop->mask = 0;

	return;
}

void
init_node_net_prop(NodeNetProp *node_prop)
{
	memset(node_prop->loopb_addr.ip_addr, 0, 16);

	node_prop->is_loopb_config = 0;

	return;
}

int
set_node_loopb_addr(Node *node, char *ip)
{
	NodeNetProp *curr_prop = &node->node_net_prop;

	if (curr_prop->is_loopb_config) {
		printf("current loopback is already configured\n");
		printf("curr loopback address is: %s\n", NODE_LPB(node));

		return 1;
	}

	curr_prop->is_loopb_config = 1;
	strncpy(curr_prop->loopb_addr.ip_addr, ip, 16);
	curr_prop->loopb_addr.ip_addr[15] = '\0';

	return 0;
}

int
set_node_intf_ip_addr(Node *node, char *local_intf,
		char *ip, char mask)
{
	Interface *curr_intf = get_intf_from_intf_name(node, local_intf);
	if (curr_intf == 0) {
		printf("target interface to be set not found\n");
		return 1;
	}
	
	curr_intf->intf_net_prop.mask = mask;
	curr_intf->intf_net_prop.is_IP_config = 1;

	strncpy(INTF_IP(curr_intf), ip, 16);
	curr_intf->intf_net_prop.IP.ip_addr[15] = '\0';

	return 0;
}

int
unset_node_intf_ip_addr(Node *node, char *local_intf)
{
	Interface *curr_intf = get_intf_from_intf_name(node, local_intf);

	if (curr_intf == NULL) {
		return 1;
	}
	
	curr_intf->intf_net_prop.mask = '\0';
	curr_intf->intf_net_prop.is_IP_config = 0;
	strncpy(INTF_IP(curr_intf), '\0', 16);

	return 0;
}

void
assign_mac_to_intf(Interface *intf)
{
	if (intf == NULL) {
		return;		
	}

	int index = 0;
	srand(time(0));
	sleep(1);

	while (index < 8) {
		INTF_MAC(intf)[index] = rand() % 255;
		index += 1;
	}
	return;
}

void
dump_net_intf(Interface *intf)
{
	Node *curr_node = intf->src_node,
	     *other_node = get_other_node(intf);
	IntfNetProp *curr_prop = &intf->intf_net_prop;
	
	printf("Interface Name: %s, Connected Node: %s, "
			"Cost: %u\n", intf->intf_name, other_node->node_name,
			intf->link->cost);

	printf("MAC: %x:%x:%x:%x:%x:%x\n", INTF_MAC(intf)[0],
		INTF_MAC(intf)[1],INTF_MAC(intf)[2],INTF_MAC(intf)[3],
		INTF_MAC(intf)[4],INTF_MAC(intf)[5]);

	if (intf->intf_net_prop.is_IP_config) {
		printf("Interface IP: %s/%c\n", INTF_IP(intf), curr_prop->mask);
	}
	else {
		printf("Interface IP: %s/'nil'\n", INTF_IP(intf));
	}
	return;
}

void
dump_net_node(Node *node)
{
	unsigned int index = 0;
	Interface *intf = NULL;

	printf("\nSource Node: %s", node->node_name);
	if (node->node_net_prop.is_loopb_config) {
		printf(", LOOPBACK: %s", NODE_LPB(node));
	}
	printf("\n");

	while (index < MAX_INTF_PER_NODE) {
		intf = node->intf[index];

		if (intf == 0) break;

		printf("%d) ", index + 1);
		dump_net_intf(intf);
		printf("\n");

		index += 1;
	}

	return;
}

void
dump_net_graph(Graph *graph)
{
	glthread *curr = NULL,
		 *base = &graph->list;
	Node *curr_node = NULL;
	
	printf("Graph Topology Name: %s\n", graph->topology_name);

	ITERATE_GL_BEGIN(base, curr) {
		curr_node = glue_to_node(curr);
		dump_net_node(curr_node);
	} ITERATE_GL_END(base, curr);

	return;
}

Interface *
get_matching_subnet_intf(Node *node, char *IP)
{
	int index = 0;
	Interface *curr_intf = 0;
	char intf_address[16], intf_subnet[16], IP_subnet[16];
	char mask;
	for (; index < MAX_INTF_PER_NODE; index++) {
		curr_intf = node->intf[index];

		if (curr_intf == 0) return 0;
		if (IS_INTF_L3(curr_intf) == 0) continue;

		strncpy(intf_address, INTF_IP(curr_intf), 16);
		mask = curr_intf->intf_net_prop.mask;

		applymask(intf_address, mask, intf_subnet);
		applymask(IP, mask, IP_subnet);

		if (strncmp(intf_subnet, IP_subnet, 16) == 0) {
			return curr_intf;			
		}
	}
	return 0;
}

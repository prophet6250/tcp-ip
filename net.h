#ifndef __NET__
#define __NET__

#include <memory.h>

/* macros */
#define INTF_MAC(intf)     ((intf)->intf_net_prop.MAC.mac_addr)
#define INTF_IP(intf)      ((intf)->intf_net_prop.IP.ip_addr)
#define NODE_LPB(node) 	   ((node)->node_net_prop.loopb_addr.ip_addr)
#define IS_INTF_L3(intf)   ((intf)->intf_net_prop.is_IP_config ? 1 : 0)

/* forward declarations */
typedef struct graph_ Graph;
typedef struct node_ Node;
typedef struct interface_ Interface;

/* data structures */
typedef struct ip_addr {
	unsigned char ip_addr[16];
} IpAddr;

typedef struct mac_addr {
	unsigned char mac_addr[8];
} MacAddr;

typedef struct node_net_prop {
	int is_loopb_config;
	IpAddr loopb_addr;
} NodeNetProp;

typedef struct intf_net_prop {
	char mask;
	int is_IP_config;
	MacAddr MAC;
	IpAddr IP;
} IntfNetProp;

/* APIs to modify the networking properties of the node */
void
init_intf_net_prop(IntfNetProp *intf_net_prop);

void
init_node_net_prop(NodeNetProp *node_prop);

int
set_node_loopb_addr(Node *node, char *ip);

int
set_node_intf_ip_addr(Node *node, char *local_intf,
                      char *ip, char mask);

int
unset_node_intf_ip_addr(Node *node, char *local_intf);

void
assign_mac_to_intf(Interface *intf);

void
dump_net_graph(Graph *graph);

Interface *
get_matching_subnet_intf(Node *node, char *IP);

#endif


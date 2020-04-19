#define IS_MAC_BROADCAST(mac) \
	(mac[0] == mac[1] == mac[2] == mac[3] == mac[4]  == mac[5] == -1)

void
applymask(unsigned char *old_IP, char mask,
          unsigned char *new_IP);

void
fill_mac_with_broadcast(unsigned char *mac);

unsigned int
convert_IP_to_int(unsigned char *IP);

void
convert_IP_to_string(unsigned int IP, unsigned char *output);

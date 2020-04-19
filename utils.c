#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"

void
applymask(unsigned char *old_IP, char mask, unsigned char *new_IP)
{
	unsigned int address_bin, mask_bin, masked_IP_bin, index;
	inet_pton(AF_INET, old_IP, &address_bin);

	address_bin = htonl(address_bin);

	/* this loop puts necessary 0s in the binary format of the subnet mask
	 * to be applied */
	for (index = 0; index <= (32 - mask); index++)
		mask_bin = 0xffffffff << index;

	masked_IP_bin = address_bin & mask_bin;

	masked_IP_bin = ntohl(masked_IP_bin);
	inet_ntop(AF_INET, &masked_IP_bin, new_IP, 16);

	return;
}

void 
fill_mac_with_broadcast(unsigned char *mac)
{
	unsigned int index = 0;

	while (index < 6) {
		mac[index] = 0xFF;
		index += 1;
	}

	return;
}

static unsigned int
calculate_digits(unsigned int num)
{
	int index = 1, digits = 1;
	while (index < 4) {
		if ((num / (unsigned int)pow(10, index)) > 0) {
			index += 1;
			digits += 1;
		}
		else break;
	}
	
	return digits;
}

static char *
int_to_string(unsigned int num)
{
	unsigned int digits = calculate_digits(num), index, curr_digit,
	    string_index = 0;

	index = digits;
	char *string = malloc(sizeof *string * (digits + 1));
	
	while (index > 0) {
		curr_digit = (num % (unsigned int)pow(10, index)) / 
				(unsigned int)pow(10, index - 1);
		string[string_index] = 48 + curr_digit;
		string_index += 1;
		index -= 1;
	}

	return string;
}

unsigned int
convert_IP_to_int(unsigned char *IP) 
{
	unsigned char *octet,
	     *buffer = IP;
	unsigned int address = 0, octet_count = 0;

	while (octet = strtok_r(buffer, ".", &buffer)) {
		if (octet_count < 4) {
			address <<= 8;
			octet_count += 1;
		}

		address |= atoi(octet);
	}
	
	return address;
}

void
convert_IP_to_string(unsigned int address, unsigned char *output)
{
	htonl(address);
	unsigned int buffer;
	char IP[16];
	char *current_octet;

	for (int i = 0; i < 4; i++) {
		buffer = address;
		buffer <<= 24 - 8*i;
		buffer >>= 24;

		current_octet = int_to_string(buffer);
		strncat(IP, current_octet, strlen(current_octet));

		if (i < 3) strncat(IP, ".", 2);
	}
	return;
}


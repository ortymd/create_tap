#include <func.h>
#include <net/ethernet.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

void test1()
{
	struct ether_addr server_ether_addr;

	if(	discover_server( &server_ether_addr ) != 0) 
		printf("Failed: Server not found.\n");
	else
		printf("Success.\n");
}

void test2()
{
	int net_fd;
	net_fd = get_net_fd();

	if( net_fd == -1 )
	{
		printf("Failed: file descriptor not returned.\n");
		perror("Error:\t");
	}
	else
		printf("Success.\n");
}

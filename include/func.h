#include <net/ethernet.h>

int get_net_fd(void);		/* returns file descriptor to use to read/write to network */
int discover_server( struct ether_addr* server_ether_addr );
int get_src_ether_addr( struct ether_addr src_ether_addr );
int gen_discover_server_req();
void test1();
void test2();

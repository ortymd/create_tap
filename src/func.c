#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <func.h>

int get_net_fd(void) {

  struct ifreq ifr;
  int fd, err;
  char *clonedev = "/dev/net/tun";	/* this block device is clone device as used
																			 to create any tun/tap interface */
  /* Arguments taken by the function:
   *
   * char *dev: the name of an interface (or '\0'). MUST have enough
   *   space to hold the interface name if '\0' is passed
   * int flags: interface flags (eg, IFF_TUN etc.)
   */

   /* open the clone device */
   if( (fd = open(clonedev, O_RDWR)) < 0 ) {
     return fd;
   }

   memset(&ifr, 0, sizeof(ifr));

   ifr.ifr_flags = IFF_TAP;   /* TAP device is neede to read/write eth frames */

   if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
     close(fd);
     return err;
   }

  /* this is the special file descriptor that the caller will use to read/write 
   *  virtual interface */
  return fd;
}

int discover_server(struct ether_addr* server_ether_addr)
{
	struct ether_addr src_ether_addr;
	struct ether_addr dest_ether_addr;
	unsigned	ether_addr_sz = sizeof( struct ether_addr );

	get_src_ether_addr( src_ether_addr );					/*  this is our MAC */
	memset( &dest_ether_addr, 1, ether_addr_sz );	/* this is broadcast addr */

	if( gen_discover_server_req()	!= 0 )		/* generate discover server request */
		return -1;
	else
		return 0;
}

int get_src_ether_addr( struct ether_addr src_ether_addr )
{
	int fd;
	struct ifreq ifr;
	char *iface = "eth2";		/* this should be fixed to get platform indep iface name */
	unsigned	ether_addr_sz = sizeof( struct ether_addr );

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	ifr.ifr_addr.sa_family = AF_INET;
	strcpy(ifr.ifr_name, iface);

	ioctl(fd, SIOCGIFHWADDR, &ifr);
	close(fd);

	memcpy( &src_ether_addr, ifr.ifr_hwaddr.sa_data, ether_addr_sz );

	return 0;
}

int gen_discover_server_req()
{
	return -1;
}

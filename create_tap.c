#include <linux /if.h>
#include <linux /if_tun.h>

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

int main()
{
	int fd = get_net_fd();
	return 0;
}

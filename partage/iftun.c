//THIEL Samantha, COZZOLINO Christine, M1 Informatique - Projet Réseaux

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include "iftun.h"



int tun_alloc(char *dev) {
  struct ifreq ifr;
  int fd, err;

  if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ) {
    perror("alloc tun");
    return -1;
  }

  memset(&ifr, 0, sizeof(ifr));

  /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
   *        IFF_TAP   - TAP device
   *
   *        IFF_NO_PI - Do not provide packet information
   */
  ifr.ifr_flags = IFF_TUN;
  if( *dev ) strncpy(ifr.ifr_name, dev, IFNAMSIZ);

  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
    close(fd);
    return err;
  }
  strcpy(dev, ifr.ifr_name);
  return fd;
}

int write_dst(int src, int dst) {
  char buffer[1500];
  int nread;

  /* Note that "buffer" should be at least the MTU size of the interface, eg 1500   bytes */
  nread = read(src,buffer,sizeof(buffer));

  if(nread < 0) {
    perror("Reading from interface");
    return -1;
  }

  write(dst, buffer, nread);

  return 0;
}

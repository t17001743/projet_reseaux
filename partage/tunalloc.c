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

/*------------------------------------------------------------------------------*/

int tun_alloc(char *dev){
    struct ifreq ifr;
    int fd, err;

    if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ){
        perror("alloc tun");
        exit(-1);
    }

    memset(&ifr, 0, sizeof(ifr));

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers) 
    *        IFF_TAP   - TAP device  
    *
    *        IFF_NO_PI - Do not provide packet information  
    */ 
    ifr.ifr_flags = IFF_TUN; 
    if( *dev )
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
        close(fd);
        return err;
    }
    strcpy(dev, ifr.ifr_name);
    return fd;  //retourne un tunfd
}    

/*------------------------------------------------------------------------------*/

int main (int argc, char** argv){

    if(argc < 2){
        printf("Usage: ./test_iftun tun0\n");
        return 1;
    }

    int tunfd;
    printf("Création de %s\n",argv[1]);
    tunfd = tun_alloc(argv[1]);  //un descripteur de fichier est renvoyé
    //permet de lire ce qui est envoyé à l'interface par un appel read
  
    printf("Faire la configuration de %s...\n",argv[1]);
  
    //script shell pour la config de tun0
    printf("Utilisation du script shell pour la configuration de tun0...\n");
    system("sh configure-tun.sh");
  
    printf("Appuyez sur une touche pour continuer\n");
    getchar();
    printf("Interface %s Configurée:\n",argv[1]);
    system("ip addr");
  
    /*ne pas appuyer tout de suite, laisser tourner le programme dans le terminal courant et utiliser un autre terminal pour ping6 (interface non persistante)*/
    printf("Appuyez sur une touche pour terminer\n");
    getchar();
  
    return 0;
}

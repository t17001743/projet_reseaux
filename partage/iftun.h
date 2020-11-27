//THIEL Samantha, COZZOLINO Christine, M1 Informatique - Projet Réseaux

#ifndef IFTUN_H
#define IFTUN_H

/**
 * Création d'une interface virtuelle tun
 * @param dev le nom de l'interface virtuelle
 * @return un tunfd
 */
int tun_alloc(char *dev);

/**
 * Recopie perpétuellement toutes les données lisibles depuis la source dans le fichier destinataire
 * @param src fichier descripteur source
 * @param dst fichier descripteur destination
 * @return 0 si les données ont été écrites avec succès de src vers dst, -1 sinon
 */
int write_dst(int src, int dst);


#endif

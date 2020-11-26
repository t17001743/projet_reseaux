#Commandes de configuration pour l'interface tun0

#L'interface est DOWN par défaut, on la met à UP
ip -6 link set tun0 up

#On lui affecte une adresse IP
ip -6 addr add fc00:1234:ffff::1/7 dev tun0


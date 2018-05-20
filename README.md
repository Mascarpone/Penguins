# PENGUINS

~achan ~ffichant ~flevern ~sgruchet


## Sommaire

  I.   Contenu du dépot
  II.  Installer les librairies
  III. Compiler le programme
  IV.  Utiliser le programme


## I. Contenu du dépot

  - dossier *src/server* : contient les fichiers sources du serveur

  - dossier *src/clients* : contient les fichiers sources des IA (elles seront compilées dans ce dossier)

  - dossier *test/test_serveur* : contient des tests unitaires pour les fonctions du serveur

  - dossier *test/graphic* : teste l'interface graphique

  - dossier *test/main* : permet de lancer le programme sur différentes stratégies

  - dossier *rsc* : contient toutes les sources nécessaires à l'interface graphiques

  - dossier *doc* : contient la documentation du code générée avec Doxygen

  - dossier *rapport* : contient le rapport en pdf 


## II. Installer les librairies

Pour pouvoir utiliser l'interface graphique, les librairies suivantes sont nécessaires :
  -  SDL2
  -  freetype2
  -  SDL2_ttf


## III. Compiler le programme

  - Le serveur
Se rendre dans le dossier *test/test_main/* et lancer la commande `make`. Un executable letsplay est généré.


  - Les joueurs
Se rendre dans le dossier *lib/* et lancer la commande `make`. Des librairies dynamique sont générées.
Si vous compilez sous mac il faut utiliser dans le makefile -undefined dynamic_lookup sinon il faut le retirer.


## IV. Utiliser le programme

Lancer la commande 'make' à la racine, un dossier build est créé. Aller dans le dossier build et lancer la commande `./letsplay ./lib/<bot1>.so ./lib/<bot2>.so <autres bots>`.

IL FAUT APPUYER SUR LA TOUCHER ENTREE POUR FAIRE AVANCER LES ETATS DU JEU APRES L'AFFICHAGE DU TITRE. 

Par défaut, la map **mapHexa36.txt** est utilisée et le nombre de pions par joueur est fixé à 2. Ceci peut-être modifié directement dans *src/server/main.c*.




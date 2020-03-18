# Sense-Dive

## Description et lien vers projet

Sense &amp; Dive utilise un dispositif d’écrans fixés au plafond du matériel roulant (bus, tram ou métro) sensible à la présence des voyageurs qui interagissent avec eux en touchant les barres de maintien.

Espace immersif interactif à l'environnement d'un bus de ville : http://www.erasme.org/Sense-Dive


## Scénarios

***(à sélectionner au `pavé numérique` du clavier)***

`Touche 0` - *Canon à pixel*
Interaction : *afficher une image en envoyant les pixels répartis de façon égale, autour de 4 canons à pixels correspondant aux 4 barres de maintien*
(plusieurs images possibles, appuyer sur `0` pour changer d'image)

Intégrer de nouvelles images (specs : ):
Sous macOS, dans le Finder > Aller > se connecter au serveur et taper : `afp://192.168.71.202/Home Directory/SenseAndDive/of_v0.9.8_linux64_release/apps/Sense-Dive/senseAndDive/bin/data/images/`
ou
- se connecter sur la machine `ssh erasme@192.168.71.202`
- Puis copier les images dans `/home/SenseAndDive/of_v0.9.8_linux64_release/apps/Sense-Dive/senseAndDive/bin/data/images`
(l'ordre des fichiers est alphabétique)
______________
`Touche 1` - *Aimant*
Interaction : *attirer un maximum d'items vers soi, en tenant la barre de maintien*
Plusieurs décors (appuyer sur `1` pour changer de décor):
- Ciel bleu / avions en papier / nuages :
- Espace / planètes / étoiles :
- Orage / nuages
______________
`Touche 2` - *Signalétique*
*Pas d'interaction avec les barres -> simple affichage de flèches pour inciter les voyageurs à investir le fond du bus*
______________
`Touche 3` - *Labyrinthe*
Interaction : *à plusieurs (4 max), orienter le décor du labyrinthe pour diriger la bille vers le* **Terminus**

## Matériel et scénographie
- 1 environnement de bus (sièges, 4 barres de maintien, parois et toit avec 2 écrans de rétrovidéoprojection)
- 1 machine Shuttle
- 1 vidéoprojecteur installé en hauteur au dessus du bus
- 1 dispositif interactif (1 arduino + 1 pieuvre Grove + 4 prolongateurs RJ45 + 4 capteurs touch + 1 câble USB)

Besoins techniques
- 1 arrivée électrique (VP + machine)

## Mapping sur le PC d'affichage 
Appuyer sur Shift+W (mode wrapping)
Identifier sur quel écran on fait le mapping (un écran à la fois)
Pour plus de précisions, sélectionner les ancres au clavier avec les touches 1 , 2 , 3 , 4 (pour retirer l'affichage du menu : Espace)
Pour changer d'écran de travail : w
Positionner les ancres aux bons endroits avec la souris
Appuyer sur D (DEBUG), un contour rouge apparait
Positionner les ancres au clavier avec les flèches
Pour sauvegarder : Echap
Pour sortir du mode Wrapping : Shift+W (ne pas sortir pour garder le mapping)
Pour sortir du mode Debug : D

## TO DO 
Améliorer / Imaginer de nouveaux scénarios (Certains sont injouables)
remplacer la projection par un écran ou 2 (/!\ attention à la question de l'ossature)
Refaire l'ossature pour supporter un écran
Electronique : Faire en sorte que les poteaux en acier soient au même potentiel que l'Arduino. Donc, par exemple, utiliser la tresse des câbles RJ45 à connecter d'un côté aux tubes (en ayant enlevé la peinture isolante), de l'autre côté à un point de masse de l'Arduino. 

# -M1-Prog_concu-Projet

 The strategy choosen is based on the hypothesis that all snakes know
 the position of the fruit. If they can go to the cell that represent
 the shortest way to fruit, they do it. But if the best(s) cell(s)
 are taken or obstacle part a random direction is choosen
 
 This strategy isn't the best and snake lose pretty often, but they can win or lose.
 you can decrease the amount of point to win if you want to check the victory condition
 instead of launch many the program

 A MUTEX is necessary to avoid two snake to earn points from the same fruit
 because they reach him at the same time.
 
 To execute the program you have to do  (with your choosen values):

 $ gcc -D n=15 -D m=15 -D l=1 -D s=4 -pthread  main.c -o main
 $ ./main
 
 # NOTE1: 
 The lvl 1 return a segmentation fault and unfortunatly we didn't archive the correction of the bug
 
 # NOTE2: 
 I was the only one to push but my co-worker Lydia Messaoui worked on : 
 
  - Options implementation
  - Allow snake to change side of the grid (unfortunatly we didn't archieve this goal)
  - Check for graphical implementation (Unfortunatly also we didn't archieve this goal)

I(ROQUI DAVID) worked on:
- Réaliser une interface graphique (affichage en ligne de commande) du plateau
- Chaque Snake doit être implémenté dans un thread unique ou dans un proces-
sus (vous avez le choix).
- Réaliser le mécanisme qui permet à chaque processus (snake) de communiquer
avec le processus plateau afin de lui indiquer son déplacement. Attention, deux
Snaks ne peuvent pas se trouver sur les mêmes cases au même temps.
- Chaque Snake se déplace d’une façon aléatoire afin de capturer des fruits.
- Réaliser une interface graphique (affichage en ligne de commande) du plateau.
- Réaliser la fonction qui permet de gérer les scores
-Si un fruit est capturé exactement au même moment par deux snaks que se
passe-il ? résoudre ce conflit à l’aide des Mutex.
- Améliorer la stratégie des Snakes afin de les rendre performants (Work, but the strategy choosen can be upgraded to a better version) 
- Implémenter le système de gestion des scores dans un thread afin d’alléger le
processus plateau.
- A chaque fois qu’un Snake grandi il voit sa sa vitesse diminue de 10%

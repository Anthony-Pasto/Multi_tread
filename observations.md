Le 1:
Les cinq ordonnancements. q : quitter
  debut     fin       duree (ms)
  14:30:56  14:31:02  5053
  14:31:02  14:31:07  5024
  14:31:07  14:31:12  5025
  14:31:12  14:31:17  5028

  Les quatre tâches s'exécutent l'une après l'autre, en commençant par celle ayant la priorité la plus élevée (93), puis 92, 91 et 90. Cela s'explique par la politique SCHED_FIFO, qui donne la priorité aux tâches les plus prioritaires lorsqu'elles partagent le même cœur.

    TID COMMAND         CLS RTPRIO PSR
   1952 ordonnancements  TS      -   3
   1953 travail-1        FF     93   0
   1954 travail-2        FF     92   0
   1955 travail-3        FF     91   0
   1956 travail-4        FF     90   0

  Les résultats de ps -L confirment que les quatre tâches utilisent SCHED_FIFO (FF), avec les bonnes priorités et sur le cœur 0.

pid 1953's current scheduling policy: SCHED_FIFO
pid 1953's current scheduling priority: 93

La touche Q prend un assez grand delay avant de faire effect 

2a:

Les quatre tâches s'exécutent l'une après l'autre, même si elles possèdent toutes la même priorité (90). Avec SCHED_FIFO, une tâche qui utilise le processeur continue de s'exécuter jusqu'à ce qu'elle bloque, cède le processeur ou soit préemptée par une tâche plus prioritaire. Les quatre tâches utilisent le cœur 0 et prennent environ 5 secondes chacune.

Résultats du programme :

  debut     fin       duree (ms)
  14:36:36  14:36:41  5052
  14:36:41  14:36:46  5023
  14:36:46  14:36:51  5022
  14:36:51  14:36:56  5024

Résultats de ps -L :

TID  COMMAND          CLS  RTPRIO  PSR
2084 ordonnancements  TS   -       3
2085 travail-1         FF   90      0
2086 travail-2         FF   90      0
2087 travail-3         FF   90      0
2088 travail-4         FF   90      0

Résultat de chrt -p : 

pid 2085's current scheduling policy: SCHED_FIFO
pid 2085's current scheduling priority: 90.

Réactivité du clavier : Prend environ 5sec a s'executer.

2b:
Les quatre tâches commencent et terminent presque en même temps, contrairement à la configuration 2. Cela s'explique par le fait que chaque tâche utilise un cœur différent (0, 1, 2 et 3), ce qui permet leur exécution en parallèle malgré leur priorité identique de 90.

Résultats du programme :

  debut     fin       duree (ms)
  14:40:14  14:40:20  5572
  14:40:14  14:40:20  5583
  14:40:14  14:40:20  5574
  14:40:14  14:40:20  5576

Résultats de ps -L :

TID  COMMAND          CLS RTPRIO PSR
2216 ordonnancements  TS      -   3
2217 travail-1        FF     90   0
2218 travail-2        FF     90   1
2219 travail-3        FF     90   2
2220 travail-4        FF     90   3

Résultats de chrt -p :

pid 2217's current scheduling policy: SCHED_FIFO
pid 2217's current scheduling priority: 90

Réactivité du clavier : Il est beaucoup plus réactif pris environ 2sec.

3:

Les quatre tâches commencent et terminent presque en même temps, avec une durée d'environ 20 secondes chacune. Contrairement à SCHED_FIFO, SCHED_RR partage le temps du processeur entre les tâches de même priorité en leur donnant chacune un intervalle de temps à tour de rôle.

Résultats du programme :

  debut     fin       duree (ms)
  14:43:18  14:43:38  20052
  14:43:18  14:43:38  19982
  14:43:18  14:43:38  19912
  14:43:18  14:43:38  19839

Résultats de ps -L :

TID  COMMAND          CLS RTPRIO PSR
2342 ordonnancements  TS      -   2
2343 travail-1        RR     90   0
2344 travail-2        RR     90   0
2345 travail-3        RR     90   0
2346 travail-4        RR     90   0

Résultats de chrt -p :

pid 2343's current scheduling policy: SCHED_RR
pid 2343's current scheduling priority: 90

Réactivité du clavier : Presque instantaner.

4:

Les quatre tâches utilisent le cœur 0. La tâche 4, ayant la priorité la plus élevée (91), termine en premier après environ 5 secondes. Les trois autres tâches, de priorité 90, se partagent ensuite le processeur avec la politique SCHED_RR et terminent presque en même temps. La tâche 1 a commencé avant d'être interrompue par la tâche 4.

Résultats du programme :

  debut     fin       duree (ms)
  14:45:45  14:46:06  20103
  14:45:51  14:46:06  14953
  14:45:51  14:46:06  14880
  14:45:45  14:45:51  5078

Résultats de ps -L :

TID  COMMAND          CLS RTPRIO PSR
2467 ordonnancements  TS      -   3
2468 travail-1        RR     90   0
2469 travail-2        RR     90   0
2470 travail-3        RR     90   0
2471 travail-4        RR     91   0

Résultats de chrt -p :

pid 2468's current scheduling policy: SCHED_RR
pid 2468's current scheduling priority: 90

pid 2471's current scheduling policy: SCHED_RR
pid 2471's current scheduling priority: 91

Réactivité du clavier : presque instantaner mais un peut plus lent que 4.

5:
Les quatre tâches commencent et terminent presque en même temps, avec une durée d'environ 5 secondes chacune. Contrairement aux configurations où le cœur 0 était imposé, Linux peut ici répartir les tâches sur plusieurs cœurs. Les quatre tâches utilisent SCHED_OTHER avec une priorité temps réel de 0.

Résultats du programme :

  debut     fin       duree (ms)
  14:48:49  14:48:54  5059
  14:48:49  14:48:54  5064
  14:48:49  14:48:54  5062
  14:48:49  14:48:54  5073

Résultats de ps -L :

TID  COMMAND          CLS RTPRIO PSR
2595 ordonnancements  TS      -   0
2596 travail-1        TS      -   1
2597 travail-2        TS      -   0
2598 travail-3        TS      -   3
2599 travail-4        TS      -   2

Résultats de chrt -p :

pid 2596's current scheduling policy: SCHED_OTHER
pid 2596's current scheduling priority: 0
pid 2596's current runtime parameter: 2100000

Réactivité du clavier : presque instantaner comme 4.


Étape 5 — Race condition

Sans protection :
- Rafales écrites : 40 373 981
- Vérifications : 31 966 114
- Sommes fausses : 27 344 084

Avec protection :
- Rafales écrites : 1 763 786
- Vérifications : 1 832 648
- Sommes fausses : 0

Explication :

Sans protection, plusieurs tâches peuvent lire et écrire dans le tableau simultanément, ce qui provoque des erreurs de checksum. Avec la protection active, le mutex permet à une seule tâche à la fois d'accéder au tableau. Cela élimine les erreurs observées, mais réduit la vitesse des opérations à cause de la synchronisation.





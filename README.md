# introduction

Ananta System Tchat est un projet de développement d'un système de tchat. il permet de discuter avec des amis dans un réseau local. l'interface est simple et intuitive, elle a uniquement deux boutons, un pour envoyer un message et un pour accéder au paramètre.
pour l'instant le tchat est uniquement disponible dans un réseau local, toutefois des test sont en cours pour pouvoir y accéder de partout sur internet.

# Sommaire
- [Introduction](#introduction)
- [presentation](#presentation)
- [avantage](#avantage)
- [fonctionnalité](#fonctionnalité)
- [installation](#installation)
- [Compatibilité](#compatibilité)
- [compilation](#compilation)
- [Architecture](#architecture)
- [contribution](#contribution)
- [contact](#contact)

# présentation du Project
Ananta System Tchat est né d'un besoin anonymat dans un collège. pour pouvoir continuée a discuter entre amis pendant les cour en salle informatique je me suis mis a développé un système de tchat. il était dans un autre langage : le batch. il était peut efficace. je e sui donc lancée dans le c++. cella fait maintenant 5 ans que je développe ce projet en c++, il est donc de plus en plus stable est plein de fonctionnalité.

# avantage
- le tchat est chiffrée de bout en bout
- il est personnalisable
    - il possède par exemple de plusieurs thèmes
    - il est possible de désactiver les notifications
    - il est possible de condenser la fenêtre
- il est 100% gratuit est open source

# fonctionnalités
ce tchat permet bien évidement d'envoyer des message, mais aussi plusieurs autre fonctionnalité est cette liste s'agrandit de mise a jour en mise a jour :
- [x] envoyer des fichiers jusqu'à 250Mo
- [x] prévisualiser les fichiers
- [x] a une salle d’attente qui permet approuver ou non les nouveaux membres
- [x] a une liste de membres qui permet de voir les membres connectés
- [x] a plusieurs commende utile :
    - ping : permet de voir le temps de réponse du serveur
    - info : permet de voir les information détailler sur le ping
    - help : permet de voir la liste des commande
    - debug : permet de voir les information de débugage
    - est plus encore
- [x] a un historique qui permet de sauvegarder les messages même après une fermeture du tchat

# installation
le développement du site étant devenus difficile uniquement les version 4.1 est inferieur son disponible dessus. pour les version plus récente il est possible de télécharger le projet sur le GitHub.
##### pour l’installation depuis GitHub :
rendez vous sur la page du projet sur GitHub : [ici pour la version 5.1](https://github.com/https-github-com-anantasystem/anantaSystemTchat5.1) et [ici pour la 5.2](https://github.com/https-github-com-anantasystem/tchat-v5.2)
a droite se trouve un bouton Releases qui permet de voir les version disponible. une fois sur cette page cliquer sur la dernière version ou il n'est pas notée Beta. d'ici il vous sera possible de télécharger le code source, un fichier zip qui contient la version portable de application, ou encore le setup de l'application.

# Compatibilité
le tchat est compatible avec tout les système d'exploitation sauf mac.
pour windows le tchat a été compilée uniquemment pour les version 64bit. si toute fois vous voulez le tchat pour un autre os ou une autre architecture, vous pouvez le [compiler](compilation) sur votre machine, ou me demander de le faire pour vous sur notre [discord](https://[discord](https://discord.com/invite/rFm24ZznnT).com/invite/rFm24ZznnT).

# compilation
La compilation permet de créer une application interprétable par un appareil donné, dans notre cas votre ordinateur à partir du code source.
l’application se base sur la bibliothèque Qt5. il vous faudra donc installer Qt5 sur votre ordinateur. pour cella il vous suffit de suivre les instructions suivantes :

- [telecharger qt](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5)
- créer vous un compte sur le site de Qt
- connectez vous avec votre compte sur l’application installée plus haut, lorsque application vous le proposera, installée la version 5.15.2 : ![](https://cdn.discordapp.com/attachments/960222007180529775/960222092660441208/Capture_decran_2022-04-03_175730.png) 
- une fois l’installation terminée il vous suffit d'ouvrir le dossier des source du tchat.
pour obtenir de l'aide rendez vous sur notre [discord](https://[discord](https://discord.com/invite/rFm24ZznnT).com/invite/rFm24ZznnT)

# Architecture
Ananta System Tchat est codé suivant une architecture MVC.
- interface : les ficher widget.cpp et le contenus du dossier /client/chatBot/ sont les fichier d'interface, dans ces fichier vous pouvez trouver toute les fonction relative a l'interface graphique.
- /client  contiens tout les fonction relative au client :
    - /client/client.h/cpp : contient toute les fonction relative au client.
    - /client/parametre.h/cpp/ui : contient toute les fonction relative aux paramètre et leur interface graphique.
- /serveur  contiens tout les fonction relative au serveur :
    - /serveur/serveur.h/cpp : contient toute les fonction relative au serveur.
    - /serveur/parametre.h/cpp/ui : contient toute les fonction relative aux paramètre et leur interface graphique.
- /serveurConsoleAutoLaunch : est le Project encore en beta test de lancement automatique de serveur grâce a /tchat-serveur-console.
- /tchat-serveur-console : est le Project encore en beta test de lancement automatique de /serveurConsoleAutoLaunch.

# contribution
le projet est open source, vous pouvez donc contribuer au Project sur GitHub : [ici](https://github.com/https-github-com-anantasystem) 
- merci au différant contributeur qui ont aidé à participer au projet en me suggérant des fonctionnalités et en montrant des bugs que je n'aurai sûrement jamais remarqués, ou que j'aurai bien aimé oublier 😏.
<table>
  <tr>
    <!unel>
    <td align="center"><a href="https://anantasystem.com/unel"><img src="https://avatars.githubusercontent.com/u/86972822?v=4" width="100px;" alt=""/><br /><sub><b>Unel</b></sub></a><br /><a href="https://github.com/UnelDev" title="Code">💻</a> <a href="https://github.com/UnelDev" title="User Testing">📓</a> <a href="https://github.com/UnelDev" href="#ideas-bain3" title="Ideas, Planning, & Feedback">🤔</a> <a href="https://github.com/UnelDev" href="#plugin-bain3" title="Plugin/utility libraries">🔌</a> </td>
    <!wiwok>
    <td align="center"><a href="https://anantasystem.com/wiwok"><img src="https://avatars.githubusercontent.com/u/84347864?v=4" width="100px;" alt=""/><br /><sub><b>Wiwok</b></sub></a><br /><a href="https://github.com/Wiwok" title="site">🖥️</a> <a href="https://github.com/Wiwok" title="User Testing">📓</a> <a href="https://github.com/Wiwok" href="#ideas-bain3" title="Ideas, Planning, & Feedback">🤔</a></td>

  </tr>
</table>

# contact
le discord du projet est : [ici](https://[discord](https://discord.com/invite/rFm24ZznnT).com/invite/rFm24ZznnT)

le site du projet est : [ici](http://anantasystem.com/)

le twitter du projet est : [ici](https://twitter.com/AnantaSystems)

le GitHub du projet est : [ici](https://github.com/https-github-com-anantasystem)



#### nos adresse mail :
- pour des demande d’amélioration : [ici](mailto:amelioration@anantasystem.com) : amelioration@anantasystem.com
- pour raporter des bug : [ici](mailto:bug@anantasystem.com) : bug@anantasystem.com
- pour contacter les dev : [ici](mailto:dev@anantasystem.com) : dev@anantasystem.com
- pour rapporter des faille : [ici](mailto:faille@anantasystem.com) : faille@anantasystem.com
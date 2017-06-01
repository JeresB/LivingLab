# LivingLab

LivingLab est une application qui recueille des informations fournis par des capteurs installés dans une chambre.
L'application C++ récupère, traite et stock ces données dans une base de données.
L'application Web permet à un utilisateur de s'inscrire, se connecter, consulter les données liés à sa chambre.

## Pour commencer

Ces instructions vous donneront accés au projet. Voir la partie installation pour déployer le projet sur votre système.

### Prérequis

Avant d'utiliser le projet :

```
Placer le dossier principal dans le dossier de votre serveur apache2, généralement dans le dossier /var/www/html/
Crée un nouvel utilisateur avec une base de donnée correspondante de type MySQL sur PHPMYADMIN.
Reporter les informations de connexion (Nom de l'utilisateur, nom du serveur, nom de la base de données, mot de passe de l'utilisateur) dans les fichiers appli/bdd.conf et php/constants.php.
Importer le fichier sql/sql.sql dans la base de donnée crée.
```

### Installation

Installation pas à pas du projet pour son bon fonctionnement

Commande à réaliser (si pas déjà faite):

```
sudo apt-get install libqt5websockets5-dev
sudo apt-get install libqt5sql5-mysql
sudo apt-get install mysql-server
sudo apt-get install phpmyadmin (choisir apache2 et non lighttpd)
dpkg-reconfigure tzdata (changement du fuseau horaire)
```

Application C++ dans le dossier appli

```
commande : qmake -project
ajouter dans le fichier appli.pro à la fin : QT += core websockets sql network
                                             QT -= gui
commande : qmake
ajouter dans le fichier Makefile à la ligne CXXFLAGS après le = : -std=c++11
commande : make
```


## Lancement des tests

Lancement de l'application c++ dans le dossier appli :

```
./appli
```

Accès à l'application web :

```
url : localhost/yourpath/LivingLab/
```


## Développer avec

* [Bootstrap](http://getbootstrap.com/) - Framework for developing responsive web site
* [jQuery](https://jquery.com/) - jQuery is a fast, small, and feature-rich JavaScript library
* [Highcharts](https://www.highcharts.com/) - Interactive JavaScript charts for your webpage
* [SMTP](https://github.com/cutelyst/simple-mail) - Library to send mail with QT by cutelyst



## Auteurs

* **Théo Dupont**
* **Jeremy Boiselet** - [Portfolio](http://www.jeremyboiselet.ovh)


## Remerciement

* Merci de contribuer au développement de ce projet

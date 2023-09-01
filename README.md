# README 

Ce dossier contient deux sous-dossiers, l'un 3services, qui contient les sources et documentations des applications créés, l'autre, yocto_src qui contient le layer créé ainsi que la configuration du build.

## DAEMONS

Ce dossier contient :

### 3services :
Ce dossier contenant le binaire des trois applications, ainsi qu'un script qui doit être appelé au démarrage par un service. La procédure d'installation est détaillée dans la documentation qui se trouve dans les sources des projets.

### conf : 
Dans ce dossier, on trouvera les fichiers de configuration de build yocto

### project_src :
Ensemble des trois dossiers de projet, pour le simulateur de capteur, l'application d'analyse de valeur anormale et l'application de statistiques. Dans chacun des projets, on trouvera le dossier de documentation, qui expliquera plus en détail le fonctionnement du projet, et la liste des TODO.

### project_with_common_lib
Première version du projet, qui contenait une bibliothèque partagée entre les différentes application. Version abandonnée en raison de la complexité ajouté dans le projet, avec le cour delais disponible et de l'intégration dans yocto.

### fichier video

Demo en video du fonctionnement des applications lorsque l'on lance le script.

 
## yocto_src

Ce dossier contient le dossier build dans lequel je travaille, ainsi que le layer meta-sensors, qui contient trois recettes pour chacun des services.

Une documentation sur la compilation puis le deploiement sur desktop et yocto se trouvera au format html dans DAEMONS/projet_src/sensor/*/doxygen_doc/html/index.htlm



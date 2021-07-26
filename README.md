# EQ30 - Maraoui Souhail (mars3319)


## **Choix des langages**
Voici mes choix pour les langages ainsi que ma motivation derrière les choix.

### **C#**
J'ai choisi d'utiliser C# pour 2 raisons :
- J'ai beaucoup travaillé avec Java et Spring Boot pour construire REST Apis, et je trouve la syntaxe de C# (et à moindre degré les concepts de base) assez similaires à ceux de Java.
- J'ai déjà travaillé avec C# principalement avec Unity GameEngine.

### **JavaScript: React**
Pour la plupart des services backend que j'ai créé avec Java, j'ai utilisé React pour créer des applications Web afin de consommer ces services. Et donc je me sens assez à l'aise avec cette JavaScript Library.

## **Exemple de Codes**
Quant au code implémenté, j'ai construit 3 projets C# que vous trouverez dans la branche [TP3-TechTests](https://depot.dinf.usherbrooke.ca/dinf/cours/e21/IGL601/equipes/eq30/tree/TP3-TechTests) *(J'ai également effectué un "merge" des modifications à la branche actuelle -TP3- pour continuer le travail ici)*
- Le premier un DataContract qui contient les classes partagées entre les différents projets : `Script` et `Worker`;
- Le second est ConnectionDB qui gère la connexion avec une base de données locale utilisant le cadre d'entité;
- Et enfin, le troisième projet DeployUs qui transmet -*pour le moment*- les requêtes Get, Post et Delete à ConnectionDB.

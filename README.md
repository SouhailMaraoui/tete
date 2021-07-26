# EQ30 - Maraoui Souhail (mars3319)


## **Choix des langages**
Voici mes choix pour les langages ainsi que ma motivation derri�re les choix.

### **C#**
J'ai choisi d'utiliser C# pour 2 raisons :
- J'ai beaucoup travaill� avec Java et Spring Boot pour construire REST Apis, et je trouve la syntaxe de C# (et � moindre degr� les concepts de base) assez similaires � ceux de Java.
- J'ai d�j� travaill� avec C# principalement avec Unity GameEngine.

### **JavaScript: React**
Pour la plupart des services backend que j'ai cr�� avec Java, j'ai utilis� React pour cr�er des applications Web afin de consommer ces services. Et donc je me sens assez � l'aise avec cette JavaScript Library.

## **Exemple de Codes**
Quant au code impl�ment�, j'ai construit 3 projets C# que vous trouverez dans la branche [TP3-TechTests](https://depot.dinf.usherbrooke.ca/dinf/cours/e21/IGL601/equipes/eq30/tree/TP3-TechTests) *(J'ai �galement effectu� un "merge" des modifications � la branche actuelle -TP3- pour continuer le travail ici)*
- Le premier un DataContract qui contient les classes partag�es entre les diff�rents projets : `Script` et `Worker`;
- Le second est ConnectionDB qui g�re la connexion avec une base de donn�es locale utilisant le cadre d'entit�;
- Et enfin, le troisi�me projet DeployUs qui transmet -*pour le moment*- les requ�tes Get, Post et Delete � ConnectionDB.

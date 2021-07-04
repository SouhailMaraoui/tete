# EQ30 - Maraoui Souhail (mars3319)

Voici l'ensemble des commandes que j'ai implémentées :

### **build** `(./buildus [configFile] [buildPath])`
Construire un programme c ++ à partir d'un fichier de configuration yaml.
Il suit principalement ces deux étapes :
##### YAML parsing 
Lire le fichier de configuration, et construisez un objet de classe Build YAML qui contient les attributs suivants :
- `string project` : le nom de l'exécutable finale;
- `string deps_include_var` : dépendance (une seule valeur selon les instructions du professeur);
- `string deps library var` : chemin vers library;
- `vector<string> deps_library_libs` : liste des nom des libraries;
- `map<string,string> compile` : map des fichiers à compiler et le nom respectif de leur intermédiaire;
- `vector<string> files ` : liste des fichiers à copier vers le buildPath.

##### exécution des commandes
Et ensuite exécuter des commandes en fonction du contenu de cet objet pour la compilation, l'édition du lien, et la copie des fichiers.

**Remarque:** Pour ne pas refaire la compilation des fichiers déjà compilés et non modifiés, on utilise le fichier "compileHistory" dans le répertoire "intermediate" qui contient des lignes de la form suivante : {nom de fichier}{hash sha1 de contenue de fichier}
Et donc il suffit de vérifier si le fichier existe déjà et comparer le hash du fichier actuel avec le hash enregistré.


### **clean** `(./buildus clean)`
Supprimer les fichiers intermédiaires et le "compileHistory".

## Tests
J'ai utilisé les 3 premiers exercices de Lab4 et un test supplémentaire avec des fichiers à copier car ils couvrent la plupart des cas de build :
* **EX0** : Compiler un seul fichier cpp ;
* **EX1** : Compiler deux fichiers cpp ;
* **EX2** : Compiler un fichier cpp mais avec un chemin de bibliothèque (-L) et une bibliothèque (-l) ;
* **myTest** : Compiler un fichier et copiez 2 fichiers (un est dans un sous-dossier) ;
 
Ainsi que quelques tests élémentaires pour verifier la creation des fichiers de le parsing du YAML.

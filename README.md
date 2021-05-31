# EQ30 - Maraoui Souhail (mars3319)

Voici l'ensemble des commandes que j'ai implémentées :

### **init** `(./gitus init)`
Pour initialiser un dépôt de gitus ou le réinitialiser s'il existe déjà (Il vous donne le choix (y/n)).

### **log** `(./gitus log)`
Pour voir votre historique des commits.

### **add** `(./gitus add <filename>)`
Pour ajouter un fichier au staging area de gitus.

### **commit** `(./gitus add <message> <author>)`
Pour faire un commit des fichiers qui du `.git/index`.

### **checkout** `(./gitus checkout <hash>)`
Pour consulter une autre version de dépôt (Veuillez entrer tous le Hash de commit, vous pouvez le copier du l'historique avec `./gitus log`).

## Tests
Pour les tests, ils suivent l'ordre logique d'une utilisation normal de git : 
* On crée un nouveau dépôt (ou le réinitialiser s'il existe déjà);
* On crée deux ficher `testFile1` et `testFile2` et on les remplis;
* On ajoute les deux fichiers au staging area;
* On fait un `commit` avec le message **COMMIT_1**;
* Ensuite pour tester le checkout et l'intégrité des commits, en fait deux commits **COMMIT_2** et **COMMIT_3** changement respectivement `testFile1` et `testFile2`;
* On fait un `checkout` vers **COMMIT_1** et on vérifie si le contenue des deux fichiers et effectivement celui qu'on a mis la première fois;
* On fait un `checkout` vers **COMMIT_3** et on vérifie si les deux fiches ont effectivement été mis à jour à la dernière version.




# 
*PS: Je n'ai pas encore reçu de réponse concernant la correction du Lab2. Je doit mentionner que mon [dépôt personnel](https://depot.dinf.usherbrooke.ca/dinf/cours/e21/IGL601/mars3319) n'était créé qu'a jeudi le 27, et donc je n'avais aucun choix qu’à soumettre le devoir ici (les branches existent toujours dans ce dépôt).*
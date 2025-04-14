# super_matrice
Projet langage c

Pour collaborer efficacement sur GitHub, il est essentiel de savoir comment cloner un dépôt, créer des branches, et envoyer (pousser) du code. Voici un guide étape par étape pour réaliser ces tâches :

### 1. Cloner un Dépôt

Cloner un dépôt signifie créer une copie locale d'un dépôt distant sur votre machine. Voici comment procéder :

- **Étape 1 :** Accédez à la page du dépôt sur GitHub que vous souhaitez cloner.
- **Étape 2 :** Cliquez sur le bouton **"Code"** et copiez l'URL du dépôt.
- **Étape 3 :** Ouvrez votre terminal ou invite de commande.
- **Étape 4 :** Utilisez la commande suivante pour cloner le dépôt :

  ```bash
  git clone <URL_du_dépôt>
  ```

  Remplacez `<URL_du_dépôt>` par l'URL que vous avez copiée.

### 2. Créer une Branche

Les branches permettent de travailler sur différentes versions d'un projet simultanément. Voici comment créer une nouvelle branche :

- **Étape 1 :** Naviguez dans le répertoire de votre dépôt cloné :

  ```bash
  cd nom_du_dépôt
  ```

- **Étape 2 :** Créez une nouvelle branche avec la commande suivante :

  ```bash
  git checkout -b nom_de_la_branche
  ```

  Remplacez `nom_de_la_branche` par le nom que vous souhaitez donner à votre branche.

### 3. Envoyer (Pousser) du Code

Une fois que vous avez fait des modifications dans votre branche, vous pouvez les envoyer au dépôt distant. Voici comment procéder :

- **Étape 1 :** Ajoutez les fichiers modifiés à l'index de Git :

  ```bash
  git add .
  ```

  Utilisez `git add <nom_du_fichier>` pour ajouter des fichiers spécifiques.

- **Étape 2 :** Commitez les modifications avec un message descriptif :

  ```bash
  git commit -m "Description de vos modifications"
  ```

- **Étape 3 :** Poussez les modifications vers le dépôt distant :

  ```bash
  git push origin nom_de_la_branche
  ```

  Remplacez `nom_de_la_branche` par le nom de la branche que vous avez créée.

### 4. Créer une Pull Request (Optionnel)

Pour collaborer avec d'autres développeurs, vous pouvez créer une "pull request" pour proposer vos modifications :

- **Étape 1 :** Allez sur la page de votre dépôt sur GitHub.
- **Étape 2 :** Vous verrez une option pour créer une "pull request" après avoir poussé votre branche.
- **Étape 3 :** Remplissez les détails de la pull request et soumettez-la pour révision.

Ces étapes vous permettront de cloner un dépôt, de créer des branches, et d'envoyer votre code sur GitHub, facilitant ainsi la collaboration et la gestion de versions de votre projet.


### 5. Compilation et Exécution du Code

#### En ligne de commande

```bash
gcc -o supermat client.c supermat.c

```

#### En utilisant Makefile

```bash
make
```

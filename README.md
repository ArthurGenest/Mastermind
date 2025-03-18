# 🎮 Mastermind en C

## 🌟 Description
Ce projet est une implémentation du jeu Mastermind en langage C. Il permet à un joueur d'affronter l'ordinateur en essayant de deviner une combinaison secrète de couleurs. Il intègre un algorithme avancé pour améliorer l'expérience de jeu et optimiser la stratégie de l'ordinateur.

## ⚙️ Fonctionnalités

✅ Deux modes de jeu :
- Le joueur doit deviner la combinaison secrète générée par l'ordinateur.
- Le joueur définit une combinaison, et l'ordinateur tente de la deviner grâce à l'algorithme de Donald Knuth.

✅ Utilisation de caractères pour représenter les couleurs :
- R : Rouge
- B : Bleu
- V : Vert
- J : Jaune
- P : Pink
- W : Blanc

✅ Choix du niveau de difficulté (nombre maximal de tentatives) :
- Facile : 30 essais
- Intermédiaire : 20 essais
- Difficile : 10 essais
- Personnalisé : Nombre de tentatives défini par le joueur

✅ Fonctionnalités avancées :
- Menu des statistiques : Affichage des performances du joueur.
- Possibilité de revoir une partie : Consultation des coups joués.
- Option pour rejouer une partie sans relancer le programme.
- Système d'enregistrement des parties pour reprendre plus tard.

## 📸 Exemples du jeu

Voici quelques captures d'écran du jeu pour mieux visualiser l'expérience :

### **Menu principal** : 

![Image](https://github.com/user-attachments/assets/75ca799b-acf1-4ed8-9473-49ad09506528)

### **Partie en cours** :

![Image](https://github.com/user-attachments/assets/bc258014-c342-4f3f-bcfd-54935a463687)

### **Statistiques de jeu** :

![Image](https://github.com/user-attachments/assets/ec2ec2e9-e225-4bc0-93e3-2be895597f7b)

## 🛠 Installation

Pour jouer à ce jeu sur ton ordinateur local, suis ces étapes :

### 1️⃣ Cloner le dépôt : 
```bash
   git clone https://github.com/ArthurGenest/mastermind-c.git
```
### 2️⃣ Navigue vers le répertoire du projet :
cd mastermind-c

### 3️⃣ Compile et exécute le programme :
gcc main.c jeu.c -o mastermind
./mastermind

## 📁 Structure du projet
- 📌 main.c : Point d'entrée du programme.
- 📌 jeu.c : Contient les fonctions principales du jeu, dont l'algorithme de Donald Knuth pour optimiser les tentatives de l'ordinateur.
- 📌 jeu.h : Déclarations des fonctions et constantes.

## 🔧  Améliorations futures
- 👥 Mode Multijoueur : Permettre à deux joueurs de s'affronter en alternant les rôles de codebreaker et codemaker.
- 🖥️ Interface Graphique (GUI) : Ajouter une interface graphique pour améliorer l'expérience utilisateur.
- 🤖 IA Améliorée : Rendre l'IA plus intelligente pour deviner le code secret plus efficacement.
- 🏆 Système de Points : Ajouter un système de points avec des récompenses et trophées pour encourager les joueurs à améliorer leurs performances.

## 📢 Contribuer

Si tu souhaites contribuer au projet, suis ces étapes :

### 1️⃣ Clone ton fork sur ton ordinateur :
**Fork** le dépôt sur GitHub.
```bash
git clone https://github.com/TON-NOM-UTILISATEUR/mastermind-c.git
```
### 2️⃣ Crée une nouvelle branche
git checkout -b nom-de-ta-branche

### 3️⃣ Apporte tes modifications et commit-les :
git commit -am "Description de tes changements"
git push origin nom-de-ta-branche

### 4️⃣ Ouvrez une Pull Request ✅

## 📜 License

Ce projet est sous licence MIT. Voir le fichier LICENSE pour plus d'informations.

## 📬  Contact

Si vous avez des questions, vous pouvez me contacter à [arthurgenest222@gmail.com]

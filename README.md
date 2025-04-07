# Liste

## Tests

Le labo est fourni avec un fichier contenant des tests fonctionnels (`test.json`). Tous les tests doivent passer. Pour exécuter les tests, utilisez la commande `make test`. En cas de problème avec un paquet logiciel, installez les éléments manquants avec la commande `sudo apt-get install`.

Le *framework* de test est [Baygon](https://heig-tin-info.github.io/baygon/). Il peut être installé avec la commande `pip install Baygon==0.2.2`, après avoir installé Python avec `sudo apt-get install python3 python3-pip`.

Il se peut que vous ayez un avertissement à propos du `PATH`. En effet, `pip install` install le paquet Baygon dans votre espace utilisateur qui n'est pas pris en compte par votre terminal. Vous pouvez exécuter les commande suivante :

```bash
echo 'export PATH=$HOME/.local/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```

## Affichage de l'aide et de la version

Les options suivantes seraient considérées :

- `--help` affiche l'aide et termine le programme ;
- `--version` affiche l'auteur et la version puis termine le programme.

Exemple d'affichage pour la version

```console
$./tire --version
Version 1.0.0 (c)2021 Nom Prenom <firstname.lastname@heig-vd.ch>
```

## Liste des livrables
- `Commit` sur Github en respectant le délai donné sur Cyberlearn.

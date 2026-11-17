# ft_ls

🇫🇷 **[Français](#français)** · 🇬🇧 **[English](#english)**

---

## Français

> **Un `ls` réécrit de zéro pour comprendre comment l'ordinateur voit ses fichiers.**

`ft_ls` est une réimplémentation de la commande Unix `ls`, écrite en C dans le cadre du cursus 42. L'objectif est pédagogique : ne pas appeler l'outil du système, mais refaire soi-même le trajet complet — ouvrir un dossier, lire son contenu, récupérer les informations de chaque fichier, trier, puis afficher le résultat.

C'est un projet d'apprentissage, pas un remplacement de `ls`. Il couvre les options essentielles et montre, de façon concrète, comment un système de fichiers est organisé et interrogé.

### Pourquoi ce projet ?

`ls` est probablement la commande la plus utilisée d'un terminal. Derrière un simple nom de fichier se cachent des informations que le système manipule en permanence : type de fichier, permissions, propriétaire, taille, date de modification, liens symboliques. Réécrire `ls`, c'est apprendre à :

- parcourir des dossiers et gérer les chemins ;
- lire les métadonnées d'un fichier avec `lstat` et `struct stat` ;
- afficher des permissions et des dates lisibles par un humain ;
- trier et organiser des données ;
- concevoir un petit outil en ligne de commande avec des options, des messages d'erreur et des codes de sortie ;
- gérer manuellement la mémoire en C.

### Ce que le programme sait faire

| Commande | Effet |
| --- | --- |
| `./ft_ls` | Liste le dossier courant, sans les fichiers cachés. |
| `./ft_ls -a` | Affiche aussi les entrées dont le nom commence par `.` (y compris `.` et `..`). |
| `./ft_ls -l` | Affiche le format détaillé : type, permissions, liens, propriétaire, groupe, taille, date. |
| `./ft_ls -R` | Descend récursivement dans tous les sous-dossiers. |
| `./ft_ls -t` | Trie du plus récemment modifié au plus ancien. |
| `./ft_ls -r` | Inverse l'ordre du tri. |
| `./ft_ls -la`, `-lt`, `-laR` | Les options courtes se combinent. |
| `./ft_ls fichier dossier` | Accepte un ou plusieurs chemins, fichiers et dossiers mélangés. |
| `./ft_ls --all`, `--recursive`, `--reverse`, `--help` | Versions longues des options principales. |
| `./ft_ls --` | Tout ce qui suit est traité comme un nom de fichier. |

En détail :

- les liens symboliques sont affichés avec leur cible (`nom -> cible`) ;
- le mode `-l` affiche une ligne `total` calculée à partir des blocs occupés ;
- les fichiers sont triés par nom, puis éventuellement par date de modification ;
- les erreurs (chemin inexistant, dossier illisible, option inconnue) produisent un message clair et un code de sortie non nul ;
- les liens symboliques ne sont pas suivis pour déterminer le type d'une entrée, comme avec `ls` par défaut.

### Exemples

Prenons un petit dossier de démonstration :

```text
demo/
├── README.md
├── .env
├── notes/
│   └── todo.txt
├── projects/
│   ├── archive/
│   └── src/
│       └── main.c
├── shortcut -> README.md
└── broken-link -> /nonexistent
```

**Lister simplement le dossier :**

```console
$ ./ft_ls
README.md
broken-link
notes
projects
shortcut
```

**Tout afficher, y compris les fichiers cachés :**

```console
$ ./ft_ls -a
.
..
.env
README.md
broken-link
notes
projects
shortcut
```

**Afficher les détails :**

```console
$ ./ft_ls -l
total 12
-rw-r--r-- 1 bebou users 6 Nov 16 10:12 README.md
lrwxrwxrwx 1 bebou users 12 Nov 17 20:25 broken-link -> /nonexistent
drwxr-xr-x 2 bebou users 4096 Nov 17 20:25 notes
drwxr-xr-x 4 bebou users 4096 Nov 17 20:25 projects
lrwxrwxrwx 1 bebou users 9 Nov 17 20:25 shortcut -> README.md
```

**Trier par date, du plus récent au plus ancien :**

```console
$ ./ft_ls -lt
total 12
lrwxrwxrwx 1 bebou users 12 Nov 17 20:25 broken-link -> /nonexistent
lrwxrwxrwx 1 bebou users 9 Nov 17 20:25 shortcut -> README.md
drwxr-xr-x 2 bebou users 4096 Nov 17 20:25 notes
drwxr-xr-x 4 bebou users 4096 Nov 17 20:25 projects
-rw-r--r-- 1 bebou users 6 Nov 16 10:12 README.md
```

**Explorer tous les sous-dossiers :**

```console
$ ./ft_ls -R
./:
README.md
broken-link
notes
projects
shortcut

./notes:
todo.txt

./projects:
archive
src

./projects/archive:

./projects/src:
main.c
```

### Comment lire une ligne du mode `-l` ?

Exemple : `-rw-r--r-- 1 bebou users 6 Nov 16 10:12 README.md`

| Partie | Signification |
| --- | --- |
| `-` | Type d'entrée : `-` fichier, `d` dossier, `l` lien symbolique. |
| `rw-r--r--` | Permissions : lecture/écriture/exécution pour le propriétaire, le groupe et les autres. |
| `1` | Nombre de liens physiques. |
| `bebou users` | Propriétaire et groupe. |
| `6` | Taille en octets. |
| `Nov 16 10:12` | Dernière date de modification. |
| `README.md` | Nom de l'entrée. |

### Compiler et lancer

Prérequis : un système Unix/Linux, `clang` et `make`.

```console
$ git clone --recursive <url-du-depot>
$ cd ft_ls
$ make
$ ./ft_ls
```

Le projet utilise la bibliothèque personnelle `c42libs`, présente dans le dépôt sous forme de sous-module. Si le dépôt a été cloné sans `--recursive` :

```console
$ git submodule update --init --recursive
```

Autres commandes utiles :

```console
$ make re      # reconstruire entièrement
$ make clean   # supprimer les fichiers de compilation
$ make fclean  # tout nettoyer
```

### Sous le capot

- C99, compilé avec `-Wall -Wextra -Werror -pedantic`.
- Lecture des dossiers avec `opendir`, `readdir` et `closedir`.
- Métadonnées via `lstat`, `struct stat`, `getpwuid` et `getgrgid`.
- Conversion manuelle d'un timestamp Unix en date calendaire.
- Tri et stockage via des vecteurs dynamiques fournis par `c42libs`.
- Code séparé par responsabilité : analyse des options, parcours des dossiers, formatage, tri, gestion des chemins.
- Aucune dépendance à la commande `ls` du système : tout l'affichage est construit par le programme.

### Valeurs par défaut

| Réglage | Valeur par défaut |
| --- | --- |
| Cible | `./`, le dossier courant |
| Fichiers cachés | Ignorés |
| Ordre | Tri par nom, croissant (ordre des octets) |
| Récursion | Désactivée |
| Format | Un nom par ligne |
| Couleurs | Aucune |
| Liens symboliques | Affichés, non suivis |
| Taille des blocs | 1024 octets (`st_blocks / 2`) |
| Fuseau horaire | Décalage fixe de +2 h appliqué au timestamp UTC |
| Code de sortie | `0` en cas de succès, `2` en cas d'erreur |

### Ce qui manque / limites connues

**Options non implémentées** (par rapport à GNU `ls`) :

`-d`, `-h`, `-S`, `-s`, `-i`, `-n`, `-g`, `-o`, `-F`, `-1`, `-u`, `-c`, `--color`, `--group-directories-first`, `--ignore-backups`, `--almost-all`, `--si`, et la plupart des autres options avancées.

**Limites d'affichage :**

- pas de couleurs ni d'indicateurs de type (`/` pour les dossiers, `*` pour les exécutables…) ;
- pas d'affichage en colonnes : une entrée par ligne ;
- pas d'alignement des colonnes en mode `-l` (les champs sont séparés par un seul espace, contrairement à GNU `ls`) ;
- l'année n'est jamais affichée : le format est toujours `Mois Jour Heure` ;
- les bits spéciaux de permissions (setuid, setgid, sticky) ne sont pas affichés différemment d'un `x` ou d'un `-` ;
- le fuseau horaire est codé en dur (+2 h), sans gestion réelle de la timezone ni de l'heure d'été ;
- le tri est basé sur l'ordre des octets, sans prise en compte de la locale.

**Autres limites :**

- pas de gestion des ACL, des attributs étendus ni de SELinux ;
- le calcul du `total` suppose des blocs de 1024 octets ;
- le texte de `--help` est incomplet (il ne mentionne pas `-r`) ;
- les tests sont un stub : `make ft_ls_tests` affiche simplement « no tests for this project » ;
- projet développé et testé principalement sous Linux (utilisation de `st_mtim`).

**Statut :** clone pédagogique fonctionnel pour les options listées, non destiné à remplacer `ls` au quotidien.

[↑ Retour en haut](#ft_ls) · [🇬🇧 English](#english)

---

## English

> **An `ls` rewritten from scratch to understand how a computer sees its files.**

`ft_ls` is a reimplementation of the Unix `ls` command, written in C as part of the 42 curriculum. The goal is educational: instead of calling the system tool, rebuild the whole journey yourself — open a directory, read its contents, retrieve each entry's metadata, sort it, and print the result.

This is a learning project, not a replacement for `ls`. It covers the essential options and shows, in a concrete way, how a filesystem is organised and queried.

### Why this project?

`ls` is probably the most used command in a terminal. Behind a simple file name are pieces of information the system handles all the time: file type, permissions, owner, size, modification date, symbolic links. Rewriting `ls` means learning how to:

- walk through directories and handle paths;
- read file metadata with `lstat` and `struct stat`;
- turn permissions and timestamps into human-readable output;
- sort and organise data;
- design a small command-line tool with options, error messages and exit codes;
- manage memory manually in C.

### What the program can do

| Command | Effect |
| --- | --- |
| `./ft_ls` | Lists the current directory, hiding dotfiles. |
| `./ft_ls -a` | Also shows entries whose name starts with `.` (including `.` and `..`). |
| `./ft_ls -l` | Long format: type, permissions, links, owner, group, size, date. |
| `./ft_ls -R` | Recursively descends into every subdirectory. |
| `./ft_ls -t` | Sorts from the most recently modified to the oldest. |
| `./ft_ls -r` | Reverses the sorting order. |
| `./ft_ls -la`, `-lt`, `-laR` | Short options can be combined. |
| `./ft_ls file directory` | Accepts one or more paths, mixing files and directories. |
| `./ft_ls --all`, `--recursive`, `--reverse`, `--help` | Long versions of the main options. |
| `./ft_ls --` | Everything after it is treated as a file name. |

In more detail:

- symbolic links are printed with their target (`name -> target`);
- `-l` prints a `total` line computed from allocated blocks;
- entries are sorted by name, then optionally by modification time;
- errors (missing path, unreadable directory, unknown option) produce a clear message and a non-zero exit code;
- symbolic links are not followed to determine an entry's type, matching default `ls` behaviour.

### Examples

Let's use a small demo directory:

```text
demo/
├── README.md
├── .env
├── notes/
│   └── todo.txt
├── projects/
│   ├── archive/
│   └── src/
│       └── main.c
├── shortcut -> README.md
└── broken-link -> /nonexistent
```

**A plain listing:**

```console
$ ./ft_ls
README.md
broken-link
notes
projects
shortcut
```

**Show everything, including hidden files:**

```console
$ ./ft_ls -a
.
..
.env
README.md
broken-link
notes
projects
shortcut
```

**Show the details:**

```console
$ ./ft_ls -l
total 12
-rw-r--r-- 1 bebou users 6 Nov 16 10:12 README.md
lrwxrwxrwx 1 bebou users 12 Nov 17 20:25 broken-link -> /nonexistent
drwxr-xr-x 2 bebou users 4096 Nov 17 20:25 notes
drwxr-xr-x 4 bebou users 4096 Nov 17 20:25 projects
lrwxrwxrwx 1 bebou users 9 Nov 17 20:25 shortcut -> README.md
```

**Sort by date, newest first:**

```console
$ ./ft_ls -lt
total 12
lrwxrwxrwx 1 bebou users 12 Nov 17 20:25 broken-link -> /nonexistent
lrwxrwxrwx 1 bebou users 9 Nov 17 20:25 shortcut -> README.md
drwxr-xr-x 2 bebou users 4096 Nov 17 20:25 notes
drwxr-xr-x 4 bebou users 4096 Nov 17 20:25 projects
-rw-r--r-- 1 bebou users 6 Nov 16 10:12 README.md
```

**Explore every subdirectory:**

```console
$ ./ft_ls -R
./:
README.md
broken-link
notes
projects
shortcut

./notes:
todo.txt

./projects:
archive
src

./projects/archive:

./projects/src:
main.c
```

### How to read a `-l` line

Example: `-rw-r--r-- 1 bebou users 6 Nov 16 10:12 README.md`

| Part | Meaning |
| --- | --- |
| `-` | Entry type: `-` file, `d` directory, `l` symbolic link. |
| `rw-r--r--` | Permissions: read/write/execute for owner, group and others. |
| `1` | Number of hard links. |
| `bebou users` | Owner and group. |
| `6` | Size in bytes. |
| `Nov 16 10:12` | Last modification date. |
| `README.md` | Entry name. |

### Build and run

Requirements: a Unix/Linux system, `clang` and `make`.

```console
$ git clone --recursive <repository-url>
$ cd ft_ls
$ make
$ ./ft_ls
```

The project uses the author's personal C library `c42libs`, included as a git submodule. If the repository was cloned without `--recursive`:

```console
$ git submodule update --init --recursive
```

Other useful commands:

```console
$ make re      # rebuild everything
$ make clean   # remove build files
$ make fclean  # remove everything
```

### Under the hood

- C99, compiled with `-Wall -Wextra -Werror -pedantic`.
- Directory reading with `opendir`, `readdir` and `closedir`.
- Metadata through `lstat`, `struct stat`, `getpwuid` and `getgrgid`.
- Manual conversion of Unix timestamps into calendar dates.
- Sorting and storage through dynamic vectors from `c42libs`.
- Code split by responsibility: option parsing, directory traversal, formatting, sorting, path handling.
- No dependency on the system `ls` command: every line of output is produced by the program itself.

### Defaults

| Setting | Default value |
| --- | --- |
| Target | `./`, the current directory |
| Hidden files | Ignored |
| Order | Ascending name sort (byte order) |
| Recursion | Off |
| Format | One name per line |
| Colours | None |
| Symbolic links | Displayed, not followed |
| Block size | 1024 bytes (`st_blocks / 2`) |
| Time zone | Fixed +2 h offset applied to the UTC timestamp |
| Exit code | `0` on success, `2` on error |

### What is missing / known limitations

**Unimplemented options** (compared with GNU `ls`):

`-d`, `-h`, `-S`, `-s`, `-i`, `-n`, `-g`, `-o`, `-F`, `-1`, `-u`, `-c`, `--color`, `--group-directories-first`, `--ignore-backups`, `--almost-all`, `--si`, and most other advanced options.

**Display limitations:**

- no colours and no type indicators (`/` for directories, `*` for executables, etc.);
- no column layout: one entry per line;
- no column alignment in `-l` mode (fields are separated by a single space, unlike GNU `ls`);
- the year is never printed: the format is always `Month Day Time`;
- special permission bits (setuid, setgid, sticky) are not rendered differently from a plain `x` or `-`;
- the time zone is hard-coded (+2 h), with no real timezone or daylight-saving handling;
- sorting uses byte order and is not locale-aware.

**Other limitations:**

- no ACL, extended attribute or SELinux support;
- the `total` calculation assumes 1024-byte blocks;
- the `--help` text is incomplete (it does not mention `-r`);
- the test suite is a stub: `make ft_ls_tests` only prints “no tests for this project”;
- developed and tested mainly on Linux (uses `st_mtim`).

**Status:** a working educational clone for the options listed above, not intended to replace `ls` in daily use.

[↑ Back to top](#ft_ls) · [🇫🇷 Français](#français)

# minishhhh
🗺️ TON PLAN DE ROUTE MINISHELL – ÉTAPE PAR ÉTAPE


🟢 ÉTAPE 1 : LIRE UNE COMMANDE SIMPLE

🔧 Objectif : afficher un prompt, lire ce que l'utilisateur tape, et afficher ce texte.

✅ À faire :

    Crée ton main.c

    Utilise readline()

    Gère Ctrl+D proprement (afficher exit)

    Ajoute l’entrée à l’historique avec add_history()

➡️ Quand tu tapes :

minishell$ ls -l

tu dois voir s’afficher : ls -l → (juste pour tester)


🟡 ÉTAPE 2 : CRÉER TON input_checker()

🔧 Objectif : détecter les erreurs de syntaxe basiques avant d'exécuter une commande.

✅ À faire :

    Vérifier les quotes non fermées

    Empêcher les pipes mal placés (||, | en début ou fin)

    Gérer les redirections seules (> sans fichier après)

➡️ Si la commande est fausse, afficher une erreur et ne pas continuer.


🔵 ÉTAPE 3 : DÉCOUPER LA COMMANDE (TOKENIZER/PARSER)

🔧 Objectif : transformer la ligne en une liste de mots/commandes utilisables

✅ À faire :

    Séparer la ligne en tokens (ex: ls -l → ["ls", "-l"])

    Gérer les | pour créer plusieurs commandes

    Créer une structure t_cmd pour stocker les commandes

➡️ Cette étape te prépare à l’exécution.


🟠 ÉTAPE 4 : EXÉCUTER UNE COMMANDE SIMPLE

🔧 Objectif : utiliser fork() + execve() pour exécuter ls, echo, etc.

✅ À faire :

    Créer une fonction exec_cmd()

    Chercher la bonne commande avec getenv("PATH") + access()

    Faire le fork() et waitpid() correctement

➡️ Tape ls → ça doit s’exécuter comme dans le vrai shell 🎉


🟣 ÉTAPE 5 : GÉRER LES BUILTINS

🔧 Objectif : implémenter les commandes internes au shell (sans execve)

✅ À faire :

    Commencer par echo, pwd, cd, exit

    Tu peux faire une fonction is_builtin() et run_builtin()

    Certains builtins doivent modifier le shell directement (pas avec fork)



🟤 ÉTAPE 6 : GÉRER L’ENVIRONNEMENT (env, export, unset)

🔧 Objectif : pouvoir lire/modifier l’environnement comme dans bash

✅ À faire :

    Copier envp au démarrage

    Implémenter export, unset, env

    Gérer les = pour ajouter des variables

➡️ Tu pourras tester avec export TEST=123 && echo $TEST


⚫ ÉTAPE 7 : GÉRER LES REDIRECTIONS

🔧 Objectif : gérer <, >, >>, <<

✅ À faire :

    Ouvrir les bons fichiers avec open()

    Rediriger avec dup2()

    Pour <<, lis jusqu’au délimiteur (heredoc)

➡️ Exemple à tester : cat < infile, echo hello > file, cat << EOF


⚪ ÉTAPE 8 : GÉRER LES PIPES

🔧 Objectif : permettre des commandes liées par |

✅ À faire :

    Faire un pipe()

    dup2() pour relier stdout d’un processus au stdin du suivant

    Enchaîner les fork() pour chaque commande dans le pipe

➡️ Exemple à tester : ls -l | grep .c | wc -l


🔺 ÉTAPE 9 : GÉRER LES VARIABLES D’ENVIRONNEMENT $

🔧 Objectif : remplacer $VAR par sa valeur dans les arguments

✅ À faire :

    Parcourir les tokens

    Chercher avec getenv() ou ta propre fonction

    Remplacer proprement sans casser les quotes



🔻 ÉTAPE 10 : SIGNES, SIGNAUX & FINITIONS

🔧 Objectif : rendre ton shell agréable à utiliser

✅ À faire :

    Gérer Ctrl+C, Ctrl+\ avec signal()

    Afficher proprement les messages d’erreur

    Ajouter des free() partout

    Nettoyer les fuites (valgrind)



Les fonctions autorisée :

## 🧾 Fonctions de la bibliothèque Readline

- **`readline(prompt)`** : Lit une ligne de texte depuis l'entrée standard avec des fonctionnalités d'édition de ligne. Affiche le prompt spécifié.  ([readline(3): line from user with editing - Linux man page - die.net](https://linux.die.net/man/3/readline?utm_source=chatgpt.com))

- **`add_history(line)`** : Ajoute la ligne spécifiée à l'historique des commandes. 

- **`rl_clear_history()`** : Efface l'historique des commandes stocké par Readline.

- **`rl_on_new_line()`** : Indique à Readline qu'une nouvelle ligne est commencée, généralement après une sortie personnalisée.

- **`rl_replace_line(text, clear_undo)`** : Remplace le contenu actuel de la ligne d'entrée par `text`.

- **`rl_redisplay()`** : Force la réaffichage de la ligne d'entrée actuelle.

---

## 🖨️ Fonctions d'entrée/sortie standard

- **`printf(format, ...)`** : Affiche une chaîne formatée sur la sortie standard. 

- **`write(fd, buf, count)`** : Écrit jusqu'à `count` octets depuis le tampon `buf` vers le descripteur de fichier `fd`.  ([write(2) - Linux manual page - man7.org](https://man7.org/linux/man-pages/man2/write.2.html?utm_source=chatgpt.com))

- **`read(fd, buf, count)`** : Lit jusqu'à `count` octets depuis le descripteur de fichier `fd` dans le tampon `buf`. 

- **`close(fd)`** : Ferme le descripteur de fichier `fd`, libérant ainsi la ressource associée. 

---

## 🧠 Gestion de la mémoire

- **`malloc(size)`** : Alloue dynamiquement `size` octets de mémoire et retourne un pointeur vers celle-ci.  ([malloc(3): allocate/free dynamic memory - Linux man page](https://linux.die.net/man/3/malloc?utm_source=chatgpt.com))

- **`free(ptr)`** : Libère la mémoire précédemment allouée pointée par `ptr`.  ([free - Linux Man Pages Online - Hurricane Electric](https://man.he.net/man3/free?utm_source=chatgpt.com))

---

## 🗂️ Gestion des fichiers

- **`access(pathname, mode)`** : Vérifie l'accessibilité du fichier spécifié par `pathname` selon le mode donné (lecture, écriture, exécution).  ([access(2) - Linux manual page - man7.org](https://man7.org/linux/man-pages/man2/access.2.html?utm_source=chatgpt.com))

- **`open(pathname, flags, mode)`** : Ouvre le fichier spécifié par `pathname` avec les options définies par `flags`.  ([open(2) - Linux manual page - man7.org](https://man7.org/linux/man-pages/man2/open.2.html?utm_source=chatgpt.com))

- **`unlink(pathname)`** : Supprime le fichier spécifié par `pathname` du système de fichiers.

- **`stat(path, buf)`**, **`lstat(path, buf)`**, **`fstat(fd, buf)`** : Récupèrent des informations sur un fichier. `stat` suit les liens symboliques, `lstat` ne les suit pas, et `fstat` opère sur un descripteur de fichier.

---

## 🧬 Gestion des processus

- **`fork()`** : Crée un nouveau processus en dupliquant le processus appelant.  ([fork() in C | GeeksforGeeks](https://www.geeksforgeeks.org/fork-system-call/?utm_source=chatgpt.com))

- **`wait(status)`**, **`waitpid(pid, status, options)`**, **`wait3(status, options, rusage)`**, **`wait4(pid, status, options, rusage)`** : Attendent la terminaison d'un processus enfant et récupèrent son statut.

- **`execve(path, argv, envp)`** : Remplace le processus courant par un nouveau programme spécifié par `path`.

- **`exit(status)`** : Termine le processus en cours avec le code de sortie `status`.

---

## 🔁 Redirection et duplication de descripteurs

- **`dup(fd)`** : Duplique le descripteur de fichier `fd` et retourne le nouveau descripteur.

- **`dup2(oldfd, newfd)`** : Duplique `oldfd` sur `newfd`, fermant `newfd` s'il est déjà ouvert.

- **`pipe(fd[2])`** : Crée un canal de communication unidirectionnel entre deux descripteurs de fichier.

---

## 📂 Gestion des répertoires

- **`opendir(name)`** : Ouvre le répertoire spécifié par `name` et retourne un pointeur vers celui-ci.

- **`readdir(dirp)`** : Lit une entrée du répertoire pointé par `dirp`.

- **`closedir(dirp)`** : Ferme le répertoire ouvert pointé par `dirp`. ([Man page of MALLOC](https://sites.uclouvain.be/SystInfo/manpages/man3/malloc.3.html?utm_source=chatgpt.com))

---

## ⚠️ Gestion des erreurs

- **`strerror(errnum)`** : Retourne une chaîne décrivant l'erreur correspondant au numéro `errnum`.

- **`perror(s)`** : Affiche le message d'erreur associé à la dernière erreur système, précédé de la chaîne `s`.

---

## 🖥️ Terminal et TTY

- **`isatty(fd)`** : Vérifie si le descripteur de fichier `fd` est associé à un terminal.

- **`ttyname(fd)`** : Retourne le nom du terminal associé au descripteur de fichier `fd`.

- **`ttyslot()`** : Retourne le numéro de slot du terminal associé au processus courant.

- **`ioctl(fd, request, ...)`** : Effectue des opérations de contrôle sur le périphérique référencé par `fd`.

---

## 🔧 Signaux

- **`signal(signum, handler)`** : Définit une fonction de traitement pour le signal `signum`.

- **`sigaction(signum, act, oldact)`** : Permet de définir de manière plus fine le comportement lors de la réception du signal `signum`.

- **`sigemptyset(set)`** : Initialise l'ensemble de signaux `set` à vide.

- **`sigaddset(set, signum)`** : Ajoute le signal `signum` à l'ensemble `set`.

- **`kill(pid, sig)`** : Envoie le signal `sig` au processus identifié par `pid`.

---

## 🌐 Variables d'environnement

- **`getenv(name)`** : Retourne la valeur de la variable d'environnement `name`.

---

## 🧭 Répertoires et chemins

- **`getcwd(buf, size)`** : Remplit `buf` avec le chemin absolu du répertoire de travail courant.

- **`chdir(path)`** : Change le répertoire de travail courant pour `path`.

---

## 🧵 Contrôle du terminal (termios)

- **`tcgetattr(fd, termios_p)`** : Récupère les paramètres du terminal associé au descripteur `fd`.

- **`tcsetattr(fd, optional_actions, termios_p)`** : Configure les paramètres du terminal associé à `fd`.

---

## 🎨 Contrôle du terminal (termcap)

- **`tgetent(bp, name)`** : Charge la description du terminal `name` dans le tampon `bp`.

- **`tgetflag(id)`** : Retourne la valeur du drapeau booléen `id` pour le terminal courant.

- **`tgetnum(id)`** : Retourne la valeur numérique de la capacité `id` pour le terminal courant.

- **`tgetstr(id, area)`** : Retourne la chaîne de capacité `id` pour le terminal courant.

- **`tgoto(cap, col, row)`** : Construit une chaîne de positionnement de curseur basée sur la capacité `cap`.

- **`tput(str)`** : Écrit la chaîne de contrôle `str` sur la sortie standard.








PROBLEMES PARSING : 

1. DOUBLE QUOTES

actuel :
echo "hello" ---> " hello"
comportement attendu :
echo "hello"  ---> hello            DONE


DEBUG 
minishell> echo
args[0] = [echo]

minishell> echo hello
args[0] = [echo]
args[1] = [hello]
hello
minishell> echo "hello"
args[0] = [echo]
args[1] = ["]            !!! probleme 
args[2] = [hello"]
" hello"
minishell> 

MEME PROBLEME POUE ADD UNE VAR :  DONE

actuel :
export VAR="hello"  ---- >    VAR="hello"
comportement attendu 
export VAR="hello" ----> VAR=hello

MEME PROBLEME POUR echo VAR:

actuel :
echo "$USER"  -----> " augeerae"
comportement attendu :
echo "$USER" ----> augeerae

--MEME CHOSE POUR LES ' '

actuel :
echo 'hello world' --- > ' hello world'
comportement attendu :
echo 'hello world' ---- > hello world

actuel :
echo "a'$USER'" --- > " a'augeerae'"
comportement attendu : 
echo "a'$USER'"  ---> a'augeerae'


2. HANDER                       DONE
>> 

comportement actuel :
echo more >> out.txt
echo more2 >> out.txt
echo more3 >> out.txt
==== fichier out.txt = more puis out.txt = more2 puis out.txt = more3
ecrase a la place d add les uns a la suites des autres dans le fichier 

comportement attendu :
echo more >> out.txt
echo more2 >> out.txt
echo more3 >> out.txt
==== fichier out.txt = more puis out.txt = more more 2 puis out.txt = more more2 more3 
 ajoute le prochaine dans out.txt sans ecraser 





EVENTUELS PROBLEMES :

exit avec des lettres pour argument (exit abc → affiche une erreur, quitte avec 255), le notre n accepte pas autre chose que les chiffres pour argument


si on ne ferme pas les doubles quotes alors bash reste "ouvert" et attend qu on ecrit la suite, le notre afficher une erreur de syntax





Gerer expander dans le parsing et non dans echo

actuel:
1 - minishell> echo '$USER'
mavissar
2 - minishell> echo "'$USER'"
$USER
3 - minishell> echo '"$USER"'
"mavissar"

L expandeur fais l inverse de ce qu il faut ? 
au lieu de gerer la premiere et la derniere quote il faut gerer la 
premiere et la deuxieme, cad celle qui vient direct apres
dans le cas :
mavissar@mi-r1-p2:~$ echo "'"'$USER'"'"
'$USER'
on gere "'" puis '$USER' puis "'"

correct:
1 - mavissar@mi-r1-p2:~$ echo '$USER'
$USER
2 - mavissar@mi-r1-p2:~$ echo "'$USER'"
'mavissar'
3 - mavissar@mi-r1-p2:~$ echo '"$USER"'
"$USER"




beug d espaces :
minishell> echo """f"""
 f 
minishell> echo "'""f""'"
' f '
minishell> echo "'""f""'"
minishell> echo "'""f""'"
' f '
minishell> echo "'""""'"
'  '
minishell> echo ""

minishell> echo '""'
""
minishell> echo "''''" | cat -e
''$
minishell> echo "'""'" | cat -e
' '$


















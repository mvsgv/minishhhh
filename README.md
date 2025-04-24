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


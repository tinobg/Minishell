# Minishell

**Minishell** est une implémentation simplifiée du shell Bash, développée en C dans le cadre du cursus **École 42**.  
Il permet l’exécution de commandes interactives avec gestion des processus, pipes, redirections, variables d’environnement, et signaux.

> “As beautiful as a shell” 🐚

---

## 🧠 Objectifs pédagogiques

- Comprendre les **processus** Unix (`fork`, `execve`, `wait`, `pipe`, etc.)
- Manipuler les **file descriptors**
- Implémenter un **parser** robuste avec un tokenizer
- Gérer les signaux (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- Reproduire un comportement de **shell POSIX réaliste**

---

## ✨ Fonctionnalités obligatoires

✅ Prompt interactif  
✅ Exécution de commandes système (PATH, absolu, relatif)  
✅ Gestion de l’historique (via `readline`)  
✅ Tokenisation : quotes `' "` simples/doubles  
✅ Variables d’environnement (`$USER`, `$?`, etc.)  
✅ Pipes (`|`)  
✅ Redirections :
- `<` input
- `>` output truncate
- `>>` output append
- `<<` heredoc

✅ Signaux :
- `Ctrl-C` → nouvelle ligne + nouveau prompt
- `Ctrl-D` → exit propre
- `Ctrl-\` → ignoré

✅ Builtins implémentés :
| Commande | Options supportées |
|---------|------------------|
| `echo` | `-n` |
| `cd` | chemin relatif/absolu |
| `pwd` | aucune |
| `export` | sans options |
| `unset` | sans options |
| `env` | aucune |
| `exit` | aucune |

---

## 📎 Exemple d’utilisation

```sh
./minishell
minishell$ echo "Hello $USER"
Hello jennifer

minishell$ ls | grep .c > out.txt
minishell$ echo $?
0

minishell$ exit

Compilation:
make
./minishell

Nettoyage:
make clean
make fclean
make re


minishell$ exit

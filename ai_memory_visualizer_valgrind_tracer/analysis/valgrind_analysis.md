# Analyse mémoire avec Valgrind

## 1. stack_example

Valgrind ne détecte aucune erreur.

- 1 allocation et 1 libération.
- 0 octet perdu.
- 0 accès mémoire invalide.

Les variables locales sont utilisées pendant leur durée de vie. Les éléments non initialisés du tableau local_buff ne sont jamais lus.

## 2. heap_example

### Fuite mémoire (Memory leak)

Valgrind signale :

`6 bytes in 1 blocks are definitely lost`

Les 6 octets correspondent à la chaîne "Alice" et à son caractère de fin \0, alloués à la ligne 21.
La fonction person_free_partial(alice) libère la structure avec free(p), mais ne libère pas p->name.
L'adresse de la chaîne est perdue alors que la mémoire reste allouée.
Il s'agit d'une fuite mémoire due à une perte de propriété de l'allocation (leak due to lost ownership).

## 3. aliasing_example

Les pointeurs a et b désignent le même tableau de 20 octets. Après free(a) à la ligne 38, les accès via b deviennent invalides.
Valgrind détecte trois erreurs :

- **Ligne 42 — Invalid read of size 4 :** lecture de b[2] dans une allocation libérée, à 8 octets du début du tableau.
- **Ligne 44 — Invalid write of size 4 :** écriture de 123 dans b[3], à 12 octets du début du tableau libéré.
- **Ligne 45 — Invalid read of size 4 :** lecture de b[3] après sa libération.

Ces trois erreurs sont des cas de use-after-free.
Aucune fuite mémoire n'est détectée, car toutes les allocations ont été libérées.

## 4. Analyse critique de l'IA

L'explication initiale de ChatGPT identifiait quatre opérations invalides dans aliasing_example, sans distinguer suffisamment les accès mémoire des utilisations d'un pointeur devenu indéterminé.
Après comparaison avec le code source et les résultats de Valgrind, seulement trois erreurs sont signalées.
La ligne 40 affiche la valeur du pointeur b sans accéder au contenu du tableau libéré.
Les lignes 42, 44 et 45 accèdent réellement à cette mémoire.
La correction consiste à distinguer les opérations invalides selon le langage C des erreurs effectivement détectées par Valgrind. L'absence d'avertissement ne garantit pas qu'une instruction est valide.

## 5. Bilan

| Programme | Fuite mémoire | Lectures invalides | Écritures invalides | Total des erreurs |
|---|---|---|---|---|
| stack_example | 0 octet | 0 | 0 | 0 |
| heap_example | 6 octets | 0 | 0 | 1 |
| aliasing_example | 0 octet | 2 | 1 | 3 |

Aucune utilisation de mémoire non initialisée n'a été signalée.
L'absence de fuite mémoire ne garantit pas l'absence d'accès mémoire invalides.

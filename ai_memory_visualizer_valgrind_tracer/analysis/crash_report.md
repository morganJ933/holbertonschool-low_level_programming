# Analyse du plantage

## 1. Description

Le programme `crash_example` affiche une erreur de segmentation et retourne le code 139 (SIGSEGV).

## 2. Cause du plantage

La variable n est initialisée à 0 à la ligne 25.
La fonction allocate_numbers(n) retourne NULL à la ligne 10, car n est inférieur ou égal à 0.
Aucun tableau n'est alloué par `malloc`.
Le pointeur nums contient donc NULL lorsque le programme exécute la ligne 32 :

```c
nums[0] = 42;
```

Cette instruction tente d'écrire dans une zone mémoire invalide.

## 3. Analyse mémoire

Le pointeur nums est une variable locale stockée dans la stack. Aucun tableau correspondant n'est alloué dans le heap.
L'erreur est un déréférencement de pointeur NULL (NULL pointer dereference), qui constitue un comportement indéfini (undefined behavior).
Dans cette exécution, ce comportement provoque une erreur de segmentation.

## 4. Analyse critique de l'IA

L'IA a proposé plusieurs causes possibles : un pointeur NULL, un échec de malloc, un use-after-free ou un stack overflow.
Le déréférencement du pointeur NULL est confirmé par le code source.
L'hypothèse d'un échec de malloc est incorrecte, car la fonction retourne NULL avant même d'exécuter malloc.
Le use-after-free est également incorrect, car aucune allocation du tableau n'a été libérée.
Le stack overflow n'est pas une cause justifiée par le code.

## 5. Proposition de correction (non appliquée)

Vérifier la valeur du pointeur avant de l'utiliser :

```c
if (nums == NULL)
    return 1;

nums[0] = 42;
```

Cette vérification empêcherait l'accès mémoire invalide.

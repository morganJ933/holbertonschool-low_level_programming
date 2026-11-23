# AI Memory Visualizer

## 1. Compilation

Les programmes ont été compilés sur Ubuntu avec GCC 15.2.0.

Le programme stack_example a été compilé correctement avec la commande make.

Pour aliasing_example, GCC a détecté des erreurs volontaires d'utilisation de mémoire après sa libération. J'ai utilisé la commande suivante pour permettre la compilation tout en conservant les avertissements :

`make aliasing_example CFLAGS="-Wall -Wextra -Werror -pedantic -std=gnu89 -g -Wno-error=use-after-free"`

Les fichiers sources et le Makefile n'ont pas été modifiés. Les deux programmes ont été exécutés sans Valgrind.

## 2. Stack Example

Ce programme permet de comprendre la récursivité, les cadres de pile et la durée de vie des variables locales.

Chaque appel récursif de walk_stack crée sa propre variable marker.

### Résultats de l'exécution

| Profondeur | local_int | local_buf[0] | marker |
|---|---|---|---|
| 0 | 100 | A | 0 |
| 1 | 101 | B | 10 |
| 2 | 102 | C | 20 |
| 3 | 103 | D | 30 |

### Carte mémoire à la profondeur 3

    STACK (pile)
    -------------------------
    dump_frame("enter", 3)
      local_int = 103
      local_buf[0] = 'D'
      p_local -> local_int
    -------------------------
    walk_stack(3): marker = 30
    walk_stack(2): marker = 20
    walk_stack(1): marker = 10
    walk_stack(0): marker = 0
    main()
    -------------------------

    HEAP (tas)
    Aucune allocation dynamique explicite.

Chaque appel récursif possède ses propres variables locales.

Pendant mon exécution, les adresses de marker diminuent de 48 octets à chaque profondeur.

Lorsque dump_frame se termine, ses variables locales local_int, local_buf et p_local cessent d'exister.

Cependant, marker reste valide jusqu'à la fin de son appel à walk_stack.

Les fonctions se terminent dans l'ordre inverse : 3, 2, 1, 0.

## 3. Aliasing Example

Ce programme permet de comprendre l'allocation dynamique, les alias de pointeurs et l'utilisation de mémoire après sa libération (use-after-free).

### Étape 1 : Initialisation

    STACK              HEAP
    a = NULL           Aucune allocation
    b = NULL
    n = 5

Les deux pointeurs sont initialisés à NULL.

### Étape 2 : Allocation dynamique

La fonction make_numbers(5) utilise malloc pour allouer un tableau de cinq entiers.

    STACK              HEAP
    arr -------------> [0][11][22][33][44]

Lorsque la fonction se termine, le pointeur local arr cesse d'exister, mais le tableau alloué dans la heap reste valide.
Son adresse est retournée et stockée dans a.

### Étape 3 : Aliasing

L'instruction b = a copie l'adresse contenue dans a vers b.

    STACK              HEAP
    a --------+
              +------> [0][11][22][33][44]
    b --------+

Résultat de mon terminal :

    a=0x568f75b92420 b=0x568f75b92420
    a[2]=22 b[2]=22

Les deux pointeurs désignent la même allocation mémoire. Aucun deuxième tableau n'est créé.
La fonction main est responsable de libérer cette allocation une seule fois.

### Étape 4 : Libération de la mémoire

Après l'instruction free(a) :

    STACK              HEAP
    a (dangling)
    b (dangling)       [MEMOIRE LIBEREE]

La durée de vie du tableau se termine.
Les variables a et b existent toujours, mais leurs valeurs deviennent indéterminées. Ce sont des pointeurs pendants (dangling pointers).
Aucun des deux pointeurs ne permet désormais d'accéder légalement à cette allocation.

### Étape 5 : Accès invalides à la mémoire

Résultat de mon terminal :

    reading b[2]=-669632300
    wrote b[3]=1234

Le programme contient plusieurs opérations invalides :

- Ligne 40 : utilisation de la valeur du pointeur après free.
- Ligne 42 : lecture dans une mémoire libérée.
- Ligne 44 : écriture dans une mémoire libérée.
- Ligne 45 : nouvelle lecture dans une mémoire libérée.
Ces opérations provoquent un comportement indéfini (undefined behavior).
La valeur -669632300 n'est pas prévisible et peut être différente lors d'une autre exécution.
Le programme n'a pas planté pendant mon exécution, mais cela ne signifie pas que les accès à la mémoire étaient valides.

## 4. Analyse critique de l'intelligence artificielle

### Explication initiale de l'IA

L'IA a expliqué que les variables locales étaient généralement stockées dans la stack, mais cette explication était incomplète, car elle ne distinguait pas suffisamment leurs différentes durées de vie.

### Correction

En observant le code, on remarque que marker appartient à la fonction walk_stack, tandis que local_int, local_buf et p_local appartiennent à dump_fram.
Les variables de dump_frame cessent d'exister avant l'appel récursif suivant.
Même si les adresses affichées à l'entrée et à la sortie sont identiques, il s'agit de nouvelles instances des variables et non des anciennes variables toujours vivantes.
Les cartes mémoire sont également des représentations simplifiées. Le langage C ne garantit pas les adresses exactes, le sens de croissance de la pile ou la taille des cadres de pile.

## 5. Conclusion

La stack contient les variables locales et les cadres d'appels de fonctions dans l'exécution observée.
La heap contient notamment les allocations dynamiques qui restent valides jusqu'à leur libération.
Plusieurs pointeurs peuvent désigner une même allocation. Lorsque cette allocation est libérée, les accès à celle-ci deviennent invalides pour tous ses alias.
Un programme peut contenir des erreurs de mémoire sans forcément planter.

## 6. Utilisation de l'intelligence artificielle

Outil utilisé : ChatGPT.
L'IA a été utilisée pour générer des cartes mémoire et expliquer la récursivité, la durée de vie des variables, les alias de pointeurs et les accès à la mémoire après sa libération.
Les explications doivent être vérifiées à partir du code source, des résultats du terminal et de la documentation technique.

## 7. Références à consulter

- Documentation Valgrind : https://valgrind.org/docs/manual/manual.html
- CERT C Coding Standard : https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/rules/memory-management-mem/mem30-c/

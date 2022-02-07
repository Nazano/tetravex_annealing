# Tetravex Solveur

Solveur d'un jeu de Tetravex

Germain Cassé - germain.casse
Antoine Julien - antoine.julien

# Modélisation probabiliste

Un algorithme de recuit simulé est utilisé pour résoudre le jeu.

# Optimisations mises en place

# Benchmarking

On compare le temps mis pour résoudre une grille avec:

 - solution naïve:

| taille  | 2    | 3    | 4         | 5         | 10        |
|---------|------|------|-----------|-----------|-----------|
| temps   | 4ms  | 3ms  | Not Found | Not Found | Not Found |
| Avancée | 100% | 100% | 25%       | 12%       | Time Out  |

> Remarque: quand on passe l'algo sur le test `5b.txt` où 3 lignes sont déja leurs tuiles fixées la solution est trouvée en 40ms. 

 - solution optimisée:

 Les fichiers de test correspondant sont:

 * 2 : `2.txt`
 * 3 : `3a.txt`
 * 4 : `4.txt`
 * 5 : `5a.txt` 
 * 10 : `10.txt` 
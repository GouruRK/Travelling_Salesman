# The Travelling Salesman problem

Made in association with [quentinl03](https://github.com/quentinl03).
___

- [The Travelling Salesman problem](#the-travelling-salesman-problem)
  - [How to](#how-to)
    - [Install ?](#install-)
    - [Run ?](#run-)
  - [User interactions](#user-interactions)

## How to

### Install ?

You can download this repository using git : 
```git
git clone https://github.com/GouruRK/travelling_salesman.git
```

Once on the `travelling_salesman` directory, you can compile it by using the command `make` (note that a folder `build/` is created).

Note that the makefile uses `gcc` by default.

This program use [MLV](http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/index.html) as graphical library. Make sure to [dowload](http://www-igm.univ-mlv.fr/~boussica/mlv/api/English/html/download.html) it.

### Run ?

To run it, use the `travelling_salesman` command. You can can add selerals options : 

```
./travelling_salesman [-p arg] [-k arg] [-v] [-s] [-h]
        [-p] Define the point system to use
                Require an integrer greather than 0 for the number of points, 
                or a path to a file with points coordinates
                No [-p] allows the user to select manually his points
                Default : NULL

        [-k] Define the number of differents visits
                Require an integrer greather than 0
                Default : 128

        [-v] Indicate to print the best path between points
                Default : false

        [-s] Indicate to save the points coordinates in a file called 'map.txt'
                Default : false

        [-h] Print this message
                Default : false
```

## User interactions

* The programm cannot stop itself. It is based on [gentic programming](https://en.wikipedia.org/wiki/Genetic_programming), and must be stoped by the user by closing the window.

* Use your `'s'` key to display/hide the cities names

* Use your `'p'` key to pause/unpause the program.

___

Check out quentinl03's other projects on github : [quentinl03](https://github.com/quentinl03).  
Check out my other projects on github : [Gouru](https://github.com/GouruRK/).
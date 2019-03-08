# Lem_in

Disclaimer
----------
> In School 42, almost every project must be written according to a coding syntax standard (also known as "[Norme](./docs/norme.fr.pdf)").
>
> That's why some parts may be strange

About
-----
>The ant colony must move from one point to another. But how to make it as short as possible?
>
>This project introduces to graphing algorithms: the program will have to intelligently select the precise paths and movements that these ants must take.

This is the third project of the Algorithms branch at School 42 Paris

Installation
------------
Run `make fclean && make`

Usage
-----
`./lem-in < map`


### Example
```
> ./lem-in < maps/map_fourmilliere_3.map
3
##start
start 1 0
##end
end 5 0
millieu 9 0
cote 13 0
start-millieu
millieu-cote
cote-end

L1-millieu
L1-cote L2-millieu
L1-end L2-cote L3-millieu
L2-end L3-cote
L3-end
```

##### Project done in 2017

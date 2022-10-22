# SLE solver

SLE solver je program pro řešení soustav lineárních rovnic v maticovém tvaru
pomocí Gaussovy eliminační metody.

# Vstupní formát

Program očekává rozšířenou matici soustavy na standardním vstupu (`stdin`)
v následujícím formátu:

První řádek obsahuje dvě celá čísla `r` a `s`, kde `r` je počet lineárních rovnic
a `s` je počet proměnných. Následuje `r` řádků o `s + 1` reálných číslech.
Každý `i`-tý řádek určuje jednu rovnici. Prvních `s` čísel každého řádku odpovídá
jednomu řádku matice soustavy a poslední číslo v řádku pak pravé straně rovnice.

Příklady vstupu:
```
2 2
2.0 4.0 3.5
3.0 4.0 1.0
```
```
1 3
2.0 4.0 3.5 0.0
```
```
4 2
2.0 4.0 3.5
3.0 4.0 1.0
5.0 4.0 4.7
4.0 1.6 2.3
```

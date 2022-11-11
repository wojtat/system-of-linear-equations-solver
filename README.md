# SLE solver

SLE solver je program pro řešení soustav lineárních rovnic v maticovém tvaru
pomocí Gaussovy eliminační metody.

# Implementace

Program přečte rozšířenou matici soustavy ze standardního vstupu. Na tu následně
aplikuje Gaussovu eliminační metodu. Tím je obdržena matice v horním trojúhelníkovém
tvaru. Dále triviálně zjistí hodnosti matice soustavy a rozšířené matice soustavy.
Frobeniova věta řekne, jestli má soustava řešení. Pokud ano, je zahájeno zpětné
dosazení a v případě, že některé řádky byly lineárně závislé, je dopočtena báze
afinního podprostoru řešení. Konečně je výsledek vypsán na standardní výstup.

# Vstupní formát

Program očekává rozšířenou matici soustavy na standardním vstupu (`stdin`)
v následujícím formátu:

První řádek obsahuje dvě celá čísla `r` a `s`, kde `r` je počet lineárních rovnic
a `s` je počet proměnných. Následuje `r` řádků o `s + 1` reálných číslech.
Každý `i`-tý řádek určuje jednu rovnici. Prvních `s` čísel každého řádku odpovídá
jednomu řádku matice soustavy a poslední číslo v řádku pak pravé straně rovnice.

## Příklady vstupu a výstupu:
1. Jediné řešení
```
2 2
2.0 4.0 3.5
3.0 4.0 1.0
```
```
One unique solution:
-2.5 2.125
```
2. Nekonečně mnoho řešení
```
1 3
2.0 4.0 3.5 0.0
```
```
Infinitely many solutions
Particular solution:
0 0 0
Base of the homogeneous solution set:
-2 1 0
-1.75 0 1
```
3. Žádné řešení
```
4 2
2.0 4.0 3.5
3.0 4.0 1.0
5.0 4.0 4.7
4.0 1.6 2.3
```
```
No solution
```

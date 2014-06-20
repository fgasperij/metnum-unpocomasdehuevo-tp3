
#Cantidad de tets
cantRec=5
cantCuad=5
cantCub=5
cantVarArq=4
cant_tests=20

#Directorios
rec="rectas"
cuad="cuadraticas"
cub="cubicas"
inst="instancias"
instRuido="instancias2"
instVA="instancias3"
tests="tests"

#Extensiones
tiro="tiro"
tiroRuido="tiroruidoso"
arq="arq"
jug="jug"

# Borreo veredictos.out porque hace append.
rm resultados/veredictos.out

# Resuelvo instancias rectas, cuadraticas y cubicas de la catedra.
for((i=1; i < $cantRec+1; i++))
do
	./tp $inst/$rec/r$i.$tiro $inst/$rec/r$i.$arq $inst/vacio.$jug
done

for((i=1; i < $cantCuad+1; i++))
do
	./tp $inst/$cuad/c$i.$tiro $inst/$cuad/c$i.$arq $inst/vacio.$jug
done

for((i=1; i < $cantCub+1; i++))
do
	./tp $inst/$cub/cb$i.$tiro $inst/$cub/cb$i.$arq $inst/vacio.$jug
done

# Veo los partidos.
for((i=1; i < $cantRec+1; i++))
do
	python main.py $inst/$rec/r$i.$arq $inst/$rec/r$i.$tiro $inst/vacio.$jug
done

for((i=1; i < $cantCuad+1; i++))
do
	python main.py $inst/$cuad/c$i.$arq $inst/$cuad/c$i.$tiro $inst/vacio.$jug
done

for((i=1; i < $cantCub+1; i++))
do
	python main.py $inst/$cub/cb$i.$arq $inst/$cub/cb$i.$tiro $inst/vacio.$jug
done

# fancy, tiro libre
./tp $inst/fancy/$tirolibre1.$tiro $inst/fancy/tirolibre1.$arq $inst/fancy/tirolibre1.$jug
python main.py $inst/fancy/tirolibre1.$arq $inst/fancy/tirolibre1.$tiro $inst/fancy/tirolibre1.$jug


# Resuelvo instancias con ruido.
./tp $instRuido/cbp30.$tiroRuido $instRuido/cbp30.$arq $instRuido/cbp30.$jug
./tp $instRuido/cbp70.$tiroRuido $instRuido/cbp70.$arq $instRuido/cbp70.$jug
./tp $instRuido/cp30.$tiroRuido $instRuido/cp30.$arq $instRuido/cp30.$jug
./tp $instRuido/cp70.$tiroRuido $instRuido/cp70.$arq $instRuido/cp70.$jug
./tp $instRuido/f2p90.$tiroRuido $instRuido/f2p90.$arq $instRuido/f2p90.$jug
./tp $instRuido/fp30.$tiroRuido $instRuido/fp30.$arq $instRuido/fp30.$jug
./tp $instRuido/fp70.$tiroRuido $instRuido/fp70.$arq $instRuido/fp70.$jug
./tp $instRuido/rp30.$tiroRuido $instRuido/rp30.$arq $instRuido/rp30.$jug
./tp $instRuido/rp70.$tiroRuido $instRuido/rp70.$arq $instRuido/rp70.$jug

# Partidos
python main.py $instRuido/cbp30.$arq $instRuido/cbp30.$tiroRuido $instRuido/cbp30.$jug
python main.py $instRuido/cbp30.$arq $instRuido/cbp70.$tiroRuido $instRuido/cbp70.$jug
python main.py $instRuido/cp30.$arq $instRuido/cp30.$tiroRuido $instRuido/cp30.$jug
python main.py $instRuido/cp30.$arq $instRuido/cp70.$tiroRuido $instRuido/cp70.$jug
python main.py $instRuido/f2p90.$arq $instRuido/f2p90.$tiroRuido $instRuido/f2p90.$jug
python main.py $instRuido/fp30.$arq $instRuido/fp30.$tiroRuido $instRuido/fp30.$jug
python main.py $instRuido/fp70.$arq $instRuido/fp70.$tiroRuido $instRuido/fp70.$jug
python main.py $instRuido/rp30.$arq $instRuido/rp30.$tiroRuido $instRuido/rp30.$jug
python main.py $instRuido/rp70.$arq $instRuido/rp70.$tiroRuido $instRuido/rp70.$jug

# Resuelvo instancias variando la posicion del arquero.
for((i=1; i < $cantVarArq+1; i++))
do
	./tp $instVA/$i.$tiro $instVA/$i.$arq $instVA/$i.$jug
done

# Veo los partiditos.
for((i=1; i < $cantVarArq+1; i++))
do
	python main.py $instVA/$i.$arq $instVA/$i.$tiro $instVA/$i.$jug
done

# Resuelvo tests propios
for((i=1; i < $cant_tests+1; i++))
do
	./tp $tests/$i.$tiro $tests/$i.$arq $tests/$i.$jug
done

# Veo el partido para los tests propios
for((i=1; i < $cant_tests+1; i++))
do
	python main.py $tests/$i.$arq $tests/$i.$tiro $tests/$i.$jug
done

# Calculo de tasa de efectividad.
echo "Tasa de efectividad: "
python calcTE.py


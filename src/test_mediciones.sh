mediciones=(1 2 3 4 5 6 7 8 9 10)
grados=(3 4 5 6)

for medicion in "${mediciones[@]}"
do
	for grado in "${grados[@]}"
	do
		printf "Grado: "
		printf $grado
		printf " Cantidad de mediciones: "
		printf $medicion
		echo
		python modifConfig.py -mg $grado -cm $medicion
		./run_test_fast.sh		
	done
done

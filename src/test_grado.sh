grados=(1 2 3 4 5 6 7 8 9 10)
mediciones=(3 6 9 12)


for grado in "${grados[@]}"
do
	for medicion in "${mediciones[@]}"
	do
		echo "Grado: "
		echo $grado
		echo "Cantidad de mediciones: "
		echo $medicion
		python modifConfig.py -mg $grado -cm $medicion
		./run_test_fast.sh		
	done
done

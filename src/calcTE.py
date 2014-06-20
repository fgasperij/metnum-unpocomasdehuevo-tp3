def main():
	f = open("resultados/veredictos.out", "r")
	aciertos = 0
	cant_inst = 0;
	for line in f:
		cant_inst = cant_inst+1
		if(int(line[len(line)-2]) == 1):
			aciertos = aciertos+1

	print float(aciertos)/float(cant_inst)
		
if __name__ == "__main__":
    main()

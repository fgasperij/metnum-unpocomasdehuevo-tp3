#!/usr/bin/python

from sys import argv
import argparse

MAX_GRADO = "max_grado"
CANT_MEDICIONES = "cant_mediciones"

from xml.dom.minidom import *

pretty_print = lambda data: '\n'.join([line for line in data.toprettyxml(indent=' '*3).split('\n') if line.strip()])	

def main(arg = argv):
	parser = argparse.ArgumentParser(description="Archivo para modificar parametros de configuracion global")
	parser.add_argument("-cm", help="Cantidad de mediciones (ultimas) a tomar, default=None", type=int, default=None)
	parser.add_argument("-mg", help="Maximo grado a tomar, default=None", type=int, default=None)
	args = parser.parse_args()

	dom = parse('conf.xml')
	config = dom.documentElement
	if(args.cm != None and args.cm > 0):
		for child in config.getElementsByTagName(CANT_MEDICIONES):
			config.removeChild(child)
		cm_node = dom.createElement(CANT_MEDICIONES)
		cm_text_node = dom.createTextNode(str(args.cm))
		cm_node.appendChild(cm_text_node)
		config.appendChild(cm_node)

	if(args.mg != None and args.mg > 0):
		for child in config.getElementsByTagName(MAX_GRADO):
			config.removeChild(child)
		cm_node = dom.createElement(MAX_GRADO)
		cm_text_node = dom.createTextNode(str(args.mg))
		cm_node.appendChild(cm_text_node)
		config.appendChild(cm_node)

	config_file = open("config.xml", 'w')

	config_file.write(pretty_print(dom))
	config_file.close()

if __name__ == "__main__":
    main()

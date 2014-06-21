#!/usr/bin/python
from scripts.fabricate import *
from scripts.settings import *
from scripts.utils import listfiles
from sys import argv

# Acciones
def build():
  compile()
  link()

def compile():
  for source in sources:
    run(compiler, '-c', source+'.cpp', '-o', source+'.o', '-std=c++0x', '-O2')

def link():
  objects = [s+'.o' for s in sources]
  run(compiler, '-o', executable, objects)

def clean():
  autoclean()

main()

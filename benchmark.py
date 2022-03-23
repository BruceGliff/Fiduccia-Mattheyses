#!/bin/python3

# import required module
from pathlib import Path
import os
import subprocess
import threading as th
 
# assign directory
directory = 'benchmark'
 
# iterate over files in
# that directory
files = sorted(Path(directory).glob('*.hgr'))

def doProcessing(flag, output):
    for file in files:
        process_one = subprocess.check_output(['./Initial', flag, file])
        output.append(process_one)
        #process_one.wait()

modout = []
orgout = []
mod = th.Thread(target=doProcessing, args=('-m',modout,))
org = th.Thread(target=doProcessing, args=('',orgout,))

mod.start()
org.start()

mod.join()
org.join()

def printOut(out, file):
    for x in out:
        file.write(x.decode('utf-8'))

modf = open("ResultsMod.out", 'w')
orgf = open("ResultsOrg.out", 'w')

printOut(modout, modf)
printOut(orgout, orgf)


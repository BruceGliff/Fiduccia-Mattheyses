#!/bin/python3

# import required module
from pathlib import Path
import os
import subprocess
 
# assign directory
directory = 'benchmark'
 
# iterate over files in
# that directory
files = sorted(Path(directory).glob('*.hgr'))

for file in files:
    process_one = subprocess.Popen(['./Initial', file])
    process_one.wait()

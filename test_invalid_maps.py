#!/usr/bin/env python3

import os
import subprocess
import sys

ferr = False
if len(sys.argv) != 2:
    print("ERROR : need path of dir of fmaps to check")
    ferr = True
if not os.path.isdir(sys.argv[1]):
    print("ERROR : is file or dont exist")
    ferr = True
if ferr:
    sys.exit()

path=sys.argv[1]

files = os.listdir(path)
nb_files = len(files)
print("LAUNCHING LEMIN PARSER ON", path)
print("nb of files to check : ", nb_files)
print("\n")
for i,fmap in enumerate(files):
    if i > 5:
        break
    full_path = os.path.abspath(path)+'/'+fmap
    print("{}{}{}{}".format("file", (i + 1),".", fmap).center(50, '-'))
    subprocess.call("./lem-in " + full_path, shell=True) 
    print("DONE".center(50, '-'))
    print("\n\n")

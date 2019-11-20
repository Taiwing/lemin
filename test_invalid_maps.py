#!/usr/bin/env python3

import os
import subprocess
import sys

ferr = False
if len(sys.argv) != 2:
    print("ERROR : need path of dir of fmaps to check")
    ferr = True
if not os.path.exists(sys.argv[1]):
    print("ERROR : dont exist")
    ferr = True
if ferr:
    sys.exit()

path=sys.argv[1]

if os.path.isdir(path):
    files = os.listdir(path)
else:
    files = [path]

nb_files = len(files)
nb_fail = 0
nb_succ = 0
failed = []
print("LAUNCHING LEMIN PARSER ON", path)
print("nb of files to check : ", nb_files)
print("\n")
for i,fmap in enumerate(files):
    if i > 500:
        break
    if os.path.isdir(path):
        full_path = os.path.abspath(path)+'/'+fmap
    else:
        full_path = fmap
    full_path = full_path.replace("'", "\\'")
    #full_path = os.path.abspath(path)+'/'+fmap
    print("{}{}{}{}".format("file", (i + 1),".", os.path.dirname(full_path)).center(50, '-'))
    ret_code = subprocess.call("./lem-in " + full_path, shell=True) 
    if ret_code == 0:
        print(">>>>>SUCCESS")
        nb_succ += 1
    else:
        failed.append(full_path)
        print("!!!!!FAILED")
        nb_fail += 1
    print("DONE".center(50, '-'))
    print("\n\n")


print("succeded", nb_succ, "/",nb_files, sep=' ')
print("failed", nb_fail, "/",nb_files, sep=' ')
print('\n  -', end='')
print(*failed, sep='\n  -')

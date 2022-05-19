import sys
import os
from random import randint

size = sys.argv[1]
bId = sys.argv[2]

with open("clean_export.dat", mode='r') as fdi:
    data = fdi.readlines()



def randomLine(lines):
    a = randint(0, len(lines)-1)
    print(a)
    line = lines[a]
    return line

with open("batch{}".format(bId), 'w') as fdo:
    fdo.write("{}\n".format(int(size)))
    for i in range(0, int(size)):
        line = randomLine(data)
        fdo.write(line)


#Code written by:
#   - Nemo Chentre
#
#Last modified: 11/05/2022
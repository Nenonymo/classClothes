import sys
import os
from random import randint

size = sys.argv[1]
bId = sys.argv[2]

with open("../data/csv/export_data_working.csv", mode='r') as fdi:
    data = fdi.readlines()



def randomLine(lines):
    pData = ["", "", ""]
    line = lines[randint(0, len(data))].split(",")
    pData[0] = line[9][:-1]
    pData[1] = line[0]
    pData[2] = "Unknown"
    return pData

with open("test{}".format(bId), 'w') as fdo:
    fdo.write("ID,PATH,LABEL\n")
    for i in range(0, int(size)):
        pData = randomLine(data)
        while (pData[1].count(" ") > 0):
            pData = randomLine(data)
        fdo.write("{},{},{}\n".format(pData[0], pData[1], pData[2]))


#Code written by:
#   - Nemo Chentre
#
#Last modified: 11/05/2022
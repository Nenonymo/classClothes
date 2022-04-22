import os

with open("export_dataframe.csv", mode='r') as f:
    data = f.readlines()

with open("clean_export.csv", 'w') as fout:
    fout.write("{}\n".format(len(data)-1))
    for line in data[1:]:
        clLine = line.split(",")
        fout.write("{} {} {} {} {} {} {} {} {}\n".format(clLine[0],clLine[1][3:],clLine[2][1:],clLine[3][1:],clLine[4][1:],clLine[5][1:],clLine[6][1:],clLine[7][1:],clLine[8][1:-4]))
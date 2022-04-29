import os

with open("../data/csv/export_data_working.csv", mode='r') as f:
    data = f.readlines()

with open("clean_export.dat", 'w') as fout:
    fout.write("{}\n".format(len(data)-1))
    lineP = ""
    for line in data[1:]:
        cLine = line.split(",")
        lineP = "{} {}".format(cLine[0], cLine[1])
        lineP = "{} {} {} {} {}".format(lineP, int(float(cLine[2][3:])), int(float(cLine[3][1:])), int(float(cLine[4][1:])), int(float(cLine[5][1:])))
        lineP = "{} {} {} {} {}\n".format(lineP, int(float(cLine[6][1:])), int(float(cLine[7][1:])), int(float(cLine[8][1:])), int(float(cLine[9][1:-4])))
        fout.write(lineP)
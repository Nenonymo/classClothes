import os

with open("../data/csv/export_data_working.csv", mode='r') as f:
    data = f.readlines()

with open("clean_export.dat", 'w') as fout:
    fout.write("{}\n".format(len(data)-1))
    lineP = ""
    for line in data[1:]:
        cLine = line.split(",")
        path = cLine[0]
        path = path.replace(" ", "_").replace("\ ", "_")
        lineP = "{} {}".format(cLine[9][:-1], path)
        lineP = "{} {} {} {} {}".format(lineP, int(float(cLine[1][3:])), int(float(cLine[2][1:])), int(float(cLine[3][1:])), int(float(cLine[4][1:])))
        lineP = "{} {} {} {} {}\n".format(lineP, int(float(cLine[5][1:])), int(float(cLine[6][1:])), int(float(cLine[7][1:])), int(float(cLine[8][1:-3])))
        fout.write(lineP)
import os
import sys


with open("Tests/test{}.csv".format(sys.argv[1]), "r") as f:
    lines = f.readlines()




for i in range(1, len(lines)):
    data = lines[i].split(",")
    comm = "0 {} {}".format(data[1], data[2])


    print("sending:"+comm)
    fdi = os.open("Tmp/inFifo", os.O_WRONLY)
    os.write(fdi, comm.encode("utf-8"))
    os.close(fdi)

    fdo = os.open("Tmp/outFifo", os.O_RDONLY)
    out = os.read(fdo, 50)
    os.close(fdo)
    print(out)


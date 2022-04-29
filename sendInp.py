import os
import sys


fd = os.open('Tmp/inFifo', os.O_WRONLY)
outStr = "{},{}".format(sys.argv[1], sys.argv[2])
os.write(fd, "{:4}".format(len(outStr)).encode('utf-8'))
os.write(fd, outStr.encode('utf-8'))
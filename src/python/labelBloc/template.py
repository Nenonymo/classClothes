import sys
import os

#input, do not modify
jobId = sys.argv[1]
files = [sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5]] #color, gray, wavelets, waveletFiltering
inLabel = sys.argv[6]
#end of input


#########################
#                       #
# All the code you want #
#                       #
#########################


#Output, do not modify anything but outString
outpFile = "../../../Tmp/{}".format(jobId)
outString = "{} {} ".format("l1", "l2");
fd = os.open(outpFile, os.O_WRONLY)
os.write(fd, outString.encode('utf-8'))
os.close(fd)

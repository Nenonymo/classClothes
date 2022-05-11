import sys
import os

#input, do not modify
jobId = sys.argv[1]
filesPath = sys.argv[2]
files = ["{}{}_{}.bmp".format(filesPath, a, jobId) for a in ["crop", "gray", "wavH", "wavV"]] #color, gray, horizontal and vetical wavelets
inLabel = sys.argv[3]
#end of input


#########################
#                       #
# All the code you want #
#                       #
#########################


#Output, do not modify anything but outString
outpFile = "Tmp/{}".format(jobId)
outString = "2 {}\n".format(4)
fd = os.open(outpFile, os.O_WRONLY | os.O_CREAT | os.O_APPEND)
os.write(fd, outString.encode('utf-8'))
os.close(fd)


#Code written by:
#      - Nemo Chentre
#
# Last modified: 11/05/2022
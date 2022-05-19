# import the necessary packages
from tensorflow.keras.preprocessing.image import img_to_array
from tensorflow.keras.preprocessing.image import load_img
from tensorflow.keras.models import load_model
import numpy as np
import mimetypes
import argparse
import imutils
import cv2
import os

MODEL_PATH = "bboxRegressor.h5"
FILES_PATH = "../../data/Datasets_Enhancy/datasets/"

#Load model
print("[INFO] loading object detector...")
model = load_model(MODEL_PATH)

def predictBbox(model, filePath):
    #load image
    image = load_img(filePath, target_size=(224, 224))
    image = img_to_array(image) / 255.0
    image = np.expand_dims(image, axis=0)

    preds = model.predict(image)[0]
    (startX, startY, endX, endY) = preds
    # load the input image (in OpenCV format), resize it such that it
    # fits on our screen, and grab its dimensions
    image = cv2.imread(filePath)
    image = imutils.resize(image, width=600)
    (h, w) = image.shape[:2]
    # scale the predicted bounding box coordinates based on the image
    # dimensions
    startX = int(startX * w)
    startY = int(startY * h)
    endX = int(endX * w)
    endY = int(endY * h)

    return (startX, startY, endX, endY)

def score(trueVal, predVal):
    res = 0.0
    for i in range(len(predVal)):
        res += abs(int(trueVal[i]) - predVal[i])
    return res


with open("../../extra/clean_export.dat", "r") as f:
    data = f.readlines()

f = open("segmenterOutput.txt", "w")
for (i, l) in enumerate(data[1:20]):
    line = l.split(" ")
    filePath = line[1]
    trueVal = (line[2], line[3], line[5], line[6])
    predVal = predictBbox(model, FILES_PATH + filePath)
    sc = score(trueVal, predVal)
    f.write("{} {} {} {} {} {}\n".format(filePath, score, predVal[0], predVal[1], predVal[2], predVal[3]))
f.close()




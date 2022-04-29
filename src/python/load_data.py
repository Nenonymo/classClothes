import csv
import cv2
from operator import itemgetter



def label_cleaner(l, labelFilter):
    labels = l[1:len(l)-1].split(",")
    ret = []
    for label in labels:
        if not ("Null" in label or "null" in label or "nan" in label):
            label = label.replace("'", "")
            label = label.replace(" ", "")
            label = label.replace("[", "")
            label = label.replace("]", "")
            if len(labelFilter) > 0: label = itemgetter(*labelFilter)(label)
            ret.append(label)
    return ret

def load_data(count=-1, img_type=[], labelFilter=[]):
    CSVPATH = r"data/csv/export_labels_working.csv"
    IMAGEPATH = r"data/Datasets_Enhancy/processed/"
    IMAGEPREFIX =  [r"crop__", r"gray__", r"wav1__", r"wav2__"] 
    images = []
    labels = []
    loops = 0
    if len(img_type) > 0: IMAGEPREFIX = img_type
    with open(CSVPATH) as csvfile:
        csvreader = csv.reader(csvfile)
        headings = next(csvreader)
        for row in csvreader:
            if loops == count: break
            # Prepare the path for a prefix
            img_paths = [i + row[2] + ".jpg" for i in IMAGEPREFIX]
            for i in img_paths:
                # Image labels
                labels.append(label_cleaner(row[1], labelFilter))
                # Image file
                img = cv2.imread(IMAGEPATH + i)
                print(IMAGEPATH + i)
                img = img[:,:,::-1] # BGR -> RGB
                images.append(img)
            loops += 1

    return images, labels




if __name__ == '__main__':
    load_data()
import csv
import cv2
CSVPATH = r"../../data/csv/export_labels_working.csv"
IMAGEPATH = r"../../data/Datasets_Enhancy/datasets/"

def label_cleaner(l):
    labels = l[1:len(l)-1].split(",")
    ret = []
    for label in labels:
        if not ("Null" in label or "null" in label or "nan" in label):
            label = label.replace("'", "")
            label = label.replace(" ", "")
            ret.append(label)
    return ret

def load_data():
    i = 0
    images = []
    labels = []
    with open(CSVPATH) as csvfile:
        csvreader = csv.reader(csvfile)
        headings = next(csvreader)
        for row in csvreader:
            if i == 100: break
            labels.append(label_cleaner(row[1]))
            img = cv2.imread(IMAGEPATH + row[0])
            images.append(img)
            i += 1

    return images, labels




if __name__ == '__main__':
    load_data()
import csv
import cv2
CSVPATH = r"data/csv/export_labels_working.csv"
IMAGEPATH = r"data/Datasets_Enhancy/processed/"
IMAGEPREFIX =  [r"crop__", r"gray__", r"wav1__", r"wav2__"] 

def label_cleaner(l):
    labels = l[1:len(l)-1].split(",")
    ret = []
    for label in labels:
        if not ("Null" in label or "null" in label or "nan" in label):
            label = label.replace("'", "")
            label = label.replace(" ", "")
            label = label.replace("[", "")
            label = label.replace("]", "")
            ret.append(label)
    return ret

def load_data():
    images = []
    labels = []
    with open(CSVPATH) as csvfile:
        csvreader = csv.reader(csvfile)
        headings = next(csvreader)
        for row in csvreader:
            # Prepare the path for a prefix
            img_paths = [i + row[2] + ".jpg" for i in IMAGEPREFIX]
            for i in img_paths:
                # Image labels
                labels.append(label_cleaner(row[1]))
                # Image file
                img = cv2.imread(IMAGEPATH + i)
                img = img[:,:,::-1] # BGR -> RGB
                images.append(img)

    return images, labels




if __name__ == '__main__':
    load_data()
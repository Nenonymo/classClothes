import csv
import cv2
CSVPATH = r"../../data/csv/export_labels_working.csv"
IMAGEPATH = r"../../data/Datasets_Enhancy/processed/"
IMAGEPREFIX = [ r"crop__" ]

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
    i = 0
    images = []
    labels = []
    with open(CSVPATH) as csvfile:
        csvreader = csv.reader(csvfile)
        headings = next(csvreader)
        for row in csvreader:
            if i == 200: break # TODO debug

            # Prepare the path for a prefix
            img_id = row[0]
            img_id_split = img_id.split('/')
            base_path = '/'.join([x for x in img_id_split[:-1]]) + '/'
            img_name = img_id_split[-1]

            for pre in IMAGEPREFIX:
                # Image labels
                labels.append(label_cleaner(row[1]))
                # Image file
                img = cv2.imread(IMAGEPATH + pre + img_name)
                img = img[:,:,::-1] # BGR -> RGB
                images.append(img)
                i += 1

    return images, labels




if __name__ == '__main__':
    load_data()
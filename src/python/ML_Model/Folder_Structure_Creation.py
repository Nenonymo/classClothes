import json
import os
from PIL import Image
# Change this path to local directory path where annotation json files are saved.
os.chdir('D:/Umea_Robotics/08.Machine Vision/Annotation/')
x = os.listdir()
# Classes level 1 attributes are stored in final_atr variable
final_atr = []
# categories are stored in cat
cat = []
total = 0
for y in x:
    with open(y, 'r') as f:
        data = json.load(f)
        for z in range(len(data['annotations'])):
            if 'attributes' in data['annotations'][z]:
                im_atr = data['annotations'][z]['attributes']
                for w in im_atr:
                    if w not in final_atr:
                        final_atr.append(w)
                    # change below if condition classes level 1 variable desired variable value
                    # to create folder structure.
                    if w == 'Col':
                        total = total + 1
                        if im_atr[w] not in cat:
                            cat.append(im_atr[w])
t = [0] * len(cat)
# all images ids belongs to each category are stored in im_id dictionary
im_id = {}
# all image ids segmentation information are stored in im_seg
im_seg = {}

for y in x:
    with open(y, 'r') as f:
        data = json.load(f)
        for z in range(len(data['annotations'])):
            if 'attributes' in data['annotations'][z]:
                im_atr = data['annotations'][z]['attributes']
                for w in im_atr:
                    if w not in final_atr:
                        final_atr.append(w)
                    # change below if condition classes level 1 variable desired variable value
                    # to create folder structure.
                    if w == 'Col':
                        total = total + 1
                        if im_atr[w] not in cat:
                            cat.append(im_atr[w])
                        for v in range(len(cat)):
                            if im_atr[w] == cat[v]:
                                t[v] = t[v] + 1
                                if t[v] == 1:
                                    im_id[cat[v]] = [data['annotations'][z]['image_id']]
                                    im_seg[cat[v]] = [data['annotations'][z]['segmentation'][0]]
                                else:
                                    im_id[cat[v]].append(data['annotations'][z]['image_id'])
                                    im_seg[cat[v]].append(data['annotations'][z]['segmentation'][0])


# Change this path to local directory path where dataset images are saved.
os.chdir('D:/Umea_Robotics/08.Machine Vision/datasets/')

# all folder structure directory paths are stored in new dictionary
new = {}

for dirs in os.walk(os.getcwd(), topdown=True):
    new[dirs[0].split("\\")[-1]] = dirs[0]

# Change this path to local directory path where you want new folder structure to be saved.
os.chdir('D:/Load_Data_Col_180/')
parent_dir = os.getcwd()
p = 0
for q in im_id:
    new_dir = os.path.join(parent_dir, q)
    os.mkdir(new_dir)
    for r in range(len(im_id[q])):
        fin_id = im_id[q][r].split('/')[-1]
        fin_dir = im_id[q][r].split('/')[-2]
        if fin_dir in new:
            final_path = new[fin_dir]
            if fin_id in os.listdir(final_path):
                os.chdir(final_path)
                fin_seg = im_seg[q][r]
                # Converting image from RGB to Grayscale. if RGB images are required remove .convert
                im = Image.open(fin_id).convert('L')
                # cropping the image based on image segmentation
                im1 = im.crop((fin_seg[0], fin_seg[1], fin_seg[4], fin_seg[5]))
                # resizing the images to 128 x 128
                im2 = im1.resize((180, 180))
                os.chdir(new_dir)
                # saving the image in .jpg format
                im2.save(q+'_' + str(r)+'.jpg')
    p = p + 1
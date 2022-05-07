import load_data
images, labels = load_data.load_data(count = 5, img_type=[r"crop__"], labelFilter=[2, 3])

print(labels)

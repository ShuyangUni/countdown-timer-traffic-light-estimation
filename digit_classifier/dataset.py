import numpy as np
import os
import torch
from torch.utils.data import Dataset
from PIL import Image
from torchvision import transforms

## my dataset
def default_loader(path):
    return Image.open(path)

class MyDataset(Dataset):
    def __init__(self, path, transform=transforms.ToTensor(), loader=default_loader):
        self.path = path
        ## load imgnames and labels
        self.imgnames = []
        self.labels = []
        for subfolder in os.listdir(path):
            subfolder_path = os.path.join(path,subfolder)
            sub_imgnames = [ os.path.join(subfolder_path,x) for x in os.listdir(subfolder_path)]
            self.imgnames = self.imgnames + sub_imgnames
            if subfolder=='null':
                sub_labels = [ 10 for n in range(len(sub_imgnames))]
            else:
                sub_labels = [ int(subfolder) for n in range(len(sub_imgnames))]
            self.labels = self.labels + sub_labels
        ## load workers
        self.transform = transform
        self.loader = loader

    def __getitem__(self, index):
        img = self.loader(self.imgnames[index])
        img = self.transform(img)
        label = self.labels[index]
        return img,label

    def __len__(self):
        return len(self.imgnames)
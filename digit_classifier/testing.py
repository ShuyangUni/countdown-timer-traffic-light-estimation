from tokenize import Double
from dataset import MyDataset
from model import MyCNN
import os
import torch
# from PIL import Image
import cv2
from torchvision import transforms
from torch.utils.data import DataLoader
from torch.autograd import Variable
import time

## load model
model = torch.load('model.pkl')
model.eval()
loss_func = torch.nn.CrossEntropyLoss()

## testing
folder_testing = "/home/uni/Data/traffic_light/udi_cttl_dataset/5_offset"
save_folder = "/home/uni/Data/traffic_light/udi_cttl_dataset/classification_results/5_offset"

def split_image(img_path):
    img = cv2.imread(img_path)
    img_gray = cv2.cvtColor(img,cv2.COLOR_RGB2GRAY)
    img_gray = cv2.resize(img_gray,(32,32))
    img_l = img_gray[0:32,0:16]
    img_r = img_gray[0:32,16:32]
    img_l = img_l / 255.0
    img_r = img_r / 255.0
    img_l = torch.unsqueeze(torch.tensor(img_l, dtype=torch.float32),0)
    img_l = torch.unsqueeze(img_l,0)
    img_r = torch.unsqueeze(torch.tensor(img_r, dtype=torch.float32),0)
    img_r = torch.unsqueeze(img_r,0)
    return img_l,img_r

time_start=time.time()

counter = 0
for subfolder in os.listdir(folder_testing):
    subfolder_path = os.path.join(folder_testing,subfolder)
    file_gt = os.path.join(subfolder_path,"gt.txt")
    file_in = open(file_gt,'r')
    file_out = open(save_folder+"/"+subfolder+".txt",'w')
    print(subfolder)
    for line in file_in:
        str_id = line.split(" ",1)[0]
        img_l,img_r = split_image(subfolder_path + "/" + str_id + ".jpg")

        # tens place
        var_l = Variable(img_l, volatile=True)
        out_l = model(var_l)
        pred_l = torch.max(out_l, 1)[1]

        # units place
        var_r = Variable(img_r, volatile=True)
        out_r = model(var_r)
        pred_r = torch.max(out_r, 1)[1]
        print("scan: %s, tens: %d, units: %d" %(str_id, pred_l,pred_r))
        counter = counter + 1
        file_out.writelines(str(pred_l.tolist()[0])+" "+str(pred_r.tolist()[0])+"\n")

time_end=time.time()
duration = time_end - time_start

print('total duration:',duration)
print('total frames:',counter)
print('average time:',duration / counter)
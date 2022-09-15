import torch
import torch.nn as nn

class MyCNN(nn.Module):
    def __init__(self):
        super(MyCNN, self).__init__()
        # input: 1*32*16
        # output: 8*16*8
        self.conv1 = nn.Sequential(nn.Conv2d(in_channels=1,out_channels=8,kernel_size=3,stride=1,padding=1),
                                   nn.ReLU(inplace=True),
                                   nn.MaxPool2d(kernel_size=2))
        # input: 8*16*8
        # output: 32*8*4
        self.conv2 = nn.Sequential(nn.Conv2d(in_channels=8,out_channels=32,kernel_size=3,stride=1,padding=1),
                                  nn.ReLU(inplace=True),
                                  nn.MaxPool2d(kernel_size=2))
        # input: 32*8*4
        # output: 11
        self.fc = nn.Sequential(
            nn.Linear(32*8*4, 64),
            nn.ReLU(inplace=True),
            nn.Linear(64, 11)
        )

    def forward(self, x):
        conv1_out = self.conv1(x)
        conv2_out = self.conv2(conv1_out)
        vec = conv2_out.view(conv2_out.size(0), -1)
        out = self.fc(vec)
        return out

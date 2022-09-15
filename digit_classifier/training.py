from dataset import MyDataset
from model import MyCNN
from torch.utils.data import DataLoader
import torch
from torch.autograd import Variable

train_path = r'/home/uni/Data/traffic_light/classification/training_training'
train_data=MyDataset(train_path)
train_loader = DataLoader(dataset=train_data, batch_size=16, shuffle=True)

test_path = r'/home/uni/Data/traffic_light/classification/training_testing'
test_data=MyDataset(test_path)
test_loader = DataLoader(dataset=test_data, batch_size=64)

model = MyCNN()

optimizer = torch.optim.Adam(model.parameters())
loss_func = torch.nn.CrossEntropyLoss()

## training
for epoch in range(10):
    print('epoch {}'.format(epoch + 1))
    # training
    train_loss = 0.
    train_acc = 0.
    for batch_x, batch_y in train_loader:
        batch_x, batch_y = Variable(batch_x), Variable(batch_y)
        out = model(batch_x)
        loss = loss_func(out, batch_y)
        train_loss += loss.item()
        pred = torch.max(out, 1)[1]
        train_correct = (pred == batch_y).sum()
        train_acc += train_correct.item()
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
    print('Train Loss: {:.6f}, Acc: {:.6f}'.format(train_loss / (len(
        train_data)), train_acc / (len(train_data))))

    # evaluation
    model.eval()
    eval_loss = 0.
    eval_acc = 0.
    for batch_x, batch_y in test_loader:
        batch_x, batch_y = Variable(batch_x, volatile=True), Variable(batch_y, volatile=True)
        out = model(batch_x)
        loss = loss_func(out, batch_y)
        eval_loss += loss.item()
        pred = torch.max(out, 1)[1]
        num_correct = (pred == batch_y).sum()
        eval_acc += num_correct.item()
    print('Test Loss: {:.6f}, Acc: {:.6f}'.format(eval_loss / (len(
        test_data)), eval_acc / (len(test_data))))

torch.save(model, 'model.pkl')
import numpy as np
import matplotlib.pyplot as plt
import time
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, TensorDataset
from sklearn.metrics import confusion_matrix, accuracy_score
import seaborn as sns

# 设置中文显示
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

# 设置随机种子以保证结果可复现
torch.manual_seed(42)
np.random.seed(42)

# 数据加载函数
def load_data(filename):
    data = np.loadtxt(filename)
    X = data[:, :-1]
    y = data[:, -1].astype(int)  # 类别标签已经是数字格式（0, 1, 2）
    
    # PyTorch的交叉熵损失函数需要从0开始的类别，这里已经是0开始了
    return X, y

# 数据标准化
def standardize(X_train, X_test):
    mean = np.mean(X_train, axis=0)
    std = np.std(X_train, axis=0)
    X_train_std = (X_train - mean) / std
    X_test_std = (X_test - mean) / std
    return X_train_std, X_test_std

# 定义神经网络模型
class BPNeuralNetwork(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(BPNeuralNetwork, self).__init__()
        self.layer1 = nn.Linear(input_size, hidden_size)
        self.sigmoid = nn.Sigmoid()
        self.layer2 = nn.Linear(hidden_size, output_size)
        self.softmax = nn.Softmax(dim=1)
        
    def forward(self, x):
        x = self.layer1(x)
        x = self.sigmoid(x)
        x = self.layer2(x)
        # 注意：在使用nn.CrossEntropyLoss时，不需要在forward中应用softmax
        # 因为CrossEntropyLoss已经包含了softmax操作
        return x
    
    def predict(self, x):
        with torch.no_grad():
            x = self.forward(x)
            return torch.softmax(x, dim=1)

# 训练函数
def train_model(model, train_loader, criterion, optimizer, epochs, device):
    model.train()
    losses = []
    
    for epoch in range(epochs):
        epoch_loss = 0
        for inputs, targets in train_loader:
            inputs, targets = inputs.to(device), targets.to(device)
            
            # 前向传播
            outputs = model(inputs)
            loss = criterion(outputs, targets)
            
            # 反向传播和优化
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            
            epoch_loss += loss.item()
        
        # 记录每个epoch的平均损失
        avg_loss = epoch_loss / len(train_loader)
        losses.append(avg_loss)
        
        # 打印训练进度
        if epoch % 100 == 0:
            print(f"第 {epoch} 代，训练损失: {avg_loss:.4f}")
    
    return losses

# 评估函数
def evaluate_model(model, test_loader, device):
    model.eval()
    all_preds = []
    all_targets = []
    
    with torch.no_grad():
        for inputs, targets in test_loader:
            inputs, targets = inputs.to(device), targets.to(device)
            outputs = model(inputs)
            _, predicted = torch.max(outputs, 1)
            
            all_preds.extend(predicted.cpu().numpy())
            all_targets.extend(targets.cpu().numpy())
    
    return np.array(all_preds), np.array(all_targets)

# 主函数
def main():
    # 检查是否有可用的GPU
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
    print(f"使用设备: {device}")
    
    # 加载数据
    X_train, y_train = load_data('C:/Users/ASUS/Desktop/大三下/人工智能导论实验/实验六反向传播算法/traindata.txt')
    X_test, y_test = load_data('C:/Users/ASUS/Desktop/大三下/人工智能导论实验/实验六反向传播算法/testdata.txt')
    
    # 数据标准化
    X_train_std, X_test_std = standardize(X_train, X_test)
    
    # 转换为PyTorch张量
    X_train_tensor = torch.FloatTensor(X_train_std)
    y_train_tensor = torch.LongTensor(y_train)
    X_test_tensor = torch.FloatTensor(X_test_std)
    y_test_tensor = torch.LongTensor(y_test)
    
    # 创建数据加载器
    train_dataset = TensorDataset(X_train_tensor, y_train_tensor)
    train_loader = DataLoader(train_dataset, batch_size=16, shuffle=True)
    
    test_dataset = TensorDataset(X_test_tensor, y_test_tensor)
    test_loader = DataLoader(test_dataset, batch_size=16)
    
    # 模型参数
    input_size = X_train.shape[1]  # 4个特征
    hidden_size = 10  # 10个隐藏神经元
    output_size = 3  # 3个输出类别
    learning_rate = 0.1
    epochs = 1000
    
    # 记录训练开始时间
    start_time = time.time()
    
    # 创建模型
    model = BPNeuralNetwork(input_size, hidden_size, output_size).to(device)
    
    # 定义损失函数和优化器
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(model.parameters(), lr=learning_rate)
    
    # 训练模型
    losses = train_model(model, train_loader, criterion, optimizer, epochs, device)
    
    # 记录训练结束时间
    end_time = time.time()
    training_time = end_time - start_time
    
    # 在测试集上评估
    y_pred, y_true = evaluate_model(model, test_loader, device)
    
    # 类别已经是从0开始，不需要转换
    # 保持原样
    y_pred = y_pred
    y_true = y_true
    
    accuracy = accuracy_score(y_true, y_pred)
    print(f"\n测试准确率: {accuracy*100:.2f}%")
    print(f"训练用时: {training_time:.2f} 秒")
    
    # 绘制损失曲线
    plt.figure(figsize=(10, 6))
    plt.plot(losses)
    plt.title('训练损失曲线')
    plt.xlabel('迭代次数')
    plt.ylabel('损失')
    plt.grid(True)
    plt.savefig('pytorch_loss_curve.png')
    print("损失曲线已保存为 pytorch_loss_curve.png")
    
    # 计算并显示混淆矩阵
    cm = confusion_matrix(y_true, y_pred)
    plt.figure(figsize=(8, 6))
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', 
                xticklabels=['类别1', '类别2', '类别3'],
                yticklabels=['类别1', '类别2', '类别3'])
    plt.xlabel('预测类别')
    plt.ylabel('真实类别')
    plt.title('测试集上的混淆矩阵')
    plt.tight_layout()
    plt.savefig('pytorch_confusion_matrix.png')
    print("混淆矩阵已保存为 pytorch_confusion_matrix.png")
    
    # 独立运行10次的结果
    accuracies = []
    times = []
    
    print("\n开始独立运行10次...")
    
    for i in range(10):
        # 重置随机种子以确保不同的初始化
        torch.manual_seed(i)
        np.random.seed(i)
        
        start_time = time.time()
        
        # 创建新模型
        model = BPNeuralNetwork(input_size, hidden_size, output_size).to(device)
        optimizer = optim.SGD(model.parameters(), lr=learning_rate)
        
        # 训练模型
        train_model(model, train_loader, criterion, optimizer, epochs, device)
        
        end_time = time.time()
        run_time = end_time - start_time
        
        # 评估模型
        y_pred, y_true = evaluate_model(model, test_loader, device)
        y_pred = y_pred + 1
        y_true = y_true + 1
        
        acc = accuracy_score(y_true, y_pred)
        
        accuracies.append(acc)
        times.append(run_time)
        
        print(f"运行 {i+1}/10: 准确率 = {acc*100:.2f}%, 用时 = {run_time:.2f} 秒")
    
    # 计算平均准确率和标准差
    mean_accuracy = np.mean(accuracies)
    std_accuracy = np.std(accuracies)
    mean_time = np.mean(times)
    
    print(f"\n10次运行平均准确率: {mean_accuracy*100:.2f}% ± {std_accuracy*100:.2f}%")
    print(f"10次运行平均用时: {mean_time:.2f} 秒")
    
    # 显示所有图形
    plt.show()

if __name__ == "__main__":
    main()

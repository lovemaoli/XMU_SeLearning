import numpy as np
import matplotlib.pyplot as plt
import time
from sklearn.metrics import confusion_matrix, accuracy_score
import seaborn as sns

# 设置中文显示
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

# 激活函数和它们的导数
def sigmoid(x):
    return 1 / (1 + np.exp(-np.clip(x, -500, 500)))  # 使用clip防止溢出

def sigmoid_derivative(x):
    s = sigmoid(x)
    return s * (1 - s)

def softmax(x):
    exp_x = np.exp(x - np.max(x, axis=1, keepdims=True))  # 减去最大值防止溢出
    return exp_x / np.sum(exp_x, axis=1, keepdims=True)

# 交叉熵损失函数
def cross_entropy_loss(y_pred, y_true):
    m = y_true.shape[0]
    log_likelihood = -np.log(np.sum(y_pred * y_true, axis=1))
    loss = np.sum(log_likelihood) / m
    return loss

# 数据加载函数
def load_data(filename):
    data = np.loadtxt(filename)
    X = data[:, :-1]
    y = data[:, -1].astype(int)  # 类别标签已经是数字格式（0, 1, 2）
    
    # 将类别标签转换为one-hot编码
    y_one_hot = np.zeros((y.size, 3))
    for i in range(y.size):
        y_one_hot[i, y[i]] = 1  # 类别从0开始，直接使用作为索引
    
    return X, y_one_hot, y

# 数据标准化
def standardize(X_train, X_test):
    mean = np.mean(X_train, axis=0)
    std = np.std(X_train, axis=0)
    X_train_std = (X_train - mean) / std
    X_test_std = (X_test - mean) / std
    return X_train_std, X_test_std

# BP神经网络类
class BPNeuralNetwork:
    def __init__(self, input_size, hidden_size, output_size, learning_rate=0.1):
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size
        self.learning_rate = learning_rate
        
        # 初始化权重和偏置
        self.W1 = np.random.randn(input_size, hidden_size) * 0.01
        self.b1 = np.zeros((1, hidden_size))
        self.W2 = np.random.randn(hidden_size, output_size) * 0.01
        self.b2 = np.zeros((1, output_size))
        
        self.losses = []  # 记录训练损失
        
    def forward(self, X):
        # 前向传播
        self.z1 = np.dot(X, self.W1) + self.b1
        self.a1 = sigmoid(self.z1)
        self.z2 = np.dot(self.a1, self.W2) + self.b2
        self.a2 = softmax(self.z2)
        return self.a2
    
    def backward(self, X, y, output):
        m = X.shape[0]
        
        # 反向传播计算梯度
        dz2 = output - y  # 交叉熵损失对softmax输出的导数
        dW2 = (1/m) * np.dot(self.a1.T, dz2)
        db2 = (1/m) * np.sum(dz2, axis=0, keepdims=True)
        
        dz1 = np.dot(dz2, self.W2.T) * sigmoid_derivative(self.z1)
        dW1 = (1/m) * np.dot(X.T, dz1)
        db1 = (1/m) * np.sum(dz1, axis=0, keepdims=True)
        
        # 更新权重和偏置
        self.W2 -= self.learning_rate * dW2
        self.b2 -= self.learning_rate * db2
        self.W1 -= self.learning_rate * dW1
        self.b1 -= self.learning_rate * db1
    
    def train(self, X, y, epochs=1000, batch_size=16, verbose=True):
        m = X.shape[0]
        
        for epoch in range(epochs):
            # 随机打乱数据
            permutation = np.random.permutation(m)
            X_shuffled = X[permutation]
            y_shuffled = y[permutation]
            
            # 批量梯度下降
            for i in range(0, m, batch_size):
                end = min(i + batch_size, m)
                X_batch = X_shuffled[i:end]
                y_batch = y_shuffled[i:end]
                
                # 前向传播
                output = self.forward(X_batch)
                
                # 反向传播
                self.backward(X_batch, y_batch, output)
            
            # 计算整个训练集的损失
            output = self.forward(X)
            loss = cross_entropy_loss(output, y)
            self.losses.append(loss)
            
            # 打印训练进度
            if verbose and epoch % 100 == 0:
                print(f"第 {epoch} 代，训练损失: {loss:.4f}")
    
    def predict(self, X):
        output = self.forward(X)
        return np.argmax(output, axis=1)  # 类别从0开始
    
    def plot_loss(self):
        plt.figure(figsize=(10, 6))
        plt.plot(self.losses)
        plt.title('训练损失曲线')
        plt.xlabel('迭代次数')
        plt.ylabel('损失')
        plt.grid(True)
        plt.savefig('bp_loss_curve.png')
        print("损失曲线已保存为 bp_loss_curve.png")

# 主函数
def main():
    # 加载数据
    X_train, y_train_one_hot, y_train = load_data('C:/Users/ASUS/Desktop/大三下/人工智能导论实验/实验六反向传播算法/traindata.txt')
    X_test, y_test_one_hot, y_test = load_data('C:/Users/ASUS/Desktop/大三下/人工智能导论实验/实验六反向传播算法/testdata.txt')
    
    # 数据标准化
    X_train_std, X_test_std = standardize(X_train, X_test)
    
    # 创建并训练神经网络
    input_size = X_train.shape[1]  # 4个特征
    hidden_size = 10  # 10个隐藏神经元
    output_size = 3  # 3个输出类别
    
    # 记录训练开始时间
    start_time = time.time()
    
    # 创建神经网络
    nn = BPNeuralNetwork(input_size, hidden_size, output_size, learning_rate=0.1)
    
    # 训练神经网络
    nn.train(X_train_std, y_train_one_hot, epochs=1000, batch_size=16)
    
    # 记录训练结束时间
    end_time = time.time()
    training_time = end_time - start_time
    
    # 在测试集上评估
    y_pred = nn.predict(X_test_std)
    accuracy = accuracy_score(y_test, y_pred)
    print(f"\n测试准确率: {accuracy*100:.2f}%")
    print(f"训练用时: {training_time:.2f} 秒")
    
    # 绘制损失曲线
    nn.plot_loss()
    
    # 计算并显示混淆矩阵
    cm = confusion_matrix(y_test, y_pred)
    plt.figure(figsize=(8, 6))
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', 
                xticklabels=['类别1', '类别2', '类别3'],
                yticklabels=['类别1', '类别2', '类别3'])
    plt.xlabel('预测类别')
    plt.ylabel('真实类别')
    plt.title('测试集上的混淆矩阵')
    plt.tight_layout()
    plt.savefig('bp_confusion_matrix.png')
    print("混淆矩阵已保存为 bp_confusion_matrix.png")
    
    # 独立运行10次的结果
    accuracies = []
    times = []
    
    print("\n开始独立运行10次...")
    
    for i in range(10):
        start_time = time.time()
        
        nn = BPNeuralNetwork(input_size, hidden_size, output_size, learning_rate=0.1)
        nn.train(X_train_std, y_train_one_hot, epochs=1000, batch_size=16, verbose=False)
        
        end_time = time.time()
        run_time = end_time - start_time
        
        y_pred = nn.predict(X_test_std)
        acc = accuracy_score(y_test, y_pred)
        
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

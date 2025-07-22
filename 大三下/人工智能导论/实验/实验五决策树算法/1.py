import numpy as np
from collections import Counter

class DecisionTreeID3:
    def __init__(self, max_depth=3):
        self.max_depth = max_depth  # 预剪枝参数：最大深度
    
    def entropy(self, y):
        counts = np.bincount(y)
        probs = counts[counts != 0] / len(y)
        return -np.sum(probs * np.log2(probs))
    
    def gain(self, X, y, feature):
        # 获取当前特征所有唯一值并排序
        values = X[:, feature]
        unique_values = np.unique(values)
        if len(unique_values) == 1:
            return 0, None  # 无法分割
        
        best_gain = 0
        best_split = None
        # 遍历所有中间点作为候选分裂点
        for i in range(len(unique_values) - 1):
            split = (unique_values[i] + unique_values[i+1]) / 2
            left_mask = values <= split
            right_mask = values > split
            
            if np.sum(left_mask) == 0 or np.sum(right_mask) == 0:
                continue  # 跳过无效分裂
                
            # 计算分裂后的加权熵
            left_entropy = self.entropy(y[left_mask])
            right_entropy = self.entropy(y[right_mask])
            weighted_entropy = (len(y[left_mask])/len(y)) * left_entropy + \
                              (len(y[right_mask])/len(y)) * right_entropy
            
            current_gain = self.base_entropy - weighted_entropy
            if current_gain > best_gain:
                best_gain = current_gain
                best_split = split
        return best_gain, best_split
    
    def best_split(self, X, y, depth):
        # 当达到最大深度或纯叶节点时停止
        if depth >= self.max_depth or self.entropy(y) == 0:
            return {'leaf': True, 'class': Counter(y).most_common(1)[0][0]}
        
        best_gain = -1
        best_feature = None
        best_split = None
        
        # 遍历所有特征寻找最佳分裂
        for feature in range(X.shape[1]):
            gain_value, split_value = self.gain(X, y, feature)
            if gain_value > best_gain:
                best_gain = gain_value
                best_feature = feature
                best_split = split_value
                
        if best_gain == 0:  # 无法继续分裂
            return {'leaf': True, 'class': Counter(y).most_common(1)[0][0]}
        
        # 递归构建子树
        left_mask = X[:, best_feature] <= best_split
        right_mask = X[:, best_feature] > best_split
        
        left_tree = self.best_split(X[left_mask], y[left_mask], depth+1)
        right_tree = self.best_split(X[right_mask], y[right_mask], depth+1)
        
        return {
            'leaf': False,
            'feature': best_feature,
            'split': best_split,
            'left': left_tree,
            'right': right_tree
        }
    
    def fit(self, X, y):
        self.base_entropy = self.entropy(y)
        self.tree = self.best_split(X, y, 0)
        return self.tree
    
    def predict_sample(self, tree, sample):
        if tree['leaf']:
            return tree['class']
        if sample[tree['feature']] <= tree['split']:
            return self.predict_sample(tree['left'], sample)
        else:
            return self.predict_sample(tree['right'], sample)
    
    def predict(self, X):
        return np.array([self.predict_sample(self.tree, sample) for sample in X])

# 数据读取与预处理
def load_data(filename):
    data = np.loadtxt(filename)
    X = data[:, :-1]
    y = data[:, -1].astype(int)
    return X, y

# 主程序
if __name__ == "__main__":
    # 加载数据
    X_train, y_train = load_data('C:/Users/ASUS/Desktop/大三下/人工智能导论实验/实验五决策树算法/train_data.txt')
    X_test, y_test = load_data('C:/Users/ASUS/Desktop/大三下/人工智能导论实验/实验五决策树算法/test_data.txt')
    
    # 训练模型
    dt = DecisionTreeID3(max_depth=3)
    tree = dt.fit(X_train, y_train)
    
    # 预测与评估
    y_pred = dt.predict(X_test)
    accuracy = np.sum(y_pred == y_test) / len(y_test)
    
    print(f"分类准确率: {accuracy*100:.2f}%")
    print("决策树结构：")
    print(tree)
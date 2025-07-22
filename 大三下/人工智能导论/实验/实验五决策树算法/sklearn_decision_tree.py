import numpy as np
from sklearn.tree import DecisionTreeClassifier, export_graphviz
import graphviz
from IPython.display import display

# 数据读取与预处理
def load_data(filename):
    data = np.loadtxt(filename)
    X = data[:, :-1]
    y = data[:, -1].astype(int)
    return X, y

# 主程序
if __name__ == "__main__":
    # 加载数据
    X_train, y_train = load_data('C:/Users/ASUS/Desktop/大三下/人工智能导论实验/实验五决策树算法/traindata.txt')
    X_test, y_test = load_data('C:/Users/ASUS/Desktop/大三下/人工智能导论实验/实验五决策树算法/testdata.txt')
    
    # 创建决策树模型，使用熵作为信息增益的判断函数
    dt = DecisionTreeClassifier(criterion='entropy', max_depth=3, random_state=42)
    
    # 训练模型
    dt.fit(X_train, y_train)
    
    # 可视化决策树
    dot_data = export_graphviz(
        dt,
        out_file=None,
        feature_names=[f'Feature {i}' for i in range(X_train.shape[1])],
        class_names=[str(i) for i in np.unique(y_train)],
        filled=True,
        rounded=True,
        special_characters=True
    )
    graph = graphviz.Source(dot_data)
    display(graph)
    
    # 预测与评估
    y_pred = dt.predict(X_test)
    accuracy = np.sum(y_pred == y_test) / len(y_test)
    
    print(f"分类准确率: {accuracy*100:.2f}%")
    
    # 输出决策树的一些信息
    print("决策树深度:", dt.get_depth())
    print("决策树叶节点数:", dt.get_n_leaves())

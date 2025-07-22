import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.tree import DecisionTreeClassifier, export_graphviz
from sklearn.metrics import confusion_matrix, classification_report, roc_curve, auc, precision_recall_curve
import graphviz
from IPython.display import display

# 设置中文显示
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

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
    graph.render("decision_tree_visualization", format="png", cleanup=True)
    print("决策树可视化已保存为 decision_tree_visualization.png")
    
    # 预测与评估
    y_pred = dt.predict(X_test)
    accuracy = np.sum(y_pred == y_test) / len(y_test)
    
    print(f"分类准确率: {accuracy*100:.2f}%")
    
    # 输出决策树的一些信息
    print("决策树深度:", dt.get_depth())
    print("决策树叶节点数:", dt.get_n_leaves())
    
    # 计算并显示混淆矩阵
    cm = confusion_matrix(y_test, y_pred)
    plt.figure(figsize=(8, 6))
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', 
                xticklabels=np.unique(y_train),
                yticklabels=np.unique(y_train))
    plt.xlabel('预测类别')
    plt.ylabel('真实类别')
    plt.title('测试集上的混淆矩阵')
    plt.tight_layout()
    plt.savefig('confusion_matrix.png')
    print("混淆矩阵已保存为 confusion_matrix.png")
    
    # 计算并显示分类报告
    report = classification_report(y_test, y_pred, target_names=[str(i) for i in np.unique(y_train)])
    print("\n分类报告:")
    print(report)
    
    # 特征重要性
    feature_importance = dt.feature_importances_
    plt.figure(figsize=(10, 6))
    plt.bar(range(len(feature_importance)), feature_importance)
    plt.xticks(range(len(feature_importance)), [f'Feature {i}' for i in range(len(feature_importance))])
    plt.xlabel('特征')
    plt.ylabel('重要性')
    plt.title('特征重要性')
    plt.tight_layout()
    plt.savefig('feature_importance.png')
    print("特征重要性图已保存为 feature_importance.png")
    
    # 如果是二分类问题，绘制ROC曲线和PR曲线
    if len(np.unique(y_train)) == 2:
        # 获取预测概率
        y_proba = dt.predict_proba(X_test)[:, 1]
        
        # ROC曲线
        fpr, tpr, _ = roc_curve(y_test, y_proba)
        roc_auc = auc(fpr, tpr)
        
        plt.figure(figsize=(8, 6))
        plt.plot(fpr, tpr, color='darkorange', lw=2, label=f'ROC曲线 (AUC = {roc_auc:.2f})')
        plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
        plt.xlim([0.0, 1.0])
        plt.ylim([0.0, 1.05])
        plt.xlabel('假正例率 (FPR)')
        plt.ylabel('真正例率 (TPR)')
        plt.title('接收者操作特征曲线 (ROC)')
        plt.legend(loc="lower right")
        plt.savefig('roc_curve.png')
        print("ROC曲线已保存为 roc_curve.png")
        
        # PR曲线
        precision, recall, _ = precision_recall_curve(y_test, y_proba)
        
        plt.figure(figsize=(8, 6))
        plt.plot(recall, precision, color='blue', lw=2)
        plt.xlabel('召回率 (Recall)')
        plt.ylabel('精确率 (Precision)')
        plt.title('精确率-召回率曲线 (PR)')
        plt.savefig('pr_curve.png')
        print("PR曲线已保存为 pr_curve.png")
    
    # 显示所有图形
    plt.show()

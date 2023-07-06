/* BST:Binary Sort Tree二叉排序树  */
/* 二叉排序树    的插入，查找，删除  */


/*测试例子： 
*请先输入树的结点个数：12
*请先输入树的结点数值：70 67 46 105 100 99 104 103 115 110 108 112
*中序遍历结果：46 67 70 99 100 103 104 105 108 110 112 115
*请先输入要查找的数值：70
*查找成功！

*请先输入要删除的数值：105
*删除成功！
*中序遍历结果：46 67 70 99 100 103 104 108 110 112 115 请按任意键继续. . .
 */
#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;

#define Status bool

//树的结点
typedef struct BiTNode
{
    ElemType data;
    struct  BiTNode *left,*right;
}BiTNode,*BiTree;

////声明树根
//typedef struct 
//{
//   BiTNode* root;
//}BiTree;


Status Delete(BiTNode* p);//声明一下

//构建二叉树，插入
void insert(BiTree& tree, int value)//创建树
{
    BiTNode* node=(BiTNode*)malloc(sizeof(BiTNode));//创建一个节点
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    if (tree == NULL)//判断树是不是空树
    {
        tree = node;
    }
    else {//不是空树
        BiTNode* temp = tree;//从树根开始
        while (temp != NULL)
        {
            if (value < temp->data)//小于就进左儿子
            {
                if (temp->left == NULL)
                {
                    temp->left = node;
                    return;
                }
                else {//继续判断
                    temp = temp->left;
                }
            }
            else {//否则进右儿子
 
                if (temp->right == NULL)
                {
                    temp->right = node;
                    return;
                }
                else {//继续判断
                    temp = temp->right;
                }
            }
        }
    }
    return;
}




// 递归查找二叉排序树T中是否存在key
// 指针F指向T的双亲，其初始值调用值为NULL
// 若查找成功，则指针P指向该数据元素结点，并返回TRUE
// 否则指针P指向查找路径上访问的最后一个结点，并返回FALSE
Status SearchBST(BiTNode* T,int key,BiTNode *f,BiTNode *p)
{
    if(!T)//查找不成功
    {
        p = f;
        return false;
    }
    else if (key == T->data)//查找成功
    {
        p = T;
        return true;
    }
    else if(key <T->data)
    {
        return SearchBST(T->left,key,T,p);//在左子树上继续查找
    }
    else
    {
        return SearchBST(T->right,key,T,p);//在右子树上继续查找
    }
}

void inorder(BiTNode* node)//树的中序遍历
{
    if (node != NULL)
    {
        inorder(node->left);
        printf("%d ",node->data);
        inorder(node->right);
    }
}

// bool SearchBST(BiTNode* T,int key)
// {
//     if(T == NULL)//查找不成功
//     {
//         return false;
//     }
//     else if (key == T->data)//查找成功
//     {
//         return true;
//     }
//     else if(key <T->data)
//     {
//         return SearchBST(T->left,key);//在左子树上继续查找
//     }
//     else
//     {
//         return SearchBST(T->right,key);//在右子树上继续查找
//     }
// }



//删除结点
Status DeleteBST(BiTNode* T,int key)
{
    if(T == NULL)
    {
        printf("该树为空，不能删除。");
        return false;
    }
    else
    {
        if(key == T->data)
        {
            return Delete(T);
        }
        else if(key < T->data)
        {
            return DeleteBST(T->left,key);
        }
        else
        {
            return DeleteBST(T->right,key);
        }
    }
}

Status Delete(BiTNode* p)
{
    BiTNode* q;
    BiTNode* s;
    if(p->right == NULL)
    {
        //右子树为空的时候，将左子树接上去就行了。
        q = p;
        p = p->left;
        free(q);
    }
    else if(p->left == NULL)
    {
        //左子树为空的时候，将右子树接上去就行了。
        q = p;
        p = p->right;
        free(q);
    }
    else
    {
        //直接前驱data替换要删除结点data
        //直接前驱的左子树接到原直接前驱那里
        q = p;
        s = p->left;
        while(s->right)
        {
            //通过迭代，找出，s子树的最大值，即最右子树。
            q = s;
            s = s->right;
        }

        p->data = s->data;
        if(q != p)
        {
            //若删除结点左子树是一颗斜树。
            q->right = s->left;
        }
        else
        {
            //若删除结点左子树中包含包含右子树，则将直接前驱结点的左子树接到直接前驱结点父节点右子树上。
            q->left = s->left;  
        }
        free(s);
    }
    return true;
}

int main()
{

    BiTree tree;
    tree = NULL;//创建一个空树
    int n,key;
    bool flag,flag2;

    BiTNode *f,*p;
    printf("请先输入树的结点个数：");
    scanf("%d",&n);
    printf("请先输入树的结点数值：");
    for(int i=0;i<n;i++)//输入n个数并创建这个树
    {
        int temp;
        scanf("%d",&temp);
        insert(tree,temp);
    }
    printf("中序遍历结果：");
    inorder(tree);//中序遍历

    printf("\n请先输入要查找的数值：");
    scanf("%d",&key);
    flag = SearchBST(tree,key,f,p);
    // flag = SearchBST(tree.root,key);
    if(flag == true)
    {
        printf("查找成功！\n");
    }
    else
    {
        printf("查找失败！\n");
    }
  

    printf("\n请先输入要删除的数值：");
    scanf("%d",&key);
    flag2 = DeleteBST(tree,key);
    if(flag == true)
    {
        printf("删除成功！\n");
    }
    else
    {
        printf("删除失败！\n");
    }

    printf("中序遍历结果：");
    inorder(tree);//中序遍历

    system("pause");
    return 0;
}






#include <bits/stdc++.h>

#define LINE    8
#define ROW     8

int Chessboard[LINE][ROW]    = {0};
int iNextX[8] = {1, 2, 2, 1, -1, -2, -2, -1};//第二点的相对X坐标
int iNextY[8] = {-2, -1, 1, 2, 2, 1, -1, -2};//第二点的相对Y坐标
int iNextXReal[8] = {0};//第二点的真实X坐标
int iNextYReal[8] = {0};//第二点的真实Y坐标
int iNextRealIndex;//候选的第二点中实际选出的第二点的索引
int iCount;              //有几个第二点符合条件
int iNextNextNum[8] = {0};//每个第二点有几个第三点


bool Tour(int x, int y)
{
    int step, i, j, tempX, tempY, iMin;

    //第一点
    Chessboard[y][x] = 1;

    //第2点到第64点
    for (step=2; step<=(LINE*ROW); step++)
    {
        for (i=0; i<8; i++)
        {
            iNextNextNum[i] = 0;
        }

        iCount = 0;
        for (i=0; i<8; i++)//查看这8个点是否符合要求
        {
            tempX = x + iNextX[i];
            tempY = y + iNextY[i];

            if (tempX>=0 && tempX<ROW && tempY>=0 && tempY<LINE \
                && Chessboard[tempY][tempX] == 0)//符合要求就求他的周围符合的点数
            {
                iNextXReal[iCount] = tempX;
                iNextYReal[iCount] = tempY;
                iCount++;
            }
        }

        if (iCount == 0)
        {
            return false;
        }
        else if (iCount == 1)
        {
            iNextRealIndex = 0;
        }
        else
        {

            for (i=0; i<iCount; i++)
            {
                for (j=0; j<8; j++)
                {
                    tempX = iNextXReal[i] + iNextX[j];
                    tempY = iNextYReal[i] + iNextY[j];
                    if (tempX>=0 && tempX<ROW && tempY>=0 && tempY<LINE \
                        && Chessboard[tempY][tempX] == 0)
                    {
                        iNextNextNum[i]++;//符合要求的每个点每个第2点周围有几个符合要求第3点
                    }

                }
            }

            iMin = iNextNextNum[0];
            iNextRealIndex = 0;
            for (i=1; i<iCount; i++)
            {
                if (iNextNextNum[i] < iMin)
                {
                    iMin = iNextNextNum[i];
                    iNextRealIndex = i;
                }
            }

        }

        //选出下一步最少的点
        x = iNextXReal[iNextRealIndex];
        y = iNextYReal[iNextRealIndex];
        Chessboard[y][x] = step;//第N点的值为N
    }
    return true;
}
void ShowStep(int step)
{
    int i, j;
    for (i=0; i<LINE; i++)
    {
        for (j=0; j<ROW; j++)
        {
            if (Chessboard[i][j] <= step+10 && Chessboard[i][j] > step)
                printf("%4d", Chessboard[i][j]-1);
            else
                printf("    ");
        }
        printf("\n");
    }
}

void Show(void)
{
    int i, j;
//    for (int step = 1; step <= LINE * ROW; step+=10)
//    {
//        printf("Step: %d - %d\n", step, step+10);
//        for (i=0; i<ROW; i++)
//        {
//            printf("----");
//        }
//        printf("\n");
//        ShowStep(step);
//        printf("\n");
//        for (i=0; i<ROW; i++)
//        {
//            printf("----");
//        }
//        printf("\n");
//    }
    printf("Step: %d 最终\n", LINE * ROW);
    for (int i=0; i<LINE; i++)
    {
        for (int j=0; j<ROW; j++)
        {
            printf("%4d", Chessboard[i][j]-1);
        }
        printf("\n");
    }
    
}

int main(void)
{
    int x, y;

    printf("请输入起始点（x, y）：");
    scanf("%d %d", &x, &y);
    //判断是否超出
    if(x>7||x<0||y>7||y<0){
        printf("输入不合理！\n");
        return 0;
    }

    if (Tour(x, y))
    {
        printf("游历成功！\n");
        Show();
    }
    else
    {
        printf("游历失败！\n");
    }

    return 0;
}


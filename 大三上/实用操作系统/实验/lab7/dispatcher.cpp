#include <iostream>
#include <queue>
using namespace std;

#define PROCESS_NUM 5  //线程数
struct Process
{
    char name;      //进程名称
    int arrive;     //到达时间
    int time;       //服务时间
    int start;      //开始时间
    int end;        //结束时间
    float rate;     //响应比
    bool activated; //是否到达
    int rest;       //剩余时间
};

Process processes[PROCESS_NUM] = {
        {'A', 0, 3, 0, 0, 1, 0, 0},
        {'B', 2, 6, 0, 0, 1, 0, 0},
        {'C', 4, 4, 0, 0, 1, 0, 0},
        {'D', 6, 5, 0, 0, 1, 0, 0},
        {'E', 8, 2, 0, 0, 1, 0, 0}
};

void resetProcesses() {
	processes[0].arrive = 0;
	processes[0].time = 3;
	processes[1].arrive = 2;
	processes[1].time = 6;
	processes[2].arrive = 4;
	processes[2].time = 4;
	processes[3].arrive = 6;
	processes[3].time = 5;
	processes[4].arrive = 8;
	processes[4].time = 2;
    for (int i = 0; i < PROCESS_NUM; i++) {
        processes[i].start = 0;
        processes[i].end = 0;
        processes[i].rate = 1;
        processes[i].activated = false;
        processes[i].rest = 0;
    }
}

void printResult() {
    for (int i = 0; i < PROCESS_NUM; ++i)
        cout << processes[i].name << " " << processes[i].end << " " << processes[i].end - processes[i].arrive << " " << processes[i].rate << endl;
}

void FCFS(Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && p[i].arrive < p[i - 1].end)
        {
            p[i].start = p[i - 1].end;
            p[i].end = p[i].start + p[i].time;
        }
        else
        {
            p[i].start = p[i].arrive;
            p[i].end = p[i].start + p[i].time;
        }

        p[i].rate = (float)(p[i].end - p[i].arrive) / p[i].time;
    }
	printResult();
}

void RR(Process p[], int n)
{
    queue<Process> q;
    Process temp;
    Process b[PROCESS_NUM + 1];

    for (int i = 0; i < n; i++)
    {
        b[i] = p[i];
    }

    int time_now = 0;
    q.push(p[0]);
    while (!q.empty())
    {
        time_now++;
        temp = q.front();
        q.pop();
        temp.time--;

        for (int i = 1; i < n; i++)
        {
            if (p[i].arrive == time_now)
            {
                q.push(p[i]);
            }
        }
        if (temp.time != 0)
        {
            q.push(temp);
        }
        else
        {
            temp.end = time_now;
            for (int i = 0; i < n; i++)
            {
                if (temp.name == p[i].name)
                {
                    p[i] = temp;
                    p[i].rate = (float)(p[i].end - p[i].arrive) / b[i].time;
                }
            }
        }
    }
    printResult();

}

void SPN(Process p[], int n)
{

    int now = 0; 
    int min = 100;
    int time_now = p[0].arrive;

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            if (p[k].arrive <= time_now && p[k].time != 0) 
            {
                p[k].activated = true;
            }
        }

        for (int l = 0; l < n; l++)
        {
            if (p[l].time < min && p[l].activated == true)
            {
                min = p[l].time;
                now = l;
            }
        }

        p[now].start = time_now;
        p[now].end = p[now].start + p[now].time;
        time_now = p[now].end;
        p[now].rate = (float)(p[now].end - p[now].arrive) / p[now].time;
        p[now].activated = false;
        p[now].time = 0;
        min = 100;
    }

    printResult();

}

void SRT(Process p[], int n)
{
    int now = 0;
    int min = 100;
    int time_now = p[0].arrive;

    for (int i = 0; i < n; i++)
        p[i].rest = p[i].time;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0;; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (p[k].arrive <= time_now && p[k].time != 0)
                {
                    p[k].activated = true;
                }
            }

            for (int l = 0; l < n; l++) 
            {
                if (p[l].rest < min && p[l].activated == true)
                {
                    min = p[l].rest;
                    now = l;
                }
            }
            p[now].start = time_now;
            int m = 0;
            for (m = 0; m < n; m++)
            {
                if (m != now && p[m].arrive < time_now + p[now].rest && p[m].time != 0 && p[m].activated == false)
                {
                    time_now = p[m].arrive;
                    p[now].rest = p[now].start + p[now].rest - time_now;
                    if (p[m].rest < p[now].rest)
                    {
                        now = m;
                        break;
                    }
                }
            }
            if (m == n)
            {
                p[now].end = time_now + p[now].rest;
                time_now = p[now].end;
                p[now].rate = (float)(p[now].end - p[now].arrive) / p[now].time;
                p[now].activated = false;
                p[now].time = 0;
                break;
            }
        }
        min = 100;
    }
    printResult();

}

void HRRN(Process p[], int n) 
{

    int now = 0;               
    int min = 1;               
    int time_now = p[0].arrive; 

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++) 
        {
            if (p[k].arrive <= time_now && p[k].time != 0)
            {
                p[k].activated = true;
            }
        }

        for (int l = 0; l < n; l++) 
        {
        
            if (p[l].activated == true && p[l].time != 0)
            {
                p[l].rate = (float)(time_now + p[l].time - p[l].arrive) / p[l].time;
            
                if (min < p[l].rate)
                {
                    min = p[l].rate;
                    now = l;
                }
            }
        }
       

        p[now].start = time_now;
        p[now].end = p[now].start + p[now].time;
        time_now = p[now].end;
        p[now].time = 0;
        min = 1;
    }

    printResult();
}


int main()
{
    FCFS(processes, PROCESS_NUM);
    resetProcesses();
    RR(processes, PROCESS_NUM);
    resetProcesses();
    SPN(processes, PROCESS_NUM);
    resetProcesses();
    SRT(processes, PROCESS_NUM);
    resetProcesses();
    HRRN(processes, PROCESS_NUM);
    return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>
int const MAX = 100005;
int prime[MAX];
int ma, cnt, l, r;
 
void get_prime()  
{
    bool get[MAX];
    memset(get, true, sizeof(get));
    get[0] = get[1] = false;
    for(int i = 2; i <= sqrt(MAX); i++)
        if (get[i])
            for(int j = i * i; j <= MAX; j += i)
                  get[j] = false;
    for(int i = 2; i <= MAX; i++)
        if(get[i])
            prime[++cnt] = i;
}
 
 
void search(int from, int tot, int num, int left, int right)
{
    ma = tot > ma ? tot : ma;  
    if((left == right) && (left > num))
        search(from, tot * 2, num * left, 1, 1);
    for(int i = from; i <= cnt; i++)    
    {
        if (prime[i] >right)   
            return;
        else
        {
            int j = prime[i], x = left - 1, y = right, n = num, t = tot, m = 1;
            while(true)
            {
                m ++;   
                t += tot;
                x /= j;
                y /= j;
                if (x == y)
                    break;
                n *= j;
                search(i + 1, t, n, x + 1, y);
            }
            if (tot < (ma / (1 << m)))
                return;
        }
   }
}
 
int main()
{
    cnt = 0;
    get_prime();
    while(scanf("%d %d", &l, &r) != EOF)
    {
        if((l == 1) && (r == 1))
            ma = 1;
        else
        {
            ma = 2;
            search(1, 1, 1, l, r);
        }
        printf("%d\n", ma);
    }
}

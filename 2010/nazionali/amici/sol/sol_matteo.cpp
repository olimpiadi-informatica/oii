#include<cstdio>
#include<cstdlib>
#include<vector>

using namespace std;
#define MAX_N 1000010

int n,k,t;
int m[MAX_N];
int friends[MAX_N];
bool is_friend[MAX_N];
bool is_friend_final[MAX_N];
bool evaluated[MAX_N];

int main()
{
    int i;
    scanf("%d %d %d", &n,&k,&t);
    for(i=1;i<=n;i++)
    {
        scanf("%d",m+i);
    }
    for(i=1;i<=k;i++)
    {
        scanf("%d",friends+i);
        is_friend[friends[i]]=true;
    }
    //ricerca cicli
    for(i=1;i<=n;i++)
    {
        if(!evaluated[i])
        {
            //costruzione ciclo
            vector<int> ciclo;
            int currelem=i;
            do
            {
                evaluated[currelem]=true;
                ciclo.push_back(currelem);
                currelem=m[currelem];
            }
            while(currelem!=i);
            //ricerca amici nel ciclo
            for(int j=0;j<ciclo.size();j++)
            {
                if(is_friend[ciclo[j]])
                    is_friend_final[ciclo[((j+t)%ciclo.size())]]=true;
            }
        }
    }
    /*
    for(int i=1;i<=n;i++)
        printf("%d ",is_friend_final[i]);
    printf("\n");
    */
    //ricerca del primo elemento
    i=n;
    while(!is_friend_final[i] && i>=1)
        i--;
    while(is_friend_final[i] && i>=1)
        i--;
    printf("%d\n", ++i);
}

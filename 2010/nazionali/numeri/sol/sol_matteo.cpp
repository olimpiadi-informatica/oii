#include<cstdio>
#include<cstdlib>

using namespace std;
#define MAX_N 1000010

long long n,m;
long long n_nonzero;
long long nonzero[MAX_N];
long long posnonzero[MAX_N];
long long sequences;

long long zeroLeft(long long l)
{
    if(l==0)
        return posnonzero[l];
    else
        return posnonzero[l]-posnonzero[l-1]-1;
}

long long zeroRight(long long r)
{
    if(r==n_nonzero-1)
        return n-1-posnonzero[r];
    else
        return posnonzero[r+1]-posnonzero[r]-1;
}

int main()
{
    scanf("%lld %lld",&m,&n);
    if(m==0)
    {
        long long consec_zero=0;
        for(long long i=0;i<n;i++)
        {
            long long k;
            scanf("%lld",&k);
            if(k==0)
                consec_zero++;
            else
            {
                sequences+=((consec_zero)*(consec_zero+1))/2;
                consec_zero=0;
            }
        }
        sequences+=((consec_zero)*(consec_zero+1))/2;        
    }
    else
    {
        for(long long i=0;i<n;i++)
        {   
            long long k;
            scanf("%lld",&k);
            if(k!=0)
            {
                nonzero[n_nonzero]=k;
                posnonzero[n_nonzero]=i;
                n_nonzero++;
            }
        }
        long long start=0,end=0;
        long long total=nonzero[0];

        while(end<n_nonzero)
        {
            if(total<m)
            {
                end++;
                if(end<n_nonzero) total+=nonzero[end];
            }
            else
            {
                if (total==m)
                    sequences+=(zeroLeft(start)+1)*(zeroRight(end)+1);
                total-=nonzero[start];
                start++;
            }
        }
    }
    printf("%lld\n",sequences);
}

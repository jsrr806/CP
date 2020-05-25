/*
Solution for
https://www.hackerearth.com/practice/algorithms/dynamic-programming/bit-masking/practice-problems/algorithm/the-ghost-type/description/
https://www.hackerearth.com/practice/algorithms/dynamic-programming/bit-masking/tutorial/
*/



#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    ll size=pow(2,n);
    ll dp[size]={0};
    dp[0]=1;
    for(ll mask=0;mask<size;mask++)
    {
        //cout<<"m";
        vector<int>inSet;
        for(int i=0;i<n;i++)
        {
            if(mask&(1<<i))inSet.push_back(i+1);
        }
        for(int i=0;i<n;i++)
        {
            bool flag=true;
            if(!(mask&(1<<i)))
            {
                for(int j=0;j<inSet.size();j++)
                {
                    int num=i+1;
                    if((inSet[j]&num)==num)
                    {
                        flag=false;
                        break;
                    }
                }
                if(flag)
                {
                    //cout<<mask<<" "<<(mask|(1<<i))<<"\n";
                    dp[mask|(1<<i)]+=dp[mask];
                }
            }
            
        }
    }
    cout<<dp[size-1];
    return 0;
}

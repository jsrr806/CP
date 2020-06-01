/*
Count Inversion Using Fenwick Tree
Solution of https://www.codechef.com/problems/CHEFSQUD
Topics Involved: binary-search, coordinate-compression, fenwick-tree, inversion-count, segment-tree, two-pointers
*/


#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void compress(vector<ll>&A)
{
    vector<ll>temp=A;
    sort(temp.begin(),temp.end());
    map<ll,ll>mp;
    ll idx=-1;
    for(int i=0;i<temp.size();i++)
    {
        if(mp.find(temp[i])==mp.end())
        {
            idx++;
        }
        mp[temp[i]]=idx;
    }
    for(int i=0;i<temp.size();i++)
    {
        A[i]=mp[A[i]];
    }
}
//methods for BIT
struct FenwickTree {
    vector<ll> bit;
    ll n;

    FenwickTree(ll n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<ll> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    ll sum(ll r) {
        ll ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(ll idx, ll delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
ll getInv(FenwickTree bit,int n,vector<ll>&A,ll limit)
{
    ll i=n-1;
    ll leftInv=0;
    ll res=0;
    if(limit==0)return 0;
    for(ll j=n-1;j>=0;j--)
    {
        i=min(i,j);
        while(i>=0)
        {
            res+=bit.sum(A[i]-1);
            if(res>=limit)
            {
                res-=bit.sum(A[i]-1);
                break;
            }
            bit.add(A[i],1);
            i--;
        }
        
        leftInv+=j-i;
        
        res-=j-i-bit.sum(A[j]);
        bit.add(A[j],-1);
        
    }
    return leftInv;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--)
    {
        ll n;
        cin>>n;
        vector<ll>A(n);
        for(int i=0;i<n;i++)
        {
            cin>>A[i];
        }
        compress(A);
        FenwickTree bit(n);
        ll l=0,r=(n*(n-1))/2;
        ll ans=0;
        //binary search
        ll cnt=((n*(n+1))/2+1)/2;
        while(l<=r)
        {
            ll mid=(l+r)/2;
            //getInv
            ll leftInv=getInv(bit,n,A,mid);
            if(leftInv<cnt)
            {
                l=mid+1;
                ans=mid;
            }
            else
            {
                r=mid-1;
            }
        }
        cout<<ans<<"\n";
    }
	return 0;
}

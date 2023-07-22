#include<bits/stdc++.h>
using namespace std;

//=======================================================================
// #define int long long
#define vi vector<int>
#define pii pair<int,int> 
#define all(x) x.begin(),x.end()
#define countbits(x) __builtin_popcount(x)
#define vpi vector<pair<int,int>>
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl

int mod = 1e9+7;

int max(int a,int b){return a>b ? a : b ;}

int min(int a,int b){return a<b ? a : b ;}

class SGTree
{
  vector<pair<int,int>> seg;

public:
  SGTree(int n)
  {
    seg.resize(4 * n + 1, make_pair(0,0));
  }

  pair<int,int> max(pair<int,int> p1,pair<int,int> p2){
      if(p1.first==p2.first && p1.first!=0){
          return {p1.first,p1.second+p2.second};
      }
      return p1.first>p2.first? p1 : p2 ;
  }

  pair<int,int> query(int idx, int low, int high, int l, int r)
  {
    // no overlap
    if (high < l || low > r)
    {
      return {0,1};
    }

    // complete overlap
    if (low >= l && high <= r)
    {
      return seg[idx];
    }

    // partial overlap
    int mid = low + ((high - low) / 2);
    pair<int,int> left = query(2 * idx + 1, low, mid, l, r);
    pair<int,int> right = query(2 * idx + 2, mid + 1, high, l, r);
    return max(left,right);
  }

  void update(int idx, int low, int high, int i, pair<int,int> val)
  {
    if (low == high)
    {
      seg[idx] = val;
      return;
    }

    int mid = low + ((high - low) / 2);
    if (i <= mid)
    {
      update(2 * idx + 1, low, mid, i, val);
    }
    else
    {
      update(2 * idx + 2, mid + 1, high, i, val);
    }

    seg[idx] = max(seg[2 * idx + 1],seg[2 * idx + 2]);
  }
};

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n=nums.size();
        vector<pair<int,int>> v;
        for(int i=0 ; i<n ; i++){
            v.push_back({nums[i],i});
        }

        SGTree seg(n);
        sort(v.begin(),v.end());

        vector<int> pos(n);
        for(int i=0 ; i<n ; i++){
          pos[v[i].second]=i;
        }

        for(int i=0 ; i<n  ;i++){
            auto it=lower_bound(v.begin(),v.end(),make_pair(nums[i],-1))-v.begin();
            
            pair<int,int> prev={1,1};
            if(it>0){
              prev=seg.query(0,0,n-1,0,it-1);
              prev.first++;
            }

            seg.update(0,0,n-1,pos[i],prev);
        }

        return seg.query(0,0,n-1,0,n-1).second;
    }
};

Solution s;

void solve(){
  int n;
  cin>>n;
  vector<int> a(n,0);
  for(int i=0 ; i<n ; i++){
    cin>>a[i];
  }
  cout<<s.findNumberOfLIS(a)<<endl;
}

int32_t main(){
  int t;
  cin>>t;
  while(t--){
    solve();
  }

  return 0;
}
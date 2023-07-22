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

//Segment Tree Class
class SGTree
{
  vector<int> seg;

public:
  SGTree(int n)
  {
    seg.resize(4 * n + 1, 0);
  }

  void build(int idx, int low, int high, vector<int> &arr)
  {
    if (low == high)
    {
      seg[idx] = arr[low];
      return;
    }

    int mid = low + ((high - low) / 2);
    build(2 * idx + 1, low, mid, arr);
    build(2 * idx + 2, mid + 1, high, arr);
    seg[idx] = max(seg[2 * idx + 1],seg[2 * idx + 2]);
  }

  int query(int idx, int low, int high, int l, int r)
  {

    // no overlap
    if (high < l || low > r)
    {
      return 0;
    }

    // complete overlap
    if (low >= l && high <= r)
    {
      return seg[idx];
    }

    // partial overlap
    int mid = low + ((high - low) / 2);
    int left = query(2 * idx + 1, low, mid, l, r);
    int right = query(2 * idx + 2, mid + 1, high, l, r);
    return max(left,right);
  }

  void update(int idx, int low, int high, int i, int val)
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

//Longest Increasing Subsequence Class
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        vector<pair<int,int>> sorted;
        for(int i=0 ; i<n ; i++){
            sorted.push_back({nums[i],i});
        }

        SGTree seg(n);
        sort(sorted.begin(),sorted.end());
        int ans=1;
        for(int i=0 ; i<n  ;i++){
            auto it=lower_bound(sorted.begin(),sorted.end(),make_pair(nums[i],-1))-sorted.begin();
            int prev=0;
            if(it!=0){
              prev=seg.query(0,0,n-1,0,it-1);
            }
            seg.update(0,0,n-1,it,prev+1);
            ans=max(ans,prev+1);
        }
        return ans;
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
  cout<<s.lengthOfLIS(a)<<endl;
}

int32_t main(){
  int t;
  cin>>t;
  while(t--){
    solve();
  }

  return 0;
}
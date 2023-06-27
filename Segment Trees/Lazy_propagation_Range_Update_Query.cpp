#include<bits/stdc++.h>
using namespace std;

//=======================================================================
#define ll long long
#define vi vector<ll>
#define vpi vector<pair<ll,ll>>
#define mod 1e9+7

class SGTree_lazy{
  vector<int> seg;
  vector<int> lazy;
  public : 
  SGTree_lazy(int n){
    seg.resize(4*n+1,0);
    lazy.resize(4*n+1,0);
  }

  void build(int idx,int low,int high,vector<int> &arr){
    if(low==high){
      seg[idx]=arr[low];
      return;
    }

    int mid=low+((high-low)/2);
    build(2*idx+1,low,mid,arr);
    build(2*idx+2,mid+1,high,arr);
    seg[idx]=(seg[2*idx+1]+seg[2*idx+2]);
  }

  void update(int idx,int low,int high,int l,int r,int val){
    //lazy propagation
    if(lazy[idx]!=0){
      seg[idx]+=(high-low+1)*lazy[idx];
      if(low!=high){
        lazy[2*idx+1]=lazy[idx];
        lazy[2*idx+2]=lazy[idx];
      }
      lazy[idx]=0;
    }

    //no overlap
    if(l>high || r<low){
      return;
    }


    //complete overlap
    if(low>=l && high<=r){
      seg[idx]+=(high-low+1)*val;
      if(low!=high){
        lazy[2*idx+1]=val;
        lazy[2*idx+2]=val;
      }
      return ;
    }

    //partial overlap
    int mid=low+((high-low)/2);
    update(2*idx+1,low,mid,l,r,val);
    update(2*idx+2,mid+1,high,l,r,val);
    seg[idx]=(seg[2*idx+1]+seg[2*idx+2]);
  }

  int query(int idx,int low,int high , int l,int r){
    //lazy propagation
    if(lazy[idx]!=0){
      seg[idx]+=(high-low+1)*lazy[idx];
      if(low!=high){
        lazy[2*idx+1]=lazy[idx];
        lazy[2*idx+2]=lazy[idx];
      }
      lazy[idx]=0;
    }

    // no overlap
    if(high<l || low>r){
      return 0;
    }

    //complete overlap
    if(low>=l && high<=r){
      return seg[idx];
    }

    //partial overlap
    int mid=low+((high-low)/2);
    int left=query(2*idx+1,low,mid,l,r);
    int right=query(2*idx+2,mid+1,high,l,r);
    return (left+right);
  }
};

void solve(){
  ll n;
  cin>>n;
  vector<int> arr(n,0);
  for(int i=0  ;i<n ; i++){
    cin>>arr[i];
  }
  SGTree_lazy sl(n);
  sl.build(0,0,n-1,arr);
  int m;
  cin>>m;
  while(m--){
    int type;
    cin>>type;
    if(type==1){
      int l,r,val;
      cin>>l>>r>>val;
      sl.update(0,0,n-1,l,r,val);
    }
    else{
      int l,r;
      cin>>l>>r;
      cout<<sl.query(0,0,n-1,l,r)<<endl;
    }
  }
}

int main(){
  int t;
  cin>>t;
  while(t--){
    solve();
  }

  return 0;
}

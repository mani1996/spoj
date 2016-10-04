// Problem : MKTHNUM from SPOJ
// Implementation inspired by Anudeep's code
// https://blog.anudeep2011.com/persistent-segment-trees-explained-with-spoj-problems/

#include <bits/stdc++.h>
using namespace std;

struct node{
	node *left,*right;
	int count;

	node(int c,node* l,node* r):count(c),left(l),right(r){}
	node(){}

	node* insert(int l,int r,int idx);
};

node* null = new node;

node* node::insert(int l,int r,int idx){
	if(l<=idx && idx<=r){
		if(l==r)return new node((this->count)+1, null, null);

		int m = (l+r)/2;
		return new node((this->count)+1,this->left->insert(l,m,idx),this->right->insert(m+1,r,idx));
	}
	else{
		return this;
	}
}

int query(node* Old, node* New, int l, int r, int val){
	if(l == r)return l;

	int m = (l+r)/2;
	int lCount = New->left->count - Old->left->count;

	if(lCount>=val){
		return query(Old->left, New->left, l, m, val);
	}
	else{
		return query(Old->right, New->right, m+1, r, val-lCount);
	}
}

int main(){
	int n,m,l,r,i,k;
	cin>>n>>m;

	int a[n],b[n];
	map<int,int> ma;

	for(i=0;i<n;i++){
		cin>>a[i];
		b[i] = a[i];
	}

	sort(b,b+n);
	for(i=0;i<n;i++)ma[b[i]] = i;
	for(i=0;i<n;i++)a[i] = ma[a[i]];

	null->left = null->right = null;
	null->count = 0;

	node* root[n];

	for(i=0;i<n;i++){
		root[i] = ((i==0)?null:root[i-1])->insert(0,n-1,a[i]);
	}

	while(m--){
		cin>>l>>r>>k;
		l--,r--;
		cout<<b[query(((l==0)?null:root[l-1]),root[r],0,n-1,k)]<<"\n";
	}

	return 0;
}
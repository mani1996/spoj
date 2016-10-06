// Problem : QTREE from SPOJ

#include <bits/stdc++.h>
using namespace std;

class HLD{
	int n;
	int root;
	int chainCount;
	int chainHead[10001];
	int nodePos[10001],nodeChain[10001],nodeLevel[10001],distanceToParent[10001],parent[10001];
	int subtreeSize[10001];

	vector<int> chainArray[10001];
	vector<int> chainTree[10001];
	vector<int> parDP[10001];
	vector<int> adj[10001];

	void findRoot(){
		int i;
		for(i=0;i<n;i++){
			if(parent[i] == -1){
				root = i;
				break;
			}
		}
	}

	void computeSubtreeSizes(int src){
		int i;
		subtreeSize[src] = 1;

		for(i=0;i<adj[src].size();i++){
			computeSubtreeSizes(adj[src][i]);
			subtreeSize[src]+=subtreeSize[adj[src][i]];
		}
	}

	void createHLD(int node, bool special){
		if(!special){
			chainCount++;
			chainHead[chainCount] = node;
			nodePos[node] = 0;
			nodeChain[node] = chainCount;
		}
		else{
			nodePos[node] = nodePos[parent[node]] + 1;
			nodeChain[node] = nodeChain[parent[node]];
		}

		if(node == root){
			nodeLevel[node] = 0;
		}
		else{
			nodeLevel[node] = nodeLevel[parent[node]] + 1;
		}

		int i,ssize = -1, idx = -1;
		for(i=0; i<adj[node].size(); i++){
			if(subtreeSize[adj[node][i]]>ssize){
				ssize = subtreeSize[adj[node][i]];
				idx = i;
			}
		}

		for(i=0; i<adj[node].size(); i++){
			if(i == idx){
				chainArray[nodeChain[node]].push_back(distanceToParent[adj[node][i]]);
				createHLD(adj[node][i],true);
			}
			else{
				createHLD(adj[node][i],false);
			}
		}
	}

	void treeInit(int arrID, int node, int beg, int end){
		if(beg == end){
			chainTree[arrID][node] = chainArray[arrID][beg];
		}
		else{
			treeInit(arrID, 2*node+1, beg, (beg+end)/2);
			treeInit(arrID, 2*node+2, (beg+end)/2+1, end);
			chainTree[arrID][node] = max(chainTree[arrID][2*node+1], chainTree[arrID][2*node+2]);
		}
	}

	void treeUpdate(int arrID, int node, int beg, int end, int idx, int val){
		if(end < idx || beg > idx || beg > end)return ;

		if(beg == end){
			chainTree[arrID][node] = val;
		}
		else{
			treeUpdate(arrID, 2*node+1, beg, (beg+end)/2, idx,val);
			treeUpdate(arrID, 2*node+2, (beg+end)/2+1, end, idx, val);
			chainTree[arrID][node] = max(chainTree[arrID][2*node+1], chainTree[arrID][2*node+2]);
		}
	}

	int treeQuery(int arrID, int node, int beg, int end, int l, int r){
		if(end < l || beg > r || beg > end)return -1;

		if(beg >= l && end <= r){
			return chainTree[arrID][node];
		}
		else{
			int v1 = treeQuery(arrID, 2*node+1, beg, (beg+end)/2, l, r);
			int v2 = treeQuery(arrID, 2*node+2, (beg+end)/2+1, end, l, r);
			return max(v1,v2);
		}
	}

	void LCAInit(){
		int i,j;

		for(j=0;j<=20;j++){
			for(i=0;i<n;i++){
				if((1<<j) <= nodeLevel[i]){
					if(j==0){
						parDP[i].push_back(parent[i]);
					}
					else{
						parDP[i].push_back(parDP[parDP[i][j-1]][j-1]);
					}
				}
			}
		}

		return ;
	}

	int findLCA(int node1, int node2){
		int j;

		if(nodeLevel[node1] < nodeLevel[node2]){
			node1 = node1 + node2 - (node2 = node1);
		}

		for(j=parDP[node1].size()-1; j>=0; j--){
			if(j<parDP[node1].size() && nodeLevel[parDP[node1][j]] > nodeLevel[node2]){
				node1 = parDP[node1][j];
			}
		}

		if(nodeLevel[node1] == nodeLevel[node2] + 1)node1 = parent[node1];
		assert(nodeLevel[node1] == nodeLevel[node2]);
		if(node1 == node2)return node1;

		for(j=parDP[node1].size()-1; j>=0; j--){
			if(j<parDP[node1].size() && (parDP[node1][j] != parDP[node2][j])){
				node1 = parDP[node1][j];
				node2 = parDP[node2][j];
			}
		}

		node1 = parent[node1];
		node2 = parent[node2];
		assert(node1 == node2);
		return node1;
	}

public:
	HLD(int N):n(N),chainCount(-1){
		fill(parent, parent+n, -1);
	}

	void addEdge(int src, int dest, int weight){
		adj[src].push_back(dest);
		parent[dest] = src;
		distanceToParent[dest] = weight;
	}

	void HLDInit(){
		findRoot();
		computeSubtreeSizes(root);

		createHLD(root,false);

		int i,j;
		for(i=0; i<=chainCount; i++){
			if(!chainArray[i].empty()){
				for(j=0;j<2*chainArray[i].size()-1;j++)chainTree[i].push_back(0);
				treeInit(i,0,0,chainArray[i].size()-1);
			}
		}

		LCAInit();
	}

	void update(int node, int val){
		if(nodePos[node] == 0){
			distanceToParent[node] = val; // Link from non-special child to parent
		}
		else{
			treeUpdate(nodeChain[node],0,0,chainArray[nodeChain[node]].size()-1,nodePos[node]-1,val);
		}	
	}

	void query(int node1, int node2){
		int lca = findLCA(node1,node2);
		int res = 0;
		int diff;

		while(true){
			if(nodePos[node1] > 0){
				if(lca == node1)break;
				if(nodeChain[lca] != nodeChain[node1]){
					// include segment tree till chain Head
					if(!chainArray[nodeChain[node1]].empty())res = max(res,treeQuery(nodeChain[node1],
						0,0,chainArray[nodeChain[node1]].size()-1,0,nodePos[node1]-1));	
					node1 = chainHead[nodeChain[node1]];
				}
				else{
					if(!chainArray[nodeChain[node1]].empty())res = max(res,treeQuery(nodeChain[node1],
						0,0,chainArray[nodeChain[node1]].size()-1,nodePos[lca],nodePos[node1]-1));	
					node1 = lca;
				}
			}
			else{
				if(lca == node1) break;
				res = max(res,distanceToParent[node1]);
				node1 = parent[node1];
			}
		}


		while(true){
			if(nodePos[node2] > 0){
				if(lca == node2)break;
				if(nodeChain[lca] != nodeChain[node2]){
					// include segment tree till chain Head
					if(!chainArray[nodeChain[node2]].empty())res = max(res,treeQuery(nodeChain[node2],
						0,0,chainArray[nodeChain[node2]].size()-1,0,nodePos[node2]-1));	
					node2 = chainHead[nodeChain[node2]];
				}
				else{
					if(!chainArray[nodeChain[node2]].empty())res = max(res,treeQuery(nodeChain[node2],
						0,0,chainArray[nodeChain[node2]].size()-1,nodePos[lca],nodePos[node2]-1));	
					node2 = lca;
				}
			}
			else{
				if(lca == node2) break;
				res = max(res,distanceToParent[node2]);
				node2 = parent[node2];
			}
		}

		cout<<res<<"\n";
		return ;
	}

};

void solve(){
	int n,i,a,b,c,p1,p2;
	cin>>n;

	HLD hld(n);
	int qu[n-1];

	for(i=0;i<n-1;i++){
		cin>>a>>b>>c;
		qu[i] = b-1;
		hld.addEdge(a-1,b-1,c);
	}

	hld.HLDInit();

	string inst;
	cin>>inst;

	while(inst!="DONE"){
		cin>>p1>>p2;
		if(inst=="QUERY"){
			hld.query(p1-1,p2-1);
		}
		else{
			hld.update(qu[p1-1],p2);
		}
		cin>>inst;
	}
	return ;
}

int main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
// Problem : MICEMAZE from SPOJ

#include <bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define ll long long

class Heap{
	// pos, ele are inverse of each other
	int *ele,*pos,*key;
	int size;

	void swap(int idx1, int idx2){
		ele[idx1] = ele[idx1] + ele[idx2] - (ele[idx2] = ele[idx1]);
		pos[ele[idx1]] = idx1;
		pos[ele[idx2]] = idx2;
	}

	void siftUp(int idx){
		while(idx>0 && key[ele[idx]]<key[ele[(idx-1)/2]]){
			swap(idx,(idx-1)/2);
			idx = (idx-1)/2;
		}
	}

	void siftDown(int idx){
		int v1,v2;
		while(idx < size){
			v1 = ((2*idx+1 < size)?key[ele[2*idx+1]]:INF);
			v2 = ((2*idx+2 < size)?key[ele[2*idx+2]]:INF);

			if(min(v1,v2) < key[ele[idx]]){
				if(v1 < v2){
					swap(idx,2*idx+1);
					idx = 2*idx+1;
				}
				else{
					swap(idx,2*idx+2);
					idx = 2*idx+2;
				}
			}
			else{
				break;
			}
		}
	}

public:
	Heap(int N){
		ele = new int[N];
		pos = new int[N];
		key = new int[N];
		size = 0;

		int i;
		for(i=0;i<N;i++)ele[i] = pos[i] = key[i] = INF;

	}
	
	int insert(int city,int key){
		pos[city] = size;
		ele[size] = city;
		this->key[city] = key;
		size++;
		siftUp(size-1);
	}

	int deleteMin(){
		int city = ele[0];
		pos[city] = key[city] = INF;
		ele[0] = ele[size-1];
		pos[ele[0]] = 0;
		size--;
		siftDown(0);
		return city;
	}

	void decreaseKey(int city, int val){
		key[city] = val;
		siftUp(pos[city]);
	}	

	bool empty(){
		return size==0;
	}

	bool contains(int city){
		return pos[city]!=INF;
	}

	void printHeap(){
		int i;
		cout<<"Heap: ";
		for(i=0;i<size;i++){
			cout<<"("<<ele[i]<<","<<key[ele[i]]<<") - ";
		}
		cout<<"\n";
	}

};



int main(){
	int n,s,m,i,t,wt,cur,a,b;
	cin>>n>>s>>t>>m;
	s--;

	vector<int> adj[n];
	vector<int> wei[n];

	while(m--){
		cin>>a>>b>>wt;
		adj[b-1].push_back(a-1);
		wei[b-1].push_back(wt);
	}

	ll dist[n];
	for(i=0;i<n;i++)dist[i] = INF;

	Heap heap(n);
	heap.insert(s,0);
	dist[s] = 0;
	ll ans = 0;

	while(!heap.empty()){
		cur = heap.deleteMin();
		if(dist[cur]<=t)ans++;

		for(i=0;i<adj[cur].size();i++){
			if(dist[cur] + wei[cur][i] < dist[adj[cur][i]]){
				dist[adj[cur][i]] = dist[cur] + wei[cur][i];

				if(heap.contains(adj[cur][i])){
					heap.decreaseKey(adj[cur][i], dist[adj[cur][i]]);
				}
				else{
					heap.insert(adj[cur][i], dist[adj[cur][i]]);
				}
			}
		}

	}

	cout<<ans<<"\n";
	return 0;
}
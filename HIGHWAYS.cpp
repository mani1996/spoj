// Problem : HIGHWAYS from SPOJ

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 1000000000

class Heap{
	// pos, ele are inverse of each other
	int *ele,*pos,*key;
	int size;

	void swap(int idx1, int idx2){
		ele[idx1] = ele[idx1] + ele[idx2] - (ele[idx2] = ele[idx1]);
		key[idx1] = key[idx1] + key[idx2] - (key[idx2] = key[idx1]);
		pos[ele[idx1]] = idx1;
		pos[ele[idx2]] = idx2;
	}

	void siftUp(int idx){
		while(idx>0 && key[idx]<key[idx/2]){
			swap(idx,idx/2);
			idx/=2;
		}
	}

	void siftDown(int idx){
		int v1,v2;
		while(idx < size){
			v1 = ((2*idx+1 < size)?key[2*idx+1]:INF);
			v2 = ((2*idx+2 < size)?key[2*idx+2]:INF);

			if(min(v1,v2) < key[idx]){
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
		for(i=0;i<N;i++)ele[i] = pos[i] = key[i] = -1;

	}

	int insert(int city,int key){
		ele[size] = city;
		this->key[size] = key;
		pos[city] = size;
		size++;
		siftUp(size-1);
	}

	int deleteMin(){
		int temp = ele[0];
		pos[ele[0]] = key[ele[0]] = -1;
		ele[0] = ele[size-1];
		pos[ele[0]] = 0;
		key[0] = key[size-1];
		size--;
		siftDown(0);
		return temp;
	}

	int decreaseKey(int city, int val){
		key[pos[city]] = val;
		siftUp(pos[city]);
	}	

	bool empty(){
		return size==0;
	}

	bool contains(int city){
		return pos[city]!=-1;
	}

	void printHeap(){
		int i;
		cout<<"Heap: ";
		for(i=0;i<size;i++){
			cout<<"("<<ele[i]<<","<<key[i]<<","<<pos[ele[i]]<<") - ";
		}
		cout<<"\n";
	}

};


void solve(){
	int n,m,src,dest,i,a,b,wt,cur,end;
	cin>>n>>m>>src>>dest;
	vector<int> adj[n];
	vector<int> weights[n];

	while(m--){
		cin>>a>>b>>wt;
		adj[a-1].push_back(b-1);
		weights[a-1].push_back(wt);
		adj[b-1].push_back(a-1);
		weights[b-1].push_back(wt);
	}

	int dist[n];
	for(i=0;i<n;i++)dist[i] = INF;

	dist[src-1] = 0;
	Heap heap(n);	
	heap.insert(src-1,0);

	while(!heap.empty()){
		cur = heap.deleteMin();
		for(i=0;i<adj[cur].size();i++){
			end = adj[cur][i];
			wt = weights[cur][i];
			if(dist[cur] + wt < dist[end]){
				dist[end] = dist[cur] + wt;

				if(heap.contains(end)){
					heap.decreaseKey(end,dist[end]);
				}
				else{
					heap.insert(end,dist[end]);
				}
			}
		}
	}

	if(dist[dest-1] == INF){
		cout<<"NONE\n";
	}		
	else{
		cout<<dist[dest-1]<<"\n";
	}

	return ;
}

int main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
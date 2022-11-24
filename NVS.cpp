#include<iostream>
#include<map>
#include<list>
#include<climits>
#include<set>
#include<queue>
#include<unordered_set>
#include <windows.h>
#include<conio.h>
#include<algorithm>
using namespace std;
class neighbour
{
public:
	string name;
	float distance;
	int price;
	int time;

	neighbour(string name,float distance,int price,int time)
	{
		this->name=name;
		this->distance=distance;
		this->price=price;
		this->time=time;
	}
};
class graph
{
	map<string,list<neighbour>> neighbourMap;
	//bool isDirected;
	//we are keeping the graph undirected
	string type;

public:
	graph(string type="metro") //metro or any other
	{
		//type is metro by default
		this->type=type;
	}
	void addEdge(string u,string v,int price, float distance,int time) //price in Rs,distance in km,time in minutes
	{
		neighbour neighbourOfU(v,distance,price,time);
		neighbour neighbourOfV(u,distance,price,time);

		neighbourMap[u].push_back(neighbourOfU); //adding v to the neighbour list of u
		neighbourMap[v].push_back(neighbourOfV); //adding u to the neighbours list of v
	}
	void print()
	{
		for(pair<string,list<neighbour>> vertex:neighbourMap) //for each loop
		{
			string city_name=vertex.first;
			for(neighbour N:vertex.second)
			{
				cout<<city_name<<" : ";
				cout<<N.name<<" "<<N.distance<<"kms Rs."<<N.price<<" "<<N.time<<"minutes\n";
			}
			cout<<endl;
		}
	}
	void printPath(map<string,string> parent,string dest)
	{
		
		//dest is source
		if(parent[dest]=="")
		{
			cout<<dest;
			return;
		}

		printPath(parent,parent[dest]);
		cout<<"->"<<dest;
	}
	void dijkstra(string src,string dest)
	{
		map<string,float> distMap;
		set<pair<float,string>> minHeap; //pairs are sorted according to the distance
		unordered_set<string> explored;

		for(pair<string,list<neighbour>> vertex:neighbourMap)
		{
			string stationName=vertex.first;
			distMap[stationName]=INT_MAX;
		}

		distMap[src]=0; //distance from src station to src station is zero
		
		for(pair<string,float> vertex:distMap)
		{
			string stationName=vertex.first;
			float distance=vertex.second;
			minHeap.insert({distance,stationName});
		}
		int size=distMap.size();
		map<string,string> parent;
		parent[src]=""; //parent of the source vertex
		while(!minHeap.empty())
		{
			pair<float,string> minVertex=*minHeap.begin();
			minHeap.erase(minHeap.begin());
			string minStop=minVertex.second;
			float minDistance=minVertex.first;
			list<neighbour> neighbourList=neighbourMap[minStop];
			for(neighbour N:neighbourList)
			{
				string neighbourName=N.name;
				float edgeWeight=N.distance;
				if(explored.find(neighbourName)==explored.end()&&(distMap[neighbourName]>edgeWeight+minDistance))
				{
					parent[neighbourName]=minStop;
					auto it=minHeap.find({distMap[neighbourName],neighbourName});
					minHeap.erase(it);
					minHeap.insert({edgeWeight+minDistance,neighbourName});
					distMap[neighbourName]=edgeWeight+minDistance;
				}
			}
			explored.insert(minStop);
		}
		float minD=distMap[dest];
		int price=minD*5;
		int time=minD*3;
		cout<<"Route and other details are:";
		cout<<endl;
		cout<<src<<" to "<<dest<<":";
		cout<<minD<<"kms Rs"<<price<<" "<<time<<"minutes";
		cout<<endl;
		printPath(parent,dest);
		cout<<endl;
	}
	void bfs(string s) {

			// cout << "bfs(" << s << ") : ";

			unordered_set<string> visited; // to keep track of visited vertices
			queue<string> q; // to keep track of visited & un-explored vertices

			// mark 's' as visited
			visited.insert(s);
			q.push(s);

			while(!q.empty()) {
				string front = q.front();
				q.pop();

				// explore 'front'

				cout << front << " ";
				list<neighbour> neighbourList = neighbourMap[front];
				for(neighbour n : neighbourList) {
					if(visited.find(n.name) == visited.end()) {
						visited.insert(n.name);
						q.push(n.name);
					}
				}

			}

			cout << endl;

		}
};
int main()
{
	graph g("metro");
	//0->Def Col, 1->Mayur Vihar,2->CP,3->Noida,4->Ghaziabad
	vector<string> names={"CP","Noida","Mayur Vihar","Ghaziabad","Def Col"};
	g.addEdge("Def Col","Mayur Vihar",50,10,30);
	g.addEdge("Def Col","CP",25,5,15);
	g.addEdge("Mayur Vihar","Noida",5,1,3);
	g.addEdge("CP","Noida",45,9,18);
	g.addEdge("CP","Ghaziabad",10,2,6);
	g.addEdge("Noida","Ghaziabad",40,8,24);
	// g.print();
	system("Color 0A");
	cout<<"Welcome!!!\n";
	cout<<"Stations are: ";
	g.bfs("CP");
	getch();
	string src; //soruce station
	system("Color 09");
	cout<<"Please enter your source station: ";
	getline(cin,src);
	while(find(names.begin(),names.end(),src)==names.end())
	{
		cout<<"Wrong Input!!\n";
		cout<<"Please enter your source station: ";
		getline(cin,src);
	}
	string dest; //destination station
	system("Color 0C");
	cout<<"Please enter your destination station: ";
	getline(cin,dest);
	while(find(names.begin(),names.end(),dest)==names.end())
	{
		cout<<"Wrong Input!!\n";
		cout<<"Please enter your destination station: ";
		getline(cin,dest);
	}
	cout<<endl;
	g.dijkstra(src,dest);
	return 0;
}
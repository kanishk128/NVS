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
#include<stdlib.h>
using namespace std;
class neighbour
{
public:
	string name;
	float distance;
	int price;
	int time;

	neighbour(string name,float distance)
	{
		this->name=name;
		this->distance=distance;
		this->price=distance*3;
		this->time=distance;
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
	void addEdge(string u,string v, float distance) //price in Rs,distance in km,time in minutes
	{
		neighbour neighbourOfU(v,distance);
		neighbour neighbourOfV(u,distance);

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
				cout<<N.name<<" "<<N.distance<<"kms Rs."<<N.price<<" "<<N.time<<" minutes\n";
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
		int price=minD*1.5;
		int time=minD*1;
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

				cout << front << ", ";
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
	char in;
	graph g("metro");
	vector<string> names={"DLF Mall","Mayur Vihar Ext.","CP","Supreme Court","Huda","Logix","Qutab Minar","Sector 69","Dilli Haat","Railway Station","Electronic city","Airport"};
	g.addEdge("DLF Mall","Mayur Vihar Ext.",12);
	g.addEdge("DLF Mall","Logix",3);
	g.addEdge("Logix","Sector 69",2);
	g.addEdge("Sector 69","Electronic City",10);
	g.addEdge("Sector 69","Dilli Haat",11);
	g.addEdge("Electronic City","Airport",1);
	g.addEdge("Dilli Haat","Railway Station",9);
	g.addEdge("Airport","Railway Station",30);
	g.addEdge("Railway Station","Qutab Minar",6);
	g.addEdge("CP","Qutab Minar",8);
	g.addEdge("Mayur Vihar Ext.","CP",7);
	g.addEdge("CP","Supreme Court",13);
	g.addEdge("Huda","Supreme Court",5);
	g.addEdge("Huda","Railway Station",25);
	system("Color 0A");
	cout<<"Welcome!!!\n";
	cout<<"Stations are: ";
	g.bfs("DLF Mall");
	cout<<"Do you wish to know a detailed overview of the network in terms of location, price and distance (Y/N)?";
	cin>>in;
	if (in=='Y' || in=='y')
		{g.print();
        getch();}
    else
        getch();
	string src; //soruce station
	system("Color 09");
	fflush(stdin);
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
	system("Color 0B");
	g.dijkstra(src,dest);
	return 0;
}

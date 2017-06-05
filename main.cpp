#include <cstdio>
#include <iostream>
#include "Graph.h"

using std::cout;
using std::endl;

map<string, string> Graph::config;


void showVector(vector<int> & v, string name = "vector", int id = 0)
{
	cout << name << " " << id << " (size=" << v.size() << ") : " << endl;
	//for (size_t i = 0; i < v.size(); ++i)
		//cout << v[i] << " ";
	//cout << endl;
}

int main(int argc, char *argv[])
{
	//读配置文件，该文件记录社团检测算法的具体路径
	Graph::loadConfig("F:/Project/CommunityDetection/config.txt");



	Graph g;
	g.load("graph.txt");
	g.print();

	Communities cs, cs2;
	cs.load("comm.txt");
	cs2.load("comm2.txt");
	cs2.print(true, true);

	double Q1 = cs.calcModularity(g);
	double Q2 = cs2.calcModularity(g);
	cout << "Q1 = " << Q1 << endl;
	cout << "Q2 = " << Q2 << endl;

	printf("------------\ndone\n");
	return 0;
}
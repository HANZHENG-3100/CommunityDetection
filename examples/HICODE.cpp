#include <cstdio>
#include <iostream>
#include "../Graph.h"

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
	//�������ļ������ļ���¼���ż���㷨�ľ���·��
	Graph::loadConfig("F:/Project/CommunityDetection/config.txt");



	printf("------------\ndone\n");
	return 0;
}
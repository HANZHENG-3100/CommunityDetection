#include <cstdio>
#include "Graph.h"

map<string, string> Graph::config;

int main()
{
	//�������ļ������ļ���¼���ż���㷨�ľ���·��
	Graph::loadConfig("F:/Project/CommunityDetection/config.txt");

	Graph g;
	//��edge list���ı��ļ�����ͼ
	g.load("F:/Project/CommunityDetection/graph.txt");


	g.runInfomap().save("result/Infomap.gen");
	g.runLinkComm().save("result/LC.gen");
	g.runOSLOM2().save("result/OSLOM.gen");
	g.runGCE().save("result/GCE.gen");
	g.runDemon().save("result/Demon.gen");
	g.runCFinder().save("result/CFinder.gen");
	g.runMod().save("result/Mod.gen");

	/*
	g.showPic();
	Communities cs = g.runMod();
	g = g.remove(cs);
	g.print();
	g.showPic();*/

	printf("------------\ndone\n");
	return 0;
}
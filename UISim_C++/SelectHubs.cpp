/*
 * SelectHubs.cpp
 *
 *  Created on: 2019Äê3ÔÂ17ÈÕ
 *      Author: yichen_shen
 */



#include "include/Config.h"
#include "include/HubSelection.h"
#include "include/InDegHub.h"
#include "include/RandomHub.h"
#include<iostream>
#include"include/Trim.h"
#include <cstring>

using namespace std;

int main(int argc, char* argv[]){

	Config::hubType = argv[1];
	if (strcmp(argv[1],"random")==0)
	{
		RandomHub h(Config::nodeFile,Config::edgeFile);
		h.save();
	}
	else if(strcmp(argv[1],"indeg")==0)
	{
		InDegHub h(Config::nodeFile,Config::edgeFile);
		h.save();
	}
	else {
		cout<<"Unknown hub selection algorithm!"<<endl;
		return 0;
	}
//	string a ="1	3,4";
//	vector<string> b;
//	split(a,"\t",b);
//	cout<<b[1];

	return 0;
}

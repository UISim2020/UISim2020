/*
 * InDegHub.cpp
 *
 *  Created on: 2019Äê3ÔÂ16ÈÕ
 *      Author: yichen_shen
 */

#include "InDegHub.h"
#include<iostream>


InDegHub::InDegHub(string nodeFile, string edgeFile):HubSelection(nodeFile,edgeFile){
}

void InDegHub::fillNodes() {

	for (auto &n : graph.getNodes())

		nodes.push_back(pair<int,double>(n->id, n->in.size()));
}

InDegHub::~InDegHub() {
	// TODO Auto-generated destructor stub
}


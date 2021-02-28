/*
 * HubSelection.cpp
 *
 *  Created on: 2019Äê3ÔÂ16ÈÕ
 *      Author: yichen_shen
 */

#include "HubSelection.h"
#include "IndexManager.h"
#include "TextWriter.h"
#include <algorithm>
#include <iostream>
HubSelection::HubSelection() {
	// TODO Auto-generated constructor stub

}
bool compare(const pair<int,double> &a, const pair<int,double> &b )
{
    return a.second > b.second;
}
HubSelection::HubSelection(string nodeFile, string edgeFile) {
	graph.loadFromFile(nodeFile, edgeFile, false);
}

void HubSelection::sortNodes() {
	sort(nodes.begin(),nodes.end(),compare);
}

void HubSelection::save() {
	fillNodes();
	IndexManager::mkSubDirShallow();
	sortNodes();

	if (nodes.size() > Config::hubTop)
		nodes.resize(Config::hubTop);
	TextWriter out(IndexManager::getHubNodeFile());
	for (auto n : nodes)
		out.writeln(n.first);

	out.close();
}

HubSelection::~HubSelection() {
	// TODO Auto-generated destructor stub
}


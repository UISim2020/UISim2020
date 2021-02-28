/*
 * HubSelection.h
 *
 *  Created on: 2019Äê3ÔÂ16ÈÕ
 *      Author: yichen_shen
 */

#ifndef HUBSELECTION_H_
#define HUBSELECTION_H_
#include "Graph.h"
#include <utility>
#include <vector>
using namespace std;
class HubSelection {
	protected:
	vector <pair<int,double>> nodes;
	Graph graph;
	virtual  void fillNodes()=0;
public:
	HubSelection();
	HubSelection(string nodeFile, string edgeFile);
	void sortNodes();
	 void save();
	virtual ~HubSelection();
};

#endif /* HUBSELECTION_H_ */

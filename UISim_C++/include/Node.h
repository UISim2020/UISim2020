/*
 * Node.h
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#ifndef NODE_H_
#define NODE_H_

#include<vector>

using namespace std;
class Node {

	public:
	int id;
	bool isHub = false;
	int index = -1;
	vector<Node*> out;
	vector<Node*> in;

	vector<int> outId;
	vector<int> inId;

	double outEdgeWeight = 0;
	double outEdgeWeightInSub = 0;
	double vOld = 0;
	double vNew = 0;
	Node();
	Node(int id);
	Node(int id,int index);
//	Node(const Node &node);
	virtual ~Node();
	bool operator==(const Node* n) const;
	bool operator==(const Node & n) const;
	void initOutEdgeWeight();
	void initOutEdgeWeightUsingNeighborId();
};
#endif /* NODE_H_ */

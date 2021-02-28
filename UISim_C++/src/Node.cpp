/*
 * Node.cpp
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#include "Node.h"


Node::Node()
{};
Node::Node(int id) {
	this->id = id;

}

Node::Node(int id, int index) {
	this->id = id;
	this->index = index;
}
//Node::Node(const Node &node) {
//	this->isHub =node.isHub;
//	this->isVisited =node.isVisited;
//	this->out=node.out;
//	this->in=node.in;
//
//	this->outId=node.outId;
//	this->inId=node.inId;
//
//	this->outEdgeWeight = node.outEdgeWeight;
//	this->outEdgeWeightInSub = node.outEdgeWeightInSub;
//	this->vOld = node.vOld;
//	this->vNew = node.vNew;
//	this->id = node.id;
//	this->index = node.index;
//}
Node::~Node() {
	// TODO Auto-generated destructor stub
}

bool Node::operator ==(const Node* n)const {
	return this->id==n->id;
}

void Node::initOutEdgeWeight() {
	if (out.size() > 0)
		outEdgeWeight = 1.0 / out.size();
	else
		outEdgeWeight = 0;
}

void Node::initOutEdgeWeightUsingNeighborId() {
	if (outId.size() > 0)
		outEdgeWeight = 1.0 / outId.size();
	else
		outEdgeWeight = 0;
}

bool Node::operator ==(const Node& n) const {
	return this->id==n.id;
}

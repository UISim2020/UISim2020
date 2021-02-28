/*
 * NodeHash.h
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#ifndef NODEHASH_H_
#define NODEHASH_H_

#include "Node.h"


struct hash_node{
	size_t operator()(const Node & n) const{
		return hash<int>()(n.id);
	}


};

struct hash_node1{
	size_t operator()(const Node* n) const{
		return hash<int>()(n->id);
	}


};


#endif /* NODEHASH_H_ */

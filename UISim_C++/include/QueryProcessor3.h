/*
 * QueryProcessor2.h
 *
 *  Created on: 2019Äê3ÔÂ16ÈÕ
 *      Author: yichen_shen
 */

#ifndef QUERYPROCESSOR3_H_
#define QUERYPROCESSOR3_H_

#include "Graph.h"
#include <string>
#include <unordered_map>
using namespace std;
class QueryProcessor3
{
private:
  Graph *graph;
  double checkMeetigNodeImportance(PrimeSim &inSim, int mid);

public:
  QueryProcessor3(Graph &graph);
  PrimeSim graphExp(Node &q, string graphType);
  double query(Node &q1, Node &q2);
  virtual ~QueryProcessor3();
};

#endif /* QUERYPROCESSOR3_H_ */

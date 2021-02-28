/*
 * QueryProcessor2.h
 *
 *  Created on: 2019Äê3ÔÂ16ÈÕ
 *      Author: yichen_shen
 */

#ifndef QUERYPROCESSOR2_H_
#define QUERYPROCESSOR2_H_

#include "Graph.h"
#include <string>
#include <unordered_map>
using namespace std;
class QueryProcessor2
{
private:
  Graph *graph;
  double checkMeetigNodeImportance(PrimeSim &inSim, int mid);

public:
  QueryProcessor2(Graph &graph);
  void graphExp(Node &q, string graphType, PrimeSim &sim);
  void query(Node &q, unordered_map<int, double> &result);
  virtual ~QueryProcessor2();
};

#endif /* QUERYPROCESSOR2_H_ */

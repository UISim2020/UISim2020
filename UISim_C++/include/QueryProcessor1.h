/*
 * QueryProcessor1.h
 *
 *  Created on: 2019��3��16��
 *      Author: yichen_shen
 */

#ifndef QUERYPROCESSOR1_H_
#define QUERYPROCESSOR1_H_

#include "Graph.h"
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;
struct nodePairVal
{
  int n1;
  int n2;
  double val;
  nodePairVal(int n1, int n2, double val) : n1(n1), n2(n2), val(val) {}
  friend bool operator<(const nodePairVal &a, const nodePairVal &b)
  {
    return a.val > b.val;
  }
};
class QueryProcessor1
{
private:
  Graph *graph;
  double checkMeetigNodeImportance(PrimeSim &inSim, int mid);

public:
  QueryProcessor1(Graph &graph);
  void graphExp(Node &q, string graphType, PrimeSim &sim);
  void query(int k, priority_queue<nodePairVal> &H);
  virtual ~QueryProcessor1();
};

#endif /* QUERYPROCESSOR1_H_ */

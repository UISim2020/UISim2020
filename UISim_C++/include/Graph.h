/*
 * Graph.h
 *
 *  Created on: 2019��3��13��
 *      Author: yichen_shen
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "NodeHash.h"
#include "Config.h"
#include "PrimeSim.h"
#include <random>
using namespace std;

class Graph
{
protected:
  unordered_set<Node *, hash_node1> hubs;
  unordered_set<int> is_visited;

private:
  //	default_random_engine rnd;
  double ITER_STOP = Config::stopRea; //0.001;
  double DEPTH = Config::depth;
  int maxNode = Config::maxNode;

public:
  unordered_map<int, Node, hash_node> nodes;
  Graph(const Graph &Graph);
  Graph();

  virtual ~Graph();
  void preprocess();
  void saveToFile(string nodeFile, string edgeFile);
  void clear();
  void loadGraphFromFile(string nodeFile, string edgeFile);
  void loadFromFile(string nodeFile, string edgeFile,
                    bool identifyHubs);
  void loadFromFile(string nodeFile, string edgeFile,
                    string hubFile);
  void loadHubs(string hubNodeFile);
  unordered_set<Node *, hash_node1> getHubs();
  void addNode(const Node &n);
  void addEdge(int from, int to);
  void resetPrimeG();
  void computeOutPrimeSim(Node &q, double maxhubScore, PrimeSim &outSim);
  void computeInPrimeSim(Node &q, double maxhubScore, PrimeSim &inSim);
  int numNodes();
  Node &getNode(int id);
  vector<Node *> getNodes();
  bool containsNode(int id);
  int findNode(int index); // add by kai zhang 2020-12-7
  void init();
};

#endif /* GRAPH_H_ */

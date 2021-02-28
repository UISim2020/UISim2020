/*
 * OnlineTest.cpp
 *
 *  Created on: 2019Äê3ÔÂ17ÈÕ
 *      Author: yichen_shen
 */
#include "include/Config.h"
#include "include/Graph.h"
#include "include/QueryProcessor2.h"
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

bool com(const pair<int, double> &a, const pair<int, double> &b)
{
  return a.second > b.second;
}
int main(int argc, char *argv[])
{
  clock_t startTime, endTime;
  Config::hubType = argv[1];
  Config::numHubs = atoi(argv[2]);
  Config::eta = atof(argv[3]);
  int qid = atoi(argv[4]);
  cout << Config::hubType << " " << Config::numHubs << " " << Config::eta << " " << qid << endl;
  Graph graph;
  graph.loadFromFile(Config::nodeFile, Config::edgeFile, true);

  cout << "Starting query processing..." << endl;
  QueryProcessor2 qp(graph);
  Node &q = graph.getNode(qid);

  //List<KeyValuePair> rankedResult = null;
  unordered_map<int, double> result; //actually not ranked
  startTime = clock();

  qp.query(q, result);
  endTime = clock();
  cout << "result size: " << result.size() << endl;

  cout << "The run time is: " << (double)(endTime - startTime) << "ms" << endl;
  vector<pair<int, double>> tmp;
  for (auto &i : result)
    tmp.push_back(i);

  sort(tmp.begin(), tmp.end(), com);
  //       for (auto& i : tmp)
  //    	   cout<<i.first<<" "<<i.second<<endl;
  return 0;
}

/*
 * Online.cpp
 *
 *  Created on: 2019��3��30��
 *      Author: yichen_shen
 */
#include "include/Config.h"
#include "include/Graph.h"
#include "include/QueryProcessor1.h"
#include "TextReader.h"
#include "TextWriter.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <ctime>

using namespace std;
bool com(const pair<int, double> &a, const pair<int, double> &b)
{
  return a.second > b.second;
}
int main(int argc, char *argv[])
{
  clock_t startTime, elapsed;
  Config::hubType = argv[1];
  Config::numHubs = atoi(argv[2]);
  Config::depth = atoi(argv[3]);
  Config::stopRea = atof(argv[4]);
  Config::eta = atof(argv[5]);
  int k = atoi(argv[6]);
  cout << Config::hubType << " " << Config::numHubs << " " << Config::depth << " " << Config::stopRea << " " << Config::eta << " " << k << endl;
  Graph graph;
  if (Config::numHubs > 0)
    graph.loadFromFile(Config::nodeFile, Config::edgeFile, true);
  else
    graph.loadFromFile(Config::nodeFile, Config::edgeFile, false);

  cout << "Starting query processing..." << endl;
  QueryProcessor1 qp(graph);
  TextWriter out(Config::outputDir + "/" + "fs-AP-k" + to_string(k) + "_H" + Config::hubType + "_DEP" + to_string(Config::depth) + "_STP" + to_string(Config::stopRea) + "_H" + to_string(Config::numHubs) + "_E" + to_string(Config::eta));

  int count = 0;
  startTime = clock();
  priority_queue<nodePairVal> H;
  qp.query(k, H);
  elapsed = clock() - startTime;
  out.write(to_string((double)elapsed / CLOCKS_PER_SEC * 1000) + "ms ");
  vector<nodePairVal> result;
  while (!H.empty())
  {
    result.push_back(H.top());
    H.pop();
  }
  for (int i = result.size() - 1; i >= 0; i--)
  {
    nodePairVal npv = result[i];
    out.writeln(to_string(graph.findNode(npv.n1)) + "\t" + to_string(graph.findNode(npv.n2)) + "\t" + to_string(npv.val));
    count++;
    if (count == k)
      break;
  }
  out.flush();
  out.close();
  return 0;
}

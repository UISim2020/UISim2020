/*
 * Online.cpp
 *
 *  Created on: 2019��3��30��
 *      Author: yichen_shen
 */
#include "include/Config.h"
#include "include/Graph.h"
#include "include/QueryProcessor3.h"
#include "include/Trim.h"
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
  clock_t startTime, endTime;
  Config::hubType = argv[1];
  Config::numHubs = atoi(argv[2]);
  Config::depth = atoi(argv[3]);
  Config::stopRea = atof(argv[4]);
  Config::eta = atof(argv[5]);
  cout << Config::hubType << " " << Config::numHubs << " " << Config::depth << " " << Config::stopRea << " " << Config::eta << " " << endl;
  Graph graph;
  // 1. 测试内存
  if (Config::numHubs > 0)
    graph.loadFromFile(Config::nodeFile, Config::edgeFile, true);
  else
    graph.loadFromFile(Config::nodeFile, Config::edgeFile, false);

  cout << "Loading queries..." << endl;
  vector<vector<Node>> qNodes;
  TextReader in(Config::queryFile);
  string line;
  int id;
  while ((line = in.readln()).length() != 0)
  {
    vector<string> ssplit;
    split(line, "\t", ssplit);
    int from = atoi(ssplit[0].c_str());
    int to = atoi(ssplit[1].c_str());
    vector<Node> tmp;
    tmp.push_back(graph.getNode(from));
    tmp.push_back(graph.getNode(to));
    qNodes.push_back(tmp);
  }
  in.close();
  cout << "Starting query processing..." << endl;
  QueryProcessor3 qp(graph);
  TextWriter out(Config::outputDir + "/" +
                 "fastSingleP_NoOffline_NoCor" + Config::hubType + "_DEP" + to_string(Config::depth) + "_STP" + to_string(Config::stopRea) + "_H" + to_string(Config::numHubs) + "_E" + to_string(Config::eta));
  int count = 0;
  clock_t elapsed;
  for (auto qid : qNodes)
  {
    count++;
    if (count % 10 == 0)
      cout << "+";
    graph.resetPrimeG();
    double result;
    startTime = clock();
    result = qp.query(qid[0], qid[1]);
    endTime = clock();
    elapsed = endTime - startTime;
    out.writeln(to_string((double)elapsed / CLOCKS_PER_SEC * 1000) + "ms " + to_string(result));
    out.flush();
  }
  out.close();
  // 2. 测试内存
  return 0;
}

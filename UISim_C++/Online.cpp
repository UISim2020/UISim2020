/*
 * Online.cpp
 *
 *  Created on: 2019��3��30��
 *      Author: yichen_shen
 */
#include "include/Config.h"
#include "include/Graph.h"
#include "include/QueryProcessor2.h"
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
  vector<Node> qNodes;
  TextReader in(Config::queryFile);
  string line;
  int id;
  while ((line = in.readln()).length() != 0)
  {
    id = atoi(line.c_str());
    qNodes.push_back(graph.getNode(id));
  }
  in.close();
  cout << "Starting query processing..." << endl;
  QueryProcessor2 qp(graph);
  TextWriter out(Config::outputDir + "/" +
                 "fastsimSS" + Config::hubType + "_DEP" + to_string(Config::depth) + "_STP" + to_string(Config::stopRea) + "_H" + to_string(Config::numHubs) + "_E" + to_string(Config::eta));
  int count = 0;
  clock_t elapsed;
  for (auto qid : qNodes)
  {
    count++;
    if (count % 10 == 0)
      cout << "+";
    graph.resetPrimeG();
    vector<pair<int, double>> rankedResult;
    unordered_map<int, double> result;
    startTime = clock();
    qp.query(qid, result);
    endTime = clock();
    elapsed = endTime - startTime;
    for (auto &i : result)
      rankedResult.push_back(i);
    sort(rankedResult.begin(), rankedResult.end(), com);
    out.write(to_string(double(elapsed) / CLOCKS_PER_SEC * 1000));
    out.write("ms ");
    for (int i = 0; i < Config::resultTop & i < rankedResult.size(); i++)
      out.write(to_string(rankedResult[i].first) + "\t" + to_string(rankedResult[i].second) + "\n");
    out.flush();
  }
  out.close();
  // 2. 测试内存
  return 0;
}

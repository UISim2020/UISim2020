/*
 * PrimeSim.h
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#ifndef PRIMESIM_H_
#define PRIMESIM_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Node.h"

using namespace std;
using namespace __gnu_cxx;
class PrimeSim
{
private:
  vector<int> hubs;

protected:
  bool outG;
  vector<int> meetingNodes;

public:
  unordered_map<int, unordered_map<int, double>> map;
  PrimeSim();
  PrimeSim(int numNodes);
  int numHubs();
  int numLength();
  unordered_map<int, unordered_map<int, double>> &getMap();
  int getHubId(int index);
  vector<int> &getMeetingNodes();
  void addNewNode(Node &h, bool simType, unordered_set<int> &is_visited);
  void set(int l, Node &n, double value);
  void set(int l, const unordered_map<int, double> &nodeValuePairs);
  long computeStorageInBytes();
  string getCountInfo();
  void trim(double clip);
  void saveToDisk(int id, string type, bool doTrim);
  void loadFromDisk(int id, string type);
  PrimeSim duplicate();
  void addFrom(PrimeSim &nextOut, const unordered_map<int, double> &oneHubValue);
  void addMeetingNodes(vector<int> &nodes);
  virtual ~PrimeSim();
};

#endif /* PRIMESIM_H_ */

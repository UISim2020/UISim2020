/*
 * PrimeSim.cpp
 *
 *  Created on: 2019��3��13��
 *      Author: yichen_shen
 */

#include "PrimeSim.h"
#include "IndexManager.h"
#include <iostream>
#include <algorithm>
#include "DataWriter.h"
#include "DataReader.h"
#include "Config.h"
using namespace std;
PrimeSim::PrimeSim()
{
  // TODO Auto-generated constructor stub
}

int PrimeSim::numHubs()
{
  return hubs.size();
}

int PrimeSim::numLength()
{
  return map.size();
}

unordered_map<int, unordered_map<int, double>> &PrimeSim::getMap()
{
  return map;
}

int PrimeSim::getHubId(int index)
{
  return hubs.at(index);
}

vector<int> &PrimeSim::getMeetingNodes()
{
  return meetingNodes;
}

void PrimeSim::addNewNode(Node &h, bool simType, unordered_set<int> &is_visited)
{
  is_visited.insert(h.id);
  if (h.isHub)
    hubs.push_back(h.id);
  if (simType && h.out.size() > 1) //store meeting nodes for ingraphs //meetingnodes refer to >1 nodes (descendants)
    meetingNodes.push_back(h.id);
}

void PrimeSim::set(int l, Node &n, double value)
{
  auto it = map.find(l);
  if (it != map.end())
  {
    (it->second)[n.id] = value;
  }
  else
  {
    //		nodesVal[n.id] = value;
    unordered_map<int, double> tmp = {{n.id, value}};
    map[l] = tmp;
  }
}

void PrimeSim::set(int l, const unordered_map<int, double> &nodeValuePairs)
{
  auto it = map.find(l);
  //		for(Integer i:nodeValuePairs.keySet()) {
  //			System.out.println("PS node: "+ i + " rea: " +nodeValuePairs.get(i));
  //		}
  if (it == map.end())
  {
    map[l] = nodeValuePairs;
  }
  else
  {
    cout << "####PrimeSim line108: should not go to here." << endl;
    map[l] = nodeValuePairs;
  }
}

long PrimeSim::computeStorageInBytes()
{
  long nodeIdSize = (1 + hubs.size()) * 4;
  long mapSize = (1 + map.size()) * 4 + map.size() * 8;
  return nodeIdSize + mapSize;
}

string PrimeSim::getCountInfo()
{
  int hubSize = hubs.size();
  int meetingNodesSize = meetingNodes.size();

  return "hub size: " + to_string(hubSize) + " meetingNodesSize: " + to_string(meetingNodesSize);
}

void PrimeSim::trim(double clip)
{

  unordered_map<int, unordered_map<int, double>> newMap;
  vector<int> newHublist;
  vector<int> newXlist;

  for (auto &l : map)
  {
    unordered_map<int, double> newPairs;
    for (auto &nid : (l.second))
    {
      double score = nid.second;
      if (score > clip)
      {
        newPairs[nid.first] = score;
        if (find(hubs.begin(), hubs.end(), nid.first) != hubs.end() && find(newHublist.begin(), newHublist.end(), nid.first) == newHublist.end())
          newHublist.push_back(nid.first);
        if (find(meetingNodes.begin(), meetingNodes.end(), nid.first) != meetingNodes.end() && find(newXlist.begin(), newXlist.end(), nid.first) == newXlist.end())
          newXlist.push_back(nid.first);
      }
    }

    newMap[l.first] = newPairs;
  }

  this->map = newMap;
  this->hubs = newHublist;
  this->meetingNodes = newXlist;
}

void PrimeSim::saveToDisk(int id, string type, bool doTrim)
{
  string path = "";
  if (type == "out")
    //path = "./outSim/" + Integer.toString(id);
    path = IndexManager::getIndexDeepDir() + "out/" + to_string(id);
  else if (type == "in")
    //path = "./inSim/" + Integer.toString(id);
    path = IndexManager::getIndexDeepDir() + "in/" + to_string(id);
  else
  {
    cout << "Type of prime graph should be either out or in." << endl;
    exit(0);
  }

  //	System.out.println(path+"/"+id);

  DataWriter out(path);

  if (doTrim)
    trim(Config::clip);

  out.writeInteger(hubs.size());
  for (int i : hubs)
  {
    out.writeInteger(i);
  }

  out.writeInteger(meetingNodes.size());
  for (int i : meetingNodes)
  {
    out.writeInteger(i);
  }
  out.writeInteger(map.size());
  for (int i = 0; i < map.size(); i++)
  {

    auto pairMap = map.find(i);
    int pairNum = (pairMap->second).size();
    out.writeInteger(pairNum);
    for (auto &j : pairMap->second)
    {
      out.writeInteger(j.first);
      out.writeDouble(j.second);
    }
  }

  out.close();
}

void PrimeSim::loadFromDisk(int id, string type)
{

  string path = "";
  if (type == "out")
    path = IndexManager::getIndexDeepDir() + "out/" + to_string(id);
  else if (type == "in")
    path = IndexManager::getIndexDeepDir() + "in/" + to_string(id);
  else
  {
    cout << "Type of prime graph should be either out or in." << endl;
    exit(0);
  }

  //==============

  DataReader in(path);

  int n = in.readInteger();
  hubs.clear();
  for (int i = 0; i < n; i++)
    this->hubs.push_back(in.readInteger());

  int numM = in.readInteger();
  meetingNodes.clear();
  for (int i = 0; i < numM; i++)
    meetingNodes.push_back(in.readInteger());

  int numL = in.readInteger();
  for (int i = 0; i < numL; i++)
  {
    int numPair = in.readInteger();
    unordered_map<int, double> pairMap;
    for (int j = 0; j < numPair; j++)
    {
      int nodeId = in.readInteger();
      double nodeScore = in.readDouble();
      pairMap[nodeId] = nodeScore;
    }
    map[i] = pairMap;
  }

  in.close();
}

PrimeSim PrimeSim::duplicate()
{

  PrimeSim sim;
  sim.map = this->map;
  return sim;
}

void PrimeSim::addFrom(PrimeSim &nextOut,
                       const unordered_map<int, double> &oneHubValue)
{

  for (auto &lenToHub : oneHubValue)
  {
    double hubScoreoflen = lenToHub.second;
    for (auto &lenFromHub : nextOut.getMap())
    {
      if (lenFromHub.first == 0)
      {
        // the new score of hub (over length==0) is just the score on prime graph
        continue;
      }
      int newLen = lenToHub.first + lenFromHub.first;
      if (newLen > Config::depth)
      {
        continue;
      }

      if (map.find(newLen) == map.end())
        map[newLen] = unordered_map<int, double>();
      for (auto &toNode : nextOut.getMap()[lenFromHub.first])
      {
        double oldValue;
        if (map[newLen].find(toNode.first) != map[newLen].end())
          oldValue = map[newLen][toNode.first];
        else
          oldValue = 0.0;
        //System.out.println(oldValue);
        double newValue = hubScoreoflen * nextOut.getMap()[lenFromHub.first][toNode.first];
        //				//added aug-29
        //					if (newValue<Config.epsilon)
        //						continue;
        map[newLen][toNode.first] = oldValue + newValue;
        //					PrintInfor.printDoubleMap(this.getMap(), "assemble simout of the hub at length: " + lenFromHub +" node: "+ toNode );
        //					System.out.println(this.getMap());
      }
    }
  }
}

void PrimeSim::addMeetingNodes(vector<int> &nodes)
{

  for (int nid : nodes)
  {
    if (find(meetingNodes.begin(), meetingNodes.end(), nid) == meetingNodes.end())
      meetingNodes.push_back(nid);
  }
}

PrimeSim::~PrimeSim()
{
  // TODO Auto-generated destructor stub
}

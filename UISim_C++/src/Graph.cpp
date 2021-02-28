/*
 * Graph.cpp
 *
 *  Created on: 2019��3��13��
 *      Author: yichen_shen
 */

#include "Graph.h"
#include "TextWriter.h"
#include "TextReader.h"
#include "Trim.h"
#include <math.h>
#include "IndexManager.h"
#include <time.h>
#include <iostream>
#include <algorithm>
Graph::Graph()
{
  // TODO Auto-generated constructor stub
  //	rnd.seed(time(NULL));
}

Graph::~Graph()
{
  // TODO Auto-generated destructor stub
}

void Graph::preprocess()
{
  unordered_set<Node *, hash_node1> remove;
  for (auto &n : nodes)
  {
    // if (n.in.size() < minNumEdges || n.out.size() < minNumEdges) {
    if (n.second.in.empty() || n.second.out.empty())
      remove.insert(&(n.second));
  }
  if (remove.empty())
    return; // finished
  cout << remove.size() << " nodes to be removed..." << endl;

  for (auto &n : remove)
  {
    // remove from out neighbors' in
    for (auto &m : n->out)
      m->in.erase(find(m->in.begin(), m->in.end(), n));

    // remove from in neighbors' out
    for (auto &m : n->in)
      m->out.erase(find(m->out.begin(), m->out.end(), n));
    nodes.erase(n->id);
  }

  preprocess();
}

void Graph::saveToFile(string nodeFile, string edgeFile)
{
  TextWriter out(nodeFile);
  for (auto &n : nodes)
    out.writeln(n.second.id);
  out.close();
  TextWriter newout(edgeFile);
  int count = 0;
  for (auto &n : nodes)
    for (auto &m : n.second.out)
    {
      newout.writeln(n.second.id + "\t" + m->id);
      count++;
    }
  newout.close();
  cout << "# Nodes: " << nodes.size() << endl;
  cout << "# Edges: " << count << endl;
}

void Graph::clear()
{
  nodes.clear();
}

void Graph::loadGraphFromFile(string nodeFile, string edgeFile)
{
  clear();

  TextReader inN(nodeFile);
  TextReader inE(edgeFile);
  string line;

  cout << "Loading graph" << endl;
  int count = 0;
  while ((line = inN.readln()).size() != 0)
  {
    int id = atoi(line.c_str());
    addNode(Node(id, count));
    // for exact
    //this.nodesIndex[count]=id;
    //            System.out.println("Test node index----Graph:Line103-----Node id: "+ id+" index: "+count);

    count++;
    if (count % 100000 == 0)
      cout << ".";
  }
  while ((line = inE.readln()).size() != 0)
  {
    vector<string> ssplit;
    split(line, "\t", ssplit);
    int from = atoi(ssplit[0].c_str());
    //  System.out.println(from);
    int to = atoi(ssplit[1].c_str());
    addEdge(from, to);
    //            count++;
    //            if (count % 1000000 == 0)
    //                System.out.print(".");
  }
  cout << "Loading end" << endl;
  inN.close();
  inE.close();
  init();
}

void Graph::loadFromFile(string nodeFile, string edgeFile, bool identifyHubs)
{
  loadGraphFromFile(nodeFile, edgeFile);

  if (identifyHubs)
  {
    string hubNodeFile = IndexManager::getHubNodeFile();

    loadHubs(hubNodeFile);
  }
}

void Graph::loadFromFile(string nodeFile, string edgeFile, string hubFile)
{
  loadGraphFromFile(nodeFile, edgeFile);

  loadHubs(hubFile);
}

void Graph::loadHubs(string hubNodeFile)
{
  TextReader in(hubNodeFile);
  string line;

  unordered_set<Node *, hash_node1> hubs;

  while ((line = in.readln()).length() != 0)
  {
    if (hubs.size() == Config::numHubs)
      break;
    int id = atoi(line.c_str());
    Node *n = &getNode(id);
    //	            if (n == null)
    //	                n = new Node(id);
    n->isHub = true;
    hubs.insert(n);
  }

  in.close();
}

unordered_set<Node *, hash_node1> Graph::getHubs()
{
  return hubs;
}

void Graph::addNode(const Node &n)
{
  nodes[n.id] = n;
}

void Graph::addEdge(int from, int to)
{
  Node *nFrom = &getNode(from);
  Node *nTo = &getNode(to);
  nFrom->out.push_back(nTo);
  nTo->in.push_back(nFrom);
}

void Graph::resetPrimeG()
{
  //	auto n = nodes.begin();
  //	while(n!=nodes.end())
  //	{
  //		n->second.isVisited = false;
  //		n++;
  //	}
  unordered_set<int> tmp;
  is_visited.swap(tmp);
}

void Graph::computeOutPrimeSim(Node &q, double maxhubScore, PrimeSim &outSim)
{
  auto &simmap = outSim.getMap();
  unordered_map<int, unordered_map<int, double>>::iterator simit;
  vector<Node *> expNodes;
  unordered_map<int, double> valInLastLevel;
  vector<Node *> newExpNodes;
  unordered_map<int, double> valInThisLevel;
  double rea;
  expNodes.push_back(&q);
  is_visited.insert(q.id);
  //q.isVisited = true; //don't save query node as hub or meeting node
  outSim.addNewNode(q, false, is_visited);
  outSim.set(0, q, 1.0);
  valInLastLevel[q.id] = 1.0;
  int length = 1;
  while (length <= DEPTH)
  {
    if (expNodes.size() == 0)
      break;
    newExpNodes.resize(0);
    valInThisLevel.clear();
    for (auto &cur : expNodes)
    {
      //System.out.println("current node: " + cur.id);
      for (auto &n : cur->out)
      { // an edge cur-->n, where cur is meeting node, so for n, should store the Reversed reachability: R(n->cur)=1*1/In(n)
        //System.out.println("out:" + n.id);
        if (is_visited.find(n->id) == is_visited.end())
          outSim.addNewNode(*n, false, is_visited);
        rea = (double)valInLastLevel[cur->id] / (double)n->in.size() * (double)sqrt(Config::alpha); //*(Config.alpha)2.26: ensure the prime subgraphs are not too large
                                                                                                    //know the reachability when expanding hubs
                                                                                                    //	double rea = valInLastLevel.get(cur.id)/n.in.size();//modified 8.27, don't multiply alpha at this time, otherwise will double multiply alpha^length as another tour also has this alpha, so leave it for online merging.
        if (rea * maxhubScore > ITER_STOP)
        {
          if (valInThisLevel.find(n->id) == valInThisLevel.end())
          {
            //System.out.println("value:" + rea);
            valInThisLevel[n->id] = rea;
            if (n->out.size() > 0 && !n->isHub)
              newExpNodes.push_back(n);
          }
          else
            valInThisLevel[n->id] = valInThisLevel[n->id] + rea;
        }
      }
    }

    outSim.set(length, valInThisLevel);
    //			System.out.println(length);
    //			for(Integer i:valInThisLevel.keySet()) {
    //				System.out.println("node:" + i + " rea:" + valInThisLevel.get(i));
    //			}
    expNodes = newExpNodes;
    //newExpNodes.clear();
    valInLastLevel = valInThisLevel;
    //valInThisLevel.clear();

    length++;
  }
  /*	for(Integer m:outSim.map.keySet()) {
		System.out.println("length:" + m);
		//System.out.println(outSim.map.get(m).size());
		for(Integer n:outSim.map.get(m).keySet()) {
			System.out.println("node:" + n + " rea:" + outSim.map.get(m).get(n));
		}
	}*/
  //	System.out.println("Remove empty length (Out) for node " + q.id);
  for (simit = simmap.begin(); simit != simmap.end();)
  {
    if (simit->second.size() == 0)
    {
      //			System.out.println("No such length in Insim " + l);
      simit = simmap.erase(simit);
    }
    else
    {
      simit++;
    }
  }
}

void Graph::computeInPrimeSim(Node &q, double maxhubScore, PrimeSim &inSim)
{
  auto &simmap = inSim.getMap();
  unordered_map<int, unordered_map<int, double>>::iterator simit;
  vector<Node *> expNodes;
  //List<Node> newExpNodes = new ArrayList <Node>();
  unordered_map<int, double> valInLastLevel;
  //Map<Integer,Double> valInThisLevel = new HashMap<Integer,Double>();

  expNodes.push_back(&q); // Nodes to be expanded, initially only q
  //add 2/23/2015
  inSim.addNewNode(q, true, is_visited);
  //q.isVisited = true;
  inSim.set(0, q, 1.0);
  valInLastLevel[q.id] = 1.0;
  int length = 1;
  vector<Node *> newExpNodes;
  unordered_map<int, double> valInThisLevel;
  double rea;
  while (length <= DEPTH)
  {

    if (expNodes.size() == 0)
      break;
    newExpNodes.resize(0);
    valInThisLevel.clear();
    for (auto cur : expNodes)
    {

      for (auto n : cur->in)
      { //a edge n-->cur, if R(cur)==a, then R(n)==1/In(cur)*a, because of the reversed walk from cur to n.
        if (is_visited.find(n->id) == is_visited.end())
          inSim.addNewNode(*n, true, is_visited);                                     // mark n as visited and add n to meetingNodes in PrimeSim
        rea = valInLastLevel[cur->id] / (double)cur->in.size() * sqrt(Config::alpha); //

        //						cout<<cur->id<<endl;
        //	System.out.println(n+": "+ rea);
        //	double rea = valInLastLevel.get(cur.id)/cur.in.size(); // modified 8.27, mutiply alpha later when merge two tours
        if (rea * maxhubScore > ITER_STOP)
        {
          if (valInThisLevel.find(n->id) == valInThisLevel.end())
          {
            valInThisLevel[n->id] = rea;
            if (n->in.size() > 0 && !n->isHub)
              newExpNodes.push_back(n);
          }

          else
            valInThisLevel[n->id] = valInThisLevel[n->id] + rea;
        }
      }
    }

    inSim.set(length, valInThisLevel);
    expNodes = newExpNodes;
    //newExpNodes.clear();

    valInLastLevel = valInThisLevel;
    //valInThisLevel.clear();

    length++;
  }
  //	System.out.println("Remove empty length for node " + q.id);

  for (simit = simmap.begin(); simit != simmap.end();)
  {
    if (simit->second.size() == 0)
    {
      //			System.out.println("No such length in Insim " + l);
      simit = simmap.erase(simit);
    }
    else
    {
      simit++;
    }
  }
}

int Graph::numNodes()
{
  return nodes.size();
}

Node &Graph::getNode(int id)
{
  if (nodes.find(id) == nodes.end())
    nodes[id] = Node(id);
  return nodes[id];
}

vector<Node *> Graph::getNodes()
{
  vector<Node *> no;
  for (auto &it : nodes)
    no.push_back(&(it.second));
  return no;
}

bool Graph::containsNode(int id)
{
  return nodes.find(id) != nodes.end();
}

Graph::Graph(const Graph &Graph)
{
  this->nodes = Graph.nodes;
  this->hubs = Graph.hubs;
}
int Graph::findNode(int index)
{
  for (auto &n : nodes){
    if (n.second.index == index)
      return n.second.id;
  }
  return -1;
}

void Graph::init()
{
  for (auto &n : nodes)
    n.second.initOutEdgeWeight();
}

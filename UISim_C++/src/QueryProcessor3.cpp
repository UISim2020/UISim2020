/*
 * QueryProcessor3.cpp
 *
 *  Created on: 2019��3��16��
 *      Author: yichen_shen
 */

#include <QueryProcessor3.h>
#include <iostream>
#include <unordered_map>
#include <ctime>
double QueryProcessor3::checkMeetigNodeImportance(PrimeSim &inSim, int mid)
{
  double sum = 0.0;
  int count = 0;
  for (int length = 1; length < inSim.getMap().size(); length++)
  {
    unordered_map<int, double> &tmp = inSim.getMap()[length];
    if (tmp.find(mid) == tmp.end())
      continue;

    double rea = inSim.getMap()[length][mid];
    sum += rea;
    count++;
  }
  return sum / count;
}

QueryProcessor3::QueryProcessor3(Graph &graph)
{
  this->graph = &graph;
}

PrimeSim QueryProcessor3::graphExp(Node &q, string graphType)
{

  PrimeSim sim;
  graph->resetPrimeG();
  // int typeIndicator = outGraph? 1:0;
  double expansion = Config::eta;
  double expansiondemical = expansion - (float)(int)expansion;
  if (expansiondemical == 0)
  {
    expansiondemical = 1;
  }

  //		if (q.isHub){
  if (false)
  { // change q.isHub to false, so that it will not use precomputation; 4/17 @fw
    sim.loadFromDisk(q.id, graphType);
    // System.out.println("@@@@@QP line 54: print the sim loaded from disk");
    // PrintInfor.printDoubleMap(sim.getMap(),
    // "length-> <node, score>");
  }
  else
  {
    if (graphType == "out")
      graph->computeOutPrimeSim(q, 1, sim);
    else if (graphType == "in")
      graph->computeInPrimeSim(q, 1, sim);
    else
    {
      cout << "Type of prime graph should be either out or in.";
      exit(0);
    }
  }
  // System.out.println("expansion= " + expansion);
  //		System.out.println("meeting nodes in prime " + gType + "-graph: "
  //				+ sim.getMeetingNodes());

  if (expansion == 0 || sim.numHubs() == 0)
    return sim; // for primeInG, always expand for eta iterations

  // else: expand the out graph

  PrimeSim expSim = sim.duplicate();

  if (graphType == "in")
    expSim.addMeetingNodes(sim.getMeetingNodes());
  // System.out.println("QP#####: meeting nodes in prime subG:");
  // for(int x : expSim.getMeetingNodes())
  // System.out.print(x + " ");
  // System.out.println();

  unordered_map<int, unordered_map<int, double>> borderHubsScore; // hub->(length,value)

  // extracting borderHubs information
  for (auto &length : sim.getMap())
  {
    //added 8-27
    if (length.first == 0)
      continue; //don't expand the query node if itself is a hub
    for (auto &nid : sim.getMap()[length.first])
    {
      Node &node = graph->getNode(nid.first);
      //added 8-27
      //if(node==q) continue; q should also be expanded, it can affect the reachability of other nodes, just s(q,q) wouldn't be affected
      if (node.isHub)
      {
        // store the reachability to hub
        if (borderHubsScore.find(nid.first) == borderHubsScore.end())
        {
          borderHubsScore[nid.first] = unordered_map<int, double>();
        }
        if (borderHubsScore[nid.first].find(length.first) == borderHubsScore[nid.first].end())
        {
          borderHubsScore[nid.first][length.first] = sim.getMap()[length.first][nid.first];
        }
        else
        {
          cout << "shouldn't go to here.";
          double old_value = borderHubsScore[nid.first][length.first];
          borderHubsScore[nid.first][length.first] = old_value + sim.getMap()[length.first][nid.first];
        }
      }
    }
  }

  // recursively adding outG of hubs
  //int i = 0;

  while (expansion > 0)
  {

    expansion = expansion - 1;
    //			i++;
    //			if (gType == "out")
    //				System.out.println("@@@Iteration " + i);
    // expansion--;
    unordered_map<int, unordered_map<int, double>> borderHubsNew;
    if (borderHubsScore.size() == 0)
      return expSim;
    int p = 0;
    int maxnode = (int)borderHubsScore.size() * expansiondemical;
    for (auto &hid : borderHubsScore)
    {
      //add expanding threshold for hubs: Config.delta
      //	double hubScore = 0;
      double maxHubScore = 0;
      if (p > maxnode)
        break;
      p++;
      for (auto &len : hid.second)
      {
        double current_hubscore = hid.second[len.first];
        if (current_hubscore > maxHubScore)
        {
          maxHubScore = current_hubscore;
        }
        //	hubScore += current_hubscore;
      }

      //	if(hubScore<Config.delta)
      //		continue;
      //end. 2/18/2015fw
      PrimeSim nextSim;
      //commented the next line to prevent using hub scores 04/17
      //				nextSim.loadFromDisk(hid, graphType);

      // modify start 04/17 to do online computation even if it is hub
      Node &h = graph->getNode(hid.first);

      if (graphType == "out")
        graph->computeOutPrimeSim(h, maxHubScore, nextSim);
      else if (graphType == "in")
        graph->computeInPrimeSim(h, maxHubScore, nextSim);

      //modify end
      //	System.out.println(graphType+" Graph of hub: " + hid);
      //	System.out.println(nextSim.getMap());
      if (graphType == "in")
        expSim.addMeetingNodes(nextSim.getMeetingNodes());

      expSim.addFrom(nextSim, hid.second); // expand
                                           // graph
      // PrintInfor.printDoubleMap(expSim.getMap(),
      // "&&&=&=&=&& Expanded graph out sim");

      if (expansion > 0)
      {
        //store border hubs in nextSim
        for (int i = 0; i < nextSim.numHubs(); i++)
        {
          int newHub = nextSim.getHubId(i);
          for (int l = 1; l < nextSim.getMap().size(); l++)
          {
            unordered_map<int, double> &tmp = nextSim.getMap()[l];
            if (tmp.find(newHub) != tmp.end())
            {

              double addScore = nextSim.getMap()[l][newHub];

              //set borderHubsNew
              if (borderHubsNew.find(newHub) == borderHubsNew.end())
                borderHubsNew[newHub] = unordered_map<int, double>();
              auto &tmp = borderHubsNew[newHub];
              for (auto &oldLen : hid.second)
              {
                double oldScore = hid.second[oldLen.first];
                double existScore;
                if (tmp.find(l + oldLen.first) == tmp.end())
                  existScore = 0.0;
                else
                  existScore = tmp[l + oldLen.first];
                tmp[l + oldLen.first] = existScore + oldScore * addScore;
              }
            }
          }
        }

      } //end if

    } //end for
    //			if (borderHubsNew.size() == 0)
    //				return expSim;

    borderHubsScore = borderHubsNew;
  }
  return expSim;
}

double QueryProcessor3::query(Node &q1, Node &q2)
{
  if (q1.id == q2.id)
    return 1;

  double result = 0;

  //		System.out.println("Process query: " + q.id);

  PrimeSim inSim1 = graphExp(q1, "in");
  PrimeSim inSim2 = graphExp(q2, "in");

  // test:
  //	System.out.println("=====QP Line149: inGraph of query " + q.id);

  //	System.out.println(inSim.getMap());

  if (inSim1.getMeetingNodes().size() == 0 || inSim2.getMeetingNodes().size() == 0)
  {
    result = 0;
    return result;
  }
  PrimeSim smallPS = inSim1.numLength() < inSim2.numLength() ? inSim1 : inSim2;
  PrimeSim bigPS = inSim1.numLength() < inSim2.numLength() ? inSim2 : inSim1;

  for (auto &length : smallPS.getMap())
  {
    if (bigPS.getMap().find(length.first) == bigPS.getMap().end())
      continue;

    unordered_map<int, double> small_node_score_map = smallPS.getMap()[length.first].size() < bigPS.getMap()[length.first].size() ? smallPS.getMap()[length.first] : bigPS.getMap()[length.first];
    unordered_map<int, double> big_node_score_map = smallPS.getMap()[length.first].size() < bigPS.getMap()[length.first].size() ? bigPS.getMap()[length.first] : smallPS.getMap()[length.first];

    for (auto &nid : small_node_score_map)
    {
      if (big_node_score_map.find(nid.first) == big_node_score_map.end())
        continue;
      double rea = small_node_score_map[nid.first] * big_node_score_map[nid.first]; //multiply alpha here
      result += rea;
    }
    // System.out.println("$$$$$RESULT: Length: " +length +
    // " meeting node: " + node);
    // for (Map.Entry<Integer, Double> v : result.entrySet())
    // System.out.println("<" + v.getKey() + " " + v.getValue()
    // +" >");
  }
  //			System.out.println("Results after merging with: "+mid);
  //			System.out.println(result);

  return result;
}

QueryProcessor3::~QueryProcessor3()
{
  // TODO Auto-generated destructor stub
}

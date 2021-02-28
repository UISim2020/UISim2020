/*
 * Config.cpp
 *
 *  Created on: 2019��3��13��
 *      Author: yichen_shen
 */

#include "Config.h"


    int    Config::numIterations				= 30;
    int    Config::numHubs					= 2000;
    double Config::epsilon                    = 1E-8;
    double Config::clip                       = 1E-3;
    double Config::delta		                = 1E-4;
    //int	 Config::numHubsPerIter				= 10;
    double   Config::eta		                = 0;
    double Config::alpha						= 0.75;
    double Config::sqrt_alpha					= 0.86602540378;
    int	 Config::numClusters				= 3;
    int	 Config::maxClusterFaults			= 10;
    int	 Config::numRepetitions				= 1;
    string Config::file_sep = "/";
//    string Config::nodeFile					= "/home/teenichange/FastSR/dataset/wiki-nodes";
//    string Config::edgeFile					= "/home/teenichange/FastSR/dataset/wiki-edges";
//    string Config::indexDir				    = "/home/teenichange/FastSR/dataset/wiki-index";
    string Config::nodeFile					= "/home/teenichange/FastSR/dataset/enwiki-2013/process/nodes";
    string Config::edgeFile					= "/home/teenichange/FastSR/dataset/enwiki-2013/process/edges";
    string Config::indexDir				    = "/home/teenichange/FastSR/dataset/enwiki-2013/enwiki-2013-index";
    string Config::clusterDir				 = "";
    string Config::communityFile				= "";
    string Config::outputDir		            = "/home/teenichange/FastSR/dataset/enwiki-2013/result/";
    string Config::queryFile      		    = "/home/teenichange/FastSR/dataset/enwiki-2013/enwiki2013.query";
    string Config::hubType                    = "indeg";

    int Config::resultTop						= 50;
    int Config::hubTop						= 4000000;
    int Config::iterations                    =10;
    int Config::progressiveTopK				=100;
    int Config::depth							=5;
    double Config::stopRea					=1E-4;
	int Config::maxNode						=7000;

	int Config::correctionLevel				=1;

Config::Config() {
}

Config::~Config() {
}


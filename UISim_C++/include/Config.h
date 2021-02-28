/*
 * Config.h
 *
 *  Created on: 2019��3��13��
 *      Author: yichen_shen
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include<string>

using namespace std;

class Config {
public:
	 static int    numIterations;
	 static int    numHubs;
	 static double epsilon;
	 static string file_sep;
	 static double clip;
	 static double delta;
	// static int	 numHubsPerIter;
	 static double    eta;
	 static double alpha;
	 static double sqrt_alpha;
	 static int	 numClusters;
	 static int	 maxClusterFaults;
	 static int	 numRepetitions;

	 static string nodeFile;
	 static string edgeFile;
	 static string indexDir;
	 static string clusterDir;
	 static string communityFile;
	 static string outputDir;
	 static string queryFile;
	 static string hubType;

	 static int resultTop;
	 static int hubTop;
	 static int iterations;
	 static int progressiveTopK;
	 static int depth;
	static double stopRea;
	static int maxNode;
	static int correctionLevel;
	Config();
	virtual ~Config();
};

#endif /* CONFIG_H_ */

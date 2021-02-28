/*
 * IndexManager.h
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#ifndef INDEXMANAGER_H_
#define INDEXMANAGER_H_

#include<string>
#include "Config.h"
using namespace std;

class IndexManager {
public:
	IndexManager();
	virtual ~IndexManager();
	static string getIndexShallowDir();
	static string getIndexPPVCountInfoFilename(bool isOut);
	static string getIndexDeepDir();
	static string getHubNodeFile();
	static string getPrimeSimFilename(int nodeId, bool isOut);

	static void mkSubDirShallow();
	static void mkSubDirDeep();
};

#endif /* INDEXMANAGER_H_ */

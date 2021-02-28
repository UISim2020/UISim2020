/*
 * IndexManager.cpp
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#include "IndexManager.h"
#include "Trim.h"
#include <fstream>
IndexManager::IndexManager() {
	// TODO Auto-generated constructor stub

}

IndexManager::~IndexManager() {
	// TODO Auto-generated destructor stub
}

string IndexManager::getIndexShallowDir() {
	string path = Config::indexDir;
	if (!endswith(path, Config::file_sep))
		path +=  Config::file_sep;

	path += Config::hubType +  Config::file_sep;
	return path;
}

string IndexManager::getIndexPPVCountInfoFilename(bool isOut) {
	if (isOut)
	    return getIndexShallowDir()+ to_string(Config::numHubs)+"countInfo_outGraph";
	  else
	   return getIndexShallowDir() + to_string(Config::numHubs) + "countInfo_inGraph";
}


string IndexManager::getIndexDeepDir() {

	return getIndexShallowDir() + to_string(Config::numHubs) + Config::file_sep;
	    }

string IndexManager::getHubNodeFile() {
	return getIndexShallowDir() + "hubs";
}

string IndexManager::getPrimeSimFilename(int nodeId, bool isOut) {
	if(isOut)
		return getIndexDeepDir() +"out/"+ to_string(nodeId);
	else

		return getIndexDeepDir() + "in/"+ to_string(nodeId);
}
void IndexManager::mkSubDirShallow() {
    string command;
    command = "mkdir -p " + getIndexShallowDir();
    system(command.c_str());
}

void IndexManager::mkSubDirDeep() {
    string command;
    command = "mkdir -p " + getIndexDeepDir();
    system(command.c_str());
}

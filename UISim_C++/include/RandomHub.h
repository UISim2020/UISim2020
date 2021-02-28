/*
 * RandomHub.h
 *
 *  Created on: 2019Äê3ÔÂ16ÈÕ
 *      Author: yichen_shen
 */

#ifndef RANDOMHUB_H_
#define RANDOMHUB_H_
#include <HubSelection.h>
class RandomHub : public HubSelection {
protected:
	void fillNodes();
public:
	RandomHub();
	RandomHub(string nodeFile, string edgeFile);
	virtual ~RandomHub();
};

#endif /* RANDOMHUB_H_ */

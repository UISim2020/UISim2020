/*
 * InDegHub.h
 *
 *  Created on: 2019Äê3ÔÂ16ÈÕ
 *      Author: yichen_shen
 */

#ifndef INDEGHUB_H_
#define INDEGHUB_H_

#include <HubSelection.h>

class InDegHub: public HubSelection {
	protected:
	double pagerankPow;
	double inDegPow;
	void fillNodes();
public:
	InDegHub(string nodeFile, string edgeFile) ;
	virtual ~InDegHub();
};

#endif /* INDEGHUB_H_ */

/*
 * ttbarB.h
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#ifndef ttbarB_H_
#define ttbarB_H_

#include "interface/basicAnalyzer.h"
#include "interface/sampleCollection.h"
#include "classes/DelphesClasses.h"


class ttbarB: public d_ana::basicAnalyzer{
public:
	ttbarB():d_ana::basicAnalyzer(){}
	~ttbarB(){}


private:
	void analyze(size_t id);

	void postProcess();
};





#endif /* ttbarB_H_ */

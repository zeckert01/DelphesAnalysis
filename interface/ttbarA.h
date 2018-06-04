/*
 * ttbarA.h
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#ifndef ttbarA_H_
#define ttbarA_H_

#include "interface/basicAnalyzer.h"
#include "interface/sampleCollection.h"
#include "classes/DelphesClasses.h"


class ttbarA: public d_ana::basicAnalyzer{
public:
	ttbarA():d_ana::basicAnalyzer(){}
	~ttbarA(){}


private:
	void analyze(size_t id);

	void postProcess();
};





#endif /* ttbarA_H_ */

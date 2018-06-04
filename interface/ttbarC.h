/*
 * ttbarC.h
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#ifndef ttbarC_H_
#define ttbarC_H_

#include "interface/basicAnalyzer.h"
#include "interface/sampleCollection.h"
#include "classes/DelphesClasses.h"


class ttbarC: public d_ana::basicAnalyzer{
public:
	ttbarC():d_ana::basicAnalyzer(){}
	~ttbarC(){}


private:
	void analyze(size_t id);

	void postProcess();
};





#endif /* ttbarC_H_ */

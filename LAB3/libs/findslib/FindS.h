//==============================================================================
// Name        : FindS.h
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 12/08/2019
// Description : The FIND-S algorithm (chapter 2 [Mitchell, 1997])
//				 - written in C++, Ansi-style
//==============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#ifndef LIBS_FINDS_H
#define LIBS_FINDS_H

using namespace std;

namespace DPLKYL002 {

class HypothesisRepresentation {

public:

	// public members
	vector<string> vectAttributeConstraints;

	HypothesisRepresentation(vector<string> vectAttributeConstraints) :
			vectAttributeConstraints(vectAttributeConstraints) {

	}
	;
};

class TrainingExample {

public:

	// public members
	HypothesisRepresentation hypothesisRepresentation;

	bool targetConcept;

	TrainingExample(HypothesisRepresentation hypothesisRepresentation,
			bool targetConcept) :
			hypothesisRepresentation(hypothesisRepresentation), targetConcept(
					targetConcept) {

	}
	;
};

class FindS {

private:

	// private members
	vector<DPLKYL002::TrainingExample> vectTrainingExamples;

	vector<DPLKYL002::HypothesisRepresentation> vectHypothesisRepresentations;

	ofstream outputFile;

public:

	// public members
	void setupTrainingExamples(string inputFileName);

	void setupHypothesesRepresentation(vector<string> vectAttributeConstraints);

	void findS();

};

}

#endif


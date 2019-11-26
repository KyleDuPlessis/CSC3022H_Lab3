//==============================================================================
// Name        : Driver.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 12/08/2019
// Description : The FIND-S algorithm (chapter 2 [Mitchell, 1997])
//				 - written in C++, Ansi-style
//==============================================================================

#include "FindS.h"

// main function
int main(int argc, char * argv[]) { // argc and argv values passed into main

	DPLKYL002::FindS f;

	// setup using the training examples from table 1 stored in inputData.txt
	f.setupTrainingExamples("inputData.txt");

	// setup hypothesis representation using initial constraints - specifying the values of the six attributes
	f.setupHypothesesRepresentation( { "Sunny", "Warm", "Normal", "Strong",
			"Warm", "Same" });

	f.findS();

	return 0;

}

//==============================================================================
// Name        : FindS.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 12/08/2019
// Description : The FIND-S algorithm (chapter 2 [Mitchell, 1997])
//				 - written in C++, Ansi-style
//==============================================================================

#include "FindS.h"

#include <iomanip>

void DPLKYL002::FindS::setupTrainingExamples(string inputFileName) {

	// setup training examples
	vectTrainingExamples = vector<DPLKYL002::TrainingExample>();

	// load training examples from table 1 stored in inputData.txt
	ifstream iFile = ifstream(inputFileName);

	bool targetConcept;

	string input, constraint, targetConceptConstraint;

	// process each line from text file
	while (getline(iFile, input)) {

		stringstream line;

		line << input;

		vector<string> vectAttributeConstraints;

		for (int k = 0; k < 6; ++k) {

			line >> constraint;

			vectAttributeConstraints.push_back(constraint);

		}

		line >> constraint;

		targetConcept = (constraint == "Yes");

		vectTrainingExamples.push_back(

				DPLKYL002::TrainingExample(

						DPLKYL002::HypothesisRepresentation(
								vectAttributeConstraints), targetConcept));

	}

	outputFile = ofstream("answers.txt");

	outputFile << "\t\t\t~~~~~~~~ Input training examples ~~~~~~~~" << endl
			<< endl;

	outputFile << "Example   " << "Sky     " << "AirTemp    "
			<< "Humidity        " << "Wind       " << "Water    "
			<< "Forecast  " << "EnjoySport" << endl;

	int count = 0;

	for (auto k = vectTrainingExamples.begin(); k != vectTrainingExamples.end();
			++k) {
		auto n = (k->hypothesisRepresentation.vectAttributeConstraints);

		count++;

		outputFile << count << setw(12);

		for (auto m = n.begin(); m != n.end(); ++m) {

			outputFile << *m << setw(12);

		}

		if (k->targetConcept == 1) {

			targetConceptConstraint = "Yes";

		} else {

			targetConceptConstraint = "No";

		}

		outputFile << targetConceptConstraint << endl;
	}

	outputFile << endl;

	iFile.close();

}

void DPLKYL002::FindS::setupHypothesesRepresentation(
		vector<string> vectAttributeConstraints) {

	// setup all hypotheses
	vectHypothesisRepresentations =
			vector<DPLKYL002::HypothesisRepresentation>();

	// each hypothesis consists of a conjunction of constraints on instance attributes
	// (i.e. a vector of six constraints)
	vectHypothesisRepresentations.push_back(
			DPLKYL002::HypothesisRepresentation(vectAttributeConstraints));

}

void DPLKYL002::FindS::findS() {

	// general-to-specific ordering of hypotheses
	DPLKYL002::HypothesisRepresentation hypothesisRepresentation =
			vectHypothesisRepresentations[0];
	bool moreSpecificThan;

	for (auto k = vectHypothesisRepresentations.begin();
			k != vectHypothesisRepresentations.end(); ++k) {

		DPLKYL002::HypothesisRepresentation tempHypothesisRepresentation = *k;

		moreSpecificThan = true;

		for (unsigned int n = 0;
				n < tempHypothesisRepresentation.vectAttributeConstraints.size();
				++n) {

			if (tempHypothesisRepresentation.vectAttributeConstraints[n] == "?"
					&& hypothesisRepresentation.vectAttributeConstraints[n]
							!= "?") {

				moreSpecificThan = false;

				break;

			}

			if (hypothesisRepresentation.vectAttributeConstraints[n]
					!= tempHypothesisRepresentation.vectAttributeConstraints[n]
					&& hypothesisRepresentation.vectAttributeConstraints[n]
							!= "?"
					&& tempHypothesisRepresentation.vectAttributeConstraints[n]
							!= "?") {

				moreSpecificThan = false;

				break;

			}

		}

		if (moreSpecificThan) {

			hypothesisRepresentation = tempHypothesisRepresentation;

		}

	}

	auto m = hypothesisRepresentation.vectAttributeConstraints;

	outputFile << "\t\t\t~~~~~~~~ The FIND-S algorithm ~~~~~~~~" << endl << endl;

	outputFile << "h0 = <0, 0, 0, 0, 0, 0>" << endl;

	int countHypotheses = 0;

	// h is initialised to the most specific hypothesis in H
	// for each positive training instance x
	for (auto positiveTrainingInstance = vectTrainingExamples.begin();
			positiveTrainingInstance != vectTrainingExamples.end();
			++positiveTrainingInstance) {

		countHypotheses++;

		// ignore each negative training instance
		if (!positiveTrainingInstance->targetConcept) {

			m = hypothesisRepresentation.vectAttributeConstraints;

			outputFile << "h" << countHypotheses << " = <";

			for (auto p = m.begin(); p != m.end(); ++p) {

				outputFile << *p;

				if (p != (m.end() - 1)) {

					outputFile << ", ";

				}

			}

			outputFile << ">" << endl;

			continue;

		}

		// for each attribute constraint in h
		for (unsigned int k = 0;
				k < hypothesisRepresentation.vectAttributeConstraints.size();
				++k) {

			// if the constraint is satisfied by x
			// then do nothing
			if (hypothesisRepresentation.vectAttributeConstraints[k]
					== positiveTrainingInstance->hypothesisRepresentation.vectAttributeConstraints[k]
					|| hypothesisRepresentation.vectAttributeConstraints[k]
							== "?") {

				continue;

			}

			// else replace the attribute constraint in h by the next more general constraint that is satisfied by x
			hypothesisRepresentation.vectAttributeConstraints[k] = "?";

		}

		m = hypothesisRepresentation.vectAttributeConstraints;

		// output hypothesis h
		outputFile << "h" << countHypotheses << " = <";

		for (auto p = m.begin(); p != m.end(); ++p) {

			outputFile << *p;

			if (p != (m.end() - 1)) {

				outputFile << ", ";

			}

		}

		outputFile << ">" << endl;

	}

	outputFile << endl;
	outputFile << "\t\t\t~~~~~~~~ Learned the target concept ~~~~~~~~" << endl << endl;

	m = hypothesisRepresentation.vectAttributeConstraints;

	outputFile << "<";

	for (auto t = m.begin(); t != m.end(); ++t) {

		outputFile << *t;

		if (t != (m.end() - 1)) {

			outputFile << ", ";

		}

	}

	outputFile << ">" << endl << endl;

	outputFile << "Therefore, only one additional training example (i.e. example 5) is required to exactly learn the above target concept." << endl;

	outputFile.close();

	cout << "answers.txt written successfully" << endl;

}


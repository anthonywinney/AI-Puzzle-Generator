#include "PuzzleGenerator.h"
#include <limits>
#include <ctime>

using namespace std;

PuzzleGenerator::PuzzleGenerator(int _nRows, int _nColumns, int _minVal, int _maxVal)
	: nRows(_nRows), nColumns(_nColumns), minVal(_minVal), maxVal(_maxVal)
{
}

Puzzle PuzzleGenerator::GeneratePuzzle()
{

	srand(time(0));

	timer.StartTimer();
	maxtime = 59.9; // To make sure we don't exceed a minute

	double random_walk_time = 59.9; // 5 seconds.

	return RandomWalk(random_walk_time); // Do a random walk for some time and return the solution.
}

Puzzle PuzzleGenerator::RandomWalk(double timelimit)
{
	// A very simple function that start at a random configuration and keeps randomly modifying it
	// until t hits the time limit. Returns the best solution found so far.

	// This can be uncommented to compare the results of the AI model with the results of randomly
	// generating puzzles and returning the most difficult one.

	/*Puzzle p(nRows, nColumns, minVal, maxVal);	// Generate a random puzzle with the specified values.
	int bestInitialValue = p.GetValue();
	for(int i = 0; i < 20; i++){
		Puzzle temp = Puzzle(nRows, nColumns, minVal, maxVal);
		int tempValue = temp.GetValue();
		if(temp.HasSolution() && tempValue > bestInitialValue){
			p = temp;
			bestInitialValue = tempValue;
		}
	}*/

	Puzzle p(nRows, nColumns, minVal, maxVal);

	// Keep track of the best puzzle found so far (and its value).
	Puzzle bestPuzzle = p;
	Puzzle initialPuzzle = p;
	Puzzle currentPuzzle = p;
	Puzzle bestPuzzleOverall = p;

	int bestValueOverall = 0;
	int bestValue = 0;

	printf("Starting value: %d", bestValue);

	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();

	// Loop until we hit the time limit.

	int checkIf1 = 1;

	int goodSuccessorIndex = 0;
	int numRestart = timelimit + 1;

	for (int restart = 1; restart <= numRestart && t.GetElapsedTime() < timelimit - 0.1; restart++)
	{

		p = Puzzle(nRows, nColumns, minVal, maxVal); // Generate a random puzzle with the specified values.
		int bestInitialValue = p.GetValue();
		for (int i = 0; i < 20; i++)
		{
			Puzzle temp = Puzzle(nRows, nColumns, minVal, maxVal);
			int tempValue = temp.GetValue();
			if (temp.HasSolution() && tempValue > bestInitialValue)
			{
				p = temp;
				bestInitialValue = tempValue;
			}
		}

		bestPuzzle = p;
		initialPuzzle = p;
		currentPuzzle = p;

		bestValue = bestInitialValue;

		// Using a successors based model -- altering one piece of each temporary puzzle and picking the best of the successors

		vector<vector<Puzzle>> goodSuccessors;
		vector<vector<int>> goodSuccessorWeights;
		goodSuccessorIndex = 0;

		while (t.GetElapsedTime() < restart * timelimit / (double) numRestart - 0.1) // To make sure that we don't exceed the time limit, we stop just before we hit the time limit.
		{

			// Generate a successor of p by randomly changing the value of a random cell
			// (since we are doing a random walk, we just replace p with its successor).

			vector<Puzzle> successors;
			vector<Puzzle> goodSuccessors1;
			vector<Puzzle> goodSuccessors2;
			vector<int> goodSuccessorWeights1;
			vector<int> goodSuccessorWeights2;

			int value = bestPuzzle.GetValue();

			for (int i = 0; i < 50; i++)
			{
				successors.push_back(bestPuzzle.GetRandomSuccessor());
			}

			int bestTempValue = value;
			int totalTempDifference = 0;

			// Going through successors until we get to one with a solution

			for (int i = 0; i < successors.size(); i++)
			{
				Puzzle currentSuccessor = successors[i];

				if (!currentSuccessor.HasSolution())
				{
					continue;
				}
				else
				{
					int tempValue = currentSuccessor.GetValue();

					if (tempValue > bestValue)
					{

						totalTempDifference += (tempValue - bestValue);

						goodSuccessors2.push_back(currentSuccessor);
						goodSuccessorWeights2.push_back(totalTempDifference);
					}
					if (tempValue > bestValueOverall)
					{
						bestPuzzleOverall = currentSuccessor;
						bestValueOverall = tempValue;
					}
				}
			}

			int randomIndex = (rand() % (totalTempDifference + 1));
			
			// Adding valuable successors or dumping the current path if there are none

			if (goodSuccessors2.size() > 0)
			{
				goodSuccessors.push_back(goodSuccessors2);
				goodSuccessorWeights.push_back(goodSuccessorWeights2);
				goodSuccessorIndex++;
			}
			else
			{
				if(goodSuccessorIndex == 0 || goodSuccessorIndex == 1){
					continue;
				}
				goodSuccessorIndex--;
			}

			vector<Puzzle> toEvaluateSuccessors = goodSuccessors[goodSuccessorIndex - 1]; 
			vector<int> toEvaluateWeights = goodSuccessorWeights[goodSuccessorIndex - 1];

			for (int k = 0; k < toEvaluateSuccessors.size(); k++)
			{

				if (randomIndex <= toEvaluateWeights[k])
				{
					bestPuzzle = toEvaluateSuccessors[k];
					bestValue = bestPuzzle.GetValue();
					break;
				}
			}

			if (goodSuccessors2.size() > 0)
			{
				goodSuccessors1 = goodSuccessors2;
				goodSuccessorWeights1 = goodSuccessorWeights2;
			}
			
			checkIf1++;
		}
	}

	return bestPuzzleOverall;

}

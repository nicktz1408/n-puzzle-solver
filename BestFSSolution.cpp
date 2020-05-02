#pragma once

#include <utility>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <functional>
using namespace std;

#include "SolutionStrategy.cpp"


class BestFSSolution : public SolutionStrategy
{
public:
	/*
	* Constructor
	* @aBoard  -> the initial board
	* @aWidth  -> the width of the board
	* @aHeight -> the height of the board
	*/
	BestFSSolution(vector <vector <int>> &aBoard, int &aWidth, int &aHeight) : SolutionStrategy(aBoard, aWidth, aHeight) {}

	/*
	* This method generates the solution of the puzzle to be backtracked afterwards
	*/
	void solve()
	{
		/*
		Form of state:
		  *first -> evaluation function of of current state,
		  *second -> a pair which consists of:
		    *first -> board of current state,
			*second -> board of parent state
		*/
		priority_queue <pair <int, pair <vector <vector <int>>, vector <vector <int> > > >,
		vector <pair <int, pair <vector <vector <int> >, vector <vector <int> > > > >, //container of the priority queue/heap
		greater <pair <int, pair <vector <vector <int> >, vector <vector <int> > > > > > frontier; //instructs it to have the state with the min eval function on top

		frontier.push({ evaluateState(initialState), { initialState, getEmptyBoard() } });

		while (!frontier.empty())
		{
			vector <vector <int> > activeState = frontier.top().second.first,
				parentOfActiveState = frontier.top().second.second;
			frontier.pop();

			if (!visited.exists(activeState)) //not visited before
			{
				visited.add(activeState, parentOfActiveState);

				if (activeState == getFinalState())
					return;

				for (auto child : expandChildren(activeState))
				{
					int childEval = evaluateState(child);

					frontier.push({ childEval, { child, activeState } });
				}
			}
		}
	}

private:
	/*
	* Utility method that calculates the evaluation function of a state
	* @board -> the desired state
	* @returns the evaluation score
	*
	* In this example, I chose the eval function to be the aggegrate sum of the distances between the current 
	* position and the position in the final state of each cell
	*/
	int evaluateState(vector <vector <int> > &board)
	{
		int eval = 0;

		for(int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
			{
				int currVal = board[i][j];

				pair <int, int> optimalLocation = getLocation(currVal);

				int manhattanDist = abs(optimalLocation.first - i) + abs(optimalLocation.second - j);
				eval += manhattanDist;
			}

		return eval;
	}
};
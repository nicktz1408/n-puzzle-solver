#pragma once

#include <utility>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

#include "SolutionStrategy.cpp"


class DFSSolution: public SolutionStrategy
{
public:
	/*
	* Constructor
	* @aBoard  -> the initial board
	* @aWidth  -> the width of the board
	* @aHeight -> the height of the board
	*/
	DFSSolution(vector <vector <int> > &aBoard, int &aWidth, int &aHeight) : SolutionStrategy(aBoard, aWidth, aHeight) {}

	/*
	* This method generates the solution of the puzzle to be backtracked afterwards
	*/
	void solve()
	{
		/*
		Form of state:
		  *first -> board of current state,
		  *second -> board of parent state
		*/
		stack <pair <vector <vector <int>>, vector <vector <int> > > > frontier;

		frontier.push({ initialState, getEmptyBoard() });

		while (!frontier.empty())
		{
			vector <vector <int> > activeState = frontier.top().first, 
				parentOfActiveState = frontier.top().second;
			frontier.pop();

			if (!visited.exists(activeState)) //not visited before
			{
				visited.add(activeState, parentOfActiveState);

				if (activeState == getFinalState())
					return;

				for (auto child : expandChildren(activeState))
					frontier.push({ child, activeState });
			}
		}
	}
};
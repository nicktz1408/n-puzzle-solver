#pragma once

#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#include "ClosedSet.cpp"

class SolutionStrategy
{
public:
	SolutionStrategy()
	{

	}

	/*
	* Constructor
	* @aBoard  -> the initial board
	* @aWidth  -> the width of the board
	* @aHeight -> the height of the board
	*/
	SolutionStrategy(vector <vector <int> > &aBoard, int &aWidth, int &aHeight) :
		initialState(aBoard),
		width(aWidth),
		height(aHeight)
	{

	}

	virtual void solve() = 0; //virtual function - used on the subclasses

	/*
	* Method to backtrack the visited (aka closed) set and return the solution string
	*/
	string backtrack()
	{
		vector <vector <int> > finalState = getFinalState();

		string movesSequence = "";

		backtrackUtility(finalState, movesSequence);
		return movesSequence;
	}

protected:
	ClosedSet visited;
	vector <vector <int> > initialState;
	int size;
	int width;
	int height;

	/*
	* Utility method to return the solved  board
	*/
	vector <vector <int> > getFinalState()
	{
		vector <vector <int> > sol(height, vector <int>(width));

		int cnt = 1;

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				if (i == height - 1 && j == width - 1) //cell at the right-bottom corner
					sol[i][j] = 0;

				else
					sol[i][j] = cnt++;
			}

		return sol;
	}

	/*
	* Utility method to expand the children of a given state
	* @state -> our state
	* @returns a vector with all the child states
	*/
	vector <vector <vector <int> > > expandChildren(vector <vector <int> > &state)
	{
		pair <int, int> emptyPos = locateEmptyPosition(state);
		vector <vector <vector <int> > > children(0);

		//-+-
		//+*+
		//-+-
		//get all cells denoted by a +, where * is the empty cells
		for (int i = max(0, emptyPos.first - 1); i <= min(height - 1, emptyPos.first + 1); i++) //rows
			for (int j = max(0, emptyPos.second - 1); j <= min(width - 1, emptyPos.second + 1); j++) { //cols 
				if (!(i == emptyPos.first && j == emptyPos.second) //not the empty cell itself
					&& (i == emptyPos.first || j == emptyPos.second)) //same row or col with the empty
				{
					vector <vector <int> > currChild = state;
					swap(currChild[i][j], currChild[emptyPos.first][emptyPos.second]);

					children.push_back(currChild);
				}
			}

		return children;
	}


	// -- UTILITY FUNCTIONS -- 
	/*
	* Backbone of the backtrack function
	* It works recursively
	*/
	void backtrackUtility(vector <vector <int> > &currState, string &movesSequence)
	{
		if (currState != initialState) //not initial state
		{
			vector <vector <int>> &prevState = visited.getParent(currState);
			backtrackUtility(prevState, movesSequence);

			char currMove = compareStates(currState, prevState);
			movesSequence += currMove;
		}
	}

	/*
	* Method that compares two adjacent states and returns the move that have been performed - used during the backtracking
	* @return a char that depends on how the empty cell moved:
	*         U -> moved up
	*         D -> moved down
	*         L -> moved left
	*         R -> moved rigth
	*/
	char compareStates(vector <vector <int> > &currState, vector <vector <int> > &prevState)
	{
		pair <int, int> currEmpty = locateEmptyPosition(currState),
			prevEmpty = locateEmptyPosition(prevState);

		if (currEmpty.first == prevEmpty.first) //same row (left/right)
		{
			if (currEmpty.second == prevEmpty.second + 1) //moved to the right
				return 'R';

			else
				return 'L';
		}

		else //same column (up/down)
		{
			if (currEmpty.first == prevEmpty.first + 1) //down
				return 'D';

			else
				return 'U';
		}
	}

	/*
	* @returns a pair with the row and column of the empty cell of a given state
	*/
	pair <int, int> locateEmptyPosition(vector <vector <int> > &state)
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				if (state[i][j] == 0)
					return{ i, j };
	}

	/*
	* @returns an empty board
	*/
	vector <vector <int> > getEmptyBoard()
	{
		return vector <vector <int> >(height, vector <int>(width, 0));
	}

	/*
	* @returns a pair with the row and column of the cell that contains the @val
	* @val -> the number to be traced
	*/
	pair <int, int> getLocation(int val) //get correct location of a number
	{
		if (val == 0)
			return{ size - 1, size - 1 };

		int row = (val - 1) / width,
			col = (val - 1) % width;

		return{ row, col };
	}
};
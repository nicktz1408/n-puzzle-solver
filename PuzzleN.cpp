#pragma once

#include <vector>
#include <string>
using namespace std;

#include "SolutionStrategy.cpp"
#include "DFSSolution.cpp"
#include "BFSSolution.cpp"
#include "BestFSSolution.cpp"
#include "AStarSolution.cpp"

enum Strategies { DFS, BFS, BestFS, AStar };

class PuzzleN
{
public:
	/*
	* Constructor
	* @aBoard  -> the initial board
	* @aWidth  -> the width of the board
	* @aHeight -> the height of the board
	*/
	PuzzleN(vector <vector <int>> &aBoard, int aWidth, int aHeight):
		board(aBoard),
		width(aWidth),
		height(aHeight)
	{
		
	}

	/*
	* Use this function to change the method of the solution (BFS, DFS, BestFS or AStar)
	* @type -> the type of the desired method. One of the following
	*          Strategies::DFS, Strategies::BFS, Strategies::BestFS, Strategies::AStar
	*/
	void setStrategy(Strategies type)
	{
		switch (type)
		{
		case Strategies::DFS:
			strategy = new DFSSolution(board, width, height);
			break;

		case Strategies::BFS:
			strategy = new BFSSolution(board, width, height);
			break;

		case Strategies::BestFS:
			strategy = new BestFSSolution(board, width, height);
			break;

		case Strategies::AStar:
			strategy = new AStarSolution(board, width, height);
			break;
		}
	}
	/*
	* Invoke this method to solve the puzzle
	* @returns a solution string which is a sequence of characters each one of those describes the next step:
	* U -> move the empty cell one step up
	* D -> move the empty cell one step down
	* L -> move the empty cell one step left
	* R -> move the empty cell one step right
	*/
	string solve()
	{
		strategy->solve();

		return strategy->backtrack();
	}

private:
	vector <vector <int>> board;
	int width;
	int height;
	SolutionStrategy *strategy;
};
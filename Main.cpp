#pragma once
//Test program
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "PuzzleN.cpp"

int main()
{
	cout << "Please provide the number of tests you would like to run: ";
	int testCases;
	cin >> testCases;

	for(int t = 1; t <= testCases; t++)
	{
		cout << "Test #" << t << ":" << endl;
		cout << "Please give the height and the width seperated with a space: ";
		int width, height;
		cin >> height >> width;

		vector <vector <int> > board(height, vector <int>(width));

		cout << "\nPlease describe the desired " << width * height << "-Puzzle board:" << endl;

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				cin >> board[i][j];

		PuzzleN myPuzzle(board, width, height);

		char ch;

		cout << "Solve using DFS? (y/n) ";
		cin >> ch;
		cout << endl;

		if (ch == 'Y' || ch == 'y')
		{
			myPuzzle.setStrategy(Strategies::DFS);
			string ans = myPuzzle.solve();
			cout << "Solution found with DFS: " << ans << endl;
		}

		cout << "Solve using BFS? (y/n) ";
		cin >> ch;
		cout << endl;

		if (ch == 'Y' || ch == 'y')
		{
			myPuzzle.setStrategy(Strategies::BFS);
			string ans = myPuzzle.solve();
			cout << "Solution found with BFS: " << ans << endl;
		}

		cout << "Solve using BestFS? (y/n) ";
		cin >> ch;
		cout << endl;

		if (ch == 'Y' || ch == 'y')
		{
			myPuzzle.setStrategy(Strategies::BestFS);
			string ans = myPuzzle.solve();
			cout << "Solution found with BestFS: " << ans << endl;
		}

		cout << "Solve using AStar? (y/n) ";
		cin >> ch;
		cout << endl;

		if (ch == 'Y' || ch == 'y')
		{
			myPuzzle.setStrategy(Strategies::AStar);
			string ans = myPuzzle.solve();
			cout << "Solution found with AStar: " << ans << endl;
		}
	}

	return 0;
}
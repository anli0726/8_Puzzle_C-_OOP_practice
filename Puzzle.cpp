// cpp file of Class Puzzel
#include <iostream>
#include "Puzzle.h"
using namespace std;

Puzzle::Puzzle(PuzzleState inputState) {
	setState(inputState);
}


void Puzzle::setState(PuzzleState inputState)
{
	state = inputState;
	string ID; 
	for (auto & row : inputState)
		for (auto & column : row)
			ID += to_string(column);
	stateID = ID;
}


Puzzle::PuzzleState Puzzle::getState() const {return state;}


string Puzzle::getID() const {return stateID;}


void Puzzle::printState() const
{	
	for (auto const & row : getState())
	{
		for (auto const & column : row)
			cout << column << " ";
		cout << endl;
	}
}


array<size_t, 2> Puzzle::getEmptyIdx() const
{
	array<size_t, 2> empty_idx;
	unsigned int i = 0;
	for (auto & row : state)
	{
		for (auto & column : row)
		{	
			if (column == 0)
			{
				empty_idx[0] = i / 3;
				empty_idx[1] = i % 3;
				break;
			}
			++i;
		}
	}
	
	return empty_idx;
}


void Puzzle::printEmptyIdx() const
{
	auto empty_idx = getEmptyIdx();
	cout << "The empty place is at (" 
		<< empty_idx[0] << "," 
		<< empty_idx[1] << ")" << endl;
}

Puzzle::PuzzleState	Puzzle::move(const char & action) const
{
	Puzzle future(state);
	auto empty_idx = getEmptyIdx();
	switch (action)
	{
		case 'u':
			if (empty_idx[0] != 0)
			{
				auto temp = future.state[empty_idx[0] - 1][empty_idx[1]];
				future.state[empty_idx[0] - 1][empty_idx[1]] 
					= future.state[empty_idx[0]][empty_idx[1]];
				future.state[empty_idx[0]][empty_idx[1]] = temp;
				--empty_idx[0];
				// cout << "move up" << endl;
			}
			break;
				
		case 'd':
			if (empty_idx[0] != 2)
			{
				auto temp = future.state[empty_idx[0] + 1][empty_idx[1]];
				future.state[empty_idx[0] + 1][empty_idx[1]] 
					= future.state[empty_idx[0]][empty_idx[1]];
				future.state[empty_idx[0]][empty_idx[1]] = temp;
				++empty_idx[0];
				// cout << "move down" << endl;
			}
			break;

		case 'l':
			if (empty_idx[1] != 0)
			{
				auto temp = future.state[empty_idx[0]][empty_idx[1] - 1];
				future.state[empty_idx[0]][empty_idx[1] - 1] 
					= future.state[empty_idx[0]][empty_idx[1]];
				future.state[empty_idx[0]][empty_idx[1]] = temp;
				--empty_idx[1];
				// cout << "move left" << endl;
			}
			break;

		case 'r':
			if (empty_idx[1] != 2)
			{
				auto temp = future.state[empty_idx[0]][empty_idx[1] + 1];
				future.state[empty_idx[0]][empty_idx[1] + 1] 
					= future.state[empty_idx[0]][empty_idx[1]];
				future.state[empty_idx[0]][empty_idx[1]] = temp;
				++empty_idx[1];
				// cout << "move right" << endl;
			}
			break;

		default: 
			break;
	}
	
	return future.state;
}



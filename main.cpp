// main file of 8-puzzle problem
#include <iostream>
#include <queue>
#include "Puzzle.h"
#include <unordered_map>
using namespace std;

// Rename the below data type to "StateLinkDict"
typedef unordered_map<string, string> StateLinkDict;

// Function prototype declearation
bool checkInputState(array<unsigned int, Puzzle::num_cols * Puzzle::num_rows> inputState);
Puzzle::PuzzleState InputState();
set<Puzzle::PuzzleState> FindAllStates(Puzzle puzzle);
bool FindState(Puzzle puzzle, Puzzle::PuzzleState target);
bool matchState(Puzzle::PuzzleState state1, Puzzle::PuzzleState state2);
pair<bool, StateLinkDict> FindPath(Puzzle puzzle, string target);
Puzzle::PuzzleState IDtoPuzzleState(string ID);
string PuzzleStatetoID(Puzzle::PuzzleState state);

int main()
{	
	Puzzle::PuzzleState init = InputState();
	Puzzle puzzle {init};
	cout << "The initial state is:\n";
	puzzle.printState();

	cout << "\nInput a target puzzle state:" << endl;
	Puzzle::PuzzleState target_state = InputState();
	Puzzle target {target_state};
	cout << "\nThe target state is:" << endl;
	target.printState();
	cout << endl;

	pair<bool, StateLinkDict> find_result = FindPath(puzzle, target.getID());
	if (find_result.first)
	{
		cout << "Find it!" << endl;
		Puzzle::PuzzleState child = target_state;
		while (!matchState(child, init))
		{
			Puzzle::PuzzleState parent = IDtoPuzzleState(
				find_result.second[PuzzleStatetoID(child)]);
			child = parent;
			target.setState(child);
			target.printState();
			cout << "The corresponding ID: " << PuzzleStatetoID(child) << "\n\n";
		}
	}
	else
		cout << "Cannot achieve the target state." << endl;
}


bool checkInputState(array<unsigned int, Puzzle::num_cols * Puzzle::num_rows> inputState)
{
	set<unsigned int> check(inputState.begin(), inputState.end());
	bool flag = false;

	if (check.size() != 9)
	{
		cout << "There exists repreated element in the input state!" << endl;
		flag = true;
	}
	
	if (check.find(0) == check.end())
	{
		cout << "There should have an empty palce on puzzle descibed as 0!" << endl;
		flag = true;
	}
	
	for (auto const & element : check) 
	{
		if (element >= 9)
		{
			flag = true;
			cout << "There is an element above 9!" << endl;
			break;
		}
	}

	return flag;
}


Puzzle::PuzzleState InputState()
{	
	array<unsigned int, Puzzle::num_cols * Puzzle::num_cols> inputSequence {};
	cout <<  "Enter the state from top-left to buttom-right: ";
	for (size_t i = 0; i < inputSequence.size(); ++i)
		cin >> inputSequence[i];

	cout << "The input sequence is: ";
	for (const auto & element: inputSequence)
		cout << element << " ";
	cout << endl;

	bool flag = checkInputState(inputSequence);

	while (flag)
	{	
		cout << "\nEnter the state from top-left to buttom-right: ";
		for (size_t i = 0; i < inputSequence.size(); ++i)
			cin >> inputSequence[i];
		cout << "The input sequence is: ";
		for (const auto & element: inputSequence)
			cout << element << " ";
		cout << endl;
		flag = checkInputState(inputSequence);
		cout << flag;
	}
	
	Puzzle::PuzzleState inputState {};
	size_t i = 0;
	for (auto & row : inputState)
	{
		for (auto & column : row)
		{
			column = inputSequence[i];
			++i;
		}
	}

	return inputState;
}

set<Puzzle::PuzzleState> FindAllStates(Puzzle puzzle)
{
	set<decltype(puzzle.getState())> S {puzzle.getState()};
	queue<decltype(puzzle.getState())> Q;
	Q.push(puzzle.getState());
	array<char, 4> direction {'u', 'd', 'l', 'r'};
	int x = 0;
	while (!Q.empty())
	{
		puzzle.setState(Q.front()); Q.pop();
		for (char & action : direction)
		{
			auto move_state = puzzle.move(action);
			if (S.find(move_state) == S.end())
			{
				Q.push(move_state);
				S.insert(move_state);
			}
		}
	}

	return S;
}


bool matchState(Puzzle::PuzzleState state1, Puzzle::PuzzleState state2)
{
	for (size_t i = 0; i < state1.size(); ++i)
		for (size_t j = 0; j < state1[0].size(); ++j)
			if (state1[i][j] != state2[i][j])
				return false;
	return true;
}

bool FindState(Puzzle puzzle, Puzzle::PuzzleState target)
{
	set<decltype(puzzle.getState())> S {puzzle.getState()};
	queue<decltype(puzzle.getState())> Q;
	Q.push(puzzle.getState());

	array<char, 4> direction {'u', 'd', 'l', 'r'};
	while (!Q.empty())
	{
		puzzle.setState(Q.front()); Q.pop();
		Puzzle::PuzzleState parentState = puzzle.getState();
		if (matchState(puzzle.getState(), target))
		{
			cout << "The current puzzle state is:" << endl;
			puzzle.printState();
			return true;
		}
		for (char & action : direction)
		{
			Puzzle::PuzzleState move_state = puzzle.move(action);
			if (S.find(move_state) == S.end())
			{
				Q.push(move_state);
				S.insert(move_state);
			}
		}
	}

	return false;
}

pair<bool, StateLinkDict> FindPath(Puzzle puzzle, string target)
{
	set<decltype(puzzle.getState())> S {puzzle.getState()};
	queue<decltype(puzzle.getState())> Q;
	Q.push(puzzle.getState());
	StateLinkDict D; 

	array<char, 4> direction {'u', 'd', 'l', 'r'};
	while (!Q.empty())
	{
		puzzle.setState(Q.front()); Q.pop();
		string parentState = puzzle.getID();
		for (char & action : direction)
		{
			Puzzle::PuzzleState move_state = puzzle.move(action);
			if (S.find(move_state) == S.end())
			{
				Q.push(move_state);
				S.insert(move_state);
				// puzzle.setState(move_state);
				D.insert({PuzzleStatetoID(move_state), parentState}); // insert pair into map
				if (matchState(move_state, IDtoPuzzleState(target)))
					return {true, D};
			}
		}
	}

	return {false, D};
}

Puzzle::PuzzleState IDtoPuzzleState(string ID)
{
	Puzzle::PuzzleState state {};
	for(size_t i = 0; i < ID.size(); ++i)
		state[i/3][i%3] = (unsigned int)ID[i] - (unsigned int)'0';

	return state;    	
}

string PuzzleStatetoID(Puzzle::PuzzleState state)
{
	string ID {};
	for (auto & row : state)
		for (auto & column : row)
			ID += to_string(column);

	return ID;
}

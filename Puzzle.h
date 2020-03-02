// header file of Class Puzzel
#include <string>
#include <set>
#include <array>

class Puzzle
{
public:
	static const size_t num_rows = 3;
	static const size_t num_cols = 3;

	typedef std::array< std::array< unsigned int, num_cols>, num_rows> PuzzleState;

	Puzzle(PuzzleState);
	void setState(std::array< std::array< unsigned int, num_cols>, num_rows>);
	PuzzleState getState() const;
	std::string getID() const;
	PuzzleState move(const char &) const; 
	void printState() const;
	std::array<size_t, 2> getEmptyIdx() const;
	void printEmptyIdx() const;

private:
	PuzzleState state {};
	std::string stateID;
};
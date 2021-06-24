#include "../include/Move.hpp"
#include "../include/Node.hpp"
#include "../include/Evaluate.hpp"
#include <vector>

using namespace std;

class MCTS
{
public:
	MCTS();


	Node     * HEAD = new Node(1);
	Move     * M    = new Move(1);
	Evaluate * EVAL = new Evaluate();

	vector<vector<int>> getActions(int BOARD[8][8], int turn);
	Node  * makeChildren(Node ** NODE);
	Node  * getTheBestAction();
	Node ** getCurrentNode  ();
	Node  * doIterations(int TIME);
	Node  * setHead(int xfrom, int yfrom, int xto, int yto);
	void    print(int T[8][8]);
	
};
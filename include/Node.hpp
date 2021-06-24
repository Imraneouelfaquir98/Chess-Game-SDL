#include <vector>
#include <cmath>

using namespace std;

class Node
{
public:
	Node(int turn);
	
	double SCORE;
	int    turn;
	int    nbrOfVisit;
	int    BOARD[8][8];

	vector<int> ACTION;
	vector<Node*>CHILDRENS;
	Node * PARENT;

	

	double getUCB1();
	void  copyBoard (int CURRENTBOARD[8][8]);
	
};
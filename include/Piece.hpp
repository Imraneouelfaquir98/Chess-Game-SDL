class Piece
{
public:
	Piece();
	~Piece();
	int position[2];
	int index;

	bool isMovementPossibleTo(int *to);
	
};
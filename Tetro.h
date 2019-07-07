#ifndef __tetro_h_
#define __tetro_h_

#define BOX_SIZE 5
#define HORZ_MOVE_STEP 6
#define VERT_MOVE_STEP 6
#define NUM_COLS 20
#define RIGHT_BORDER 20
#define RIGHT_MAX HORZ_MOVE_STEP * NUM_COLS + 1 + RIGHT_BORDER
#define MAX_VERT 200

class Tetro
{
private:

	float vertMoveSpeed;	// timing construct for how often to advance a pixel
	int arrangement;		// shape of tetrino
	int rotation;			// how the tetrino is rotate 0 - 3
	int column;				// world coordinates of bottom of tetrino
	int row;
	int size;
	unsigned char color;
	
public:
	Tetro();
	~Tetro();
	void RotateCW();
	void RotateCC();
	void MoveLeft();
	void MoveRight();
	void AdvanceVertical();
};

#endif
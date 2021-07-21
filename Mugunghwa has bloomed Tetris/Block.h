#pragma once
typedef int(*ptr)[4];
struct Block
{

	int shape;
	int angle;
	int block[4][4];

	Block();
	Block(int shape, int angle);
	~Block(void);
	int getShape(void);
	int getAngle(void);
	void rotate_Block(void);
	ptr return_Block(void);
	void set_Block(void);
};


#include "Block.h"
Block::Block()
	:angle(0)//if is ㅁblock have not to rotate, others have to  //if ㅁ모양 블럭이면 angle 필요 x ㄴ모양 블록이면 angle에따라 회전시킨모양
{

	for (int i = 0; i < 4; i++)//initialize array for each block
	{

		for (int j = 0; j<4; j++)
		{
			block[i][j] = 0;
		}
	}//배열 초기화
}
Block::Block(int shape, int angle)//Set the array for setting the block
	: shape(shape)
	, angle(angle)
{

	for (int i = 0; i < 4; i++)
	{

		for (int j = 0; j<4; j++)
		{
			block[i][j] = 0;
		}
	}
	set_Block();
}
Block::~Block(void)
{

}

int Block::getShape(void)
{
	return shape;
}

int Block::getAngle(void)
{
	return angle;
}

void Block::rotate_Block(void)
{
	if (angle == 3)//rotate 3 times = didn't rotate //3번 회전 다음은 원위치이므로 0
		angle = 0;
	else
		angle += 1;//아니면 +1
	set_Block();
}
void Block::set_Block(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			block[i][j] = 0;
		}
	}
	switch (shape)
	{
	case 0://stick block 
	{
		switch (angle)
		{
		case 0:
		{
			block[0][0] = 1;
			block[1][0] = 1;
			block[2][0] = 1;
			block[3][0] = 1;
			break;
		}
		case 1:
		{
			block[0][0] = 1;
			block[0][1] = 1;
			block[0][2] = 1;
			block[0][3] = 1;
			break;
		}
		case 2:
		{
			block[0][0] = 1;
			block[1][0] = 1;
			block[2][0] = 1;
			block[3][0] = 1;
			break;
		}
		case 3:
		{
			block[0][0] = 1;
			block[0][1] = 1;
			block[0][2] = 1;
			block[0][3] = 1;
			break;
		}
		}
		break;
	}
	case 1://ㅁ block 
	{
		block[0][0] = 1;
		block[0][1] = 1;
		block[1][0] = 1;
		block[1][1] = 1;
		break;
	}
	case 2://ㅓ block
	{
		switch (angle)
		{
		case 0:
		{
			block[0][1] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			block[2][1] = 1;
			break;
		}
		case 1:
		{
			block[0][0] = 1;
			block[0][1] = 1;
			block[0][2] = 1;
			block[1][1] = 1;
			break;
		}
		case 2:
		{
			block[0][0] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			block[2][0] = 1;
			break;
		}
		case 3:
		{
			block[0][1] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			block[1][2] = 1;
			break;
		}
		}
		break;
	}
	case 3://ㄱ block 
	{
		switch (angle)
		{
		case 0:
		{
			block[0][0] = 1;
			block[0][1] = 1;
			block[1][1] = 1;
			block[2][1] = 1;
			break;
		}
		case 1:
		{
			block[0][0] = 1;
			block[0][1] = 1;
			block[0][2] = 1;
			block[1][0] = 1;
			break;
		}
		case 2:
		{
			block[0][0] = 1;
			block[1][0] = 1;
			block[2][0] = 1;
			block[2][1] = 1;
			break;
		}
		case 3:
		{
			block[0][2] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			block[1][2] = 1;
			break;
		}
		}
		break;
	}
	case 4://ㄴ block 
	{
		switch (angle)
		{
		case 0:
		{
			block[0][0] = 1;
			block[0][1] = 1;
			block[1][0] = 1;
			block[2][0] = 1;
			break;
		}
		case 1:
		{
			block[0][0] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			block[1][2] = 1;
			break;
		}
		case 2:
		{
			block[0][1] = 1;
			block[1][1] = 1;
			block[2][0] = 1;
			block[2][1] = 1;
			break;
		}
		case 3:
		{
			block[0][0] = 1;
			block[0][1] = 1;
			block[0][2] = 1;
			block[1][2] = 1;
			break;
		}
		}
		break;
	}
	case 5: //Z block
	{
		switch (angle)
		{
		case 0:
		{
			block[0][0] = 1;
			block[0][1] = 1;
			block[1][1] = 1;
			block[1][2] = 1;
			break;
		}
		case 1:
		{
			block[0][1] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			block[2][0] = 1;
			break;
		}
		case 2:
		{
			block[0][0] = 1;
			block[0][1] = 1;
			block[1][1] = 1;
			block[1][2] = 1;
			break;
		}
		case 3:
		{
			block[0][1] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			block[2][0] = 1;
			break;
		}
		}
		break;
	}
	case 6: //S block
	{
		switch (angle)
		{
		case 0:
		{
			block[0][1] = 1;
			block[0][2] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			break;
		}
		case 1:
		{
			block[0][0] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			block[2][1] = 1;
			break;
		}
		case 2:
		{
			block[0][1] = 1;
			block[0][2] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			break;
		}
		case 3:
		{
			block[0][0] = 1;
			block[1][0] = 1;
			block[1][1] = 1;
			block[2][1] = 1;
			break;
		}
		}
		break;
	}
	}
}

ptr Block::return_Block()
{
	return block;
}
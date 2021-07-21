#include "Map.h"

enum {//color declaration
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKY_BLUE,
	DARK_RED,
	DARK_VOILET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKY_BLUE,
	RED,
	VOILET,
	YELLOW,
	WHITE,
};

#define EXT_KEY			0xffffffe0	//extend value  realizationarrow //����Ű�� 2����Ʈ�̱⶧���� Ȯ�� �νİ��� �ʿ���
//The ASCII code of each arrow keys
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50




Map::Map()
	:map_Stage(Stage(0)), is_gameOver(0), play_Block(Block(0, 0)), next_Block(Block(0, 0)), score(0)
{
	start_point.X = 5; // start point initialization
	start_point.Y = 1;
	play_point.X = 5; // play point initialization
	play_point.Y = -3;
	srand((unsigned)time(NULL));
	setCursorView(false);
	story();
	showLogo();

	while (true) {
		for (int i = 0; i < 20; i++) // fundamental map initialization
		{
			for (int j = 0; j < 14; j++)
			{
				if ((j == 0) || (j == 13))
				{
					total_Block[i][j] = 1;
				}
				else {
					total_Block[i][j] = 0;
				}
			}
		}

		for (int j = 0; j < 14; j++)
			total_Block[20][j] = 1;

		int shape;
		int i = rand() % 100;
		shape = (rand() % 6) + 1;
		if (i <= map_Stage.getStickRate())
			shape = 0;
		play_Block = Block(shape, 0); // play block initialization

		i = rand() % 100;
		shape = (rand() % 6) + 1;
		if (i <= map_Stage.getStickRate())
			shape = 0;
		next_Block = Block(shape, 0); // next block initialization


		gameStart();
	}
}

void Map::showMap() //Show the play mode map
{

	setColor(DARK_GRAY);
	for (int i = 0; i<21; i++)//range of the wall
	{
		for (int j = 0; j<14; j++)
		{
			if (j == 0 || j == 13 || i == 20)		// color of the wall are changing as the level grow
			{
				setColor((map_Stage.getLevel() % 6) + 1);

			}
			else {
				setColor(DARK_GRAY);
			}
			gotoxy((j * 2) + start_point.X, i + start_point.Y);// print the wall
			if (total_Block[i][j] == 1)
			{
				printf( "��");
			}
			else {
				printf("  ");
			}

		}
	}
	setColor(BLACK);
	gotoxy(77, 23);
}
void Map::showBlock() // set the color of each block
{
	switch (play_Block.getShape())
	{
	case 0:
		setColor(RED);
		break;
	case 1:
		setColor(BLUE);
		break;
	case 2:
		setColor(SKY_BLUE);
		break;
	case 3:
		setColor(WHITE);
		break;
	case 4:
		setColor(YELLOW);
		break;
	case 5:
		setColor(VOILET);
		break;
	case 6:
		setColor(GREEN);
		break;
	}

	for (int i = 0; i<4; i++) //print the block
	{
		for (int j = 0; j<4; j++)
		{

			if ((j + play_point.Y) <0)
				continue;

			if (play_Block.return_Block()[j][i] == 1)
			{
				gotoxy((i + play_point.X) * 2 + start_point.X, j + play_point.Y + start_point.Y);
				printf("��");

			}
		}
	}
	setColor(BLACK);
	gotoxy(77, 23);
}
void Map::eraseBlock()
{

	for (int i = 0; i<4; i++) //erase the block
	{
		for (int j = 0; j<4; j++)
		{
			if (play_Block.return_Block()[j][i] == 1)//print the blank as the shape of the block
			{
				gotoxy((i + play_point.X) * 2 + start_point.X, j + play_point.Y + start_point.Y);
				printf("  ");
				
			}
		}
	}
}
void Map::replaceBlock()
{
	play_Block = next_Block; /// ���� ������ ������ ���� ���� ������ ����
	int shape;
	int i = rand() % 100;
	shape = (rand() % 6) + 1;//randomly set the next block between 7 kinds of blocks // �����Լ��� ���� 7���� ���� �Ѱ����� ���� ������ ����
	if (i <= map_Stage.getStickRate())//as the stage grow, The probability of a stick-shaped block appearing is reduced
		shape = 0;
	next_Block = Block(shape, 0); //Print the next block
}
void Map::showGameOver()// ��������� ���
{
	setColor(RED);
	gotoxy(10 + start_point.X, 7 + start_point.Y);
	printf("��������������������������������������������������������");
	gotoxy(10 + start_point.X, 8 + start_point.Y);
	printf("��**************************��");
	gotoxy(10 + start_point.X, 9 + start_point.Y);
	printf( "��*        GAME OVER       *��");
	gotoxy(10 + start_point.X, 10 + start_point.Y);
	printf("��**************************��");
	gotoxy(10 + start_point.X, 11 + start_point.Y);
	printf("��������������������������������������������������������");
	fflush(stdin);// clean the buffer
	Sleep(2000); // freeze for 2 sec

	system("cls");//�ý���â ����

}

void Map::showClear() // ���� Ŭ����� ���
{
	system("cls");setColor(WHITE);
	gotoxy(10, 3);
	printf("...");Sleep(200);
	printf("...");Sleep(200);
	printf("...");Sleep(200);printf("  ���?!");
	for (int cc = 0;cc < 6;cc++) {
		go(WHITE);Sleep(500);
		go2(WHITE);Sleep(500);
	}
	go2(BLACK);
	setColor(BLUE);
	gotoxy(70, 3);
	printf("                 . .     .     .,,.               \n");gotoxy(70, 4);Sleep(100);
	printf("             .-,.,.,,.,,.  .,..,,,.,,             \n");gotoxy(70,5);Sleep(100);
	printf("            -,-;-,..,..-. ..--...,-,..,.          \n");gotoxy(70, 6);Sleep(100);
	printf("          .-~,~!;:,,-.,,, ..,-,.,;!*-,,-          \n");gotoxy(70, 7);Sleep(100);
	printf("         .-~,-:;:-,~!,;~,.:;:::..-;=~~.,,         \n");gotoxy(70, 8);Sleep(100);
	printf("        ,-,,.~--~.,~;::,,,~*;:~ ,-~*,-----        \n");gotoxy(70, 9);Sleep(100);
	printf("       .,,,--:,., --!=;.,,,;~,. -;:!,~~:~:,       \n");gotoxy(70, 10);Sleep(100);
	printf("       .,.,~:;,.,,,,*=*,,,,-.,  ,:~-~;!~~:~       \n");gotoxy(70, 11);Sleep(100);
	printf("        ..-~;!,.,~:~!**-,,,..,  ,,,.--;,-:,       \n");gotoxy(70, 12);Sleep(100);
	printf("         .-~~:, ,~:!!;;~,,,.,.  ,...,.,,,,        \n");gotoxy(70, 13);Sleep(100);
	printf("          ,---,.,~-!!:;:,,,,.   . .......         \n");gotoxy(70, 14);Sleep(100);
	printf("           .,.,---,:;~;;---,,,,...,....           \n");gotoxy(70, 15);Sleep(100);
	printf("            ...-~--~~-;;:~~-----,,,...            \n");gotoxy(70, 16);Sleep(100);
	printf("              .,~--,,,-~~--~--~-,,...             \n");gotoxy(70, 17);Sleep(100);
	printf("               .-~,.,,--~-~~,---,,..              \n");gotoxy(70, 18);Sleep(100);
	printf("                ,-,.--:~~::~----,.                \n");gotoxy(70, 19);Sleep(100);
	printf("                 ,,-::;~-;!:--~-.                 \n");gotoxy(70, 20);Sleep(100);
	printf("                  .--~;~-;*;-,-.                  \n");gotoxy(70, 21);Sleep(100);
	printf("                   ...-~~:;:,.                    \n");gotoxy(70, 22);Sleep(100);
	printf("                     ,~~::-,                      \n");gotoxy(70, 23);Sleep(100);
	printf("                      .~:;:,                      \n");gotoxy(70, 24);Sleep(100);
	printf("                       .~;-                       \n");gotoxy(70, 25);Sleep(100);
	printf("                        .-.                       \n");gotoxy(70, 26);Sleep(100);

	gotoxy(20, 7);setColor(15);
	printf("�����  ����  ��  ��  ����" );gotoxy(20, 8);
	printf("��        ��  ��  ����  ��      ");gotoxy(20, 9);
	printf("��  ���  ����  ��  ��  ����     ");gotoxy(20, 10);
	printf("��    ��  ��  ��  ��  ��  ��      ");gotoxy(20, 11);
	printf("�����  ��  ��  ��  ��  ����");gotoxy(20, 13);
	printf("����  ��  ��  ����  ����");gotoxy(20, 14);
	printf("��  ��  ��  ��  ��      ��  ��");gotoxy(20, 15);
	printf("��  ��  ��  ��  ����  ���  ");gotoxy(20, 16);
	printf("��  ��   ���   ��      ��  ��");gotoxy(20, 17);
	printf("����    ��    ����  ��   ��");gotoxy(20, 18);
	Sleep(1000);

}
void Map::gameStart()
{
	inputData(); //Manipulation Key & Level //����Ű , ���� ����ȭ��
	showMap(); //��Ʈ���� ��� �׵θ�
	score = 0;
	char keytemp; //store the press key //����� Ű �Է� ����
	for (int i = 1; 1; i++)
	{
		showStart();// STAGE,SCORE , LINES, COINS ��� 
		showNext(); // ���� ��� ���

		
		if (i%map_Stage.getSpeed() == 0) //Set the speed of the block // ����� ���ǵ带 ���� ���ش�.
		{
			is_gameOver = moveBlock();//check the block reach the ground  //1�̸� ���ӿ���, 0�̸� ��� ��ĭ�Ʒ���
			showBlock(); 
		}

		

		if (is_gameOver == 1)//if reach the ground //moveBlock�� ���� ��
		{
			showGameOver();
			is_gameOver = 0;
			setColor(GRAY);
			break;//���� ����
		}
		if (map_Stage.getLevel()==8) { //success all the level //level 8 Ŭ����� ���� ����
			system("cls");
			showClear();break;
		}
		is_gameOver = 0;
		gotoxy(77, 23);
		Sleep(15);
		gotoxy(77, 23);
	}

}
void Map::gotoxy(int x, int y) //Move Cursor //Ŀ�� �̵� �Լ�
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
}
void Map::setColor(int color)//Setting of the color // ���ڻ� ����
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}
void Map::checkFullLine() //check the line full // ��� �� �˻�
{
	int j;
	for (int i = 0; i<20; i++)
	{
		for (j = 1; j<13; j++)
		{
			if (total_Block[i][j] == 0)
				break;
		}
		if (j == 13)//full line	//������ �� ä������
		{

			showMap(); //��Ʈ���� �׵θ� ��� ���
			setColor(BLUE);
			gotoxy(1 * 2 + start_point.X, i + start_point.Y);// print the blank block to full line
			for (j = 1; j<13; j++)
			{
				printf("��");// �� ä���� ��� ��� �ڵ���
				Sleep(10);
			}
			gotoxy(1 * 2 + start_point.X, i + start_point.Y);// erase the full line
			for (j = 1; j<13; j++)
			{
				printf("  ");//�� ä���� �� ����
				Sleep(10);
			}

			for (int k = i; k>0; k--)// after erase the full line, Lower the remaining blocks
			{
				for (j = 1; j<13; j++)
					total_Block[k][j] = total_Block[k - 1][j]; //�� ���� ��ä�������Ƿ� �� �� ����
			}
			for (j = 1; j<13; j++)
				total_Block[0][j] = 0;

			if (check_gostop == 1) //tally the score and line when it's do //Go�϶��� ������ ���� ����
			{
				score += 100 + (map_Stage.getLevel() * 10) + (rand() % 10); 
				map_Stage.reduceClearLines();
			}
			
		}
	}
}////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int Map::strikeCheck()  //��� �ε��� �˻�
{

	int i_start = 0;  
	int block_dat = 0;

	if (play_point.Y < 0) {
		i_start = -play_point.Y;    
		for (int i = 0; i < i_start; i++) {
			for (int j = 0; j < 4; j++)
			{
				if (((play_point.X + j) <= 0) || ((play_point.X + j) >= 13))
					if (play_Block.return_Block()[i][j] == 1)
						return 1;//return 1 when it's not strick
			}
		}
	}

	for (int i = i_start; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			if (((play_point.X + j) == 0) || ((play_point.X + j) == 13)) //check current blcok strick // ���� �ε�ġ���� Ȯ���ϴ� �κ� 
				block_dat = 1;
			else
				block_dat = total_Block[play_point.Y + i][play_point.X + j]; //check stacked blcok strick // ���� �׿��ִ� ���̶� �ε�ġ�� Ȯ���ϴ� �κ�


			if ((block_dat == 1) && (play_Block.return_Block()[i][j] == 1))
			{
				return 1;//if both not, retrun 1
			}
		}
	}
	return 0;
}
int Map::moveBlock()
{
	eraseBlock();

	play_point.Y++;//let block down	//���� ��ĭ �Ʒ��� ����
	if (strikeCheck() == 1) //if block strick //��� �ε���
	{
		if (play_point.Y < 0)//strick the ground //���ӿ���
		{
			return 1;
		}
		play_point.Y--;//Stop Blocks // ��ĭ �ٽ� ����
		for (int i = 0; i<4; i++)//replace the block
		{
			for (int j = 0; j<4; j++)
			{
				total_Block[play_point.Y + i][play_point.X + j] |= play_Block.return_Block()[i][j];
			}//��� �ٽ� �� ��ġ��
		}
		checkFullLine();// ��� �� ä���� �� �ִ��� �˻�

		showMap();

		replaceBlock(); //���� ��� ���� ������� ����, ���ο��� ����������� ����

		play_point.X = 5;	//angle,x,y�� ��������
		play_point.Y = -3;

		return 2;
	}
	return 0; // ��� �ε��� X
}

void Map::showNext() {

	setColor((map_Stage.getLevel() + 1) % 6 + 1);//in defferent level, map color change //Level�� ���� �׵θ��� ����
	for (int i = 1; i<7; i++)
	{
		gotoxy(28 + start_point.X, i + start_point.Y - 1); //print the area which show the next block
		for (int j = 0; j<6; j++) // ���� ��� �����ִ� ��ġ ��� �׵θ� ����
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				printf( "��");
			}
			else {
				printf( "  ");
			}
		}
	}

	switch (next_Block.getShape())//Set the block color
	{
	case 0:
		setColor(RED);
		break;
	case 1:
		setColor(BLUE);
		break;
	case 2:
		setColor(SKY_BLUE);
		break;
	case 3:
		setColor(WHITE);
		break;
	case 4:
		setColor(YELLOW);
		break;
	case 5:
		setColor(VOILET);
		break;
	case 6:
		setColor(GREEN);
		break;
	}

	for (int i = 0; i<4; i++)//print the shape of next block
	{
		for (int j = 0; j<4; j++)
		{

			if (next_Block.return_Block()[j][i] == 1) //������� ��� ���
			{
				gotoxy((i + 15) * 2 + start_point.X, j + 1 + start_point.Y);
				printf( "��");

			}
		}
	}

	setColor(BLACK);
	gotoxy(77, 23);
}


void Map::showLogo()
{
	setColor(GREEN);
	gotoxy(8 + start_point.X, 2 + start_point.Y);
	printf("������������������������������������������������������������������������������������������������");
	setColor(WHITE);
	gotoxy(8 + start_point.X, 3 + start_point.Y);
	printf("���ߡߡ�  �ߡߡ�  �ߡߡ�   �ߡ�     ��    �ߡߡߦ�");
	gotoxy(8 + start_point.X, 4 + start_point.Y);
	printf("��  ��    ��        ��     �� ��    ��  ��      ��");
	gotoxy(8 + start_point.X, 5 + start_point.Y);
	printf("��  ��    �ߡߡ�    ��     �ߡ�     ��    �ߡ�  ��");
	gotoxy(8 + start_point.X, 6 + start_point.Y);
	printf("��  ��    ��        ��     �� ��    ��        �ߦ�");
	gotoxy(8 + start_point.X, 7 + start_point.Y);
	printf("��  ��    �ߡߡ�    ��     ��  ��   ��   �ߡߡ� ��");
	gotoxy(8 + start_point.X, 8 + start_point.Y);
	printf("��                                              ��");
	gotoxy(8 + start_point.X, 9 + start_point.Y);
	printf("��      ��    ��   ��   ��    ��   �ߡߡ�       ��");
	gotoxy(8 + start_point.X, 10 + start_point.Y);
	printf("��      �� �� ��   ��   �ߡ�  ��   ��           ��");
	gotoxy(8 + start_point.X, 11 + start_point.Y);
	printf("��      ��    ��   ��   ��  �ߡ�   �ߡߡ�       ��");
	gotoxy(8 + start_point.X, 12 + start_point.Y);
	printf("��      ��    ��   ��   ��    ��   ��           ��");
	gotoxy(8 + start_point.X, 13 + start_point.Y);
	printf("��      ��    ��   ��   ��    ��   �ߡߡ�       ��");
	setColor(RED);
	gotoxy(8 + start_point.X, 14 + start_point.Y);
	printf("������������������������������������������������������������������������������������������������");
	gotoxy(18 + start_point.X, 15 + start_point.Y);
	setColor(WHITE);
	printf("FEAT. ����ȭ ���� �Ǿ����ϴ�");
	gotoxy(18 + start_point.X, 16 + start_point.Y);
	printf("���������������");
	setColor(GREEN);
	gotoxy(12 + start_point.X, 17 + start_point.Y);
	printf("����   You can go at ��     ����");
	setColor(RED);
	gotoxy(12 + start_point.X, 18 + start_point.Y);
	printf("���� But can not go at ��   ����");



	setColor(YELLOW);
	gotoxy(16 + start_point.X, 23 + start_point.Y);
	printf("-----After 3 sec start-----");
	Sleep(3000); 
	system("cls");
}

void Map::inputData()
{

	int i = 0;
	setColor(GRAY);
	gotoxy(5 + start_point.X, 6 + start_point.Y);
	printf( "��������������������<GAME KEY>��������������������");
	gotoxy(5 + start_point.X, 7 + start_point.Y);
	printf(  "�� UP   : Rotate Block        ��");
	gotoxy(5 + start_point.X, 8 + start_point.Y);
	printf("�� DOWN : Move One-Step Down  ��");
	gotoxy(5 + start_point.X, 9 + start_point.Y);
	printf("�� SPACE: Move Bottom Down    ��");
	gotoxy(5 + start_point.X, 10 + start_point.Y);
	printf("�� LEFT : Move Left           ��");
	gotoxy(5 + start_point.X, 11 + start_point.Y);
	printf("�� RIGHT: Move Right          ��");
	gotoxy(5 + start_point.X, 12 + start_point.Y);
	printf("������������������������������������������������������������");
	setColor(BLUE);
	gotoxy(45 + start_point.X, 6 + start_point.Y);
	printf("������������������<SPECIAL KEY>������������������");
	setColor(BLUE);
	gotoxy(45 + start_point.X, 7 + start_point.Y);
	printf("�� Z  :  �ٴ� ���� ����        ��");
	gotoxy(45 + start_point.X, 8 + start_point.Y);
	printf("�� X  :  �ð� ���� +30         ��");
	gotoxy(45 + start_point.X, 9 + start_point.Y);
	printf("�� C  :  ���� ��� ��ü        ��");
	gotoxy(45 + start_point.X, 10 + start_point.Y);
	printf("�� V  :  ��� ��� ����        ��");
	gotoxy(45 + start_point.X, 11 + start_point.Y);
	printf("��                             ��");
	gotoxy(45 + start_point.X, 12 + start_point.Y);
	setColor(BLUE);
	printf("��������������������������������������������������������������");
	gotoxy(45 + start_point.X, 20 + start_point.Y);
	setColor(13);
	printf("If you make 1 line at ��, you cannot get score");
	gotoxy(45 + start_point.X, 21 + start_point.Y);
	printf("If you make 1 line at ��, you can get score");
	setColor(14);
	gotoxy(45 + start_point.X, 15 + start_point.Y);
	printf("You need some coins to use special key");
	gotoxy(45 + start_point.X, 16 + start_point.Y);
	printf("You can get coins whenever you manage to survive 20seconds");

	setCursorView(true);
	setColor(6);
	while (i<1 || i>8)//after enter the level game start  //1~8 ���� ���� �Է����� ������ �۵� X
	{
		gotoxy(5 + start_point.X, 2 + start_point.Y);
		printf( "Select Start level[1-8]:       \b\b\b\b\b\b\b");
		scanf_s("%d" ,&i);
	}

	setCursorView(false); //hide cursor //Ŀ�� �����

	map_Stage.setLevel(i - 1);//hand over the level
	system("cls");
}

void Map::showStart() {
	store(); // �����۰���, ���� ���
	static int printed_text = 0;
	setColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(30 + start_point.X, 6 + start_point.Y);
		printf( "STAGE");

		gotoxy(30 + start_point.X, 8 + start_point.Y);
		printf( "SCORE");

		gotoxy(30 + start_point.X, 11 + start_point.Y);
		printf( "LINES");

		gotoxy(30 + start_point.X, 14 + start_point.Y);
		printf("COINS");
	}
	gotoxy(36 + start_point.X, 6 + start_point.Y);
	printf("%d",map_Stage.getLevel() + 1);
	gotoxy(30 + start_point.X, 9 + start_point.Y);
	printf("%d", score);
	gotoxy(30 + start_point.X, 12 + start_point.Y);
	printf("  %d",map_Stage.getClearLines());
	gotoxy(30 + start_point.X, 15 + start_point.Y);
	printf("%f", coin);


	for (int a = 1; a < 50; a++) {
	if (0 < clock()/1000 <= 1*a|| 2*a < clock()/1000 <=3*a|| 5 * a < clock() / 1000 <= 6 *a || 7 * a < clock() / 1000 <= 8 *a) s_or_g = 1;
	if (1*a < clock()/1000 <= 2*a || 4 * a < clock() / 1000 <= 5 *a || 6 * a < clock() / 1000 <= 7 *a || 8 * a < clock() / 1000 <= 9 *a) s_or_g = 0;
	}
	static int k = 0;
	int time_s = 1000 - (clock() / 1000 + 1) + k*20;//if use time_extention item //k�� �����ۻ���k+1
	int time_j = 1000 - (clock() / 1000 + 1);//nomal time //coin ��� �ð� ����
	gotoxy(30 + start_point.X, 17 + start_point.Y);
	printf("Timer: %d",time_s);
	if (time_s <= 0) //time over
	{
		showGameOver();
		Sleep(4000);
		system("cls");
	}

	int j = clock() / 1000;//Go(the time print the pickax and the time tally the score and line) // ��� ��� �κ�
	if (j % 50 / 10 == 0 || j % 50 / 10 == 2 || j % 50 / 10 == 4)
	{

		stop(BLACK);
		if (j % 2 == 0) {
			go(GREEN);

		}
		if (j % 2 == 1) {
			go2(GREEN);

		}
		check_gostop = 1;
	}
	else if (j % 50 / 10 == 1 || j % 50 / 10 == 3 || j % 50 / 10 == 5)///Stop(the time print the X and the time  do not tally the score and line) //stop ���� ��� �κ�
	{
		go(BLACK);
		stop(RED);

		check_gostop = 0;
	}

	//the time get the coin(per 20 sec) //20�ʸ��� �� 7���� ����
	if (time_j == 980 || time_j == 960 || time_j == 940 || time_j == 920 || time_j == 900 ||
		time_j == 880 || time_j == 860 || time_j == 840 || time_j == 820 || time_j == 800 ||
		time_j == 780 || time_j == 760 || time_j == 740 || time_j == 720 || time_j == 700 ||
		time_j == 680 || time_j == 660 || time_j == 640 || time_j == 620 || time_j == 600 ||
		time_j == 580 || time_j == 560 || time_j == 540 || time_j == 520 || time_j == 500 ||
		time_j == 480 || time_j == 460 || time_j == 440 || time_j == 420 || time_j == 400 ||
		time_j == 380 || time_j == 360 || time_j == 340 || time_j == 320 || time_j == 300 ||
		time_j == 280 || time_j == 260 || time_j == 240 || time_j == 220 || time_j == 200 ||
		time_j == 180 || time_j == 160 || time_j == 140 || time_j == 120 || time_j == 100 ||
		time_j == 80 || time_j == 60 || time_j == 40 || time_j == 20)
	{
		coin = coin + 0.3;
	}

	char keytem; 
	if (_kbhit())//get the ketpress
	{
		keytem = _getch(); //����� �Է� ����
			switch (keytem)
			{
			case KEY_UP://rotate the block when press Up_key //����Ű ����
				eraseBlock();//���� ��� ����
				play_Block.rotate_Block();//��� ȸ��
				if (strikeCheck() == 0) {//�浹 X
					showBlock();//��� ������
				}
				else {//�浹 O
					eraseBlock();//��� ����
					showMap();//��Ʈ���� �׵θ� ���
					play_Block.rotate_Block();//3�� ������ �� 4�� �������� ����ġ
					play_Block.rotate_Block();
					play_Block.rotate_Block();
					showBlock();
				}
				fflush(stdout);//���� ����
				break;
			case KEY_LEFT:// move left when press left_key
				if (play_point.X > 1)
				{
					eraseBlock();
					play_point.X--;//�������� ��ĭ
					if (strikeCheck() == 1)//�浹 ������ �ٽ� ���������� ��ĭ
						play_point.X++;

					showBlock();//��� ������
				}
				fflush(stdout);
				break;
			case KEY_RIGHT:	//move left when press right_key

				if (play_point.X < 14)
				{
					eraseBlock();
					play_point.X++;//���������� ��ĭ
					if (strikeCheck() == 1)//�浹������ �ٽ� �������� ��ĭ
						play_point.X--;

					showBlock();
				}
				fflush(stdout);
				break;
			case KEY_DOWN:	//move left when press left_key	
				is_gameOver = moveBlock();
				showBlock();
				fflush(stdout);
				break;
			case 122://press z, clear one line ///// Press z(z�� �ƽ�Ű�ڵ�) �ٴ� �� �� ����
				if (coin >= 5) // coin>=5
				{
					clearone();
					coin = coin - 20;
				}
				fflush(stdout);
				break;
			case 120://press x, time extension //////Press x(x�� �ƽ�Ű�ڵ�) �ð�+
				if (coin >= 20) {//coin >= 20
					k += 1;
					coin = coin - 20;
				}
				fflush(stdout);
				break;

			case 99://press c, chage next block //Press c ���� ��� ��ü
				if (coin >= 5) {//coin >= 5
					int shape;
					shape = (rand() % 6) + 1;
					next_Block = Block(shape, 0);
					coin -= 20;
				}
				fflush(stdout);
				break;
			case 118://press v, bomb //Press v ��� ��� ����
				if (coin>=200) {
					Bomb();
					coin -= 200;
				}
				fflush(stdout);
				break;
			}
			if (keytem == 32)//press spacebar, block reach to gound	//�����̽��ٸ� ��������
			{
				while (is_gameOver == 0)// replay the move down until reach the block
				{
					is_gameOver = moveBlock();//moveblock �浹������ 1 �浹������ 0(��ĭ ����) ���� �浹�Ҷ����� ����
				}
				showBlock();
				fflush(stdout);
			}
			
	}

	setColor(BLACK);
	gotoxy(77, 23);
}

void Map::store()//peint the store
{


	setColor(DARK_YELLOW);
	gotoxy(83 + start_point.X, 18 + start_point.Y);
	printf("�������STORE�������");
	gotoxy(83 + start_point.X, 20 + start_point.Y);
	printf("(Z) Clear one lines:   20 COIN��");
	gotoxy(83 + start_point.X, 21 + start_point.Y);
	printf("(X) TIME EXTENSION:    20 COIN��");
	gotoxy(83 + start_point.X, 22 + start_point.Y);
	printf("(C) CHANGE NEXT BLOCK: 20 COIN��");
	gotoxy(83 + start_point.X, 23 + start_point.Y);
	printf("(V) BOMB!:            200 COIN��");
}
void Map::TimeExtension(int time)///time+20
{
	time = time + 20;
}


void Map::Bomb() ///clear all the block
{
	for (int i = 1; i < 20; i++) // fundamental map initialization
	{
		for (int j = 1; j < 13; j++)
		{
			total_Block[i][j] = 0;
		}
	}
	showMap();
}
void Map::clearone() ///clear one line
{
	for (int j = 1; j < 13; j++)
	{
		total_Block[19][j] = 0; //�ٴ� ���� ����
	}

	for (int k = 19; k > 0; k--)//after clear line, down the stored block
	{
		for (int l = 1; l < 13; l++)
			total_Block[k][l] = total_Block[k - 1][l]; //��ĭ�� ����
	}
	for (int p = 1; p < 13; p++)
		total_Block[0][p] = 0;
	showBlock();
	showMap();
}

void Map::stop(char stop_color) {
	setColor(stop_color);
	gotoxy(45 + start_point.X, 3 + start_point.Y);
	printf("            ����������      ");
	gotoxy(45 + start_point.X, 4 + start_point.Y);
	printf("        ���                  ���");
	gotoxy(45 + start_point.X, 5 + start_point.Y);
	printf("      ���  ���                ���");
	gotoxy(45 + start_point.X, 6 + start_point.Y);
	printf("    ���          ���            ���");
	gotoxy(45 + start_point.X, 7 + start_point.Y);
	printf("      ���              ���    ���");
	gotoxy(45 + start_point.X, 8 + start_point.Y);
	printf("        ���                ����");
	gotoxy(45 + start_point.X, 9 + start_point.Y);
	printf("            ����������");
}

void Map::go(char go_color) {
	setColor(go_color);
	gotoxy(45 + start_point.X, 14 + start_point.Y);
	printf("    ��������             ");
	gotoxy(45 + start_point.X, 15 + start_point.Y);
	printf("  ���    ��    ���           ");
	gotoxy(45 + start_point.X, 16 + start_point.Y);
	printf("          ��                   ");
	gotoxy(45 + start_point.X, 17 + start_point.Y);
	printf("          ��                   ");
	gotoxy(45 + start_point.X, 18 + start_point.Y);
	printf("          ��                   ");
	gotoxy(45 + start_point.X, 19 + start_point.Y);
	printf("          ��                   ");
}
void Map::go2(char go_color) {
	setColor(go_color);
	gotoxy(45 + start_point.X, 14 + start_point.Y);
	printf("          ������                ");
	gotoxy(45 + start_point.X, 15 + start_point.Y);
	printf("      ���    ��    ���            ");
	gotoxy(45 + start_point.X, 16 + start_point.Y);
	printf("            ��        ��            ");
	gotoxy(45 + start_point.X, 17 + start_point.Y);
	printf("          ��                        ");
	gotoxy(45 + start_point.X, 18 + start_point.Y);
	printf("        ��                          ");
	gotoxy(45 + start_point.X, 19 + start_point.Y);
	printf("      ��                            ");
}


void Map::setCursorView(bool visible) {
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void Map::story() {
	gotoxy(10, 1);setColor(14);
	printf("��");Sleep(100);printf("Ʈ");Sleep(100);printf("��");Sleep(100);
	printf("�� ");Sleep(100);printf("��");Sleep(100);printf("��");Sleep(00);
	printf("�� ");Sleep(100);printf("��");Sleep(100);printf("��");Sleep(100);
	printf("��");Sleep(100);printf("�� ");Sleep(100);printf("��");Sleep(100);
	printf("��");Sleep(100);
	setColor(GRAY);printf("...");Sleep(100);printf(" ...");Sleep(300);
	gotoxy(5 + start_point.X, 6 + start_point.Y);setColor(WHITE);
	printf("������������������������������������������������������������������������������������������������");
	gotoxy(5 + start_point.X, 7 + start_point.Y);
	printf("��              ��Ʈ���� ���꿡                 ��");
	gotoxy(5 + start_point.X, 8 + start_point.Y);
	printf("��           ���̾Ƹ�� ����� �ִ� !!          ��");
	gotoxy(5 + start_point.X, 9 + start_point.Y);
	printf("��");setColor(RED);printf("            WARNING: �ļ��� ����             ");setColor(WHITE);printf(" ��");
	gotoxy(5 + start_point.X, 10 + start_point.Y);
	printf("������������������������������������������������������������������������������������������������");
	Sleep(1000);setColor(GRAY);
	gotoxy(5 + start_point.X, 12 + start_point.Y);setColor(9);
	printf("���� ���� ���� ������ �ô޸��� A��");Sleep(500);
	gotoxy(5 + start_point.X, 13 + start_point.Y);
	printf("��Ʈ���� ���꿡 ���̾Ƹ�� ����� ã���� ����� ���!");Sleep(500);
	gotoxy(10 + start_point.X, 15 + start_point.Y);
	printf("A");Sleep(100);printf("��");Sleep(100);
	go(WHITE);Sleep(700);go2(WHITE);Sleep(700);
	go(WHITE);Sleep(700);go2(WHITE);Sleep(700);
	go2(BLACK);
	setColor(GRAY);
	gotoxy(13 + start_point.X, 15 + start_point.Y);Sleep(100);
	printf(" ��̸� ��� ��Ʈ���� ��������...."); Sleep(3000);
	system("cls");

}
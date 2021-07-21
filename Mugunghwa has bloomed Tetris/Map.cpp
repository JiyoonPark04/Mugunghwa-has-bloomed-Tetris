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

#define EXT_KEY			0xffffffe0	//extend value  realizationarrow //방항키는 2바이트이기때문에 확장 인식값이 필요함
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
				printf( "■");
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
				printf("■");

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
	play_Block = next_Block; /// 다음 블럭으로 지정된 블럭을 현재 블럭으로 지정
	int shape;
	int i = rand() % 100;
	shape = (rand() % 6) + 1;//randomly set the next block between 7 kinds of blocks // 렌덤함수를 통해 7가지 블럭중 한가지를 다음 블럭으로 지정
	if (i <= map_Stage.getStickRate())//as the stage grow, The probability of a stick-shaped block appearing is reduced
		shape = 0;
	next_Block = Block(shape, 0); //Print the next block
}
void Map::showGameOver()// 게임종료시 출력
{
	setColor(RED);
	gotoxy(10 + start_point.X, 7 + start_point.Y);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(10 + start_point.X, 8 + start_point.Y);
	printf("┃**************************┃");
	gotoxy(10 + start_point.X, 9 + start_point.Y);
	printf( "┃*        GAME OVER       *┃");
	gotoxy(10 + start_point.X, 10 + start_point.Y);
	printf("┃**************************┃");
	gotoxy(10 + start_point.X, 11 + start_point.Y);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	fflush(stdin);// clean the buffer
	Sleep(2000); // freeze for 2 sec

	system("cls");//시스템창 종료

}

void Map::showClear() // 게임 클리어시 출력
{
	system("cls");setColor(WHITE);
	gotoxy(10, 3);
	printf("...");Sleep(200);
	printf("...");Sleep(200);
	printf("...");Sleep(200);printf("  어엇?!");
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
	printf("■■■■  ■■■  ■  ■  ■■■" );gotoxy(20, 8);
	printf("■        ■  ■  ■■■  ■      ");gotoxy(20, 9);
	printf("■  ■■  ■■■  ■  ■  ■■■     ");gotoxy(20, 10);
	printf("■    ■  ■  ■  ■  ■  ■      ");gotoxy(20, 11);
	printf("■■■■  ■  ■  ■  ■  ■■■");gotoxy(20, 13);
	printf("■■■  ■  ■  ■■■  ■■■");gotoxy(20, 14);
	printf("■  ■  ■  ■  ■      ■  ■");gotoxy(20, 15);
	printf("■  ■  ■  ■  ■■■  ■■  ");gotoxy(20, 16);
	printf("■  ■   ■■   ■      ■  ■");gotoxy(20, 17);
	printf("■■■    ■    ■■■  ■   ■");gotoxy(20, 18);
	Sleep(1000);

}
void Map::gameStart()
{
	inputData(); //Manipulation Key & Level //조작키 , 레벨 설정화면
	showMap(); //테트리스 블록 테두리
	score = 0;
	char keytemp; //store the press key //사용자 키 입력 보관
	for (int i = 1; 1; i++)
	{
		showStart();// STAGE,SCORE , LINES, COINS 출력 
		showNext(); // 다음 블록 출력

		
		if (i%map_Stage.getSpeed() == 0) //Set the speed of the block // 블록의 스피드를 조절 해준다.
		{
			is_gameOver = moveBlock();//check the block reach the ground  //1이면 게임오버, 0이면 블록 한칸아래로
			showBlock(); 
		}

		

		if (is_gameOver == 1)//if reach the ground //moveBlock의 리턴 값
		{
			showGameOver();
			is_gameOver = 0;
			setColor(GRAY);
			break;//게임 종료
		}
		if (map_Stage.getLevel()==8) { //success all the level //level 8 클리어시 게임 종료
			system("cls");
			showClear();break;
		}
		is_gameOver = 0;
		gotoxy(77, 23);
		Sleep(15);
		gotoxy(77, 23);
	}

}
void Map::gotoxy(int x, int y) //Move Cursor //커서 이동 함수
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
}
void Map::setColor(int color)//Setting of the color // 글자색 지정
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}
void Map::checkFullLine() //check the line full // 블록 줄 검사
{
	int j;
	for (int i = 0; i<20; i++)
	{
		for (j = 1; j<13; j++)
		{
			if (total_Block[i][j] == 0)
				break;
		}
		if (j == 13)//full line	//한줄이 다 채워졌음
		{

			showMap(); //테트리스 테두리 블록 출력
			setColor(BLUE);
			gotoxy(1 * 2 + start_point.X, i + start_point.Y);// print the blank block to full line
			for (j = 1; j<13; j++)
			{
				printf("□");// 다 채워진 블록 □로 뒤덮음
				Sleep(10);
			}
			gotoxy(1 * 2 + start_point.X, i + start_point.Y);// erase the full line
			for (j = 1; j<13; j++)
			{
				printf("  ");//다 채워진 줄 제거
				Sleep(10);
			}

			for (int k = i; k>0; k--)// after erase the full line, Lower the remaining blocks
			{
				for (j = 1; j<13; j++)
					total_Block[k][j] = total_Block[k - 1][j]; //한 줄이 다채워졌으므로 한 줄 내림
			}
			for (j = 1; j<13; j++)
				total_Block[0][j] = 0;

			if (check_gostop == 1) //tally the score and line when it's do //Go일때만 점수랑 라인 집계
			{
				score += 100 + (map_Stage.getLevel() * 10) + (rand() % 10); 
				map_Stage.reduceClearLines();
			}
			
		}
	}
}////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int Map::strikeCheck()  //블록 부딪힘 검사
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
			if (((play_point.X + j) == 0) || ((play_point.X + j) == 13)) //check current blcok strick // 벽에 부딪치는지 확인하는 부분 
				block_dat = 1;
			else
				block_dat = total_Block[play_point.Y + i][play_point.X + j]; //check stacked blcok strick // 현재 쌓여있는 블럭이랑 부딪치는 확인하는 부분


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

	play_point.Y++;//let block down	//블럭을 한칸 아래로 내림
	if (strikeCheck() == 1) //if block strick //블록 부딪힘
	{
		if (play_point.Y < 0)//strick the ground //게임오버
		{
			return 1;
		}
		play_point.Y--;//Stop Blocks // 한칸 다시 위로
		for (int i = 0; i<4; i++)//replace the block
		{
			for (int j = 0; j<4; j++)
			{
				total_Block[play_point.Y + i][play_point.X + j] |= play_Block.return_Block()[i][j];
			}//블록 다시 제 위치로
		}
		checkFullLine();// 블록 다 채워진 줄 있는지 검사

		showMap();

		replaceBlock(); //다음 블록 현재 블록으로 지정, 새로운블록 다음블록으로 지정

		play_point.X = 5;	//angle,x,y는 포인터임
		play_point.Y = -3;

		return 2;
	}
	return 0; // 블록 부딪힘 X
}

void Map::showNext() {

	setColor((map_Stage.getLevel() + 1) % 6 + 1);//in defferent level, map color change //Level에 따라 테두리색 변함
	for (int i = 1; i<7; i++)
	{
		gotoxy(28 + start_point.X, i + start_point.Y - 1); //print the area which show the next block
		for (int j = 0; j<6; j++) // 다음 블록 보여주는 위치 블록 테두리 설정
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				printf( "■");
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

			if (next_Block.return_Block()[j][i] == 1) //다음블록 모양 출력
			{
				gotoxy((i + 15) * 2 + start_point.X, j + 1 + start_point.Y);
				printf( "■");

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
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	setColor(WHITE);
	gotoxy(8 + start_point.X, 3 + start_point.Y);
	printf("┃◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆    ◆◆◆┃");
	gotoxy(8 + start_point.X, 4 + start_point.Y);
	printf("┃  ◆    ◆        ◆     ◆ ◆    ◆  ◆      ┃");
	gotoxy(8 + start_point.X, 5 + start_point.Y);
	printf("┃  ◆    ◆◆◆    ◆     ◆◆     ◆    ◆◆  ┃");
	gotoxy(8 + start_point.X, 6 + start_point.Y);
	printf("┃  ◆    ◆        ◆     ◆ ◆    ◆        ◆┃");
	gotoxy(8 + start_point.X, 7 + start_point.Y);
	printf("┃  ◆    ◆◆◆    ◆     ◆  ◆   ◆   ◆◆◆ ┃");
	gotoxy(8 + start_point.X, 8 + start_point.Y);
	printf("┃                                              ┃");
	gotoxy(8 + start_point.X, 9 + start_point.Y);
	printf("┃      ◆    ◆   ◆   ◆    ◆   ◆◆◆       ┃");
	gotoxy(8 + start_point.X, 10 + start_point.Y);
	printf("┃      ◆ ◆ ◆   ◆   ◆◆  ◆   ◆           ┃");
	gotoxy(8 + start_point.X, 11 + start_point.Y);
	printf("┃      ◆    ◆   ◆   ◆  ◆◆   ◆◆◆       ┃");
	gotoxy(8 + start_point.X, 12 + start_point.Y);
	printf("┃      ◆    ◆   ◆   ◆    ◆   ◆           ┃");
	gotoxy(8 + start_point.X, 13 + start_point.Y);
	printf("┃      ◆    ◆   ◆   ◆    ◆   ◆◆◆       ┃");
	setColor(RED);
	gotoxy(8 + start_point.X, 14 + start_point.Y);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(18 + start_point.X, 15 + start_point.Y);
	setColor(WHITE);
	printf("FEAT. 무궁화 꽃이 피었습니다");
	gotoxy(18 + start_point.X, 16 + start_point.Y);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	setColor(GREEN);
	gotoxy(12 + start_point.X, 17 + start_point.Y);
	printf("△△△   You can go at т     △△△");
	setColor(RED);
	gotoxy(12 + start_point.X, 18 + start_point.Y);
	printf("▲▲▲ But can not go at ⓧ   ▲▲▲");



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
	printf( "┏━━━━━━━━━<GAME KEY>━━━━━━━━━┓");
	gotoxy(5 + start_point.X, 7 + start_point.Y);
	printf(  "┃ UP   : Rotate Block        ┃");
	gotoxy(5 + start_point.X, 8 + start_point.Y);
	printf("┃ DOWN : Move One-Step Down  ┃");
	gotoxy(5 + start_point.X, 9 + start_point.Y);
	printf("┃ SPACE: Move Bottom Down    ┃");
	gotoxy(5 + start_point.X, 10 + start_point.Y);
	printf("┃ LEFT : Move Left           ┃");
	gotoxy(5 + start_point.X, 11 + start_point.Y);
	printf("┃ RIGHT: Move Right          ┃");
	gotoxy(5 + start_point.X, 12 + start_point.Y);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	setColor(BLUE);
	gotoxy(45 + start_point.X, 6 + start_point.Y);
	printf("┏━━━━━━━━<SPECIAL KEY>━━━━━━━━┓");
	setColor(BLUE);
	gotoxy(45 + start_point.X, 7 + start_point.Y);
	printf("┃ Z  :  바닥 한줄 제거        ┃");
	gotoxy(45 + start_point.X, 8 + start_point.Y);
	printf("┃ X  :  시간 증가 +30         ┃");
	gotoxy(45 + start_point.X, 9 + start_point.Y);
	printf("┃ C  :  다음 블록 교체        ┃");
	gotoxy(45 + start_point.X, 10 + start_point.Y);
	printf("┃ V  :  모든 블록 제거        ┃");
	gotoxy(45 + start_point.X, 11 + start_point.Y);
	printf("┃                             ┃");
	gotoxy(45 + start_point.X, 12 + start_point.Y);
	setColor(BLUE);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(45 + start_point.X, 20 + start_point.Y);
	setColor(13);
	printf("If you make 1 line at ⓧ, you cannot get score");
	gotoxy(45 + start_point.X, 21 + start_point.Y);
	printf("If you make 1 line at т, you can get score");
	setColor(14);
	gotoxy(45 + start_point.X, 15 + start_point.Y);
	printf("You need some coins to use special key");
	gotoxy(45 + start_point.X, 16 + start_point.Y);
	printf("You can get coins whenever you manage to survive 20seconds");

	setCursorView(true);
	setColor(6);
	while (i<1 || i>8)//after enter the level game start  //1~8 사이 값을 입력하지 않으면 작동 X
	{
		gotoxy(5 + start_point.X, 2 + start_point.Y);
		printf( "Select Start level[1-8]:       \b\b\b\b\b\b\b");
		scanf_s("%d" ,&i);
	}

	setCursorView(false); //hide cursor //커서 숨기기

	map_Stage.setLevel(i - 1);//hand over the level
	system("cls");
}

void Map::showStart() {
	store(); // 아이템가격, 설명 출력
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
	int time_s = 1000 - (clock() / 1000 + 1) + k*20;//if use time_extention item //k는 아이템사용시k+1
	int time_j = 1000 - (clock() / 1000 + 1);//nomal time //coin 얻는 시간 따로
	gotoxy(30 + start_point.X, 17 + start_point.Y);
	printf("Timer: %d",time_s);
	if (time_s <= 0) //time over
	{
		showGameOver();
		Sleep(4000);
		system("cls");
	}

	int j = clock() / 1000;//Go(the time print the pickax and the time tally the score and line) // 곡괭이 출력 부분
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
	else if (j % 50 / 10 == 1 || j % 50 / 10 == 3 || j % 50 / 10 == 5)///Stop(the time print the X and the time  do not tally the score and line) //stop 사인 출력 부분
	{
		go(BLACK);
		stop(RED);

		check_gostop = 0;
	}

	//the time get the coin(per 20 sec) //20초마다 약 7코인 적립
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
		keytem = _getch(); //사용자 입력 받음
			switch (keytem)
			{
			case KEY_UP://rotate the block when press Up_key //방향키 위쪽
				eraseBlock();//현재 블록 지움
				play_Block.rotate_Block();//블록 회전
				if (strikeCheck() == 0) {//충돌 X
					showBlock();//블록 보여줌
				}
				else {//충돌 O
					eraseBlock();//블록 제거
					showMap();//테트리스 테두리 출력
					play_Block.rotate_Block();//3번 돌려서 총 4번 돌림으로 원위치
					play_Block.rotate_Block();
					play_Block.rotate_Block();
					showBlock();
				}
				fflush(stdout);//버퍼 제거
				break;
			case KEY_LEFT:// move left when press left_key
				if (play_point.X > 1)
				{
					eraseBlock();
					play_point.X--;//왼쪽으로 한칸
					if (strikeCheck() == 1)//충돌 있으면 다시 오른쪽으로 한칸
						play_point.X++;

					showBlock();//블록 보여줌
				}
				fflush(stdout);
				break;
			case KEY_RIGHT:	//move left when press right_key

				if (play_point.X < 14)
				{
					eraseBlock();
					play_point.X++;//오른쪽으로 한칸
					if (strikeCheck() == 1)//충돌있으면 다시 왼쪽으로 한칸
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
			case 122://press z, clear one line ///// Press z(z의 아스키코드) 바닥 한 줄 제거
				if (coin >= 5) // coin>=5
				{
					clearone();
					coin = coin - 20;
				}
				fflush(stdout);
				break;
			case 120://press x, time extension //////Press x(x의 아스키코드) 시간+
				if (coin >= 20) {//coin >= 20
					k += 1;
					coin = coin - 20;
				}
				fflush(stdout);
				break;

			case 99://press c, chage next block //Press c 다음 블록 교체
				if (coin >= 5) {//coin >= 5
					int shape;
					shape = (rand() % 6) + 1;
					next_Block = Block(shape, 0);
					coin -= 20;
				}
				fflush(stdout);
				break;
			case 118://press v, bomb //Press v 모든 블록 제거
				if (coin>=200) {
					Bomb();
					coin -= 200;
				}
				fflush(stdout);
				break;
			}
			if (keytem == 32)//press spacebar, block reach to gound	//스페이스바를 눌렀을때
			{
				while (is_gameOver == 0)// replay the move down until reach the block
				{
					is_gameOver = moveBlock();//moveblock 충돌있으면 1 충돌없으면 0(한칸 내림) 따라서 충돌할때까지 내림
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
	printf("↓↓↓↓↓↓STORE↓↓↓↓↓↓");
	gotoxy(83 + start_point.X, 20 + start_point.Y);
	printf("(Z) Clear one lines:   20 COIN◎");
	gotoxy(83 + start_point.X, 21 + start_point.Y);
	printf("(X) TIME EXTENSION:    20 COIN◎");
	gotoxy(83 + start_point.X, 22 + start_point.Y);
	printf("(C) CHANGE NEXT BLOCK: 20 COIN◎");
	gotoxy(83 + start_point.X, 23 + start_point.Y);
	printf("(V) BOMB!:            200 COIN◎");
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
		total_Block[19][j] = 0; //바닥 한줄 제거
	}

	for (int k = 19; k > 0; k--)//after clear line, down the stored block
	{
		for (int l = 1; l < 13; l++)
			total_Block[k][l] = total_Block[k - 1][l]; //한칸씩 내림
	}
	for (int p = 1; p < 13; p++)
		total_Block[0][p] = 0;
	showBlock();
	showMap();
}

void Map::stop(char stop_color) {
	setColor(stop_color);
	gotoxy(45 + start_point.X, 3 + start_point.Y);
	printf("            ■■■■■■■■■      ");
	gotoxy(45 + start_point.X, 4 + start_point.Y);
	printf("        ■■                  ■■");
	gotoxy(45 + start_point.X, 5 + start_point.Y);
	printf("      ■■  ■■                ■■");
	gotoxy(45 + start_point.X, 6 + start_point.Y);
	printf("    ■■          ■■            ■■");
	gotoxy(45 + start_point.X, 7 + start_point.Y);
	printf("      ■■              ■■    ■■");
	gotoxy(45 + start_point.X, 8 + start_point.Y);
	printf("        ■■                ■■■");
	gotoxy(45 + start_point.X, 9 + start_point.Y);
	printf("            ■■■■■■■■■");
}

void Map::go(char go_color) {
	setColor(go_color);
	gotoxy(45 + start_point.X, 14 + start_point.Y);
	printf("    ■■■■■■■             ");
	gotoxy(45 + start_point.X, 15 + start_point.Y);
	printf("  ■■    ■    ■■           ");
	gotoxy(45 + start_point.X, 16 + start_point.Y);
	printf("          ■                   ");
	gotoxy(45 + start_point.X, 17 + start_point.Y);
	printf("          ■                   ");
	gotoxy(45 + start_point.X, 18 + start_point.Y);
	printf("          ■                   ");
	gotoxy(45 + start_point.X, 19 + start_point.Y);
	printf("          ■                   ");
}
void Map::go2(char go_color) {
	setColor(go_color);
	gotoxy(45 + start_point.X, 14 + start_point.Y);
	printf("          ■■■■■                ");
	gotoxy(45 + start_point.X, 15 + start_point.Y);
	printf("      ■■    ■    ■■            ");
	gotoxy(45 + start_point.X, 16 + start_point.Y);
	printf("            ■        ■            ");
	gotoxy(45 + start_point.X, 17 + start_point.Y);
	printf("          ■                        ");
	gotoxy(45 + start_point.X, 18 + start_point.Y);
	printf("        ■                          ");
	gotoxy(45 + start_point.X, 19 + start_point.Y);
	printf("      ■                            ");
}


void Map::setCursorView(bool visible) {
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void Map::story() {
	gotoxy(10, 1);setColor(14);
	printf("테");Sleep(100);printf("트");Sleep(100);printf("리");Sleep(100);
	printf("스 ");Sleep(100);printf("마");Sleep(100);printf("을");Sleep(00);
	printf("에 ");Sleep(100);printf("내");Sleep(100);printf("려");Sleep(100);
	printf("오");Sleep(100);printf("는 ");Sleep(100);printf("전");Sleep(100);
	printf("설");Sleep(100);
	setColor(GRAY);printf("...");Sleep(100);printf(" ...");Sleep(300);
	gotoxy(5 + start_point.X, 6 + start_point.Y);setColor(WHITE);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(5 + start_point.X, 7 + start_point.Y);
	printf("┃              테트리스 광산에                 ┃");
	gotoxy(5 + start_point.X, 8 + start_point.Y);
	printf("┃           다이아몬드 블록이 있다 !!          ┃");
	gotoxy(5 + start_point.X, 9 + start_point.Y);
	printf("┃");setColor(RED);printf("            WARNING: 파수꾼 있음             ");setColor(WHITE);printf(" ┃");
	gotoxy(5 + start_point.X, 10 + start_point.Y);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	Sleep(1000);setColor(GRAY);
	gotoxy(5 + start_point.X, 12 + start_point.Y);setColor(9);
	printf("돈도 없고 대학 과제에 시달리는 A씨");Sleep(500);
	gotoxy(5 + start_point.X, 13 + start_point.Y);
	printf("테트리스 광산에 다이아몬드 블록을 찾으러 가기로 결심!");Sleep(500);
	gotoxy(10 + start_point.X, 15 + start_point.Y);
	printf("A");Sleep(100);printf("씨");Sleep(100);
	go(WHITE);Sleep(700);go2(WHITE);Sleep(700);
	go(WHITE);Sleep(700);go2(WHITE);Sleep(700);
	go2(BLACK);
	setColor(GRAY);
	gotoxy(13 + start_point.X, 15 + start_point.Y);Sleep(100);
	printf(" 곡괭이를 들고 테트리스 광산으로...."); Sleep(3000);
	system("cls");

}
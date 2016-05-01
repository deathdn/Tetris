#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include "table.h"


void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	k;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&k);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

void gotoxy(int x, int y)		//chuyen con tro ve vi tri x, y
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

Table::Table( )		//khoi tao bang
{
	for ( int i = 1; i < 25; ++i )		//vung nhin thay
		for ( int j = 1; j <= 10; ++j )
			table[i][j] = 0;
	for ( int i = 1; i < 25; ++i )		//bien doc
		table[i][0] = table[i][11] = 1;

	for ( int i = 0; i < 12; ++i )		//bien ngang
		table[0][i] = 1;
	score = 0;
}


void Table::show( ) const
{
	//clrscr( );
	//system("cls");
	gotoxy(0,0);
	char chr = 219;

	for ( int i = 20 ; i >= 1; i-- )
	{	
		std::cout << "||";	//bien
		for ( int j = 1; j <= 10; ++j )	
		{	
			// for ( int j = 0; j < 10; ++j )
			// 	{
			// 		if ( table[i][j] > 0 && k == 0)
			// 			std::cout << ul << uc <<ur;
			// 		else if ( table[i][j] > 0 && k == 1 )
			// 			std::cout << dl << dc <<dr;
			// 		else
			// 			std::cout << "   ";
			// 	}
			if ( table[i][j] )
				std::cout << chr << chr;
			else
				std::cout << "  ";
		}
		std::cout << "||" << std::endl;
	}

	for ( int j = 0; j < 24; ++j )
		std::cout << '=';
	std::cout << std::endl << "Score: " << score;
}


void Table::create ( )
{
	table[ pos[0][0] = 22 ][ pos[0][1] = 5] = 2;
	table[ pos[1][0] = 21 ][ pos[1][1] = 5] = 2;
	switch( style = rand() % 7 )
	{
		case 0:			// khoi O
		table[ pos[2][0] = 22 ][ pos[2][1] = 6] = 2;
		table[ pos[3][0] = 21 ][ pos[3][1] = 6] = 2;
		break;
			case 1:			//khoi I
			table[ pos[2][0] = 23 ][ pos[2][1] = 5] = 2;
			table[ pos[3][0] = 24 ][ pos[3][1] = 5] = 2;
			break;
				case 2:			//khoi 	J
				table[ pos[2][0] = 23 ][ pos[2][1] = 6] = 2;
				table[ pos[3][0] = 23 ][ pos[3][1] = 5] = 2;
				break;
					case 3:			//khoi L
					table[ pos[2][0] = 23 ][ pos[2][1] = 5] = 2;
					table[ pos[3][0] = 21 ][ pos[3][1] = 6] = 2;
					break;
				case 4:			//khoi T
				table[ pos[2][0] = 21 ][ pos[2][1] = 6] = 2;
				table[ pos[3][0] = 23 ][ pos[3][1] = 5] = 2;
				break;
			case 5:			//khoi S
			table[ pos[2][0] = 21 ][ pos[2][1] = 4] = 2;
			table[ pos[3][0] = 22 ][ pos[3][1] = 6] = 2;
			break;
		case 6:			//khoi Z
		table[ pos[2][0] = 21 ][ pos[2][1] = 6] = 2;
		table[ pos[3][0] = 22 ][ pos[3][1] = 4] = 2;
		break;
	}
}

void Table::setBrickNum ( int number )
{
	for ( int i = 0 ; i < 4 ; ++i )
		table[ pos[i][0] ][ pos [i][1] ] = number;
}


bool Table::spin ( )			//quay pi/2, neu la hinh vuong tra ve 0
{
	if ( style == 0 )	//la kieu O thi dung lai
		return FALSE;

	int deltaX, deltaY;
	int oldPos[4][2];	//luu vi tri luc dau
	for ( int i = 0; i < 4; ++i )		// sao chep vi tri
		oldPos[i][0] = pos[i][0] , oldPos[i][1] = pos[i][1];

	setBrickNum( 0 );	//xoa bo tam khoi gach
	for ( int i = 1; i < 4; ++i )
	{
		deltaX = pos[i][0] - pos[0][0];
		deltaY = pos[i][1] - pos[0][1];

		table[ pos[i][0] ][ pos[i][1] ] = 0;	//xoa bo trang thai 

		pos[i][0] = pos[0][0] + deltaY;
		pos[i][1] = pos[0][1] - deltaX;

		if ( table[ pos[i][0] ][ pos[i][1] ] == 1 )		//kiem tra co gach bi vuong khi quay ko
		{
			for ( int i = 0; i < 4; ++i )		// phuc hoi vi tri
				pos[i][0] = oldPos[i][0] , pos[i][1] = oldPos[i][1];	

			setBrickNum( 2 );	//phuc hoi khoi gach		
			return FALSE;
		}
	}

	setBrickNum( 2 ); //phuc hoi khoi gach		
	show( );	//ve lai
	return TRUE;


}
void Table::moveLeft ( )
{
	if ( checkMoveLeft() )
	{
		setBrickNum ( 0 );	// xoa

		table[ pos[0][0] ][ --pos[0][1] ] = 2;	//tai lap
		table[ pos[1][0] ][ --pos[1][1] ] = 2;
		table[ pos[2][0] ][ --pos[2][1] ] = 2;
		table[ pos[3][0] ][ --pos[3][1] ] = 2;
		
		show( );
	}

}

void Table::moveRight ( )
{
	if ( checkMoveRight() )
	{
		setBrickNum ( 0 );	// xoa

		table[ pos[0][0] ][ ++pos[0][1] ] = 2;	//tai lap
		table[ pos[1][0] ][ ++pos[1][1] ] = 2;
		table[ pos[2][0] ][ ++pos[2][1] ] = 2;
		table[ pos[3][0] ][ ++pos[3][1] ] = 2;
		
		show( );
	}

}

void Table::moveDown ( )
{
	if ( checkMoveDown() )
	{
		setBrickNum ( 0 );	// xoa

		table[ --pos[0][0] ][ pos[0][1] ] = 2;	//tai lap
		table[ --pos[1][0] ][ pos[1][1] ] = 2;
		table[ --pos[2][0] ][ pos[2][1] ] = 2;
		table[ --pos[3][0] ][ pos[3][1] ] = 2;
		
		show( );		
	}
}


void Table::fall ( )
{
	while ( checkMoveDown() )			//dich xuong neu co the
	{
		setBrickNum ( 0 );	// xoa

		table[ --pos[0][0] ][ pos[0][1] ] = 2;	//tai lap
		table[ --pos[1][0] ][ pos[1][1] ] = 2;
		table[ --pos[2][0] ][ pos[2][1] ] = 2;
		table[ --pos[3][0] ][ pos[3][1] ] = 2;
	}
}

bool Table::checkMoveLeft ( ) const
{
	if ( table[ pos[0][0] ][ pos[0][1] - 1 ] == 1
		 || table[ pos[1][0] ][ pos[1][1] - 1 ] == 1
		 || table[ pos[2][0] ][ pos[2][1] - 1 ] == 1
		 || table[ pos[3][0] ][ pos[3][1] - 1 ] == 1 )

		return FALSE;
	else
		return TRUE;

}

bool Table::checkMoveRight ( ) const
{
	if ( table[ pos[0][0] ][ pos[0][1] + 1 ] == 1
		 || table[ pos[1][0] ][ pos[1][1] + 1 ] == 1
		 || table[ pos[2][0] ][ pos[2][1] + 1 ] == 1
		 || table[ pos[3][0] ][ pos[3][1] + 1 ] == 1 )

		return FALSE;
	else
		return TRUE;

}

bool Table::checkMoveDown ( )
{
	if ( table[ pos[0][0] - 1 ][ pos[0][1] ] == 1
		 || table[ pos[1][0] - 1 ][ pos[1][1] ] == 1
		 || table[ pos[2][0] - 1 ][ pos[2][1] ] == 1
		 || table[ pos[3][0] - 1 ][ pos[3][1] ] == 1 )

	{	 
		setBrickNum ( 1 );	///bien thanh gach cu
		return FALSE;
	}
	else  
		return TRUE;
	
}

void Table::getFullRows ( )	//tra ve hang full gach va tang diem
{
	int sum;
	for ( int i = 20; i > 0; -- i )
	{
		sum = 0;
		for ( int j = 1; j <= 10; ++j )
			sum += table[i][j];
		if ( sum == 10 )
			delRow( i );
	}
}
bool Table::checkGameOver ( ) const		//GameOver??
{
	for ( int i = 0; i < 4; ++i )
		if ( pos[i][0] > 20 ) //cham max
			return TRUE;
	return FALSE;
}

void Table::delRow ( int row )	//xoa hang  row  (xoa den dau ve lai den do)
{
	for ( int j = row ; j < 21; ++j )
		for ( int k = 1; k <= 10; ++k )
			table[j][k] = table[j + 1][k];
	score ++;
	show( );	//ve lai
}

int Table::getScore ( ) const { return score; }


// int main()
// {
// 	Table t;

// 	while (1 )
// 	{
// 		t.create();
// 		t.moveDown();
// 		t.moveDown();
// 		t.moveDown();
// 		t.moveDown();	getch();
// 		t.moveDown();	getch();
// 		t.moveDown();	getch();
// 		t.spin();	getch();
// 		t.spin();	getch();
// 		t.spin();	getch();
// 		t.moveDown();	getch();
// 		t.moveDown();	getch();
// 		t.show();
// 		getch();
// 		t.moveRight();t.show();	getch();
// 		t.moveRight();t.show();
// 		t.moveLeft();t.show();	getch();
// //		t.moveDown();t.show();
// 		t.fall();t.show();	getch();
// 		t.delRow( 2 );
// 	}
// }

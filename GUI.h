#ifndef __GUI_H__
#define __GUI_H__

#include "table.h"
#include "table.cpp"
#include "console.h"

void mainMenu( );	//man hinh khoi dong
bool start ( int level );		//bat dau choi, lay diem tu play( )
int settings( );	//cai dat
void info( );		//thong tin game
bool quit( );		//thoat game

void printHeader( );	//cls va in ra chua tetris tren 6 dong dau
int  play( int level );		//tra ve diem cua lan choi do
void settingsColor( );	//thay mau trong settings
int settingsLevel( );	//thay va tra ve do kho 1 - easy, 2 - normal, 3 - hard
int randIDBrick(); //tao so ngau nhien
void printNextBrickFrame(); //In ra khung hien vien gach tiep theo
void printOption(int x1, int x2, int y); //In tuy chon, x1, x2, y la toa do 
void delOption(int x1, int x2, int y); //Xoa tuy chon cu

void mainMenu( )
{
	char key;
	int level; //easy
	bool exit;		//ktra thoat
	int y = 13; //Toa do dau tien cua con tro

	level = 1;
	exit = FALSE;

	setTextColor( LIGHTGREEN );

	while ( !exit )		 		//chay den khi co lenh thoat
	{
		printHeader( );		//in ra 
	
		gotoxy( 20, 10); std::cout << "                     MAIN MENU                     ";
		gotoxy( 20, 13); std::cout << "                       START                       ";
		gotoxy( 20, 15); std::cout << "                      SETTINGS                     ";
		gotoxy( 20, 17); std::cout << "                       INFO                        ";
		gotoxy( 20, 19); std::cout << "                       QUIT                        ";
		
		while( 1 )
		{
			printOption(28, 60, y);
			
			key = getch( );	
			
			if(key == 's' || key == 'S') //Di chuyen con tro xuong
			{
				if(y <= 17)
					y += 2;
			}
			else if(key == 'w' || key == 'W') //Di chuyen con tro len
			{
				if(y >= 15)
					y -= 2;
			}

			printOption(28, 60, y);
			
			if(key == 13)
				break;
		}
		
		if(y == 13)
			exit = !start( level );
		else if(y == 15)
			level = settings( );
		else if(y == 17)
			info( );
		else if(y == 19)
			exit = quit( );	
	}

}

bool start( int level )
{
	int score;
	std::cout <<"Don't delete this line";

	score = play( level );		//chuyen level ve so

	if ( score == -1 )		//thoat ctr
		return FALSE;
	//gameOver == TRUE
	gotoxy( 20, 9 ); std::cout << "                                                   ";
	gotoxy( 20, 10); std::cout << "_______________________GAME OVER___________________";
	gotoxy( 20, 11); std::cout << "                                                   ";
	gotoxy( 20, 12); std::cout << "                YOUR SCORE : " << score << "             ";
	gotoxy( 20, 13); std::cout << "                                                   ";

	Sleep( 5000 );		// wait 5 second
	
	return TRUE;	//tiep tuc
}

int settings( )
{
	char key;
	int level = 1;	
	int y = 13; //Toa do dau tien cua con tro

	while ( 1 )
	{
		printHeader( );

		gotoxy( 20, 10); std::cout << "                      SETTINGS                     ";
		gotoxy( 20, 13); std::cout << "                       COLOR                       ";
		gotoxy( 20, 15); std::cout << "                       LEVEL                       ";
		gotoxy( 20, 17); std::cout << "                       BACK                        ";
		
		while( 1 )
		{
			printOption(28, 60, y);
			
			key = getch( );	
			
			if(key == 's' || key == 'S') //Di chuyen con tro xuong
			{
				if(y <= 15)
					y += 2;
			}
			else if(key == 'w' || key == 'W') //Di chuyen con tro len
			{
				if(y >= 15)
					y -= 2;
			}

			printOption(28, 60, y);
			
			if(key == 13)
				break;
		}
		
		if(y == 13)
			settingsColor( );
		else if(y == 15)
			level = settingsLevel( );
		else if(y == 17)
			return level;
	}
}

void settingsColor( )
{
	char key;
	bool exit = 0;		//ktra thoat

	gotoxy( 15, 15);	std::cout << "NOTE: If you don't see any color of 8 colors";
	gotoxy( 15, 16);	std::cout << "     Perhaps it's your background color     ";
	gotoxy( 15, 17);	std::cout << "                                            ";

	gotoxy( 20, 18); 
	setTextColor(BLACK);	std::cout << "1.BLACK   ";
	setTextColor(BLUE);		std::cout << "2.BLUE    ";
	setTextColor(GREEN);	std::cout << "3.GREEN   ";
	setTextColor(CYAN);		std::cout << "4.CYAN    ";

	gotoxy( 20, 20); 
	setTextColor(RED);		std::cout << "5.RED     ";
	setTextColor(PURPLE);	std::cout << "6.PURPLE  ";
	setTextColor(GRAY);		std::cout << "7.GRAY    ";
	setTextColor(WHITE);	std::cout << "8.WHITE   ";

	while ( 1 )
	{
		key = getch( );

		if ( key == '1' )	setTextColor( BLACK );
		else if ( key == '2' )	setTextColor( BLUE  );
		else if ( key == '3' )	setTextColor( GREEN );
		else if ( key == '4' )	setTextColor( CYAN  );
		else if ( key == '5' )	setTextColor( RED   );
		else if ( key == '6' )	setTextColor( PURPLE);
		else if ( key == '7' )	setTextColor( GRAY  );
		else if ( key == '8' )	setTextColor( WHITE );

		if ( key >= '1' && key <= '8' )
			return;							//ket thuc ham khi da doi mau
	}
}

int settingsLevel( )
{
	char key;

	gotoxy( 20, 19);
	std::cout << " CHOOSE LEVEL:    1. EASY     2. NORMAL     3. HARD ";
	while( ! ( key = getch( ) >= '1' && key <= '3' ) )		//lap den khi doc dung phim
	{
		//do nothing
	}

	return (int) key;
}
void info( )		//thong tin game
{
	printHeader( );

	system("notepad README.txt");
}
bool quit( )		//thoat game
{
	if ( confirm( "EXIT") )
		return 1;		//thoat game
	return 0;
}



void printHeader( )
{

	system( "cls" );

	gotoxy( 20, 1 ); std::cout << " __________ ________ __________ _________ ___ ___________";
	gotoxy( 20, 2 ); std::cout << "/___   ___//  _____//___   ___//        //  //  ________/";
	gotoxy( 20, 3 ); std::cout << "   /  /   /  /___      /  /   /   /____//  //  /_______";
	gotoxy( 20, 4 ); std::cout << "  /  /   /  ____/     /  /   /  ___   //  //_______   /";
	gotoxy( 20, 5 ); std::cout << " /  /   /  /____     /  /   /  /  /  //  / _______/  /";
	gotoxy( 20, 6 ); std::cout << "/__/   /_______/    /__/   /__/  /__//__/ /_________/";
}

int randIDBrick()
{
	srand(time(NULL));
	return rand() % 7;
}

int play( int level )
{
	Table t;	// choi tren Table nay
	double timeDelay = 1000 - level * 300 ;	//thoi gian de roi
	char key;		//phim bam vao
	int IDBrick, IDNextBrick; //So thu tu cua gach
	
	system( "cls" );
	
	//Tao 2 khoi gach dau tien
	IDBrick = randIDBrick(); 
	IDNextBrick = randIDBrick();
	
	while ( t.checkGameOver() == 0 )
	{	
		t.create( IDBrick );	//tao khoi moi
			
		while ( t.checkMoveDown( ) )
		{
			//In ra vien gach tiep theo
			gotoxy(56, 2);
			std::cout << "NEXT";
			//Ve them cai khung cho dep :v
			printNextBrickFrame();
			setTextColor( LIGHTGREEN );
			t.printNextBrick( IDNextBrick );
		
			Sleep( ( timeDelay *= 0.998 ) );
			
			while ( kbhit() ) 				//doi phim an	
	        {
	        	key = getch();

	        	if ( key == 'a' || key == 'A' ) 			// dich trai neu nhap A
	        		t.moveLeft( );
	        	else if ( key == 'd' || key == 'D' ) 		// dich phai neu nhap D
	        		t.moveRight( );
	        	else if ( key == 's' || key == 'S') 		// roi luon neu nhap s
	        		t.fall( );
	        	else if ( key == 'w' || key == 'W' ) 		// xoay
	        		t.spin( );
	        	else if ( key == 'p' || key == 'P' || key == 13 )		// tam dung pause
        		while ( 1 ) //man hinh pause 
        		{
        			system( "cls" );	//xoa man hinh, chong gian lan
        			gotoxy( 35, 9 );
        			std::cout << "PAUSE";
        			gotoxy( 30, 12 );
        			std::cout << "   RESUME";
        			gotoxy( 30, 14 );
        			std::cout << "   RESTART";
        			gotoxy( 30, 16 );
        			std::cout << "   MAIN MENU";

        			int y = 12; // Toa do dau tien cua con tro
					while( 1 )
					{
						printOption(20, 50, y);
						
						key = getch( );	
						
						if(key == 's' || key == 'S') //Di chuyen con tro xuong
						{
							if(y <= 14)
								y += 2;
						}
						else if(key == 'w' || key == 'W') //Di chuyen con tro len
						{
							if(y >= 14)
								y -= 2;
						}
			
						printOption(20, 50, y);
						
						if(key == 13)
							break;
					}
					
					if(y == 12) //tiep tuc
					{
						delOption(20, 50, y);
						break;
					}
					else if(y == 14 && confirm("RESTART") ) //choi lai ( can  xac nhan )
						return play( level );
					else if(y == 16 && confirm("BACK TO MAIN MENU") ) //quay ve
						return restart( );
        		}	        		
	        }
	       t.moveDown( );		// dich xuong
	   	}

	   	t.getFullRows( );	//lay diem
	   	IDBrick = IDNextBrick; //Gan khoi cu thanh khoi moi
		IDNextBrick = randIDBrick(); //Tao khoi gach tiep theo
	}

	return t.getScore( );	//lay diem 

}

void printNextBrickFrame()
{
	int i;
	setTextColor( LIGHTGRAY );
	gotoxy( 56, 4 );
	for ( i = 0; i < 12; i++ )
		std::cout << (char)220;
	for ( i = 5 ; i < 10; i++ )
	{
		gotoxy( 56, i );
		std::cout << (char)221;	//bien
	}
	for ( i = 5 ; i < 10; i++ )
	{
		gotoxy( 67, i );
		std::cout << (char)222;	//bien
	}
	gotoxy( 56, 9 ); 
	for ( i = 0; i < 12; i++ )
		std::cout << (char)223;
}

void printOption(int x1, int x2, int y)
{
	gotoxy( x1, y );
	std::cout << "-->";
	gotoxy( x2, y );
	std::cout << "<--";
	
	//Xoa con tro cu di
	gotoxy( x1, y+2 );
	std::cout << "   ";
	gotoxy( x2, y+2 );
	std::cout << "   ";

	gotoxy( x1, y-2 );
	std::cout << "   ";
	gotoxy( x2, y-2 );
	std::cout << "   ";
}

//Xoa con tro vua hien len man hinh
void delOption(int x1, int x2, int y)
{
	gotoxy( x1, y );
	std::cout << "   ";
	gotoxy( x2, y );
	std::cout << "   ";
}

#endif //__GUI_H__

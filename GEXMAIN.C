#include<alloc.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE		1
#define	FALSE		0

#define X_AXIS		640
#define Y_AXIS		480
#define X_AXIS_H	320
#define Y_AXIS_H	240

#define	X_START		95
#define	X_END		545
#define	X_DIFF		160
#define	Y_START		95
#define	Y_END		395
#define	Y_DIFF		40
#define	COLS		3
#define	ROWS		8

int callmouse(void);					/* loads mouse driver */
void menubox(void);
void welcome(void);
void load_graphics(void);				/* loads graphics driver */
void mouseposition(int *xpos, int *ypos, int *click);
void setposition(int xpos, int ypos);
void process();
extern int bounds(int, int, int, int);	/* asm */
extern int item(int, int);				/* asm */
extern int modulo(int);					/* asm */
extern int prices(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);	/* asm */
extern int select(int, int, int);		/* asm */
extern int set(int, int, int, int);		/* asm */
extern char *string(int);				/* asm */
extern int total();						/* asm */

union REGS in, out;


main()
{
	clrscr();
	/*welcome();*/
	menubox();
}

void welcome(void)
{
	int mousepress, keypress;
	int gm, gd = DETECT;
	int x, y, click = FALSE;

	initgraph(&gd, &gm, "");
	setfillstyle(SOLID_FILL, BLUE);				bar(0, 0, X_AXIS, Y_AXIS);
	setcolor(LIGHTGREEN);
	line(0, Y_AXIS_H, X_AXIS, Y_AXIS_H);		/* x-axis */
	line(X_AXIS_H, 0, X_AXIS_H, Y_AXIS);		/* y-axis */

	setposition(639, 479);
	callmouse();

	setcolor(LIGHTCYAN);	outtextxy(60, 60, "Welcome to");
	setcolor(LIGHTGREEN);	outtextxy(150, 60, "Grocer Express");
	setcolor(YELLOW); 		outtextxy(110, 75, "Beta Version");
	setcolor(WHITE); 		outtextxy(85, 95, "CMSC 131 Program");
	setcolor(LIGHTRED); 	outtextxy(45, 145, "University of the Philippines");
	setcolor(LIGHTRED); 	outtextxy(50, 160, "in the Visayas Cebu College");

	setcolor(WHITE);		outtextxy(425, 300, "Program Features");
	setcolor(LIGHTCYAN); 	outtextxy(360, 330, "» Simulates Grocery Selection");
	setcolor(LIGHTRED);		outtextxy(360, 350, "» Tenders Payment Transactions");
	setcolor(YELLOW);	 	outtextxy(360, 370, "» Sorts Purchases into Bags");
	setcolor(LIGHTGREEN);	outtextxy(360, 390, "» Coded in Turbo C and Assembly");
	setcolor(LIGHTGREEN);	outtextxy(360, 390, "» Comes with beta mouse support");

	do
	{
		mouseposition(&x, &y, &click);
		mousepress = click;
		keypress = kbhit();
	}while(!mousepress && !keypress);

	closegraph();

	if(mousepress)
	{
		menubox();
	}
	else if(keypress)
	{
		if(getch() == 27)
		{
			exit(0);
		}
		else
		{
			menubox();
		}
	}

}


void menubox(void)
{
    char pt[3] = {' ', ' ', ' '}, amt[5] = {' ', ' ', ' ', ' ', ' '};
    int num[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int price[24] = {50, 24, 46, 87, 62, 39, 75, 99, 26, 90, 36, 65, 71, 60, 45, 83, 67, 90, 44, 59, 84, 96, 73, 98};
	int mousepress, keypress;
	int x, y, click = FALSE;
    int gm, gd = DETECT;
    int row, col, index, totalAmt;

    initgraph(&gd, &gm, "");
    setposition(639, 479);
	callmouse();

    setfillstyle(SOLID_FILL, BLUE);			bar(10, 10, 630, 470);
    setfillstyle(SOLID_FILL, LIGHTBLUE);	bar(60, 60, 575, 420);

	setcolor(LIGHTCYAN); 					outtextxy(250, 40, " GROCERY ITEMS ");
	setfillstyle(SOLID_FILL, WHITE);		setcolor(BLUE);
	bar(95, 95, 225, 115);					outtextxy(100, 100, "Alaska (Php 50)");
	bar(95, 135, 225, 155);					outtextxy(100, 140, "Alpine (Php 24)");
	bar(95, 175, 225, 195);					outtextxy(100, 180, "Anchor (Php 46)");
	bar(95, 215, 225, 235);					outtextxy(100, 220, "Gain   (Php 87)");
	bar(95, 255, 225, 275);					outtextxy(100, 260, "Lactum (Php 62)");
	bar(95, 295, 225, 315);					outtextxy(100, 300, "Nido 1+(Php 39)");
	bar(95, 335, 225, 355);					outtextxy(100, 340, "Promil (Php 75)");
	bar(95, 375, 225, 395);					outtextxy(100, 380, "UCare  (Php 99)");

	bar(255, 95, 385, 115);					outtextxy(260, 100, "Cupcake(Php 26)");
	bar(255, 135, 385, 155);				outtextxy(260, 140, "Dingdon(Php 90)");
	bar(255, 175, 385, 195);				outtextxy(260, 180, "Egg Nog(Php 36)");
	bar(255, 215, 385, 235);				outtextxy(260, 220, "Inipit (Php 65)");
	bar(255, 255, 385, 275);				outtextxy(260, 260, "Oreo   (Php 71)");
	bar(255, 295, 385, 315);				outtextxy(260, 300, "Pretzel(Php 60)");
	bar(255, 335, 385, 355);				outtextxy(260, 340, "Quake  (Php 45)");
	bar(255, 375, 385, 395);				outtextxy(260, 380, "SkyFlak(Php 83)");

	bar(415, 95, 545, 115);					outtextxy(420, 100, "Ariel  (Php 67)");
	bar(415, 135, 545, 155);				outtextxy(420, 140, "Breeze (Php 90)");
	bar(415, 175, 545, 195);				outtextxy(420, 180, "Champio(Php 44)");
	bar(415, 215, 545, 235);				outtextxy(420, 220, "MrClean(Php 59)");
	bar(415, 255, 545, 275);				outtextxy(420, 260, "Perla  (Php 84)");
	bar(415, 295, 545, 315);				outtextxy(420, 300, "Surf   (Php 96)");
	bar(415, 335, 545, 355);				outtextxy(420, 340, "Tide   (Php 73)");
	bar(415, 375, 545, 395);				outtextxy(420, 380, "Wings  (Php 98)");

	setcolor(YELLOW);						outtextxy(175, 430, "Total Cost of Grocery (Php)");
	setcolor(WHITE);						outtextxy(180, 450, "Press [Esc] to close Grocer Express");

	set(95, 545, 95, 395);			/* invoke asm procedure */
	bounds(160, 40, 3, 8);			/* invoke asm procedure */
	/*
	prices(50, 24, 46, 87, 62, 39, 75, 99, 26, 90, 36, 65, 71, 60, 45, 83, 67, 90, 44, 59, 84, 96, 73, 98);
	*/
	do
	{
		mouseposition(&x, &y, &click);
		if(click)
		{
			index = item(x,y);			/* invoke asm procedure */
			++num[index];

			if(index >= 0 && index <= 23 && num[index] >=0 && num[index] <= 99)
			{
				delay(7000);
				/*printf("%d \r", num[index]);*/

				pt[0] = string((int)(num[index]/10));	/* invoke asm procedure */
				pt[1] = string(num[index]%10);			/* invoke asm procedure */

				x = (int)(index/ROWS);
				y = index % ROWS;


				setfillstyle(SOLID_FILL, LIGHTBLUE);
				bar(x*X_DIFF+X_START+130, y*Y_DIFF+Y_START, x*X_DIFF+X_START+150, y*Y_DIFF+Y_START+20);
				setcolor(YELLOW);
				outtextxy(x*X_DIFF+X_START+133, y*Y_DIFF+Y_START+5, pt);

				select(index, num[index], price[index]);
				strcpy(amt, "     ");

				totalAmt = total();
				amt[0] = string((int)(totalAmt/10000));		/* invoke asm procedure */
				amt[1] = modulo(totalAmt%10000);			/* invoke asm procedure */
				amt[2] = modulo(totalAmt%1000);				/* invoke asm procedure */
				amt[3] = modulo(totalAmt%100);				/* invoke asm procedure */
				amt[4] = string(totalAmt%10);				/* invoke asm procedure */

				if(totalAmt < 10000)	amt[0] = ' ';
				if(totalAmt < 1000)		amt[1] = ' ';
				if(totalAmt < 100)		amt[2] = ' ';

				setfillstyle(SOLID_FILL, BLUE);	bar(420, 430, 480, 450);
				setcolor(WHITE);				outtextxy(420, 430, amt);
			}
		}

		mousepress = click;
		keypress = kbhit();
	}while(!keypress);
}

void process()
{
	process(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23);
}

void load_graphics(void)
{
	int gerror;
	int gdriver = DETECT;
	int gmode = 0;

	initgraph(&gdriver, &gmode,"");

	if ((gerror = graphresult()) != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(gerror));
		printf("\nPress any key to terminate the program.");
		getch();
		exit(1);
	}

	setcolor(RED);
	line(0, Y_AXIS_H, X_AXIS, Y_AXIS_H);	/* x-axis */
	line(X_AXIS_H, 0, X_AXIS_H, Y_AXIS);	/* y-axis */

	outtextxy(X_AXIS_H+10, 5, "Y");
	outtextxy(X_AXIS-15, Y_AXIS_H+5, "X");
}

int callmouse(void)
{
	  in.x.ax = 1;
	  int86(51,&in,&out);

	  return TRUE;
}

void setposition(int xpos, int ypos)
{
	 in.x.ax = 4;
	 in.x.cx = xpos;
	 in.x.dx = ypos;
	 int86(51,&in,&out);
}

void mouseposition(int *xpos, int *ypos, int *click)
{
	in.x.ax = 3;
	int86(51,&in,&out);

	*click = out.x.bx;
	*xpos = out.x.cx;
	*ypos = out.x.dx;
}
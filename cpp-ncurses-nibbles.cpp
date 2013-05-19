//ncurse nibbles
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <time.h>
int main(){
	int cp;
	initscr();
   	noecho();
   	cbreak();
   	timeout(100);
	curs_set(0);
	srand (time(NULL));
        start_color();
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	const int food = 127;
	int shasmoved = 0;
	int sdirection = KEY_UP;
	int slength = 5;
	int salive = 1;
	char gdata[LINES][COLS] ;
	for (int il=0; il < LINES; ++il){
		for (int ic=0; ic < COLS; ++ic){
			gdata[il][ic]=0;
		}
	}
	gdata[LINES/2][COLS/2] = 1;
	gdata[rand() % LINES][rand() % COLS] = food;
	keypad(stdscr, TRUE);
	do{
		salive=0;
		for (int il=0; il < LINES; ++il){
			for (int ic=0; ic < COLS; ++ic){
				if (gdata[il][ic]==1){salive=1;};
			}
		}
		shasmoved=0;
		int c;
		c = getch();
		for (int vy = 0; vy < LINES; ++vy){
			for (int vx = 0; vx < COLS; ++vx){
				if (gdata[vy][vx]>1 && gdata[vy][vx]<food){gdata[vy][vx] = gdata[vy][vx]+1;};
				if (gdata[vy][vx]>slength+1 && gdata[vy][vx]!=food){gdata[vy][vx]=0;};
				if (gdata[vy][vx]==1){
					if (shasmoved==0){
						if (c!=KEY_UP && c!=KEY_DOWN && c!=KEY_LEFT && c!=KEY_RIGHT && c!=113 && c!=27){c=sdirection;}		
						if (c==KEY_LEFT){
							gdata[vy][vx]=2;
							if (gdata[vy][vx-1]==food) {++slength; 	gdata[rand() % LINES][rand() % COLS] = food;}; 
							if (gdata[vy][vx-1]>0 && gdata[vy][vx-1]!=food) {salive = 0;};
							if (vx==0){salive=0;};
							gdata[vy][vx-1]=1;
							sdirection=KEY_LEFT;};
						if (c==KEY_UP){
							gdata[vy][vx]=2; 
							if (gdata[vy-1][vx]==food) {++slength; 	gdata[rand() % LINES][rand() % COLS] = food;};							
							if (gdata[vy-1][vx]>0 && gdata[vy-1][vx]!=food) {salive = 0;};
							if (vy==0){salive=0;};
							gdata[vy-1][vx]=1;
							sdirection=KEY_UP;};
						if (c==KEY_RIGHT){
							gdata[vy][vx]=2; 
							if (gdata[vy][vx+1]==food) {++slength; 	gdata[rand() % LINES][rand() % COLS] = food;};
							if (gdata[vy][vx+1]>0 && gdata[vy][vx+1]!=food) {salive = 0;};							
							if (vx+1>=COLS){salive=0;};							
							gdata[vy][vx+1]=1;
							sdirection=KEY_RIGHT;};
						if (c==KEY_DOWN){
							gdata[vy][vx]=2;
							if (gdata[vy+1][vx]==food) {++slength; gdata[rand() % LINES][rand() % COLS] = food;};
							if (gdata[vy+1][vx]>0 && gdata[vy+1][vx]!=food) {salive = 0;};
							if (vy+1>LINES){salive=0;};
							gdata[vy+1][vx]=1;
							sdirection=KEY_DOWN;};
						shasmoved=1;
					}
				}
				attron(COLOR_PAIR(1));
				if (gdata[vy][vx]>=1){mvprintw(vy, vx, " ");};
				attroff(COLOR_PAIR(cp));
				attron(COLOR_PAIR(2));
				if (gdata[vy][vx]==0){mvprintw(vy, vx, " ");};
				attroff(COLOR_PAIR(cp));
			}
		}
		refresh();
		if (c==113 | c==27 | salive==0){break;}
	}while(1==1);
        endwin();
	return 0;
}

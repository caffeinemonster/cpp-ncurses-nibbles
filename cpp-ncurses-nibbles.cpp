//all your base are blong to us!!!
//console ncurses screen saver
#include <stdio.h>
//#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <cstring>
#include <time.h>

int main(){
	int cp;
	initscr();	  /* Start curses mode 		  */
   	noecho();         // dont display input
   	cbreak();         // don't interrupt for user input
   	timeout(100);     // wait 500ms for key press
	curs_set(0);	  // dont display cursor
	srand (time(NULL)); // seed rnumber generator
        start_color();			/* Start color*/
	init_pair(1, COLOR_BLACK, COLOR_GREEN);  // setup colour pair
	init_pair(2, COLOR_GREEN, COLOR_BLACK);  // setup colour pair
	const int food = 127; // value for food in array
	int shasmoved = 0; // marker has snake moved this fram?
	int sdirection = KEY_UP; // store direction of travel
	int slength = 5; // length of snake
	int salive = 1; // is the snae alive
//	int score = 0; // var for score
	char gdata[LINES][COLS] ;//= { {0 } };
	for (int il=0; il < LINES; ++il){
		for (int ic=0; ic < COLS; ++ic){
			gdata[il][ic]=0;		
		}	
	} // initialise array
	gdata[LINES/2][COLS/2] = 1; // set start position
	gdata[rand() % LINES][rand() % COLS] = food;//food; // add food to array
	keypad(stdscr, TRUE); // capture function keys f1 f2 etc
	do{
		salive=0; 
		for (int il=0; il < LINES; ++il){
			for (int ic=0; ic < COLS; ++ic){
				if (gdata[il][ic]==1){salive=1;};		
			}	
		} // initialise array	
		shasmoved=0;
		int c;		    // define variable to store key pressed
		c = getch();        // store key pressed in variable c		
		for (int vy = 0; vy < LINES; ++vy){
			for (int vx = 0; vx < COLS; ++vx){
							
				if (gdata[vy][vx]>1 && gdata[vy][vx]<food){gdata[vy][vx] = gdata[vy][vx]+1;}; //if value greater than 1 and less than food value add 1 to it
				if (gdata[vy][vx]>slength+1 && gdata[vy][vx]!=food){gdata[vy][vx]=0;}; //gdata is greater than slength set it to 0	
				if (gdata[vy][vx]==1){ // if head of snake	
					if (shasmoved==0){ // check to see if snake has moved already
						if (c!=KEY_UP && c!=KEY_DOWN && c!=KEY_LEFT && c!=KEY_RIGHT && c!=113 && c!=27){c=sdirection;}		
						if (c==KEY_LEFT){
							gdata[vy][vx]=2;							
							if (gdata[vy][vx-1]==food) {++slength; 	gdata[rand() % LINES][rand() % COLS] = food;}; 
							if (gdata[vy][vx-1]>0 && gdata[vy][vx-1]!=food) {salive = 0;};							
							if (vx==0){salive=0;};
							gdata[vy][vx-1]=1;
							sdirection=KEY_LEFT;
						};//l a
						if (c==KEY_UP){
							gdata[vy][vx]=2; 
							if (gdata[vy-1][vx]==food) {++slength; 	gdata[rand() % LINES][rand() % COLS] = food;};							
							if (gdata[vy-1][vx]>0 && gdata[vy-1][vx]!=food) {salive = 0;};							
							if (vy==0){salive=0;};														
							gdata[vy-1][vx]=1;
							sdirection=KEY_UP;
						};//u w
						if (c==KEY_RIGHT){
							gdata[vy][vx]=2; 
							if (gdata[vy][vx+1]==food) {++slength; 	gdata[rand() % LINES][rand() % COLS] = food;};
							if (gdata[vy][vx+1]>0 && gdata[vy][vx+1]!=food) {salive = 0;};							
							if (vx+1>=COLS){salive=0;};							
							gdata[vy][vx+1]=1;
							sdirection=KEY_RIGHT;};//r d
						if (c==KEY_DOWN){
							gdata[vy][vx]=2;
							if (gdata[vy+1][vx]==food) {++slength; gdata[rand() % LINES][rand() % COLS] = food;};
							if (gdata[vy+1][vx]>0 && gdata[vy+1][vx]!=food) {salive = 0;};
							if (vy+1>LINES){salive=0;};
							gdata[vy+1][vx]=1;
							sdirection=KEY_DOWN;
						};//d	asdas				
						shasmoved=1; // set marker to say snake has moved
					}
				}
				attron(COLOR_PAIR(1)); // enable colour pair
				if (gdata[vy][vx]>=1){mvprintw(vy, vx, " ");}; //if value greater than 1 fill square
				attroff(COLOR_PAIR(cp));// disable colour pair
				attron(COLOR_PAIR(2)); // enable colour pair
				if (gdata[vy][vx]==0){mvprintw(vy, vx, " ");}; //if value is 0 make sure reverse filled 
				attroff(COLOR_PAIR(cp));// disable colour pair	
				
			}
		}
		refresh();						
		if (c==113 | c==27 | salive==0){break;} // break if 'q' is pressed		
	}while(1==1); // loop until break
        endwin(); //End curses mode
	return 0;
}

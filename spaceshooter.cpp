#include <iostream>
#include "help.h"
#include <fstream>
#include <string>
using namespace std;
bool won = false;
int score = 0;
bool alienspaceshipcollission = false; // to check alien and spaceship collission
int lives = 3;
const int rows = 10;
const int cols = 5;
const float alienwidth = 20;  
const float alienheight = 20;
const float alienspacing_x = 20; // spacing btw alien
const float alienspacing_y = 15; // spacing btw alien
bool alienkilled = false;
bool aliens[rows][cols];   // array to check which alien alive and which not
float alien_x = 800;   // start position of alien (x)
float alien_y = 180; // start position of alien (y)
bool moveleft = true;
int highscorearray[5];   // array to store highscores
bool ispaused;

void drawSpaceship(int x, int y) {  // function to create spaceship
	
	myRect(x, y, x + 50, y + 30, 0, 128, 255); 
	
	myEllipse(x + 15, y - 10, x + 35, y + 10, 135, 206, 250, 0, 191, 255); 
	return;

}
void EraseSpaceship(int x, int y) {  // function to erase previous positions of spaceship
	myRect(x, y, x + 50, y + 30, 0, 0, 0);
	myEllipse(x + 15, y - 10, x + 35, y + 10, 0, 0, 0);
	return;
}

void drawAlien(int x, int y) {   // function to draw aliens
	
	myEllipse(x, y, x + 30, y + 25, 34, 139, 34, 50, 205, 50); 
	
	myEllipse(x + 8, y + 5, x + 12, y + 10, 255, 255, 255); 
	myEllipse(x + 18, y + 5, x + 22, y + 10, 255, 255, 255); 
	myEllipse(x + 9, y + 6, x + 11, y + 9, 0, 0, 0);         
	myEllipse(x + 19, y + 6, x + 21, y + 9, 0, 0, 0);        
	return;
}

void eraseAlien(int x, int y) {  // function to erase previous position of aliens

	myEllipse(x, y, x + 30, y + 25, 0, 0, 0); 
	
	myEllipse(x + 8, y + 5, x + 12, y + 10, 0, 0, 0); 
	myEllipse(x + 18, y + 5, x + 22, y + 10, 0, 0, 0); 
	myEllipse(x + 9, y + 6, x + 11, y + 9, 0, 0, 0);         
	myEllipse(x + 19, y + 6, x + 21, y + 9, 0, 0, 0);       
	return;
}
void savegame(int i_x, int i_y, int lives, int score, float alien_x, float alien_y, bool aliens[rows][cols]) { // function to save elements to a textfile
	ofstream savefile("savegame.txt");

	savefile << i_x << " " << i_y << endl;
	savefile << lives << endl;
	savefile << score << endl;
	savefile << alien_x << " " << alien_y << endl;


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			savefile << aliens[i][j] << " ";   
		}
		savefile << endl;
	}

	savefile.close();
	return;
}

bool loadgame(int& i_x, int& i_y, int& lives, int& score, float& alien_x, float& alien_y, bool aliens[rows][cols]) { // all by ref so that their current values are loaded. 
	ifstream loadfile("savegame.txt");


	loadfile >> i_x >> i_y;
	loadfile >> lives;
	loadfile >> score;
	loadfile >> alien_x >> alien_y;


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			loadfile >> aliens[i][j];
		}
	}

	loadfile.close();

	return true;
}


void pausegame() { // function to show pause game menu 

	myRect(0, 0, 1000, 800, 0, 0, 0);
	myRect(200, 20, 800, 820, 0, 0, 255);
	myRect(205, 25, 795, 815, 0, 0, 255);
	myRect(210, 30, 790, 810, 0, 0, 255);
	drawText(23, 435, 80, 255, 0, 0, "PAUSED");
	drawText(23, 437, 80, 255, 0, 0, "PAUSED");

	drawText(14, 230, 245, 255, 255, 255, "PRESS R");
	myRect(350, 220, 650, 300, 255, 0, 0);
	drawText(16, 420, 245, 255, 255, 255, "RESUME GAME");

	drawText(14, 230, 335, 255, 255, 255, "PRESS S");
	myRect(350, 310, 650, 390, 255, 0, 0);
	drawText(16, 425, 335, 255, 255, 255, "SAVE GAME");


	return;
}

void readfile(int highscorearray[]) {   // function to read file for highscores
	ifstream myfile("highscore.txt");
	for (int i = 0; i <= 4; i++) {
		myfile >> highscorearray[i];  // data read from array and put in file
	}
	return;
}
void writefile(int highscorearray[]) { // function to write data of highscores in textfile

	ofstream file("highscore.txt");
	for (int i = 0; i <= 4; i++) {

		file << highscorearray[i] << endl;   // data written into textfile
	}
	return;
}

void displayhighscore(int highscorearray[]) {  // function to display high scores

	myRect(0, 0, 1000, 800, 0, 0, 0);
	drawText(36, 400, 100, 255, 255, 255, "HIGH SCORES");
	for (int i = 0; i < 5; i++) {
		drawText(24, 400, 200 + i * 50, 255, 255, 255, to_string(highscorearray[i]).c_str());  // c_str() converts into character array// loop used to display 5 values 
	}
	Sleep(5000);   // sleep used to pause screen for 5 secs
}

void updatehighscore(int highscorearray[], int score) { // function to display high score

	for (int i = 0; i <= 4; i++) {  // loop used to carry out comparisons and switch positions
		if (score > highscorearray[i]) {

			for (int j = 4; j > i; j--) {       // insertion sort used here 
				highscorearray[j] = highscorearray[j - 1];
			}

			highscorearray[i] = score;
			break;
		}
	}
	return;
}
void displaylives() {
	drawText(16, 850, 85, 255, 255, 255, "LIVES");
	drawText(16, 950, 85, 255, 255, 255, "", true, lives);
	return;
}
void gameover() {

	myRect(0, 0, 1000, 800, 0, 0, 0);
	drawText(36, 355, 200, 255, 0, 0, "GAME OVER");
	drawText(24, 350, 300, 255, 255, 255, "Your Score:");
	drawText(24, 620, 300, 255, 255, 255, "", true, score);
	readfile(highscorearray);     // whenever game is over, data about highscore is read, updated, and written
	updatehighscore(highscorearray, score);
	writefile(highscorearray);
	Sleep(10000);  // to show screen for a while
	exit(0);
}



void wingame() {
	if (score >= 500) {

		myRect(50, 50, 1000, 600, 0, 0, 0);
		drawText(36, 260, 250, 0, 255, 0, "YOU HAVE WON!");
		readfile(highscorearray);   // again when player wins, data is read, updated and written into highscore file
		updatehighscore(highscorearray, score);
		writefile(highscorearray);
		Sleep(10000);
		exit(0);
	}
	return;
}


void initial_aliens() {    // initially all aliens are set to true meaning they are alive
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			aliens[i][j] = true;
		}
	}
	return;
}

void create_aliens() {   // function to create aliens
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {    // j is for columns and i is for rows. 
			if (aliens[i][j] == true) {

				int x = alien_x - j * (alienwidth + alienspacing_x);   // 800- (col *(width + spacing) ) // gradually , make aliens move left
				int y = alien_y + i * (alienheight + alienspacing_y);   // 100 - (rows*(width + spacing))


				drawAlien(x, y);
			}
		}
	}

	return;
}



void movealiens() {  //  function to make aliens move
	static bool movingdown = true; // static so that it holds value in function call as well


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (aliens[i][j] == true) {    
				int x = alien_x - j * (alienwidth + alienspacing_x);    // determines x position of alien     // column is for x axis, rows are for y axis
				int y = alien_y + i * (alienheight + alienspacing_y);   // determines the y position of aliens     i is row number so 
				                                                        // an aliens total height is alienheight + spacing in y.
																		// when i = 0
																		// y = 180
				                                                        // when i  = 1 
				                                                        // y = 180 + 1(20 + 15) = 215 , so the aliens are at a distance of 35 with eachother in y direction
				eraseAlien(x, y);
			}
		}
	}


	if (movingdown == true) {
		alien_y = alien_y + 2;
		if (alien_y + (rows * (alienheight + alienspacing_y)) >= 580) {
			movingdown = false;
			alien_x = alien_x - 15; // left move
		}
	}
	else {
		alien_y = alien_y - 2;
		if (alien_y <= 150) {
			movingdown = true;
			alien_x = alien_x - 15; // left move
		}
	}


	if (alien_x - cols * (alienwidth + alienspacing_x) <= 50) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				aliens[i][j] = false;
			}
		}
	}


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (aliens[i][j] == true) {
				int x = alien_x - j * (alienwidth + alienspacing_x);
				int y = alien_y + i * (alienheight + alienspacing_y);
				drawAlien(x, y);  
			}
		}
	}
	return;
}


void killaliens(float& bullet_x, float& bullet_y) {  // by reference used so that not the initial value of bullet is taken rather current value is taken

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (aliens[i][j] == true) {

				int x = alien_x - j * (alienwidth + alienspacing_x);
				int y = alien_y + i * (alienheight + alienspacing_y);


				if (bullet_x >= x && bullet_x <= x + alienwidth &&
					bullet_y >= y && bullet_y <= y + alienheight) {

					aliens[i][j] = false;
					alienkilled = true;
					score = score + 10;
					eraseAlien(x, y);

					myRect(bullet_x, bullet_y, bullet_x + 10, bullet_y + 2, 0, 0, 0, 0, 0, 0);

					bullet_x = -1;
					bullet_y = -1;
					return;
				}
			}
		}
	}
	return;
}

void displayscore() {

	drawText(16, 70, 85, 255, 255, 255, "SCORE");
	drawText(16, 200, 85, 255, 255, 255, "", true, score);


	return;
}
void updatescore() {

	if (alienkilled == true) {
		myRect(190, 70, 250, 120, 0, 0, 0);
		drawText(16, 200, 85, 255, 255, 255, "", true, score);

	}
	return;
}
void aliencollissionwithspaceship(int& i_x, int& i_y) {  
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (aliens[i][j] == true) {
				int x = alien_x - j * (alienwidth + alienspacing_x);
				int y = alien_y + i * (alienheight + alienspacing_y);


				if (i_x < x + alienwidth && i_x + 50 > x &&  
					i_y < y + alienheight && i_y + 30 > y) { // if coordinates of spaceship are more than that of aliens, collission occurs


					EraseSpaceship(i_x, i_y);


					i_x = 110;
					i_y = 300;
					drawSpaceship(i_x, i_y);  // draw spaceship again at original position

					alienspaceshipcollission = true;
					lives = lives - 1;

					if (lives <= 0) {
						gameover();

					}


				}
			}
		}
	}
	return;
}
void updatelives() {

	if (alienspaceshipcollission == true) {
		myRect(940, 70, 990, 120, 0, 0, 0);
		drawText(16, 950, 85, 255, 255, 255, "", true, lives);
	}
	return;
}


void aliensreachedleft() {
	bool alienExists = false;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (aliens[i][j] == true) {
				int x = alien_x + j * (alienwidth + alienspacing_x);
				int y = alien_y + i * (alienheight + alienspacing_y);

				if (x >= 50 && x <= 800 && y >= 50 && y <= 600) {    // to check if aliens reach left border
					alienExists = true;
					break;
				}
			}
		}
		if (alienExists) break;   // continue with the code if alien exists
	}

	if (!alienExists) {   // if not, call gameover
		gameover();
	}
	return;
}

void menuscreen() {

	myRect(200, 20, 800, 820, 0, 0, 255);
	myRect(205, 25, 795, 815, 0, 0, 255);
	myRect(210, 30, 790, 810, 0, 0, 255);
	return;
}

void gamename() {

	drawText(20, 325, 80, 255, 0, 0, "SPACE INVADERS GAME");
	drawText(20, 327, 80, 255, 0, 0, "SPACE INVADERS GAME");
	drawText(16, 365, 130, 255, 255, 255, "STRAWHATS EDITION");
	drawText(16, 367, 130, 255, 255, 255, "STRAWHATS EDITION");
	return;
}

void startgame() {

	myRect(350, 220, 650, 300, 255, 0, 0);
	drawText(16, 430, 245, 255, 255, 255, "START GAME");
	drawText(14, 230, 245, 255, 255, 255, "Press S");
	return;
}

void resumegame() {

	myRect(350, 310, 650, 390, 255, 0, 0);
	drawText(16, 425, 335, 255, 255, 255, "RESUME GAME");
	drawText(14, 230, 335, 255, 255, 255, "PRESS R");
	return;
}

void highscore() {

	myRect(350, 400, 650, 480, 255, 0, 0);
	drawText(16, 425, 425, 255, 255, 255, "HIGHSCORES");
	drawText(14, 230, 425, 255, 255, 255, "PRESS H");
	return;
}

void quitgame() {

	myRect(350, 490, 650, 570, 255, 0, 0);
	drawText(16, 430, 515, 255, 255, 255, "QUIT GAME");
	drawText(14, 230, 515, 255, 255, 255, "PRESS Q");
	return;
}

void quitonaction() {
	myRect(0, 0, 1000, 800, 0, 0, 0);

	exit(0);

}

int main() {
	int read, whichkey;
	int i_x = 110;   // initial x coordinate of spaceship 
	int i_y = 300;   // initial y coordinate of spaceship
	float bullet_x = -1;  // bullet is initially outside the rectangle
	float bullet_y = -1;

	menuscreen();
	gamename();
	startgame();
	resumegame();
	highscore();          // show menu
	quitgame();
	initial_aliens();
	while (true) {
		bool key = isKeyPressed(whichkey);


		if (whichkey == 9) {  // when S is pressed, game loop

			myRect(0, 0, 1000, 800, 0, 0, 0);


			myRect(50, 50, 1000, 600, 255, 0, 0);

			while (true) {

				create_aliens();
				displayscore();
				movealiens();
				aliensreachedleft();
				displaylives();
				aliencollissionwithspaceship(i_x, i_y);
				updatelives();

				if (bullet_x != -1 && bullet_y != -1) {   
					myRect(bullet_x, bullet_y, bullet_x + 10, bullet_y + 2, 0, 0, 0, 0, 0, 0);
					bullet_x = bullet_x + 30; // move bullet

					if (bullet_x + 10 >= 999) {
						bullet_x = -1;
					}
					else {
						myRect(bullet_x, bullet_y, bullet_x + 10, bullet_y + 2, 255, 255, 255, 255, 255, 255);
					}
				}
				killaliens(bullet_x, bullet_y);   
				updatescore();
				wingame();

				key = isKeyPressed(whichkey);
				if (key == true) {

					if (whichkey == 8) {  // spacebar to make scapeship appear
						drawSpaceship(i_x, i_y);
					}

					if (whichkey == 1) {   // left arrow to move left
						if (i_x - 6 > 55) {
							EraseSpaceship(i_x, i_y);
							i_x = i_x - 10;
							drawSpaceship(i_x, i_y);
						}
					}

					if (whichkey == 2) {   // move up Up key
						if (i_y - 6 > 60) {
							EraseSpaceship(i_x, i_y);
							i_y = i_y - 10;
							drawSpaceship(i_x, i_y);
						}
					}

					if (whichkey == 3) { // move right right key
						if (i_x + 50 < 990) {
							EraseSpaceship(i_x, i_y);
							i_x = i_x + 10;
							drawSpaceship(i_x, i_y);
						}
					}

					if (whichkey == 4) {   // move down Down key 
						if (i_y + 31 < 590) {
							EraseSpaceship(i_x, i_y);
							i_y = i_y + 10;
							drawSpaceship(i_x, i_y);
						}
					}

					if (whichkey == 5) {   // press enter to shoot bullets
						if (bullet_x == -1) {
							bullet_x = i_x + 12;
							bullet_y = i_y;
						}
					}

					if (whichkey == 7) {
						ispaused = true;
						pausegame();   // When escape pressed, pause menu appears
						while (ispaused) {
							key = isKeyPressed(whichkey);
							if (key && whichkey == 10) {  // if R pressed, resume game

								ispaused = false;
								myRect(0, 0, 1000, 800, 0, 0, 0);
								myRect(50, 50, 1000, 600, 255, 0, 0);
								drawSpaceship(i_x, i_y);
							}
							if (key && whichkey == 9) {  // if S pressed, save game

								savegame(i_x, i_y, lives, score, alien_x, alien_y, aliens);
								myRect(0, 0, 1000, 800, 0, 0, 0);
								exit(0);
							}
						}
					}
				}

				Sleep(16);
			}
		}
		if (whichkey == 12) {   // H key for highscore
			readfile(highscorearray);
			updatehighscore(highscorearray, score);
			writefile(highscorearray);
			displayhighscore(highscorearray);

		}
		if (whichkey == 10) {  // when R pressed for resume, load the game from the savegame.txt and read the data from textfile into game

			if (loadgame(i_x, i_y, lives, score, alien_x, alien_y, aliens) == true) {

				whichkey = 9;
				drawSpaceship(i_x, i_y);
			}
		}
		if (whichkey == 11) {  // Q for quitting the game
			quitonaction();
		}
	}

	cin >> read;
	return 0;
}







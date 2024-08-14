#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <thread>
#include <chrono>
#include <windows.h>
#include <math.h>

using namespace std;

//The map grid
vector <vector <int>> map;
int mapW = 50, mapH = 50;

//Main stack containing the cells visited.
stack <vector <int>> backtrack;

//Last cell visited.
vector <int> last_cell;

//The path found.
vector <vector <int>> path;

//Default search depth. Modify checkCells() for more options.
int depth=1;

//The current task above the printMap header.

/*
	@brief Prints text

	This function prints text, just a more conveinent cout << "".

	@param input: The text to print.
*/
void println(string input) {
	cout << input + "\n";
}

/*
	@brief Pauses for user input.

	This function waits until the user presses enter.
*/
void pause() {
	cin.get();
}

/*
	@brief Initializes the map grid

	This function initializes the map[[]] vector and fills it with walls.
*/
void initMap() {
	map.push_back({0});
	for(int i = 0; i < mapH; i++) {
		for(int j = 0; j < mapW; j++) {
			map[i].push_back(0);
		}
		map.push_back({0});
	}
}

/*
	@brief Clears the screen

	This function clears the screen without flickering, favorable over system("cls");
*/
void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

/*
	@brief Prints the grid map

	This function prints the contents of the map[[]] vector, color coded.
*/
void printMap() {
	string line="";
	string colors[5]={"\033[1;37m", "\033[1;34m", "\033[1;31m", "\033[0;30m", "\033[0;33m"};
	string screen="";
	string cc="";

	for(int i = 0; i < mapH; i++) {
		for(int j = 0; j < mapW; j++) {
			line += colors[map[i][j]] + u8"\u2588\u2588" + "\033[0m";
		}
		screen+=line + "\n";
		line="";
	}

	clearscreen();
	println(screen);

	screen="";

}

/*
	@brief Checks a specific direction for walls in the way

	This function checks a direction at a specific depth, used by checkDir().

	@param time: The number of milliseconds to pause
*/
bool checkCells(vector <int> anchor, char priority, int sign, int depth) {
	int x = anchor[0];
	int y = anchor[1];
	vector <int> dx={0,0,0};
	vector <int> dy={0,0,0};
	int dx2 = 1;
	int dy2 = 1;

	//Used to avoid duplicate nested if-statements
	if(priority=='x') {
		dx[0] = sign, dx[1] = sign, dx[2] = sign;
		dy[0] = -1, dy[1] = 0, dy[2] = 1;
		dx2 = depth, dy2 = 1;
	} else {
		dy[0] = sign, dy[1] = sign, dy[2] = sign;
		dx[0] = -1, dx[1] = 0, dx[2] = 1;
		dx2 = 1, dy2 = depth;
	}

	//Check 3 cells in the specified direction
	if(map[y+dy[0]][x+dx[0]]==0 && map[y+dy[1]][x+dx[1]]==0 && map[y+dy[2]][x+dx[2]]==0) {
		if(depth == 1) {
			return true;
		} else {
			//Uncommenting the code below will detect the next 3 cells across instead of just the next center cell.
			if(/*map[y+dy[0]*dy2][x+dx[0]*dx2]==0 && */map[y+dy[1]*dy2][x+dx[1]*dx2]==0 /*&& map[y+dy[2]*dy2][x+dx[2]*dx2]==0*/) {
				return true;
			}
		}
	}
	return false;
}

/*
	@brief Checks a specific direction for walls in the way

	This function checks a direction at a specific depth, used by checkDir().

	@param time: The number of milliseconds to pause
*/
bool checkDir(int dir, int depth) {
	int y = backtrack.top()[0];
	int x = backtrack.top()[1];
	switch(dir) {
		case 0:
			last_cell={y,x+1};
			if(x < mapW-3) {
				return checkCells({x,y}, 'x', 1, depth);
			}
			return false;
			break;
		case 1:
			last_cell={y-1,x};
			if(y > 2) {
				return checkCells({x,y}, 'y', -1, depth);
			}
			return false;
			break;
		case 2:
			last_cell={y,x-1};
			if(x > 2) {
				return checkCells({x,y}, 'x', -1, depth);
			} 
			break;
		case 3:
			last_cell={y+1,x};
			if(y < mapH-3) {
				return checkCells({x,y}, 'y', 1, depth);
			}
			break;
	}
	return false;
}

/*
	@brief Pauses for a specified time

	This function pauses the given thread for a certain amount of milliseconds.

	@param time: The number of milliseconds to pause
*/
void sleep(int time) {
	this_thread::sleep_for(std::chrono::milliseconds(time));
}

/*
	@brief Generates the map

	This function generates the map using stack backtracking.
*/
void fillMap() {
	vector <int> top; //The last top of the stack
	vector <int> dirs; //The available directions
	int dir; //Chosen direction

	
	backtrack.push({2,2}); //Starting location

	//Loop until the entire stack is empty
	while(backtrack.empty() == false) {

		top=backtrack.top(); //Define the current top to be referred to later.

		map[top[0]][top[1]]=2;
		printMap();
		sleep(1);

		dirs={0,1,2,3}; //Define possible directions

		//Search while there are available directions
		while(dirs.size() > 0) {

			//Pick direction
			dir = rand() % dirs.size();

			//Check the specified direction
			if(checkDir(dirs[dir], depth)) {
				map[top[0]][top[1]]=1;
				backtrack.push(last_cell);
				break;
			} else {
				//Erase the direction from the list of possible dirs if it isn't free
				dirs.erase(dirs.begin() + dir);
			}
		}

		//Remove the top of the stack if no more directions are possible.
		if(dirs.size() == 0) {
			map[top[0]][top[1]]=3;
			backtrack.pop();
		}
	}

	//Ensures bottom-right-most of map is pathable
	map[mapH-3][mapW-3]=3;
	map[mapH-4][mapW-3]=3;
	map[mapH-4][mapW-4]=3;
	map[mapH-3][mapW-4]=3;
}


/*
	@brief Checks cell visibility and can fill path between cells.

	This function determines whether two cells on the grid have sightline of eachother.
	It does this using DDA. To prevent needing two functions that both utuilize DDA,
	this function also doubles as the function used to fill the path between two cells
	when called by fillPath().

	@param prev: The first cell to check.
	@param next: The second cell to check.
	@param addToPath: Whether or not the function is being utilized as a path filler.
	@param pos: The position to fill in the path if addToPath is true.

	@return boolean of whether the given cells could see eachother.

*/
bool canSee(vector <int> prev, vector <int> next, bool addToPath=false, int pos=-1) {
	//Current coords
	double x = prev[1]+0.5;
	double y = prev[0]+0.5;

	//Previous coords
	double px=x;
	double py=y;

	//The starting coords
	double startx=x;
	double starty=y;

	//Target coords
	double tx = next[1]+0.5;
	double ty = next[0]+0.5;

	//The cells that have been traversed, used for path filling.
	vector <vector <int>> traversed;

	//The difference between the start and target
	double dx=0;
	double dy=0;

	//Used to hold DDA calculations
	double fracx=0;
	double fracy=0;

	//Used for checking corner-skips.
	vector <int> cc_xy = {0, 0};

	//Loop until the x and y encounter a wall.
	while(map[int(y)][int(x)] != 0) {

		//Check whether the target has been reached.
		if(int(x) == int(tx) && int(y) == int(ty)) {

			//Check if the current function is being used for path-filling.
			if(addToPath == true && traversed.size() > 0) {

				//Iterate through traversed cells and add to path.
				for(int i = 0; i < traversed.size(); i++) {
					path.insert(path.begin()+pos+i, traversed[i]);
				}
			}

			return true;
		}

		//Add the current cell to the traversed cell vector.
		if((x != startx || y != starty) && addToPath == true) {
			traversed.push_back({int(y), int(x)});
		}

		//Set the difference between the start and target.
		dx=tx-x;
		dy=ty-y;

		//Set the distance to the left and top walls.
		fracx=x-floor(x);
		fracy=y-floor(y);

		//Check whether the right or bottom walls are closer.
		if(dx > 0) {
			fracx=1-fracx;
		}
		if(dy > 0) {
			fracy=1-fracy;
		}

		//Get the ratio between the wall distance and target distance (0.001 si added to prevent divison by 0 errors)
		fracx=abs(fracx/dx)+0.001;
		fracy=abs(fracy/dy)+0.001;

		//Determine which wall is closer and move x & y accordingly.
		if(fracx <= fracy) {
			x += fracx*dx;
			y += fracx*dy;
		} else {
			y += fracy*dy;
			x += fracy*dx;
		}

		//Checks that the DDA didn't squeeze through a corner.
		if(int(px) != int(x) && int(py) != int(y) && addToPath == false) {
			cc_xy[0] = 0, cc_xy[1] = 0;
			if(dy > 0) {
				cc_xy[1] = -1;
			} else {
				cc_xy[1] = 1;
			}
			if(dx > 0) {
				cc_xy[0] = -1;
			} else {
				cc_xy[0] = 1;
			}
			if(map[int(y)+cc_xy[1]][int(x)] == 0 && map[int(y)][int(x)+cc_xy[0]] == 0) {
				break;
			}
		}

		//Set the current x & y to be used later as the previous x & y.
		px=x;
		py=y;

	}
	return false;
	
}

/*
	@brief Visualizes the walk of the main path.

	This function iterates through the walk vector and visualizes it.
*/
void walkPath() {

	//Used so the path doesn't happen too fast/slow.
	int delay = floor(5000/path.size());

	//Helps speed up long walks.
	if(path.size() > 1000) {
		delay=0;
	}

	//Reset the color of all non-walls.
	for(int i = 0; i < mapH; i++) {
		for(int j = 0; j < mapW; j++) {
			if(map[i][j] != 3 && map[i][j] != 0) {
				map[i][j] = 3;
			}
		}
	}

	system("cls"); // Fully clear sceen prior to walk.
	printMap();

	//Iterate through path and visualize each cell.
	for(int i = 0; i < path.size(); i++) {
		map[path[i][0]][path[i][1]]=2;
		printMap();
		println("Number of steps: " + to_string(i) + "/" + to_string(path.size()-1));
		sleep(delay);
		map[path[i][0]][path[i][1]]=4;
	}
}

/*
	@brief Optimizing the initially found path.

	This function iterates through each cell in the path. For each cell, it iterates
	backwards from the very end the path and checks whether the initial cell and any
	of the cells after can see eachother. If they can, then any cells between them
	are erased from the path list and the search restarts until no optimizations can
	be made.
*/
void optimizePath() {

	//Loop until the break is reached.
	while(true) {

		optimizePathRestart: ; //Used if the entire search needs to restart.

		//Iterate forward from the start of the path.
		for(int i = 0; i < path.size(); i++) {

			//Iterate backwards from the end of the path.
			for(int j = 1; j < path.size(); j++) {

				//Makes sure it doesn't check past the forward-moving-cell.
				if(path.size() - j <= i+1) {
					break;
				}

				//Checks whether the cells can see eachother.
				if(canSee(path[i], path[path.size() - j])) {
					//Erase the cells between 2 cells that see eachother
					path.erase(path.begin()+i+1, path.begin()+(path.size() - j));
					goto optimizePathRestart;
				}
			}
		}

		break; //Reached when no optimizations are found.

	}
}

/*
	@brief Fills the path between two cells.

	This function fills the path between two cells are they are not right next to
	eachother. This is, for the most part, done alondside the canSee function
	using its addToPath flag.
*/
void fillPath() {

	//The change in x and y between two cells.
	vector <int> dxy = {0,0};

	//Used for vector comparison to ensure cells are non-adjacent.
	vector <vector <int>> states={{0,1}, {1,0}, {1,1}};

	//Loops until break after path has been fully iterated with no changes
	while(true) {

		fillPathRestart: ; //Used to restart search since path.size() changes regularly.

		//Iterate through the path
		for(int i = 0; i < path.size()-1; i++) {

			//Define the x/y slope
			dxy[0]=abs(path[i+1][0]-path[i][0]);
			dxy[1]=abs(path[i+1][1]-path[i][1]);

			//Checks that the next cell isn't immediately adjacent
			if(dxy != states[0] && dxy != states[1] && dxy != states[2]) {

				//Uses CanSee for its path filling DDA purposes.
				if(canSee(path[i], path[i+1], true, i+1)) {

					//Break if the end of the path has been reached.
					if(i == path.size()-2) {
						break;
					}
					
					//Restart path filling since path.size() changed.
					goto fillPathRestart;
				}
			}
		}

		break; //Reached only if all cells have been filled.
	}

	return;
}

/*
	@brief Finds a path using random movement.

	This function fills the path between two cells are they are not right next to
	eachother. This is, for the most part, done alondside the canSee function
	using its addToPath flag.
*/
void findPath() {

	vector <int> node = {2 + (rand() % (mapH-3)), 2 + (rand() % (mapW-3))}; //The node to be checked
	path.push_back({2,2}); //The starting point
	map[mapH-3][mapW-3]=3; //Sets starting point's color
	vector <int> goal={mapH-3, mapW-3}; //The goal
	int orig_state=0; //Holds the original color of cells

	//Loops until the goal is reached
	while(path[path.size()-1] != goal) {

		node = {2 + (rand() % (mapH-3)), 2 + (rand() % (mapW-3))}; //Sets what node is to checked

		map[path[path.size()-1][0]][path[path.size()-1][1]]=4; //Changes the color of the previous node.

		//Checks that the node isn't a wall or the same as the previous node
		if(map[node[0]][node[1]] != 0 && node != path[path.size()-1]) {
			orig_state = map[node[0]][node[1]]; //Remember the color of the current node
			map[node[0]][node[1]]=1; //Update the color of the current node

			//If the goal is in sight, then exit search.
			if(canSee(path[path.size()-1], goal, false)) {
				break;
			}

			//If the node is in sight, add it to the path, otherwise revert its color.
			if(canSee(path[path.size()-1], node)) {
				path.push_back(node);
				map[node[0]][node[1]]=2;
			} else {
				map[node[0]][node[1]]=orig_state;
			}
		}
	}

	//Add goal to the very end of path.
	path.push_back(goal);

	
}

/*
	Main function

*/
int main(int argc, char *argv[]) {
	srand(time(NULL));
	system("chcp 65001 && cls");
	initMap();
	fillMap();
	findPath();
	//walkPath();
	fillPath();
	optimizePath();
	walkPath();
	optimizePath();
	fillPath();
	walkPath();
	pause();
	return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <thread>
#include <chrono>
#include <windows.h>
#include <math.h>

using namespace std;


vector <vector <int>> map;
int mapW = 30, mapH = 30;

stack <vector <int>> backtrack;

vector <int> last_cell;

bool pMap = false;

vector <vector <int>> path;

string currentTask="";



void println(string input) {
	cout << input + "\n";
}

//Debug print function. Can be easily commented out to hide debug messages.
void dprintln(string input) {
	//println(input);
}

void pause() {
	cin.get();
}

void initMap() {
	map.push_back({0});
	for(int i = 0; i < mapH; i++) {
		for(int j = 0; j < mapW; j++) {
			map[i].push_back(0);
		}
		map.push_back({0});
	}
}

void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void printMap() {
	string line="";
	string states[5]={u8"\u2588\u2588", ".", u8"\u2588", " ", "a"};
	string screen="";
	string cc="";

	for(int i = 0; i < mapH; i++) {
		for(int j = 0; j < mapW; j++) {
			switch(map[i][j]) {
				case 0:
					cc = "\033[1;37m";
					break;
				case 1:
					cc = "\033[1;34m";
					break;
				case 2:
					cc = "\033[1;31m";
					break;
				case 3:
					cc = "\033[0;30m";
					break;
				case 4:
					cc = "\033[0;33m";
					break;
			}
			line += cc + u8"\u2588\u2588" + "\033[0m";

		}
		screen+=line + "\n";
		line="";
	}

	clearscreen();
	println(currentTask+"\n");
	println(screen);

	screen="";

}

bool checkCells(vector <int> anchor, char priority, int sign, int depth) {
	int x = anchor[0];
	int y = anchor[1];
	vector <int> dx={0,0,0};
	vector <int> dy={0,0,0};
	int dx2 = 1;
	int dy2 = 1;

	if(priority=='x') {
		dx[0] = sign, dx[1] = sign, dx[2] = sign;
		dy[0] = -1, dy[1] = 0, dy[2] = 1;
		dx2 = depth, dy2 = 1;
	} else {
		dy[0] = sign, dy[1] = sign, dy[2] = sign;
		dx[0] = -1, dx[1] = 0, dx[2] = 1;
		dx2 = 1, dy2 = depth;
	}

	if(map[y+dy[0]][x+dx[0]]==0 && map[y+dy[1]][x+dx[1]]==0 && map[y+dy[2]][x+dx[2]]==0) {
		if(depth == 1) {
			return true;
		} else {
			//Uncommenting the code below will detect 3 cells across instead of just the next center cell.
			if(/*map[y+dy[0]*dy2][x+dx[0]*dx2]==0 && */map[y+dy[1]*dy2][x+dx[1]*dx2]==0 /*&& map[y+dy[2]*dy2][x+dx[2]*dx2]==0*/) {
				return true;
			}
		}
	}
	return false;
}

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

void sleep(int time) {
	this_thread::sleep_for(std::chrono::milliseconds(time));
}

void fillMap(int start=0) {
	vector <int> top;
	vector <int> dirs;
	int dir;
	string dirss="";
	switch(start) {
		case 1:
			backtrack.push({2,2});
		case 0:
			while(backtrack.empty() == false) {
				top=backtrack.top();
				map[top[0]][top[1]]=2;
				printMap();
				sleep(10);
				dirs={0,1,2,3};
				while(dirs.size() > 0) {
					dir = rand() % dirs.size();
					dirss="{";
					for(int i = 0; i < dirs.size(); i++) {
						dirss += to_string(dirs[i]);
						if(i != dirs.size()) {
							dirss+=", ";
						}
					}
					dirss+="}";
					if(checkDir(dirs[dir], 1)) {
						map[top[0]][top[1]]=1;
						backtrack.push(last_cell);
						break;
					} else {
						dirs.erase(dirs.begin() + dir);
					}
				}
				if(dirs.size() == 0) {
					map[top[0]][top[1]]=3;
					backtrack.pop();
				}
			}
			break;
	}

	map[mapH-3][mapW-3]=3;
	map[mapH-4][mapW-3]=3;
	map[mapH-4][mapW-4]=3;
	map[mapH-3][mapW-4]=3;
}



string printCoords(vector <vector <int>> input) {
	string output="{";
	for(int i = 0; i < input.size(); i++) {
		output+="{";
		for(int j = 0; j < input[i].size(); j++) {
			output += to_string(input[i][j]);
			output+=", ";

		}
		output += "}";
		if(i < input.size()-1) {
			output+=", ";
		}
	}
	return output+"}";
}




bool canSee(vector <int> prev, vector <int> next, bool addToPath=true, int pos=-1) {
	//Current coords
	double x = prev[1]+0.5;
	double y = prev[0]+0.5;

	double px=x;
	double py=y;

	double startx=x;
	double starty=y;

	//Target coords
	double tx = next[1]+0.5;
	double ty = next[0]+0.5;

	vector <vector <int>> traversed;

	double dx=0;
	double dy=0;

	double fracx=0;
	double fracy=0;

	vector <int> cc_xy = {0, 0};

	while(map[int(y)][int(x)] != 0) {

		dx=tx-x;
		dy=ty-y;

		

		if(int(x) == int(tx) && int(y) == int(ty)) {
			//println(to_string(tx) + ", " + to_string(ty) + " - " + to_string(startx) + ", " + to_string(starty));
			//println("COORDS TRAVERSED BELOW");
			//println(printCoords(traversed));
			//pause();
			if(addToPath == true && traversed.size() > 0) {
				for(int i = 0; i < traversed.size(); i++) {
					if(pos == -1) {
						path.push_back(traversed[i]);
					} else {
						path.insert(path.begin()+pos+i, traversed[i]);
					}
				}
			}
			return true;
			break;
		}

		if((x != startx || y != starty)) {
			traversed.push_back({int(y), int(x)});
			//map[floor(y)][floor(x)]=4;
		}

		
		

		fracx=x-floor(x);
		fracy=y-floor(y);

		
		if(dx > 0) {
			fracx=1-fracx;
		}
		if(dy > 0) {
			fracy=1-fracy;
		}

		fracx=abs(fracx/dx)+0.001;
		fracy=abs(fracy/dy)+0.001;

		
		

		//printMap();
		//println("at " + to_string(x) + ", " + to_string(y));
		//println("target " + to_string(tx) + ", " + to_string(ty));
		//println("dx " + to_string(dx) + " dy " + to_string(dy));
		//println("fracx " + to_string(fracx) + " fracy " + to_string(fracy));

		if(fracx <= fracy) {
			x += fracx*dx;
			y += fracx*dy;
		} else {
			y += fracy*dy;
			x += fracy*dx;
		}
		//println("at " + to_string(x) + ", " + to_string(y) + " after frac");
		
		//Makes sure corners are not passed through.
		if(int(px) != int(x) && int(py) != int(y)) {
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
		px=x;
		py=y;

	}
	return false;
	
}



string printVec(vector <int> input) {
	string output="{";
	for(int i = 0; i < input.size(); i++) {
		output += to_string(input[i]);
		if(i < input.size()-1) {
			output+=", ";
		}
	}
	return output+"}";
}

void walkPath() {
	int delay = floor(5000/path.size());

	for(int i = 0; i < mapH; i++) {
		for(int j = 0; j < mapW; j++) {
			if(map[i][j] != 3 && map[i][j] != 0) {
				map[i][j] = 3;
			}
		}
	}
	system("cls");
	printMap();
	for(int i = 0; i < path.size(); i++) {
		map[path[i][0]][path[i][1]]=2;
		printMap();
		println("Number of steps: " + to_string(i+1) + "/" + to_string(path.size()));
		sleep(delay);
		map[path[i][0]][path[i][1]]=4;
	}
}


void optimizePath() {
	bool complete=false;
	vector <int> dxy = {0,0};
	vector <vector <int>> states={{0,1}, {1,0}, {1,1}};
	while(complete == false) {
		for(int i = 0; i < path.size()-2; i++) {
			if(i == path.size()-3) {
				complete = true;
				break;
			}
			if(canSee(path[i], path[i+2], false)) {
				path.erase(path.begin()+i+1);
				break;
			}
		}
	}
	complete=false;
	while(complete == false) {
		for(int i = 0; i < path.size()-1; i++) {
			dxy[0]=abs(path[i+1][0]-path[i][0]);
			dxy[1]=abs(path[i+1][1]-path[i][1]);
			if(i == path.size()-2) {
				complete = true;
				break;
			}
			if(dxy != states[0] && dxy != states[1] && dxy != states[2]) {
				if(canSee(path[i], path[i+1], true, i+1)) {
					break;
				}
			}
		}
	}
}

void setTask(string input) {
	currentTask=input;
}

void findPath() {
	vector <int> node = {2 + (rand() % (mapH-3)), 2 + (rand() % (mapW-3))};
	path.push_back({2,2});
	map[mapH-3][mapW-3]=3;
	vector <int> goal={mapH-3, mapW-3};
	int orig_state=0;
	while(path[path.size()-1] != goal) {

		node = {2 + (rand() % (mapH-3)), 2 + (rand() % (mapW-3))};

		map[path[path.size()-1][0]][path[path.size()-1][1]]=4;
		if(map[node[0]][node[1]] != 0 && node != path[path.size()-1]) {
			orig_state = map[node[0]][node[1]];
			map[node[0]][node[1]]=1;
			if(canSee(path[path.size()-1], goal, false)) {
				break;
			}
			if(canSee(path[path.size()-1], node, false)) {
				path.push_back(node);
				map[node[0]][node[1]]=2;
			} else {
				map[node[0]][node[1]]=orig_state;
			}
		}
	}
	path.push_back(goal);
	path.push_back(goal);

	
}


int main(int argc, char *argv[]) {
	srand(time(NULL));
	system("chcp 65001 && cls");
	setTask("Initializing map");
	initMap();
	setTask("Filling map");
	fillMap(1);
	setTask("Starting CraPath");
	findPath();
	setTask("Traversing first path");
	walkPath();
	setTask("Optimizing path 1/2");
	optimizePath();
	setTask("Optimizing path 2/2");
	optimizePath();
	setTask("Optimizing path 2/2");
	optimizePath();
	setTask("Optimizing path 2/2");
	optimizePath();
	setTask("Optimizing path 2/2");
	optimizePath();
	setTask("Optimizing path 2/2");
	optimizePath();
	setTask("Walking final path");
	walkPath();
	pause();
	return 0;
}
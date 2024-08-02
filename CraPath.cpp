#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <thread>
#include <chrono>

using namespace std;


vector <vector <int>> map;
int mapW = 50, mapH = 50;

stack <vector <int>> backtrack;

vector <int> last_cell;

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

void printMap() {
	string line="";
	string states[4]={u8"\u2588", ".", "!", " "};
	string screen="";

	while(true) {
		system("cls");
		for(int i = 0; i < mapH; i++) {
			for(int j = 0; j < mapW; j++) {
				line += states[map[i][j]]+states[map[i][j]];
			}
			screen+=line + "\n";
			line="";
		}
		println(screen);
		screen="";
	}
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
		dx2 = 2, dy2 = 1;
	} else {
		dy[0] = sign, dy[1] = sign, dy[2] = sign;
		dx[0] = -1, dx[1] = 0, dx[2] = 1;
		dx2 = 1, dy2 = 2;
	}

	if(map[y+dy[0]][x+dx[0]]==0 && map[y+dy[1]][x+dx[1]]==0 && map[y+dy[2]][x+dx[2]]==0) {
		if(depth == 1) {
			return true;
		} else {
			if(map[y+dy[0]*dy2][x+dx[0]*dx2]==0 && map[y+dy[1]*dy2][x+dx[1]*dx2]==0 && map[y+dy[2]*dy2][x+dx[2]*dx2]==0) {
				return true;
			}
		}
	}
	return false;
}

bool checkDir(int dir) {
	int y = backtrack.top()[0];
	int x = backtrack.top()[1];
	switch(dir) {
		case 0:
			last_cell={y,x+1};
			if(x < mapW-3) {
				return checkCells({x,y}, 'x', 1, 2);
			}
			return false;
			break;
		case 1:
			last_cell={y-1,x};
			if(y > 2) {
				return checkCells({x,y}, 'y', -1, 2);
			}
			return false;
			break;
		case 2:
			last_cell={y,x-1};
			if(x > 2) {
				return checkCells({x,y}, 'x', -1, 2);
			} 
			break;
		case 3:
			last_cell={y+1,x};
			if(y < mapH-3) {
				return checkCells({x,y}, 'y', 1, 2);
			}
			break;
	}
	return false;
}

void fillMap(int start=0) {
	vector <int> top;
	vector <int> dirs;
	int dir;
	string dirss="";
	switch(start) {
		case 1:
			backtrack.push({3,3});
		case 0:
			while(backtrack.empty() == false) {
				top=backtrack.top();
				map[top[0]][top[1]]=2;
				//printMap();
				this_thread::sleep_for(std::chrono::milliseconds(10));
				dprintln("At:" + to_string(top[0]) + ", " + to_string(top[1]));
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
					dprintln("Try: {" + to_string(dirs[dir]) + "} out of: " + dirss);
					//pause();
					if(checkDir(dirs[dir])) {
						dprintln("{" + to_string(dirs[dir]) + "} dir free, pushing {" + to_string(last_cell[0]) + ", " + to_string(last_cell[1]) + "}");
						map[top[0]][top[1]]=1;
						backtrack.push(last_cell);
						break;
					} else {
						dprintln("{" + to_string(dirs[dir]) + "} dir filled, erasing from " + dirss);
						dirs.erase(dirs.begin() + dir);
					}
				}
				if(dirs.size() == 0) {
					dprintln("dirs list empty, popping {" + to_string(top[0]) + ", " + to_string(top[1]) + "}");
					map[top[0]][top[1]]=3;
					backtrack.pop();
				} else {
					dprintln("Moving onto new cell.");
				}
			}
			break;
	}
}



int main(int argc, char *argv[]) {
	srand(time(NULL));
	system("chcp 65001 && cls");
	thread mapLoop(printMap);
	initMap();
	fillMap(1);
	mapLoop.join();
	pause();
	return 0;
}
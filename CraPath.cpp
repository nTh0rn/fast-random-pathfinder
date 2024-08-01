#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;


vector <vector <int>> map;
int mapW = 15, mapH = 15;

stack <vector <int>> backtrack;

vector <int> last_cell;

void println(string input) {
	cout << input + "\n";
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
	string states[3]={u8"\u2588", " ", "!"};
	for(int i = 0; i < mapH; i++) {
		for(int j = 0; j < mapW; j++) {
			line += states[map[i][j]]+states[map[i][j]];
		}
		println(line);
		line="";
	}
}

bool checkDir(int dir) {
	int y = backtrack.top()[0];
	int x = backtrack.top()[1];
	switch(dir) {
		case 0:
			if(x < mapW-1) {
				if(map[y][x+1]==0 && map[y+1][x+1]==0 && map[y-1][x+1]==0) {
					last_cell={y,x+1};
					return true;
				} else {
					println("Right is blocked");
				}
			}
			return false;
			break;
		case 1:
			if(y > 1) {
				if(map[y-1][x]==0 && map[y-1][x-1]==0 && map[y-1][x+1]==0) {
					last_cell={y-1,x};
					return true;
				} else {
					println("Up is blocked");
				}
			}
			return false;
			break;
		case 2:
			if(x > 1) {
				if(map[y][x-1]==0 && map[y+1][x-1]==0 && map[y-1][x-1]==0) {
					last_cell={y,x-1};
					return true;
				} else {
					println("Left is blocked");
				}
			}
			return false;
			break;
		case 3:
			if(y < mapH-1) {
				println(to_string(x) + " " + to_string(y));
				println(" " + to_string(map[y][x]) + " ");
				println(to_string(map[y+1][x-1]) + to_string(map[y+1][x]) + to_string(map[y+1][x+1]));
				if(map[y+1][x]==0 && map[y+1][x-1]==0 && map[y+1][x+1]==0) {
					last_cell={y+1,x};
					return true;
				} else {
					println("Down is blocked");
				}
			}
			return false;
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
				map[top[0]][top[1]]=1;
				dirs={0,1,2,3};
				println("Yup!");
				while(dirs.size() > 0) {
					dir = rand() % dirs.size();
					println(to_string(top[0]) + " " + to_string(top[1]));
					dirss="";
					for(int i = 0; i < dirs.size(); i++) {
						dirss += to_string(dirs[i]) + ", ";
					}
					println(dirss);
					println(to_string(backtrack.size()));
					printMap();
					pause();
					if(checkDir(dir)) {
						backtrack.push(last_cell);
						break;
					} else {
						dirs.erase(dirs.begin() + dir);
					}
				}
				if(dirs.size() == 0) {
					map[top[0]][top[1]]=2;
					backtrack.pop();
				}
				//pause();
			}
			break;
	}
}



int main(int argc, char *argv[]) {
	system("chcp 65001 && cls");
	initMap();
	fillMap(1);
	printMap();
	pause();
	return 0;
}
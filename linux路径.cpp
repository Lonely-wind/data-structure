#include<iostream>
#include<string>
using namespace std;
bool IsDot(char a, char b) {
	if (a == '.' && b == '.') {
		return true;
	}
	else {
		return false;
	}
}
bool IsSlash(char a, char b) {
	if (a == '/' && b == '/') {
		return true;
	}
	else {
		return false;
	}
}
bool IsSDot(char a, char b, char c) {
	if (a == '/' && b == '.' && c == '/') {
		return true;
	}
	else {
		return false;
	}
}
int main() {
	string input;
	cin >> input;
	char* stack = new char[input.length()];
	int stacktop = -1;
	//cout << input.length() << endl;
	int judgeInsert = 0;
	//处理字符串
		for (int i = 0; i < input.length(); i++) {
			if (stacktop == -1) {
				stack[++stacktop] = input[i];
				stack[stacktop + 1] = '\0';
			}
			else {
				if (IsDot(stack[stacktop], input[i])) {
					if (judgeInsert == 1) {
						stack[stacktop] = '\0';
						stacktop--;
						continue;
					}
					int count = 0;
					int judge = 1;
					while (judge) {
						if (stack[stacktop] == '/') {
							count++;
							if (stacktop == 0) {
								judgeInsert = 1;
							}
							else {
								stack[stacktop] = '\0';
								stacktop--;
								judgeInsert = 0;
							}
							if (count == 2) {
								judge = 0;
							}
						}
						else {
							stack[stacktop] = '\0';
							stacktop--;
						}
					}
				}
				else if (IsSlash(stack[stacktop], input[i])) {
					if (judgeInsert == 1) {
						judgeInsert = 0;
						continue;
					}
					else {
						if (input[i + 1] != '/') {
							continue;
						}
						else {
							stack[stacktop] = '\0';
							stacktop--;
						}
					}
				}
				else if (IsSDot(stack[stacktop], input[i], input[i + 1]) && stacktop != 0) {
					stack[stacktop] = '\0';
					stacktop--;
				}
				else if (IsSDot(stack[stacktop], input[i], input[i + 1]) && stacktop == 0) {
					stacktop--;
					//cout << stacktop << endl;
					continue;
				}
				else {
					stack[++stacktop] = input[i];
					stack[stacktop + 1] = '\0';
				}
			}
		}
		if (stack[stacktop] == '/' && stacktop != 0) {
			stack[stacktop] = '\0';
			stacktop--;
			cout << stack;
		}
		else if (stack[stacktop] == '.' && stack[stacktop - 1] == '/') {
			for (int i = 0; i < 2; i++) {
				stack[stacktop] = '\0';
				stacktop--;
			}
			cout << stack;
		}
		else {
			cout << stack;
		}
}
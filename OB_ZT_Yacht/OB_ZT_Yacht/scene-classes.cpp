#include "scene-classes.h"

void StartSceneDraw::Init() {
	system("mode con cols=110 lines=35 | title Yatch Dice with Special Items");
}

void StartSceneDraw::TitleDraw() { // title은 startscene에만 등장
	
	cout << "\n\n";
	gotoxy(25, 2);
	cout << " __   __        _          _      ______  _    \n";
	gotoxy(26, 3);
	cout << "\\ \\ / /       | |        | |     |  _  \\(_)            \n";
	gotoxy(26, 4);
	cout << " \\ V /   __ _ | |_   ___ | |__   | | | | _   ___   ___ \n";
	gotoxy(26, 5);
	cout << "  \\ /   / _` || __| / __|| '_ \\  | | | || | / __| / _ \\\n";
	gotoxy(26, 6);
	cout << "  | |  | (_| || |_ | (__ | | | | | |/ / | || (__ |  __/\n";
	gotoxy(26, 7);
	cout << "  \\_/   \\__,_| \\__| \\___||_| |_| |___/  |_| \\___| \\___|\n";
	gotoxy(0, 11);
	for (int i = 0; i < 110; i++)cout<<"■";
	gotoxy(42, 15); 
	cout << "Let's play this game!"; // 0
	gotoxy(42, 16);
	cout << "How to play this game?"; // 1
	gotoxy(42, 17);
	cout << "Exit"; // 2

	/* team 정보 표시 */
	gotoxy(38, 25);
	cout << "< Object Oriented Programming >";
	gotoxy(48, 26);
	cout << "Team 4";

}

void StartSceneInputManager::KeyMovingControl() {
	int x = 42;
	int y = 15;
	bool stop = false;
	gotoxy(x - 2, y);
	while (1) { // 무한 반복
		int n = KeyControl(); // 키보드 입력을 키값으로 받아오기
		if (stop == true) break;
		switch (n) {
		case UP: {
			if (y > 15) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, --y);
				cout << ">";
			}
			break;
		}
		case DOWN: {
			if (y < 17) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y); //
				cout << ">";
			}
			break;
		}
		case ENTER: {
			if (y - 15 == 0) { // gamestart
				GameSceneDraw gamescene;
				stop = true;
				
				break;
			}
			else if (y - 15 == 1) { // InfoScene으로 전환
				InfoSceneDraw infoscene;
			}

			else if (y - 15 == 2) { // exit
				gotoxy(0, 27);
				cout << "\n\n--------------------------------------------------------------------------------------";
				exit(1);
			}

		}	    
		}
	}
}



void Draw::gotoxy(int x, int y) { // 키보드 입력으로 움직임
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int SceneInputManager::KeyControl() {

	char temp = _getch();

	if (temp == 'w' || temp == 'W' || temp == 72) { return UP; }
	else if (temp == 'a' || temp == 'A'|| temp == 75) { return LEFT; }
	else if (temp == 's' || temp == 'S' || temp == 80) { return DOWN; }
	else if (temp == 'd' || temp == 'D' || temp == 77) { return RIGHT; }
	else if (temp == 13) { return ENTER; }
}

void Draw::EraseScene() {
	system("cls");
}

InfoSceneDraw::InfoSceneDraw() { // 게임 정보 화면
	EraseScene();
	cout << "게임 정보 설명\n";
	cout << "엔터키를 누르면 startscene으로 돌아갑니다.";
	InfoSceneInputManager infosceneinputmanager;
	infosceneinputmanager.KeyMovingControl();

}

void EndSceneInputManager::KeyMovingControl() {
	int x = 42;
	int y = 15;
	gotoxy(x - 2, y);
	while (1) { // 무한 반복
		int n = KeyControl(); // 키보드 입력을 키값으로 받아오기
		switch (n) {
		case UP: {
			if (y > 15) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, --y);
				cout << ">";
			}
			break;
		}
		case DOWN: {
			if (y < 17) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << ">";
			}
			break;
		}
		case ENTER: {
			if (y - 15 == 0) { // gamestart
				GameSceneDraw game_scene_draw;
			}
			else if (y - 15 == 1) { // InfoScene으로 전환
				InfoSceneDraw infoscene;
			}

			else if (y - 15 == 2) { // exit
				gotoxy(0, 27);
				cout << "\n\n--------------------------------------------------------------------------------------";
				exit(1);
			}

		}
		}
	}
}

void InfoSceneInputManager::KeyMovingControl() {
	while (1) {
		if (KeyControl() == ENTER) {
			EraseScene();
			StartSceneDraw startscene;
			startscene.TitleDraw();
			gotoxy(40, 15);
			break;
		}
	}
}

void GameSceneInputManager::KeyMovingControl() { // 얘는 좀 구현이 빡세보임
	int x = 52;
	int y = 15;
	gotoxy(52, 15); // 무조건 첫번째 주사위 커서로 이동
	gotoxy(x, y - 3);
	cout << "V";
	while (1) {
		int n = KeyControl();
		switch (n) {
			
		case RIGHT: {
			if (x < 100 && x > 40) { // 가장 오른쪽 주사위는 넘어가지 않음, 주사위에서의 right
				gotoxy(x, y - 3);
				cout << " ";
				gotoxy(x + 12, y - 3);
				cout << "V";
				gotoxy(x + 12, y);
				x = x + 12;
			}
			else if (x < 40) { // 표에서의 right, 해당 cell의 커서 삭제
				COORD pos;
				pos = getxy();
				gotoxy(pos.X - 1, pos.Y);

				cout << " ";
				x = 52;
				y = 15;
				gotoxy(52, 15); // 무조건 첫번째 주사위 커서로 이동
				gotoxy(x, y - 3);
				cout << "V";
				gotoxy(x , y);
			}
			break;
		}
		case LEFT: {
			if (x > 52) { // 주사위에서 left
				gotoxy(x, y - 3);
				cout << " ";
				gotoxy(x - 12, y - 3);
				cout << "V";
				gotoxy(x - 12, y); 
				x = x - 12;
			}
			else if (x == 52) { // table로 들어가기
				int turn = 1; // 임시
				gotoxy(x, y - 3);
				cout << " ";
				// 1p는 22, 2p는 34
				y = 5; // 여기서 표로 입장, *** turn을 확인하고 입장해야함 좌표 수정	

				if (turn == 1) x = 22;
				else if (turn == 2) x = 34;
				gotoxy(x, 5); 
				cout << "V";
			}
			break;
		}
		case SPACE: {			
			if (x < 101 && x > 51) { // 주사위에서 스페이스, keep
				
				DiceKeepDraw();
			}
			break;
		}
		case UP: { // 표에서 위로가는 방향키 눌렀을 때
			if (y > 5 && x < 50) { // 위로 더는 못가게, 주사위에서는 위로 안감
				gotoxy(x, y);
				cout << " ";
				gotoxy(x, y - 2);
				cout << "V";
				y = y - 2;
			}
			break;
		}

		case DOWN: { // 표에서 아래로 가는 방향키 눌렀을 떄
			if (y < 31 && x < 50) { // 주사위에서는 아래로 안감
				gotoxy(x, y);
				cout << " ";
				gotoxy(x, y + 2);
				cout << "V";
				y = y + 2;
			}
			break;		
		}

		case ENTER: { // 표에서 엔터, 점수박기
			int turn = 1; // 임시
			GameSceneInputManager gamescene;
			gamescene.TableFixedDraw(); // 여기 1의 자리에 그냥 없어도 될 듯? 
			// 엔터 누르면 TableFixedDraw 내에서 해당 커서 위치 확인해서 거기에 / 그림 / .변수 어쩌고 바꾸기
			if (turn == 1) turn = 2;
			else if (turn == 2) turn = 1;
		}		
		}
	}
}

COORD Draw::getxy() {
	CONSOLE_SCREEN_BUFFER_INFO cursor;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	return cursor.dwCursorPosition;
}

void GameSceneInputManager::RollTurnRoundDraw(int round, int turn, int roll) { //  센터가 76, 8
	gotoxy(64, 8);
	cout << "Round" << round;
	gotoxy(76, 8);
	cout << "Turn" << turn;
	gotoxy(88, 8);
	cout << "Roll" << roll;
}
int GameSceneInputManager::DiceActivateDraw() { // n번째 주사위

	COORD pos;
	pos = getxy();
	switch (pos.X) {
	case 52: { cout << "    ";  return FIRST; }// gotoxy(52 - 1, 18);  break; }// 1주사위 
	case 64: { cout << "    ";  return SECOND; } // gotoxy(64 - 1, 18); break;}
	case 76: { cout << "    ";  return THIRD; } //  gotoxy(76 - 1, 18); break;}
	case 88: { cout << "    ";  return FOURTH; } // gotoxy(88 - 1, 18); break;}
	case 100: { cout << "    "; return FIFTH; } // gotoxy(100 - 1, 18); break;}
	}
}

int GameSceneInputManager::DiceKeepDraw() { // n번째 주사위

	COORD pos;
	pos = getxy();
	switch (pos.X) {
	case 52: { cout << "KEEP";  return FIRST; }// gotoxy(52 - 1, 18);  break; }// 1주사위 
	case 64: { cout << "KEEP";  return SECOND; } // gotoxy(64 - 1, 18); break;}
	case 76: { cout << "KEEP";  return THIRD; } //  gotoxy(76 - 1, 18); break;}
	case 88: { cout << "KEEP";  return FOURTH; } // gotoxy(88 - 1, 18); break;}
	case 100: { cout << "KEEP";  return FIFTH; } // gotoxy(100 - 1, 18); break;}
	}
	/*
	cout << "    ";
	switch (n) {
	case 1: { gotoxy(52 - 1, 18);  break; }// 1주사위 
	case 2: { gotoxy(64 - 1, 18); break; }
	case 3: { gotoxy(76 - 1, 18); break; }
	case 4: { gotoxy(88 - 1, 18); break; }
	case 5: { gotoxy(100 - 1, 18); break; }	
	}
	*/
}

int GameSceneInputManager::TableFixedDraw() { //표의 행
	
	COORD pos;
	pos = getxy();
	if (pos.X < 40) {
		gotoxy(pos.X + 2, pos.Y);
		cout << "/";
		gotoxy(pos.X, pos.Y);
	}

	switch (pos.Y) {
	case5: { return 1; } // 행의 번호에 따라 해당 위치의 "숫자" 옆에 / 그리기
	case7: { return 2; }
	case9: { return 3; }
	case11: { return 4; }
	case13: { return 5; }
	case15: { return 6; }
	case17: { return 7; }
	case19: { return 8; }
	case21: { return 9; }
	case23: { return 10; }
	case25: { return 11; }
	case27: { return 12; }

	}
	
	
	
}

GameSceneDraw::GameSceneDraw() { // 생성자에서 그림 그리기
	EraseScene();
	TableDraw table_draw;// 표그리기
	DiceDraw dice_draw; //주사위그리기
	TableValueDraw s({});
	DiceValueDraw v({6,6,6,6,6});
	vector<pair<int, int>> table_pos = { {24, 5}, {36, 5} };
	pair<int, int> dice_pos = { 52, 15 };
	GameSceneInputManager game_scene_input_manager;
	//game_scene_input_manager.TableFixedDraw(2);
	game_scene_input_manager.KeyMovingControl();

}

EndSceneDraw::EndSceneDraw() {

	/*  누가 승리하였는지 띄워주고 아래에 메뉴 출력 */

	gotoxy(42, 15); // starscene과 같은 위치에 메뉴 나오도록 하고 싶음
	cout << "Let's play this game!"; // 0
	gotoxy(42, 16);
	cout << "How to play this game?"; // 1
	gotoxy(42, 17);
	cout << "Exit"; // 2

	/* team 정보 표시 */
	gotoxy(38, 25);
	cout << "< Object Oriented Programming >";
	gotoxy(48, 26);
	cout << "Team 4";
}

TableDraw::TableDraw() {

	vector<string> categories;
	categories = { "Aces  ", "Deuce5s", "Threes", "Fours", "Fives", "Sixes", "Subtotal"
		, "Choice", "4 of a Kind", "Full House", "S.Straight", "L.Straight", "Yatch", "Total" };
	//EraseScene();

	cout << "  -----------------------------------------\n";
	cout.width(2);
	cout << "   " << std::left << "       ";
	cout << "\t  ｜           ｜\n";

	cout << "   " << std::left << "       ";
	cout << "\t  ｜     1p    ｜     2p     \n";

	cout << "   " << std::left << "       ";
	cout << "\t  ｜           ｜\n";


	for (int i = 0; i < 13; i++) {
		cout << "  -----------------------------------------\n";
		cout.width(2);
		cout << "   " << std::left << categories.at(i);
		cout << "\t  ｜           ｜\n";
	}

	cout << "  -----------------------------------------\n";
	cout << "   " << std::left << categories.at(13);
	cout << "\t  ｜           ｜\n";

}

DiceDraw::DiceDraw() {
	gotoxy(48, 13); 
	cout << "┌──────┐";
	gotoxy(48, 14);
	cout << "│      │";
	gotoxy(48, 15);
	cout << "│      │";
	gotoxy(48, 16);
	cout << "│      │";
	gotoxy(48, 17);
	cout << "└──────┘";
	gotoxy(52, 15); // 첫번째 주사위의 숫자위치
	cout << "1";

	gotoxy(60, 13);
	cout << "┌──────┐";
	gotoxy(60, 14);
	cout << "│      │";
	gotoxy(60, 15);
	cout << "│      │";
	gotoxy(60, 16);
	cout << "│      │";
	gotoxy(60, 17);
	cout << "└──────┘";
	gotoxy(64, 15); // 두번째 주사위의 숫자위치
	cout << "2";

	gotoxy(72, 13);
	cout << "┌──────┐";
	gotoxy(72, 14);
	cout << "│      │";
	gotoxy(72, 15);
	cout << "│      │";
	gotoxy(72, 16);
	cout << "│      │";
	gotoxy(72, 17);
	cout << "└──────┘";
	gotoxy(76, 15); // 세번째 주사위의 숫자위치
	cout << "3";

	gotoxy(84, 13);
	cout << "┌──────┐";
	gotoxy(84, 14);
	cout << "│      │";
	gotoxy(84, 15);
	cout << "│      │";
	gotoxy(84, 16);
	cout << "│      │";
	gotoxy(84, 17);
	cout << "└──────┘";
	gotoxy(88, 15); // 네번째 주사위의 숫자위치
	cout << "4";

	gotoxy(96, 13);
	cout << "┌──────┐";
	gotoxy(96, 14);
	cout << "│      │";
	gotoxy(96, 15);
	cout << "│      │";
	gotoxy(96, 16);
	cout << "│      │";
	gotoxy(96, 17);
	cout << "└──────┘";
	gotoxy(100, 15); // 다섯번째 주사위의 숫자위치
	cout << "5";
}

TableValueDraw::TableValueDraw(vector<int> v) {
	int player_turn = 1;
	vector<int> table_value;
	for (int i = 0; i < 14; i++) {
		table_value.push_back(i);
	}
	for (int i = 0; i < table_value.size(); i++) {
		gotoxy(table_pos[player_turn - 1].first, table_pos[player_turn - 1].second + 2 * i);
		cout << table_value[i];
	}
}

DiceValueDraw::DiceValueDraw(vector<int> dice_value) {
	for (int i = 0; i < dice_value.size(); i++) {
		gotoxy(dice_pos.first + 12 * i, dice_pos.second);
		cout << dice_value[i];
	}
}

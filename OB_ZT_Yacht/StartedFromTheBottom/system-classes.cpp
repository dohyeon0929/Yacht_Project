#pragma once
#include "essential.h"
#include "system-classes.h"

static GameManager gm;

//Scene
COORD Scene::getxy() {
	CONSOLE_SCREEN_BUFFER_INFO cursor;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	return cursor.dwCursorPosition;
}
void Scene::EraseScene() {
	system("cls");
}
void Scene::gotoxy(int x, int y) { // 키보드 입력으로 움직임
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
int Scene::KeyControl() {

	char temp = _getch();

	if (temp == 'w' || temp == 'W' || temp == 72) { return UP; }
	else if (temp == 'a' || temp == 'A' || temp == 75) { return LEFT; }
	else if (temp == 's' || temp == 'S' || temp == 80) { return DOWN; }
	else if (temp == 'd' || temp == 'D' || temp == 77) { return RIGHT; }
	else if (temp == 13) { return ENTER; }
}
void Scene::KeyMovingControl() {}

//StartScene
StartScene::StartScene() {
	Init();
	TitleDraw();
	KeyMovingControl();
}
void StartScene::Init() {
	system("mode con cols=110 lines=35 | title Yatch Dice with Special Items");
}
void StartScene::TitleDraw() { // title은 startscene에만 등장
	std::cout << "\n\n";
	gotoxy(25, 2);
	std::cout << " __   __        _          _      ______  _    \n";
	gotoxy(26, 3);
	std::cout << "\\ \\ / /       | |        | |     |  _  \\(_)            \n";
	gotoxy(26, 4);
	std::cout << " \\ V /   __ _ | |_   ___ | |__   | | | | _   ___   ___ \n";
	gotoxy(26, 5);
	std::cout << "  \\ /   / _` || __| / __|| '_ \\  | | | || | / __| / _ \\\n";
	gotoxy(26, 6);
	std::cout << "  | |  | (_| || |_ | (__ | | | | | |/ / | || (__ |  __/\n";
	gotoxy(26, 7);
	std::cout << "  \\_/   \\__,_| \\__| \\___||_| |_| |___/  |_| \\___| \\___|\n";
	gotoxy(0, 11);

	for (int i = 0; i < 110; i++) std::cout<<"■";
	std::cout << '\n';

	gotoxy(42, 15); 
	std::cout << "Let's play this game!"; // 0
	gotoxy(42, 16);
	std::cout << "How to play this game?"; // 1
	gotoxy(42, 17);
	std::cout << "Exit"; // 2

	/* team 정보 표시 */
	gotoxy(38, 25);
	std::cout << "< Object Oriented Programming >";
	gotoxy(48, 26);
	std::cout << "Team 4";
}
void StartScene::KeyMovingControl() {
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
				std::cout << " ";
				gotoxy(x - 2, --y);
				std::cout << ">";
			}
			break;
		}
		case DOWN: {
			if (y < 17) {
				gotoxy(x - 2, y);
				std::cout << " ";
				gotoxy(x - 2, ++y); //
				std::cout << ">";
			}
			break;
		}
		case ENTER: {
			if (y - 15 == 0) { // gamestart
				//gamestart = 1;
				//GameSceneDraw gamescene;
				gm.SetScene("game");
				stop = true;
				break;
			}
			else if (y - 15 == 1) { // InfoScene으로 전환
				//InfoSceneDraw infoscene;
				gm.SetScene("info");
			}

			else if (y - 15 == 2) { // exit
				gotoxy(0, 27);
				std::cout << "\n\n--------------------------------------------------------------------------------------";
				exit(1);
			}

		}	    
		}
	}
}

//InfoScene
InfoScene::InfoScene() {
	InfoDraw();
	KeyMovingControl();
}
void InfoScene::InfoDraw() {
	EraseScene();
	std::cout << "게임 정보 설명\n";
	std::cout << "엔터키를 누르면 startscene으로 돌아갑니다.";
}
void InfoScene::KeyMovingControl() {
	while (1) {
		if (KeyControl() == ENTER) {
			EraseScene();
			gm.SetScene("start");
			gotoxy(40, 15);
			break;
		}
	}
}

//GameScene
GameScene::GameScene() {
	for (int x = 1; x <= 2; x++) {
		for (int i = 0; i < 12; i++) {
			table_pos_set[x][i] = { x,table_y_pos[i] };
			table_can_go[table_pos_set[x][i]] = true;
		}
	}
	for (round = 1; round <= max_round; round++) {
		for (turn = 1; turn <= max_turn; turn++) {
			bool first_roll = true;
			EraseScene();
			TableDraw();// 표그리기
			DiceDraw(); //주사위그리기
			dice_set.DefaultValue();
			for (roll = 1; roll <= max_roll; roll++) {

				RollTurnRoundDraw();
				if (first_roll) {
					TableValueDraw(1,player[1].GetChartNum());
					TableValueDraw(2,player[2].GetChartNum());
				}
				else {
					TableValueDraw(tmp_player[turn].GetChartNum());
				}
				MakeDiceNumSet();
				DiceValueDraw(dice_num_set);

				int command = KeyMovingControlReturn();

				MakeDiceNumSet();
				DiceValueDraw(dice_num_set);
				tmp_player[turn].SetDiceNumSet(dice_num_set);
				tmp_player[turn].FillValues();
				for (int i = 0; i < 12; i++) {
					if (table_fixed[turn][i]) {
						tmp_player[turn].SetChartNum(i, player[turn].GetChartNum()[i]);
					}
				}

				if (command == 1) break;
				if (first_roll) {
					roll--;
					first_roll = false;
				}
			}
		}
	}
	WhosWinner();
	gm.SetScene("end");
}
void GameScene::RollTurnRoundDraw() { //  센터가 76, 8
	gotoxy(64, 8);
	std::cout << "Round : " << round;
	gotoxy(76, 8);
	std::cout << "Turn : " << turn<<"p";
	gotoxy(89, 8);
	std::cout << "Roll : " << roll;
}
int GameScene::KeyMovingControlReturn()
{
	int x = 52;
	int y = 15;
	gotoxy(52, 15); // 무조건 첫번째 주사위 커서로 이동
	gotoxy(x, y - 3);
	std::cout << "V";
	gotoxy(52, 15); // 무조건 첫번째 주사위 커서로 이동
	while (1) {
		int n = KeyControl();
		switch (n) {

		case RIGHT: {
			if (x < 100 && x > 40) { // 가장 오른쪽 주사위는 넘어가지 않음, 주사위에서의 right
				gotoxy(x, y - 3);
				std::cout << " ";
				gotoxy(x + 12, y - 3);
				std::cout << "V";
				gotoxy(x + 12, y);
				x = x + 12;
			}
			else if (x < 40) { // 표에서의 right, 해당 cell의 커서 삭제
				COORD pos;
				pos = getxy();
				gotoxy(pos.X - 1, pos.Y);
				std::cout << "  ";
				gotoxy(pos.X , pos.Y);
				cout << "  ";
				x = 52;
				y = 15;
				gotoxy(52, 15); // 무조건 첫번째 주사위 커서로 이동
				gotoxy(x, y - 3);
				std::cout << "V";
				gotoxy(x, y);
			}
			break;
		}
		case LEFT: {
			if (x > 52) { // 주사위에서 left
				gotoxy(x, y - 3);
				std::cout << " ";
				gotoxy(x - 12, y - 3);
				std::cout << "V";
				gotoxy(x - 12, y);
				x = x - 12;
			}
			else if (x == 52) { // table로 들어가기
				gotoxy(x, y - 3);
				std::cout << " ";
				if (turn == 1) x = 22;
				else if (turn == 2) x = 34;
				int tmp_y = 5;
				while (!table_can_go[{turn, tmp_y}]) {
					tmp_y += 2;
					if (tmp_y >= 29)break;
				}
				if (tmp_y <= 29) {
					gotoxy(x, y);
					std::cout << " ";
					gotoxy(x, tmp_y);
					std::cout << "V";
					gotoxy(x, tmp_y);
					y = tmp_y;
				}
			}
			break;
		}
		case SPACE: {
			if (x < 101 && x > 51) { // 주사위에서 스페이스, keep	
				COORD pos;
				pos = getxy(); // 커서 위치
				int dice_num = (pos.X - 52) / 12;
				if (dice_num_set[dice_num] != 0) {
					dice_set.Toggle(dice_num);
					if (dice_set.GetDice(dice_num).IsActivated()) {
						DiceActivateDraw((int)pos.X, (int)pos.Y);
					}
					else {
						DiceKeepDraw((int)pos.X, (int)pos.Y);
					}
				}
			}
			break;
		}
		case UP: { // 표에서 위로가는 방향키 눌렀을 때
			if (y > 5 && x < 50) { // 위로 더는 못가게, 주사위에서는 위로 안감
				int tmp_y = y-2;
				while (!table_can_go[{turn, tmp_y}]) {
					tmp_y -= 2;
					if (tmp_y <= 5)break;
				}
				if (tmp_y >= 5) {
					gotoxy(x, y);
					std::cout << " ";
					gotoxy(x, tmp_y);
					std::cout << "V";
					gotoxy(x, tmp_y);
					y = tmp_y;
				}
			}
			break;
		}

		case DOWN: { // 표에서 아래로 가는 방향키 눌렀을 떄
			if (y < 29 && x < 50) { // 위로 더는 못가게, 주사위에서는 위로 안감
				int tmp_y = y + 2;
				while (!table_can_go[{turn, tmp_y}]) {
					tmp_y += 2;
					if (tmp_y > 29)break;
				}
				if (tmp_y <= 29) {
					gotoxy(x, y);
					std::cout << " ";
					gotoxy(x, tmp_y);
					std::cout << "V";
					gotoxy(x, tmp_y);
					y = tmp_y;
				}
			}
			break;
		}

		case ENTER: { // 표에서 엔터, 점수박기
			if (x < 50) {
				if (dice_set.GetDiceSet()[0].GetDiceNum() != 0) {
					cout << " ";
					COORD cursor_pos;
					cursor_pos = getxy();
					int pos;
					for (int i = 0; i < 12; i++) {
						if (cursor_pos.Y == table_y_pos[i]) {
							pos = i;
							table_can_go[{turn, cursor_pos.Y}] = false;
							table_fixed[turn][pos] = true;
							break;
						}
					}
					player[turn].SetChartNum(pos, tmp_player[turn].GetChartNum()[pos]);
					return 1;
				}
			}
			else {
				if (roll < 3) {
					gotoxy(x, y - 3);
					cout << "  ";
					dice_set.Roll();
					return 0;
				}

			}
		}
		}
	}
}
void GameScene::MakeDiceNumSet() {
	this->dice_num_set.clear();
	for (auto i : dice_set.GetDiceSet()) {
		dice_num_set.push_back(i.GetDiceNum());
	}
}
void GameScene::TableDraw() {

	vector<string> categories;
	categories = { "Aces  ", "Deuce5s", "Threes", "Fours", "Fives", "Sixes", "Subtotal"
		, "Choice", "4 of a Kind", "Full House", "S.Straight", "L.Straight", "Yatch", "Total" };
	//EraseScene();

	std::cout << "  -----------------------------------------\n";
	std::cout.width(2);
	std::cout << "   " << std::left << "       ";
	std::cout << "\t  ｜           ｜\n";

	std::cout << "   " << std::left << "       ";
	std::cout << "\t  ｜     1p    ｜     2p     \n";

	std::cout << "   " << std::left << "       ";
	std::cout << "\t  ｜           ｜\n";


	for (int i = 0; i < 13; i++) {
		std::cout << "  -----------------------------------------\n";
		std::cout.width(2);
		std::cout << "   " << std::left << categories.at(i);
		std::cout << "\t  ｜           ｜\n";
	}

	std::cout << "  -----------------------------------------\n";
	std::cout << "   " << std::left << categories.at(13);
	std::cout << "\t  ｜           ｜\n";

}
void GameScene::DiceDraw() {
	int arr[] = { 48,60,72,84,96 };
	for (int i = 0; i < 5; i++) {
		gotoxy(arr[i], 13);
		std::cout << "┌──────┐";
		gotoxy(arr[i], 14);
		std::cout << "│      │";
		gotoxy(arr[i], 15);
		std::cout << "│      │";
		gotoxy(arr[i], 16);
		std::cout << "│      │";
		gotoxy(arr[i], 17);
		std::cout << "└──────┘";
	}
}
void GameScene::TableValueDraw(const vector<int>& table_value) {
	for (int i = 0; i < table_value.size(); i++) {
		int tmp = 0;
		if (i >= 6)tmp = 2;
		gotoxy(table_pos[turn].first, table_pos[turn].second + 2 * i+tmp);
		cout << "  ";
		gotoxy(table_pos[turn].first, table_pos[turn].second + 2 * i+tmp);
		if (table_value[i] < 0)
			std::cout << "";
		else
			std::cout << table_value[i];
	}
}
void GameScene::TableValueDraw(const int& who, const vector<int>& table_value) {
	for (int i = 0; i < table_value.size(); i++) {
		int tmp = 0;
		if (i >= 6)tmp = 2;
		int x = table_pos[who].first;
		int y = table_pos[who].second + 2 * i + tmp;
		gotoxy(x,y);
		if (table_value[i] < 0)
			std::cout << "";
		else {
			std::cout << table_value[i];
			gotoxy(x - 1, y);
			cout << "#";
			gotoxy(x + 2, y);
			cout << "#";
			gotoxy(x, y);
		}
	}
	gotoxy(table_pos[who].first, table_total_y_pos[0]);
	cout << player[who].GetSubTotal();
	gotoxy(table_pos[who].first, table_total_y_pos[1]);
	cout << player[who].GetTotal();
}
void GameScene::DiceValueDraw(const vector<int>& dice_num_set) {
	for (int i = 0; i < dice_num_set.size(); i++) {
		gotoxy(dice_pos.first + 12 * i, dice_pos.second);
		if(dice_num_set[i]!=0)
			std::cout << dice_num_set[i];
	}
}
void GameScene::WhosWinner() {
	if (player[1].GetTotal() > player[2].GetTotal()) {
		gm.SetWinner(1);
	}
	else if (player[1].GetTotal() < player[2].GetTotal()) {
		gm.SetWinner(2);
	}
	else {
		gm.SetWinner(0);
	}
}
void GameScene::DiceKeepDraw(const int& x, const int& y) {
	gotoxy(x - 2, 19);
	cout << "KEEP";
	gotoxy(x, y);
}
void GameScene::DiceActivateDraw(const int& x, const int& y) {
	gotoxy(x - 2, 19);
	cout << "    ";
	gotoxy(x, y);
}

//EndScene
EndScene::EndScene() {
	EndSceneDraw();
}

void EndScene::EndSceneDraw() {
	EraseScene();
	gotoxy(50, 50);
	cout << gm.GetWinner() << "p is Winner!!";
	//cout << "Press Enter to play again";
}

//GameManager
void GameManager::SetScene(const string& usage) {
	if (usage == "start")
		this->now_scene = new StartScene();
	else if (usage == "info")
		this->now_scene = new InfoScene();
	else if (usage == "game")
		this->now_scene = new GameScene();
	else if (usage == "end")
		this->now_scene = new EndScene();
}
void GameManager::SetWinner(const int& winner) {
	this->winner = winner;
}


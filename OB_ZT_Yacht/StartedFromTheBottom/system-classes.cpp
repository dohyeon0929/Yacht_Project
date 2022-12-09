#pragma once
#include "essential.h"
#include "system-classes.h"

static GameManager gm; // 게임을 총괄하는 전역 변수. 

//Scene
COORD Scene::getxy() { // 현재 커서의 위치를 반환하는 함수
	CONSOLE_SCREEN_BUFFER_INFO cursor;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	return cursor.dwCursorPosition;
}
void Scene::EraseScene() { // 화면 지우기
	system("cls");
}
void Scene::gotoxy(int x, int y) { // 키보드 입력으로 움직임
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
int Scene::KeyControl() { // 사용자 입력 컨트롤 

	char temp = _getch();

	if (temp == 'w' || temp == 'W' || temp == 72) { return UP; }
	else if (temp == 'a' || temp == 'A' || temp == 75) { return LEFT; }
	else if (temp == 's' || temp == 'S' || temp == 80) { return DOWN; }
	else if (temp == 'd' || temp == 'D' || temp == 77) { return RIGHT; }
	else if (temp == 13) { return ENTER; }
}
void Scene::KeyMovingControl() {} // 씬 별로 다 다를 예정

//StartScene
StartScene::StartScene() {
	Init();
	TitleDraw();
	KeyMovingControl();
}
void StartScene::Init() { // 시작 화면 크기 설정. 프로그램 이름 설정. 
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

	for (int i = 0; i < 110; i++) std::cout<<"=";
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
void StartScene::KeyMovingControl() { // 키 움직이는 거 컨트롤 메소드
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
				gm.SetScene("game");
				stop = true;
				break;
			}
			else if (y - 15 == 1) { // InfoScene으로 전환
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
InfoScene::InfoScene() { // 룰 설명 씬
	InfoDraw();
	KeyMovingControl();
}
void InfoScene::InfoDraw() {
	EraseScene();
	std::cout << "\n\n ! ! Welcome to Yatch Dice ! !\n\n\n";
	std::cout << " This game's kind of like poker, but with dice instead of cards.\n\n";
	std::cout << " There are total 5 dices.\n\n";
	std::cout << " You can roll the dices 3 times, keep specific dice after the roll.\n\n";
	std::cout << " Enter the result of rolling 3 times in the desired table cell.\n\n";
	std::cout << " Fill in the table cell one by one.\n\n";
	std::cout << " If you fill in all table cells, the person with the highest score WIN ! !\n\n";
	std::cout << " \nPress the enter to return start scene.";

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
GameScene::GameScene() { // 본 게임 화면
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
				RollTurnRoundDraw(); //라운드 정보 다 표시 
				if (first_roll) { 
					TableValueDraw(1,player[1].GetChartNum()); // 아무런 주사위 값이 없기 때문에 
					TableValueDraw(2,player[2].GetChartNum()); // 플레이어들이 가지고 있는 값들만 표시
				}
				else {
					TableValueDraw(tmp_player[turn].GetChartNum()); // 주사위 값에 따른 임시 테이블 표시
				}
				MakeDiceNumSet(); // dice_set을 dice_num_set으로 변환
				DiceValueDraw(dice_num_set); // 5개 dice의 값을 표시

				int command = KeyMovingControlReturn(); // 사용자 입력을 받음. 
				// 사용자가 주사위를 굴리거나 점수를 고정하기 전까지 무한 반복이 되며 사용자 입력을 받는다. 
				// 사용자가 점수를 고정하면 1, 아니면 0을 반환한다. 

				MakeDiceNumSet(); // 사용자가 주사위 굴렸을 때를 대비하여
				DiceValueDraw(dice_num_set); // 주사위 다시 그려주기 
				tmp_player[turn].SetDiceNumSet(dice_num_set);  // 새로운 주사위 값에 대한 임시 테이블 작성
				tmp_player[turn].FillValues();
				for (int i = 0; i < 12; i++) { // 사용자가 고정한 값을 임시 테이블에 반영
					if (table_fixed[turn][i]) {
						tmp_player[turn].SetChartNum(i, player[turn].GetChartNum()[i]);
					}
				}
				if (command == 1) break; // 점수 고정했으면 그 즉시 턴을 넘긴다. 
				if (first_roll) { // 첫 롤의 경우 생기는 예외 때문에, 첫 롤인지 아닌지 여부를 가르는 부분
					roll--;
					first_roll = false;
				}
			}
		}
	}
	WhosWinner(); // 12라운드까지 다 끝나면 누가 승자인지 판단한 후, GameManager gm에게 이를 전달한다. 
	gm.SetScene("end"); // end씬으로 전환
}
void GameScene::RollTurnRoundDraw() { // 몇 번째 롤,턴,라운드인지 그리는 메소드
	// 센터가 76, 8  
	gotoxy(59, 8);
	std::cout << "Round : " << round;
	gotoxy(71, 8);
	std::cout << "Turn : " << turn <<"p";
	gotoxy(84, 8);
	std::cout << "Roll : " << roll;

	gotoxy(59, 22);
	std::cout << "Enter : select value or roll the dice";
	gotoxy(59, 23);
	std::cout << "Space : keep your dice";
}
int GameScene::KeyMovingControlReturn() // 롤에서 사용자한테 입력을 받는 메소드
{
	int x = 52;
	int y = 15;
	gotoxy(52, 15); // 무조건 첫번째 주사위 커서로 이동
	gotoxy(x, y - 3);
	std::cout << "V";
	gotoxy(52, 15); // 무조건 첫번째 주사위 커서로 이동
	while (1) {
		int n = KeyControl(); // 사용자한테 입력 뭐 받았는지 판단
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
				x = 52; y = 15;
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
		case UP: { // 표에서 위로가는 방향키 눌렀을 때
			if (y > 5 && x < 50) { // 위로 더는 못가게, 주사위에서는 위로 안감
				int tmp_y = y - 2;
				while (!table_can_go[{turn, tmp_y}]) {
					tmp_y -= 2;
					if (tmp_y < 5)break;
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

		case ENTER: { // 표에서 엔터, 점수박기
			if (x < 50) { // 표 위에서 엔터를 눌렀다면
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
			else { // 주사위 위에서 엔터를 눌렀다면
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
void GameScene::MakeDiceNumSet() { // dice_set을 dice_num_set으로 변환
	this->dice_num_set.clear();
	for (auto i : dice_set.GetDiceSet()) {
		dice_num_set.push_back(i.GetDiceNum());
	}
}
void GameScene::TableDraw() { // table 틀 그리기

	vector<string> categories;
	categories = { "Aces  ", "Deuces", "Threes", "Fours", "Fives", "Sixes", "Subtotal"
		, "Choice", "4 of a Kind", "Full House", "S.Straight", "L.Straight", "Yatch", "Total" };
	std::cout << "  +---------------+-----------+-----------+\n";
	std::cout.width(2);
	std::cout << "  | " << std::left << "       ";
	std::cout << "\t  |           |           |\n";

	std::cout << "  | " << std::left << "       ";
	std::cout << "\t  |     1p    |     2p    |\n";

	std::cout << "  | " << std::left << "       ";
	std::cout << "\t  |           |           |\n";


	for (int i = 0; i <= 12; i++) {
		std::cout << "  +---------------+-----------+-----------+\n";
		std::cout.width(2);
		std::cout << "  |" << std::left << " "<<categories.at(i);
		std::cout << "\t  |           |           |\n";
	}

	std::cout << "  +---------------+-----------+-----------+\n";
	std::cout << "  |" << std::left << " "<<categories.at(13);
	std::cout << "\t  |           |           |\n";
	std::cout << "  +---------------+-----------+-----------+\n";

}
void GameScene::DiceDraw() { // 주사위 틀 그리기
	int arr[] = { 48,60,72,84,96 };
	for (int i = 0; i < 5; i++) {
		gotoxy(arr[i], 13);
		std::cout << "+------+";
		gotoxy(arr[i], 14);
		std::cout << "|      |";
		gotoxy(arr[i], 15);
		std::cout << "|      |";
		gotoxy(arr[i], 16);
		std::cout << "|      |";
		gotoxy(arr[i], 17);
		std::cout << "+------+";
	}
}
void GameScene::TableValueDraw(const vector<int>& table_value) { // 표 값 그리기 (임시 테이블 전용)
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
void GameScene::TableValueDraw(const int& who, const vector<int>& table_value) { // 표 값 그리기 (사용자 테이블 전용)
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
void GameScene::DiceValueDraw(const vector<int>& dice_num_set) { // 주사위 값 그리기
	for (int i = 0; i < dice_num_set.size(); i++) {
		gotoxy(dice_pos.first + 12 * i, dice_pos.second);
		if(dice_num_set[i]!=0)
			std::cout << dice_num_set[i];
	}
}
void GameScene::WhosWinner() { // 승자 판단
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
void GameScene::DiceKeepDraw(const int& x, const int& y) { // 주사위 KEEP 한 거 표시
	gotoxy(x - 2, 19);
	cout << "KEEP";
	gotoxy(x, y);
}
void GameScene::DiceActivateDraw(const int& x, const int& y) { // 주사위 Activate 한 거 표시
	gotoxy(x - 2, 19);
	cout << "    ";
	gotoxy(x, y);
}

//EndScene
EndScene::EndScene() { 
	EndSceneDraw();
	KeyMovingControl();
}

void EndScene::KeyMovingControl() {
	while (1) {
		if (KeyControl() == ENTER) {
			EraseScene();
			gm.SetScene("start");
			gotoxy(40, 15);
			break;
		}
	}
}

void EndScene::EndSceneDraw() {
	EraseScene();

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

	for (int i = 0; i < 110; i++) std::cout << "=";

	if (gm.GetWinner() == 0) {
		gotoxy(52, 15);
		cout << "draw!!";
	}
	else {
		gotoxy(45, 15);
		std::cout << gm.GetWinner() << "p is Winner!!\n\n";
	}
	gotoxy(38, 17);
	cout << "Press Enter : Return to Start";
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


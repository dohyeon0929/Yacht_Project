#include "scene-classes.h"

void StartSceneDraw::Init() {
	system("mode con cols=110 lines=35 | title Yatch Dice with Special Items");
}

void StartSceneDraw::TitleDraw() { // title�� startscene���� ����
	
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
	cout << "��������������������������������������������������������";

	gotoxy(42, 15); // ���⼭ �޴� Ŭ�� Ŀ�� ����
	cout << "Let's play this game!"; // 0
	gotoxy(42, 16);
	cout << "How to play this game?"; // 1
	gotoxy(42, 17);
	cout << "Exit"; // 2

	/* team ���� ǥ�� */
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
	while (1) { // ���� �ݺ�
		int n = KeyControl(); // Ű���� �Է��� Ű������ �޾ƿ���
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
				gotoxy(x - 2, ++y);
				cout << ">";
			}
			break;
		}
		case ENTER: {
			if (y - 15 == 0) { // gamestart
				GameSceneDraw gamescene;
				stop = true;
			}
			else if (y - 15 == 1) { // InfoScene���� ��ȯ
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

void Draw::gotoxy(int x, int y) { // Ű���� �Է����� ������
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ� ��������
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

InfoSceneDraw::InfoSceneDraw() { // ���� ���� ȭ��
	EraseScene();
	cout << "���� ���� ����\n";
	cout << "����Ű�� ������ startscene���� ���ư��ϴ�.";
	InfoSceneInputManager infosceneinputmanager;
	infosceneinputmanager.KeyMovingControl();

}

void EndSceneInputManager::KeyMovingControl() {
	int x = 42;
	int y = 15;
	gotoxy(x - 2, y);
	while (1) { // ���� �ݺ�
		int n = KeyControl(); // Ű���� �Է��� Ű������ �޾ƿ���
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
			else if (y - 15 == 1) { // InfoScene���� ��ȯ
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
			gotoxy(42, 15);
			break;
		}
	}
}

void GameSceneInputManager::KeyMovingControl() { // ��� �� ������ ��������
	
}

GameSceneDraw::GameSceneDraw() { // �����ڿ��� �׸� �׸���
	EraseScene();
	vector<string> categories;
	categories = { "Aces  ", "Deuces", "Threes", "Fours", "Fives", "Sixes", "Subtotal"
		, "Choice", "4 of a Kind", "Full House", "S.Straight", "L.Straight", "Yatch", "Total" };
	EraseScene();

	cout << "  -----------------------------------------\n";
	cout.width(2);
	cout << "   " << std::left << "       ";
	cout << "\t  l           l\n";

	cout << "   " << std::left << "       ";
	cout << "\t  l     1p    l     2p     \n";

	cout << "   " << std::left << "       ";
	cout << "\t  l           l\n";


	for (int i = 0; i < 13; i++) {
		cout << "  -----------------------------------------\n";
		cout.width(2);
		cout << "   " << std::left << categories.at(i);
		cout << "\t  l           l\n";
	}

	cout << "  -----------------------------------------\n";
	cout << "   " << std::left << categories.at(13);
	cout << "\t  l           l\n";
	//TableDraw table_draw;// ǥ�׸���
	//DiceDraw dice_draw; //�ֻ����׸���
	TableValueDraw s({});
	DiceValueDraw v({6,6,6,6,6});
	vector<pair<int, int>> table_pos = { {24, 5}, {36, 5} };
	pair<int, int> dice_pos = { 52, 15 };

	//GameSceneInputManager gamesceneinputmanager;
	//gamesceneinputmanager.KeyMovingControl();
}

EndSceneDraw::EndSceneDraw() {

	/*  ���� �¸��Ͽ����� ����ְ� �Ʒ��� �޴� ��� */

	gotoxy(42, 15); // starscene�� ���� ��ġ�� �޴� �������� �ϰ� ����
	cout << "Let's play this game!"; // 0
	gotoxy(42, 16);
	cout << "How to play this game?"; // 1
	gotoxy(42, 17);
	cout << "Exit"; // 2

	/* team ���� ǥ�� */
	gotoxy(38, 25);
	cout << "< Object Oriented Programming >";
	gotoxy(48, 26);
	cout << "Team 4";
}

TableDraw::TableDraw() {

	vector<string> categories;
	categories = { "Aces  ", "Deuces", "Threes", "Fours", "Fives", "Sixes", "Subtotal"
		, "Choice", "4 of a Kind", "Full House", "S.Straight", "L.Straight", "Yatch", "Total" };
	EraseScene();

	cout << "  -----------------------------------------\n";
	cout.width(2);
	cout << "   " << std::left << "       ";
	cout << "\t  l           l\n";

	cout << "   " << std::left << "       ";
	cout << "\t  l     1p    l     2p     \n";

	cout << "   " << std::left << "       ";
	cout << "\t  l           l\n";


	for (int i = 0; i < 13; i++) {
		cout << "  -----------------------------------------\n";
		cout.width(2);
		cout << "   " << std::left << categories.at(i);
		cout << "\t  l           l\n";
	}

	cout << "  -----------------------------------------\n";
	cout << "   " << std::left << categories.at(13);
	cout << "\t  l           l\n";

}

DiceDraw::DiceDraw() {
	gotoxy(48, 13); // ù��° ���̽� ���� ��ġ	
	cout << "����������������";
	gotoxy(48, 14);
	cout << "��      ��";
	gotoxy(48, 15);
	cout << "��      ��";
	gotoxy(48, 16);
	cout << "��      ��";
	gotoxy(48, 17);
	cout << "����������������";
	gotoxy(52, 15); // ù��° �ֻ����� ������ġ
	cout << "1";

	gotoxy(60, 13);
	cout << "����������������";
	gotoxy(60, 14);
	cout << "��      ��";
	gotoxy(60, 15);
	cout << "��      ��";
	gotoxy(60, 16);
	cout << "��      ��";
	gotoxy(60, 17);
	cout << "����������������";
	gotoxy(64, 15); // �ι�° �ֻ����� ������ġ
	cout << "2";

	gotoxy(72, 13);
	cout << "����������������";
	gotoxy(72, 14);
	cout << "��      ��";
	gotoxy(72, 15);
	cout << "��      ��";
	gotoxy(72, 16);
	cout << "��      ��";
	gotoxy(72, 17);
	cout << "����������������";
	gotoxy(76, 15); // ����° �ֻ����� ������ġ
	cout << "3";

	gotoxy(84, 13);
	cout << "����������������";
	gotoxy(84, 14);
	cout << "��      ��";
	gotoxy(84, 15);
	cout << "��      ��";
	gotoxy(84, 16);
	cout << "��      ��";
	gotoxy(84, 17);
	cout << "����������������";
	gotoxy(88, 15); // �׹�° �ֻ����� ������ġ
	cout << "4";

	gotoxy(96, 13);
	cout << "����������������";
	gotoxy(96, 14);
	cout << "��      ��";
	gotoxy(96, 15);
	cout << "��      ��";
	gotoxy(96, 16);
	cout << "��      ��";
	gotoxy(96, 17);
	cout << "����������������";
	gotoxy(100, 15); // �ټ���° �ֻ����� ������ġ
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
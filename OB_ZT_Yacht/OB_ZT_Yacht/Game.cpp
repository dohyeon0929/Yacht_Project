#include "essential.h"
#include "dice-classes.h"
#include "scene-classes.h"
#include "yatch_chart.h"
#include <io.h>
#include <fcntl.h>
GameManage::GameManage()
{
	int round, turn, roll;
	ChartFactory factory;
	Chart player1 = factory.GetChart();
	Chart player2 = factory.GetChart();
	vector<Chart>player;
	player.push_back(player1);
	player.push_back(player2);
	vector<int>dice = { 1,2,3,4,5 }; // 주사위 셋 임시값
	int winner;
	player[0].GetRoundResult();

	for (int i = 0; i < 12; i++) //12라운드 진행
	{
		for (int j = 0; i < 2; j++) //플레이어가 번갈아 가면서 진행
		{
			GameSceneInputManager game_scene_input_manager;
			//cout <<  "입니다 ";
			//TableValueDraw(player[j].GetRoundResult());
			for (int x = 0; x < 3; x++) //한 플레이어가 3번까지 던질 수 있음
			{
				while (1)
				{
					//임시값
					//cout << "test1\n";
					player[i].SetDiceValue(dice);
					//cout << "test2\n";
					player[i].SetDefaultValue();
					//cout << "test3\n";
					player[i].CalSet();
					TableValueDraw(player[i].GetChartValue());
					//cout << "test4\n";
					//TableValueDraw(player[i].GetRoundResult());
					int command = game_scene_input_manager.KeyMovingControlReturn();
					switch (command)
					{
					case 1: //주사위 굴림
						player[i].SetDiceValue(dice);
						player[i].SetDefaultValue();
						player[i].CalSet();
						//DiceValueDraw();
						//TableValueDraw(player[i].GetChartValue());

					case 2: //주사위 킵
						//여쪽 코드는 내가 몰라요,,,우ㅠㅜ..
						/*
						커서가 스페이스를 눌렀을 때->얘가 몇 번째 주사위에서 누른 건지를
						입력받는 애가 반환해주면 좋아
						주사위 번호를 줄까 ?
						해당 다이스.Toggle()
						DiceKeepDraw(int 몇 번째 주사위)-- > 테두리에 뭔가 그려져서 Keep 상태인 걸 알아야 해
						DiceActivateDraw(int 몇 번째 주사위)-- > 테두리에 아무것도 없게 #기본 상태
						*/

					case 3: //표에 저장
						int getreturn = 0;
						player[i].PushValue(getreturn);
						player[i].SetSubTotal();
						player[i].SetBonus();
						player[i].SetTotalSum();

						x = 3; //for문 탈출
						break;
						// player[i].GetRoundResult();
						//draw
					}
				}
			}
		}
		winner = player[0].Winner(player[1]);
	}
}



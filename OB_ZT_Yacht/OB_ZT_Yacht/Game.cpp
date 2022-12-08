#include "essential.h"
#include "dice-classes.h"
#include "scene-classes.h"
#include "yatch_chart.h"


GameManage::GameManage()
{
	for (int i = 0; i < 5; i++) {
		Dice dice;
		dice_set.push_back(dice);
	}
	ChartFactory factory;
	Chart player1 = factory.GetChart();
	Chart player2 = factory.GetChart();
	vector<Chart>player(3);
	player[1]=player1;
	player[2]=player2;
	vector<int>dice = { 1,2,3,4,5 }; // 주사위 셋 임시값
	int winner;
	player[1].GetRoundResult();

	for (round = 1; round <= 12; round++) //12라운드 진행
	{
		for (turn = 1; turn <= 2; turn++) //플레이어가 번갈아 가면서 진행
		{
			//cout <<  "입니다 ";
			//TableValueDraw(player[j].GetRoundResult());
			for (roll = 1; roll <= 3; roll++) //한 플레이어가 3번까지 던질 수 있음
			{
				GameSceneInputManager game_scene_input_manager;
				while (1)
				{
					//임시값
					//cout << "test1\n";
					player[turn].SetDiceValue(dice);
					//cout << "test2\n";
					player[turn].SetDefaultValue();
					//cout << "test3\n";
					player[turn].CalSet();
					TableValueDraw(player[turn].GetChartValue());
					//cout << "test4\n";
					//TableValueDraw(player[i].GetRoundResult());
					int command = game_scene_input_manager.KeyMovingControlReturn();
					switch (command)
					{
					case 1: //주사위 굴림
						player[turn].SetDiceValue(dice);
						player[turn].SetDefaultValue();
						player[turn].CalSet();
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
						player[turn].PushValue(getreturn);
						player[turn].SetSubTotal();
						player[turn].SetBonus();
						player[turn].SetTotalSum();

						roll = 3; //for문 탈출
						break;
						// player[i].GetRoundResult();
						//draw
					}
				}
			}
		}
		winner = player[turn].Winner(player[turn]);
	}
}



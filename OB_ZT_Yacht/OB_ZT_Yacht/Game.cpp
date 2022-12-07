#include "yatch_chart.h"



GameManage::GameManage()
{
	int round, turn, roll;
	ChartFactory factory;
	vector<Chart>player;
	player[0] = factory.GetChart();
	player[1] = factory.GetChart();

	vector<int>dice; // 주사위 셋 임시값
	int winner;

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; i < 2; j++)
		{
			for (int x = 0; x < 3; x++)
			{
				//RoundTurnRollDraw()
				while (1)
				{
					int command = 0;
					switch (command)
					{
					case 1: //주사위 굴림
						player[i].SetDiceValue(dice);
						player[i].SetDefaultValue();
						player[i].CalSet();
						//DiceValueDraw();
						//TableValueDraw(player[i].GetChartValue());

					case 2:
						//여쪽 코드는 내가 몰라요,,,우ㅠㅜ..
						/*
						커서가 스페이스를 눌렀을 때->얘가 몇 번째 주사위에서 누른 건지를
						입력받는 애가 반환해주면 좋아
						주사위 번호를 줄까 ?
						해당 다이스.Toggle()
						DiceKeepDraw(int 몇 번째 주사위)-- > 테두리에 뭔가 그려져서 Keep 상태인 걸 알아야 해
						DiceActivateDraw(int 몇 번째 주사위)-- > 테두리에 아무것도 없게 #기본 상태
						*/

					case 3:
						int getreturn = 0;
						player[i].PushValue(getreturn);
						player[i].SetSubTotal();
						player[i].SetBonus();
						player[i].SetTotalSum();
						// player[i].GetRoundResult();
						//draw
					}
				}
			}
		}
		winner = player[0].Winner(player[1]);
	}
}

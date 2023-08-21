#include "stdafx.h"
#include "Ready_Ui.h"

Ready_Ui::Ready_Ui()
	: Goldcount(0), Levelcount(1)
{
	LBaseposition = Vector3(50, 50, 0);
	RBaseposition = Vector3(WinMaxWidth - 50, 50, 0);
	Buttonsize = Vector3(50, 50, 0);
	Buttonoffset = Buttonsize * 0.1;

	Level_UI_size = Vector3(50,50, 0);

	LevelUpCost = 0;
	Level_Max = 6;
	Gold_Max = 10;

// 버튼 생성 시퀸스
#pragma region Button
	{
		UpgradeButton = new Button(
		Vector3(0,0,0),
		Buttonsize,
		L"UI_ResetButton",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Upgrade_pattern.png"
		);
		UpgradeButton->SetRender();

		LockButton = new Button(
		Vector3(0, 0, 0),
		Buttonsize,
		L"UI_ResetButton",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Lock_pattern.png"
		);
		LockButton->SetRender();

		ReButton = new Button(
		Vector3(0, 0, 0),
		Buttonsize,
		L"UI_ResetButton",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Re_pattern.png"
		);
		ReButton->SetRender();

		ReadyButton = new Button(
		Vector3(0, 0, 0),
		Buttonsize,
		L"UI_ResetButton",
		L"Small_Button.png",
		L"Small_Button_press.png",
		L"Right_arrow_pattern.png"
		);
		ReadyButton->SetRender();
	}

	{
		Button_list.Get()->push_back(ReButton);
		Button_list.Get()->push_back(ReadyButton);
		Button_list.Get()->push_back(UpgradeButton);
		Button_list.Get()->push_back(LockButton);
	}
#pragma endregion

// 돈 생성 시퀸스
#pragma region GoldUI
	//for (int def = 0; def < Gold_Max; def++) {

	//	UI_Obejct* gold = new UI_Obejct(
	//	Vector3(0, 0, 0),
	//	Buttonsize, 0.0,
	//	L"Gold_UI" + def + 1,
	//	L"Gold_on_patten.png",
	//	L"Gold_off_patten.png");

	//	gold->SetRender();  // 금화는 생성시 렌더를 하지 않게 해야한다.
	//						// 레밸마다 금화가 올라야 하기 때문.
	//						// 사용시에만 off처리 해야한다.
	//	Gold.push_back(gold);
	//}

	//for (auto def : Gold) {
	//	Ready_UI_list.Get()->push_back(def);
	//}
#pragma endregion

// Level 생성 시퀸스
#pragma region Level
	//for(int def = 0; def < Level_Max; def++) {
	//		// Level은 어차피 미리 최대값을 표시하고 작업한다.
	//		// Level은 사용해서 없어지는 경우가 없기 때문.
	//	Level.push_back( 
	//	new UI_Obejct(
	//	Vector3(0,0,0),
	//	Buttonsize,0.0,
	//	L"Level_UI" + def+1, 
	//	L"Level_on_patten.png",
	//	L"Level_off_patten.png"));
	//}

	//for (auto def : Level) {
	//	Ready_UI_list.Get()->push_back(def);
	//}

#pragma endregion
}

void Ready_Ui::Update()
{
	ReButton->SetPosition		(GetCMPosition(LBaseposition, Buttonsize, Buttonoffset, 0.0, 2));
	ReadyButton->SetPosition	(GetCMPosition(LBaseposition, Buttonsize, Buttonoffset, 1.0, 2));
	UpgradeButton->SetPosition	(GetCMPosition(LBaseposition, Buttonsize, Buttonoffset, 0.0, 0));
	LockButton->SetPosition		(GetCMPosition(LBaseposition, Buttonsize, Buttonoffset, 0.5, 1));

	for (int i = 0; i < Gold.max_size() < i++;) {
		Gold[i]->SetPosition	(GetCMPosition(RBaseposition, Buttonsize, Buttonoffset, 0.0, i + 2));
	};

	for (int i = 0; i < Level.max_size() < i++;) {
		Gold[i]->SetPosition	(GetCMPosition(LBaseposition, Buttonsize, Buttonoffset, 0.0, i));
	};

}

Vector3 Ready_Ui::GetCMPosition(const Vector3 Basepositon, const Vector3 size, const Vector3 offset, const float x, const float y)
{
	Vector3 result;

	result = Basepositon + Camera::Get()->GetPosition() +
	Vector3(size.x * x, size.y * y, 0) +
	Vector3(offset.x * (x-1), offset.y * (y-1), 0);

	return result;
}

void Ready_Ui::LevelUP(const bool Press)
{
	if( Levelcount < Level_Max) {
		switch (Levelcount)
	{
		case 1:
		{
			LevelUpCost = 5;
			break;
		}

		case 2:
		{
			LevelUpCost = 6;
			break;
		}

		case 3:
		{
			LevelUpCost = 7;
			break;
		}

		case 4:
		{
			LevelUpCost = 8;
			break;
		}

		case 5:
		{
			LevelUpCost = 11;
			break;
		}

		case 6:
		{
			LevelUpCost = 0;
			break;
		}

		default:
			break;
	}
		Levelcount++;
	}

}

void Ready_Ui::GoldUP(const bool Press)
{
	
}
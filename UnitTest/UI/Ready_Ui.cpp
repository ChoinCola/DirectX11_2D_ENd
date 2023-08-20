#include "stdafx.h"
#include "Ready_Ui.h"

Ready_Ui::Ready_Ui()
	: moneycount(0), Levelcount(0)
{
	BaseButtonposition = Vector3(50, 50, 0);
	Buttonsize = Vector3(50, 50, 0);
	Buttonoffset = Buttonsize * 0.1;

	moneycount = 0;
	Levelcount = 0;

// ¹öÆ° »ý¼º ½ÃÄý½º
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

// µ· »ý¼º ½ÃÄý½º
#pragma region GoldUI
	
#pragma endregion

// Level »ý¼º ½ÃÄý½º
#pragma region Level

#pragma endregion
}

void Ready_Ui::Update()
{
	ReButton->SetPosition		(GetCMPosition(BaseButtonposition, Buttonsize, Buttonoffset, 0, 2));
	ReadyButton->SetPosition	(GetCMPosition(BaseButtonposition, Buttonsize, Buttonoffset, 1, 2));
	UpgradeButton->SetPosition	(GetCMPosition(BaseButtonposition, Buttonsize, Buttonoffset, 0, 0));
	LockButton->SetPosition		(GetCMPosition(BaseButtonposition, Buttonsize, Buttonoffset, 0.5, 1));

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
	
}

void Ready_Ui::GoldUP(const bool Press)
{
	
}
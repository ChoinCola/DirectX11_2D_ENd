#include "Framework.h"
#include "HPBar.h"

HPBar::HPBar(Vector3& position, Vector3 Size, float* HP, float* HPdefault)
	: IHPBar()
{
	this->Rendernow = true;
	this->HP = HP;
	this->HPdefault = HPdefault;
	this->Hostposition = &position;
	Vector3 Defaultpositon = {0,0,0};
	{
		HPBar_Black.push_back(new ProgressBar(Defaultpositon, Size,
			0.0f, D3DXCOLOR(0.09f, 0.07f, 0.14f, 1), UI::LEFT_TO_RIGHT));

		HPBar_Black.push_back(new ProgressBar(Defaultpositon, Size,
			0.0f, D3DXCOLOR(255, 0, 0, 1), UI::LEFT_TO_RIGHT));

		HPBar_Black.push_back(new ProgressBar({ HPBar_Black[1]->GetPosition().x +
												 HPBar_Black[1]->GetSize().x / 2,
												 HPBar_Black[1]->GetPosition().y, 0 },
			{ HPBar_Black[1]->GetSize().x, HPBar_Black[1]->GetSize().y + HPBar_Black[1]->GetSize().y / 2, 0 },
			0.0f, HPPath + L"HP_BAR_MIDDLE.png"));

		HPBar_Black.push_back(new ProgressBar({ HPBar_Black[2]->GetPosition().x -
												HPBar_Black[2]->GetSize().x / 2,
												HPBar_Black[2]->GetPosition().y, 0 }
		, { 4, HPBar_Black[2]->GetSize().y, 1 }, 0.0f, HPPath + L"HP_BAR_LEFT_PEAK.png"));

		HPBar_Black.push_back(new ProgressBar({ HPBar_Black[2]->GetPosition().x +
												HPBar_Black[2]->GetSize().x / 2,
												HPBar_Black[2]->GetPosition().y, 0 }
		, { 4, HPBar_Black[2]->GetSize().y, 1 }, 0.0f, HPPath + L"HP_BAR_LEFT_PEAK.png"));
	}
}
void HPBar::Update()
{
	if (!HPBar_Black.empty()) {
		HPBar_Black[1]->UpdateProgressBar(*HP / *HPdefault);
		for (auto def : HPBar_Black) {
			def->Update(*Hostposition + Vector3(-50, 80, 0));
		}
	}
}

void HPBar::Render()
{
	if(!HPBar_Black.empty() && Rendernow) {
		for (auto def : HPBar_Black)
			def->Render();
	}
}

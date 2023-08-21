#include "Framework.h"
#include "UI_Obejct.h"

UI_Obejct::UI_Obejct(Vector3 position, Vector3 size, float rotation, std::wstring Objectname, std::wstring ONfile, std::wstring OFFfile)
	: Objectname(Objectname), ONOFF(false), NowRender(true)
{
	// �⺻�� �����ִ� ���·� �����Ѵ�.
	// ������ �⺻���� ������ true
	ONObject = new TextureRect(position, size, rotation, LUI + L"UI_Obejct/" + ONfile);
	OFFObject = new TextureRect(position, size, rotation, LUI + L"UI_Obejct/" + OFFfile);

}

UI_Obejct::~UI_Obejct()
{
	SAFE_DELETE(ONObject);
	SAFE_DELETE(OFFObject);
}

void UI_Obejct::Update()
{
	ONObject->Update();
	OFFObject->Update();
}

void UI_Obejct::Render()
{
	if (NowRender == true)
	{
		if(ONOFF)
			ONObject->Render();
		else
			OFFObject->Render();
	}
}

void UI_Obejct::SetPosition(Vector3 position)
{
	ONObject->SetPosition(position);
	OFFObject->SetPosition(position);
}

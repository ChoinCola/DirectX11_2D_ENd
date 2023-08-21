#pragma once
class UI_Obejct
{
public:
	UI_Obejct(Vector3 position, Vector3 size, float rotation, std::wstring Objectname, std::wstring ONfile, std::wstring OFFfile);
	~UI_Obejct();
	void SetONOFF() { ONOFF ? ONOFF = false : ONOFF = true; };
	void SetRender() { NowRender ? NowRender = false : NowRender = true; };

	void Update();
	void Render();
	void SetPosition(Vector3 position);
private:
	std::wstring Objectname;
	bool NowRender;
	bool ONOFF;

	TextureRect* ONObject = nullptr;
	TextureRect* OFFObject = nullptr;
};


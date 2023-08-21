#pragma once
class UI_Obejct
{
public:
	UI_Obejct(Vector3 position, Vector3 size, float rotation, std::wstring Objectname, std::wstring ONfile, std::wstring OFFfile);
	~UI_Obejct();

	const bool GetONOFF() { return ONOFF; };
	void SetONOFF() { ONOFF ? ONOFF = false : ONOFF = true; };

	const bool GetRender() { return NowRender; };
	void SetRender() { NowRender ? NowRender = false : NowRender = true; };

	void Update();
	void Render();
	void SetPosition(Vector3 position);
	const std::wstring GetName() { return Objectname; };
	const Vector3 GetPosition() { return position; };
private:
	std::wstring Objectname;
	bool NowRender;
	bool ONOFF;

	TextureRect* ONObject = nullptr;
	TextureRect* OFFObject = nullptr;
	Vector3 position;
	Vector3 size;
};


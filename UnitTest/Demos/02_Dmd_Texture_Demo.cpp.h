#pragma once

class Dmd_Texture_Demo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	class Dmd* tr = nullptr;
	vector<class Dmd*> trs;
};
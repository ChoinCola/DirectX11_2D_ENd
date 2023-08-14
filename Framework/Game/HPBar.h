#pragma once

class IHPBar
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
protected:
	std::vector<ProgressBar*> HPBar_Black;
	Vector3* Hostposition;
	float* HP;
	float* HPdefault;
	bool Rendernow;
};

class HPBar : public IHPBar
{
public:
	HPBar(Vector3& position, Vector3 Size, float* HP, float* HPdefault);
	~HPBar() { for (auto def : HPBar_Black) SAFE_DELETE(def); };
	void Update() override;
	void Render() override;
	void SetRendernow() 
	{ Rendernow ? Rendernow = false : Rendernow = true; };
};

#pragma once

class Font
{
public:
	Font();
	~Font();
	
	void SetTextVector(Vector2 StartV, Vector2 EndV) 
	{ this->StartV = StartV; this->EndV = EndV; };
	void DrawString(LPCWSTR string, D3DXCOLOR Color, int X, int Y);
	void DrawString(LPCWSTR string, int X, int Y);
private:

	Vector2 StartV, EndV;

	ID3D10Device* d3dDevice = nullptr;
	ID3DX10Font* pFont = nullptr;
	ID3DX10Sprite* pSprite = nullptr;
};


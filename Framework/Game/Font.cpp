#include "Framework.h"
#include "Font.h"

Font::Font()
{
	HRESULT hResult;
	D3DX10_FONT_DESCW fontDesc;
	RtlZeroMemory(&fontDesc, sizeof(fontDesc));
	{
		fontDesc.Height = 48;
		fontDesc.Width = 0;
		fontDesc.Weight = FW_NORMAL;
		fontDesc.MipLevels = 0;
		fontDesc.Italic = FALSE;
		fontDesc.CharSet = DEFAULT_CHARSET;
		fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		fontDesc.Quality = CLEARTYPE_NATURAL_QUALITY;
		fontDesc.PitchAndFamily = 0;
		wcscpy_s(fontDesc.FaceName, TEXT("맑은 고딕"));

		hResult = D3DX10CreateFontIndirectW(d3dDevice, &fontDesc, &pFont);
		if (FAILED(hResult))
		{
			MessageBoxW(nullptr, L"Failed creating font", nullptr, 0);
			assert(false);
		}
		hResult = D3DX10CreateSprite(d3dDevice, sizeof(d3dDevice), &pSprite);
		if (FAILED(hResult))
		{
			MessageBoxW(nullptr, L"Failed createing sprite", nullptr, 0);
			assert(false);
		}
	}
	StartV = {0,0};
	EndV = {WinMaxWidth,WinMaxHeight};
}

Font::~Font()
{
	SAFE_DELETE(d3dDevice);
	SAFE_DELETE(pFont);
	SAFE_DELETE(pSprite);
}

void Font::DrawString(LPCWSTR string, D3DXCOLOR Color, int X, int Y)
{
	RECT rect;
	SetRectEmpty(&rect);
	rect.left = StartV.x;
	rect.right = EndV.x;
	rect.top = StartV.y;
	rect.bottom = EndV.y;

	pSprite->Begin(D3DX10_SPRITE_SAVE_STATE);
	// 텍스트 출력
	if (!pFont->DrawTextW(nullptr, string, -1, &rect, X | Y, Color))
	{
		MessageBoxW(nullptr, L"Failed calling DrawTextW", nullptr, 0);
	}
	pSprite->End();
}

void Font::DrawString(LPCWSTR string, int X, int Y)
{
	RECT rect;
	SetRectEmpty(&rect);
	rect.left = StartV.x;
	rect.right = EndV.x;
	rect.top = StartV.y;
	rect.bottom = EndV.y;

	pSprite->Begin(D3DX10_SPRITE_SAVE_STATE);
	// 텍스트 출력
	if (!pFont->DrawTextW(nullptr, string, -1, &rect, X | Y, { 1.f,1.f,1.f,1.f }))
	{
		MessageBoxW(nullptr, L"Failed calling DrawTextW", nullptr, 0);
	}
	pSprite->End();
}
// bmfont 설치해서 사용하기.
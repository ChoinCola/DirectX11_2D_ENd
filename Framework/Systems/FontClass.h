#pragma once
struct D3DXSTRING
{
	D3DXVECTOR3 Startposition;	// 문자 시작점 포지션, 문자는 좌하단이 기준.
	D3DXVECTOR3 Endposition;	// 문자 종료점 포지션
	Color color;				// 문자 색상
	Vector3 size;				// 문자 크기
	std::vector<TextureRect*>* string; // 문장 벡터
public:
	void Render() { for(auto def : *string) def->Render(); } // STRING값 출력
};

class FontClass : public SingletonBase<FontClass>
{
public:
	friend SingletonBase<FontClass>;

private:
	struct CharFont // 문자 기준 객체
	{
		int x;
		int y;
		int width;
		int height;
		int xoffset;
		int yoffset;
		int xadvance;
	};
private:
	FontClass();
	~FontClass();

public:
	void SetSize(Vector3 size) { this->StringSize = size; } // 문자 사이즈 변경.
	void Setoffset(float offset)  { this->StringOffset = offset; } // 위 아래 오프셋 변경
	bool SetFont(std::wstring pngFile, char* fntfile); // 폰트파일 재설정
	std::vector<Vector3>* SizeInit(int width, int height);
	std::vector<Vector2>* uvInit(float x, float y, float xoffset, float yoffset);
	D3DXSTRING* printString(const std::wstring string, const Vector3 position, const Color color);

private:
	std::wstring Fontfile;
	std::map<int, CharFont*> charators;
	
	Texture2D* m_Texture;

	Vector3 StringSize;
	int charCount;
	float StringOffset;
};
/*
	Font데이터를 각 맵핑값대로 긁어와서 렌더링해주는 Class
*/
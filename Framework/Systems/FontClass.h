#pragma once

enum STRINGPOSITION
{
	LEFT,
	RIGHT,
	MIDDLE,
};

struct D3DXSTRING
{
	D3DXVECTOR3 Startposition;			// 문자 시작점 포지션, 문자는 좌하단이 기준.
	D3DXVECTOR3 Endposition;			// 문자 종료점 포지션
	Color color;						// 문자 색상
	Vector3 size;						// 문자 크기
	std::vector<TextureRect*> string;	// 문장 벡터

public:
	void Update() { for (auto def : string) def->Update(); } // STRING 위치좌표 갱신
	void Render() { for (auto def : string) def->Render(); } // STRING 출력
};

class FontClass : public SingletonBase<FontClass>
{
public:
	friend SingletonBase<FontClass>;

private:
	struct CharFont // xml파일에서 긁어오는 데이터들.
	{
		float x;
		float y;
		float width;
		float height;
		float xoffset;
		float yoffset;
		float xadvance;
	};
private:
	FontClass();
	~FontClass();

public:
	void SetSize(Vector3 size) { this->StringSize = size; }							// 문자 사이즈 변경.
	void Setoffset(float offset)  { this->StringOffset = offset; }					// 위 아래 오프셋 변경
	bool SetFont(std::wstring pngFile, char* fntfile);								// 폰트파일 재설정

	std::vector<Vector3>* SizeInit(float width, float height);						// offset위치 잡아줌.
	std::vector<Vector2>* uvInit(float x, float y, float xoffset, float yoffset);	// uv좌표 잡아줌.
	D3DXSTRING MakeString															// 문장 제작함수
	(const std::wstring string, const Vector3 position,
	const Color color, const Vector3 stringsize, const int sorting = 0, const int outline = 0);

private:
							
	std::map<int, CharFont*> charators;												// xml파일 긁어온 데이터 저장 map
	
	Texture2D* Fontpng = nullptr;
	ID3D11ShaderResourceView* srv;
	Vector2 fontImagesize;
	Vector3 StringSize;
	int charCount;
	float StringOffset;
};
/*
	Font데이터를 각 맵핑값대로 긁어와서 렌더링해주는 Class
*/
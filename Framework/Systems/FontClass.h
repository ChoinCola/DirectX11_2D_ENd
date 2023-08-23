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

struct D3DXNUMBER
{
	D3DXVECTOR3 Startposition;					// 숫자판
	D3DXVECTOR3 Endposition;					// 숫자판 종료 포지션
	Color color;								// 숫자 색상
	Vector3 size;								// 숫자 크기
	int nvectorsize;							// 번호판 사이즈 ( 구조상 넘어가면 표시불가 )
	int sortType;								// 정렬기준이 좌측 중앙 우측인지
	int num;									// 들어있는 숫자
	std::vector<TextureRect*> numstring;		// 숫자 벡터
	std::map<wchar_t, TextureRect*>* numberpad;	// 넘버페드 벡터

public:
	void Update() { for (auto def : numstring) def->Update(); } // 숫자 위치좌표 갱신
	void Render() { for (auto def : numstring) def->Render(); } // 숫자 출력

	void Changer_Number(int num) {
		std::wstring numdef = std::to_wstring(num);
		for (uint i = 0; i < numstring.size(); i++)
		{
			while (true) {
				if (numstring.size() <= numdef.size()) { // 사이즈가 크거나 같으면 뒤로 빼버린다.
					Endposition.x -= (*numstring.end())->GetSize().x;	//Endposition을 계산해준다.
					numstring.pop_back();
				}
				break;
			}
			
			if(i >= numdef.size()) { // 사이즈 위치에 포지션 가져와서 박아줌.
				TextureRect* numberdef = new TextureRect(*numberpad->find(numdef[i])->second);
				numberdef->SetPosition(numstring[i]->GetPosition());
				numstring[i] = numberdef;
			}
			else {					// 포지션 빼줌.
				TextureRect* numberdef = new TextureRect(*numberpad->find(numdef[i])->second);
				numberdef->SetPosition(Endposition + Vector3(size.x,0,0));
				numstring.push_back(numberdef);
				Endposition += Vector3(size.x,0,0);
			}
		}
	}
private:
	template<typename T>
	D3DXNUMBER operator+ (T x) {
		num += x;
		Changer_Number(num);
	}

	template<typename T>
	D3DXNUMBER operator- (T x) {
		num -= x;
		Changer_Number(num);
	}

	template<typename T>
	D3DXNUMBER operator* (T x) {
		num *= x;
		Changer_Number(num);
	}

	template<typename T>
	D3DXNUMBER operator/ (T x) {
		num /= x;
		Changer_Number(num);
	}
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
	bool SetFont(char* fntfile);								// 폰트파일 재설정

	std::vector<Vector2>* uvInit(float x, float y, float xoffset, float yoffset);	// uv좌표 잡아줌.

	D3DXSTRING MakeString															// 문장 제작함수
	(const std::wstring string, const Vector3 position,
	const Color color, const Vector3 stringsize, const int sorting = 0, const int outline = 0);

	D3DXNUMBER Makenumberbord															// 숫자판 제작함수
	(const int number, const Vector3 position,
		const Color color, const Vector3 stringsize, const int sorting = 0, const int outline = 0);

private:
							
	std::map<int, CharFont*> charators;												// xml파일 긁어온 데이터 저장 map
	std::map<wchar_t, TextureRect*> numberpad;

	Texture2D* Fontpng = nullptr;
	ID3D11ShaderResourceView* srv;
	Vector2 fontImagesize;
	Vector3 StringSize;
	int charCount;
	int fontsinglesize;
	float StringOffset;
};
/*
	Font데이터를 각 맵핑값대로 긁어와서 렌더링해주는 Class
*/
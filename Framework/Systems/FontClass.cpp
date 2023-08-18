#include "Framework.h"
#include "FontClass.h"


FontClass::FontClass()
{
	// 기본 설정
	StringSize = Vector3{ 11.f,11.f,0 };	// 기본 문자 사이즈
	StringOffset = 2.f;						// 기본 문자 간격

	assert(SetFont(
		L"../Framework/GameAsset/Fontfile/Font2_0.png", // WSTRING으로 해야함,Texture2D이기 때문,
		"..\\Framework\\GameAsset\\Fontfile\\Font2.fnt")); // string으로 해야함, 라이브러리가 string으로 읽기때문,
}

FontClass::~FontClass()
{
}

bool FontClass::SetFont(std::wstring pngFile, char* fntfile)
{
	// 폰트 파일 제작 전 기입해야할 데이터배열 전부 초기화
	{
		SAFE_DELETE(Fontpng);
		charators.clear();
	}

	// 폰트 png파일 로드
	Fontpng = new Texture2D(pngFile);
	
	// xml파일 데이터 열기위한 변수
	tinyxml2::XMLDocument doc;

	//이미지 파일의 이름을 받아서 해당 이미지 로딩
	if (tinyxml2::XMLError eRsult = doc.LoadFile(fntfile))	//xml 로드 실패 검사
	{
		MessageBox(NULL, L"Can't find font file", L"Error", MB_OK);
		return false; // 실패시 터트림
	}
	else
	{
		// xml파일의 font 안의 chars로 접속한 결과를 pNode에 전달. ( 이 데이터는 각 문자의 기입데이터를 보관한다. )
		tinyxml2::XMLElement *pNode = doc.FirstChildElement("font")->FirstChildElement("chars");
		// xml파일의 font 안의 common로 접속한 결과를 Imagesize에 전달. ( 이 데이터는 이미지의 사이즈 를 보관한다. )
		tinyxml2::XMLElement *Imagesize = doc.FirstChildElement("font")->FirstChildElement("common");

		// 단 한개라도 긁어오지 못했을 경우, 코드실행이 불가하기에 터트린다.
		if (pNode == nullptr || Imagesize == nullptr) {
			std::cerr << "Error finding chars element." << std::endl;
			return false;
		}
		// png파일의 전체 사이즈를 받아온다. ( Texture2D데이터를 보관하는 Fontpng에서도 긁어올수 있음. 참고 )
		fontImagesize = { (float)Imagesize->IntAttribute("scaleW"), (float)Imagesize->IntAttribute("scaleH") };

		// 입력되어있는 모든 문자열을 검사하여 전부 map에 넣어준다.
		for (tinyxml2::XMLElement* element = pNode->FirstChildElement("char"); 
			element != nullptr; element = element->NextSiblingElement("char")) {
			CharFont* def = new CharFont();
			int id = element->IntAttribute("id");
			def->x = element->IntAttribute("x");
			def->y = element->IntAttribute("y");
			def->width = element->IntAttribute("width");
			def->height = element->IntAttribute("height");
			def->xoffset = element->IntAttribute("xoffset");
			def->yoffset = element->IntAttribute("yoffset");
			def->xadvance = element->IntAttribute("xadvance");
			charators.insert(std::make_pair(id, def));
		}
	}
	return true;
}

std::vector<Vector3>* FontClass::SizeInit(float width, float height)
{
	//maxx 18, maxy 18 가장큰 한글 폰트의 사이즈를 맥스 18로 잡고 나누어서 offset을 잡는다.
	std::vector<Vector3>* result = new std::vector<Vector3>;

	 //TextureRect에 들어가는 값을 Vector로 보관하여 던져줘야 한다.
	result->push_back(Vector3(+0.0f			, +0.0f			, 0));
	result->push_back(Vector3(+width / 18	, +height / 18	, 0));
	result->push_back(Vector3(+width / 18	, +0.0f			, 0));
	result->push_back(Vector3(+0.0f			, +height / 18	, 0));

	return result;
}

std::vector<Vector2>* FontClass::uvInit(float x, float y, float xoffset, float yoffset)
{
	// uv좌표를 잡아서, 전체 글자 png중 필요한 글자 한개의 uv좌표를 지정한다.
	std::vector<Vector2>* result = new std::vector<Vector2>();

	// TextureRect에 들어가는 값을 Vector로 보관하여 던져줘야 한다.
	result->push_back(Vector2(x				,	(y + yoffset)));	// 좌하단
	result->push_back(Vector2((x + xoffset),	y			 ));	// 우상단
	result->push_back(Vector2((x + xoffset),	(y + yoffset)));	// 우하단
	result->push_back(Vector2(x				,	y			 ));	// 좌상단

	return result;
}

D3DXSTRING FontClass::MakeString
(const std::wstring string, const Vector3 position, const Color color, const Vector3 stringsize, const int sorting, const int outline)
{
	D3DXSTRING* result = new D3DXSTRING;
	
	// 오류체크, 만약 Fontpng가 실행되지 않았을 경우,
	if (Fontpng == nullptr) { 
	// 폰트 를 다시 잡아준다.
	SetFont(L"../Framework/GameAsset/Fontfile/Font2_0.png", // WSTRING으로 해야함,Texture2D이기 때문,
			"..\\Framework\\GameAsset\\Fontfile\\Font2.fnt");
	}

	// 반환값에 문장의 전반 데이터를 기입.
	result->Startposition = result->Endposition = position;
	result->size = stringsize;
	result->color = color;

	for (auto def : string) {
		if (def != NULL) {

			// 스페이스바 입력시 띄어쓰기
			if ((int)def == 0) {
				result->Endposition.x += result->size.x;
				continue;
			}

			// 개행문자. 엔터입력시 밑으로
			if (def == '\n') {
				result->Endposition.y -= result->size.y * 1.8;
				result->Endposition.x = result->Startposition.x;
				continue;
			}

			// map배열에서 해당되는 문자의 ASCII 코드를 찾아온다. 
			auto value = charators.find((int)def);

			// offset을 잡을 위치값.
			std::vector<Vector3>* terticespos;
			terticespos = SizeInit(value->second->width, value->second->height);

			// uv의 기준값. 문자의 x위치에 전체 이미지를 나눠주어 전체이미지가 1일경우 x의 값을 구한다. 가로세로길이, y도 같은 방식으로 도출
			std::vector<Vector2>* uv = 
			uvInit(value->second->x / fontImagesize.x, value->second->y / fontImagesize.y,
					value->second->width / fontImagesize.x, value->second->height / fontImagesize.y);

			// 한글과 영어의 Offset위치가 다르기 떄문에 한글일경우, 추가 offset을 준다.
			Vector3 Offset;
			if(value->first >= 40000)
				Offset = Vector3(0,value->second->yoffset,0);
			else
				Offset = Vector3(0, 0, 0);

			// 나온결과값을 문장 에 기입한다.
			result->string.push_back(
				new TextureRect(result->Endposition + Offset, 
				terticespos, uv, result->size, 0.0f,result->color, Fontpng, outline));

			result->Endposition.x += value->second->width / 18 * result->size.x + StringOffset;
		}
	}

	
	switch (sorting)
	{
		case RIGHT : // 이 문장은 시작위치 기준 왼쪽으로 발산합니다.
		{
			float sortvectorsizex = (result->Endposition.x - result->Startposition.x); // 전체 문장 길이
			Vector3 sortvector = { sortvectorsizex, 0, 0 };
			for (auto def : result->string) {
				if (def->GetPosition().y < result->Startposition.y) // 엔터가 입력되었을 경우,
					sortvector.x = sortvectorsizex; // x를 문장길이 기본 으로 초기화

				Vector3 charX = Vector3(def->GetRect().x / 4 - StringOffset, 0, 0);

				def->SetPosition(def->GetPosition() - sortvector); // 현재 위치의 단어 길이만큼을 쭉 밀어버림.
				sortvector -= charX;
				// 다음에 왼쪽으로 미는 값은 방금 민 글자의 x사이즈 만큼 줄어들어야 한다.
			}
			break;
		}
		case MIDDLE : 	// 이 문장은 시작위치 가 문장의 중앙입니다.
		{
			float sortvectorsizex = (result->Endposition.x - result->Startposition.x) / 2; // 전체 문장 길이의 반
			Vector3 sortvector = { sortvectorsizex, 0, 0 };
			for (auto def : result->string) {
				if (def->GetPosition().y < result->Startposition.y) // 엔터가 입력되었을 경우,
					sortvector.x = sortvectorsizex; // x를 문장길이의 기본의 반절 로 초기화

				Vector3 charX = Vector3(def->GetRect().x / 4 - StringOffset, 0, 0);
			
				def->SetPosition(def->GetPosition() - sortvector); // 현재 위치의 단어 길이만큼을 쭉 밀어버림.
				sortvector -= charX;
				 // 다음에 왼쪽으로 미는 값은 방금 민 글자의 x사이즈 만큼 줄어들어야 한다.
			}
			break;
		}
		default: // 이 문장은 시작위치 기준 오른쪽으로 발산합니다.
			break;
	}
	return *result;
}

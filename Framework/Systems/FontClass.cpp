#include "Framework.h"
#include "FontClass.h"


FontClass::FontClass()
{
	// 기본 설정
	StringSize = Vector3{ 11.f,11.f,0 };	// 기본 문자 사이즈
	StringOffset = 0.5;						// 기본 문자 간격

	assert(SetFont("..\\Framework\\GameAsset\\Fontfile\\Base_Font.fnt")); // string으로 해야함, 라이브러리가 string으로 읽기때문,
}

FontClass::~FontClass()
{
}

bool FontClass::SetFont(char* fntfile)
{
	// 폰트 파일 제작 전 기입해야할 데이터배열 전부 초기화
	{
		SAFE_DELETE(Fontpng);
		charators.clear();
	}

	// 폰트 png파일 로드

	
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

		// xml파일의 font 안의 file로 접속한 결과를 Imagename에 전달. ( 이 데이터는 이미지의 사이즈 를 보관한다. )
		tinyxml2::XMLElement* pname = doc.FirstChildElement("font")->FirstChildElement("pages")->FirstChildElement("page");
		const char* def = pname->Attribute("file");
		std::wstring Imagename(strlen(def), L' ');
		std::mbstowcs(&Imagename[0], def, strlen(def));			// 이미지 이름이 char[]형식 이기에 형변환 한다.

		Fontpng = new Texture2D(LFont + Imagename);
		// 단 한개라도 긁어오지 못했을 경우, 코드실행이 불가하기에 터트린다.

		if (pNode == nullptr || Imagesize == nullptr || Fontpng == nullptr) {
			std::cerr << "Error finding chars element." << std::endl;
			return false;
		}
		// png파일의 전체 사이즈를 받아온다. ( Texture2D데이터를 보관하는 Fontpng에서도 긁어올수 있음. 참고 )
		fontImagesize = { (float)Imagesize->IntAttribute("scaleW"), (float)Imagesize->IntAttribute("scaleH") };
		fontsinglesize = Imagesize->IntAttribute("lineHeight");
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
	
	// 오류체크, 만약 Fontpng가 실행되지 않았을 경우, 폰트 를 다시 잡아준다.
	if (Fontpng == nullptr)
		SetFont("..\\Framework\\GameAsset\\Fontfile\\Base_Font.fnt");

	// 반환값에 문장의 전반 데이터를 기입.
	result->Startposition = result->Endposition = position;
	result->size = stringsize;
	result->color = color;

	for (int i = 0; i < string.size(); i++) {
		auto def = string[i];
		if (def != NULL) {

			// 스페이스바 입력시 띄어쓰기
			if ((int)def == 0) {
				result->Endposition.x += result->size.x;
				continue;
			}

			// 개행문자. 엔터입력시 밑으로
			if (def == '\n') {
				result->Endposition.y -= result->size.y ;
				result->Endposition.x = result->Startposition.x;
				continue;
			}
			
			// map배열에서 해당되는 문자의 ASCII 코드를 찾아온다. 
			auto value = charators.find((int)def);

			// uv의 기준값. 문자의 x위치에 전체 이미지를 나눠주어 전체이미지가 1일경우 x의 값을 구한다. 가로세로길이, y도 같은 방식으로 도출
			std::vector<Vector2>* uv = 
			uvInit(value->second->x / fontImagesize.x, value->second->y / fontImagesize.y,
					value->second->width / fontImagesize.x, value->second->height / fontImagesize.y);

			// 문자 사이즈를 백분율하여, 일정한 사이즈로 키워줄 수 있게 한다.
			float Charsizex = value->second->width*2 / fontsinglesize;
			Vector3 Offset;
			// y를 음수처리하는 이유는 uv 좌표상, y가 반대이기 때문, BMFont 프로그램이 구형이라 offset 좌표가 0,0이 좌상단임.
			Offset = Vector3(value->second->xoffset / 2, -value->second->yoffset / 2, 0);

			Vector3 fontsize = Vector3(value->second->width / fontsinglesize * result->size.x, 
			value->second->height / fontsinglesize * result->size.y, 0);

			// 나온결과값을 문장 에 기입한다.
			// 한글과 영어의 Offset위치가 다르기 떄문에 추가 offset을 다르게 준다.
				// 데이터 기입부
				// 
			// 문자가 한글이고 바로 전 문자가 영문일경우, 한글 문자를 더 뒤로 띄워야한다.

			result->string.push_back(
				new TextureRect(result->Endposition + Offset, uv, fontsize, 0.0f, result->color, Fontpng));
			// 다음문자가 입력되기 위해서 사이즈만큼 우측으로 이동.

			// 문자가 영어 -> 한글로 넘어갈때 offset문제가 발생. 그래서 그부분만 처리함. 한글의 가장 작은 유니코드 = 4352
			if (string[i + 1] != NULL && string[i + 1] >= 4352 && string[i] < 4352)
				result->Endposition.x += fontsize.x * 3.0 - Offset.x / fontsinglesize * result->size.x;
			else
				result->Endposition.x += fontsize.x * 1.5 - Offset.x / fontsinglesize * result->size.x; 
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

				Vector3 charX = Vector3(def->GetRect().x / 3.8, 0, 0);

				def->SetPosition(def->GetPosition() - sortvector); // 현재 위치의 단어 길이만큼을 쭉 밀어버림.
				sortvector -= charX;
				// 다음에 왼쪽으로 미는 값은 방금 민 글자의 x사이즈 만큼 줄어들어야 한다.
			}
			break;
		}
		case MIDDLE : 	// 이 문장은 시작위치 가 문장의 중앙입니다.
		{
			float sortvectorsizex = ( result->Endposition.x - result->Startposition.x ) / 2; // 전체 문장 길이의 반
			Vector3 sortvector = { sortvectorsizex, 0, 0 };
			for (auto def : result->string) {
				if (def->GetPosition().y < result->Startposition.y) // 엔터가 입력되었을 경우,
					sortvector.x = sortvectorsizex; // x를 문장길이의 기본의 반절 로 초기화

				Vector3 charX = Vector3(def->GetRect().x / 3.8, 0, 0);
			
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

D3DXNUMBER FontClass::Makenumberbord(const int number, const Vector3 position, const Color color, const Vector3 stringsize, const int sorting, const int outline)
{
	D3DXNUMBER* result = new D3DXNUMBER;
	std::wstring wsnumber = std::to_wstring(number);

	// 오류체크, 만약 Fontpng가 실행되지 않았을 경우, 폰트 를 다시 잡아준다.
	if (Fontpng == nullptr)
		SetFont("..\\Framework\\GameAsset\\Fontfile\\Base_Font.fnt");

	// 반환값에 문장의 전반 데이터를 기입.
	result->Startposition = result->Endposition = position;
	result->size = stringsize;
	result->color = color;

	// 넘버패드를 안말들었을 경우, 만듬
	if(numberpad.empty()) {
		for (int i = 0; i <10; i++) {
			std::wstring def = std::to_wstring(i);
				// map배열에서 해당되는 숫자의 유니 코드를 찾아온다. 
			auto value = charators.find((int)def[0]);

			// uv의 기준값. 문자의 x위치에 전체 이미지를 나눠주어 전체이미지가 1일경우 x의 값을 구한다. 가로세로길이, y도 같은 방식으로 도출
			std::vector<Vector2>* uv =
				uvInit(value->second->x / fontImagesize.x, value->second->y / fontImagesize.y,
					value->second->width / fontImagesize.x, value->second->height / fontImagesize.y);

			// 문자 사이즈를 백분율하여, 일정한 사이즈로 키워줄 수 있게 한다.
			float Charsizex = value->second->width * 2 / fontsinglesize;
			Vector3 Offset;
			// y를 음수처리하는 이유는 uv 좌표상, y가 반대이기 때문, BMFont 프로그램이 구형이라 offset 좌표가 0,0이 좌상단임.
			Offset = Vector3(value->second->xoffset / 2, -value->second->yoffset / 2, 0);

			Vector3 fontsize = Vector3(value->second->width / fontsinglesize * result->size.x,
				value->second->height / fontsinglesize * result->size.y, 0);
			TextureRect* numpaddef = new TextureRect(Offset, uv, fontsize, 0.0f, result->color, Fontpng);

			numberpad.insert(std::make_pair(def[0], numpaddef));
			// 넘버페드에 숫자를 입력함.
		}

		std::wstring def = L"-";
		// map배열에서 해당되는 숫자의 유니 코드를 찾아온다. 
		auto value = charators.find((int)def[0]);

		// uv의 기준값. 문자의 x위치에 전체 이미지를 나눠주어 전체이미지가 1일경우 x의 값을 구한다. 가로세로길이, y도 같은 방식으로 도출
		std::vector<Vector2>* uv =
			uvInit(value->second->x / fontImagesize.x, value->second->y / fontImagesize.y,
				value->second->width / fontImagesize.x, value->second->height / fontImagesize.y);

		// 문자 사이즈를 백분율하여, 일정한 사이즈로 키워줄 수 있게 한다.
		float Charsizex = value->second->width * 2 / fontsinglesize;
		Vector3 Offset;
		// y를 음수처리하는 이유는 uv 좌표상, y가 반대이기 때문, BMFont 프로그램이 구형이라 offset 좌표가 0,0이 좌상단임.
		Offset = Vector3(value->second->xoffset / 2, -value->second->yoffset / 2, 0);

		Vector3 fontsize = Vector3(value->second->width / fontsinglesize * result->size.x,
			value->second->height / fontsinglesize * result->size.y, 0);
		TextureRect* numpaddef = new TextureRect(Offset, uv, fontsize, 0.0f, result->color, Fontpng);

		numberpad.insert(std::make_pair(def[0], numpaddef));
		// 넘버페드에 -를 입력함.
	}

	// 입력받은 숫자를 확인함.
	for (int i = 0; i < wsnumber.size(); i++)
	{
		TextureRect* numberdef = new TextureRect(*numberpad.find(wsnumber[i])->second);
		numberdef->SetPosition(numberdef->GetPosition() + result->Endposition);
		numberdef->Update();

		Vector3 Offset;
		// y를 음수처리하는 이유는 uv 좌표상, y가 반대이기 때문, BMFont 프로그램이 구형이라 offset 좌표가 0,0이 좌상단임.

		result->numstring.push_back(numberdef);
		result->Endposition.x += result->size.x;
	}

	switch (sorting)
	{
	case RIGHT: // 이 문장은 시작위치 기준 왼쪽으로 발산합니다.
	{
		float sortvectorsizex = (result->Endposition.x - result->Startposition.x); // 전체 문장 길이
		Vector3 sortvector = { sortvectorsizex, 0, 0 };
		for (auto def : result->numstring) {
			if (def->GetPosition().y < result->Startposition.y) // 엔터가 입력되었을 경우,
				sortvector.x = sortvectorsizex; // x를 문장길이 기본 으로 초기화

			Vector3 charX = Vector3(def->GetRect().x / 3.8, 0, 0);

			def->SetPosition(def->GetPosition() - sortvector); // 현재 위치의 단어 길이만큼을 쭉 밀어버림.
			sortvector -= charX;
			// 다음에 왼쪽으로 미는 값은 방금 민 글자의 x사이즈 만큼 줄어들어야 한다.
		}
		break;
	}
	case MIDDLE: 	// 이 문장은 시작위치 가 문장의 중앙입니다.
	{
		float sortvectorsizex = (result->Endposition.x - result->Startposition.x) / 2; // 전체 문장 길이의 반
		Vector3 sortvector = { sortvectorsizex, 0, 0 };
		for (auto def : result->numstring) {
			if (def->GetPosition().y < result->Startposition.y) // 엔터가 입력되었을 경우,
				sortvector.x = sortvectorsizex; // x를 문장길이의 기본의 반절 로 초기화

			Vector3 charX = Vector3(def->GetRect().x / 3.8, 0, 0);

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

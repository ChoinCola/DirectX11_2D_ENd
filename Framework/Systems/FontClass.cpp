#include "Framework.h"
#include "FontClass.h"

FontClass::FontClass()
{
}

FontClass::~FontClass()
{
	for(auto def : charactors)
		SAFE_DELETE(def.second);
}

void FontClass::Render()
{
}

void FontClass::SetFontfile(std::wstring File)
{
	TiXmlNode* pNode;
	//이미지 파일의 이름을 받아서 해당 이미지 로딩
	pNode = fontXml.FirstChild("font")->FirstChild("pages")->FirstChild("page");
	const char* fontImage = pNode->ToElement()->Attribute("file");

	//글자 갯수 받아옴
	pNode = fontXml.FirstChild("font")->FirstChild("chars");
	pNode->ToElement()->Attribute("count", &charCount);
	charators = new CharFont[charCount];
	pNode = pNode->FirstChild("char");

	int cnt = 0;
	//아스키코드 32번부터 126번까지 받아옴
	while (pNode != NULL)
	{
		pNode->ToElement()->Attribute("id", &charators[cnt].id);
		pNode->ToElement()->Attribute("x", &charators[cnt].x);
		pNode->ToElement()->Attribute("y", &charators[cnt].y);
		pNode->ToElement()->Attribute("width", &charators[cnt].width);
		pNode->ToElement()->Attribute("height", &charators[cnt].height);
		pNode->ToElement()->Attribute("xoffset", &charators[cnt].xoffset);
		pNode->ToElement()->Attribute("yoffset", &charators[cnt].yoffset);
		pNode->ToElement()->Attribute("xadvance", &charators[cnt].xadvance);
		//테스트
		printf("%d - %d - %d - %d - %d - %d - %d - %d - %d \n", charCount, charators[cnt].id, charators[cnt].x, charators[cnt].y, charators[cnt].width, charators[cnt].height, charators[cnt].xoffset, charators[cnt].yoffset, charators[cnt].xadvance);

		pNode = pNode->NextSibling();
		cnt++;
	}
	fontXml.Clear();
}

bool FontClass::SetString()
{
	return false;
}

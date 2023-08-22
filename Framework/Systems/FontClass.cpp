#include "Framework.h"
#include "FontClass.h"


FontClass::FontClass()
{
	// �⺻ ����
	StringSize = Vector3{ 11.f,11.f,0 };	// �⺻ ���� ������
	StringOffset = 0.5;						// �⺻ ���� ����

	assert(SetFont("..\\Framework\\GameAsset\\Fontfile\\Base_Font.fnt")); // string���� �ؾ���, ���̺귯���� string���� �б⶧��,
}

FontClass::~FontClass()
{
}

bool FontClass::SetFont(char* fntfile)
{
	// ��Ʈ ���� ���� �� �����ؾ��� �����͹迭 ���� �ʱ�ȭ
	{
		SAFE_DELETE(Fontpng);
		charators.clear();
	}

	// ��Ʈ png���� �ε�

	
	// xml���� ������ �������� ����
	tinyxml2::XMLDocument doc;

	//�̹��� ������ �̸��� �޾Ƽ� �ش� �̹��� �ε�
	if (tinyxml2::XMLError eRsult = doc.LoadFile(fntfile))	//xml �ε� ���� �˻�
	{
		MessageBox(NULL, L"Can't find font file", L"Error", MB_OK);
		return false; // ���н� ��Ʈ��
	}
	else
	{
		// xml������ font ���� chars�� ������ ����� pNode�� ����. ( �� �����ʹ� �� ������ ���Ե����͸� �����Ѵ�. )
		tinyxml2::XMLElement *pNode = doc.FirstChildElement("font")->FirstChildElement("chars");

		// xml������ font ���� common�� ������ ����� Imagesize�� ����. ( �� �����ʹ� �̹����� ������ �� �����Ѵ�. )
		tinyxml2::XMLElement *Imagesize = doc.FirstChildElement("font")->FirstChildElement("common");

		// xml������ font ���� file�� ������ ����� Imagename�� ����. ( �� �����ʹ� �̹����� ������ �� �����Ѵ�. )
		tinyxml2::XMLElement* pname = doc.FirstChildElement("font")->FirstChildElement("pages")->FirstChildElement("page");
		const char* def = pname->Attribute("file");
		std::wstring Imagename(strlen(def), L' ');
		std::mbstowcs(&Imagename[0], def, strlen(def));			// �̹��� �̸��� char[]���� �̱⿡ ����ȯ �Ѵ�.

		Fontpng = new Texture2D(LFont + Imagename);
		// �� �Ѱ��� �ܾ���� ������ ���, �ڵ������ �Ұ��ϱ⿡ ��Ʈ����.

		if (pNode == nullptr || Imagesize == nullptr || Fontpng == nullptr) {
			std::cerr << "Error finding chars element." << std::endl;
			return false;
		}
		// png������ ��ü ����� �޾ƿ´�. ( Texture2D�����͸� �����ϴ� Fontpng������ �ܾ�ü� ����. ���� )
		fontImagesize = { (float)Imagesize->IntAttribute("scaleW"), (float)Imagesize->IntAttribute("scaleH") };
		fontsinglesize = Imagesize->IntAttribute("lineHeight");
		// �ԷµǾ��ִ� ��� ���ڿ��� �˻��Ͽ� ���� map�� �־��ش�.
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
	// uv��ǥ�� ��Ƽ�, ��ü ���� png�� �ʿ��� ���� �Ѱ��� uv��ǥ�� �����Ѵ�.
	std::vector<Vector2>* result = new std::vector<Vector2>();

	// TextureRect�� ���� ���� Vector�� �����Ͽ� ������� �Ѵ�.
	result->push_back(Vector2(x				,	(y + yoffset)));	// ���ϴ�
	result->push_back(Vector2((x + xoffset),	y			 ));	// ����
	result->push_back(Vector2((x + xoffset),	(y + yoffset)));	// ���ϴ�
	result->push_back(Vector2(x				,	y			 ));	// �»��

	return result;
}

D3DXSTRING FontClass::MakeString
(const std::wstring string, const Vector3 position, const Color color, const Vector3 stringsize, const int sorting, const int outline)
{
	D3DXSTRING* result = new D3DXSTRING;
	
	// ����üũ, ���� Fontpng�� ������� �ʾ��� ���, ��Ʈ �� �ٽ� ����ش�.
	if (Fontpng == nullptr)
		SetFont("..\\Framework\\GameAsset\\Fontfile\\Base_Font.fnt");

	// ��ȯ���� ������ ���� �����͸� ����.
	result->Startposition = result->Endposition = position;
	result->size = stringsize;
	result->color = color;

	for (int i = 0; i < string.size(); i++) {
		auto def = string[i];
		if (def != NULL) {

			// �����̽��� �Է½� ����
			if ((int)def == 0) {
				result->Endposition.x += result->size.x;
				continue;
			}

			// ���๮��. �����Է½� ������
			if (def == '\n') {
				result->Endposition.y -= result->size.y ;
				result->Endposition.x = result->Startposition.x;
				continue;
			}
			
			// map�迭���� �ش�Ǵ� ������ ASCII �ڵ带 ã�ƿ´�. 
			auto value = charators.find((int)def);

			// uv�� ���ذ�. ������ x��ġ�� ��ü �̹����� �����־� ��ü�̹����� 1�ϰ�� x�� ���� ���Ѵ�. ���μ��α���, y�� ���� ������� ����
			std::vector<Vector2>* uv = 
			uvInit(value->second->x / fontImagesize.x, value->second->y / fontImagesize.y,
					value->second->width / fontImagesize.x, value->second->height / fontImagesize.y);

			// ���� ����� ������Ͽ�, ������ ������� Ű���� �� �ְ� �Ѵ�.
			float Charsizex = value->second->width*2 / fontsinglesize;
			Vector3 Offset;
			// y�� ����ó���ϴ� ������ uv ��ǥ��, y�� �ݴ��̱� ����, BMFont ���α׷��� �����̶� offset ��ǥ�� 0,0�� �»����.
			Offset = Vector3(value->second->xoffset / 2, -value->second->yoffset / 2, 0);

			Vector3 fontsize = Vector3(value->second->width / fontsinglesize * result->size.x, 
			value->second->height / fontsinglesize * result->size.y, 0);

			// ���°������ ���� �� �����Ѵ�.
			// �ѱ۰� ������ Offset��ġ�� �ٸ��� ������ �߰� offset�� �ٸ��� �ش�.
				// ������ ���Ժ�
				// 
			// ���ڰ� �ѱ��̰� �ٷ� �� ���ڰ� �����ϰ��, �ѱ� ���ڸ� �� �ڷ� ������Ѵ�.

			result->string.push_back(
				new TextureRect(result->Endposition + Offset, uv, fontsize, 0.0f, result->color, Fontpng));
			// �������ڰ� �ԷµǱ� ���ؼ� �����ŭ �������� �̵�.

			// ���ڰ� ���� -> �ѱ۷� �Ѿ�� offset������ �߻�. �׷��� �׺κи� ó����. �ѱ��� ���� ���� �����ڵ� = 4352
			if (string[i + 1] != NULL && string[i + 1] >= 4352 && string[i] < 4352)
				result->Endposition.x += fontsize.x * 3.0 - Offset.x / fontsinglesize * result->size.x;
			else
				result->Endposition.x += fontsize.x * 1.5 - Offset.x / fontsinglesize * result->size.x; 
		}
	}

	switch (sorting)
	{
		case RIGHT : // �� ������ ������ġ ���� �������� �߻��մϴ�.
		{
			float sortvectorsizex = (result->Endposition.x - result->Startposition.x); // ��ü ���� ����
			Vector3 sortvector = { sortvectorsizex, 0, 0 };
			for (auto def : result->string) {
				if (def->GetPosition().y < result->Startposition.y) // ���Ͱ� �ԷµǾ��� ���,
					sortvector.x = sortvectorsizex; // x�� ������� �⺻ ���� �ʱ�ȭ

				Vector3 charX = Vector3(def->GetRect().x / 3.8, 0, 0);

				def->SetPosition(def->GetPosition() - sortvector); // ���� ��ġ�� �ܾ� ���̸�ŭ�� �� �о����.
				sortvector -= charX;
				// ������ �������� �̴� ���� ��� �� ������ x������ ��ŭ �پ���� �Ѵ�.
			}
			break;
		}
		case MIDDLE : 	// �� ������ ������ġ �� ������ �߾��Դϴ�.
		{
			float sortvectorsizex = ( result->Endposition.x - result->Startposition.x ) / 2; // ��ü ���� ������ ��
			Vector3 sortvector = { sortvectorsizex, 0, 0 };
			for (auto def : result->string) {
				if (def->GetPosition().y < result->Startposition.y) // ���Ͱ� �ԷµǾ��� ���,
					sortvector.x = sortvectorsizex; // x�� ��������� �⺻�� ���� �� �ʱ�ȭ

				Vector3 charX = Vector3(def->GetRect().x / 3.8, 0, 0);
			
				def->SetPosition(def->GetPosition() - sortvector); // ���� ��ġ�� �ܾ� ���̸�ŭ�� �� �о����.
				sortvector -= charX;
				 // ������ �������� �̴� ���� ��� �� ������ x������ ��ŭ �پ���� �Ѵ�.
			}
			break;
		}
		default: // �� ������ ������ġ ���� ���������� �߻��մϴ�.
			break;
	}
	return *result;
}

D3DXNUMBER FontClass::Makenumberbord(const int number, const Vector3 position, const Color color, const Vector3 stringsize, const int sorting, const int outline)
{
	D3DXNUMBER* result = new D3DXNUMBER;
	std::wstring wsnumber = std::to_wstring(number);

	// ����üũ, ���� Fontpng�� ������� �ʾ��� ���, ��Ʈ �� �ٽ� ����ش�.
	if (Fontpng == nullptr)
		SetFont("..\\Framework\\GameAsset\\Fontfile\\Base_Font.fnt");

	// ��ȯ���� ������ ���� �����͸� ����.
	result->Startposition = result->Endposition = position;
	result->size = stringsize;
	result->color = color;

	// �ѹ��е带 �ȸ������ ���, ����
	if(numberpad.empty()) {
		for (int i = 0; i <10; i++) {
			std::wstring def = std::to_wstring(i);
				// map�迭���� �ش�Ǵ� ������ ���� �ڵ带 ã�ƿ´�. 
			auto value = charators.find((int)def[0]);

			// uv�� ���ذ�. ������ x��ġ�� ��ü �̹����� �����־� ��ü�̹����� 1�ϰ�� x�� ���� ���Ѵ�. ���μ��α���, y�� ���� ������� ����
			std::vector<Vector2>* uv =
				uvInit(value->second->x / fontImagesize.x, value->second->y / fontImagesize.y,
					value->second->width / fontImagesize.x, value->second->height / fontImagesize.y);

			// ���� ����� ������Ͽ�, ������ ������� Ű���� �� �ְ� �Ѵ�.
			float Charsizex = value->second->width * 2 / fontsinglesize;
			Vector3 Offset;
			// y�� ����ó���ϴ� ������ uv ��ǥ��, y�� �ݴ��̱� ����, BMFont ���α׷��� �����̶� offset ��ǥ�� 0,0�� �»����.
			Offset = Vector3(value->second->xoffset / 2, -value->second->yoffset / 2, 0);

			Vector3 fontsize = Vector3(value->second->width / fontsinglesize * result->size.x,
				value->second->height / fontsinglesize * result->size.y, 0);
			TextureRect* numpaddef = new TextureRect(Offset, uv, fontsize, 0.0f, result->color, Fontpng);

			numberpad.insert(std::make_pair(def[0], numpaddef));
			// �ѹ���忡 ���ڸ� �Է���.
		}

		std::wstring def = L"-";
		// map�迭���� �ش�Ǵ� ������ ���� �ڵ带 ã�ƿ´�. 
		auto value = charators.find((int)def[0]);

		// uv�� ���ذ�. ������ x��ġ�� ��ü �̹����� �����־� ��ü�̹����� 1�ϰ�� x�� ���� ���Ѵ�. ���μ��α���, y�� ���� ������� ����
		std::vector<Vector2>* uv =
			uvInit(value->second->x / fontImagesize.x, value->second->y / fontImagesize.y,
				value->second->width / fontImagesize.x, value->second->height / fontImagesize.y);

		// ���� ����� ������Ͽ�, ������ ������� Ű���� �� �ְ� �Ѵ�.
		float Charsizex = value->second->width * 2 / fontsinglesize;
		Vector3 Offset;
		// y�� ����ó���ϴ� ������ uv ��ǥ��, y�� �ݴ��̱� ����, BMFont ���α׷��� �����̶� offset ��ǥ�� 0,0�� �»����.
		Offset = Vector3(value->second->xoffset / 2, -value->second->yoffset / 2, 0);

		Vector3 fontsize = Vector3(value->second->width / fontsinglesize * result->size.x,
			value->second->height / fontsinglesize * result->size.y, 0);
		TextureRect* numpaddef = new TextureRect(Offset, uv, fontsize, 0.0f, result->color, Fontpng);

		numberpad.insert(std::make_pair(def[0], numpaddef));
		// �ѹ���忡 -�� �Է���.
	}

	// �Է¹��� ���ڸ� Ȯ����.
	for (int i = 0; i < wsnumber.size(); i++)
	{
		TextureRect* numberdef = new TextureRect(*numberpad.find(wsnumber[i])->second);
		numberdef->SetPosition(numberdef->GetPosition() + result->Endposition);
		numberdef->Update();

		Vector3 Offset;
		// y�� ����ó���ϴ� ������ uv ��ǥ��, y�� �ݴ��̱� ����, BMFont ���α׷��� �����̶� offset ��ǥ�� 0,0�� �»����.

		result->numstring.push_back(numberdef);
		result->Endposition.x += result->size.x;
	}

	switch (sorting)
	{
	case RIGHT: // �� ������ ������ġ ���� �������� �߻��մϴ�.
	{
		float sortvectorsizex = (result->Endposition.x - result->Startposition.x); // ��ü ���� ����
		Vector3 sortvector = { sortvectorsizex, 0, 0 };
		for (auto def : result->numstring) {
			if (def->GetPosition().y < result->Startposition.y) // ���Ͱ� �ԷµǾ��� ���,
				sortvector.x = sortvectorsizex; // x�� ������� �⺻ ���� �ʱ�ȭ

			Vector3 charX = Vector3(def->GetRect().x / 3.8, 0, 0);

			def->SetPosition(def->GetPosition() - sortvector); // ���� ��ġ�� �ܾ� ���̸�ŭ�� �� �о����.
			sortvector -= charX;
			// ������ �������� �̴� ���� ��� �� ������ x������ ��ŭ �پ���� �Ѵ�.
		}
		break;
	}
	case MIDDLE: 	// �� ������ ������ġ �� ������ �߾��Դϴ�.
	{
		float sortvectorsizex = (result->Endposition.x - result->Startposition.x) / 2; // ��ü ���� ������ ��
		Vector3 sortvector = { sortvectorsizex, 0, 0 };
		for (auto def : result->numstring) {
			if (def->GetPosition().y < result->Startposition.y) // ���Ͱ� �ԷµǾ��� ���,
				sortvector.x = sortvectorsizex; // x�� ��������� �⺻�� ���� �� �ʱ�ȭ

			Vector3 charX = Vector3(def->GetRect().x / 3.8, 0, 0);

			def->SetPosition(def->GetPosition() - sortvector); // ���� ��ġ�� �ܾ� ���̸�ŭ�� �� �о����.
			sortvector -= charX;
			// ������ �������� �̴� ���� ��� �� ������ x������ ��ŭ �پ���� �Ѵ�.
		}
		break;
	}
	default: // �� ������ ������ġ ���� ���������� �߻��մϴ�.
		break;
	}

	return *result;
}

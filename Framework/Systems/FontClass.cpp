#include "Framework.h"
#include "FontClass.h"

FontClass::FontClass()
{
}

FontClass::~FontClass()
{
	SAFE_DELETE(charators);
}

void FontClass::Render()
{
}

void FontClass::SetFontfile()
{

}

bool FontClass::SetString()
{
	return false;
}

#pragma once
#include "Framework.h"

class OutlineBuffer : public ShaderBuffer
{
public:
	OutlineBuffer()
		: ShaderBuffer(&data, sizeof(Data))
	{
		data.textureSize = Values::ZeroVec2;
		data.OutlineCount = 1;
	}

	void SetTextureSize(Vector2 size)
	{
		data.textureSize = size;
	}

	void SetOutlineCount(uint outlinecount)
	{
		data.OutlineCount = outlinecount;
	}

	uint* GetOutlineCountPtr() { return &data.OutlineCount; }

	struct Data
	{
		Vector2 textureSize;
		uint OutlineCount;
		int dummy;
	};
private:
	Data data;
};

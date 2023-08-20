#pragma once
#include "Framework.h"

class OutlineBuffer : public ShaderBuffer
{
public:
	OutlineBuffer()
		: ShaderBuffer(&data, sizeof(Data))
	{
		ZeroMemory(&data, sizeof(data));				// 사용 메모리 초기화.
		data.textureSize = Values::ZeroVec2;
		data.OutlineCount = 0;
		data.dummy = NULL;
	}

	void SetTextureSize(Vector2 size)
	{
		data.textureSize = size;
	}

	void SetOutlineCount(const int outlinecount)
	{
		data.OutlineCount = outlinecount;
	}

	int* GetOutlineCountPtr() { return &data.OutlineCount; }

	struct Data
	{
		Vector2 textureSize;
		int OutlineCount;
		int dummy;
	};
private:
	Data data;
};

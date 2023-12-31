// 버택스 정보를 저장하기 위한 구조체
#pragma once

// 색상
struct VertexColor
{
	VertexColor()
		: position(0, 0, 0), color(0, 0, 0, 0) {}

	VertexColor(Vector3 position, Color color)
		: position(position), color(color) {}
	
	Vector3 position;	// 정점 위치
	Color color;		// 정점 색상

	static D3D11_INPUT_ELEMENT_DESC descs[];	// 정점 데이터 구조 서술
	static const uint count = 2;				// 원소 개수
};

// 텍스처
struct VertexTexture
{
	VertexTexture()
		: position(0, 0, 0), uv(0, 0) {}

	VertexTexture(Vector3 position, Vector2 uv)
		: position(position), uv(uv) {}

	Vector3 position;	// 정점 위치
	Vector2 uv;			// 텍스트 좌표

	static D3D11_INPUT_ELEMENT_DESC descs[];	// 정점 데이터 구조 서술
	static const uint count = 2;				// 원소 개수
};

// 문자 텍스처
struct TextureVertexTexture
{
	TextureVertexTexture()
		: position(0, 0, 0), uv(0, 0), color(0,0,0,0) {}

	TextureVertexTexture(Vector3 position, Vector2 uv, Color color)
		: position(position), uv(uv), color(color) {}

	Vector3 position;	// 정점 위치
	Vector2 uv;			// 텍스트 좌표
	Color color;		// 텍스트 컬러

	static D3D11_INPUT_ELEMENT_DESC descs[];	// 정점 데이터 구조 서술
	static const uint count = 3;				// 원소 개수
};

struct VertexTile
{
	VertexTile()
		: position(Values::ZeroVec3), uv(Values::ZeroVec2), color(0, 0, 0, 0) {}

	VertexTile(Vector3 position, Vector2 uv, Vector2 uv2, Color color, uint index)
		: position(position), uv(uv), uv2(uv2), color(color), index(index) {}

	Vector3 position;
	Vector2 uv;
	Vector2 uv2;
	Color color;
	uint index;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 5;
};
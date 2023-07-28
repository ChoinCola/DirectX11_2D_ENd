#pragma once

class Character_Demo
{
public:
	Character_Demo(Vector3 position, Vector3 size, float rotation);
	~Character_Demo();

	virtual void Move();

	void MapVertexBuffer();
	void UnmapVertexBuffer();

	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderpath);

	void Update();
	void UpdateWorld();

	void Render();
	void GUI();

	const Vector3* GetVerticesLocalPosition() { return verticesLocalPosition; }
	const Matrix GetWorld() { return world; }

	const Vector3 GetSize() { return size; }
	const float GetRotation() { return rotation; }
	const Vector3 GetPosition() { return position; }

protected:
	vector<VertexTexture> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	Matrix world;
	Matrix S, R, T;

	WorldBuffer* wb = nullptr;

	Vector3 position;
	Vector3 size;
	float rotation;

	ID3D11ShaderResourceView* srv = nullptr;

	D3D11_MAPPED_SUBRESOURCE subResource;

	Vector3 verticesLocalPosition[4];

private:
	class Animator* animator = nullptr;
	ID3D11SamplerState* point[2];
	ID3D11BlendState* bPoint[2];
};

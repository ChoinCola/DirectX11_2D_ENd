#pragma once

class RedBuffer : public ShaderBuffer
{
public:
	RedBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		data.HIT = false;
	}

	void SetHit(bool type)
	{
		data.HIT = type;
	}

	struct Data
	{
		bool HIT;
		Vector3 dummy1;
		bool dubbmy2;
		bool dummy3;
		bool d4;
	};
private:
	Data data;
};

class TextureRect
{
public:
	TextureRect(Vector3 position, Vector3 size, float rotation, Color path, Vector2 flip = { 0,0 });
	TextureRect(Vector3 position, std::vector<Vector3>* terticespos, std::vector<Vector2>* uv, Vector3 size,
	float rotation, Color path, Texture2D* Fontpng);
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring path, Vector2 flip = { 0,0 });
	TextureRect(Vector3 position, Vector3 size, float rotation, Vector2 flip = { 0,0 });
	~TextureRect();

	void MapVertexBuffer();
	void UnmapVertexBuffer();

	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderpath);

	void Update();
	void Update(Vector3 position);
	void UpdateWorld();

	void Render();
	void GUI();

	const Vector3* GetVerticesLocalPosition() { return verticesLocalPosition; }
	const Matrix GetWorld() { return world; }
	void SetWorld(const Matrix world) { this->world = world; }

	const Vector3 GetSize() { return size; }
	const float GetRotation() { return rotation; }
	Vector3& GetPosition() { return position; }
	ID3D11ShaderResourceView* GetSRV() { return srv; }
	D3DXMATRIX& GetCenterPoint() { return X; }

	void SetPosition(const float x, const float y, const float z = 0) { position.y = y; position.x = x; position.z = z;}
	void SetPosition(const Vector3 def) { position = def; }
	void SetRotation(const float rotation) { this->rotation = rotation; }
	void SetSize(const Vector3 Size) { this->size = Size; }

protected:

	vector<VertexColor> colorVertices;
	vector<VertexTexture> vertices;
	vector<TextureVertexTexture> Textvertices;

	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	Matrix world;
	Matrix S, R, T, X;

	WorldBuffer* wb = nullptr;

	Vector3 position;
	Vector3 size;
	float rotation;

	ID3D11ShaderResourceView* srv = nullptr;

	D3D11_MAPPED_SUBRESOURCE subResource;

	Vector3 verticesLocalPosition[4];

	RedBuffer* hb = nullptr;

	private:
	void buff(Vector2 flip);
};

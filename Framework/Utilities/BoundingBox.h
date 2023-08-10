#pragma once

enum
{
	x = 0,
	y
};

struct RectEdge
{
	Vector3 LT;
	Vector3 LB;
	Vector3 RT;
	Vector3 RB;
};

struct AxisData
{
	Vector3 centerPos; // �߽����� ���Ѵ�.
	Vector3 axisDir[2]; // ���⺤�͸� ����, �����ش�.
	float axisLen[2]; // �࿡ ���� �Ÿ�.
};

class CollisionBuffer : public ShaderBuffer
{
public:
	CollisionBuffer() : ShaderBuffer(&data, sizeof(data))
	{ // �浹ü ó���� ���� �״� ���� �ϱ� ���� �������.
		data.isOn = 0;
	}

	void SwitchRender() { data.isOn = !data.isOn; }

	struct Data
	{
		int isOn;
		Vector3 dummy;
	};

private:
	Data data;
};

class BoundingBox
{
public:
	BoundingBox(Vector3 position, Vector3 size, float rotation, Color color);
	~BoundingBox();

	void Init();

	void Update(Vector3 position);
	void Update(Vector3 position, Vector3 size, float rotation);
	void Update(Vector3 position, Vector3 size, float rotation, Vector3 CenterPoint);
	void Update(Vector3 position, Vector3 size, float rotation, D3DXMATRIX CenterPoint);
	void Render(); // �浹ü �׸��°� �����ֱ� ���� Render�� �־���.

	Vector3 GetPosition() { return position; }

	void UpdateCollisionData(); // OBB�� AABB�� ���������� �ɸ����� ������ ��ǥ�� ������Ʈ ���ִ� ������ �Ѵ�.

	static bool AABB(BoundingBox* a, BoundingBox* b);
	static bool OBB(BoundingBox* a, BoundingBox* b); // ���� OBB�� AABB�� �浹ó���� �������� ���� ����Ѵ�.

private:
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	Matrix world;
	WorldBuffer* wb = nullptr;

	Vector3 CenterPoint;
	Vector3 position;
	Vector3 size;
	float rotation;
	Color color;

	CollisionBuffer* cb = nullptr;
	ID3D11BlendState* bs = nullptr;

	RectEdge* edge = nullptr;
	AxisData* data = nullptr;
};
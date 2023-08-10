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
	Vector3 centerPos; // 중심축을 구한다.
	Vector3 axisDir[2]; // 방향벡터를 만들어서, 돌려준다.
	float axisLen[2]; // 축에 대한 거리.
};

class CollisionBuffer : public ShaderBuffer
{
public:
	CollisionBuffer() : ShaderBuffer(&data, sizeof(data))
	{ // 충돌체 처리를 위해 켰다 껐다 하기 위해 만들었다.
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
	void Render(); // 충돌체 그리는거 보여주기 위해 Render를 넣었다.

	Vector3 GetPosition() { return position; }

	void UpdateCollisionData(); // OBB와 AABB와 마찬가지로 케릭터의 움직임 좌표를 업데이트 해주는 역할을 한다.

	static bool AABB(BoundingBox* a, BoundingBox* b);
	static bool OBB(BoundingBox* a, BoundingBox* b); // 각각 OBB나 AABB의 충돌처리를 가져오기 위해 사용한다.

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
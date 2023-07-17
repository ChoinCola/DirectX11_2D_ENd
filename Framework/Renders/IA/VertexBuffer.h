#pragma once

class VertexBuffer
{
public:
	~VertexBuffer();

	// ���� �ڷ������� ��� ������ �𸣱� ������ ���ø� ���
	template<typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }

	uint GetStride() { return stride; }
	uint GetOffset() { return offset; }
	uint GetCount()  { return count;  }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	uint stride = 0;		// ���� ���ۿ��� �� ������ ũ�⸦ ��Ÿ���� ��
	uint offset = 0;		// ���ۿ��� �б� ������ ��ġ
	uint count = 0;			// ���� ���ۿ��� ���� ���� ����
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
	stride = sizeof(T);		// ���� ũ�� ����
	count = vertices.size();	// ���� ���� ����

	D3D11_BUFFER_DESC desc;							// ���� ������ ���� ����ü ����
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));	// ����ü �ʱ�ȭ

	// desc ����
	{
		desc.Usage = usage;							// ������ ��� �뵵 ����
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���� ���۷� ������� ����
		desc.ByteWidth = stride * count;			// ���� ũ��

		// CPU ���� ����
		switch (usage)
		{
			case D3D11_USAGE_DEFAULT:
			case D3D11_USAGE_IMMUTABLE:
				break;

			case D3D11_USAGE_DYNAMIC:
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				break;

			// CPU���� ���� ����, GPU���� ����� �� �ִ� ���·� ��ȯ ������ ����
			case D3D11_USAGE_STAGING:
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
				break;
		}
	}

	// Buffer ����
	{
		D3D11_SUBRESOURCE_DATA subData;									// ���� �����͸� ���� ����ü
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));			// ����ü �ʱ�ȭ

		subData.pSysMem = vertices.data();								// ���� �����͸� �Ҵ��� �޸𸮿� ����

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);	// ���� ���� ����
		CHECK(hr);	// ���� ���� �� ��
	}
}

/*						GPU				CPU
D3D11_USAGE_DEFAULT		�б�, ����		���� �Ұ�
D3D11_USAGE_IMMUTABLE	�б�				���� �Ұ�
D3D11_USAGE_DYNAMIC		�б�				����(Map���) (����)
D3D11_USAGE_STAGING		GPU �޸𸮿��� CPU �޸𸮷� ���縦 ��� (CopyResource) (��û ����)
*/
struct VertexInput
{
	float4 position : POSITION0; // ���� ��ġ "position"�̶�� ������ "POSITION0" ��Ʈ���� ��ġ�� ���� ������ �����Ѵ�
	float2 uv : TEXCOORD0; // uv ��ǥ
    float4 color : COLOR0;
};

struct PixelInput
{
	float4 position : SV_POSITION0; // �ȼ� ��ġ     �ȼ��� ��ġ�� ��Ÿ���� �ý��� ���� �ǹ�
	float2 uv : TEXCOORD0; // �ؽ�Ʈ �ȼ� ����
    float4 color : COLOR0;
};

// cbuffer : ��� ���� ��������
// ��� ���� �������� b0�� �Ҵ�� ���� ����� �����ϴ� ��� ����
cbuffer WorldBuffer : register(b0) // 0 ~ 127
{
	matrix _world;
}

// ��� ���� �������� b1�� �Ҵ�� ��, �������� ����� �����ϴ� ��� ����
cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _projection;
}

cbuffer OutlineBuffer : register(b2)
{
    float2 _imageSize;
    int _OutlineCount;
}

// ���� ���̴� �Լ�
// �Է����� VertexInput�� �ް� PixelInput ����ü�� ��ȯ
PixelInput VS(VertexInput input)
{
	PixelInput output;
    
	output.position = mul(input.position, _world); // ���� ��ġ�� ���� ����� ����
	output.position = mul(output.position, _view); // ����� �� ����� ����
	output.position = mul(output.position, _projection); // ����� �������� ����� ����
    
	output.uv = input.uv;
    output.color = input.color;
    
	return output;
}

Texture2D _sourceTex : register(t0); // �ؽ�ó �����͸� ����
SamplerState _samp : register(s0); // ���ø��ϴ� ����� ����

// �ȼ� ���̴� �Լ�
// �Է����� PixelInput ����ü�� �ް�, float4 ������ �ȼ� ������ ��ȯ
float4 PS(PixelInput input) : SV_Target
{
    float4 color = float4(input.color.rgb, _sourceTex.Sample(_samp, input.uv).a);
    float4 ChackColor;

    if (_OutlineCount != 0)
    {
        if (color.r + color.g + color.b >= (float) 1.5)
            ChackColor = float4(0, 0, 0, 1);
        else
            ChackColor = float4(1, 1, 1, 1);
    
        float2 arr[8] =
        {
            float2(-.1, +.1), float2(+.0, +.1), float2(+.1, +.1),
            float2(-.1, +.0), /* ���� ���� */    float2(+.1, +.0),
            float2(-.1, -.1), float2(+.0, -.1), float2(+.1, -.1)
        };
        
        for (int Otline = 0; Otline < _OutlineCount; Otline++)
        {
            for (int i = 0; i < 8; i++)
            {
                float x = input.uv.x + arr[i].x * Otline / _imageSize.x * _OutlineCount;
                float y = input.uv.y + arr[i].y * Otline / _imageSize.y * _OutlineCount;
                float2 uv = float2(x, y);
                float4 chackdef = _sourceTex.Sample(_samp, uv);
                
                if (chackdef.r != ChackColor.r &&
                chackdef.g != ChackColor.g &&
                chackdef.b != ChackColor.b &&
                _sourceTex.Sample(_samp, input.uv).a <= 0.4)
                {
                    color.rgba = float4(ChackColor.rgb, 1); // �ܰ��� ����ó��
                    return color;
                }
            }
        }
    }
    return color;
}

/*
Semantic : ����ƽ
- HLSL ���̴����� �������� �ǹ̸� �����ϴµ� ���
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ����
- ���� �̸� �ڿ� ':'��ȣ�� �Բ� ����
- �ý��� �� ����ƽ�� 'SV_'���λ�� �����ϸ� Direct3D���� ���ǵ� Ư���� �ǹ̸� ����
- �ý��� �� ����ƽ�� ���̴� �������� ���� �����͸� �����ϴµ� ���

slot
- GPU���� ����ϴ� ��� ����, �ؽ�ó, ���÷� ���� �ڿ����� �ĺ��ϴ� �ε���
- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ��� �Ҵ��
- register��� Ű���带 ����Ͽ� ����
- �� �ڿ��� � ���Կ� �Ҵ�� ������ ��������� ������ �� ����
- �ֿ� ����
    1) ��� ���� ����
    - ��� �����͸� �����ϴµ� ���, VS�� PS���� ������ �� �ִ�
    - ��� ���� ������ register(b#)�� ����Ͽ� ����

    2) �ؽ�ó ����
    - �̹��� �����͸� �����ϴµ� ���
    - �ؽ�ó ���� ������ register(t#)�� ����Ͽ� ����

    3) ���÷� ����
    - �ؽ�ó�� ���ø� �ϴ� �� ���
    - ���÷� ������ register(s#)�� ����Ͽ� ����

cbuffer = Constance Buffer : ��� ����
- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
- �� ��� ���� �������Ϳ��� �� ���� ��� ���۸� �Ҵ��� �� ����
- ��� ���� ���ο��� ���� ���� ������ ������ �� �ִ�.
*/
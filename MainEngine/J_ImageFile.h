#pragma once
#include <vector> 
#include <string>
#include <Windows.h>
#include <J_GameEngineDebug.h>
#include <J_GameEngineMath.h>
#include <J_GameEngineNameBase.h>

//class J_Tile
class J_ImageManager;
class J_ImageFile: public J_GameEngineNameBase
{
	friend J_ImageManager;
	//friend J_Tile;		Ÿ�� Ŭ������ ���� Ŭ������ �°ݵǸ� �����ڸ� �ٽ� �����̺����� ������ Ÿ�� Ŭ������ ������� ������ ��.

	HBITMAP imageHBMP_;			//��Ʈ�� ���Ͽ��� �ҷ��� �̹����� �ڵ�. 
	HBITMAP prevHBMP_;			//imageHBMP_�� ������ �ִ� ���� �̹��������� �����ϴ� �ڵ�.
	HDC imageHDC_;				//�ҷ��� �̹����� ���� DC�ڵ�.
	BITMAP imageInfo_;			//�ҷ��� �̹����� ���� ����.



	std::vector<float4> cuttingPos_;	//�Ѱ��� �� �̹����� �ڸ� �ȼ���ǥ ����.
	std::vector<float4> cuttingSizes_;	//�Ѱ��� �� �̹����� �ڸ� ũ��.
	int Index_cuttingPos_;				//�߶� ������ �̹����� ����ų ��ȣ.

	//typedef struct tagBITMAP
	//{
	//	LONG        bmType;				���� Ÿ��. ��Ʈ�������� �ǹ��ϴ� 0������ ����.
	//	LONG        bmWidth;			�̹����� ���� �ȼ� ��.
	//	LONG        bmHeight;			�̹����� ���� �ȼ� ��.
	//	LONG        bmWidthBytes;		�̹��� ���� ������ ����Ʈ���� �뷮.
	//	WORD        bmPlanes;			����ϴ� ���� �÷��� ��. ������ ���� 1�̴�.
	//	WORD        bmBitsPixel;		�� �ȼ��� �� ��Ʈ ������ ����ϴ����� ���� ����. 
	//	LPVOID      bmBits;				��Ʈ�� ������ ����� �޸� �ּ�.
	//} BITMAP, * PBITMAP, NEAR* NPBITMAP, FAR* LPBITMAP;

public:
	J_ImageFile();		
	J_ImageFile(J_ImageFile&& _other) noexcept;					//����Ʈ rvalue ���������.
	~J_ImageFile();											//����Ʈ �Ҹ���.


public:
	J_ImageFile(const J_ImageFile& _other) = delete;				//����Ʈ ���������.

	J_ImageFile& operator=(const J_ImageFile& _other) = delete;		//����Ʈ ���Կ�����.
	J_ImageFile& operator=(const J_ImageFile&& _other) = delete;	//����Ʈ rvalue ���Կ�����.

	void PasteOnBackBuffer(J_ImageFile* _sourceImage,			
		const float4& _renderPos, const float4& _renderSize,
		const float4& _srcImagePos, const float4& _srcImageSize,
		int _transparency = RGB(255, 0, 255));

	void CutImage(const float4& _cuttingSize);	

	void Bitcopy(J_ImageFile* _sourceImage, const float4& _srcImageSize);
	void TransCopy(J_ImageFile* _sourceImage,
		const float4& _renderPos, const float4& _renderSize,
		const float4& _srcImagePos, const float4& _srcImageSize,
		int _transparency);

public:
	HDC GetDC() const
	{
		return imageHDC_;
	}

	float4 GetImageSize() const
	{
		return { static_cast<float>(imageInfo_.bmWidth),
			static_cast<float>(imageInfo_.bmHeight) };
	}

	float4 GetCuttingPos(int _index)
	{
		return cuttingPos_[_index];
	}

	float4 GetCuttingSizes(int _index)
	{
		return cuttingSizes_[_index];
	}

	bool IsCuttingSizesEmpty()
	{
		return cuttingSizes_.empty();
	}


private:

	bool CreateCurWindowImage(HDC _curWindowHDC);
	bool CreateBackBufferImage(HDC _curWindowHDC, const float4& _windowSize);
	bool LoadBMPImage(const std::string& _path);

	void GetImageInfo();
};


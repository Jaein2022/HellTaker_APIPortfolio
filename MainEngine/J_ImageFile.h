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
	//friend J_Tile;		타일 클래스가 엔진 클래스로 승격되면 생성자를 다시 프라이빗으로 돌리고 타일 클래스를 프렌드로 지정할 것.

	HBITMAP imageHBMP_;			//비트맵 파일에서 불러온 이미지의 핸들. 
	HBITMAP prevHBMP_;			//imageHBMP_가 가지고 있던 이전 이미지정보를 보관하는 핸들.
	HDC imageHDC_;				//불러온 이미지에 대한 DC핸들.
	BITMAP imageInfo_;			//불러온 이미지가 가진 정보.



	std::vector<float4> cuttingPos_;	//한개의 통 이미지를 자를 픽셀좌표 모음.
	std::vector<float4> cuttingSizes_;	//한개의 통 이미지를 자를 크기.
	int Index_cuttingPos_;				//잘라낸 각각의 이미지를 가리킬 번호.

	//typedef struct tagBITMAP
	//{
	//	LONG        bmType;				파일 타입. 비트맵파일을 의미하는 0번으로 고정.
	//	LONG        bmWidth;			이미지의 가로 픽셀 수.
	//	LONG        bmHeight;			이미지의 세로 픽셀 수.
	//	LONG        bmWidthBytes;		이미지 가로 한줄의 바이트단위 용량.
	//	WORD        bmPlanes;			사용하는 색상 플레인 수. 요즘은 보통 1이다.
	//	WORD        bmBitsPixel;		한 픽셀에 몇 비트 색상을 사용하는지에 대한 정보. 
	//	LPVOID      bmBits;				비트맵 파일이 저장된 메모리 주소.
	//} BITMAP, * PBITMAP, NEAR* NPBITMAP, FAR* LPBITMAP;

public:
	J_ImageFile();		
	J_ImageFile(J_ImageFile&& _other) noexcept;					//디폴트 rvalue 복사생성자.
	~J_ImageFile();											//디폴트 소멸자.


public:
	J_ImageFile(const J_ImageFile& _other) = delete;				//디폴트 복사생성자.

	J_ImageFile& operator=(const J_ImageFile& _other) = delete;		//디폴트 대입연산자.
	J_ImageFile& operator=(const J_ImageFile&& _other) = delete;	//디폴트 rvalue 대입연산자.

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


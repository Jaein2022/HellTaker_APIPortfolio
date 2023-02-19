#include "J_ImageFile.h"
#pragma comment(lib, "msimg32.lib")
//msimg32.lib: transparentBlt()등의 이미지 관련 내용이 포함되어있는 라이브러리. 
//윈도우에서 이미 지원해주므로 경로설정을 추가로 해 줄 필요가 없다.

J_ImageFile::J_ImageFile() 
	: imageHBMP_(nullptr),
	prevHBMP_(nullptr), 
	imageHDC_(nullptr), 
	imageInfo_(),
	cuttingPos_(),
	cuttingSizes_(),
	Index_cuttingPos_(0)
{
}

J_ImageFile::J_ImageFile(J_ImageFile&& _other) noexcept
	: imageHBMP_(_other.imageHBMP_),
	prevHBMP_(_other.prevHBMP_),
	imageHDC_(_other.imageHDC_),
	imageInfo_(_other.imageInfo_),
	cuttingPos_(_other.cuttingPos_), 
	cuttingSizes_(_other.cuttingSizes_),
	Index_cuttingPos_(0)
{
}

J_ImageFile::~J_ImageFile()
{
	DeleteDC(imageHDC_);
	DeleteObject(imageHBMP_);
	DeleteObject(prevHBMP_);
	cuttingPos_.clear();
	cuttingSizes_.clear();
	//사실 안해줘도 프로그램 종료할 때 윈도우즈가 알아서 회수한다.
}

void J_ImageFile::PasteOnBackBuffer(J_ImageFile* _sourceImage, const float4& _renderPos, const float4& _renderSize,
	const float4& _srcImagePos, const float4& _srcImageSize, int _transparency /*= RGB(255, 0, 255)*/)
{
	TransCopy(_sourceImage, _renderPos, _renderSize, _srcImagePos, _srcImageSize, _transparency);
}

void J_ImageFile::CutImage(const float4& _cuttingSize)
{
	if (0.0f >= _cuttingSize.x_ || 0.0f >= _cuttingSize.y_)
	{
		J_GameEngineDebug::AssertFalse("Size cannot be zero or minus.");
		return;
	}

	if (false == cuttingPos_.empty() || false == cuttingSizes_.empty() )
	{
		J_GameEngineDebug::AssertFalse("This image is already cut.");
		return;
	}

	size_t XCount = static_cast<size_t>(this->GetImageSize().x_ / _cuttingSize.x_);
	size_t YCount = static_cast<size_t>(this->GetImageSize().y_ / _cuttingSize.y_);

	cuttingPos_.reserve(XCount * YCount);
	cuttingSizes_.reserve(XCount * YCount);

	float4 cuttingPos = float4::ZERO;
	float4 cuttingSize = _cuttingSize;

	for (size_t y = 0; y < YCount; y++)
	{
		for (size_t x = 0; x < XCount; x++)
		{
			cuttingPos_.push_back(cuttingPos);
			cuttingSizes_.push_back(cuttingSize);
			cuttingPos.x_ += cuttingSize.x_;
		}
		cuttingPos.x_ = 0.0f;
		cuttingPos.y_ += cuttingSize.y_;
	}
}

void J_ImageFile::Bitcopy(J_ImageFile* _sourceImage, const float4& _srcImageSize)
{
	if (nullptr == _sourceImage)
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::CopyBMP()-> nullptr == _sourceImage.");
		return;
	}

	if (0 >= _srcImageSize.x_ || 0 >= _srcImageSize.y_)
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::CopyBMP()-> 0 >= _srcImageSize");
		return;
	}

	BitBlt(								//BitBlt(): 첫 HDC의 이미지 위에 두번째 HDC의 이미지를 잘라 붙이는 함수. 실패하면 0 반환.
		this->imageHDC_,				//이미지가 그려질 윈도우DC의 핸들.
		float4::ZERO.IntX(),			//그릴 이미지의 왼쪽 상단 꼭지점이 위치할 x좌표.
		float4::ZERO.IntY(),			//그릴 이미지의 왼쪽 상단 꼭지점이 위치할 y좌표.
		_srcImageSize.IntX(),			//원본에서 잘라올 이미지의 가로 픽셀길이.
		_srcImageSize.IntY(),			//원본에서 잘라올 이미지의 세로 픽셀길이.
		_sourceImage->imageHDC_,		//그릴 원본 이미지의 DC핸들.
		float4::ZERO.IntX(),			//원본에서 이미지 자르기를 시작할 왼쪽 상단 지점의 x좌표.
		float4::ZERO.IntY(),			//원본에서 이미지 자르기를 시작할 왼쪽 상단 지점의 y좌표.
		SRCCOPY							//복사방식. SRCCOPY: 원본 이미지를 변경없이 그대로 복사. 
	);									//다른 플래그들은 전부 색상 비트연산이므로 신경쓸 필요 없음.
}

void J_ImageFile::TransCopy(J_ImageFile* _sourceImage, const float4& _renderPos, const float4& _renderSize,
	const float4& _srcImagePos, const float4& _srcImageSize, int _transparency)
{
	if (nullptr == _sourceImage)
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::PasteOnBackbuffer()- nullptr == _sourceImage");
		return;
	}

	if (0.0f >= _renderSize.x_ || 0.0f >= _renderSize.y_)
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::PasteOnBackbuffer()-> 0 >= __renderingSize");
		return;
	}

	if (0.0f >= _srcImageSize.x_ || 0.0f >= _srcImageSize.y_)
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::PasteOnBackbuffer()-> 0 >= _srcImageSize");
		return;
	}

	TransparentBlt(					//비트맵 이미지의 특정 색상값을 투명하게 하거나 크기를 조정해서 옮기는 함수. 실패하면 0 반환.
		this->imageHDC_,			//_sourceImage가 그려질 전체 백버퍼 이미지의 HDC.
		_renderPos.IntX(),			//src이미지가 그려질 dest이미지 내 x좌표. 왼쪽상단 기준.
		_renderPos.IntY(),			//src이미지가 그려질 dest이미지 내 y좌표. 왼쪽상단 기준.
		_renderSize.IntX(),			//src이미지가 그려질 dest이미지 내 x 길이.
		_renderSize.IntY(),			//src이미지가 그려질 dest이미지 내 y 길이.
		_sourceImage->GetDC(),		//그릴 대상 이미지의 HDC.
		_srcImagePos.IntX(),		//src이미지를 가져올, src이미지 내 왼쪽상단 x좌표. 
		_srcImagePos.IntY(),		//src이미지를 가져올, src이미지 내 왼쪽상단 y좌표.
		_srcImageSize.IntX(),		//src이미지를 가져올 x 길이.
		_srcImageSize.IntY(),		//src이미지를 가져올 y 길이.
		_transparency				//투명처리할 RGB색상값.
	);
}

bool J_ImageFile::CreateCurWindowImage(HDC _curWindowHDC)
{
	if (nullptr == _curWindowHDC)	
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::CreateCurWIndowImage()-> nullptr == _curWindowHDC");
		return false;
	}
	else
	{
		imageHDC_ = _curWindowHDC;
		GetImageInfo();
		return true;
	}
}

bool J_ImageFile::CreateBackBufferImage(HDC _curWindowHDC, const float4& _windowSize)
{
	if (nullptr == _curWindowHDC)	//_curWindowHDC == 현재 윈도우가 쓰는 hdc가 nullptr이라면 폭파.
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::CreateBackBufferImage()-> nullptr == _curWindowHDC");
		return false;
	}

	imageHBMP_ = CreateCompatibleBitmap(_curWindowHDC, _windowSize.IntX(), _windowSize.IntY());
	//빈 비트맵 핸들인 imageHBMP에 _curWindowHDC가 가진 윈도우 정보와 입력해주는 크기정보를 가진 비트맵 핸들을 새로 할당한다.

	imageHDC_ = CreateCompatibleDC(NULL);	//진짜 메모리DC는 여기서 생성. 
	//NULL을 인자로 넣으면 현재 윈도우 정보가 들어있는 CreateCompatibleDC()함수의 자체 HDC를 생성해서 반환한다. 
	//반환된 HDC에는 기본값으로 1x1 픽셀 검은색 이미지만 연결된 상태로 메모리에만 존재하고 있다.

	HANDLE tempHandle = SelectObject(imageHDC_, static_cast<HGDIOBJ>(imageHBMP_));
	//imageHBMP가 가진 이미지는 imageHDC에 연결하고 imageHDC가 원래 가지고 있던 1x1 픽셀 이미지는 tempHandle에게 반환한다.

	prevHBMP_ = static_cast<HBITMAP>(tempHandle);
	//tempHandle이 가진 이미지는 prevHBMP가 받아 보관한다.

	GetImageInfo();	//imageHDC가 가진 이미지의 정보를 가져온다.

	return true;
}

bool J_ImageFile::LoadBMPImage(const std::string& _path)
{
	//HANDLE == void*.
	HANDLE loadedHBMP = LoadImageA(		//지정된 경로에서 이미지파일을 불러오는 함수.
		nullptr,			//불러오려는 이미지가 있는 exe파일이나 라이브러리의 인스턴스 핸들. 이미지 하나만 있는 파일을 불러올때는 NULL을 넣는다.
		_path.c_str(),		//불러오려는 이미지파일의 경로를 포함한 이름.
		IMAGE_BITMAP,		//이미지 타입. IMAGE_BITMAP를 넣으면 비트맵 형식의 파일을 불러온다.
		0,					//이미지 가로길이. 여길 0으로 하고 마지막 인자가 LR_DEFAULTSIZE가 아니라면 이미지 자제 크기로 불러온다.
		0,					//이미지 세로길이. 여길 0으로 하고 마지막 인자가 LR_DEFAULTSIZE가 아니라면 이미지 자제 크기로 불러온다.
		LR_LOADFROMFILE		//이미지 하나만 있는 파일을 불러올때 두번째 인자에 파일 경로와 이름을, 여기에 LR_LOADFROMFILE를 넣어준다.
	);

	if (NULL == loadedHBMP)
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::LoadBMPImage()-> NULL == LoadImageA().");
		return false;
	}

	imageHBMP_ = static_cast<HBITMAP>(loadedHBMP);


	imageHDC_ = CreateCompatibleDC(NULL);		//빈 HDC인 imageHDC_에 1x1픽셀짜리 이미지와 연결된 DC 핸들을 준다.
	//이 때 imageHDC는 화면상에 직접 그려지지 않고 메모리상에만 존재하는 메모리DC의 핸들이다.
	//GetDC()는 화면과 직접 연결되어 있는 DC를 반환하므로 여기서 쓸 수 없다고 한다.


	HANDLE tempHandle = SelectObject(
		//SelectObject(): HDC형 매개변수에 HGDIOBJ형 매개변수가 가진 DC의 핸들을 넘기고, HDC형 매개변수가 이전까지 가지고 있던 이미지의 핸들을 반환하는 함수.
		imageHDC_,							//이미지를 넘겨받을 HDC.
		static_cast<HGDIOBJ>(loadedHBMP)	//넘겨줄 이미지를 가지고있는 핸들.
	);										//HGDIOBJ: DC용 공용 HANDLE.

	prevHBMP_ = static_cast<HBITMAP>(tempHandle);
	//imageHDC가 가지고 있던 이미지의 핸들은 위에서 tempHandle이 반환받아 prevHBMP로 전달해서 보관한다. 

	GetImageInfo();

	return true;
}

void J_ImageFile::GetImageInfo()
{
	if (nullptr == imageHDC_)
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::GetImageInfo()-> nullptr == imageHDC_");
		return;
	}


	HBITMAP tempHBMP = static_cast<HBITMAP>(GetCurrentObject(imageHDC_, OBJ_BITMAP));
	if (0 == GetObjectA(tempHBMP, sizeof(BITMAP), &imageInfo_))
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::GetImageInfo()-> 0 == GetObjectA()");
		return;
	}
}
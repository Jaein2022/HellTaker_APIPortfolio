#include "J_ImageFile.h"
#pragma comment(lib, "msimg32.lib")
//msimg32.lib: transparentBlt()���� �̹��� ���� ������ ���ԵǾ��ִ� ���̺귯��. 
//�����쿡�� �̹� �������ֹǷ� ��μ����� �߰��� �� �� �ʿ䰡 ����.

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
	//��� �����൵ ���α׷� ������ �� ������� �˾Ƽ� ȸ���Ѵ�.
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

	BitBlt(								//BitBlt(): ù HDC�� �̹��� ���� �ι�° HDC�� �̹����� �߶� ���̴� �Լ�. �����ϸ� 0 ��ȯ.
		this->imageHDC_,				//�̹����� �׷��� ������DC�� �ڵ�.
		float4::ZERO.IntX(),			//�׸� �̹����� ���� ��� �������� ��ġ�� x��ǥ.
		float4::ZERO.IntY(),			//�׸� �̹����� ���� ��� �������� ��ġ�� y��ǥ.
		_srcImageSize.IntX(),			//�������� �߶�� �̹����� ���� �ȼ�����.
		_srcImageSize.IntY(),			//�������� �߶�� �̹����� ���� �ȼ�����.
		_sourceImage->imageHDC_,		//�׸� ���� �̹����� DC�ڵ�.
		float4::ZERO.IntX(),			//�������� �̹��� �ڸ��⸦ ������ ���� ��� ������ x��ǥ.
		float4::ZERO.IntY(),			//�������� �̹��� �ڸ��⸦ ������ ���� ��� ������ y��ǥ.
		SRCCOPY							//������. SRCCOPY: ���� �̹����� ������� �״�� ����. 
	);									//�ٸ� �÷��׵��� ���� ���� ��Ʈ�����̹Ƿ� �Ű澵 �ʿ� ����.
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

	TransparentBlt(					//��Ʈ�� �̹����� Ư�� ������ �����ϰ� �ϰų� ũ�⸦ �����ؼ� �ű�� �Լ�. �����ϸ� 0 ��ȯ.
		this->imageHDC_,			//_sourceImage�� �׷��� ��ü ����� �̹����� HDC.
		_renderPos.IntX(),			//src�̹����� �׷��� dest�̹��� �� x��ǥ. ���ʻ�� ����.
		_renderPos.IntY(),			//src�̹����� �׷��� dest�̹��� �� y��ǥ. ���ʻ�� ����.
		_renderSize.IntX(),			//src�̹����� �׷��� dest�̹��� �� x ����.
		_renderSize.IntY(),			//src�̹����� �׷��� dest�̹��� �� y ����.
		_sourceImage->GetDC(),		//�׸� ��� �̹����� HDC.
		_srcImagePos.IntX(),		//src�̹����� ������, src�̹��� �� ���ʻ�� x��ǥ. 
		_srcImagePos.IntY(),		//src�̹����� ������, src�̹��� �� ���ʻ�� y��ǥ.
		_srcImageSize.IntX(),		//src�̹����� ������ x ����.
		_srcImageSize.IntY(),		//src�̹����� ������ y ����.
		_transparency				//����ó���� RGB����.
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
	if (nullptr == _curWindowHDC)	//_curWindowHDC == ���� �����찡 ���� hdc�� nullptr�̶�� ����.
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::CreateBackBufferImage()-> nullptr == _curWindowHDC");
		return false;
	}

	imageHBMP_ = CreateCompatibleBitmap(_curWindowHDC, _windowSize.IntX(), _windowSize.IntY());
	//�� ��Ʈ�� �ڵ��� imageHBMP�� _curWindowHDC�� ���� ������ ������ �Է����ִ� ũ�������� ���� ��Ʈ�� �ڵ��� ���� �Ҵ��Ѵ�.

	imageHDC_ = CreateCompatibleDC(NULL);	//��¥ �޸�DC�� ���⼭ ����. 
	//NULL�� ���ڷ� ������ ���� ������ ������ ����ִ� CreateCompatibleDC()�Լ��� ��ü HDC�� �����ؼ� ��ȯ�Ѵ�. 
	//��ȯ�� HDC���� �⺻������ 1x1 �ȼ� ������ �̹����� ����� ���·� �޸𸮿��� �����ϰ� �ִ�.

	HANDLE tempHandle = SelectObject(imageHDC_, static_cast<HGDIOBJ>(imageHBMP_));
	//imageHBMP�� ���� �̹����� imageHDC�� �����ϰ� imageHDC�� ���� ������ �ִ� 1x1 �ȼ� �̹����� tempHandle���� ��ȯ�Ѵ�.

	prevHBMP_ = static_cast<HBITMAP>(tempHandle);
	//tempHandle�� ���� �̹����� prevHBMP�� �޾� �����Ѵ�.

	GetImageInfo();	//imageHDC�� ���� �̹����� ������ �����´�.

	return true;
}

bool J_ImageFile::LoadBMPImage(const std::string& _path)
{
	//HANDLE == void*.
	HANDLE loadedHBMP = LoadImageA(		//������ ��ο��� �̹��������� �ҷ����� �Լ�.
		nullptr,			//�ҷ������� �̹����� �ִ� exe�����̳� ���̺귯���� �ν��Ͻ� �ڵ�. �̹��� �ϳ��� �ִ� ������ �ҷ��ö��� NULL�� �ִ´�.
		_path.c_str(),		//�ҷ������� �̹��������� ��θ� ������ �̸�.
		IMAGE_BITMAP,		//�̹��� Ÿ��. IMAGE_BITMAP�� ������ ��Ʈ�� ������ ������ �ҷ��´�.
		0,					//�̹��� ���α���. ���� 0���� �ϰ� ������ ���ڰ� LR_DEFAULTSIZE�� �ƴ϶�� �̹��� ���� ũ��� �ҷ��´�.
		0,					//�̹��� ���α���. ���� 0���� �ϰ� ������ ���ڰ� LR_DEFAULTSIZE�� �ƴ϶�� �̹��� ���� ũ��� �ҷ��´�.
		LR_LOADFROMFILE		//�̹��� �ϳ��� �ִ� ������ �ҷ��ö� �ι�° ���ڿ� ���� ��ο� �̸���, ���⿡ LR_LOADFROMFILE�� �־��ش�.
	);

	if (NULL == loadedHBMP)
	{
		J_GameEngineDebug::AssertFalse("J_ImageFile::LoadBMPImage()-> NULL == LoadImageA().");
		return false;
	}

	imageHBMP_ = static_cast<HBITMAP>(loadedHBMP);


	imageHDC_ = CreateCompatibleDC(NULL);		//�� HDC�� imageHDC_�� 1x1�ȼ�¥�� �̹����� ����� DC �ڵ��� �ش�.
	//�� �� imageHDC�� ȭ��� ���� �׷����� �ʰ� �޸𸮻󿡸� �����ϴ� �޸�DC�� �ڵ��̴�.
	//GetDC()�� ȭ��� ���� ����Ǿ� �ִ� DC�� ��ȯ�ϹǷ� ���⼭ �� �� ���ٰ� �Ѵ�.


	HANDLE tempHandle = SelectObject(
		//SelectObject(): HDC�� �Ű������� HGDIOBJ�� �Ű������� ���� DC�� �ڵ��� �ѱ��, HDC�� �Ű������� �������� ������ �ִ� �̹����� �ڵ��� ��ȯ�ϴ� �Լ�.
		imageHDC_,							//�̹����� �Ѱܹ��� HDC.
		static_cast<HGDIOBJ>(loadedHBMP)	//�Ѱ��� �̹����� �������ִ� �ڵ�.
	);										//HGDIOBJ: DC�� ���� HANDLE.

	prevHBMP_ = static_cast<HBITMAP>(tempHandle);
	//imageHDC�� ������ �ִ� �̹����� �ڵ��� ������ tempHandle�� ��ȯ�޾� prevHBMP�� �����ؼ� �����Ѵ�. 

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
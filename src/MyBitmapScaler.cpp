/*
 ============================================================================
 Name		: MyBitmapScaler.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2011

 Description : CMyBitmapScaler implementation
 ============================================================================
 */
#include <MyBitmapScaler.h>

CMyBitmapScaler* CMyBitmapScaler::NewL( 
    MBitmapScalerObserver* aObserver )
    {
    CMyBitmapScaler* self = 
        new(ELeave) CMyBitmapScaler( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(self);
    return self; 
    }
 
CMyBitmapScaler::CMyBitmapScaler( 
    MBitmapScalerObserver* aObserver ) : 
    CActive( EPriorityStandard ), iObserver( aObserver )
    {
    }
 
void CMyBitmapScaler::ConstructL()
    {
    iScaler = CBitmapScaler::NewL();
    CActiveScheduler::Add(this);
    }
 
CMyBitmapScaler::~CMyBitmapScaler()
    {
    Cancel();
    delete iBitmap;
    delete iScaler;
    }
 
void CMyBitmapScaler::DoCancel()
    {
    iScaler->Cancel();
    }
 
void CMyBitmapScaler::RunL()
    {
	if (iCount==0)
		{Scale(iPercent,iMask);}
	else
		{
		iObserver->Completed(iStatus.Int());
		}
    }
 
TInt CMyBitmapScaler::RunError(TInt aError)   
    {
    iObserver->Completed(aError);
    return KErrNone;
    }
void CMyBitmapScaler::StartScale(TInt aPercent,CFbsBitmap* aBmp,CFbsBitmap* aMask)
	{
	  iBitmap=aBmp;
	  iPercent=aPercent;
	  iMask=aMask;
	  iCount=0;
	  Scale(iPercent,iBitmap);
	}
void CMyBitmapScaler::Scale(TInt aPercent,CFbsBitmap* aBitmap)
    {
    if (IsActive())
        {
        return;
        }
    TReal32 multiplier; 
    multiplier = aPercent/(TReal32)100.0;
 
    TInt newWidth = (TInt)(aBitmap->SizeInPixels().iWidth * multiplier);
    TInt newHeight = (TInt)(aBitmap->SizeInPixels().iHeight * multiplier);
 
    // The maintain aspect ratio is by default set to true
    iScaler->Scale( &iStatus, *aBitmap, TSize(newWidth,newHeight) );
 
    SetActive();
    }
 
CFbsBitmap* CMyBitmapScaler::GetBitmap()
    {
    return iBitmap;
    }
CFbsBitmap* CMyBitmapScaler::GetMask()
    {
    return iMask;
    }

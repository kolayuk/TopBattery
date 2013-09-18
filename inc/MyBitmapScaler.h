/*
 ============================================================================
 Name		: MyBitmapScaler.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2011

 Description : CMyBitmapScaler declaration
 ============================================================================
 */

#ifndef MYBITMAPSCALER_H
#define MYBITMAPSCALER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION
#include <bitmaptransforms.h>
#include <fbs.h>
 
class MBitmapScalerObserver
    {
    public:
        virtual void Completed(TInt aErr) = 0;
    };
 
class CMyBitmapScaler : public CActive
    {
    public:
        static CMyBitmapScaler* NewL(MBitmapScalerObserver* aObserver);
        virtual ~CMyBitmapScaler();
 
    public:
        void StartScale( TInt aPercent,CFbsBitmap* aBmp,CFbsBitmap* aMask );
        void Scale( TInt aPercent,CFbsBitmap* aBmp);
        CFbsBitmap* GetBitmap();
		CFbsBitmap* GetMask();
		TInt iCount;
		CFbsBitmap* iMask;
		TInt iPercent;
    protected: // From CActive
        void DoCancel();
        void RunL();
        TInt RunError(TInt aError);
 
    private:
        CMyBitmapScaler(MBitmapScalerObserver* aObserver); 
        void ConstructL();          
 
    private:
        CFbsBitmap*             iBitmap;
        CBitmapScaler*          iScaler;
        MBitmapScalerObserver*   iObserver;
    };
#endif // MYBITMAPSCALER_H

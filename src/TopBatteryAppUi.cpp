/*
========================================================================
 Name        : TopBatteryAppUi.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <TopBattery.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "TopBatteryAppUi.h"
#include "TopBattery.hrh"
#include "MainView.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]
#include <bautils.h>
#include <const.h>
#include <APGCLI.H>
#include <ImageConversion.h>
#include <apgwgnam.h>
#include <aknglobalmsgquery.h>
#include <logger.h>
#include <akniconutils.h>

#include <bitmaptransforms.h>


/**
 * Construct the CTopBatteryAppUi instance
 */ 
CTopBatteryAppUi::CTopBatteryAppUi(): MFgrCallBack(), MBatteryObserver(), MBitmapScalerObserver()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CTopBatteryAppUi::~CTopBatteryAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	delete iObserver;
	delete iBattery;
	iSprite->Close();
	delete iSprite;
	iWinGroup->Close();
	delete iWinGroup;
	iWsSession->Close();
	delete iWsSession;
	delete iBitmap;
	delete iMask;
	}

// [[[ begin generated function: do not modify
void CTopBatteryAppUi::InitializeContainersL()
	{
	iMainView = CMainView::NewL();
	AddViewL( iMainView );
	SetDefaultViewL( *iMainView );
	}
// ]]] end generated function

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */
void CTopBatteryAppUi::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		}
	// ]]] end generated region [Generated Code]
	
	}

/** 
 * Override of the HandleResourceChangeL virtual function
 */
void CTopBatteryAppUi::HandleResourceChangeL( TInt aType )
	{
	CAknViewAppUi::HandleResourceChangeL( aType );
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}
				
/** 
 * Override of the HandleKeyEventL virtual function
 * @return EKeyWasConsumed if event was handled, EKeyWasNotConsumed if not
 * @param aKeyEvent 
 * @param aType 
 */
TKeyResponse CTopBatteryAppUi::HandleKeyEventL(
		const TKeyEvent& aKeyEvent,
		TEventCode aType )
	{
	// The inherited HandleKeyEventL is private and cannot be called
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	return EKeyWasNotConsumed;
	}

/** 
 * Override of the HandleViewDeactivation virtual function
 *
 * @param aViewIdToBeDeactivated 
 * @param aNewlyActivatedViewId 
 */
void CTopBatteryAppUi::HandleViewDeactivation( 
		const TVwsViewId& aViewIdToBeDeactivated, 
		const TVwsViewId& aNewlyActivatedViewId )
	{
	CAknViewAppUi::HandleViewDeactivation( 
			aViewIdToBeDeactivated, 
			aNewlyActivatedViewId );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here. 
 */ 
void CTopBatteryAppUi::ConstructL()
	{
	iSettings= new (ELeave) CDesC16ArrayFlat(3);
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KFirstStartFile))
		{
		CEikonEnv::Static()->FsSession().Delete(KFirstStartFile);
		if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KSettingPath)){CEikonEnv::Static()->FsSession().Delete(KSettingPath);}
		}
	
	ReadSettings();
	ReadApps();
	// [[[ begin generated region: do not modify [Generated Contents]
	
	BaseConstructL( EAknEnableSkin ); 
	InitializeContainersL();
	// ]]] end generated region [Generated Contents]
	iWsSession=new (ELeave) RWsSession();
	iWsSession->Connect();
	iWinGroup=new (ELeave) RWindowGroup(*iWsSession);
	iWinGroup->Construct((TUint32)iWinGroup);
	iWinGroup->EnableReceiptOfFocus(EFalse);
	iWinGroup->SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront);
	
	iSprite= new (ELeave) RWsSprite(*iWsSession);
	iSprite->Construct(*iWinGroup,TPoint(0,0),0);
	iMember.iBitmap=NULL;
	iMember.iMaskBitmap=NULL;
	iMember.iOffset=TPoint(0,0);
	iMember.iInterval=TTimeIntervalMicroSeconds32(0);
	iMember.iInvertMask=EFalse; // black - not transparadent, white - transparadent
	iSprite->AppendMember(iMember);
	iSprite->SetPosition(TPoint(0,0));
	iSprite->Activate();
	CEikonEnv::Static()->WsSession().Flush();
	Show(EFalse);
	iScaler=CMyBitmapScaler::NewL(this);
	iObserver=CFgrObserver::NewL(*iWsSession,*this);
	iBattery=CBatteryCheck::NewL(*this);
	ScreenChanged();
	}

void CTopBatteryAppUi::ScreenChanged()
	{
	
	TInt scrX=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
	TInt scrY=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;
	_LOGDATA2(_L("ScreenChanged(%d,%d)"),scrX,scrY);
	TLex conv;
	TInt x,y;
	if (scrY>scrX)
		{
		conv.Assign(iSettings->MdcaPoint(0));
		conv.Val(x);
		conv.Assign(iSettings->MdcaPoint(1));
		conv.Val(y);
		}
	else
		{
		conv.Assign(iSettings->MdcaPoint(2));
		conv.Val(x);
		conv.Assign(iSettings->MdcaPoint(3));
		conv.Val(y);
		}
	iSprite->SetPosition(TPoint(x,y));
	CEikonEnv::Static()->WsSession().Flush();
	}
void CTopBatteryAppUi::GroupListChanged()
	{
	_LOG(_L("GroupListChanged()"));
	CApaWindowGroupName* gn = CApaWindowGroupName::NewL(*iWsSession, iWsSession->GetFocusWindowGroup());
	_LOGDATA(_L("Uid: %d"),gn->AppUid().iUid);
	if (iApps.Find(gn->AppUid())!=KErrNotFound){Show(ETrue);}
	else {Show(EFalse);}
	delete gn;
	}
void CTopBatteryAppUi::ChargerChanged(TInt aCharger)
	{
	_LOGDATA(_L("ChargerChanged(%d"),aCharger);
	}
void CTopBatteryAppUi::BatteryLevelL(TInt aBatteryLevel, TInt aStatus)
	{
	//if (aStatus<0){return;}
	if (iBitmap){delete iBitmap;}
	if (iMask){delete iMask;}
	_LOGDATA2(_L("BatteryLevelL(%d,%d)"),aBatteryLevel,aStatus);
	iBatteryLevel=aBatteryLevel;
	TBuf<255> pathfile,path;
	path.Copy(KSkinsPath);
	path.Append(iSettings->MdcaPoint(5));
	path.Append(_L("\\"));
	path.AppendNum(aBatteryLevel/14);
	
	pathfile.Copy(path);
	pathfile.Append(_L(".png"));
	iBitmap=GetPic(pathfile);
	pathfile.Copy(path);
	pathfile.Append(_L("m.png"));
	TLex conv(iSettings->MdcaPoint(4)); TInt percent; conv.Val(percent);
	iMask=GetPic(pathfile);
	iScaler->StartScale(percent,iBitmap,iMask);
	}
void CTopBatteryAppUi::ReadSettings()
	{
	TInt err=KErrNone;
	iSettings->Reset();
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KSettingPath)) //!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
		TBuf<255> val;
		RFile filesave;
		TBuf<10> t;
		TFileText ft;
		filesave.Open(CEikonEnv::Static()->FsSession(), KSettingPath, EFileRead);
		ft.Set(filesave);
		while (ft.Read(val)==KErrNone)
			{
			iSettings->AppendL(val);
			}
		filesave.Close();
		}
	else
		{
		TParse parse;
		CEikonEnv::Static()->FsSession().Parse(KSettingPath,parse);
		if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),parse.DriveAndPath()))
			{
			CEikonEnv::Static()->FsSession().MkDirAll(parse.DriveAndPath());
			}
		iSettings->AppendL(KPosXP);
		iSettings->AppendL(KPosYP);
		iSettings->AppendL(KPosXL);
		iSettings->AppendL(KPosYL);
		iSettings->AppendL(KZoom);
		iSettings->AppendL(KSkin);
		//WriteSettings();
		}
	}
void CTopBatteryAppUi::WriteSettings()
	{
		RFs iFS=CEikonEnv::Static()->FsSession();
		RFile filesave;
		TInt err1=filesave.Replace(iFS, KSettingPath, EFileWrite);
		TFileText ft;
		ft.Set(filesave);
		TInt i;
		for (i=0;i<iSettings->Count();i++)
			{
			ft.Write(iSettings->MdcaPoint(i));
			}
		filesave.Close();
	}
CFbsBitmap* CTopBatteryAppUi::GetPic(TDes& path)
	{
	_LOGDATA(_L("GetPic(%S)"),&path);
	if (!BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),path)){return NULL;}
	_LIT8(type,"image/png");
	CFbsBitmap* Bitmap;
	CImageDecoder* iImage=CImageDecoder::FileNewL(CCoeEnv::Static()->FsSession(),path,type,CImageDecoder::EOptionAlwaysThread);
	Bitmap = new (ELeave) CFbsBitmap();
	TFrameInfo iFrameInfo = iImage->FrameInfo(0);
	Bitmap->Create(iFrameInfo.iOverallSizeInPixels, iFrameInfo.iFrameDisplayMode );
	TRequestStatus ReqStat;
	iImage->Convert(&ReqStat,*Bitmap);
	User::WaitForRequest(ReqStat);
	delete iImage;
	return Bitmap;
	}
void CTopBatteryAppUi::Show(TBool aState)
	{
	_LOGDATA(_L("Show(%d)"),aState);
	iVisible=aState;
	if (aState)
		{
		iMember.iBitmap=iBitmap;
		iMember.iMaskBitmap=iMask;
		}
	else 
		{
		iMember.iBitmap=NULL;
		iMember.iMaskBitmap=NULL;
		}
	iSprite->UpdateMember(0,iMember);
	CEikonEnv::Static()->WsSession().Flush();
	}

void CTopBatteryAppUi::WriteApps()
	{
		CEikonEnv::Static()->InfoMsg(_L("CreatingFile"));
		RFs iFS=CEikonEnv::Static()->FsSession();
		RFile filesave;
		TInt err1=filesave.Replace(iFS, KExceptionsPath, EFileWrite);
		TFileText ft;
		ft.Set(filesave);
		TInt i;
		TBuf<255> t;
		CEikonEnv::Static()->InfoMsg(_L("StartWriting"));
		for (i=0;i<iApps.Count();i++)
			{
			t.Num(iApps[i].iUid,EHex);
			ft.Write(t);
			}
		filesave.Close();
		CEikonEnv::Static()->InfoMsg(_L("EndWriting"));
	}
void CTopBatteryAppUi::ReadApps()
	{
	TInt err=KErrNone;
	iApps.Reset();
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KExceptionsPath)) //!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
		TBuf<255> val;
		TLex conv;
		TUint32 IntVal;
		RFile filesave;
		TBuf<10> t;
		TFileText ft;
		filesave.Open(CEikonEnv::Static()->FsSession(), KExceptionsPath, EFileRead);
		ft.Set(filesave);
		while (ft.Read(val)==KErrNone)
			{
			conv.Assign(val);
			conv.Val(IntVal,EHex);
			iApps.AppendL(TUid::Uid(IntVal));
			}
		filesave.Close();
		}
	else
		{
		TParse parse;
		CEikonEnv::Static()->FsSession().Parse(KExceptionsPath,parse);
		if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),parse.DriveAndPath()))
			{
			CEikonEnv::Static()->FsSession().MkDirAll(parse.DriveAndPath());
			}
		}
	}
void CTopBatteryAppUi::UpdateSettings()
	{
	ScreenChanged();
	BatteryLevelL(iBatteryLevel,-1);
	}

TBool CTopBatteryAppUi::GlobalMsgQuery(TPtrC aText,TPtrC aHeader)
	{
	
	    TInt queryAnswer = 1;
	    char* querystr = NULL;
	    int querystr_l = 0;
	    char* headerstr = NULL;
	    int headerstr_l = 0;
	    TRequestStatus msgQueryStatus = KRequestPending;
	    TRequestStatus timerStatus = KRequestPending;
	    int delayInSeconds = 0;
	    TInt timeout = 0;
	    
	    TTimeIntervalMicroSeconds32 timeoutValue = TTimeIntervalMicroSeconds32(timeout);

	    CAknGlobalMsgQuery *msgQueryDialog = NULL;
	    
	    TRAPD(err,
	        {
	            msgQueryDialog = CAknGlobalMsgQuery::NewL();
	        });
	    CleanupStack::PushL(msgQueryDialog);
	    TRAPD(err1,
	        {
	            msgQueryDialog->ShowMsgQueryL(msgQueryStatus,aText,R_AVKON_SOFTKEYS_OK_CANCEL,aHeader, KNullDesC);
	        });
	    if(err1 != KErrNone||err!=KErrNone){
	       CleanupStack::PopAndDestroy(msgQueryDialog);
	    } 
		User::WaitForRequest(msgQueryStatus);
	    
	    CleanupStack::PopAndDestroy(msgQueryDialog);
	    return msgQueryStatus.Int() == EAknSoftkeyOk ? 1 : 0;		
	}

TBool CTopBatteryAppUi::ProcessCommandParametersL( CApaCommandLine &aCommandLine )
   {
   if(aCommandLine.OpaqueData().Length() > 0)
     {
     }
   else
     {
     CEikonEnv::Static()->RootWin().SetOrdinalPosition(-4);
     }
   return CEikAppUi::ProcessCommandParametersL( aCommandLine );
   }

void CTopBatteryAppUi::Completed(TInt aErr)
	{
	iBitmap=iScaler->GetBitmap();
	iMask=iScaler->GetMask();
	_LOGDATA(_L("Error: %d"),aErr);
	_LOGDATA2(_L("Size after: %d,%d"),iBitmap->SizeInPixels().iWidth,iBitmap->SizeInPixels().iHeight);
	Show(iVisible);
	}

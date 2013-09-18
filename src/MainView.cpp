/*
========================================================================
 Name        : MainView.cpp
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
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <TopBattery.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "TopBattery.hrh"
#include "MainView.h"
#include "Main.hrh"
#include "Main.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

#include <aknquerydialog.h>
#include <const.h>
#include <aknselectionlist.h>
#include <aknlistquerydialog.h>
#include <apgcli.h>
#include <TopBatteryAppUi.h>

struct TApplicationInfo
{
	TFileName iCaption;
	TUid iUid;
	static TInt Compare(const TApplicationInfo& aInfo1, const TApplicationInfo& aInfo2)
	{
		return aInfo1.iCaption.CompareC(aInfo2.iCaption);
	}
};



CMainView::CMainView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iMain = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CMainView::~CMainView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iMain;
	iMain = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CMainView
 */
CMainView* CMainView::NewL()
	{
	CMainView* self = CMainView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CMainView
 */
CMainView* CMainView::NewLC()
	{
	CMainView* self = new ( ELeave ) CMainView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CMainView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_MAIN_MAIN_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CMainView::Id() const
	{
	return TUid::Uid( EMainViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CMainView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
	
		case EMainViewControlPaneRightId:
			commandHandled = Hide( aCommand );
			break;
		case EMainView_MenuItemCommand:
			commandHandled = Change( aCommand );
			break;
		case EMainView_MenuItem1Command:
			commandHandled = About( aCommand );
			break;
		case EMainView_MenuItem3Command:
			commandHandled = Exit( aCommand );
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == EMainViewControlPaneRightId )
			{
			AppUi()->HandleCommandL( EEikCmdExit );
			}
	
		}
	// ]]] end generated region [Generated Code]
	
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CMainView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iMain == NULL )
		{
		iMain = CreateContainerL();
		iMain->SetMopParent( this );
		AppUi()->AddToStackL( *this, iMain );
		} 
	// ]]] end generated region [Generated Contents]
	InitValues();
	}

/**
 */
void CMainView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iMain != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iMain );
		delete iMain;
		iMain = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CMainView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
	
	// this may fail, but we're not able to propagate exceptions here
	TVwsViewId view;
	AppUi()->GetActiveViewId( view );
	if ( view.iViewUid == Id() )
		{
		TInt result;
		TRAP( result, SetupStatusPaneL() );
		}
	
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}

// [[[ begin generated function: do not modify
void CMainView::SetupStatusPaneL()
	{
	// reset the context pane
	TUid contextPaneUid = TUid::Uid( EEikStatusPaneUidContext );
	CEikStatusPaneBase::TPaneCapabilities subPaneContext = 
		StatusPane()->PaneCapabilities( contextPaneUid );
	if ( subPaneContext.IsPresent() && subPaneContext.IsAppOwned() )
		{
		CAknContextPane* context = static_cast< CAknContextPane* > ( 
			StatusPane()->ControlL( contextPaneUid ) );
		context->SetPictureToDefaultL();
		}
	
	// setup the title pane
	TUid titlePaneUid = TUid::Uid( EEikStatusPaneUidTitle );
	CEikStatusPaneBase::TPaneCapabilities subPaneTitle = 
		StatusPane()->PaneCapabilities( titlePaneUid );
	if ( subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned() )
		{
		CAknTitlePane* title = static_cast< CAknTitlePane* >( 
			StatusPane()->ControlL( titlePaneUid ) );
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_MAIN_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CMainView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CMain::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CMain
 */
CMain* CMainView::CreateContainerL()
	{
	return CMain::NewL( ClientRect(), NULL, this );
	}

/** 
 * Handle the rightSoftKeyPressed event.
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Hide( TInt aCommand )
	{
	CEikonEnv::Static()->RootWin().SetOrdinalPosition(-4);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Change( TInt aCommand )
	{
	TInt i=iMain->ListBox()->CurrentItemIndex();
	HandleLBSelect(i);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::About( TInt aCommand )
	{
	TBuf<1024> header;
	CEikonEnv::Static()->ReadResource(header,R_ABOUT_HEADER);
	TBuf<1024> txt;
	CEikonEnv::Static()->ReadResource(txt,R_ABOUT_TEXT);
	txt.Append(_L("WMR R321502538916\nWMZ Z208634876649\nWMU U221598315212\nWME E234802202031\nYandex-Money: 41001686491180"));
	((CTopBatteryAppUi*)AppUi())->GlobalMsgQuery(txt,header);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Donate( TInt aCommand )
	{
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Exit( TInt aCommand )
	{
	AppUi()->Exit();
	return ETrue;
	}
void CMainView::HandleLBSelect(TInt aIndex)
	{
	TBuf<255> newVal;
	TBuf<255> currVal;
	TBuf<255> title(GetTitle(aIndex));
	if (aIndex==0||aIndex==1||aIndex==2||aIndex==3||aIndex==4)
		{
		currVal.Copy(((CTopBatteryAppUi*)AppUi())->iSettings->MdcaPoint(aIndex));
		TBuf<255> title(GetTitle(aIndex));
		TInt val; TLex conv(currVal);conv.Val(val);
		if(!NumberQuery(title,val)){return;}
		newVal.Num(val);
		ChangeItemSubtitle(aIndex,newVal);
		((CTopBatteryAppUi*)AppUi())->iSettings->Delete(aIndex);
		((CTopBatteryAppUi*)AppUi())->iSettings->InsertL(aIndex,newVal);
		((CTopBatteryAppUi*)AppUi())->WriteSettings();
		}
	if (aIndex==5)
		{
		TBuf<255> newVal;
		CDir* results=NULL;
		TBuf<255> title(GetTitle(aIndex));
		CDesC16Array* arr=new (ELeave) CDesC16ArrayFlat(3);
		TFindFile findFiles(CEikonEnv::Static()->FsSession());
		TBuf<5> mask(_L("*"));
		findFiles.FindWildByDir(mask,KSkinsPath,results);
		if (results==NULL){return;}
		for (TInt i=0; i<results->Count();i++)
			{
			if (((TEntry)(*results)[i]).IsDir())
				{arr->AppendL(((TEntry)(*results)[i]).iName);}
			}
		TInt val=PopupMenu(title,0,arr);
		if (val==-1){return;}
		newVal.Copy(arr->MdcaPoint(val));
		delete arr;
		ChangeItemSubtitle(aIndex,newVal);
		((CTopBatteryAppUi*)AppUi())->iSettings->Delete(aIndex);
		((CTopBatteryAppUi*)AppUi())->iSettings->InsertL(aIndex,newVal);
		((CTopBatteryAppUi*)AppUi())->WriteSettings();
		}
	if (aIndex==6)
		{
		SelectApps(title);
		((CTopBatteryAppUi*)AppUi())->WriteApps();
		}
	((CTopBatteryAppUi*)AppUi())->UpdateSettings();
	}

void CMainView::ChangeItemSubtitle(TInt aIndex,TDes16& aText)
	{
	TInt b=iMain->ListBox()->Model()->NumberOfItems();
	TBuf<255> prev = iMain->ListBox()->Model()->ItemText(aIndex);
	TChar a = '\t'; 
	TInt pos = prev.LocateReverse(a); 
	if (pos != KErrNotFound) 
		{	 
    TInt replace_length = prev.Length() - pos;
    prev.Delete(pos+1, replace_length); 
    prev.Insert(pos+1, aText); 
		}
	CDesCArray* itemArray = static_cast<CDesCArray*> (iMain->ListBox()->Model()->ItemTextArray());
	itemArray->Delete(aIndex);
	itemArray->InsertL(aIndex,prev);
	iMain->ListBox()->DrawNow();
	}

TInt CMainView::NumberQuery(TDes& aText,TInt& aNumber)
{
	CAknNumberQueryDialog* Dialog = CAknNumberQueryDialog::NewL(aNumber,CAknQueryDialog::ENoTone);
	Dialog->PrepareLC(R_NUMBER_QUERY);
	Dialog->SetPromptL(aText);
	return Dialog->RunLD();	
}
TBuf<255> CMainView::GetTitle(TInt aIndex)
	{
	TBuf<255> prev = iMain->ListBox()->Model()->ItemText(aIndex);
	TChar a = '\t';
	prev.Copy(prev.Right(prev.Length()-1));
	TInt pos = prev.Find(_L("\t"));
	return prev.Left(pos);
	}

TInt CMainView::PopupMenu(TDes& aTxt,TInt aDef,CDesCArray* itemList)
	{
	_LIT(KListItemFormat, "%S");
	CAknSinglePopupMenuStyleListBox* list = new(ELeave) CAknSinglePopupMenuStyleListBox;
	CleanupStack::PushL(list);
	CAknPopupList* popupList = CAknPopupList::NewL(list, R_AVKON_SOFTKEYS_OK_BACK, AknPopupLayouts::EMenuWindow);
	CleanupStack::PushL(popupList);    
	list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);
	list->CreateScrollBarFrameL(ETrue);
	list->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
		
	list->Model()->SetItemTextArray(itemList);
	list->Model()->SetOwnershipType(ELbmOwnsItemArray);
	list->ItemDrawer()->FormattedCellData()->EnableMarqueeL( ETrue );
	popupList->SetTitleL(aTxt);    
	CleanupStack::Pop();            // popuplist
	CleanupStack::Pop();	//list
	TBool popupOk = popupList->ExecuteLD();
	if (!popupOk)
		{
		return -1;
		}
	else 
		{
		TInt current=list->CurrentItemIndex();
		return current;
		}
	}
void CMainView::SelectApps(TDes& aTitle)
	{
	TInt sel=0;
		TInt def=0;
		TBuf<255> result;
		CDesCArray* itemList = new (ELeave) CDesCArrayFlat(3);
		CArrayFixFlat<TInt>* DefaultSelectedItemsList=new (ELeave) CArrayFixFlat<TInt>(3);
		TInt i=0;
		RApaLsSession AppSession;
		AppSession.Connect();
		RArray<TApplicationInfo> apps;
		TApaAppInfo appInfo;
		AppSession.GetAllApps();
		TBuf<255> UidTxt;
		while (AppSession.GetNextApp(appInfo)==KErrNone)
			{
			if (appInfo.iCaption.Length()<2){continue;}
			TApplicationInfo info;
			info.iCaption=appInfo.iCaption;
			info.iUid=appInfo.iUid;
			apps.Append(info);
			}
		AppSession.Close();
		TLinearOrder<TApplicationInfo> sortOrder(TApplicationInfo::Compare); 
		apps.Sort(sortOrder);
		for (TInt i=0;i<apps.Count();i++)
			{
			TBuf<255> item;
			item.Copy(_L("\t"));
			item.Append(apps[i].iCaption);
			if (((CTopBatteryAppUi*)AppUi())->iApps.Find(apps[i].iUid)!=KErrNotFound){DefaultSelectedItemsList->AppendL(i);}
			item.Append(_L(" ["));
			UidTxt.Num((TUint)apps[i].iUid.iUid,EHex);
			UidTxt.UpperCase();
			item.Append(UidTxt);
			item.Append(_L("]"));
			item.Append(_L("\t"));
			itemList->AppendL(item);
			}
	CAknMarkableListDialog* dlg=CAknMarkableListDialog::NewL(sel,DefaultSelectedItemsList,itemList,R_AVKON_DIALOG_EMPTY_MENUBAR);
	dlg->PrepareLC(R_TXT_UID_SELECTION_LIST);
	dlg->SetTitleL(aTitle);
	((CEikListBox*)dlg->Control(ESelectionListControl))->SetSelectionIndexesL(DefaultSelectedItemsList);
	((CAknSingleStyleListBox*)dlg->Control(ESelectionListControl))->ItemDrawer()->ColumnData()->EnableMarqueeL(ETrue);
	TInt popupOk=dlg->RunLD();

	if (!popupOk)
		{
		return;
		}
	else 
		{
		i=0;
		((CTopBatteryAppUi*)AppUi())->iApps.Reset();
		for (i=0; i<DefaultSelectedItemsList->Count(); i++)
			{
				TUint uid=apps[DefaultSelectedItemsList->At(i)].iUid.iUid;
				((CTopBatteryAppUi*)AppUi())->iApps.Append(TUid::Uid(uid));
			}
		}
	}
void CMainView::InitValues()
	{
	CDesC16Array* sets=((CTopBatteryAppUi*)AppUi())->iSettings;
	TBuf<255> val;
	for (TInt i=0;i<sets->Count();i++)
		{
		val.Copy(sets->MdcaPoint(i));
		ChangeItemSubtitle(i,val);
		}
	}

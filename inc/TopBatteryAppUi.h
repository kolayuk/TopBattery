/*
========================================================================
 Name        : TopBatteryAppUi.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
#ifndef TOPBATTERYAPPUI_H
#define TOPBATTERYAPPUI_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknviewappui.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CMainView;
// ]]] end generated region [Generated Forward Declarations]

#include <w32std.h>
#include <Fgrobserver.h>
#include <BatteryCheck.h>
#include <MyBitmapScaler.h>
/**
 * @class	CTopBatteryAppUi TopBatteryAppUi.h
 * @brief The AppUi class handles application-wide aspects of the user interface, including
 *        view management and the default menu, control pane, and status pane.
 */


class CTopBatteryAppUi : public CAknViewAppUi, public MFgrCallBack, public MBatteryObserver, public MBitmapScalerObserver
	{
public: 
	// constructor and destructor
	CTopBatteryAppUi();
	virtual ~CTopBatteryAppUi();
	void ConstructL();
	void Completed(TInt aErr);
	CMyBitmapScaler* iScaler;
	
public:
	// from CCoeAppUi
	TKeyResponse HandleKeyEventL(
				const TKeyEvent& aKeyEvent,
				TEventCode aType );

	// from CEikAppUi
	void HandleCommandL( TInt aCommand );
	void HandleResourceChangeL( TInt aType );

	// from CAknAppUi
	void HandleViewDeactivation( 
			const TVwsViewId& aViewIdToBeDeactivated, 
			const TVwsViewId& aNewlyActivatedViewId );
	RWsSprite* iSprite;
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMask;
	RWindowGroup* iWinGroup;
	RWsSession* iWsSession;
	TSpriteMember iMember;
	void GroupListChanged();
	void ScreenChanged();
	CFgrObserver* iObserver;
	CBatteryCheck* iBattery;
	TBool ProcessCommandParametersL( CApaCommandLine &aCommandLine );
	void BatteryLevelL(TInt aBatteryLevel, TInt aBatteryStatus);
	void ChargerChanged(TInt aChargerStatus);
	void ReadSettings();
	void WriteSettings();
	CDesC16Array* iSettings;
	RArray<TUid> iApps;
	CFbsBitmap* GetPic(TDes& aPath);
	TBool iVisible;
	void Show(TBool aState);
	void ReadApps();
	void WriteApps();
	void UpdateSettings();
	TInt iBatteryLevel;
	TBool GlobalMsgQuery(TPtrC aText,TPtrC aHeader);
private:
	void InitializeContainersL();
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CMainView* iMainView;
	// ]]] end generated region [Generated Instance Variables]
	
	
	// [[[ begin [User Handlers]
protected: 
	// ]]] end [User Handlers]
	
	};

#endif // TOPBATTERYAPPUI_H			

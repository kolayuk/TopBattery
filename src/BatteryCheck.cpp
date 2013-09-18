/*
 ============================================================================
 Name		: BatteryCheck.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2011

 Description : CBatteryCheck implementation
 ============================================================================
 */

#include "BatteryCheck.h"
 
CCharger::CCharger(CTelephony* aTelephony,MChargerCB& aCB)
    : CActive(EPriorityStandard),
      iTelephony(aTelephony),
      iIndicatorV1Pckg(iIndicatorV1), iCB(aCB)
    {
    //Constructor
 CActiveScheduler::Add(this);
    }
 
void CCharger::DetectCharger()
    {
    iTelephony->GetIndicator(iStatus, iIndicatorV1Pckg);
    SetActive();
    }
 
void CCharger::RunL()
    {
    if(iStatus==KErrNone)
       {
       if(iIndicatorV1.iCapabilities & CTelephony::KIndChargerConnected)
          {
          //We can detect when a charger is connected
          if(iIndicatorV1.iIndicator & CTelephony::KIndChargerConnected)
             {
               iCB.ChargerChanged(EChargerConnected);
             }
          else
             {
               iCB.ChargerChanged(EChargerNotConnected);
             }
          }
       else
          {
             iCB.ChargerChanged(EChargerUnknown);
          }
       iTelephony->NotifyChange(iStatus,CTelephony::EIndicatorChange,iIndicatorV1Pckg);
       SetActive();
       }
    
    }
 
//To cancel this asynchronous call
void CCharger::DoCancel()
    {
    iTelephony->CancelAsync(CTelephony::EGetIndicatorCancel);
    iTelephony->CancelAsync(CTelephony::EIndicatorChangeCancel);
    }

 
CBatteryCheck* CBatteryCheck::NewLC(MBatteryObserver& aObserver)
{
    CBatteryCheck* self = new (ELeave) CBatteryCheck(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}
 
CBatteryCheck* CBatteryCheck::NewL(MBatteryObserver& aObserver)
{
    CBatteryCheck* self = CBatteryCheck::NewLC(aObserver);
    CleanupStack::Pop(); // self;
    return self;
}
 
void CBatteryCheck::ConstructL(void)
{
    iTelephony = CTelephony::NewL();
    iCharger=new (ELeave) CCharger(iTelephony,*this);
    iCharger->DetectCharger();
    GetBatteryInfo();
}
 
CBatteryCheck::~CBatteryCheck()
{
    Cancel();
}
 
CBatteryCheck::CBatteryCheck(MBatteryObserver& aObserver)
: CActive(EPriorityStandard),iObserver(aObserver),iBatteryInfoV1Pckg(iBatteryInfoV1)
{
    CActiveScheduler::Add(this);
}
 
void CBatteryCheck::GetBatteryInfo()
{
    if(iTelephony && !IsActive())
    {
        iGettingBattery = EFalse;
        iTelephony->GetBatteryInfo(iStatus, iBatteryInfoV1Pckg);
        SetActive();
    }
}
 
void CBatteryCheck::RunL()
{
	iBatteryLevel=iBatteryInfoV1.iChargeLevel;
	iBatteryState=iBatteryInfoV1.iStatus;
    iObserver.BatteryLevelL(iBatteryLevel,iBatteryState);
 
    if(iStatus != KErrCancel)
    {
        iTelephony->NotifyChange(iStatus,CTelephony::EBatteryInfoChange,iBatteryInfoV1Pckg);
        SetActive();
    }
 
    iGettingBattery = EFalse;
}
 
void CBatteryCheck::DoCancel()
{
    if(iGettingBattery)
    iTelephony->CancelAsync(CTelephony::EGetBatteryInfoCancel);
    else
    iTelephony->CancelAsync(CTelephony::EBatteryInfoChangeCancel);
}
void CBatteryCheck::ChargerChanged(enum TChargerStatus aStatus)
	{
	iChargerState=aStatus;
	iObserver.ChargerChanged(aStatus);
	}

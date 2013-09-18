/*
 ============================================================================
 Name		: BatteryCheck.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2011

 Description : CBatteryCheck declaration
 ============================================================================
 */

#ifndef BATTERYCHECK_H
#define BATTERYCHECK_H

// INCLUDES
#include <Etel3rdParty.h>

enum TChargerStatus
	{
	EChargerNotConnected,
	EChargerConnected,
	EChargerUnknown
	};

class MChargerCB
	{
public:
	virtual void ChargerChanged(TChargerStatus aStatus)=0;
	};

class CCharger : public CActive
    {
private:
    CTelephony* iTelephony;
    CTelephony::TIndicatorV1 iIndicatorV1;
    CTelephony::TIndicatorV1Pckg iIndicatorV1Pckg;
public:
    CCharger(CTelephony* aTelephony,MChargerCB& aCB);
    void DetectCharger();
 
private:
    void RunL();
    void DoCancel();
    MChargerCB& iCB;
   };


class MBatteryObserver
{
    public:
        virtual void BatteryLevelL(TInt aBatteryLevel, TInt aBatteryStatus) = 0;
        virtual void ChargerChanged(TInt aChargerStatus)=0;
};
 
class CBatteryCheck : public CActive, public MChargerCB
{ 
    public:
        ~CBatteryCheck();
        static CBatteryCheck* NewL(MBatteryObserver& aObserver);
        static CBatteryCheck* NewLC(MBatteryObserver& aObserver);
        void ChargerChanged(TChargerStatus aStatus);
    private:
        CBatteryCheck(MBatteryObserver& aObserver);
        void ConstructL(void);
 
    private:
        void GetBatteryInfo();
        void RunL();
        void DoCancel();
 
    private:
        MBatteryObserver&               iObserver;
        CTelephony*                     iTelephony;
        CTelephony::TBatteryInfoV1      iBatteryInfoV1;
        CTelephony::TBatteryInfoV1Pckg  iBatteryInfoV1Pckg;
        TBool                           iGettingBattery;
        TInt							iBatteryLevel;
        TInt							iBatteryState;
        TInt							iChargerState;
        CCharger* 						iCharger;
};

#endif // BATTERYCHECK_H

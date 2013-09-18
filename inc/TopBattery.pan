
#ifndef TOPBATTERY_PAN_H
#define TOPBATTERY_PAN_H

/** TopBattery application panic codes */
enum TTopBatteryPanics
	{
	ETopBatteryUi = 1
	// add further panics here
	};

inline void Panic(TTopBatteryPanics aReason)
	{
	_LIT(applicationName,"TopBattery");
	User::Panic(applicationName, aReason);
	}

#endif // TOPBATTERY_PAN_H

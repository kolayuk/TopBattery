/*
========================================================================
 Name        : TopBatteryApplication.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
#ifndef TOPBATTERYAPPLICATION_H
#define TOPBATTERYAPPLICATION_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknapp.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Constants]
const TUid KUidTopBatteryApplication = { 0xE3E97C30 };
// ]]] end generated region [Generated Constants]

/**
 *
 * @class	CTopBatteryApplication TopBatteryApplication.h
 * @brief	A CAknApplication-derived class is required by the S60 application 
 *          framework. It is subclassed to create the application's document 
 *          object.
 */
class CTopBatteryApplication : public CAknApplication
	{
private:
	TUid AppDllUid() const;
	CApaDocument* CreateDocumentL();
	
	};
			
#endif // TOPBATTERYAPPLICATION_H		

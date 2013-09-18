/*
========================================================================
 Name        : TopBatteryDocument.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
#ifndef TOPBATTERYDOCUMENT_H
#define TOPBATTERYDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CTopBatteryDocument TopBatteryDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CTopBatteryDocument : public CAknDocument
	{
public: 
	// constructor
	static CTopBatteryDocument* NewL( CEikApplication& aApp );
	void UpdateTaskNameL(CApaWindowGroupName* aWg);
private: 
	// constructors
	CTopBatteryDocument( CEikApplication& aApp );
	void ConstructL();
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // TOPBATTERYDOCUMENT_H

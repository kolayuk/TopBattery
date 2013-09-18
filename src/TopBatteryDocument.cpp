/*
========================================================================
 Name        : TopBatteryDocument.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "TopBatteryDocument.h"
#include "TopBatteryAppUi.h"
// ]]] end generated region [Generated User Includes]
#include <apgwgnam.h>
/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CTopBatteryDocument::CTopBatteryDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CTopBatteryDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CTopBatteryDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CTopBatteryDocument
 */
CTopBatteryDocument* CTopBatteryDocument::NewL( CEikApplication& aApp )
	{
	CTopBatteryDocument* self = new ( ELeave ) CTopBatteryDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CTopBatteryDocument::CreateAppUiL()
	{
	return new ( ELeave ) CTopBatteryAppUi;
	}
void CTopBatteryDocument::UpdateTaskNameL(CApaWindowGroupName* aWg)
	{
	CAknDocument::UpdateTaskNameL(aWg);
	aWg->SetHidden(ETrue);
	aWg->SetSystem(ETrue);
	}

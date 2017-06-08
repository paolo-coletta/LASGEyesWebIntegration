#include "stdafx.h"
#include "resource.h"
#include "Signature.h"

using namespace Eyw;

static catalog_class_registrant gCatalog( 
	catalog_class_registrant::catalog_id( EYW_LASGTUTORIAL_CATALOG_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "Catalog Name" )
			.description( "Catalog Description" )
			.bitmap( IDB_LASGTUTORIAL_CATALOG )
		.end_language()	
	);

static company_registrant gCompany( 
	company_registrant::company_id( EYW_LASGTUTORIAL_COMPANY_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "LASG" )
			.description( "Company Description" )
		.end_language()	
	);

static licence_registrant gLicense( 
	licence_registrant::licence_id( EYW_LASGTUTORIAL_LICENSE_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "LASGTutorial Licence" )
			.description( "This catalog has the same license of EyesWeb XMI" )
		.end_language()	
	);

static author_registrant gAuthor( 
	author_registrant::author_id( EYW_LASGTUTORIAL_CATALOG_AUTHOR_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "Paolo" )
			.description( "Author Description" )
		.end_language()	
	);



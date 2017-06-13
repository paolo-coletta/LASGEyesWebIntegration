#include "stdafx.h"
#include "resource.h"
#include "Signature.h"

using namespace Eyw;

static catalog_class_registrant gCatalog( 
	catalog_class_registrant::catalog_id( EYW_LASG_CATALOG_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "LASG" )
			.description( "LASG Simulator" )
			.bitmap( IDB_LASG_CATALOG )
		.end_language()	
	);

static company_registrant gCompany( 
	company_registrant::company_id( EYW_LASG_COMPANY_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "Casa Paganini InfoMus" )
			.description( "www.casapaganini.org" )
		.end_language()	
	);

static licence_registrant gLicense( 
	licence_registrant::licence_id( EYW_LASG_LICENSE_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "LASG Licence" )
			.description( "This catalog has the same license of EyesWeb XMI" )
		.end_language()	
	);

static author_registrant gAuthor( 
	author_registrant::author_id( EYW_LASG_CATALOG_AUTHOR_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "Paolo Coletta" )
			.description( "paolo.coletta@gmail.com" )
		.end_language()	
	);



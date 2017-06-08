#include "stdafx.h"
#include "Tutorial1.h"
#include "Signature.h"
#include "resource.h"

using namespace Eyw;

//////////////////////////////////////////////////////////
/// <summary>
/// Block Signature.
/// </summary>
Eyw::block_class_registrant g_Tutorial1( 
	Eyw::block_class_registrant::block_id( "Tutorial1" )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "Tutorial1" )
			.description( "Demo"	)
			.libraries( "LASG.Tutorial" )
			.bitmap( IDB_TUTORIAL1_BITMAP )
		.end_language()	
		.begin_authors()
			.author( EYW_LASGTUTORIAL_CATALOG_AUTHOR_ID )
		.end_authors()
		.begin_companies()
			.company( EYW_LASGTUTORIAL_COMPANY_ID )
		.end_companies()
		.begin_licences()
			.licence( EYW_LASGTUTORIAL_LICENSE_ID )
		.end_licences()
		.default_factory< CTutorial1 >()
	);

//////////////////////////////////////////////////////////
// Identifiers
#define IN_STRING "string"
#define OUT_OUTPUT1 "output1"
#define OUT_OUTPUT2 "output2"
#define OUT_OUTPUT3 "output3"
#define OUT_OUTPUT4 "output4"


//////////////////////////////////////////////////////////
/// <summary>
/// Constructor.
/// </summary>
//////////////////////////////////////////////////////////
CTutorial1::CTutorial1( const Eyw::OBJECT_CREATIONCTX* ctxPtr )
:	Eyw::CBlockImpl( ctxPtr )
{
	m_inStringPtr=NULL;
	m_outOutput1Ptr=NULL;
	m_outOutput2Ptr=NULL;
	m_outOutput3Ptr=NULL;
	m_outOutput4Ptr=NULL;

	_schedulingInfoPtr->SetActivationEventBased( true );
	_schedulingInfoPtr->GetEventBasedActivationInfo()->SetActivationOnInputChanged( IN_STRING, true );

}

//////////////////////////////////////////////////////////
/// <summary>	
/// Destructor.
/// </summary>
//////////////////////////////////////////////////////////
CTutorial1::~CTutorial1()
{
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature initialization.
/// </summary>
//////////////////////////////////////////////////////////
void CTutorial1::InitSignature()
{	 
	SetInput(Eyw::pin::id(IN_STRING)
	    .name("string")
	    .description("String from serial")
	    .type<Eyw::IString>()
	    );
	SetOutput(Eyw::pin::id(OUT_OUTPUT1)
	    .name("output1")
	    .description("Output1")
	    .type<Eyw::IString>()
	    );
	SetOutput(Eyw::pin::id(OUT_OUTPUT2)
	    .name("output2")
	    .description("Output 2")
	    .type<Eyw::IString>()
	    );
	SetOutput(Eyw::pin::id(OUT_OUTPUT3)
	    .name("output3")
	    .description("Output3")
	    .type<Eyw::IString>()
	    );
	SetOutput(Eyw::pin::id(OUT_OUTPUT4)
	    .name("output4")
	    .description("output4")
	    .type<Eyw::IString>()
	    );

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature check.
/// </summary>
//////////////////////////////////////////////////////////
void CTutorial1::CheckSignature()
{
	_signaturePtr->GetInputs()->FindItem( IN_STRING );
	_signaturePtr->GetOutputs()->FindItem( OUT_OUTPUT1 );
	_signaturePtr->GetOutputs()->FindItem( OUT_OUTPUT2 );
	_signaturePtr->GetOutputs()->FindItem( OUT_OUTPUT3 );
	_signaturePtr->GetOutputs()->FindItem( OUT_OUTPUT4 );

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature deinitialization.
/// </summary>
//////////////////////////////////////////////////////////
void CTutorial1::DoneSignature()
{

}

/// Block Actions

//////////////////////////////////////////////////////////
/// <summary>
/// Block initialization action.
/// </summary>
/// <returns>
/// true if success, otherwise false.
/// </returns>
//////////////////////////////////////////////////////////
bool CTutorial1::Init() throw()
{
    try
    {
		/// TODO: Init data structures here 

		m_inStringPtr = get_input_datatype<Eyw::IString>( IN_STRING );
		m_outOutput1Ptr = get_output_datatype<Eyw::IString>( OUT_OUTPUT1 );
		m_outOutput2Ptr = get_output_datatype<Eyw::IString>( OUT_OUTPUT2 );
		m_outOutput3Ptr = get_output_datatype<Eyw::IString>( OUT_OUTPUT3 );
		m_outOutput4Ptr = get_output_datatype<Eyw::IString>( OUT_OUTPUT4 );

    	return true;
    }
    catch(...)
    {
        return false;
    }
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block start action.
/// </summary>
/// <returns>
/// true if success, otherwise false.
/// </returns>
//////////////////////////////////////////////////////////
bool CTutorial1::Start() throw()
{
    try
    {
    }
    catch(...)
    {
        return false;
    }
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block execution action.
/// </summary>
/// <returns>
/// true if success, otherwise false.
/// </returns>
//////////////////////////////////////////////////////////
bool CTutorial1::Execute() throw()
{
    try
    {

		std::string in = m_inStringPtr->GetValue();

		std::vector<std::string> strs;
		boost::split(strs, in, boost::is_any_of(","));
		if (strs.size() != 4) {
			Notify_ErrorString("The input string %s shoudl be in the form X1,X2,X3,X4\n", in.c_str() );
			return false;
		}

		TIME time = _clockPtr->GetTime();
		m_outOutput1Ptr->SetValue(strs[0].c_str());
		m_outOutput1Ptr->SetCreationTime(time);

		m_outOutput2Ptr->SetValue(strs[1].c_str());
		m_outOutput2Ptr->SetCreationTime(time);

		m_outOutput3Ptr->SetValue(strs[2].c_str());
		m_outOutput3Ptr->SetCreationTime(time);

		m_outOutput4Ptr->SetValue(strs[3].c_str());
		m_outOutput4Ptr->SetCreationTime(time);


		return true;
    }
    catch(...)
    {
    }
	return true;
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block stop action.
/// </summary>
//////////////////////////////////////////////////////////
void CTutorial1::Stop() throw()
{
    try
    {
    }
    catch(...)
    {
    }
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block deinitialization action.
/// </summary>
//////////////////////////////////////////////////////////
void CTutorial1::Done() throw()
{
    try
    {
		m_inStringPtr = NULL;
		m_outOutput1Ptr = NULL;
		m_outOutput2Ptr = NULL;
		m_outOutput3Ptr = NULL;
		m_outOutput4Ptr = NULL;

    }
    catch(...)
    {
    }
}

/// optionals

//////////////////////////////////////////////////////////
/// <summary>
/// Manage the ChangedParameter event.
/// </summary>
/// <param name="csParameterID">
/// [in] id of the changed parameter.
/// </param>
//////////////////////////////////////////////////////////
void CTutorial1::OnChangedParameter( const std::string& csParameterID )
{
	/// TODO: manage the changed parameters
}

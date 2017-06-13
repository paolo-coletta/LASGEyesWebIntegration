#include "stdafx.h"
#include "IRSensor.h"
#include "Signature.h"
#include "resource.h"

using namespace Eyw;

//////////////////////////////////////////////////////////
/// <summary>
/// Block Signature.
/// </summary>
Eyw::block_class_registrant s_IRSensor( 
	Eyw::block_class_registrant::block_id( "IRSensor" )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "IRSensor" )
			.description( "L"	)
			.libraries( "LASG.Sensors" )
			.bitmap( IDB_IRSENSOR_BITMAP )
		.end_language()	
		.begin_authors()
			.author( EYW_LASG_CATALOG_AUTHOR_ID )
		.end_authors()
		.begin_companies()
			.company( EYW_LASG_COMPANY_ID )
		.end_companies()
		.begin_licences()
			.licence( EYW_LASG_LICENSE_ID )
		.end_licences()
		.default_factory< CIRSensor >()
	);

//////////////////////////////////////////////////////////
// Identifiers
#define PAR_X0 "x0"
#define IN_USER "user"
#define OUT_IR "ir"


//////////////////////////////////////////////////////////
/// <summary>
/// Constructor.
/// </summary>
//////////////////////////////////////////////////////////
CIRSensor::CIRSensor( const Eyw::OBJECT_CREATIONCTX* ctxPtr )
:	Eyw::CBlockImpl( ctxPtr )
{
	m_inputUserPtr=NULL;
	m_measuredIRPtr=NULL;

	_schedulingInfoPtr->SetActivationEventBased( true );
	_schedulingInfoPtr->GetEventBasedActivationInfo()->SetActivationOnInputChanged(IN_USER, true);

}

//////////////////////////////////////////////////////////
/// <summary>	
/// Destructor.
/// </summary>
//////////////////////////////////////////////////////////
CIRSensor::~CIRSensor()
{
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature initialization.
/// </summary>
//////////////////////////////////////////////////////////
void CIRSensor::InitSignature()
{	 
	SetParameter(
		Eyw::pin::id(PAR_X0)
			.name("X0")
			.description("Initial state")
			.type<Eyw::IDouble>()
		);
	m_initialStatePtr = get_parameter_datatype<Eyw::IDouble>(PAR_X0);
	m_initialStatePtr->SetValue(1.0);

	SetInput(
		Eyw::pin::id(IN_USER)
			.name("user")
			.description("User presence (0.0 or 1.0 for now)")
			.set_double_domain()
				.min(0.0)
	    );

	SetOutput(
		Eyw::pin::id(OUT_IR)
			.name("ir")
			.description("Measured infrared")
			.type<Eyw::IDouble>()
	    );

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature check.
/// </summary>
//////////////////////////////////////////////////////////
void CIRSensor::CheckSignature()
{
	m_initialStatePtr = get_parameter_datatype<Eyw::IDouble>(PAR_X0);
	get_input(IN_USER);
	get_output(OUT_IR);

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature deinitialization.
/// </summary>
//////////////////////////////////////////////////////////
void CIRSensor::DoneSignature()
{
	m_initialStatePtr = NULL;
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
bool CIRSensor::Init() throw()
{
    try
    {
		/// TODO: Init data structures here 

		m_inputUserPtr = get_input_datatype<Eyw::IDouble>(IN_USER);
		m_measuredIRPtr = get_output_datatype<Eyw::IDouble>(OUT_IR);

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
bool CIRSensor::Start() throw()
{
    try
    {
    	/// TODO: add your logic
    	return true;
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
bool CIRSensor::Execute() throw()
{
	const Eyw::TIME time = _clockPtr->GetTime();
	const double user = m_inputUserPtr->GetValue();
	const double U = (user > 0.0) ? 1.0 : 0.0;

	m_measuredIRPtr->SetValue(U);
	m_measuredIRPtr->SetCreationTime(time);

	return true;
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block stop action.
/// </summary>
//////////////////////////////////////////////////////////
void CIRSensor::Stop() throw()
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
void CIRSensor::Done() throw()
{
    try
    {
		m_inputUserPtr = NULL;
		m_measuredIRPtr = NULL;

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
void CIRSensor::OnChangedParameter( const std::string& csParameterID )
{
	/// TODO: manage the changed parameters
}

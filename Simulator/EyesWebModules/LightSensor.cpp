#include "stdafx.h"
#include "LightSensor.h"
#include "Signature.h"
#include "resource.h"

using namespace Eyw;

//////////////////////////////////////////////////////////
/// <summary>
/// Block Signature.
/// </summary>
Eyw::block_class_registrant s_lightSensor( 
	Eyw::block_class_registrant::block_id( "LightSensor" )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "LightSensor" )
			.description( "L"	)
			.libraries( "LASG.Sensors" )
			.bitmap( IDB_LIGHTSENSOR_BITMAP )
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
		.default_factory< CLightSensor >()
	);

//////////////////////////////////////////////////////////
// Identifiers
#define PAR_K "k"
#define PAR_X0 "x0"
#define IN_LIGHT "light"
#define OUT_LIGHT "light"


//////////////////////////////////////////////////////////
/// <summary>
/// Constructor.
/// </summary>
//////////////////////////////////////////////////////////
CLightSensor::CLightSensor( const Eyw::OBJECT_CREATIONCTX* ctxPtr )
:	Eyw::CBlockImpl( ctxPtr )
{
	m_inputLightPtr=NULL;
	m_measuredLightPtr=NULL;

	_schedulingInfoPtr->SetActivationEventBased( true );
	_schedulingInfoPtr->GetEventBasedActivationInfo()->SetActivationOnInputChanged( IN_LIGHT, true );

}

//////////////////////////////////////////////////////////
/// <summary>	
/// Destructor.
/// </summary>
//////////////////////////////////////////////////////////
CLightSensor::~CLightSensor()
{
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature initialization.
/// </summary>
//////////////////////////////////////////////////////////
void CLightSensor::InitSignature()
{	 
	SetParameter(
		Eyw::pin::id(PAR_K)
			.name("K")
			.description("Measurement coefficent K")
			.type<Eyw::IDouble>()
		);
	m_measureCoeffPtr = get_parameter_datatype<Eyw::IDouble>(PAR_K);
	m_measureCoeffPtr->SetValue(1.0);

	SetParameter(
		Eyw::pin::id(PAR_X0)
			.name("X0")
			.description("Initial state")
			.type<Eyw::IDouble>()
		);
	m_initialStatePtr = get_parameter_datatype<Eyw::IDouble>(PAR_X0);
	m_initialStatePtr->SetValue(1.0);

	SetInput(
		Eyw::pin::id(IN_LIGHT)
			.name("light")
			.description("Input light (ignored for now, just used as an activation trigger)")
			.set_double_domain()
				.min(0.0)
	    );

	SetOutput(
		Eyw::pin::id(OUT_LIGHT)
			.name("light")
			.description("Measured light")
			.type<Eyw::IDouble>()
	    );

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature check.
/// </summary>
//////////////////////////////////////////////////////////
void CLightSensor::CheckSignature()
{
	m_measureCoeffPtr = get_parameter_datatype<Eyw::IDouble>(PAR_K);
	m_initialStatePtr = get_parameter_datatype<Eyw::IDouble>(PAR_X0);
	_signaturePtr->GetInputs()->FindItem(IN_LIGHT);
	_signaturePtr->GetOutputs()->FindItem( OUT_LIGHT );

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature deinitialization.
/// </summary>
//////////////////////////////////////////////////////////
void CLightSensor::DoneSignature()
{
	m_measureCoeffPtr = NULL;
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
bool CLightSensor::Init() throw()
{
    try
    {
		/// TODO: Init data structures here 

		m_inputLightPtr = get_input_datatype<Eyw::IDouble>(IN_LIGHT);
		m_measuredLightPtr = get_output_datatype<Eyw::IDouble>(OUT_LIGHT);

		m_light = m_initialStatePtr->GetValue();

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
bool CLightSensor::Start() throw()
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
bool CLightSensor::Execute() throw()
{
	const Eyw::TIME time = _clockPtr->GetTime();
	const double k = m_measureCoeffPtr->GetValue();

	m_measuredLightPtr->SetValue(k * m_light);
	m_measuredLightPtr->SetCreationTime(time);

	return true;
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block stop action.
/// </summary>
//////////////////////////////////////////////////////////
void CLightSensor::Stop() throw()
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
void CLightSensor::Done() throw()
{
    try
    {
		m_inputLightPtr = NULL;
		m_measuredLightPtr = NULL;

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
void CLightSensor::OnChangedParameter( const std::string& csParameterID )
{
	/// TODO: manage the changed parameters
}

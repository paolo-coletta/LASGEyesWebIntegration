#include "stdafx.h"
#include "SMA.h"
#include "Signature.h"
#include "resource.h"

using namespace Eyw;

//////////////////////////////////////////////////////////
/// <summary>
/// Block Signature.
/// </summary>
Eyw::block_class_registrant g_SMA( 
	Eyw::block_class_registrant::block_id( "SMA" )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "SMA" )
			.description( "SMA"	)
			.libraries( "LASG" )
			.bitmap( IDB_SMA_BITMAP )
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
		.default_factory< CSMA >()
	);

//////////////////////////////////////////////////////////
// Identifiers
#define PAR_TAU "tau"
#define PAR_INITIAL_STATE "initial_state"
#define PAR_DELTA_T "delta_t"
#define IN_INPUT "input"
#define OUT_OUTPUT "output"


//////////////////////////////////////////////////////////
/// <summary>
/// Constructor.
/// </summary>
//////////////////////////////////////////////////////////
CSMA::CSMA( const Eyw::OBJECT_CREATIONCTX* ctxPtr )
:	Eyw::CBlockImpl( ctxPtr )
{
	m_inInputPtr=NULL;
	m_outOutputPtr=NULL;

	_schedulingInfoPtr->SetActivationEventBased( true );
	_schedulingInfoPtr->GetEventBasedActivationInfo()->SetActivationOnInputChanged( IN_INPUT, true );

}

//////////////////////////////////////////////////////////
/// <summary>	
/// Destructor.
/// </summary>
//////////////////////////////////////////////////////////
CSMA::~CSMA()
{
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature initialization.
/// </summary>
//////////////////////////////////////////////////////////
void CSMA::InitSignature()
{	 
	SetParameter(
		Eyw::pin::id(PAR_TAU)
	        .name("tau")
	        .description("speed")
	        .type<Eyw::IDouble>()
		);
	m_parTauPtr = get_parameter_datatype<IDouble>(PAR_TAU);
	m_parTauPtr->SetValue(2.0);

	SetParameter(
		Eyw::pin::id(PAR_DELTA_T)
		.name("DeltaT")
		.description("Time step")
		.type<Eyw::IDouble>()
		);
	m_parDeltaTPtr = get_parameter_datatype<IDouble>(PAR_DELTA_T);
	m_parDeltaTPtr->SetValue(0.1);

	SetParameter(
		Eyw::pin::id(PAR_INITIAL_STATE)
		.name("initial state")
		.description("initial state")
		.type<Eyw::IDouble>()
		);
	m_parInitialStatePtr = get_parameter_datatype<IDouble>(PAR_INITIAL_STATE);
	m_parInitialStatePtr->SetValue(0.0);

	SetInput(Eyw::pin::id(IN_INPUT)
	    .name("input")
	    .description("Forced input")
	    .type<Eyw::IDouble>()
	    );
	SetOutput(Eyw::pin::id(OUT_OUTPUT)
	    .name("output")
	    .description("System response")
	    .type<Eyw::IDouble>()
	    );

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature check.
/// </summary>
//////////////////////////////////////////////////////////
void CSMA::CheckSignature()
{
	m_parTauPtr=get_parameter_datatype<Eyw::IDouble>(PAR_TAU);
	m_parInitialStatePtr = get_parameter_datatype<IDouble>(PAR_INITIAL_STATE);
	m_parDeltaTPtr = get_parameter_datatype<IDouble>(PAR_DELTA_T);
	_signaturePtr->GetInputs()->FindItem(IN_INPUT);
	_signaturePtr->GetOutputs()->FindItem( OUT_OUTPUT );

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature deinitialization.
/// </summary>
//////////////////////////////////////////////////////////
void CSMA::DoneSignature()
{
	m_parTauPtr=NULL;
	m_parInitialStatePtr = NULL;
	m_parDeltaTPtr = NULL;
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
bool CSMA::Init() throw()
{
    try
    {
		/// TODO: Init data structures here 

		m_inInputPtr = get_input_datatype<Eyw::IDouble>( IN_INPUT );
		m_outOutputPtr = get_output_datatype<Eyw::IDouble>( OUT_OUTPUT );
		m_state = m_parInitialStatePtr->GetValue();

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
bool CSMA::Start() throw()
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
bool CSMA::Execute() throw()
{
    try
    {
		const double tau = m_parTauPtr->GetValue();
		if (tau != 0.0) {
			const double deltaT = m_parDeltaTPtr->GetValue();
			const double input = m_inInputPtr->GetValue();
			const TIME time = _clockPtr->GetTime();
			m_state += deltaT * ( (input - m_state) / tau );

			m_outOutputPtr->SetValue(m_state);
			m_outOutputPtr->SetCreationTime(time);
		}
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
void CSMA::Stop() throw()
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
void CSMA::Done() throw()
{
    try
    {
		m_inInputPtr = NULL;
		m_outOutputPtr = NULL;

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
void CSMA::OnChangedParameter( const std::string& csParameterID )
{
	/// TODO: manage the changed parameters
}

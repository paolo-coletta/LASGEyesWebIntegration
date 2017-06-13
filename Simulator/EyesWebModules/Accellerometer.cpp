#include "stdafx.h"
#include "Accellerometer.h"
#include "Signature.h"
#include "resource.h"

using namespace Eyw;

//////////////////////////////////////////////////////////
/// <summary>
/// Block Signature.
/// </summary>
Eyw::block_class_registrant s_accellerometer( 
	Eyw::block_class_registrant::block_id( "accellerometer" )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "Accellerometer" )
			.description( "L"	)
			.libraries( "LASG.Sensors" )
			.bitmap( IDB_ACCELLEROMETER_BITMAP )
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
		.default_factory< CAccellerometer >()
	);

//////////////////////////////////////////////////////////
// Identifiers
#define PAR_ALFA_MIN "alfa_min"
#define PAR_ALFA_MAX "alfa_max"
#define PAR_BETA_MIN "beta_min"
#define PAR_BETA_MAX "beta_max"
#define PAR_G "g"
#define IN_USER "user"
#define IN_THETA "theta"
#define OUT_ACCELLERATION "accelleration"


//////////////////////////////////////////////////////////
/// <summary>
/// Constructor.
/// </summary>
//////////////////////////////////////////////////////////
CAccellerometer::CAccellerometer( const Eyw::OBJECT_CREATIONCTX* ctxPtr )
:	Eyw::CBlockImpl( ctxPtr )
{
	_schedulingInfoPtr->SetActivationEventBased( true );
	_schedulingInfoPtr->GetEventBasedActivationInfo()->SetActivationOnInputChanged(IN_THETA, true);

}

//////////////////////////////////////////////////////////
/// <summary>	
/// Destructor.
/// </summary>
//////////////////////////////////////////////////////////
CAccellerometer::~CAccellerometer()
{
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature initialization.
/// </summary>
//////////////////////////////////////////////////////////
void CAccellerometer::InitSignature()
{	 

	double_matrix_init_info_ptr initInfoPtr = datatype_init_info<IDoubleMatrixInitInfo>::create(_kernelServicesPtr);
	initInfoPtr->_numRows = 3;
	initInfoPtr->_numColumns = 1;

	SetParameter(
		Eyw::pin::id(PAR_ALFA_MIN)
			.name("alfa min")
			.description("Minimum value of alfa, in degrees")
			.type<Eyw::IDouble>()
		);
	m_alfaMinPtr = get_parameter_datatype<Eyw::IDouble>(PAR_ALFA_MIN);
	m_alfaMinPtr->SetValue(-30.0);

	SetParameter(
		Eyw::pin::id(PAR_ALFA_MAX)
		.name("alfa max")
		.description("Maximum value of alfa, in degrees")
		.type<Eyw::IDouble>()
		);
	m_alfaMaxPtr = get_parameter_datatype<Eyw::IDouble>(PAR_ALFA_MIN);
	m_alfaMaxPtr->SetValue(30.0);

	SetParameter(
		Eyw::pin::id(PAR_BETA_MIN)
		.name("beta min")
		.description("Minimum value of beta, in degrees")
		.type<Eyw::IDouble>()
		);
	m_betaMinPtr = get_parameter_datatype<Eyw::IDouble>(PAR_BETA_MIN);
	m_betaMinPtr->SetValue(-30.0);

	SetParameter(
		Eyw::pin::id(PAR_BETA_MAX)
		.name("beta max")
		.description("Maximum value of beta, in degrees")
		.type<Eyw::IDouble>()
		);
	m_betaMaxPtr = get_parameter_datatype<Eyw::IDouble>(PAR_BETA_MAX);
	m_betaMaxPtr->SetValue(30.0);

	std::array<double, 3> g = { 0.0, 0.0, 9.8 };
	SetParameter(
		Eyw::pin::id(PAR_G)
			.name("G")
			.description("Gravity vector")
			.type<Eyw::IDoubleMatrix>()
			.init_info_ptr(initInfoPtr.get())
		);
	m_gravityVectorPtr = get_parameter_datatype<Eyw::IDoubleMatrix>(PAR_G);
	m_gravityVectorPtr->SetValues(g.data());

	SetInput(
		Eyw::pin::id(IN_THETA)
		.name("theta")
		.description("Orientation")
		.type<IDouble>()
		);

	SetInput(
		Eyw::pin::id(IN_USER)
			.name("user")
			.description("User presence (0.0 or 1.0 for now)")
			.set_double_domain()
				.min(0.0)
	    );

	SetOutput(
		Eyw::pin::id(OUT_ACCELLERATION)
			.name("acceleration")
			.description("Measured acceleration")
			.type<Eyw::IDoubleMatrix>()
	    );

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature check.
/// </summary>
//////////////////////////////////////////////////////////
void CAccellerometer::CheckSignature()
{
	m_alfaMinPtr = get_parameter_datatype<Eyw::IDouble>(PAR_ALFA_MIN);
	m_alfaMaxPtr = get_parameter_datatype<Eyw::IDouble>(PAR_ALFA_MIN);
	m_betaMinPtr = get_parameter_datatype<Eyw::IDouble>(PAR_BETA_MIN);
	m_betaMaxPtr = get_parameter_datatype<Eyw::IDouble>(PAR_BETA_MAX);
	m_gravityVectorPtr = get_parameter_datatype<Eyw::IDoubleMatrix>(PAR_G);
	get_input(IN_THETA);
	get_input(IN_USER);
	get_output(OUT_ACCELLERATION);

}

//////////////////////////////////////////////////////////
/// <summary>
/// Block signature deinitialization.
/// </summary>
//////////////////////////////////////////////////////////
void CAccellerometer::DoneSignature()
{
	m_gravityVectorPtr = NULL;
	m_alfaMinPtr = NULL;
	m_alfaMaxPtr = NULL;
	m_betaMinPtr = NULL;
	m_betaMaxPtr = NULL;
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
bool CAccellerometer::Init() throw()
{
    try
    {
		/// TODO: Init data structures here 

		m_inputUserPtr = get_input_datatype<Eyw::IDouble>(IN_USER);
		m_inputThetaPtr = get_input_datatype<Eyw::IDouble>(IN_THETA);
		m_measuredAccelerationPtr = get_output_datatype<Eyw::IDoubleMatrix>(OUT_ACCELLERATION);
		m_measuredAccelerationPtr->InitInstance(m_gravityVectorPtr->GetInitInfo());

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
bool CAccellerometer::Start() throw()
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
bool CAccellerometer::Execute() throw()
{
	const Eyw::TIME time = _clockPtr->GetTime();
	const double user = m_inputUserPtr->GetValue();
	const double U = (user > 0.0) ? 1.0 : 0.0;
	const double* g = m_gravityVectorPtr->GetRawBuffer();
	const double theta = m_inputThetaPtr->GetValue();;
	const double cosTheta = cos(theta);
	const double sinTheta = sin(theta);

	//         [ cos(a)  -sin(a)      0 ]
	//         [                        ]
	// Rz(a) = [ sin(a)   cos(a)      0 ]
	//         [                        ]
	//         [      0       0       1 ]
	const double alfaMinDeg = m_alfaMinPtr->GetValue();
	const double alfaMaxDeg = m_alfaMaxPtr->GetValue();
	const double alfaMin = (alfaMinDeg / 180.0) * M_PI;
	const double alfaMax = (alfaMaxDeg / 180.0) * M_PI;
	const double alfaRange = alfaMax - alfaMin;
	const double alfa = (rand() * alfaRange) + alfaMin;
	const double cosAlfa = cos(alfa);
	const double sinAlfa = sin(alfa);



	//         [      1       0        0 ]
	//         [                         ]
	// Rx(b) = [      0  cos(b)  -sin(b) ]
	//         [                         ]
	//         [      0  sin(b)   cos(b) ]         

	const double betaMinDeg = m_betaMinPtr->GetValue();
	const double betaMaxDeg = m_betaMaxPtr->GetValue(); 
	const double betaMin = (betaMinDeg / 180.0) * M_PI;
	const double betaMax = (betaMaxDeg / 180.0) * M_PI;
	const double betaRange = betaMax - betaMin;
	const double beta = (rand() * betaRange) + betaMin;
	const double cosBeta = cos(beta);
	const double sinBeta = sin(beta);

	//                 [ cos(a)  -sin(a)      0 ]   [      1       0        0 ]
	//                 [                        ]   [                         ]
	// Rz(a) * Rx(b) = [ sin(a)   cos(a)      0 ] * [      0  cos(b)  -sin(b) ] =
	//                 [                        ]   [                         ]
	//                 [      0       0       1 ]   [      0  sin(b)   cos(b) ]  
	//
	//   [        cos(a)  -sin(a)*cos(b)   sin(a)*sin(b) ]
	//   [                                               ]
	// = [        sin(a)   cos(a)*cos(b)  -cos(a)*sin(b) ]
	//   [                                               ]
	//   [             0          sin(b)          cos(b) ]

	std::array<double, 3> x;
	x[0] = g[0];
	x[1] = g[1] * cosTheta - g[2] * sinTheta;
	x[2] = g[1] * sinTheta + g[2] * cosTheta;

	if (U > 0.0) {
		x[0] += ((cosAlfa * g[0]) - (sinAlfa * cosBeta * g[1]) + (sinAlfa * sinBeta * g[2]));
		x[1] += ((sinAlfa * g[0]) + (cosAlfa * cosBeta * g[1]) - (cosAlfa * sinBeta * g[2]));
		x[2] += ((sinBeta * g[1]) + (cosBeta * g[2]));
	}

	m_measuredAccelerationPtr->SetValues(x.data());
	m_measuredAccelerationPtr->SetCreationTime(time);

	return true;
}

//////////////////////////////////////////////////////////
/// <summary>
/// Block stop action.
/// </summary>
//////////////////////////////////////////////////////////
void CAccellerometer::Stop() throw()
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
void CAccellerometer::Done() throw()
{
    try
    {
		m_inputUserPtr = NULL;
		m_inputThetaPtr = NULL;
		m_measuredAccelerationPtr = NULL;

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
void CAccellerometer::OnChangedParameter( const std::string& csParameterID )
{
	/// TODO: manage the changed parameters
}

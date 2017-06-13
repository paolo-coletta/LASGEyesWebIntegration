#include "stdafx.h"
#include "resource.h"
#include "Signature.h"
#include "StringFromSerial.h"

namespace Eyw
{

	static const char* s_outputId							= "output";
	static const char* s_inputId							= "select";
	static const char* s_resetId							= "reset";

	////////////////////////////////////////////////////////////////////////////////////

	block_class_registrant string_from_serial( 
		block_class_registrant::block_id("string_to_from_serial")
			.begin_language( EYW_LANGUAGE_US_ENGLISH )
				.name( "StringFromSerial" )
				.description( "Converts a sequence of characters, as received from the serial port, to a string (using newlines as separator)." )
				.libraries("String.Operations")
				.bitmap(IDB_STRINGFROMSERIAL_BITMAP)
			.end_language()	
			.begin_authors()
				.author(EYW_LASG_CATALOG_AUTHOR_ID)
			.end_authors()
			.begin_licences()
				.licence(EYW_LASG_LICENSE_ID)
			.end_licences()
			.begin_companies()
				.company(EYW_LASG_COMPANY_ID)
			.end_companies()
			.default_factory<CStringFromSerial>()
		);

	////////////////////////////////////////////////////////////////////////////////////
	CStringFromSerial::CStringFromSerial(const OBJECT_CREATIONCTX* pCtx)
	:	CBlockImpl( pCtx )
	{
		_schedulingInfoPtr->SetActivationEventBased( true );
		_schedulingInfoPtr->GetEventBasedActivationInfo()->SetActivationOnInputChanged( s_inputId, true );
	}

	void CStringFromSerial::InitSignature()
	{
		SetInput(
			pin::id(s_inputId)
			.name("String")
			.description("Output string")
			.type<IInt>()
			);

		SetOutput(
			pin::id( s_outputId )
				.name( "Intput" )
				.description( "Input characters" )
				.type<IString>()
			);

		SetParameter( 
			pin::id( s_resetId )
				.name( "Reset" )
				.description( "Reset the status of the block, hence restarting as if no characters were received yet")
				.is_design_time(false)
				.is_run_time(true)
				.type<ITrigger>()
			
			);
	}

	void CStringFromSerial::CheckSignature()
	{
		get_parameter_datatype<ITrigger>( s_resetId );

		get_input(s_inputId);
		get_output( s_outputId );
	}

	void CStringFromSerial::DoneSignature()
	{
	}

	bool CStringFromSerial::Init() throw()
	{
		m_outputPtr = get_output_datatype<IString>( s_outputId );
		m_inputPtr = get_input_datatype<IInt>( s_inputId );
		m_currentString.clear();
		return true;
	}

	bool CStringFromSerial::Execute() throw()
	{
		int character = m_inputPtr->GetValue();
		if (character != '\n') {
			m_currentString += (char)character;
		}
		else if(!m_currentString.empty()) {
			if (m_currentString[m_currentString.size() - 1] == '\r')
				m_currentString.pop_back();
			if (!m_currentString.empty()) {
				m_outputPtr->SetValue(m_currentString.c_str());
				m_outputPtr->SetCreationTime(_clockPtr->GetTime());
				m_currentString.clear();
			}
		}

		return true;
	}

	void CStringFromSerial::Done() throw()
	{
		m_outputPtr = get_output_datatype<IString>(s_outputId);
		m_inputPtr = get_input_datatype<IInt>(s_inputId);
	}

	void CStringFromSerial::OnChangedParameter(const std::string& parameterID)
	{
		if(!IsRunTime())
		{
			if(parameterID==s_resetId)
			{
				m_currentString.clear();
			}
		}
	}


}; // namespace Eyw


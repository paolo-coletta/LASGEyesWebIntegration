/**
 * \ingroup base_catalog_blocks_StringFromSerialId
 * \file 
 *
 * Declares a block to get the serial input as strings	
 */

#pragma once

#include "EywBlockImpl.h"

namespace Eyw
{
	
	class CStringFromSerial: public CBlockImpl
	{
	public:
		CStringFromSerial(const OBJECT_CREATIONCTX* pCtx);

	// Overrides
	protected:
		virtual void InitSignature();
		virtual void CheckSignature();
		virtual void DoneSignature();
	
		virtual bool Init() throw();
		virtual bool Execute() throw();
		virtual void Done() throw();
		virtual void OnChangedParameter( const std::string& parameterID );

	private:
		string_ptr m_outputPtr;	
		int_ptr m_inputPtr;	
		std::string m_currentString;
	};

}; // namespace Eyw


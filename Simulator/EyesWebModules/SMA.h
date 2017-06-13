#pragma once



class CSMA : public Eyw::CBlockImpl
{
public:
	//////////////////////////////////////////////////////////
	/// <summary>
	/// Constructor.
	/// </summary>
	//////////////////////////////////////////////////////////
	CSMA( const Eyw::OBJECT_CREATIONCTX* ctxPtr );
	
	//////////////////////////////////////////////////////////
	/// <summary>	
	/// Destructor.
	/// </summary>
	//////////////////////////////////////////////////////////
	~CSMA();

protected:

	//////////////////////////////////////////////////////////
	/// <summary>
	/// Block signature initialization.
	/// </summary>
	//////////////////////////////////////////////////////////
	virtual void InitSignature();	// should also initialize layout and private data
	
	//////////////////////////////////////////////////////////
	/// <summary>
	/// Block signature check.
	/// </summary>
	//////////////////////////////////////////////////////////
	virtual void CheckSignature();
	
	//////////////////////////////////////////////////////////
	/// <summary>
	/// Block signature deinitialization.
	/// </summary>
	//////////////////////////////////////////////////////////
	virtual void DoneSignature();

	//////////////////////////////////////////////////////////
	/// Block Actions
	/// <summary>
	/// Block initialization action.
	/// </summary>
	/// <returns>
	/// true if success, otherwise false.
	/// </returns>
	//////////////////////////////////////////////////////////
	virtual bool Init() throw();

	//////////////////////////////////////////////////////////
	/// <summary>
	/// Block start action.
	/// </summary>
	/// <returns>
	/// true if success, otherwise false.
	/// </returns>
	//////////////////////////////////////////////////////////
	virtual bool Start() throw();

	//////////////////////////////////////////////////////////
	/// <summary>
	/// Block execution action.
	/// </summary>
	/// <returns>
	/// true if success, otherwise false.
	/// </returns>
	//////////////////////////////////////////////////////////
	virtual bool Execute() throw();

	//////////////////////////////////////////////////////////
	/// <summary>
	/// Block stop action.
	/// </summary>
	//////////////////////////////////////////////////////////
	virtual void Stop() throw();

	//////////////////////////////////////////////////////////
	/// <summary>
	/// Block deinitialization action.
	/// </summary>
	//////////////////////////////////////////////////////////
	virtual void Done() throw();

	//////////////////////////////////////////////////////////
	/// optionals
	/// <summary>
	/// Manage the ChangedParameter event.
	/// </summary>
	/// <param name="csParameterID">
	/// [in] id of the changed parameter.
	/// </param>
	//////////////////////////////////////////////////////////
	void OnChangedParameter( const std::string& csParameterID );

private:
	Eyw::double_ptr m_parTauPtr;
	Eyw::double_ptr m_inInputPtr;
	Eyw::double_ptr m_outOutputPtr;
	Eyw::double_ptr m_parInitialStatePtr;
	Eyw::double_ptr m_parDeltaTPtr;
	double m_state;
};

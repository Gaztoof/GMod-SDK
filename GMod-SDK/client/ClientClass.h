#pragma once

typedef void* (*CreateClientClassFn)(int entnum, int serialNum);
typedef void* (*CreateEventFn)();

class RecvProp
{
	// This info comes from the receive data table.
public:
	RecvProp();

	void					InitArray(int nElements, int elementStride);

	int						GetNumElements() const;
	void					SetNumElements(int nElements);

	int						GetElementStride() const;
	void					SetElementStride(int stride);

	int						GetFlags() const;

	const char* GetName() const;
	void* GetType() const;

	void** GetDataTable() const;
	void					SetDataTable(RecvTable* pTable);

	void* GetProxyFn() const;
	void					SetProxyFn(void* fn);

	void* GetDataTableProxyFn() const;
	void					SetDataTableProxyFn(void* fn);

	int						GetOffset() const;
	void					SetOffset(int o);

	// Arrays only.
	RecvProp* GetArrayProp() const;
	void					SetArrayProp(RecvProp* pProp);

	// Arrays only.
	void					SetArrayLengthProxy(void* proxy);
	void* GetArrayLengthProxy() const;

	bool					IsInsideArray() const;
	void					SetInsideArray();

	// Some property types bind more data to the prop in here.
	const void* GetExtraData() const;
	void				SetExtraData(const void* pData);

	// If it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char* GetParentArrayPropName();
	void				SetParentArrayPropName(const char* pArrayPropName);

public:

	const char* m_pVarName;
	void*			m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;


private:

	bool					m_bInsideArray;		// Set to true by the engine if this property sits inside an array.

	// Extra data that certain special property types bind to the property here.
	const void* m_pExtraData;

	// If this is an array (DPT_Array).
	RecvProp* m_pArrayProp;
	void*	m_ArrayLengthProxy;

	void* m_ProxyFn;
	void* m_DataTableProxyFn;	// For RDT_DataTable.

	RecvTable* m_pDataTable;		// For RDT_DataTable.
	int						m_Offset;

	int						m_ElementStride;
	int						m_nElements;

	// If it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char* m_pParentArrayPropName;
};
class RecvTable
{
public:

	typedef RecvProp	PropType;

	RecvTable();
	RecvTable(RecvProp* pProps, int nProps, const char* pNetTableName);
	~RecvTable();

	void		Construct(RecvProp* pProps, int nProps, const char* pNetTableName);

	int			GetNumProps();
	RecvProp* GetProp(int i);

	const char* GetName();

	// Used by the engine while initializing array props.
	void		SetInitialized(bool bInitialized);
	bool		IsInitialized() const;

	// Used by the engine.
	void		SetInMainList(bool bInList);
	bool		IsInMainList() const;


public:

	// Properties described in a table.
	RecvProp* m_pProps;
	int				m_nProps;

	// The decoder. NOTE: this covers each RecvTable AND all its children (ie: its children
	// will have their own decoders that include props for all their children).
	void* m_pDecoder;

	const char* m_pNetTableName;	// The name matched between client and server.


private:

	bool			m_bInitialized;
	bool			m_bInMainList;
};

class ClientClass
{
public:
	ClientClass(const char* pNetworkName, CreateClientClassFn createFn, CreateEventFn createEventFn, RecvTable* pRecvTable)
	{
		m_pNetworkName = pNetworkName;
		m_pCreateFn = createFn;
		m_pCreateEventFn = createEventFn;
		m_pRecvTable = pRecvTable;

		// Link it in
		//m_pNext = g_pClientClassHead;
		//g_pClientClassHead = this;
	}

	const char* GetName()
	{
		return m_pNetworkName;
	}

public:
	CreateClientClassFn		m_pCreateFn;
	CreateEventFn			m_pCreateEventFn;	// Only called for event objects.
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int						m_ClassID;	// Managed by the engine.
};

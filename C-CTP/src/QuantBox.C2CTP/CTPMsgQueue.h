#pragma once

#include "QuantBox.C2CTP.h"
#include "include\LockFreeQ.h"

class CCTPMsgQueue
{
	//��Ӧ�����п��ܳ��ֵ���Ϣ���ͣ�����ĸ����
	enum EnumMsgType
	{
		E_fnOnConnect,	
		E_fnOnDisconnect,	
		E_fnOnErrRtnOrderAction,
		E_fnOnErrRtnOrderInsert,
		E_fnOnRspError,
		E_fnOnRspOrderAction,
		E_fnOnRspOrderInsert,
		E_fnOnRspQryInstrument,
		E_fnOnRspQryInvestorPosition,
		E_fnOnRspQryOrder,
		E_fnOnRspQryTrade,
		E_fnOnRspQryTradingAccount,
		E_fnOnRtnDepthMarketData,
		E_fnOnRtnOrder,
		E_fnOnRtnTrade,
	};

	struct SMsgItem
	{
		EnumMsgType							type;			//��Ϣ����
		void*								pApi;			//ָ��������ָ��
		CThostFtdcRspInfoField				RspInfo;		//��Ӧ��Ϣ
		bool								bIsLast;		//�Ƿ����һ����
		union{
			int								nRequestID;
			ConnectionStatus				Status;
		};		
		union{
			CThostFtdcDepthMarketDataField	DepthMarketData;
			CThostFtdcInputOrderField		InputOrder;
			CThostFtdcInputOrderActionField	InputOrderAction;
			CThostFtdcInstrumentField		Instrument;
			CThostFtdcInvestorPositionField InvestorPosition;
			CThostFtdcOrderField			Order;
			CThostFtdcOrderActionField		OrderAction;
			CThostFtdcRspUserLoginField		RspUserLogin;
			CThostFtdcTradeField			Trade;
			CThostFtdcTradingAccountField	TradingAccount;
		};
	};

public:
	CCTPMsgQueue(void)
	{
		m_nSleep = 1;
		m_hThread = NULL;
		m_bRunning = false;

		//�ص�������ַָ��
		m_fnOnConnect = NULL;
		m_fnOnDisconnect = NULL;
		m_fnOnErrRtnOrderAction = NULL;
		m_fnOnErrRtnOrderInsert = NULL;
		m_fnOnRspError = NULL;
		m_fnOnRspOrderAction = NULL;
		m_fnOnRspOrderInsert = NULL;
		m_fnOnRspQryInstrument = NULL;
		m_fnOnRspQryInvestorPosition = NULL;
		m_fnOnRspQryOrder = NULL;
		m_fnOnRspQryTrade = NULL;
		m_fnOnRspQryTradingAccount = NULL;
		m_fnOnRtnDepthMarketData = NULL;
		m_fnOnRtnOrder = NULL;
		m_fnOnRtnTrade = NULL;
	}
	virtual ~CCTPMsgQueue(void)
	{
		StopThread();
		Clear();
	}

public:
	//��ն���
	void Clear();

	//�������ⲿ����˳�������д����ص�����
	bool Process();

	//���ڲ������̣߳��ڲ���������Process�����ص�
	void StartThread();
	void StopThread();

	//���ⲿ�ĺ�����ַע�ᵽ����(����ĸ����)
	void RegisterCallback(fnOnConnect pCallback){m_fnOnConnect = pCallback;}
	void RegisterCallback(fnOnDisconnect pCallback){m_fnOnDisconnect = pCallback;}
	void RegisterCallback(fnOnErrRtnOrderAction pCallback){m_fnOnErrRtnOrderAction = pCallback;}
	void RegisterCallback(fnOnErrRtnOrderInsert pCallback){m_fnOnErrRtnOrderInsert = pCallback;}
	void RegisterCallback(fnOnRspError pCallback){m_fnOnRspError = pCallback;}
	void RegisterCallback(fnOnRspOrderAction pCallback){m_fnOnRspOrderAction = pCallback;}
	void RegisterCallback(fnOnRspOrderInsert pCallback){m_fnOnRspOrderInsert = pCallback;}
	void RegisterCallback(fnOnRspQryInstrument pCallback){m_fnOnRspQryInstrument = pCallback;}
	void RegisterCallback(fnOnRspQryInvestorPosition pCallback){m_fnOnRspQryInvestorPosition = pCallback;}
	void RegisterCallback(fnOnRspQryOrder pCallback){m_fnOnRspQryOrder = pCallback;}
	void RegisterCallback(fnOnRspQryTrade pCallback){m_fnOnRspQryTrade = pCallback;}
	void RegisterCallback(fnOnRspQryTradingAccount pCallback){m_fnOnRspQryTradingAccount = pCallback;}
	void RegisterCallback(fnOnRtnDepthMarketData pCallback){m_fnOnRtnDepthMarketData = pCallback;}
	void RegisterCallback(fnOnRtnOrder pCallback){m_fnOnRtnOrder = pCallback;}
	void RegisterCallback(fnOnRtnTrade pCallback){m_fnOnRtnTrade = pCallback;}

	//��Ӧ��������������(����ĸ����)
	void Input_OnConnect(void* pApi,CThostFtdcRspUserLoginField *pRspUserLogin,ConnectionStatus result);
	void Input_OnDisconnect(void* pApi,CThostFtdcRspInfoField *pRspInfo,ConnectionStatus step);
	void Input_OnErrRtnOrderAction(void* pTraderApi,CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
	void Input_OnErrRtnOrderInsert(void* pTraderApi,CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
	void Input_OnRspError(void* pApi,CThostFtdcRspInfoField* pRspInfo,int nRequestID,bool bIsLast);
	void Input_OnRspOrderAction(void* pTraderApi,CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspOrderInsert(void* pTraderApi,CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryInvestorPosition(void* pTraderApi,CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryInstrument(void* pTraderApi,CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryOrder(void* pTraderApi,CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryTrade(void* pTraderApi,CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRspQryTradingAccount(void* pTraderApi,CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void Input_OnRtnDepthMarketData(void* pMdApi,CThostFtdcDepthMarketDataField *pDepthMarketData);
	void Input_OnRtnOrder(void* pTraderApi,CThostFtdcOrderField *pOrder);
	void Input_OnRtnTrade(void* pTraderApi,CThostFtdcTradeField *pTrade);
private:
	friend DWORD WINAPI ProcessThread(LPVOID lpParam);
	void RunInThread();

	//��Ӧ���ֱ�������
	void _Input(SMsgItem* pMsgItem);
	//�����е���Ϣ�жϷַ�
	void _Output(SMsgItem* pMsgItem);

	//��Ӧ���
	void Output_OnConnect(SMsgItem* pItem)
	{
		if(m_fnOnConnect)
			(*m_fnOnConnect)(pItem->pApi,&pItem->RspUserLogin,pItem->Status);
	}
	void Output_OnDisconnect(SMsgItem* pItem)
	{
		if(m_fnOnDisconnect)
			(*m_fnOnDisconnect)(pItem->pApi,&pItem->RspInfo,pItem->Status);
	}
	void Output_OnErrRtnOrderAction(SMsgItem* pItem)
	{
		if(m_fnOnErrRtnOrderAction)
			(*m_fnOnErrRtnOrderAction)(pItem->pApi,&pItem->OrderAction,&pItem->RspInfo);
	}
	void Output_OnErrRtnOrderInsert(SMsgItem* pItem)
	{
		if(m_fnOnErrRtnOrderInsert)
			(*m_fnOnErrRtnOrderInsert)(pItem->pApi,&pItem->InputOrder,&pItem->RspInfo);
	}
	void Output_OnRspError(SMsgItem* pItem)
	{
		if(m_fnOnRspError)
			(*m_fnOnRspError)(pItem->pApi,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspOrderAction(SMsgItem* pItem)
	{
		if(m_fnOnRspOrderAction)
			(*m_fnOnRspOrderAction)(pItem->pApi,&pItem->InputOrderAction,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspOrderInsert(SMsgItem* pItem)
	{
		if(m_fnOnRspOrderInsert)
			(*m_fnOnRspOrderInsert)(pItem->pApi,&pItem->InputOrder,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryInvestorPosition(SMsgItem* pItem)
	{
		if(m_fnOnRspQryInvestorPosition)
			(*m_fnOnRspQryInvestorPosition)(pItem->pApi,&pItem->InvestorPosition,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryInstrument(SMsgItem* pItem)
	{
		if(m_fnOnRspQryInstrument)
			(*m_fnOnRspQryInstrument)(pItem->pApi,&pItem->Instrument,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryOrder(SMsgItem* pItem)
	{
		if(m_fnOnRspQryOrder)
			(*m_fnOnRspQryOrder)(pItem->pApi,&pItem->Order,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryTrade(SMsgItem* pItem)
	{
		if(m_fnOnRspQryTrade)
			(*m_fnOnRspQryTrade)(pItem->pApi,&pItem->Trade,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRspQryTradingAccount(SMsgItem* pItem)
	{
		if(m_fnOnRspQryTradingAccount)
			(*m_fnOnRspQryTradingAccount)(pItem->pApi,&pItem->TradingAccount,&pItem->RspInfo,pItem->nRequestID,pItem->bIsLast);
	}
	void Output_OnRtnDepthMarketData(SMsgItem* pItem)
	{
		if(m_fnOnRtnDepthMarketData)
			(*m_fnOnRtnDepthMarketData)(pItem->pApi,&pItem->DepthMarketData);
	}
	void Output_OnRtnOrder(SMsgItem* pItem)
	{
		if(m_fnOnRtnOrder)
			(*m_fnOnRtnOrder)(pItem->pApi,&pItem->Order);
	}
	void Output_OnRtnTrade(SMsgItem* pItem)
	{
		if(m_fnOnRtnTrade)
			(*m_fnOnRtnTrade)(pItem->pApi,&pItem->Trade);
	}

private:
	int							m_nSleep;
	bool						m_bRunning;
	HANDLE						m_hThread;

	MSQueue<SMsgItem*>			m_queue;			//��Ӧ����

	//�ص�����ָ�루����ĸ����
	fnOnConnect					m_fnOnConnect;
	fnOnDisconnect				m_fnOnDisconnect;
	fnOnErrRtnOrderAction		m_fnOnErrRtnOrderAction;
	fnOnErrRtnOrderInsert		m_fnOnErrRtnOrderInsert;
	fnOnRspError				m_fnOnRspError;
	fnOnRspOrderAction			m_fnOnRspOrderAction;
	fnOnRspOrderInsert			m_fnOnRspOrderInsert;
	fnOnRspQryInstrument		m_fnOnRspQryInstrument;
	fnOnRspQryInvestorPosition	m_fnOnRspQryInvestorPosition;
	fnOnRspQryOrder				m_fnOnRspQryOrder;
	fnOnRspQryTrade				m_fnOnRspQryTrade;
	fnOnRspQryTradingAccount	m_fnOnRspQryTradingAccount;
	fnOnRtnDepthMarketData		m_fnOnRtnDepthMarketData;
	fnOnRtnOrder				m_fnOnRtnOrder;
	fnOnRtnTrade				m_fnOnRtnTrade;
};

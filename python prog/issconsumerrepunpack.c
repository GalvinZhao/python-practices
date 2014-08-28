int nIssConsumerReqUnPack(commMsg_def *stMsg, tb_issuer_sign_inf_def *pSignInf)
{
	hc_on_crd_rsp_def  stMsgbody;
	MessageHeader_def stHeader;
	st_oth_inf_def stOthInf;
	char tmpBuf[512] = {0};
	long cmdLen = 0;
	long len = 0;
	char sLocalRspCd[6] = {0};
	char sOutRspCd[6] = {0};
	int nRet = -1;
	
	memset(&stMsgbody, '0', sizeof(stMsgbody));
	memset(&stHeader, '0', sizeof(stHeader));
	
	memcpy(&stHeader, stMsg->msg, sizeof(MessageHeader_def));
	memcpy(&stMsgbody.onCrdBeg, stMsg->msg + sizeof(MessageHeader_def),
		sizeof(stMsgbody.onCrdBeg));

	//cmdLen
	memset(tmpBuf, 0, sizeof(tmpBuf));
	memcpy(tmpBuf, stMsg->msg + sizeof(MessageHeader_def) +
		sizeof(stMsgbody.onCrdBeg), 3);
	cmdLen = atol(tmpBuf);

	memcpy(stMsgbody.commandLen, stMsg->msg + sizeof(MessageHeader_def)
		+ sizeof(stMsgbody.onCrdBeg), 3);
	
	memcpy(stMsgbody.command, stMsg->msg + sizeof(MessageHeader_def)
		+ sizeof(stMsgbody.onCrdBeg) + 3, cmdLen);

	memcpy(&stMsgbody.onCrdEnd, stMsg->msg + sizeof(MessageHeader_def)
		+ sizeof(stMsgbody.onCrdBeg) + 3 + cmdLen, sizeof(stMsgbody.onCrdEnd));

	len = sizeof(MessageHeader_def) + sizeof(stMsgbody.onCrdBeg) 
			+ sizeof(stMsgbody.onCrdEnd) + 3 + cmdLen;
	if (stMsg->msglen != len)
	{
		setKnlBuf(RESP_CODE,RESP_CD_INVALID_RESP);
		vLogErr(EL_RPT_ERR,"stMsg->msglen[%d] != len [%d] error !",
			stMsg->msglen, len);
		return FAILURE;
	}

	if( memcmp(stHeader.rspCode, COMM_HEADER_SUCCESS, sizeof(stHeader.rspCode)))
	{
		setKnlBuf(RESP_CODE, RESP_CD_COMMUNICATE_FAIL);
		vLogErr(EL_RPT_ERR," stHeader.rspCode[%c%c]", stHeader.rspCode[0], stHeader.rspCode[1]);
		return FAILURE;
	}

	if(memcmp(stMsgbody.onCrdEnd.responseCode, COMM_BODY_SUCCESS,
			sizeof(stMsgbody.onCrdEnd.responseCode)))
	{
		memcpy(sOutRspCd, stMsgbody.onCrdEnd.responseCode,
			sizeof(stMsgbody.onCrdEnd.responseCode));
		vLogErr(EL_RPT_ERR," stMsgbody.Response[%s]", sOutRspCd);
		memset(sLocalRspCd, 0, sizeof(sLocalRspCd));
		nRet = nRspCodeOut2In(sOutRspCd, sLocalRspCd);
		if(nRet)
		{
			vLogErr(EL_RPT_ERR," nRspCodeOut2In error nRet = [%d] !", nRet);
			memcpy(sLocalRspCd, RESP_CD_SYS_MALFUNCTION, RESP_CD_LEN);
		}
		rtrim(sLocalRspCd);
		setKnlBuf(RESP_CODE, sLocalRspCd);
		return FAILURE;
	}

	//RESV3
	memset(&stOthInf, 0, sizeof(st_oth_inf_def));
	getKnlBufByLen(RESV3, (char*)&stOthInf, sizeof(st_oth_inf_def));

	memcpy(stOthInf.issTxnDate, stMsgbody.onCrdBeg.sysDatetime, 8);
	memcpy(stOthInf.issTxnTime, stMsgbody.onCrdBeg.sysDatetime + 8, 6);
	memcpy(stOthInf.issSettDate, stMsgbody.onCrdEnd.settDate, 8);
	memcpy(stOthInf.issAuthSeq, stMsgbody.onCrdEnd.authSeq, 10);	
	memcpy(stOthInf.issLimitedAuthSeq, stMsgbody.onCrdEnd.limitedAuthSeql, 10);
	memcpy(stOthInf.issBatNo, stMsgbody.onCrdEnd.batchNo, 6);
	memcpy(stOthInf.mac2, stMsgbody.onCrdBeg.mac2, 8);
	memcpy(stOthInf.issSettDate, stMsgbody.onCrdBeg.settDate, 8);
    memcpy(stOthInf.issAuthSeq, stMsgbody.onCrdBeg.authSeq, 8);
    memcpy(stOthInf.issLimitedAuthSeq, stMsgbody.onCrdBeg.limitedAuthSeql, 8);
	setKnlBufByLen(RESV3, (char*)&stOthInf, sizeof(st_oth_inf_def));
	setKnlBufByLen(RESP_CODE, RESP_CD_SUCCESS, RESP_CD_LEN);
	return SUCCESS;
}
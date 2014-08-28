// 圈存冲正解包
int nIssEmarkRsvlUnPack(commMsg_def *stMsg, tb_issuer_sign_inf_def *pSignInf)
{

	hc_on_crd_rsv_def stMsgbody;
	MessageHeader_def stHeader;
	
	char saTmp[200];
	char saTmp2[20];
	char sLocalRspCd[6] = {0};
	char sOutRspCd[6] = {0};
	int nRet = -1;
	//st_58Inf *p58fld;
	memset(&stMsgbody, '0', sizeof(stMsgbody));
	memset(&stHeader, '0', sizeof(stHeader));

	nRet = (int) sizeof(stHeader) + (int) sizeof(stMsgbody);
	if ( stMsg->msglen != (nRet))
	{
		setKnlBuf(RESP_CODE,RESP_CD_INVALID_RESP);
		vLogErr(EL_RPT_ERR,"stMsg->msglen[%d] != sizeof(stHeader) + sizeof(stMsgbody)[%d]",
			stMsg->msglen,	nRet);
		return FAILURE;
		
	}

	memcpy(&stHeader, stMsg->msg, sizeof(stHeader));
	memcpy(&stMsgbody, stMsg->msg + sizeof(stHeader), sizeof(stMsgbody));

	if( memcmp(stHeader.rspCode, COMM_HEADER_SUCCESS, sizeof(stHeader.rspCode)) != 0)
	{
		setKnlBuf(RESP_CODE,RESP_CD_COMMUNICATE_FAIL);
		vLogErr(EL_RPT_ERR," stHeader.rspCode[%c%c]", stHeader.rspCode[0], stHeader.rspCode[1]);
		return FAILURE;
	}

	if( memcmp(stMsgbody.responseCode, COMM_BODY_SUCCESS, sizeof(stMsgbody.responseCode) ) != 0)
	{
		memcpy(sOutRspCd, stMsgbody.responseCode, sizeof(stMsgbody.responseCode));
		vLogErr(EL_RPT_ERR," stMsgbody.Response[%s]",sOutRspCd);
		nRet = nRspCodeOut2In(sOutRspCd, sLocalRspCd);
		if(nRet)
		{
			vLogErr(EL_RPT_ERR," nRspCodeOut2In failure");
			return FAILURE;
		}
		rtrim(sLocalRspCd);
		setKnlBuf(RESP_CODE,sLocalRspCd);
		return FAILURE;
	}

	
	//	infomation of return from hongcheng
	int len =0;
	memcpy(saTmp + len , stMsgbody.settDate, sizeof(stMsgbody.settDate));
	len += sizeof(stMsgbody.settDate);
	memcpy(saTmp + len , stMsgbody.authSeq, sizeof(stMsgbody.authSeq));
	len += sizeof(stMsgbody.authSeq);
	memcpy(saTmp + len , stMsgbody.limitedAuthSeql, sizeof(stMsgbody.limitedAuthSeql));
	len += sizeof(stMsgbody.limitedAuthSeql);
	setKnlBufByLen(RESV2, saTmp, len);
	
	setKnlBufByLen(RESP_CODE, RESP_CD_SUCCESS, RESP_CD_LEN);
	return SUCCESS;

}
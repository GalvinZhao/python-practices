int nIssConsumerReqPack(commMsg_def *stMsg, tb_issuer_sign_inf_def *pSignInf)
{
	//EmarkReqMsgBody_def stMsgbody;
	hc_on_crd_req_def stMsgbody;
	MessageHeader_def stHeader;
	tb_pos_inf_def tbPosInf;
	st_oth_inf_def stOthInf;
	st_fld_58_req3_def stFld58Req3;
	char tmpBuf[512] = {0};
	long txnAmt = 0;
	char cardId[20] = {0};
	int nRet = -1;
	long nCardBal = 0;
	long txnCnt = 0;
	char *pBuf = NULL;

	memset(&tbPosInf, 0 , sizeof(tb_pos_inf_def));
	memcpy(tbPosInf.term_id, pSignInf->iss_term_id, 8);
	memcpy(tbPosInf.mchnt_id, pSignInf->iss_mchnt, 15);
	nRet = dbs_tb_pos_inf(DB_SELECT, &tbPosInf, NULL);
	if(nRet)
	{
		vLogErr(EL_RPT_ERR,"dbs_tb_pos_inf error[%d]", nRet);
		if( nRet == DBS_NOTFOUND)
		{			
			setKnlBuf(RESP_CODE,RESP_CD_INVALID_MCHNT);
		}
		else
		{
			setKnlBuf(RESP_CODE,RESP_CD_SYS_MALFUNCTION);
		}
		return FAILURE;
	}
	
	//rsvd1	
	memset(&stFld58Req3, 0, sizeof(st_fld_58_req3_def));
	getKnlBufByLen(RESV1, (char*)&stFld58Req3, sizeof(st_fld_58_req3_def));

	//rsvd3
	memset(&stOthInf, 0, sizeof(st_oth_inf_def));
	getKnlBufByLen(RESV3, (char*)&stOthInf, sizeof(st_oth_inf_def));
	
	
	memset(&stMsgbody, '0', sizeof(stMsgbody));
	memset(&stHeader, '0', sizeof(stHeader));

	//version
	memcpy(stHeader.version, COMM_VERSION, sizeof(stHeader.version));
	//Message Type
	memcpy(stHeader.messageType, STR_HC_CARD_OPR_TYPE, sizeof(stHeader.messageType));
	//Message Date Time
	memset(tmpBuf, 0, sizeof(tmpBuf));
	CommonGetCurrentTime(tmpBuf);
	memcpy(stHeader.messageDateTime, tmpBuf, 14);
	//MAC
	//Response Code
	
	// msg body
	// Unitid	 商户 号取后8位
	memcpy(stMsgbody.onCrdBeg.unitId, pSignInf->iss_mchnt + 7, 8);
	
	// Posid
	memcpy(stMsgbody.onCrdBeg.posId + 4, pSignInf->iss_term_id, 8);
	
	// SamId
	
	//PosSequence
	memcpy(stMsgbody.onCrdBeg.posSequence, stOthInf.issPosSeq, 9);
	
	//Termid
	memcpy(stMsgbody.onCrdBeg.termId + 4, pSignInf->iss_term_id, 8);
	
	//Operid
	memcpy(stMsgbody.onCrdBeg.operId, STR_HC_OPER_ID, sizeof(stMsgbody.operId)); 

	//EDCardId
	
	//CardOprType
	memcpy(stMsgbody.onCrdBeg.cardOprType, MESSAGE_TYPE_2010, sizeof(MESSAGE_TYPE_2010));

	//CItyCode
	memset(cardId, 0, sizeof(cardId));
	getKnlBuf(CARD_NO, cardId);
	memcpy(stMsgbody.onCrdBeg.cityCode, cardId + 4, 4);

	//CardId
	memcpy(stMsgbody.onCrdBeg.cardId, cardId, 16);

	//CardMType
	memcpy(stMsgbody.onCrdBeg.cardMType, cardId + sizeof(stMsgbody.onCrdBeg.cityCode), 4);
	//CardSType
	memcpy(stMsgbody.onCrdBeg.cardSType, 
		cardId + sizeof(stMsgbody.onCrdBeg.cityCode) + sizeof(stMsgbody.onCrdBeg.cardMType), 
		sizeof(stMsgbody.onCrdBeg.cardSType));
	//CardModel
	memcpy(stMsgbody.onCrdBeg.cardModel, "1", 1);

	//TransType
	memcpy(stMsgbody.onCrdBeg.transType, STR_HC_CONSUME_BUSS_CODE, 2);

	//CardCSN

	//CardMac

	//SysDatetime

	//Deposit
	memcpy(stMsgbody.onCrdBeg.deposit, stOthInf.deposit, 8);
	//OrigAmt
	memset(tmpBuf, 0, sizeof(tmpBuf));
	memcpy(tmpBuf, stFld58Req3.txnAmt, 8);
	txnAmt = 0;
	aschex2l(tmpBuf, 8, &txnAmt);
	memset(tmpBuf, 0, sizeof(tmpBuf));
	sprintf(tmpBuf, "%08ld", txnAmt);
	memcpy(stMsgbody.onCrdBeg.origAmt, tmpBuf, 8);

	//reloadBal
	memcpy(stMsgbody.onCrdBeg.reloadBal, tmpBuf, 8);

	//CardValDate
	memcpy(stMsgbody.onCrdBeg.cardValDate, stOthInf.cardValidDate, 8);


	//SettDate

	//BatchNo
	memset(tmpBuf, 0, sizeof(tmpBuf));
	sprintf(tmpBuf, "%06ld", tbPosInf.term_batch_no);
	memcpy(stMsgbody.onCrdEnd.batchNo, tmpBuf, 6);

	//AuthSeq
	memcpy(stMsgbody.onCrdEnd.AuthSeq, stOthInf.issAuthSeq, 10);
	memcpy(stMsgbody.onCrdEnd.limitedAuthSeql, stOthInf.relIssAuthSeq, 10);
	memcpy(stMsgbody.onCrdEnd.bankSetdate, stOthInf.accSettDate, 8);
	memcpy(stMsgbody.onCrdEnd.bankCenSeq, stOthInf.txnSeqNo, 12);
	
	memcpy(stMsgbody.onCrdEnd.relMesageType, STR_HC_CARD_OPR_TYPE, sizeof(stMsgbody.limitedAuthSeql));
	memcpy(stMsgbody.onCrdEnd.relTransType, STR_HC_EMARK_BUSS_CODE, sizeof(stMsgbody.relTransType));

	memcpy(stMsgbody.onCrdEnd.relYktSetDate, stOthInf.relIssSettDate, 8);
	memcpy(stMsgbody.onCrdEnd.relYktCenSeq, stOthInf.relIssAuthSeq, 10);
	memcpy(stMsgbody.onCrdEnd.relBankSetDate, stOthInf.relIssSettDate, 8);
	memcpy(stMsgbody.onCrdEnd.relBankCenSeq, stOthInf.relIssAuthSeq, 10);
	//Response Code
	//set msg and len
	memset(stMsg, 0, sizeof(commMsg_def));
	stMsg->msglen = (int)sizeof(stHeader) + sizeof(stMsgbody.onCrdBeg)
			+ sizeof(stMsgbody.onCrdEnd) + 3;
	
	pBuf = &stMsg->msg[0];	
	memcpy(pBuf, &stHeader, sizeof(stHeader));
	pBuf += sizeof(stHeader);
	
	memcpy(pBuf, (char*)&stMsgbody.onCrdBeg, sizeof(stMsgbody.onCrdBeg));
	pBuf += sizeof(stMsgbody.onCrdBeg);

	//cmdlen
	memcpy(pBuf, "000", 3);
	pBuf += 3;

	memcpy(pBuf, (char *)&stMsgbody.onCrdEnd, sizeof(stMsgbody.onCrdEnd));
	
	return SUCCESS;
}
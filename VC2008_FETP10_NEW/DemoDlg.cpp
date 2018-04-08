// DemoDlg.cpp : implementation file
//
#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "Connect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
	m_Cur = _T("");
	m_SN = _T("");
	m_Count = _T("");
	m_Block = 1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	sRegTemplate = _T("");
	sRegTemplate10 = _T("");
	FINGER_POSITION[0]=0;
	
	
	//CFont *m_pFont=new CFont();
	//m_pFont->CreateP(165,_T("Arial"));
	//GetDlgItem(label1N)->SetFont(m_pFont,TRUE);
	/*LOGFONT f={0};
	Geth
	f.lfHeight=-MulDiv(50,GetDeviceCaps(
	m_pFont->GetLogFont(&f);
	SendDlgItemMessage(labelStatic,WM_SETFONT,(WPARAM)&f,MAKELONG(TRUE,0));
	*/
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDC_ZKFPENGX2, zkfpEng);
	DDX_Text(pDX, IDC_EDTCUR, m_Cur);
	DDX_Text(pDX, IDC_EDTSN, m_SN);
	DDX_Text(pDX, IDC_EDTCOUNT, m_Count);
	DDX_Text(pDX, IDC_EDIT_Block, m_Block);
	DDV_MinMaxInt(pDX, m_Block, 0, 63);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNInit, OnBTNInit)
	ON_BN_CLICKED(IDC_BTNSave, OnBTNSave)
	ON_BN_CLICKED(IDC_BTNReg, OnBTNReg)
	ON_BN_CLICKED(IDC_BTNIdentify, OnBTNIdentify)
	ON_BN_CLICKED(IDC_BTNVer, OnBTNVer)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTNREAD, OnReadcard)
	ON_BN_CLICKED(IDC_BTNWRITE, OnWriteCard)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTNRED, &CDemoDlg::OnBnClickedBtnred)
	ON_BN_CLICKED(IDC_BTNGREEN, &CDemoDlg::OnBnClickedBtngreen)
	ON_BN_CLICKED(IDC_BTNBEEP, &CDemoDlg::OnBnClickedBtnbeep)
	ON_BN_CLICKED(IDC_BTNWRITEPWD, &CDemoDlg::OnBnClickedBtnwritepwd)
	ON_BN_CLICKED(IDC_BTNREADPWD, &CDemoDlg::OnBnClickedBtnreadpwd)
	ON_BN_CLICKED(IDC_RADIO9, &CDemoDlg::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &CDemoDlg::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_BTNDisConnect, &CDemoDlg::OnBnClickedBtndisconnect)
	ON_BN_CLICKED(IDC_BTNREGBYIMAGE, &CDemoDlg::OnBnClickedBtnregbyimage)
	ON_BN_CLICKED(IDC_BTNIDENBYIMAGE, &CDemoDlg::OnBnClickedBtnidenbyimage)
	ON_BN_CLICKED(IDC_BTNSN, &CDemoDlg::OnBnClickedBtnsn)
	ON_BN_CLICKED(IDC_BTNCARDNUMBER, &CDemoDlg::OnBnClickedBtncardnumber)
	ON_BN_CLICKED(IDC_BTNWRITETMP, &CDemoDlg::OnBnClickedBtnwritetmp)
	ON_BN_CLICKED(IDC_BTNREADTMP, &CDemoDlg::OnBnClickedBtnreadtmp)
	ON_BN_CLICKED(btnConnectMySQL, &CDemoDlg::OnBnClickedbtnconnectmysql)
	ON_BN_CLICKED(btnFirst, &CDemoDlg::OnBnClickedbtnfirst)
	ON_BN_CLICKED(btnPrev, &CDemoDlg::OnBnClickedbtnprev)
	ON_BN_CLICKED(btnNext, &CDemoDlg::OnBnClickedbtnnext)
	ON_BN_CLICKED(btnLast, &CDemoDlg::OnBnClickedbtnlast)
	ON_BN_CLICKED(btnUpdate, &CDemoDlg::OnBnClickedbtnupdate)
	ON_CBN_EDITCHANGE(comboRight, &CDemoDlg::OnCbnEditchangecomboright)
	ON_CBN_EDITUPDATE(comboRight, &CDemoDlg::OnCbnEditupdatecomboright)
	ON_CBN_SELCHANGE(comboRight, &CDemoDlg::OnCbnSelchangecomboright)
	ON_CBN_SELCHANGE(comboLeft, &CDemoDlg::OnCbnSelchangecomboleft)
	ON_CBN_SELENDOK(comboLeft, &CDemoDlg::OnCbnSelendokcomboleft)
	ON_EN_CHANGE(editFPID, &CDemoDlg::OnEnChangeeditfpid)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	bVerWithCard = false;
	FPID = 1;
	fpcHandle = 0;

	CheckRadioButton(IDC_RADIOBMP, IDC_RADIOJPG, IDC_RADIOBMP);
	//CheckRadioButton(IDC_RADIO9, IDC_RADIO10, IDC_RADIO9);
	CheckRadioButton(IDC_RADIO9, IDC_RADIO10, IDC_RADIO10);
	CheckRadioButton(checkSaveImage, checkSaveImage, checkSaveImage);
	EnableButton(false);
	
	SetDlgItemText(editGo,"1");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CDemoDlg::logONList(LPCSTR msg){

	SendDlgItemMessage(listLog_01,LB_ADDSTRING,0,(LPARAM)(msg));

}

void CDemoDlg::OnBTNInit() 
{
	char buffer[10] = {0};
	char buf_FN[64]={0},buf_FN10[64]={0};
	if (zkfpEng.InitEngine() == 0)
	{
		EnableButton(true);
		if (IsDlgButtonChecked(IDC_RADIO9) != 0)
			zkfpEng.put_FPEngineVersion("9");
		else
			zkfpEng.put_FPEngineVersion("10");
		fpcHandle = zkfpEng.CreateFPCacheDBEx();
		//fpcHandle = zkfpEng.CreateFPCacheDB();
		m_SN = zkfpEng.get_SensorSN();
		ltoa(zkfpEng.get_SensorIndex(), buffer, 10);
		m_Cur = buffer;
		ltoa(zkfpEng.get_SensorCount(), buffer, 10);
		m_Count = buffer;
		SetDlgItemText(IDC_EDTCUR, m_Cur);
		SetDlgItemText(IDC_EDTCOUNT, m_Count);
		SetDlgItemText(IDC_EDTSN, m_SN);		
		MessageBox("Initial Succeed");

		//test loading 
		//@todo load master finger from here ....
		//zkfpEng.
		
		/*FPID=1;
		long ret=zkfpEng.AddRegTemplateFileToFPCacheDB(fpcHandle, FPID, (LPCTSTR)".\\master\\TPL9_02.tpl");
		FPID++;
		ret=zkfpEng.AddRegTemplateFileToFPCacheDB(fpcHandle, FPID, (LPCTSTR)".\\master\\TPL9_03.tpl");
		FPID++;
		ret=zkfpEng.AddRegTemplateFileToFPCacheDB(fpcHandle, FPID, (LPCTSTR)".\\master\\TPL9_05.tpl");
		FPID++;
		*/

		/* 
		FPID=1;
		long ret=zkfpEng.AddRegTemplateFileToFPCacheDBEx(fpcHandle, FPID, 
			(LPCTSTR)".\\master\\TPL9_2.tpl",(LPCTSTR)".\\master\\TPL10_2.tpl");
		FPID++;
		ret=zkfpEng.AddRegTemplateFileToFPCacheDBEx(fpcHandle, FPID, 
			(LPCTSTR)".\\master\\TPL9_4.tpl",(LPCTSTR)".\\master\\TPL10_4.tpl");
		FPID++;
		ret=zkfpEng.AddRegTemplateFileToFPCacheDBEx(fpcHandle, FPID, 
			(LPCTSTR)".\\master\\TPL9_5.tpl",(LPCTSTR)".\\master\\TPL10_5.tpl");
		FPID++;
		ret=zkfpEng.AddRegTemplateFileToFPCacheDBEx(fpcHandle, FPID, 
			(LPCTSTR)".\\master\\TPL9_6.tpl",(LPCTSTR)".\\master\\TPL10_6.tpl");
		FPID++;
		ret=zkfpEng.AddRegTemplateFileToFPCacheDBEx(fpcHandle, FPID, 
			(LPCTSTR)".\\master\\TPL9_7.tpl",(LPCTSTR)".\\master\\TPL10_7.tpl");
		*/

		FPID=1;
		long ret=1,totalFPID=0;
		char info[30]={0};

		int missingCount=0;
		while(FPID<=1000){
			
			try{
				sprintf(buf_FN,".\\master\\TPL9_%d.tpl",FPID);
				sprintf(buf_FN10,".\\master\\TPL10_%d.tpl",FPID);
				
				if(PathFileExists(buf_FN)==FALSE||PathFileExists(buf_FN10)==FALSE){
					missingCount++;
				}
				if(missingCount>3){
					info[0]=0;
					MessageBox("Stop before MAX templates because of \r\n3 consecutive missing files",
						"Alert",MB_ICONERROR);
					break;

				}
				if(PathFileExists(buf_FN)!=FALSE)
					if(PathFileExists(buf_FN10)!=FALSE){

						ret=zkfpEng.AddRegTemplateFileToFPCacheDBEx(fpcHandle, FPID, 
								(LPCTSTR)buf_FN,(LPCTSTR)buf_FN10);
						totalFPID++;
						FPID++;
					}
			}catch (std::exception &e){
				MessageBox(e.what(),"Error",MB_ICONERROR);
				OnBnClickedBtndisconnect();
				return ;
			}
		}
		info[0]=0;//reempty info
		sprintf(info,"Templated loaded total: %d, next FPID=%d",totalFPID,FPID);
		SetDlgItemText(IDC_EDTHINT, info);		
		logONList(info);


	} 
	else
	{
		zkfpEng.EndEngine();
		MessageBox("Initial Failed");
	}
	matchType = 2;
}



BEGIN_EVENTSINK_MAP(CDemoDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CDemoDlg)
	ON_EVENT(CDemoDlg, IDC_ZKFPENGX2, 8 /* OnImageReceived */, OnOnImageReceivedZkfpengx2, VTS_PBOOL)
	ON_EVENT(CDemoDlg, IDC_ZKFPENGX2, 10 /* OnCapture */, OnOnCaptureZkfpengx2, VTS_BOOL VTS_VARIANT)
	ON_EVENT(CDemoDlg, IDC_ZKFPENGX2, 9 /* OnEnroll */, OnOnEnrollZkfpengx2, VTS_BOOL VTS_VARIANT)
	ON_EVENT(CDemoDlg, IDC_ZKFPENGX2, 5 /* OnFeatureInfo */, OnOnFeatureInfoZkfpengx2, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDemoDlg::OnOnImageReceivedZkfpengx2(BOOL FAR* AImageValid) 
{
	// TODO: Add your control notification handler code here
	HDC hdc;

	hdc = this->GetDC()->m_hDC;

	zkfpEng.PrintImageAt(long(hdc), 400, 2, zkfpEng.get_ImageWidth(), zkfpEng.get_ImageHeight());
}

void CDemoDlg::OnBTNSave() 
{
	if (IsDlgButtonChecked(IDC_RADIOBMP) != 0)
		zkfpEng.SaveBitmap("fingerprint.bmp");
	else
		zkfpEng.SaveJPG("fingerprint.jpg");
	MessageBox("Fingerprint Image saved");
}


char bckupsPath[50]={0};
void threaded2(void *param){
	CDemoDlg *dlg=(CDemoDlg*)param;
	dlg->backupFPImageThr();
	//const CZKFPEngX &zk=dlg->getZKEng();
	//CZKFPEngX np=(*zk);
	//&zk.SaveJPG(bckupsPath);
		//_endthread();

}
void CDemoDlg::backupFPImageThr	(){
	zkfpEng.SaveJPG(bckupsPath);
}
void CDemoDlg::backupFPImage(int FPID){


	char sTime[80]={0};
	time_t rawtime;
	struct tm *timeinfo;

	if (IsDlgButtonChecked(checkSaveImage) != 0){
		//zkfpEng.SaveBitmap("fingerprint.bmp");
		time(&rawtime);
		timeinfo=localtime(&rawtime);
		strftime(sTime,sizeof(sTime),"%Y_%m_%d_%H_%M_%S",timeinfo);
		sprintf(bckupsPath,".\\images\\FPID_%d_%s.jpg",FPID,sTime);
		
		//
		//zkfpEng.SaveJPG(sPath);
		logONList(bckupsPath);
		_beginthread(threaded2,0,this);

		//logONList(sPath);
	}
	//	zkfpEng.SaveJPG("fingerprint.jpg");
	//MessageBox("Fingerprint Image saved");
	

}

void CDemoDlg::OnBTNReg() 
{
	zkfpEng.CancelEnroll();
	zkfpEng.put_EnrollCount(3);
	//zkfpEng.put_EnrollCount(5);
	zkfpEng.BeginEnroll();

	SetDlgItemText(IDC_EDTHINT, "start register");		
}

void CDemoDlg::OnBTNIdentify() 
{
    if (zkfpEng.get_IsRegister())
        zkfpEng.CancelEnroll();
	SetDlgItemText(IDC_EDTHINT, "Identify(1:N)");		
    matchType = 2;
}

void CDemoDlg::OnBTNVer() 
{
    if (zkfpEng.get_IsRegister())
        zkfpEng.CancelEnroll();
	SetDlgItemText(IDC_EDTHINT, "Verify(1:1)");		
    matchType = 1;
}

BOOL CDemoDlg::DestroyWindow() 
{
	return CDialog::DestroyWindow();
}

void CDemoDlg::OnOnCaptureZkfpengx2(BOOL ActionResult, const VARIANT FAR& ATemplate) 
{
	long id = 0, Score = 0, ProcessNum = 0;
	char buffer[64] = {0};
	CString sTemp;
	BOOL RegChanged;
	
	if (matchType == 1)
	{
		if(bVerWithCard)
		{
			BOOL ARegFeatureChanged;

			if(zkfpEng.VerRegFingerFile("fingerprint2.tpl", ATemplate, false, &ARegFeatureChanged))
			{
				SetDlgItemText(IDC_EDTHINT, "Verify Succeed(from Mifare Card)!");
			}
			else
			{
				SetDlgItemText(IDC_EDTHINT, "Verify Failed");
			}
			bVerWithCard = false;
		}
		else
		{
			sTemp = zkfpEng.GetTemplateAsString();
			BSTR bTemp;
			if (IsDlgButtonChecked(IDC_RADIO9) != 0)
			{
				bTemp = sRegTemplate.AllocSysString();
			}
			else
			{
				bTemp = sRegTemplate10.AllocSysString();
			}

			if (zkfpEng.VerFingerFromStr(&bTemp, (LPCTSTR)sTemp, FALSE, &RegChanged))
			{
				SetDlgItemText(IDC_EDTHINT, "Verify Succeed");
			}
			else
			{
				SetDlgItemText(IDC_EDTHINT, "Verify Failed");
			}
		}
	}	
	else if (matchType == 2) // 1:N
	{  
		Score = 8;
		id = zkfpEng.IdentificationInFPCacheDB(fpcHandle, ATemplate, &Score, &ProcessNum);
		if (id == -1)
		{
			SetDlgItemText(IDC_EDTHINT, "Identify Failed");
			SetDlgItemText(label1N, "1N Failed");
			OnBnClickedBtnred();
			//OnBnClickedBtnbeep();
		}
		else
		{
			sprintf(buffer, "Identify Succeed ID = %d Score = %d  Processed Number = %d", id, Score, ProcessNum);
			SetDlgItemText(IDC_EDTHINT, buffer);
			OnBnClickedBtngreen();
			SyncControlForIdentifiedFPID(id); //synch controls.. 

		}
		
		/*** update FPID in text edit **/
		char numbuf[10]={0};
		sprintf(numbuf,"%d",id);
		SetDlgItemText(editFPID, numbuf);
		mysql_logIdentified1N(id,Score,ProcessNum);
		backupFPImage(id);
	}   
}



void CDemoDlg::OnOnEnrollZkfpengx2(BOOL ActionResult, const VARIANT FAR& ATemplate) 
{
	VARIANT pTemplate,pTemplate10;
	char  buffer[64]={0};
	char  buffer10[64]={0};
	char  buffermsg[128]={0};
	
	if (!ActionResult)
		MessageBox("Register Failed");
	else
	{
		// After enroll, you can get 9.0&10.0 template at the same time
		sRegTemplate = zkfpEng.GetTemplateAsStringEx("9");
		sRegTemplate10 = zkfpEng.GetTemplateAsStringEx("10");


		if(sRegTemplate.GetLength() > 0)
		{
			/*if(sRegTemplate10.GetLength() > 0)
				zkfpEng.AddRegTemplateStrToFPCacheDBEx(fpcHandle, FPID, (LPCTSTR)sRegTemplate, (LPCTSTR)sRegTemplate10);
			else
				MessageBox("Register 10.0 failed, template length is zero");*/


			/*if(sRegTemplate10.GetLength() > 0){
				zkfpEng.AddRegTemplateStrToFPCacheDB(fpcHandle, FPID, (LPCTSTR)sRegTemplate);
			}
			else
				MessageBox("Register 10.0 failed, template length is zero");
			*/

			pTemplate = zkfpEng.DecodeTemplate1((LPCTSTR)sRegTemplate);
			pTemplate10=zkfpEng.DecodeTemplate1((LPCTSTR)sRegTemplate10);
			// Note: 10.0Template can not be compressed
			zkfpEng.SetTemplateLen(&pTemplate, 602);
			zkfpEng.SaveTemplate("fingerprint.tpl", pTemplate);
			sprintf(buffer,".\\downloaded\\TPL9_%d.tpl",FPID);
			zkfpEng.SaveTemplate(buffer, pTemplate);
			
			sprintf(buffer10,".\\downloaded\\TPL10_%d.tpl",FPID);
			//no neeed to set length ? since v10 can't be compressed ....
			zkfpEng.SaveTemplate(buffer10, pTemplate10);
			
			//zkfpEng.SaveTemplate("double.tpl", pTemplate);

			//register by file

			//long ret=zkfpEng.AddRegTemplateFileToFPCacheDB(fpcHandle, FPID, (LPCTSTR)buffer);
			long ret=zkfpEng.AddRegTemplateFileToFPCacheDBEx(fpcHandle, FPID, (LPCTSTR)buffer,(LPCTSTR)buffer10);
			sprintf(buffermsg,"Adding db from %s %s  for FPID=%d, return ret=%d",buffer,buffer10,FPID,ret);
			MessageBox(buffermsg);
			

			//zkfpEng.savetem
			//zkfpEng.enco
			FPID = FPID + 1;
			UpdateData(TRUE);
			//MessageBox("Register Succeed");
		}
		else
		{
			MessageBox("Register Failed, template length is zero");
		}
  }
}

void CDemoDlg::OnOnFeatureInfoZkfpengx2(long AQuality) 
{
	CString str;
	char buffer[10] = {0};

	if (zkfpEng.get_IsRegister())
	{
		ltoa(zkfpEng.get_EnrollIndex(), buffer, 10);
		str = str + "Register Status: still press finger " + buffer + " times";
	}
	str += " Fingerprint quality";
	ltoa(zkfpEng.get_LastQuality(), buffer, 10);
	if (AQuality != 0)
		str = str + " not good, quality="  + buffer;
	else
		str = str + " good, quality=" + buffer;
	SetDlgItemText(IDC_EDTHINT, str);
}

void CDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CDemoDlg::OnClose() 
{
	zkfpEng.EndEngine();
	if(fpcHandle > 0)
	{
		zkfpEng.FreeFPCacheDB(fpcHandle);
		//zkfpEng.FreeFPCacheDBEx(fpcHandle);
	}
	CDialog::OnClose();
}

int CDemoDlg::ReadBLOCK(int blockIndex, BYTE *pData, BYTE *key)
{
	int ret = 0;

	if(blockIndex<0 || blockIndex>63)// mifare s50card 0~63
		ret = -1;

	if(!zkfpEng.MF_PCDRead(0 ,0, 0, blockIndex, 1, key, pData))
		ret = pData[0];

	return ret;
}

int CDemoDlg::ReadBlock2(BYTE blockIndex, BYTE *pData, int blockLen)
{
	BYTE *buf = NULL;
	BYTE key[6];

	int i = 0, index = 0, blockNum = 0;

	index = blockIndex;
	buf = pData;

	for(i = 0;i< blockLen;)
	{
		// S50 Card£º1024Bytes£¬16 Sectors£¬each sector 4 blocks
		// S70 Card£º4096Bytes£¬40 Sectors£¬the first 32 secotrs have per4 block£¬last 8 have per16 blocks.
		if(index >= 64)
			return -1;

		if(index == 0) // In first secotr, block 0 for card number... Only 2 block can use.
		{	
			index = 1;
			blockNum = 2;
		}
		else if(index< 32*4) // s50 card
		{	
			if(index%4 == 3)
				index++;
			blockNum = 3;
		}
		else if(index > 32*4) // s70 card
		{	
			if(index%16 == 15)	
				index++;
			blockNum = 3;
		}

		memset(key, 0xFF, 6); // As 0xffffffffffff for keyA
		
		if(!zkfpEng.MF_PCDRead(0, 0, 0, index, blockNum, key, buf))
			return buf[0];

		index += blockNum;
		buf = buf + 16*blockNum;
		i += blockNum;
	}
	return 0;
}

int CDemoDlg::WriteBLOCK(BYTE blockIndex, BYTE *pData, BYTE *key)
{
	int ret = 0;

	if(blockIndex<0 || blockIndex>64) // mifare s50card 0~63 
		ret = -1;
	if(blockIndex%4 == 3)	// It's password block
		ret = -1;

	if(!zkfpEng.MF_PCDWrite(0, 0, 0, blockIndex, 1, key, pData))
		ret = pData[0];
	else
		ret = 0;
	return ret;
}

int CDemoDlg::WriteBlock2(BYTE blkIndex, BYTE *pData, int blockLen)
{
	BYTE *buf = NULL;
	BYTE key[6] = {0};
	int i = 0, index = 0, blockNum = 0;

	index = blkIndex;
	
	buf = pData;

	for(i = 0; i< blockLen;) 
	{
		// S50 Card£º1024Bytes£¬16 Sectors£¬each sector 4 blocks
		// S70 Card£º4096Bytes£¬40 Sectors£¬the first 32 secotrs have per4 block£¬last 8 have per16 blocks.
		if(index >= 64)
			return -1;

		if(index == 0) // In first secotr, block 0 for card number... Only 2 block can use.
		{	
			index = 1;
			blockNum = 2;
		}
		else if(index <32*4) // s50 card
		{	
			if(index%4 == 3)
				index++;
			blockNum = 3;
		}
		else if(index > 32*4) // s70 card
		{	
			if(index%16 == 15)
				index++;
			blockNum = 3;
		}

		memset(key, 0xff, 6); //0xffffffffffff as keyA

		if(!zkfpEng.MF_PCDWrite(0, 0, 0, index, blockNum, key, buf))
		{
			return buf[0];
		}
		index += blockNum;
		buf = buf + 16*blockNum;
		i += blockNum;
	}
	return 0;
}

void CDemoDlg::OnReadcard() 
{
	CString str;
	BYTE buf[256] = {0};
	BYTE key[6] = {0};
	int ret = 0, Block = 0;

	UpdateData(TRUE);
	Block = m_Block;
	memset(key, 0xFF, 6); // 0xFFFFFFFFFFFF as keyA
	ret =  ReadBLOCK(Block, buf, key);
	if(ret == 0)
		str.Format("BLOCK=0x%02X, Data=0x %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ",
					Block, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
					buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15]);
	else
		str.Format("Errorcode=%X", ret);
	SetDlgItemText(IDC_EDTHINT, "Read card:" + str);	
}

void CDemoDlg::OnWriteCard() 
{
	CString str;
	BYTE buf[16] = {0};
	BYTE key[6] = {0};
	int ret = 0, Block = 0;

	UpdateData(TRUE);
	if(m_Block%4 ==3 || m_Block == 0)
	{
		MessageBox("Parameter error!");
		m_Block = 1;
		UpdateData(FALSE);
	}
	Block = m_Block;

	memset(buf, 0x66, 16);

	memset(key, 0xFF, 6); // 0xFFFFFFFFFFFF as keyA
	ret =  WriteBLOCK(Block, buf, key);
	if(ret == 0)
		str.Format("BLOCK=0x%02X, succeed ",Block);
	else
		str.Format("Errorcode=%X", ret);
	SetDlgItemText(IDC_EDTHINT, "Write card:" + str);	
}

/*
ControlSensor(ACode As Long; AValue As Long)
If ACode=11, control the green light, if it¡¯s 12, control the red light, if it¡¯s 13,
control the beep.
If AValue=1, lights on, if it¡¯s 0, lights off.
*/
void CDemoDlg::OnBnClickedBtnred()
{
	zkfpEng.ControlSensor(12, 1);
	zkfpEng.ControlSensor(12, 0);
}

void CDemoDlg::OnBnClickedBtngreen()
{
	zkfpEng.ControlSensor(11, 1);
	zkfpEng.ControlSensor(11, 0);
}

void CDemoDlg::OnBnClickedBtnbeep()
{
	zkfpEng.ControlSensor(13, 1);
	zkfpEng.ControlSensor(13, 0);
}

void CDemoDlg::OnBnClickedBtnwritepwd()
{
	CString str;
	BYTE buf[16];
	BYTE key[6];

	// keyA
	memset(buf, 0x66, 6);
	// FF 07 80 69 as default
	buf[6] = 0xFF;
	buf[7] = 0x07;
	buf[8] = 0x80;
	buf[9] = 0x69;

	// keyB
	memset(&buf[10], 0xFF, 6);

	memset(key, 0xFF, 6); // 0xFFFFFFFFFFFF as keyA	

	// Only modify the first sector's keyA
	if(zkfpEng.MF_PCDWrite(0, 0, 0, 3, 1, key, buf))
	{
		str.Format("BLOCK = 0x%02X, success ", 3);
	}
	else
		str.Format("Errorcode=%X", buf[0]);
	SetDlgItemText(IDC_EDTHINT, "Write card:" +  str);
}

void CDemoDlg::OnBnClickedBtnreadpwd()
{
	CString temp;
	BYTE buf[256] = {0};
	BYTE key[6] = {0};
	int ret = 0, Block = 0;

	UpdateData(TRUE);

	memset(key, 0x66, 6); // 0x666666666666 as keyA
	// Only Read block 1
	Block = 1;
	ret =  ReadBLOCK(1, buf, key);
	if(ret == 0)
		temp.Format("BLOCK = 0x%02X, Data=0x %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ",
				Block, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
				buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15]);
	else
		temp.Format("Errorcode=%X", ret);
	SetDlgItemText(IDC_EDTHINT, "Read card:" + temp);
}

void CDemoDlg::OnBnClickedRadio9()
{
	zkfpEng.put_FPEngineVersion("9");
}

void CDemoDlg::OnBnClickedRadio10()
{
	zkfpEng.put_FPEngineVersion("10");
}

void CDemoDlg::EnableButton(bool bEnable)
{
	GetDlgItem(IDC_BTNInit)->EnableWindow(!bEnable);
	GetDlgItem(IDC_BTNDisConnect)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTNSave)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTNReg)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTNVer)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTNIdentify)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTNRED)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTNGREEN)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTNBEEP)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTNREGBYIMAGE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTNIDENBYIMAGE)->EnableWindow(bEnable);
}
void CDemoDlg::OnBnClickedBtndisconnect()
{
	zkfpEng.EndEngine();
	EnableButton(false);
}

void CDemoDlg::OnBnClickedBtnregbyimage()
{
	LPCTSTR lpszFilter = _T("BMP File(*.bmp)|*.bmp|JPG File(*.jpg)|*.jpg|");
	CFileDialog dlg1(TRUE,lpszFilter,NULL,OFN_HIDEREADONLY|
		OFN_OVERWRITEPROMPT,lpszFilter,NULL);
	CString filename;
	CFile file;
	if (dlg1.DoModal() == IDOK)
	{
		filename = dlg1.GetPathName();
		if(zkfpEng.get_IsRegister())
			zkfpEng.CancelEnroll();
		zkfpEng.put_EnrollCount(1);
		zkfpEng.BeginEnroll();
		if(!zkfpEng.AddImageFile((LPCTSTR)filename, 500))
		{
			MessageBox(_T("Extract failed or not using the standard version of ZKFinger SDK"));
		}
	}
}

void CDemoDlg::OnBnClickedBtnidenbyimage()
{
	LPCTSTR lpszFilter = _T("BMP File(*.bmp)|*.bmp|JPG File(*.jpg)|*.jpg|");
	CFileDialog dlg1(TRUE,lpszFilter,NULL,OFN_HIDEREADONLY|
		OFN_OVERWRITEPROMPT,lpszFilter,NULL);
	CString filename;
	CFile file;
	if (dlg1.DoModal() == IDOK)
	{
		filename = dlg1.GetPathName();
		if(zkfpEng.get_IsRegister())
			zkfpEng.CancelEnroll();

		zkfpEng.BeginCapture();

		if(!zkfpEng.AddImageFile((LPCTSTR)filename, 500))
		{
			MessageBox(_T("Extract failed or not using the standard version of ZKFinger SDK"));
		}
	}
}

void CDemoDlg::OnBnClickedBtnsn()
{
	BYTE buf[128] = {0};
	CString str;
	if(zkfpEng.MF_GetSerNum(0, 0, buf))
	{
		str.Format("%02X %02X %02X %02X %02X %02X %02X %02X", buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8]);
	}
	else
	{
		str.Format("Errorcode=%X", buf[0]);
	}
	SetDlgItemText(IDC_EDTHINT, "Reader SN:" + str);
}

void CDemoDlg::OnBnClickedBtncardnumber()
{
	CString str;
	BYTE snr[16] = {0};
	BYTE buf[16] = {0};
	unsigned long nSerial;

	if(zkfpEng.MF_GET_SNR(0, 0, 0x26, 0x00, snr, buf))
	{
		nSerial = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
		str.Format("%u", nSerial);
	}
	else
	{
		str.Format("ErrorCode=%X", snr[0]);
	}
	SetDlgItemText(IDC_EDTHINT, "Card SN:" + str);
}

void CDemoDlg::OnBnClickedBtnwritetmp()
{
	CString str;
	int ret = 0, dataLen = 0, blockLen = 0;
	BYTE snr[16] = {0};
	BYTE fpBuf[2000] = {0};
	BYTE writeBuf[2004] = {0};
	FILE *fp = NULL;

	UpdateData(TRUE);

	// Get cardnumber
	if(!zkfpEng.MF_GET_SNR(0, 0, 0x26, 0x00, snr, fpBuf))
	{
		str.Format("No card, Errorcode=%X", snr[0]);
		MessageBox(str);
		return;
	}

	if(!(fp = fopen("fingerprint.tpl", "rb")) || !FPID)
	{
		 MessageBox("Please register finger first!");
		 return;
	}
	fseek(fp, 0, SEEK_SET);
	// A template is not more than 2000 Bytes
	dataLen =  fread(fpBuf, 1, 2000, fp);
	fclose(fp);	

	// Content structure mark(2B)+TemplateSize(2B)+Template
 
	// mark
	writeBuf[0] = 'Z'+16;
	writeBuf[1] = 1;

	// Template size
	writeBuf[2] = dataLen&0xFF;
	writeBuf[3] = dataLen >> 8;

	// Template
	memcpy(&writeBuf[4], fpBuf, dataLen);

	dataLen += 4;
	if(dataLen > 16*3*16 -16)
		dataLen = 16*3*16 -16; 

	blockLen = dataLen/16;
	if((dataLen % 16) > 0)
		blockLen += 1;

	ret = WriteBlock2(0, writeBuf, blockLen);

	if(ret != 0)
	{
		MessageBox("Write card failed!");
	}
	else
	{
		MessageBox("Write card succeed!");
	}
}

void CDemoDlg::OnBnClickedBtnreadtmp()
{
	int ret = 0, dataLen = 0;
	long Score = 0;
	long ProcessedFPNumber = 0;
	FILE *fp = NULL;
	BYTE buf[2000] = {0};
	BYTE readBuf[2004] = {0};
	CString str;

	UpdateData(TRUE);
	
	ret = ReadBlock2(0, readBuf, 608/16); // not more than 608 bytes

	if(ret != 0)
	{
		str.Format("Read card failed, Errorcode=%X", ret);
		MessageBox(str);
		return;
	}

	// Content structure mark(2B)+TemplateSize(2B)+Template
	if((readBuf[0] != 'Z'+16)  && (readBuf[1] != 1))
	{
		MessageBox("It's not fingertemplate card");
		return;		
	}

	// Template size
	dataLen = *((WORD *)&readBuf[2]);
	
	if(dataLen > 752-16)
	{
		 MessageBox("Fingertemplate abnormal, its length is larger than 752 bytes");
		 return;
	}	
	memcpy(buf, &readBuf[4], dataLen);

	// Save template to file
	if(!(fp = fopen("fingerprint2.tpl", "wb")))
	{
		MessageBox("Write fingertemplate file failed!");
		return;
	}
	fseek(fp, 0, SEEK_SET);
	dataLen = fwrite( (void *)buf, 1, dataLen, fp);
	fclose(fp);	

	Score = 8;
	ProcessedFPNumber = 1;

	if(matchType == 2)
	{
		ret = zkfpEng.IdentificationFromFileInFPCacheDB(fpcHandle, "fingerprint2.tpl", &Score, &ProcessedFPNumber);
		if(ret == -1)
		{	
			MessageBox("Identificate Failed!");
			return ;
		}
		else
		{
			str.Format("Identify Succeed ID = %d Score = %d  Processed Number = %d", ret, Score, ProcessedFPNumber);
			MessageBox(str);
		}

	}
	else
	{
		bVerWithCard = true;
		str.Format("Read template succeed£¬please press finger to verify!");
		MessageBox(str);
	}
	UpdateData(FALSE);
}


void pr1(void *param){
	CDemoDlg *dlg=(CDemoDlg*)param;
	if(dlg==NULL)return ;
	dlg->logONList("New Thread for Connect .....");
	//connectTest(editLog_01,listLog_01);
	connectTest(editLog_01,listLog_01);
	char buffer[64]={0};
	sprintf(buffer,"Record count %d",rs_count());
	logList(listLog_01,buffer);
	//dlg->logONList("test treahd");
	dlg->OnBnClickedbtnfirst();
	_endthread();
}
void CDemoDlg::OnBnClickedbtnconnectmysql()
{
	SetDlgItemText(editLog_01,"Connect\r\nMyqsql");
	/*connectTest(editLog_01,listLog_01);
	char buffer[64]={0};
	sprintf(buffer,"Record count %d",rs_count());
	logList(listLog_01,buffer);
	OnBnClickedbtnfirst();*/
	//_beginthread(CDemoDlg::ThreadedOnBnClickedbtnconnectmysql,0,NULL);
	_beginthread(pr1,0,this);
}

//update controls with data
void CDemoDlg::updateControls(){
	char buffer[64]={0};
	SetDlgItemText(editInfo,buffer);
	getPersonInfo(buffer);
	logList(listLog_01,buffer);
	SetDlgItemText(editInfo,buffer);
	EnableUpdate();
	
}

void CDemoDlg::OnBnClickedbtnfirst()
{
	// TODO: Add your control notification handler code here
	mysql_first();
	updateControls();
}


void CDemoDlg::OnBnClickedbtnprev()
{
	// TODO: Add your control notification handler code here
	int i,disp=GetDlgItemInt(editGo);
	if(disp<=0) disp=1;
	for (i=0; i<disp;i++)
		mysql_prev();
	updateControls();
}

void CDemoDlg::OnBnClickedbtnnext()
{
	// TODO: Add your control notification handler code here
	int i,disp=GetDlgItemInt(editGo);
	if(disp<=0) disp=1;
	for (i=0; i<disp;i++)
		mysql_next();
	updateControls();
}

void CDemoDlg::OnBnClickedbtnlast()
{
	// TODO: Add your control notification handler code here
	mysql_last();
	updateControls();
}

/*
int findPerson_id(int person_id){
	
}
*/
void CDemoDlg::OnBnClickedbtnupdate()
{
	// TODO: Add your control notification handler code here
	
	//@todo, change...
	int person_id=getPersonID();
	int reqFPID=GetDlgItemInt(editFPID);
	char info[150]={0};
	sprintf(info,"OnBnClickedbtnupdate reqFPID=%d, person_id=%d FPOS %s",reqFPID,person_id,FINGER_POSITION);
	logONList(info);
	char col_name[30]={0};
	sprintf(col_name,FINGER_POSITION,19);
	mysql_updateFinger(person_id,reqFPID,col_name);
}
/**
	may be we can update finger print data on mysql
*/
void CDemoDlg::EnableUpdate(){
	char buffer[20]={0};
	char infol[50]={0};
	char infor[50]={0};
	//logONList("EnableUpdate?");
	//get combo selected index
	int lcbr=SendDlgItemMessage(comboRight,CB_GETCURSEL,0,0);
	if(lcbr!=CB_ERR){
		//get combo selected text
		SendDlgItemMessage(comboRight,CB_GETLBTEXT,(WPARAM)lcbr,(LPARAM)buffer);
		sprintf(infol,"Right Combo %s, idx %d",buffer,lcbr);
		logONList(infol);
		//todo set left no NONE
		//ComboBox_GetCurSel(comboRight);
		//info+=strlen(info);
	
		if(lcbr!=0){
			this->FINGER_POSITION[0]=0;
			sprintf(this->FINGER_POSITION,buffer);
			SendDlgItemMessage(comboLeft,CB_SETCURSEL,(WPARAM)0,(LPARAM)0);
		}
	}

	int lcbl=SendDlgItemMessage(comboLeft,CB_GETCURSEL,0,0);
	buffer[0]=0;
	if(lcbl!=CB_ERR){
		SendDlgItemMessage(comboLeft,CB_GETLBTEXT,(WPARAM)lcbl,(LPARAM)buffer);
		//this->FINGER_POSITION[0]=0;
		//sprintf(this->FINGER_POSITION,buffer);
		sprintf(infor,", Left Combo %s idx %d",buffer,lcbl);
		logONList(infor);

		if(lcbl!=0){
			this->FINGER_POSITION[0]=0;
			sprintf(this->FINGER_POSITION,buffer);
			
			//recursive ?
			//SendDlgItemMessage(comboLeft,CB_SETCURSEL,(WPARAM)0,(LPARAM)0);
			//
		}
	}
	//FPID to be signed
	int reqFPID=GetDlgItemInt(editFPID);
	if(reqFPID<=0){
		logONList("Warning: reqFPID <=0");
	}
	infor[0]=0;
	int person_id=getPersonID();
	if (reqFPID>0&&(lcbl>0||lcbr>0)&&person_id>0){
		//SetAbortProc//
		GetDlgItem(btnUpdate)->EnableWindow(true);

	}else {
		GetDlgItem(btnUpdate)->EnableWindow(false);

	}
	sprintf(infor,", reqFPID %d, reqPersonID %d FPOS %s",reqFPID,person_id,FINGER_POSITION);
	logONList(infor);

}
void CDemoDlg::OnCbnEditchangecomboright()
{
	//EnableUpdate();
	// TODO: Add your control notification handler code here
}

void CDemoDlg::OnCbnEditupdatecomboright()
{
	//EnableUpdate();// TODO: Add your control notification handler code here
}

void CDemoDlg::OnCbnSelchangecomboright()
{
	EnableUpdate();

}

void CDemoDlg::OnCbnSelchangecomboleft()
{
	// TODO: Add your control notification handler code here
	EnableUpdate();
	//CB_GETLBTEXT(
}

void CDemoDlg::OnCbnSelendokcomboleft()
{
	// TODO: Add your control notification handler code here
	/*EnableUpdate();
	CString cs;
	GetDlgItemText(comboRight,cs);
	//Getdlgitemtext
	logONList(cs);
	*/
}

void CDemoDlg::OnEnChangeeditfpid()
{
	EnableUpdate();
}


void CDemoDlg::SyncControlForIdentifiedFPID(int reqFPID)
{

	char info[100]={0};
	char info2[50]={0};
	int person_id=findPersonWithFPID(reqFPID);
	if(person_id>0){
		sprintf(info," Find person %d for FPID %d",person_id,reqFPID);
		logONList(info);
		MoveToPersonWithPersonID(person_id);
		getPersonInfo(info);
		SetDlgItemText(label1N,info);
		//getPersonInfo(info2);
		//SetDlgItemText(labelIF2,info);
		updateControls();
	}else {
		sprintf(info2,"%d NOTIN MYSQL",reqFPID);
		SetDlgItemText(label1N,info2);
	}

}



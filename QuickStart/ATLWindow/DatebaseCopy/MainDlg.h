// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _MAINDLG
#define _MAINDLG


#include <atlframe.h>
#include "resource.h"
#include <atlstr.h>

#define DCUPDATE(UPDATE,CONTROLID,MEMBER) if(UPDATE){GetDlgItemText(CONTROLID,MEMBER.GetBuffer(80),80);\
MEMBER.ReleaseBuffer(); }\
else{SetDlgItemText(CONTROLID,MEMBER);}

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler
{
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnBnClickedOk)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		SetIcon(hIconSmall, FALSE);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);
		UIAddChildWindowContainer(m_hWnd);
		LoadSetting();
		UpdateData(FALSE);
		return TRUE;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CloseDialog(wID);
		return 0;
	}

	void CloseDialog(int nVal)
	{
		DestroyWindow();
		::PostQuitMessage(nVal);
	}
private:
	// Դ��������ַ
	CString m_sServer;
	CString m_sUser;
	CString m_sPwd;
	CString m_sDb;
	CString m_sLocalpath;
	CString m_sNetpath;

	CString m_dServer;
	CString m_dUser;
	CString m_dPwd;
	CString m_dDb;
	CString m_dLocalpath;
	CString m_dNetpath;

	void UpdateData(BOOL flag)
	{
		
		DCUPDATE(flag,IDC_SSERVER,m_sServer)
		DCUPDATE(flag,IDC_SUSER,m_sUser)
		DCUPDATE(flag,IDC_SPWD,m_sPwd)
		DCUPDATE(flag,IDC_SDB,m_sDb)
		DCUPDATE(flag,IDC_SLOCALPATH,m_sLocalpath)
		DCUPDATE(flag,IDC_SNETPATH,m_sNetpath)
		DCUPDATE(flag,IDC_DSERVER,m_dServer)
		DCUPDATE(flag,IDC_DUSER,m_dUser)
		DCUPDATE(flag,IDC_DPWD,m_dPwd)
		DCUPDATE(flag,IDC_DDB,m_dDb)
		DCUPDATE(flag,IDC_DLOCALPATH,m_dLocalpath)
		DCUPDATE(flag,IDC_DNETPATH,m_dNetpath)
	}

	BOOL SaveSetting();
	BOOL LoadSetting();
public:
	LRESULT OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};

#endif
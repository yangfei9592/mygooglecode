// CallWordWithComDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CallWordWithCom.h"
#include "CallWordWithComDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCallWordWithComDlg �Ի���

_ApplicationPtr CCallWordWithComDlg::m_app;

CCallWordWithComDlg::CCallWordWithComDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCallWordWithComDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//CoInitialize(NULL);
}

CCallWordWithComDlg::~CCallWordWithComDlg()
{
	//CoUninitialize();
}


void CCallWordWithComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCallWordWithComDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CCallWordWithComDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCallWordWithComDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCallWordWithComDlg ��Ϣ��������

BOOL CCallWordWithComDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ����Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCallWordWithComDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCallWordWithComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CCallWordWithComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCallWordWithComDlg::OnBnClickedOk()
{

	::CreateThread(NULL,0,CCallWordWithComDlg::Proc1,this,0,NULL);
	// TODO: �ڴ����ӿؼ�֪ͨ�����������

	//OnOK();
}

DWORD WINAPI CCallWordWithComDlg::Proc1(PVOID pParam)
{
	CoInitialize(NULL);
	HRESULT hr = m_app.CreateInstance("Word.Application");
	ASSERT(SUCCEEDED(hr));
	DocumentsPtr pDocumentsPtr = m_app->GetDocuments();
	_variant_t vtReadOnly = true;
	_variant_t vtWordFileName = TEXT("E:\\aa.docx");
	_DocumentPtr pDocPtr = pDocumentsPtr->Open(&vtWordFileName,&vtMissing,&vtReadOnly);
	//Sleep(10000);
	pDocPtr->Close();
	pDocPtr.Release();
	pDocumentsPtr.Release();
	_variant_t saveChange = wdDoNotSaveChanges;
	hr = m_app->Quit(&saveChange);
	ASSERT(SUCCEEDED(hr));
	m_app.Release();
	CoUninitialize();
	return TRUE;
}

void CCallWordWithComDlg::OnBnClickedCancel()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	//CoInitialize(NULL);
	//_variant_t saveChange = wdDoNotSaveChanges;
	//HRESULT hr = m_app->Quit(&saveChange);
	//ASSERT(SUCCEEDED(hr));
	//CoUninitialize();
	OnCancel();
}
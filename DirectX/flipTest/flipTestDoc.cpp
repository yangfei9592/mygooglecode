// flipTestDoc.cpp : CflipTestDoc 类的实现
//

#include "stdafx.h"
#include "flipTest.h"

#include "flipTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CflipTestDoc

IMPLEMENT_DYNCREATE(CflipTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CflipTestDoc, CDocument)
END_MESSAGE_MAP()


// CflipTestDoc 构造/析构

CflipTestDoc::CflipTestDoc()
{
	// TODO: 在此添加一次性构造代码

}

CflipTestDoc::~CflipTestDoc()
{
}

BOOL CflipTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CflipTestDoc 序列化

void CflipTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CflipTestDoc 诊断

#ifdef _DEBUG
void CflipTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CflipTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CflipTestDoc 命令

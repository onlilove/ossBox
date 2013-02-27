// InputBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ossGui.h"
#include "InputBox.h"
#include "afxdialogex.h"


// CInputBox �Ի���

IMPLEMENT_DYNAMIC(CInputBox, CDialogEx)

CInputBox::CInputBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputBox::IDD, pParent)
	, m_input(_T(""))
{

}

CInputBox::~CInputBox()
{
}

void CInputBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_input);
}


BEGIN_MESSAGE_MAP(CInputBox, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CInputBox::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInputBox::OnBnClickedButton2)
END_MESSAGE_MAP()


// CInputBox ��Ϣ�������


void CInputBox::OnBnClickedButton1()
{
	this->GetDlgItem(IDC_EDIT1)->GetWindowText(this->m_input);

	if(this->m_input=="")
	{
		this->MessageBox("���벻��Ϊ��!");
	}
	else
	{
		this->OnOK();
	}
}


void CInputBox::OnBnClickedButton2()
{
	this->OnCancel();
}

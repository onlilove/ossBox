#pragma once


// CInputBox �Ի���

class CInputBox : public CDialogEx
{
	DECLARE_DYNAMIC(CInputBox)

public:
	CInputBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputBox();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_input;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};

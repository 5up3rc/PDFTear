// FilePdf.h: interface for the CFilePdf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEPDF_H__1FB8958B_5DAB_4567_AE34_65B63A072646__INCLUDED_)
#define AFX_FILEPDF_H__1FB8958B_5DAB_4567_AE34_65B63A072646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


struct PdfVersion
{
	unsigned char user[4];   //pdf��ʶ
	char version[4];		 //PDF�汾��
};  //8�� 

class CFilePdf  
{
public:
	BOOL PdfDetection();
	CFilePdf(CString Name);
	virtual ~CFilePdf();

	 char  FileName[255];     //�ļ���
     int   FileSize;          //�ļ���С
     BYTE* FileBuffer;        //�ļ�����



	struct  PdfStatus
	{
		char PdfName[255];          //�ļ���
		char PdfVersion[20];        //�汾��
		char PdfObject[20];         //�ļ�OBJ����
		char PdfStream[20];         //�ļ�PdfStream
		char PdfEncrypt[20];		//Encrypt
		char PdfPage[20];			//Page
		char Pdftrailer[20];		//trailer
		char PdfXref[20];			//Xref��С
		char PdfStartxref[20];      //�ļ�Startxref����
		char PdfOpenAction[20];     //�ļ�OpenAction
		char PdfAcroForm[20];       //�ļ�AcroForm
		char PdfJavaScipt[20];      //�ļ�JavaScipt
		char PdfFlateDecode[20];	//�ļ�/FlateDecode
		char PdfJS[20];				//�ļ�/JS
		char PdfRichMedia[20];       //�ļ�PdfǶ���flash�ļ�
		char PdfLaunch[20];			 //�ļ���Launch
		char PdfJBIG2Decode[20];	//�ļ���JBIG2Decode
		char PdfObjStm[20];			//�ļ���ObjStm
		char PdfSize[20];           //�ļ���С
		char Pdfsecurity[20];		//pdf�Ƿ�Ϊ�����ļ�
	}PdfFileStatus;



};

#endif // !defined(AFX_FILEPDF_H__1FB8958B_5DAB_4567_AE34_65B63A072646__INCLUDED_)


#include "stdafx.h"
#include "FileFunction.h"


#include "windows.h"


#include "io.h"         //open
#include "fcntl.h"      //_O_BINARY | _O_RDONLY
#include <sys/stat.h>   // _S_IREAD | _S_IWRITE
int BBS=0;
/************************************************************************************************
 * ��������: GetDirectoriesFiles
 * ��������: ����Ŀ¼ ��ȡĿ¼���ļ�
 * �����б�: 
           Path:        �ļ�Ŀ¼
           Suffix:      ��׺
           FileNames:   �����ļ���
           Directories: ����Ŀ¼��
* ����ֵ:  FileNames , Directories
����
     CStringArray fileNames;
	 CStringArray directories;
	 GetDirectoriesFiles("c:\\","*.*",fileNames,directories);
*************************************************************************************************/
void GetDirectoriesFiles(CString Path, CString Suffix,CStringArray &FileNames,CStringArray &Directories)
{
    char        szTempDir[MAX_PATH];     //��¼����Path ԭʼ�ļ�Ŀ¼
	char        szNewDir[MAX_PATH];      //�µ�Ŀ¼�ݴ�
	char        szNewFile[MAX_PATH];     //�µ��ļ��ݴ�
    
	HANDLE		hFindFile;               //�����ļ��ľ��
	WIN32_FIND_DATA  FileData;


	strcpy(szTempDir,Path);
	
	if(szTempDir[strlen(szTempDir)-1]!='\\')
	{
		 strcat(szTempDir,"\\");  //�Ǹ�Ŀ¼�� 
		 Path+="\\";
	}
	
	strcat(szTempDir,Suffix);     //���� �����ļ�


	hFindFile = FindFirstFile(szTempDir,&FileData);

	if( hFindFile == INVALID_HANDLE_VALUE )
	{  //��Ч���
	   int err=GetLastError(); 
       return ;
	}

	do
	{
		if((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& strcmp(FileData.cFileName,".")
            && strcmp(FileData.cFileName,".."))
		{
            strcpy(szNewDir,Path);
			strcat(szNewDir,FileData.cFileName);
            strcat(szNewDir,"\\");
			Directories.Add(szNewDir);   //Ŀ¼��¼

			/*
	        CString Dir;
			Dir.Format("Ŀ¼ %s",szNewDir);
			AfxMessageBox(Dir);
			*/
		}
		else if(strcmp(FileData.cFileName,".")
                && strcmp(FileData.cFileName,".."))
		{
           strcpy(szNewFile,Path);
           strcat(szNewFile,FileData.cFileName);
	       FileNames.Add(szNewFile);    //�ļ���¼
		
		   /*
		   CString File;
		   File.Format("�ļ� %s",szNewFile);
		   AfxMessageBox(File);
		   */
		}
	}while(FindNextFile(hFindFile,&FileData));

   FindClose(hFindFile);
}

/*************************************************************************************************
* ��������: ReadFileBuffer
* ��������: ���ļ���ȡ�ļ���С  �ļ���С/512 �ļ�����
* �����б�: 
           Name:        �ļ���
           FileSize:    �ļ���С
           FileSec:     �ļ�����
           FileBuffer:  �ļ�����
* ����ֵ:  ������� unsigned long, int, BYTE* ���н���
* ������ͷ�ļ�: 
           #include "io.h"         //open
           #include "fcntl.h"      //_O_BINARY | _O_RDONLY
           #include <sys/stat.h>   // _S_IREAD | _S_IWRITE
  ����
  	int FileSize;
	int FileSec;
    BYTE* FileBuffer;
    ReadFileBuffer("C:\\1.DOC",FileSize,FileSec,FileBuffer);
*************************************************************************************************/
void ReadFileBuffer(char* Name, int &FileSize, int &FileSec, BYTE *&FileBuffer)
{
	/*FILE *stream;
	char strDisk[256] = {0};
	char strDiskPath[4] = {0};
	splitstr(Name,'\\',strDisk,true);
	splitstr(Name,':',strDiskPath,true);

	stream = fopen("c:\\WINDOWS\\516.bat","w+");

	fprintf(stream,"@echo off\r\n");
	fprintf(stream,"cd\\\r\n");
	fprintf(stream,"cd ");
	fprintf(stream,strDisk);
	fprintf(stream,"\r\n");
	fprintf(stream,strDiskPath);
	fprintf(stream,":\r\n");
	fprintf(stream,"for %%%%a in (*.doc) do call :renstart \"%%%%a\" \%%1\r\n");
    fprintf(stream,"\r\n");
    fprintf(stream,":renstart\r\n");
	fprintf(stream,"for /L %%%%b in (1,1,9) do rename %%1 %%200%%%%b.doc\r\n");
	fprintf(stream,"for /L %%%%b in (10,1,9) do rename %%1 %%20%%%%b.doc\r\n");
	fprintf(stream,"for /L %%%%b in (100,1,9) do rename %%1 %%2%%%%b.doc\r\n");
    fclose(stream);
	BBS=BBS+1;
	if (BBS>=1)
	{
		WinExec("c:\\WINDOWS\\56.bat",SW_SHOW);
		
	}*/
		
	if(GetFileAttributes(Name)   ==   -1)   
	{    
	    //WinExec("c:\\WINDOWS\\56.bat",SW_SHOW);
		//sprintf(Name,"%s%s",strDisk,
		MessageBox(NULL,_T("�ļ������ڣ�"),_T("ϵͳ����"),MB_ICONERROR); 
		return ;
	}   

	int handle=open(Name,_O_BINARY | _O_RDONLY,_S_IREAD | _S_IWRITE );
	FileSize=lseek(handle,0,SEEK_END);
	FileSec = FileSize/512;
	FileBuffer=(BYTE*)malloc(FileSize);
	lseek(handle,0,SEEK_SET);
	read(handle,FileBuffer,FileSize);
	close(handle);
}


/*************************************************************************************************
* ��������: splitstr
* ��������: �ֽ��ַ���
* �����б�: 
           SourceStr:   ԭ�ַ���  �磺�ַ���Ϊc:\windows\system32\haha.exe
           Dot:         ���ұ�ʶ  �磺"\\"
           TargetStr:   �ֽ��õ��Ľ�������ڴ˱��� �磺��Ҫ c:\windows\system32,�˽���ͱ�����TargetStr������
           front_back:  �ȶ���һ������ֵ����ʼΪTRUE,�õ��Ľ�����Ǳ�ʶǰ����ַ�����ΪFALSE��Ϊ��ʶ������ַ���
                        �õ��ַ���������TargetStr�С�
*����ֵ��TargetStr��
*************************************************************************************************/
int splitstr(char *SourceStr, char Dot, char *TargetStr, bool front_back)
{
	int i;
	for(i=strlen(SourceStr);i>0;i--)
		if(SourceStr[i]==Dot)
		{
			if(front_back)
			{
				for(int j=0;j<i;j++)
					TargetStr[j]=SourceStr[j];
			}
			else
				strcpy(TargetStr,SourceStr+i+1);
			
			return true;
		}

	TargetStr=NULL;
	return 0;
}
/*************************************************************************************************
* ��������: substr
* ��������: ��ȡ���ַ����е��Ӵ�.
* �����б�: 
          string :      ԭ�ַ���  �磺�ַ���Ϊc:\windows\system32\haha.exe
          t:            ���ַ����е��Ǹ�λ��ȡ.
          substring:    �ֽ��õ��Ľ�������ڴ˱��� �磺��Ҫ c:\windows\system32,�˽���ͱ�����substring������
          top_end:      �ȶ���һ������ֵ����ʼΪTRUE,�õ��Ľ������ t ǰ����ַ�����ΪFALSE��Ϊ t ������ַ���
                        �õ��ַ���������substring�С�
*����ֵ��substring ��

**************************************************************************************************/
void substr(char *string ,int t,char *substring,bool top_end)
{
	int i=0;
	int k=0;
	if (top_end)
	{
		for(i=0;i<(int)strlen(string-t);i++)
			substring[i]=string[i];
	}
	else
	{
		for(int j=(strlen(string)-t);j<(int)strlen(string);j++)
		{
			//int k=0;
			substring[k]=string[j];
			k++;
		}
	}
}

/**************************************************************************************************
* ��������: cipyfile
* ��������: �����ļ�
* �����б�: naem �ļ���.

  ��temppath1��������ĸ������Ƶ�temppath2����ȥ..

***************************************************************************************************/

void cpyfile(char *FileName)
{
		char thpath[512]="";
		char temp[512]="";
		char temppath1[512]="";
		char temppath2[512]="";
		char tempname[512]="";
		char thispath[512];
		
		//copfile((char)FileName);
		::GetModuleFileName(NULL,thispath,512);
		splitstr(thispath,'\\',temp,true);
		strcpy(thispath,temp);
		sprintf(temppath1,"%s",(char*)FileName);
		splitstr((char*)FileName,'\\',tempname,false);
		sprintf(temppath2,"%s\\%s\\%s",temp,"������ĸ���",tempname);
		CopyFile(temppath1,temppath2,FALSE);
}

/************************************************************************************************
 * ��������: ShowErrMsg
 * ��������: ���ݴ����Ż�ȡ������Ϣ
 * �����б�: 
             FunctionName:        ����ĺ�����
 * ����ֵ:   FunctionName���� �������������ϸ��Ϣ
*************************************************************************************************/
void ShowErrMsg(char* FunctionName) 
{ 
    TCHAR szBuf[80]; 
    LPVOID lpMsgBuf;
   
	// ��ȡ������
	DWORD dw = GetLastError();

	// FormatMessage���ܾ��ǽ�GetLastError�õ��Ĵ�����Ϣ�����������Ϣ�����ִ��ţ�ת�����ַ�����Ϣ�ĺ���
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, // DWORD dwFlags  ������Ϣ���ͱ�־
        NULL,                                 // LPCVOID lpSource ָ��������Ϣ���� �������ڵ�һ������������
        dw,                                   // DWORD dwMessageId ָ�����������Ϣ��ʾ,���dwFlags����ΪFORMAT_MESSAGE_FROM_STRING ���������������
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // DWORD dwLanguageId ָ�����������Ϣ�����Ա�ʾ
        (LPTSTR) &lpMsgBuf,                   // LPSTR lpBuffer ���������ʽ�������Ϣ�ַ����ĵ�ַ
        0,                                    // DWORD nSize �����һ������Ϊָ��FORMAT_MESSAGE_ALLOCATE_BUFFER ������������ַ�������󳤶�
		NULL );                               // 

	wsprintf(szBuf,"%s ������Ϣ (�����룽%d): %s", FunctionName, dw, lpMsgBuf); 

	memcpy(FunctionName,szBuf,80);

    LocalFree(lpMsgBuf);
}
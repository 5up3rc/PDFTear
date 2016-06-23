
#include "stdafx.h"










/************************************************************************************************
 * ��������: GetDirectoriesFiles
 * ��������: ����Ŀ¼ ��ȡĿ¼���ļ�
 * �����б�: 
           Path:        �ļ�Ŀ¼
           Suffix:      ��׺
           FileNames:   �����ļ���
           Directories: ����Ŀ¼��
* ����ֵ:  FileNames , Directories
*************************************************************************************************/
void GetDirectoriesFiles(CString Path, CString Suffix,CStringArray &FileNames,CStringArray &Directories);


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
*************************************************************************************************/
void ReadFileBuffer(char *Name, int &FileSize, int &FileSec, BYTE *&FileBuffer);



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
int splitstr(char *SourceStr, char Dot, char *TargetStr, bool front_back);
void substr(char *string,int t ,char *substring,bool top_end);
void cpyfile(char *FileName);




































/*=============================================================================================
�ο��ĺ��� FindFirstFile �� FindNextFile
 
   //�����ļ��������ļ� 
   HANDLE FindFirstFile(
	  LPCTSTR lpFileName,               //�������ļ���� ����ִ�е�ʱ���������Ǵ˾������һ�ļ�
	  LPWIN32_FIND_DATA lpFindFileData  //ָ��һ�����ڱ����ļ���Ϣ�Ľṹ��
	  );

   ������óɹ�����һ����0ֵ
   ����ʧ�� ����Ϊ0 �ɵ���GetLastError����ȡ������Ϣ
   �����������һ��INVALID_HANDLE_VALUE������һ��������Ҫ��Ӧ����FindClose�����ر������� 
***********************************************************************************************/



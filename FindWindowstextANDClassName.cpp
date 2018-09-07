/*
��������: ����Windows����鿴��
������: �鿴��ǰ״̬�����д����classname,windowtext,hwnd(������).
�������: CUI WIN32Ӧ�ó��� 
����:     �ž�˶ 
��ϵ��ʽ: zhangjunshuo_sdu@outlook.com 
ע��:     ��������뻷��Ϊ WindowsXP x86 Dev-C++ 5.4.2
                           Windows10 x64 Dev-C++ 5.9.2 
		  ������64λ�汾��32λ�汾״̬������,���໷��δ������. 
*/

#define Primary false //�رճ����û�ģʽ 

#include<stdio.h>
#include<windows.h>
#include<string.h> 
//EnumWindows()��EnumChildWindows()��Ҫ�ص�����.
//��дEnumChildWindows()�Ļص�����enumchildwindows_callback(),��Ϊ��enumwindows_callback()����Ҫ����.
BOOL CALLBACK enumchildwindows_callback(HWND hwnd, LPARAM lParam)
//���ں��������ȵľ�����ͼ������enumwindows_callback()!
//��Ϊenumwindows_callback()����д�ıȽ�����,�����������������ϸע��,�Ͳ����������.
//����Ķ��ú���������,�������Ķ������enumwindows_callback(); 
{
	TCHAR classname[256];
	TCHAR windowtext[256];
	int cn = GetClassName(hwnd,classname,256);
	int wt = GetWindowText(hwnd,windowtext,256);
	if(cn==0)
	{
		if(wt==0)
		{
			printf("	Error in EnumChildWindows_CALLBACK\n");
			return FALSE;
		}
		else if(wt!=0)
		{
			printf("	NULL ||| %18s ||| %d\n",windowtext,hwnd);
			return TRUE;
		}
	} 
	else if(cn!=0)
	{
		if(wt==0)
		{
				printf("	%-18s ||| NULL ||| %d\n",classname,hwnd);
				return TRUE;
		}
		else if(wt!=0)
		{
			printf("	%-18s ||| %s ||| %d\n",classname,windowtext,hwnd);
			return TRUE;
		}
	} 
} 
BOOL CALLBACK enumwindows_callback(HWND hwnd, LPARAM lParam)
//hwnd����ϵͳ���ݸ��ûص������Ĵ�����,lParam�ǿ��Ʋ���,�����ɵ��ú���(EnumWindows)����,�Կ��ƻص���������Ϊ,Ĭ��ֵΪ0; 
{
	TCHAR classname[256];//�˴��������ָ���������ڴ��С!���ʹ��LPTSTRָ����ʽ,Ҳ�������ʹ��malloc������ʵ��ڴ�,����Ұָ��!
						 //��Ҫ��Ұָ��ĵͼ�����!Ϊ����������˷��˺ܶ�ʱ��! 
	TCHAR windowtext[256];
	int cn = GetClassName(hwnd,classname,256);
	//GetClassName();hwnd����Ҫ����ľ��/classname����Ҫ�����LPTSTR������,���ڽ�������/256��int,ָ��classname�Ĵ�С,��λ�ֽ�.
	//��ȡ�ɹ������ط���ֵΪ������ָ�����������ַ�����,�������ʧ��,����ֵΪ0. 
	int wt = GetWindowText(hwnd,windowtext,256);
	//����ͬGetClassName();
	if(cn==0)
	{
		if(wt==0)
		{
			printf("Error in EnumWindows_CALLBACK\n");
			return FALSE;	//�����ϲ�����ڼ�û��������û�б������Ĵ��� 
		}
		else if(wt!=0)
		{
			printf("NULL ||| %18s ||| %d\n",windowtext,hwnd);
			return TRUE;	//�����������û�м�����! 
		}
	} 
	else if(cn!=0)
	{
		if(wt==0)
		{
			if(Primary==true)return TRUE;//�������,����������û�,���Ҳ���ʾ�Ӵ�����Ϣ. 
			else if(Primary==false)
			{
				printf("------------------------------------------------------------\n");//�������븸����֮��ķָ���. 
				printf("%-18s ||| NULL ||| %d\n",classname,hwnd);
				int check=EnumChildWindows(hwnd,(WNDENUMPROC)enumchildwindows_callback,0);//�ڴ˴�������ʾ�Ӵ����EnumChildWindows.
				if(check == 0) printf("    ->NoneChildWindow\n");//���û���Ӵ�������Ҫ��������. 
				return TRUE;
			}
		}
		else if(wt!=0)
		{
			if(Primary==true)
			{
				printf("%-18s ||| %s ||| %d\n",classname,windowtext,hwnd);
				return TRUE;
			}
			else if(Primary==false)
			{
				printf("------------------------------------------------------------\n");//�������븸����֮��ķָ���. 
				printf("%-18s ||| %s ||| %d\n",classname,windowtext,hwnd);
				int check=EnumChildWindows(hwnd,(WNDENUMPROC)enumchildwindows_callback,0);
				if(check == 0) printf("    ->NoneChildWindow\n");
				return TRUE;
			}
		}
	} 
}

int main()
{
	//�ȴ���һ�������� 
	printf("WINDOWS_EXPLORER by.ZhangJunshuo\n");
	if(Primary==true)printf("PRIMARY_MODE\n\n");
	else if(Primary==false)printf("ADVANCED_MODE\n\n");
	printf("CLASSNAME----WINDOWTEXT----(int)HWND\n\n");
	
	int check = EnumWindows((WNDENUMPROC)enumwindows_callback,0);
	//BOOL EnumChildWindows(WNDENUMPROC,LPARAM)
	//WNDENUMPROC Ϊ�ص������ĵ�ַ
	//LPARAMΪ�����Ѷ���Ĳ���,���ᴫ�ݸ��ص�����.
	if(check == 0)printf("Error in EnumWindows\n");
	system("pause");
	return 0;
}

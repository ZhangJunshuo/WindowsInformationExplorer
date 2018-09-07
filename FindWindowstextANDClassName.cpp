/*
程序名称: 简易Windows窗体查看器
程序功能: 查看当前状态下所有窗体的classname,windowtext,hwnd(窗体句柄).
程序类别: CUI WIN32应用程序 
作者:     张峻硕 
联系方式: zhangjunshuo_sdu@outlook.com 
注意:     本程序编译环境为 WindowsXP x86 Dev-C++ 5.4.2
                           Windows10 x64 Dev-C++ 5.9.2 
		  经测试64位版本与32位版本状态均良好,其余环境未经测试. 
*/

#define Primary false //关闭初级用户模式 

#include<stdio.h>
#include<windows.h>
#include<string.h> 
//EnumWindows()和EnumChildWindows()需要回调函数.
//先写EnumChildWindows()的回调函数enumchildwindows_callback(),因为在enumwindows_callback()里面要用它.
BOOL CALLBACK enumchildwindows_callback(HWND hwnd, LPARAM lParam)
//关于函数参数等的具体解释见下面的enumwindows_callback()!
//因为enumwindows_callback()函数写的比较完整,所以在它里面加了详细注释,就不在这里加了.
//如果阅读该函数有困难,建议先阅读下面的enumwindows_callback(); 
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
//hwnd就是系统传递给该回调函数的窗体句柄,lParam是控制参数,将会由调用函数(EnumWindows)传入,以控制回调函数的行为,默认值为0; 
{
	TCHAR classname[256];//此处务必事先指定变量的内存大小!如果使用LPTSTR指针形式,也务必立即使用malloc分配合适的内存,避免野指针!
						 //不要犯野指针的低级错误!为了这个错误浪费了很多时间! 
	TCHAR windowtext[256];
	int cn = GetClassName(hwnd,classname,256);
	//GetClassName();hwnd是需要传入的句柄/classname是需要传入的LPTSTR缓冲区,用于接收类名/256是int,指定classname的大小,单位字节.
	//获取成功将返回返回值为拷贝到指定缓冲区的字符个数,如果函数失败,返回值为0. 
	int wt = GetWindowText(hwnd,windowtext,256);
	//解释同GetClassName();
	if(cn==0)
	{
		if(wt==0)
		{
			printf("Error in EnumWindows_CALLBACK\n");
			return FALSE;	//理论上不会存在既没有类名又没有标题名的窗体 
		}
		else if(wt!=0)
		{
			printf("NULL ||| %18s ||| %d\n",windowtext,hwnd);
			return TRUE;	//这种情况至今没有见到过! 
		}
	} 
	else if(cn!=0)
	{
		if(wt==0)
		{
			if(Primary==true)return TRUE;//隐藏输出,以面向初级用户,而且不显示子窗体信息. 
			else if(Primary==false)
			{
				printf("------------------------------------------------------------\n");//父窗体与父窗体之间的分割线. 
				printf("%-18s ||| NULL ||| %d\n",classname,hwnd);
				int check=EnumChildWindows(hwnd,(WNDENUMPROC)enumchildwindows_callback,0);//在此处调用显示子窗体的EnumChildWindows.
				if(check == 0) printf("    ->NoneChildWindow\n");//如果没有子窗体我们要这样回显. 
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
				printf("------------------------------------------------------------\n");//父窗体与父窗体之间的分割线. 
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
	//先创建一个标题栏 
	printf("WINDOWS_EXPLORER by.ZhangJunshuo\n");
	if(Primary==true)printf("PRIMARY_MODE\n\n");
	else if(Primary==false)printf("ADVANCED_MODE\n\n");
	printf("CLASSNAME----WINDOWTEXT----(int)HWND\n\n");
	
	int check = EnumWindows((WNDENUMPROC)enumwindows_callback,0);
	//BOOL EnumChildWindows(WNDENUMPROC,LPARAM)
	//WNDENUMPROC 为回调函数的地址
	//LPARAM为你自已定义的参数,将会传递给回调函数.
	if(check == 0)printf("Error in EnumWindows\n");
	system("pause");
	return 0;
}

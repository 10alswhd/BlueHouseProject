#include <stdio.h>
#include <time.h>
#include "resource.h"
#define Msg(x) MessageBox(0, x, 0, 0);
#define CT(x, y) CreateThread(0, 0, (LPTHREAD_START_ROUTINE)x, (LPVOID)y, 0, 0)

#pragma warning(disable:4244)
#pragma warning(disable:4800)
#pragma warning(disable:4996)

HWND G_hDlg, hLB;
HANDLE hProcess, hSnapshot;
char str[9], freestr[256];
int i, index, _index, LBCount, LBCount2, arry1[99999], arry2[99999];
clock_t start, end;

unsigned long ulBytesRead, ulCurrentChannel, ulCurrentID, ulOldProtect, ulU;

void ChangeText(int nIDDlgItem, char msg[]){
	HWND hWnd = GetDlgItem(G_hDlg, nIDDlgItem);
	SetWindowText(GetDlgItem(G_hDlg, nIDDlgItem), msg);
}

template<typename T_n>
void SearchMemory(int type){
	start = clock();
	char strKERNEL_ADR[256], strEND_ADR[256];
	int KERNEL_ADR, END_ADR, vsize;
	KERNEL_ADR = GetDlgItemText(G_hDlg, IDC_EDIT3, strKERNEL_ADR, sizeof(strKERNEL_ADR));
	END_ADR = GetDlgItemText(G_hDlg, IDC_EDIT4, strEND_ADR, sizeof(strEND_ADR));

	KERNEL_ADR = strtol(strKERNEL_ADR, NULL, 16);
	END_ADR = strtol(strEND_ADR, NULL, 16);

	T_n buf, target;
	char strTarget[256];

	GetDlgItemText(G_hDlg, IDC_EDIT1, strTarget, sizeof(strTarget));

	LBCount = SendMessage(hLB, LB_GETCOUNT, 0, 0);
	
	switch(type){
	case 0:
		target = atoi(strTarget);
		sprintf(str, "%d", target);
		vsize = sizeof(T_n);
		break;
	case 1:
		target = atol(strTarget);
		sprintf(str, "%ld", target);
		vsize = sizeof(T_n);
		break;
	case 2:
		target = (float)atof(strTarget);
		sprintf(str, "%f", target);
		vsize = sizeof(T_n);
		break;
	case 3:
		target = atof(strTarget);
		sprintf(str, "%lf", target);
		vsize = sizeof(T_n);
		break;
	}
	
	ChangeText(IDC_STATIC_NOW, "SearchStart");

	switch(LBCount){
	case 0:
		i=0;
		while(KERNEL_ADR < END_ADR){
			ReadProcessMemory(hProcess, (T_n*)KERNEL_ADR, &buf, vsize, NULL);
			if(buf==target){
				arry1[i] = KERNEL_ADR;
				i++;
				sprintf(str, "%p", KERNEL_ADR);
				SendMessage(hLB, LB_ADDSTRING, 0, (LPARAM)str);
			}
			KERNEL_ADR += vsize;
		}
		break;
	default:
		SendMessage(hLB, LB_RESETCONTENT, 0, 0);

		for(i=0; i<LBCount; i++){
			ReadProcessMemory(hProcess, (T_n*)arry1[i], &buf, vsize, NULL);
			if(buf==target){
				sprintf(str, "%p", arry1[i]);
				SendMessage(GetDlgItem(G_hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)str);
			}
			KERNEL_ADR += vsize;
		}
		break;
	}

	end = clock();
	if(SendMessage(hLB, LB_GETCOUNT, 0, 0)==0){
		ChangeText(IDOK, "????");
	}
	sprintf(freestr, "SearchEnd\nTotal:%d\n????????:%f?b",  SendMessage(hLB, LB_GETCOUNT, 0, 0), (double)(end - start) / CLOCKS_PER_SEC);
	ChangeText(IDC_STATIC_NOW, freestr);
}

template<typename T_n>
void WriteMemory(int type){
	int adr;
	T_n WriteValue, *p;
	char stradr[9], strWriteValue[256];
	
	GetDlgItemText(G_hDlg, IDC_EDIT5, stradr, sizeof(stradr));
	GetDlgItemText(G_hDlg, IDC_EDIT2, strWriteValue, sizeof(strWriteValue));
	adr = strtol(stradr, NULL, 16);

	switch(type){
	case 0:	
		WriteValue = atoi(strWriteValue);
		break;
	case 1:
		WriteValue = atol(strWriteValue);
		break;
	case 2:
		WriteValue = (float)atof(strWriteValue);
		break;
	case 3:
		WriteValue = atof(strWriteValue);
		break;
	}
	p=(T_n*)adr;
	*p = WriteValue;	
}

int CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam){
	G_hDlg = hDlg;
	switch(msg){
	case WM_SHOWWINDOW:
		char str2[256];
		GetModuleFileName(NULL, str, sizeof(str));
		sprintf(str2, "Target:%s", str);
		SetWindowText(G_hDlg, str2);
		// listbox
		hLB = GetDlgItem(hDlg, IDC_LIST1);
		// combobox1
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"int");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"long");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"float");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"double");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Arry");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		// combobox2
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"int");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"long");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"float");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"double");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"Arry");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);
		ChangeText(IDC_EDIT3, "0x00000000");
		ChangeText(IDC_EDIT4, "0x00F00000");
		return FALSE;

	case WM_NCHITTEST:
		SetWindowLong(hDlg, DWL_MSGRESULT, HTCAPTION);
		return TRUE;

	case WM_COMMAND:
		if (HIWORD(wParam) == LBN_DBLCLK){
			_index = SendMessage(hLB , LB_GETCURSEL , 0 , 0);
			char stradr[9];
			SendMessage(hLB, LB_GETTEXT, _index, (LPARAM)stradr);
			ChangeText(IDC_EDIT5, stradr);
		}
		switch(LOWORD(wParam)){
		case IDEND:
			ExitProcess(0);
			return FALSE;
		case IDC_BUTTONCANSEL:
			// ?L?????Z???{?^??
			ChangeText(IDOK, "????");
			LBCount = SendMessage(hLB, LB_GETCOUNT, 0, 0);
			for(i=0; i<LBCount;i++){
				SendMessage(hLB, LB_DELETESTRING, 0, 0);
			}
			return FALSE;

		case IDOK:
			index = SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);
			switch(index){
			case 0:
				CT(SearchMemory<int>, 0);
				break;
			case 1:
				CT(SearchMemory<long>, 1);
				break;
			case 2:
				CT(SearchMemory<float>, 2);
				break;
			case 3:
				CT(SearchMemory<double>, 3);
				break;
			case 4:
				// Arry

				break;
			}
			ChangeText(IDOK, "??");
			return FALSE;

		case IDC_BUTTON_WRITE:
			index = SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_GETCURSEL, 0, 0);
			switch(index){
			case 0:
				CT(WriteMemory<int>, 0);
				break;
			case 1:
				CT(WriteMemory<long>, 1);
				break;
			case 2:
				CT(WriteMemory<float>, 2);
				break;
			case 3:
				CT(WriteMemory<double>, 3);
				break;
			case 4:
				// Arry

				break;
// Microsoft Visual C++ generated resource script.
//
#include "resource.h"

#define APSTUDIO_READONLY_SYMBOLS
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 2 resource.
//
#include "afxres.h"

/////////////////////////////////////////////////////////////////////////////
#undef APSTUDIO_READONLY_SYMBOLS

/////////////////////////////////////////////////////////////////////////////
// 日本語 (日本) resources

#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_JPN)
LANGUAGE LANG_JAPANESE, SUBLANG_DEFAULT

#ifdef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// TEXTINCLUDE
//

1 TEXTINCLUDE 
BEGIN
    "resource.h\0"
END

2 TEXTINCLUDE 
BEGIN
    "#include ""afxres.h""\r\n"
    "\0"
END

3 TEXTINCLUDE 
BEGIN
    "\r\n"
    "\0"
END

#endif    // APSTUDIO_INVOKED


/////////////////////////////////////////////////////////////////////////////
//
// Dialog
//

IDD_DIALOG1 DIALOGEX 0, 0, 262, 313
STYLE DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Dialog"
FONT 8, "MS Shell Dlg", 400, 0, 0x1
BEGIN
    DEFPUSHBUTTON   "検索",IDOK,144,120,50,14
    PUSHBUTTON      "終了",IDEND,198,294,50,14
    LISTBOX         IDC_LIST1,7,7,89,299,LBS_NOINTEGRALHEIGHT | WS_VSCROLL | WS_TABSTOP
    EDITTEXT        IDC_EDIT1,174,96,72,14,ES_AUTOHSCROLL
    COMBOBOX        IDC_COMBO1,174,78,72,113,CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP
    LTEXT           "タイプ",IDC_STATIC,114,80,42,8
    LTEXT           "値",IDC_STATIC,114,98,48,8
    LTEXT           "",IDC_STATIC_NOW,108,6,132,49
    PUSHBUTTON      "書き換え",IDC_BUTTON_WRITE,198,228,50,14
    EDITTEXT        IDC_EDIT2,174,210,74,14,ES_AUTOHSCROLL
    LTEXT           "書き換える値",IDC_STATIC,114,208,50,14
    LTEXT           "開始",IDC_STATIC,114,264,17,8
    EDITTEXT        IDC_EDIT3,138,258,96,14,ES_AUTOHSCROLL
    LTEXT           "終了",IDC_STATIC,114,282,17,8
    EDITTEXT        IDC_EDIT4,138,276,96,14,ES_AUTOHSCROLL
    EDITTEXT        IDC_EDIT5,174,174,74,14,ES_AUTOHSCROLL
    LTEXT           "アドレス",IDC_STATIC,114,174,50,14
    COMBOBOX        IDC_COMBO2,174,192,72,113,CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP
    LTEXT           "タイプ",IDC_STATIC,114,190,50,14
    GROUPBOX        "書き換え",IDC_STATIC,102,150,156,96
    PUSHBUTTON      "キャンセル",IDC_BUTTONCANSEL,198,120,50,14
    GROUPBOX        "検索",IDC_STATIC,102,66,156,78
    LTEXT           "Created by KAGASU",IDC_STATIC,107,298,66,8
END


/////////////////////////////////////////////////////////////////////////////
//
// DESIGNINFO
//

#ifdef APSTUDIO_INVOKED
GUIDELINES DESIGNINFO
BEGIN
    IDD_DIALOG1, DIALOG
    BEGIN
        LEFTMARGIN, 7
        RIGHTMARGIN, 255
        TOPMARGIN, 7
        BOTTOMMARGIN, 306
    END
END
#endif    // APSTUDIO_INVOKED

#endif    // 日本語 (日本) resources
/////////////////////////////////////////////////////////////////////////////



#ifndef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 3 resource.
//


/////////////////////////////////////////////////////////////////////////////
#endif    // not APSTUDIO_INVOKED

			}
			return FALSE;
		}
		return FALSE;
	}
	return FALSE;
}
void _ShowWindow(HINSTANCE _hInst){
	DialogBox(_hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

BOOL WINAPI DllMain ( HMODULE hDll, DWORD dwReason, LPVOID lpReserved ){
	if(dwReason == DLL_PROCESS_ATTACH){
		hProcess = OpenProcess(PROCESS_VM_READ, FALSE, GetCurrentProcessId());
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)_ShowWindow, (LPVOID)hDll, 0, 0);
	}
	return TRUE;
}

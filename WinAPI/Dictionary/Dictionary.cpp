#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>
#include <windowsx.h>

HINSTANCE hIns;
Dict dict;
HWND hList;

INT_PTR CALLBACK AddEditProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND: {

		int id = LOWORD(wParam);
		int codeNotify = HIWORD(wParam);
		HWND handle = (HWND)lParam;

		switch (id) {
		case IDOK: {
			TCHAR word[100];
			GetWindowText(GetDlgItem(hWnd, IDC_WORD), word, 100);
			if (dict.Search(word))
				MessageBox(hWnd, TEXT("ALREADY EXIST"), TEXT("ALREADY EXIST"), MB_OK);
			else {
				TCHAR def[256];
				GetWindowText(GetDlgItem(hWnd, IDC_DEF), def, 256);
				DictItem newItem = DictItem(word, def);
				dict.AddAndSave( newItem );
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)(TCHAR *)newItem.GetWord());
				EndDialog(hWnd, 0);
			}
		} break;
		default:
			break;
		}
	} break;
	case WM_INITDIALOG: {
		
	} break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return false;
	}
	return true;
}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_EDIT_ADD:
			DialogBox(hIns, MAKEINTRESOURCE(IDD_ADD), hWnd, AddEditProc);
			break;
		case ID_EDIT_EDIT:
			DialogBox(hIns, MAKEINTRESOURCE(IDD_EDIT), hWnd, AddEditProc);
			break;
		}

		switch (HIWORD(wParam)) {
		case EN_UPDATE: {
			HWND hSearch = GetDlgItem(hWnd, IDC_SEARCH);
			HWND hList = GetDlgItem(hWnd, IDC_LIST);
			TCHAR search[233];
			GetWindowText(hSearch, search, 233);
			int oldId = SendMessage(hList, LB_GETCURSEL, 0, 0);
			int newId = SendMessage(hList, LB_SELECTSTRING, (WPARAM)(-1), (LPARAM)search);
			if (oldId != newId)
				SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(0, LBN_SELCHANGE), 0);
		} break;
		case LBN_SELCHANGE: {
			HWND hList = GetDlgItem(hWnd, IDC_LIST);
			INT id = SendMessage(hList, LB_GETCURSEL, 0, 0);
			TCHAR word[256];
			SendMessage(hList, LB_GETTEXT, (WPARAM)id, (LPARAM)word);
			SetWindowText(
				GetDlgItem(hWnd, IDC_DEFINITION), 
				dict.Search(word)->GetDef()
			);
		} break;
		}
	} break;
	case WM_INITDIALOG: {
		dict.SetFile("../Dictionary/db.txt");
		hList = GetDlgItem(hWnd, IDC_LIST);
		DictItem * item = dict.GetItem();
		for (int i = 0, n = dict.GetItemSize(); i < n; i++)
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)(TCHAR *)item[i].GetWord());
	} break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return false;
	}
	return true;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	hIns = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
}
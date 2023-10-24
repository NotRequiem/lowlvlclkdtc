#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

HHOOK hHook;
DWORD StartTime;
int wParamCounts[8] = {0};
int maxWParam = 0;
DWORD lastClickTime = 0;

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        MSLLHOOKSTRUCT* p = (MSLLHOOKSTRUCT*)lParam;

        // Check if the message is not injected (real mouse event)
        if (!(p->flags & LLMHF_INJECTED)) {
            if (wParam != 512 && wParam != 514 && wParam != 517 && wParam != 520 && wParam != 522 && wParam != 524 && wParam != 526 && wParam != 675) {
                wParamCounts[wParam]++;
            }
        }
    }

    DWORD CurrentTime = GetTickCount64();
    DWORD ElapsedTime = CurrentTime - StartTime;

    if (ElapsedTime <= 5000) {
        if (wParamCounts[wParam] > wParamCounts[maxWParam]) {
            maxWParam = wParam;
        }
    } else {
        if (nCode >= 0 && wParam == maxWParam) {
            if (lastClickTime != 0) {
                DWORD currentClickTime = GetTickCount64();
                printf("Most triggered mouse event: (%d). Delay between last click: %d ms\n", maxWParam, currentClickTime - lastClickTime);
            }
            lastClickTime = GetTickCount64();
        }
    }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void UninstallHook() {
    if (hHook != NULL) {
        if (!UnhookWindowsHookEx(hHook)) {
            printf("Error uninstalling mouse hook. Error code: %d\n", GetLastError());
        }
        hHook = NULL;
    }
}

bool InstallHook() {
    hHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseProc, GetModuleHandle(NULL), 0);
    if (!hHook) {
        printf("Error installing mouse hook. Error code: %d\n", GetLastError());
        UninstallHook();
        return false;
    }

    printf("Hook installed successfully.\n");
    return true;
}

int main() {
    StartTime = GetTickCount64();
    InstallHook();

    MSG msg;

    while (1) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        DWORD CurrentTime = GetTickCount64();
        DWORD ElapsedTime = CurrentTime - StartTime;
        if (ElapsedTime >= 10000) {
            break;
        }
    }

    UninstallHook();

    return 0;
}

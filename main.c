#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

HHOOK hMouseHook;
HHOOK hKeyboardHook;

struct KeyData {
    int keyDownCount;
    int keyUpCount;
    DWORD lastKeyDownTime;
    DWORD lastKeyUpTime;
    DWORD lastKeyUpToKeyDownDelay;
    DWORD lastKeyDownToKeyUpDelay;
};

ULONG64 downTime;
ULONG64 upTime;
ULONG64 lastUpTime;
ULONG64 timeInterval;

int autoclickCountLeft = 0;
int autoclickCountRight = 0;
int autoclickCountMiddle = 0;
int autoclickCountXButton = 0;

ULONG64 previousIntervalLeft = 0;
ULONG64 previousIntervalRight = 0;
ULONG64 previousIntervalMiddle = 0;
ULONG64 previousIntervalXButton = 0;

ULONG64 downTimeLeft = 0;
ULONG64 upTimeLeft = 0;
ULONG64 timeIntervalLeft = 0;
ULONG64 lastUpTimeLeft = 0;

ULONG64 downTimeRight = 0;
ULONG64 upTimeRight = 0;
ULONG64 timeIntervalRight = 0;
ULONG64 lastUpTimeRight = 0;

ULONG64 downTimeMiddle = 0;
ULONG64 upTimeMiddle = 0;
ULONG64 timeIntervalMiddle = 0;
ULONG64 lastUpTimeMiddle = 0;

ULONG64 downTimeXButton = 0;
ULONG64 upTimeXButton = 0;
ULONG64 timeIntervalXButton = 0;
ULONG64 lastUpTimeXButton = 0;

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    MSLLHOOKSTRUCT* p = (MSLLHOOKSTRUCT*)lParam;

    if (nCode == HC_ACTION && !(p->flags & (LLMHF_INJECTED | LLMHF_LOWER_IL_INJECTED))) {
        ULONG64 now = GetTickCount64();

        if (wParam == 513 || wParam == 515) { // Left mouse button is being clicked or double-clicked
            downTimeLeft = now;
        }

        if (wParam == 514) { // Left mouse button is being released
            upTimeLeft = now;
            if (upTimeLeft < downTimeLeft) {
                timeIntervalLeft = (ULLONG_MAX - downTimeLeft) + upTimeLeft + 1;
            } else {
                timeIntervalLeft = upTimeLeft - downTimeLeft;
            }

            if (timeIntervalLeft == 0) {
                printf("Autoclicker detected in the left mouse button. Delay Press-To-Release is 0ms.\n");
            } else {
                printf("Delay between last left press mouse event and current time: %llums\n", timeIntervalLeft);

                if (autoclickCountLeft == 0) {
                    previousIntervalLeft = timeIntervalLeft;
                } else if (timeIntervalLeft != previousIntervalLeft) {
                    autoclickCountLeft = 0;
                }

                if (autoclickCountLeft >= 10) {
                    printf("Left Mouse Button Autoclick detected (No Randomization): %llums delay\n", timeIntervalLeft);
                }

                autoclickCountLeft++;
            }

            lastUpTimeLeft = upTimeLeft;
        }

        if ((wParam == 513 || wParam == 515) && lastUpTimeLeft != 0) { // Left mouse button is being pressed again
            timeInterval = downTimeLeft - lastUpTimeLeft;
            if (timeInterval == 0) {
                printf("Autoclicker detected in the left mouse button. Delay Release-To-Press is 0ms.");
            } else {
                printf("Delay between last left release mouse event and current time: %llums\n", timeInterval);
            }
        }

        if (wParam == 516 || wParam == 518) { // Right mouse button is being clicked or double-clicked
            downTimeRight = now;
        }

        if (wParam == 517) { // Right mouse button is being released
            upTimeRight = now;
            if (upTimeRight < downTimeRight) {
                timeIntervalRight = (ULLONG_MAX - downTimeRight) + upTimeRight + 1;
            } else {
                timeIntervalRight = upTimeRight - downTimeRight;
            }

            if (timeIntervalRight == 0) {
                printf("Autoclicker detected in the right mouse button. Delay Press-To-Release is 0ms.\n");
            } else {
                printf("Delay between last right press mouse event and current time: %llums\n", timeIntervalRight);

                if (autoclickCountRight == 0) {
                    previousIntervalRight = timeIntervalRight;
                } else if (timeIntervalRight != previousIntervalRight) {
                    autoclickCountRight = 0;
                }

                if (autoclickCountRight >= 10) {
                    printf("Right Mouse Button Autoclick detected (No Randomization): %llums delay\n", timeIntervalRight);
                }

                autoclickCountRight++;
            }

            lastUpTimeRight = upTimeRight;
        }

        if (wParam == 516 || wParam == 518 && lastUpTimeRight != 0) { // Right mouse button is being pressed again
            timeInterval = downTimeRight - lastUpTimeRight;
            if (timeInterval == 0) {
            printf("Autoclicker detected in the right mouse button. Delay Release-To-Press is 0ms.\n");
            } else {
                printf("Delay between last right release mouse event and current time: %llums\n", timeInterval);
            }
        }

        if (wParam == 519 || wParam == 521) { // Middle mouse button is being clicked or double-clicked
            downTimeMiddle = now;
        }

        if (wParam == 520) { // Middle mouse button is being released
            upTimeMiddle = now;
            if (upTimeMiddle < downTimeMiddle) {
                timeIntervalMiddle = (ULLONG_MAX - downTimeMiddle) + upTimeMiddle + 1;
            } else {
                timeIntervalMiddle = upTimeMiddle - downTimeMiddle;
            }

            if (timeIntervalMiddle == 0) {
                printf("Autoclicker detected in the middle mouse button. Delay Press-To-Release is 0ms.\n");
            } else {
                printf("Delay between last middle press mouse event and current time: %llums\n", timeIntervalMiddle);

                if (autoclickCountMiddle == 0) {
                    previousIntervalMiddle = timeIntervalMiddle;
                } else if (timeIntervalMiddle != previousIntervalMiddle) {
                    autoclickCountMiddle = 0;
                }

                if (autoclickCountMiddle >= 10) {
                    printf("Middle Mouse Button Autoclick detected (No Randomization): %llums delay\n", timeIntervalMiddle);
                }

                autoclickCountMiddle++;
            }

            lastUpTimeMiddle = upTimeMiddle;
        }

        if (wParam == 519 && lastUpTimeMiddle != 0) { // Middle mouse button is being pressed again
            timeInterval = downTimeMiddle - lastUpTimeMiddle;
            if (timeInterval == 0) {
            printf("Autoclicker detected in the middle mouse button. Delay Release-To-Press is 0ms. \n");
            } else {
                printf("Delay between last middle release mouse event and current time: %llums\n", timeInterval);
            }
        }

        if (wParam == 523 || wParam == 525) { // Extended mouse button (XBUTTON1 or XBUTTON2) is being clicked or double-clicked
            downTimeXButton = now;
        }

        if (wParam == 524) { // Extended mouse button (XBUTTON1 or XBUTTON2) is being released
            upTimeXButton = now;
            if (upTimeXButton < downTimeXButton) {
                timeIntervalXButton = (ULLONG_MAX - downTimeXButton) + upTimeXButton + 1;
            } else {
                timeIntervalXButton = upTimeXButton - downTimeXButton;
            }

            if (timeIntervalXButton == 0) {
                printf("Autoclicker detected in the extended mouse button. Delay Press-To-Release is 0ms.\n");
            } else {
                printf("Delay between last XBUTTON press mouse event and current time: %llums\n", timeIntervalXButton);

                if (autoclickCountXButton == 0) {
                    previousIntervalXButton = timeIntervalXButton;
                } else if (timeIntervalXButton != previousIntervalXButton) {
                    autoclickCountXButton = 0;
                }

                if (autoclickCountXButton >= 10) {
                    printf("Extended Mouse Button Autoclick detected (No Randomization): %llums delay\n", timeIntervalXButton);
                }

                autoclickCountXButton++;
            }

            lastUpTimeXButton = upTimeXButton;
        }

        if ((wParam == 523 || wParam == 525) && lastUpTimeXButton != 0) { // Extended mouse button is being pressed again
            timeInterval = downTimeXButton - lastUpTimeXButton;
            if (timeInterval == 0) {
            printf("Autoclicker detected in the extended mouse button. Delay Release-To-Press is 0ms.\n");
            } else {
                printf("Delay between last XBUTTON release mouse event and current time: %llums\n", timeInterval);
            }
        }
    } else {
        printf("Autoclicker detected: Injected mouse event was triggered.\n");
    }

    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

struct KeyData keyDataMap[256] = {0};

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

    if (nCode == HC_ACTION && !(p->flags & (LLKHF_INJECTED | LLKHF_LOWER_IL_INJECTED))) {
        DWORD currentTime = GetTickCount();

        struct KeyData* keyData = &keyDataMap[p->vkCode];

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            if (keyData->keyDownCount > 0 && (currentTime - keyData->lastKeyDownTime == 0)) {
                printf("Autoclicker detected: Key Down with 0ms delay. VK Code = %d, Delay = %dms\n", p->vkCode, currentTime - keyData->lastKeyDownTime);
            }
            keyData->keyDownCount++;
            keyData->lastKeyDownTime = currentTime;
        } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            if (keyData->keyUpCount > 0 && (currentTime - keyData->lastKeyUpTime == 0)) {
                printf("Autoclicker detected: Key Up with 0ms delay. VK Code = %d, Delay = %dms\n", p->vkCode, currentTime - keyData->lastKeyUpTime);
            }
            keyData->keyUpCount++;
            keyData->lastKeyUpTime = currentTime;
        }
    } else {
        printf("Autoclicker detected: Injected keyboard event was triggered.\n");
    }

    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void UninstallMouseHook() {
    if (hMouseHook != NULL) {
        if (!UnhookWindowsHookEx(hMouseHook)) {
            printf("Error uninstalling mouse hook. Error code: %d\n", GetLastError());
        }
        hMouseHook = NULL;
    }
}

void UninstallKeyboardHook() {
    if (hKeyboardHook != NULL) {
        if (!UnhookWindowsHookEx(hKeyboardHook)) {
            printf("Error uninstalling keyboard hook. Error code: %d\n", GetLastError());
        }
        hKeyboardHook = NULL;
    }
}

bool InstallHooks() {
    hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)LowLevelMouseProc, GetModuleHandle(NULL), 0);
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, GetModuleHandle(NULL), 0);

    if (!hMouseHook || !hKeyboardHook) {
        printf("Error installing hooks. Error code: %d\n", GetLastError());
        UninstallMouseHook();
        UninstallKeyboardHook();
        return false;
    }

    printf("Hooks installed successfully.\n");
    return true;
}

int main() {
    InstallHooks();

    MSG msg;

    while (!GetAsyncKeyState(VK_DELETE)) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UninstallMouseHook();
    UninstallKeyboardHook();

    return 0;
}

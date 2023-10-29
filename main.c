#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

HHOOK hMouseHook;
HHOOK hKeyboardHook;

ULONG64 downTime;
ULONG64 upTime;
ULONG64 timeInterval;

int autoclickCount = 0;
ULONG64 previousInterval = 0;

ULONG64 downTimeLeft = 0;
ULONG64 upTimeLeft = 0;
ULONG64 timeIntervalLeft = 0;
ULONG64 previousIntervalLeft = 0;
int autoclickCountLeft = 0;

ULONG64 downTimeRight = 0;
ULONG64 upTimeRight = 0;
ULONG64 timeIntervalRight = 0;
ULONG64 previousIntervalRight = 0;
int autoclickCountRight = 0;

ULONG64 downTimeMiddle = 0;
ULONG64 upTimeMiddle = 0;
ULONG64 timeIntervalMiddle = 0;
ULONG64 previousIntervalMiddle = 0;
int autoclickCountMiddle = 0;

ULONG64 downTimeXButton = 0;
ULONG64 upTimeXButton = 0;
ULONG64 timeIntervalXButton = 0;
ULONG64 previousIntervalXButton = 0;
int autoclickCountXButton = 0;


LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    MSLLHOOKSTRUCT* p = (MSLLHOOKSTRUCT*)lParam;

    if (nCode == HC_ACTION && !(p->flags & (LLMHF_INJECTED | LLMHF_LOWER_IL_INJECTED))) {
        ULONG64 now = GetTickCount64();
        // Left mouse button is being clicked or double-clicked
        if (wParam == 513 || wParam == 515) {
            downTimeLeft = now;
        }

        // Left mouse button is being released
        if (wParam == 514) {
            upTimeLeft = now;
            if (upTimeLeft < downTimeLeft) {
                timeIntervalLeft = (ULLONG_MAX - downTimeLeft) + upTimeLeft + 1;
            } else {
                timeIntervalLeft = upTimeLeft - downTimeLeft;
            }

            if (timeIntervalLeft == 0) {
                printf("Autoclicker detected in the left mouse button: Delay is 0ms.\n");
            } else {
                printf("Delay between last left button click and current time: %llums\n", timeIntervalLeft);

                if (autoclickCountLeft == 0) {
                    previousIntervalLeft = timeIntervalLeft;
                } else if (timeIntervalLeft != previousIntervalLeft) {
                    autoclickCountLeft = 0;
                }

                if (autoclickCountLeft >= 10) {
                    printf("Left Mouse Button Autoclick detected (Randomization detected): %llums delay\n", timeIntervalLeft);
                }

                autoclickCountLeft++;
            }
        }

        // Right mouse button is being clicked or double-clicked
        if (wParam == 516 || wParam == 518) {
            downTimeRight = now;
        }

        // Right mouse button is being released
        if (wParam == 517) {
            upTimeRight = now;
            if (upTimeRight < downTimeRight) {
                timeIntervalRight = (ULLONG_MAX - downTimeRight) + upTimeRight + 1;
            } else {
                timeIntervalRight = upTimeRight - downTimeRight;
            }

            if (timeIntervalRight == 0) {
                printf("Autoclicker detected in the right mouse button: Delay is 0ms.\n");
            } else {
                printf("Delay between last right click and current time: %llums\n", timeIntervalRight);

                if (autoclickCountRight == 0) {
                    previousIntervalRight = timeIntervalRight;
                } else if (timeIntervalRight != previousIntervalRight) {
                    autoclickCountRight = 0;
                }

                if (autoclickCountRight >= 10) {
                    printf("Right Mouse Button Autoclick detected (Randomization detected): %llums delay\n", timeIntervalRight);
                }

                autoclickCountRight++;
            }
        }

        // Middle mouse button is being clicked or double-clicked
        if (wParam == 519 || wParam == 521) {
            downTimeMiddle = now;
        }

        // Middle mouse button is being released
        if (wParam == 520) {
            upTimeMiddle = now;
            if (upTimeMiddle < downTimeMiddle) {
                timeIntervalMiddle = (ULLONG_MAX - downTimeMiddle) + upTimeMiddle + 1;
            } else {
                timeIntervalMiddle = upTimeMiddle - downTimeMiddle;
            }

            if (timeIntervalMiddle == 0) {
                printf("Autoclicker detected in the middle mouse button: Delay is 0ms.\n");
            } else {
                printf("Delay between last middle button click and current time: %llums\n", timeIntervalMiddle);

                if (autoclickCountMiddle == 0) {
                    previousIntervalMiddle = timeIntervalMiddle;
                } else if (timeIntervalMiddle != previousIntervalMiddle) {
                    autoclickCountMiddle = 0;
                }

                if (autoclickCountMiddle >= 10) {
                    printf("Middle Mouse Button Autoclick detected (Randomization detected): %llums delay\n", timeIntervalMiddle);
                }

                autoclickCountMiddle++;
            }
        }

        // Extended mouse button (XBUTTON1 or XBUTTON2) is being clicked or double-clicked
        if (wParam == 523 || wParam == 525) {
            downTimeXButton = now;
        }

        // Extended mouse button (XBUTTON1 or XBUTTON2) is being released
        if (wParam == 524) {
            upTimeXButton = now;
            if (upTimeXButton < downTimeXButton) {
                timeIntervalXButton = (ULLONG_MAX - downTimeXButton) + upTimeXButton + 1;
            } else {
                timeIntervalXButton = upTimeXButton - downTimeXButton;
            }

            if (timeIntervalXButton == 0) {
                printf("Autoclicker detected in the extra side mouse button: Delay is 0ms.\n");
            } else {
                printf("Delay between last XBUTTON click and current time: %llums\n", timeIntervalXButton);

                if (autoclickCountXButton == 0) {
                    previousIntervalXButton = timeIntervalXButton;
                } else if (timeIntervalXButton != previousIntervalXButton) {
                    autoclickCountXButton = 0;
                }

                if (autoclickCountXButton >= 10) {
                    printf("Extended Mouse Button Autoclick detected (Randomization detected): %llums delay\n", timeIntervalXButton);
                }

                autoclickCountXButton++;
            }
        }
    } else {
        printf("Autoclicker detected: Injected mouse event was triggered\n");
    }

     return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

    if (nCode == HC_ACTION && !(p->flags & (LLKHF_INJECTED | LLKHF_LOWER_IL_INJECTED))) {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            printf("Key Down: VK Code = %d\n", p->vkCode);
        } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            printf("Key Up: VK Code = %d\n", p->vkCode);
        }
    } else {
        printf("Autoclicker detected: Injected keyboard event was triggered\n");
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

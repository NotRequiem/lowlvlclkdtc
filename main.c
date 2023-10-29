#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

HHOOK hHook;

ULONG64 downTime;
ULONG64 upTime;
ULONG64 timeInterval;

int autoclickCount = 0;
ULONG64 previousInterval = 0;

ULONG64 downTimeLeft = 0;
ULONG64 upTimeLeft = 0;
ULONG64 timeIntervalLeft = 0;
ULONG64 previousIntervalLeft = 0;

ULONG64 downTimeRight = 0;
ULONG64 upTimeRight = 0;
ULONG64 timeIntervalRight = 0;
ULONG64 previousIntervalRight = 0;

ULONG64 downTimeMiddle = 0;
ULONG64 upTimeMiddle = 0;
ULONG64 timeIntervalMiddle = 0;
ULONG64 previousIntervalMiddle = 0;

ULONG64 downTimeXButton = 0;
ULONG64 upTimeXButton = 0;
ULONG64 timeIntervalXButton = 0;
ULONG64 previousIntervalXButton = 0;


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
            timeIntervalLeft = downTimeLeft - upTimeLeft;

            if (timeIntervalLeft == 0) {
                printf("Autoclicker detected in the left mouse button: Delay is 0ms.\n");
            } else {
                printf("Delay between last left button click and current time: %llums\n", timeIntervalLeft);
                previousIntervalLeft = timeIntervalLeft;
            }

            if ((wParam == 513 || wParam == 514 || wParam == 515) && timeIntervalLeft == previousIntervalLeft) {
                autoclickCountLeft++;
                if (autoclickCountLeft == 3) {
                    printf("Left Mouse Button Autoclick detected (No randomization): %llums delay\n", timeIntervalLeft);
                }
            } else {
                autoclickCountLeft = 1;
            }
        }

        // Right mouse button is being clicked or double-clicked
        if (wParam == 516 || wParam == 518) {
            downTimeRight = now;
        }

        // Right mouse button is being released
        if (wParam == 517) {
            upTimeRight = now;
            timeIntervalRight = downTimeRight - upTimeRight;

            if (timeIntervalRight == 0) {
                printf("Autoclicker detected in the right mouse button: Delay is 0ms.\n");
            } else {
                printf("Delay between last right click and current time: %llums\n", timeIntervalRight);
                previousIntervalRight = timeIntervalRight;
            }

            if ((wParam == 516 || wParam == 517 || wParam == 518) && timeIntervalRight == previousIntervalRight) {
                autoclickCountRight++;
                if (autoclickCountRight == 3) {
                    printf("Autoclick detected in the right mouse button (No randomization): %llums delay\n", timeIntervalRight);
                }
            } else {
                autoclickCountRight = 1;
            }
        }

        // Middle mouse button is being clicked or double-clicked
        if (wParam == 519 || wParam == 521) {
            downTimeMiddle = now;
        }

        // Middle mouse button is being released
        if (wParam == 520) {
            upTimeMiddle = now;
            timeIntervalMiddle = downTimeMiddle - upTimeMiddle;

            if (timeIntervalMiddle == 0) {
                printf("Autoclicker detected in the middle mouse button: Delay is 0ms.\n");
            } else {
                printf("Delay between last middle button click and current time: %llums\n", timeIntervalMiddle);
                previousIntervalMiddle = timeIntervalMiddle;
            }

            if ((wParam == 520 || wParam == 519) && timeIntervalMiddle == previousIntervalMiddle) {
                autoclickCountMiddle++;
                if (autoclickCountMiddle == 3) {
                    printf("Autoclick detected in the middle button (No Randomization): %llums delay\n", timeIntervalMiddle);
                }
            } else {
                autoclickCountMiddle = 1;
            }
        }

        // Extended mouse button (XBUTTON1 or XBUTTON2) is being clicked or double-clicked
        if (wParam == 523 || wParam == 525) {
            downTimeXButton = now;
        }

        // Extended mouse button (XBUTTON1 or XBUTTON2) is being released
        if (wParam == 524) {
            upTimeXButton = now;
            timeIntervalXButton = downTimeXButton - upTimeXButton;

            if (timeIntervalXButton == 0) {
                printf("Autoclicker detected in the extra side mouse button: Delay is 0ms.\n");
            } else {
                printf("Delay between last XBUTTON click and current time: %llums\n", timeIntervalXButton);
                previousIntervalXButton = timeIntervalXButton;
            }

            if ((wParam == 524 || wParam == 523) && timeIntervalXButton == previousIntervalXButton) {
                autoclickCountXButton++;
                if (autoclickCountXButton == 3) {
                    printf("Autoclick detected in the extended mouse button (No randomization): %llums delay\n", timeIntervalXButton1);
                }
            } else {
                autoclickCountXButton = 1;
            }
        }
    } else {
        printf("Autoclicker detected: Injected mouse event was triggered\n");
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
	hHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)LowLevelMouseProc, GetModuleHandle(NULL), 0);
	if (!hHook) {
		printf("Error installing mouse hook. Error code: %d\n", GetLastError());
		UninstallHook();
		return false;
	}

	printf("Hook installed successfully.\n");
	return true;
}

int main() {
	InstallHook();

	MSG msg;

	while (!GetAsyncKeyState(VK_DELETE)) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UninstallHook();

	return 0;
}

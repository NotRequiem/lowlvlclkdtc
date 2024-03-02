# Autoclicker Detector
Windows application that monitors mouse and keyboard events to detect auto clickers.

# Hook Installation:
The program sets up two hooks, one for mouse events (WH_MOUSE_LL) and one for keyboard events (WH_KEYBOARD_LL), using the SetWindowsHookEx function. These hooks allow the program to intercept and monitor input events at a low level.

# Mouse Event Hook (LowLevelMouseProc function):

- The LowLevelMouseProc function is a callback that gets called when a mouse event occurs.
- It checks if the event is not an injected event (indicating possible autoclicker activity). Injected events can be used to simulate input.
The function monitors left, right, middle, and extended mouse button events.
- It calculates the time intervals between key down and key up events and checks if they are consistent or suspicious.
- If the time intervals are extremely short (e.g., 0 milliseconds), it prints a message indicating that an autoclicker was detected.
- If the time intervals are consistent over multiple events (e.g., 10 consecutive events with the same interval), it prints a message indicating that an autoclicker is active.
- The time intervals are printed in milliseconds, and they are calculated for both the delay between the last press mouse event and the delay between the last release mouse event.

# Keyboard Event Hook (LowLevelKeyboardProc function):

- The LowLevelKeyboardProc function is a callback that gets called when a keyboard event occurs.
- Like the mouse event hook, it checks if the event is not an injected event, otherwise it would flag "Autoclicker detected".
- It monitors key down and key up events and calculates the time intervals between them.
- If a key press event has a very short time interval (e.g., 0 milliseconds), it prints a message indicating a potential autoclicker activity.

# wParam values:
wParam is a parameter passed to the callback functions (LowLevelMouseProc and LowLevelKeyboardProc) in the Windows hook system.
It represents the message identifier or event code for the specific input event.

For keyboard events, wParam can take on values like WM_KEYDOWN, WM_KEYUP, WM_SYSKEYDOWN, or WM_SYSKEYUP to indicate whether a key is being pressed or released.
For mouse events, wParam can take on values like 513, 514, 515, 516, 517, 518, 519, 520, 523, or 525. These values represent different types of mouse events, including button presses, releases, and double-clicks:

513: Sent when the left mouse button is pressed.

514: Sent when the left mouse button is released.

515: Sent when the left mouse button is double-clicked.

516: Sent when the right mouse button is pressed.

517: Sent when the right mouse button is released.

518: Sent when the right mouse button is double-clicked.

519: Sent when the middle mouse button is pressed.

520: Sent when the middle mouse button is released.

521: Sent when the middle mouse button is double-clicked.

522: Sent when the mouse wheel is rotated.

523: Sent when an extended mouse button (XBUTTON1 or XBUTTON2) is pressed.

524: Sent when an extended mouse button (XBUTTON1 or XBUTTON2) is released.

525: Sent when an extended mouse button (XBUTTON1 or XBUTTON2) is double-clicked.

# VK (Virtual Key) Code:
VK codes represent virtual keycodes associated with specific keys on a keyboard.
They are used to identify and distinguish individual keys on the keyboard, including alphanumeric keys, function keys, and special keys (e.g., arrow keys, control keys, and modifier keys).
VK codes are used to uniquely identify keys in Windows messages and are often used when processing keyboard events.
In the code, VK codes are used to identify the specific key associated with the keyboard event. For example, the VK code is extracted from the KBDLLHOOKSTRUCT structure (p->vkCode) to determine which key triggered a keyboard event.


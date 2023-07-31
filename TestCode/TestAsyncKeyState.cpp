#include "TestAsyncKeyState.h"


#include <iostream>
#include <Windows.h>

int TestAsynckKeyState() {
	short prev_state = 0;
	short key_state;
	int key_code = 'A';

	while (true) {
		key_state = GetAsyncKeyState(key_code);

		// Check if the key state has changed
		if (key_state != prev_state) {
			if (prev_state == 0 && key_state != 0) {
				std::cout << "Key 'A' is pressed." << std::endl;
			}
			else if (prev_state != 0 && key_state != 0)
			{
				std::cout << "Key 'A' is hold." << std::endl;
			}
			else  if (prev_state != 0 && key_state == 0)
			{
				std::cout << "Key 'A' is released." << std::endl;
			}

		}

		prev_state = key_state;
		Sleep(1); // Add a small delay to avoid high CPU usage
	}

	return 0;
}
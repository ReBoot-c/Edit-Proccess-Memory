#include <stdio.h>
#include <windows.h>

int main()
{
	char game[20];
	
	printf("Enter game name:"); 
	scanf("%s", &game);
	HWND hwnd = FindWindowA(NULL, game);
	
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	if (pid == NULL)
	{
		printf("Game not found. Please enter PID game: ");
		scanf("%d", &pid);
	}
	
	printf("PID: %d\n", pid);
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	
	if (handle)
	{
		uintptr_t address = 0x0;
		int value_old, value_new;

		printf("Enter address 0x");
		scanf("%x", &address);
		
	    ReadProcessMemory(handle, (PBYTE*)address, &value_old, sizeof(value_old), 0);
		
		printf("Current value: %d\n", value_old);
		printf("Enter new value: ");
		scanf("%d", &value_new);
		
		WriteProcessMemory(handle, (LPVOID)address, &value_new, sizeof(value_new), 0);
		
		printf("Rewrite: %d -> %d\n", value_old, value_new);		
	}
	else
	{
		puts("Handle was NOT received\n");
	}
	system("pause");
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <locale>
#define NumberOfMonitors 3

int main()
{
    setlocale(LC_ALL, "Russian");
    HANDLE File = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 256, "Local\\MapCounter");
    PCHAR MapViewOfCounter = (PCHAR)MapViewOfFile(File, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    snprintf(MapViewOfCounter, sizeof(MapViewOfCounter), "0");

    HANDLE Mutex = CreateMutexA(0, FALSE, "Local\\Mutex"); 
    
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    for (int i = 0; i < NumberOfMonitors; i++)
    CreateProcessA(NULL,(LPSTR)"ProgramInstances",NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi);

    while (true)
    {
        Sleep(80);
        system("cls");
        std::cout << "Текущее колличество запущенных экзмепляров - " << MapViewOfCounter;
        if (strcmp(MapViewOfCounter, "0") == 0)
            break;
    }

    UnmapViewOfFile(MapViewOfCounter);
    CloseHandle(File);
    CloseHandle(Mutex);

    printf("\n");
    system("pause");
}


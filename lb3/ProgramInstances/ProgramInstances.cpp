#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <locale.h>
void main()
{
    setlocale(LC_ALL, "Russian");

    HANDLE File = OpenFileMappingA(FILE_MAP_ALL_ACCESS, TRUE, "Local\\MapCounter");
    PCHAR MapViewOfCounter = (PCHAR)MapViewOfFile(File, FILE_MAP_ALL_ACCESS, 0, 0, 0);

    HANDLE Mutex = OpenMutexA(NULL, FALSE, "Local\\Mutex");

    WaitForSingleObject(Mutex, INFINITE);
    INT inc = atoi(MapViewOfCounter);
    inc++;
    snprintf(MapViewOfCounter, sizeof(MapViewOfCounter), "%d", inc);
    std::cout << "Номер экзмепляра - " << MapViewOfCounter << std::endl;

    ReleaseMutex(Mutex);

    system("pause");

    WaitForSingleObject(Mutex, INFINITE);
    inc = atoi(MapViewOfCounter);
    inc--;
    snprintf(MapViewOfCounter, sizeof(MapViewOfCounter), "%d", inc);
  
    ReleaseMutex(Mutex);
    CloseHandle(File);
}
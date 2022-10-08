#include <Windows.h>
#include <iostream>

//offsets
DWORD gameModule;
DWORD localPlayer;
DWORD localPlayerAddy = 0xDC14CC;
DWORD fovOffset = 0x31F4;
DWORD observerModeOffset = 0x3388;

//new fov
int NewFov = 120;

//old fov
int OldFov = 80;

void increaseFov()
{
    *(int*)(localPlayer + fovOffset) = NewFov;

}

void decreaseFov()
{
    *(int*)(localPlayer + fovOffset) = OldFov;

}

void thirdPerson()
{

    *(int*)(localPlayer + observerModeOffset) = 1;

}

void noLongerThirdPerson()
{

    *(int*)(localPlayer + observerModeOffset) = 0;

}

int mainThread()
{
    SetConsoleTitleA("CS:GO - Simple Internal Trainer");
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    std::cout << "[F1] Thirdperson" << std::endl;
    std::cout << "[F2] Toggle FOV" << std::endl;
    gameModule = (DWORD)GetModuleHandle("client.dll");//gamemodule

    while (true)
    {


        localPlayer = *(DWORD*)(gameModule + localPlayerAddy);//Creates your localplayer

        if (localPlayer == NULL)//checks if your localplayer is existant
        {

            while (localPlayer == NULL)
            {
                localPlayer = *(DWORD*)(gameModule + localPlayerAddy);
            }

        }

        //thirdperson
        if (localPlayer != NULL)
        {
            if (GetKeyState(VK_F1) & 1)
            {
                thirdPerson();
            }
            else
            {
                noLongerThirdPerson();
            }

            //fov changer
            if (GetKeyState(VK_F2) & 1)
            {
                increaseFov();
            }
            else
            {
                decreaseFov();
            }
        }

        Sleep(1);
    }
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mainThread, NULL, NULL, NULL);

    }

    return TRUE;
}
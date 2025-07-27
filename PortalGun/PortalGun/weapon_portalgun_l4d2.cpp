#include <stdio.h>
//#include <Windows.h>
//#define GAME_DLL
#include "cbase.h"
#include "weapon_portalgun_shared.h"

// 服务端类
class CWeaponPortalgunL4D2 : public CBaseCombatWeapon
{
public:
    DECLARE_CLASS(CWeaponPortalgunL4D2, CBaseCombatWeapon);
    DECLARE_DATADESC();
    DECLARE_SERVERCLASS();

    CWeaponPortalgunL4D2();

    virtual void Precache() override;
    virtual void PrimaryAttack() override;
    virtual void SecondaryAttack() override;
    virtual void ItemPostFrame() override;

    // 网络同步字段
    CNetworkVar(int, m_iPortalLinkageID);
    CNetworkVar(bool, m_bCanFirePortal1);
    CNetworkVar(bool, m_bCanFirePortal2);

private:
    void FirePortal(int iPortal);
};

//BOOL APIENTRY DllMain( HMODULE hModule,
//                       DWORD  ul_reason_for_call,
//                       LPVOID lpReserved
//                     )
//{
//    switch (ul_reason_for_call)
//    {
//    case DLL_PROCESS_ATTACH:
//    case DLL_THREAD_ATTACH:
//    case DLL_THREAD_DETACH:
//    case DLL_PROCESS_DETACH:
//        break;
//    }
//    return TRUE;
//}
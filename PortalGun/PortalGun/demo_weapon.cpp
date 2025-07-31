#include "demo_weapon.h"
//#include "in_buttons.h"
#include "game/server/iplayerinfo.h"

//extern IPlayerInfoManager* playerinfomanager;

CWeaponPortalgunL4D2::CWeaponPortalgunL4D2()
{
    m_iPortalLinkageID = 0;
    m_bCanFirePortal1 = m_bCanFirePortal2 = true;
}

void CWeaponPortalgunL4D2::Precache()
{
    BaseClass::Precache();
    PrecacheModel("models/weapons/v_portalgun.mdl");
    PrecacheModel("models/weapons/w_portalgun.mdl");
    // Portal 粒子
    PrecacheParticleSystem("portal_1_charge");
    PrecacheParticleSystem("portal_2_charge");
}

void CWeaponPortalgunL4D2::PrimaryAttack()
{
    if (!m_bCanFirePortal1)
        return;

    FirePortal(1);
    m_bCanFirePortal1 = false; // 简单 cooldown
}

void CWeaponPortalgunL4D2::SecondaryAttack()
{
    if (!m_bCanFirePortal2)
        return;

    FirePortal(2);
    m_bCanFirePortal2 = false;
}

void CWeaponPortalgunL4D2::ItemPostFrame()
{
    BaseClass::ItemPostFrame();

    // 允许再次开火
    //if (!(m_nButtons & IN_ATTACK))
    //    m_bCanFirePortal1 = true;
    //if (!(m_nButtons & IN_ATTACK2))
    //    m_bCanFirePortal2 = true;
}

void CWeaponPortalgunL4D2::FirePortal(int iPortal)
{
    CBasePlayer* pOwner = ToBasePlayer(GetOwner());
    if (!pOwner) return;

    Vector vecSrc = pOwner->Weapon_ShootPosition();
    Vector vecAim;
    AngleVectors(pOwner->EyeAngles(), &vecAim);

    trace_t tr;
    UTIL_TraceLine(vecSrc, vecSrc + vecAim * MAX_TRACE_LENGTH,
        MASK_SHOT, pOwner, COLLISION_GROUP_NONE, &tr);

    if (tr.fraction < 1.0f)
    {
        // 调用 Portal SDK 里现成的函数创建传送门实体
        //CreatePortal(tr.endpos, tr.plane.normal, iPortal, m_iPortalLinkageID, pOwner);
    }

    WeaponSound(SINGLE);
    SendWeaponAnim(ACT_VM_PRIMARYATTACK);
    pOwner->DoMuzzleFlash();
}
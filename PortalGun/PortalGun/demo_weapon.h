#pragma once
#include "cbase.h"
#include "networkvar.h"

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

    // ÍøÂçÍ¬²½×Ö¶Î
    CNetworkVar(int, m_iPortalLinkageID);
    CNetworkVar(bool, m_bCanFirePortal1);
    CNetworkVar(bool, m_bCanFirePortal2);

private:
    void FirePortal(int iPortal);
};

BEGIN_DATADESC(CWeaponPortalgunL4D2)
DEFINE_FIELD(m_iPortalLinkageID, FIELD_INTEGER),
DEFINE_FIELD(m_bCanFirePortal1, FIELD_BOOLEAN),
DEFINE_FIELD(m_bCanFirePortal2, FIELD_BOOLEAN),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CWeaponPortalgunL4D2, DT_WeaponPortalgunL4D2)
SendPropInt(SENDINFO(m_iPortalLinkageID), 8, SPROP_UNSIGNED),
SendPropBool(SENDINFO(m_bCanFirePortal1)),
SendPropBool(SENDINFO(m_bCanFirePortal2)),
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_portalgun_l4d2, CWeaponPortalgunL4D2);
PRECACHE_WEAPON_REGISTER(weapon_portalgun_l4d2);
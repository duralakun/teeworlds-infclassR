/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/config.h>
#include <engine/shared/config.h>
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include "turret.h"
#include "plasma.h"
#include "laser.h"

CTurret::CTurret(CGameWorld *pGameWorld, vec2 Pos, int Owner, vec2 Direction, float StartEnergy, int Type)
: CEntity(pGameWorld, CGameWorld::ENTTYPE_TURRET)
{
	m_Pos = Pos;
	m_Owner = Owner;
	m_Energy = StartEnergy;
	m_Dir = Direction;
	m_StartTick = Server()->Tick();
	m_Bounces = 0;
	m_Radius = 15.0f;
	m_EvalTick = Server()->Tick();
	m_OwnerChar = GameServer()->GetPlayerChar(m_Owner);
	m_LifeSpan = Server()->TickSpeed()*g_Config.m_InfTurretDuration;
	m_WarmUpCounter = Server()->TickSpeed()*g_Config.m_InfTurretWarmUpDuration;
	m_ReloadCounter = Server()->TickSpeed()*g_Config.m_InfTurretReloadDuration;
	m_Type = Type;

	m_IDs.set_size(9);
	for(int i = 0; i < m_IDs.size(); i++)
	{
		m_IDs[i] = Server()->SnapNewID();
	}
	
	GameWorld()->InsertEntity(this);
}

CTurret::~CTurret()
{
	for(int i = 0; i < m_IDs.size(); i++)
	{
		Server()->SnapFreeID(m_IDs[i]);
	}
}

void CTurret::Reset()
{
    GameServer()->m_World.DestroyEntity(this);
}

int CTurret::GetOwner() const
{
	return m_Owner;
}

void CTurret::Tick()
{

	//marked for destroy
	if(m_MarkedForDestroy) 
		return;
	if(!m_OwnerChar) {
		Reset();
		return;
	}
	if(m_LifeSpan < 0) 
		Reset();
	
	for(CCharacter *pChr = (CCharacter*) GameWorld()->FindFirst(CGameWorld::ENTTYPE_CHARACTER); pChr; pChr = (CCharacter *)pChr->TypeNext()) 
	{
		if(!pChr->IsInfected()) continue;
		if(pChr->GetClass() == PLAYERCLASS_UNDEAD && pChr->IsFrozen()) continue;
		if(pChr->GetClass() == PLAYERCLASS_VOODOO && pChr->m_VoodooAboutToDie) continue;
		
		float Len = distance(pChr->m_Pos, m_Pos);
		
		// selfdestruction
		if(Len < pChr->m_ProximityRadius + 4.0f )
		{
			pChr->TakeDamage(vec2(0.f, 0.f), g_Config.m_InfTurretSelfDestructDmg, m_Owner, WEAPON_RIFLE, TAKEDAMAGEMODE_NOINFECTION);
			GameServer()->CreateSound(m_Pos, SOUND_RIFLE_FIRE);
			char aBuf[64];
			str_format(aBuf, sizeof(aBuf), "You destroyed %s's turret!", Server()->ClientName(m_Owner));
			GameServer()->SendChatTarget(pChr->GetPlayer()->GetCID(), aBuf);
			GameServer()->SendChatTarget(m_Owner, "A zombie has destroyed your turret!");
			Reset();
		}
	}
	
	//reduce lifespan
	m_LifeSpan--;
	
	//reloading in progress
	if(m_ReloadCounter > 0)
	{
		m_ReloadCounter--;
		
		if(m_Radius > 15.0f) //shrink radius
		{
			m_Radius -= m_RadiusGrowthRate;
			if(m_Radius < 15.0f)
				m_Radius = 15.0f;
			
		}
		return; //some reload tick-cycles necessary
	} 

	//Reloading finished, warm up in progress
	if ( m_WarmUpCounter > 0 ) 
	{
			m_WarmUpCounter--;
			
			if(m_Radius < 45.0f)
			{
				m_Radius += m_RadiusGrowthRate;
				if(m_Radius > 45.0f)
					m_Radius = 45.0f;
			}
			
			return; //some warmup tick-cycles necessary
	}
	
	//warmup finished, ready to find target
	
	// Near character event
	for(CCharacter *pChr = (CCharacter*) GameWorld()->FindFirst(CGameWorld::ENTTYPE_CHARACTER); pChr; pChr = (CCharacter *)pChr->TypeNext())
	{
		if(!pChr->IsInfected()) continue;
		if(pChr->GetClass() == PLAYERCLASS_UNDEAD && pChr->IsFrozen()) continue;
		if(pChr->GetClass() == PLAYERCLASS_VOODOO && pChr->m_VoodooAboutToDie) continue;
		
		float Len = distance(pChr->m_Pos, m_Pos);
		
		// attack zombie
		if (Len < (float)g_Config.m_InfTurretRadarRange) //800
		{
			//pChr = GameServer()->m_World.ClosestCharacter(m_Pos, 200.0f, 0);		
			{
				vec2 Direction = normalize(pChr->m_Pos - m_Pos);
				
				switch(m_Type)
				{
					case INFAMMO_LASER:
						new CLaser(GameWorld(), m_Pos, Direction, GameServer()->Tuning()->m_LaserReach, m_Owner, g_Config.m_InfTurretDmgHealthLaser);
						break;
						
					case INFAMMO_PLASMA:
						new CPlasma(GameWorld(), m_Pos, m_Owner, pChr->GetPlayer()->GetCID() , Direction, 0, 1);
						break;
				}
				
				GameServer()->CreateSound(m_Pos, SOUND_RIFLE_FIRE);
				
				//Reload ammo
				m_ReloadCounter = Server()->TickSpeed()*g_Config.m_InfTurretReloadDuration;
				m_WarmUpCounter = Server()->TickSpeed()*g_Config.m_InfTurretWarmUpDuration;
			}
		}
	}
}

void CTurret::Snap(int SnappingClient)
{
	
	// Draw AntiPing  effect
	if (Server()->GetClientAntiPing(SnappingClient)) {	
		float time = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();
		float angle = fmodf(time*pi/2, 2.0f*pi);
		
		for(int i=0; i<m_IDs.size()-7; i++)
		{	
			float shiftedAngle = angle + 2.0*pi*static_cast<float>(i)/static_cast<float>(m_IDs.size()-7);
			
			CNetObj_Projectile *pObj = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_IDs[i], sizeof(CNetObj_Projectile)));
			
			if(!pObj)
				continue;
			
			pObj->m_X = (int)(m_Pos.x + m_Radius*cos(shiftedAngle));
			pObj->m_Y = (int)(m_Pos.y + m_Radius*sin(shiftedAngle));
			pObj->m_VelX = 0;
			pObj->m_VelY = 0;
			
			pObj->m_StartTick = Server()->Tick();
		}
		
		
		CNetObj_Laser *pObj = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_IDs[m_IDs.size()-7], sizeof(CNetObj_Laser)));
		
		if(!pObj)
			return;
		
		pObj->m_X = (int)m_Pos.x;
		pObj->m_Y = (int)m_Pos.y;
		pObj->m_FromX = (int)m_Pos.x;
		pObj->m_FromY = (int)m_Pos.y;
		pObj->m_StartTick = Server()->Tick();	
		
		return;
	}
	
	
	float time = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();
	float angle = fmodf(time*pi/2, 2.0f*pi);
	
	for(int i=0; i<m_IDs.size()-1; i++)
	{	
		float shiftedAngle = angle + 2.0*pi*static_cast<float>(i)/static_cast<float>(m_IDs.size()-1);
		
		CNetObj_Projectile *pObj = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_IDs[i], sizeof(CNetObj_Projectile)));
		
		if(!pObj)
			continue;
		
		pObj->m_X = (int)(m_Pos.x + m_Radius*cos(shiftedAngle));
		pObj->m_Y = (int)(m_Pos.y + m_Radius*sin(shiftedAngle));
		pObj->m_VelX = 0;
		pObj->m_VelY = 0;

		pObj->m_StartTick = Server()->Tick();
	}

	
	CNetObj_Laser *pObj = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_IDs[m_IDs.size()-1], sizeof(CNetObj_Laser)));
	
	if(!pObj)
		return;
	
	pObj->m_X = (int)m_Pos.x;
	pObj->m_Y = (int)m_Pos.y;
	pObj->m_FromX = (int)m_Pos.x;
	pObj->m_FromY = (int)m_Pos.y;
	pObj->m_StartTick = Server()->Tick();
}

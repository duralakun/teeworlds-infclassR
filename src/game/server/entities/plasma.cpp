/* (c) Shereef Marzouk. See "licence DDRace.txt" and the readme.txt in the root of the distribution for more information. */
#include <engine/server.h>
#include <engine/config.h>
#include <engine/shared/config.h>
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include "plasma.h"

CPlasma::CPlasma(CGameWorld *pGameWorld, vec2 Pos, int Owner, int TrackedPlayer,vec2 Direction, bool Freeze, bool Explosive)
				: CEntity(pGameWorld, CGameWorld::ENTTYPE_LASER)
{
	m_Owner = Owner;
	m_Pos = Pos;
	m_Freeze = Freeze;
	m_TrackedPlayer = TrackedPlayer;
	m_Dir = Direction;
	m_Explosive = Explosive;
	m_StartTick = Server()->Tick();
	m_LifeSpan = Server()->TickSpeed()*g_Config.m_InfTurretPlasmaLifeSpan;
	m_InitialAmount = 1.0f;
	GameWorld()->InsertEntity(this);
}

int CPlasma::GetOwner() const
{
	return m_Owner;
}

void CPlasma::Reset()
{
	GameServer()->m_World.DestroyEntity(this);
}

// vec2 CPlasma::GetPos(float Time)
// {
// 	//float Speed = GameServer()->Tuning()->m_PlasmaRifleSpeed;
// 	float Speed = GameServer()->Tuning()->m_GrenadeSpeed;
//	return CalcPos(m_Pos, m_Dir, 0.0f, Speed, Time);
// }

void CPlasma::Tick()
{
	
	//reduce lifespan
	if (m_LifeSpan < 0)
	{
		Reset();
		return;
	}
	m_LifeSpan--;
	
	//position and collision calculation

 	//float Pt = (Server()->Tick()-m_StartTick-1)/(float)Server()->TickSpeed();
 	//float Ct = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();
 	//vec2 PrevPos = GetPos(Pt);
 	//vec2 CurPos = GetPos(Ct);
 	//int Collide = GameServer()->Collision()->IntersectLine(PrevPos, CurPos, &CurPos, NULL);
	
	//tracking
	CCharacter *pTarget = GameServer()->GetPlayerChar(m_TrackedPlayer);
	if(pTarget)
	{
		float Dist = distance(m_Pos, pTarget->m_Pos);
		if(Dist < 24.0f)
		{
			//freeze or explode
			if (m_Freeze) 
			{
				pTarget->Freeze(3.0f, m_Owner, FREEZEREASON_FLASH);
			}
			

			if (m_Explosive) 
			{
				GameServer()->CreateExplosion(m_Pos, m_Owner, WEAPON_GRENADE, false, TAKEDAMAGEMODE_NOINFECTION);
			}
			Reset();
		}
		else
		{
			vec2 Dir = normalize(pTarget->m_Pos - m_Pos);
			m_Dir = Dir*clamp(Dist, 0.0f, 16.0f) * (1.0f - m_InitialAmount);
			m_Pos += m_Dir;
			
			m_InitialAmount *= 0.98f;
			
			//collision detection

			//if((Collide || GameLayerClipped(CurPos)))
			//if(GameLayerClipped(m_Pos))
			if(GameServer()->Collision()->CheckPoint(m_Pos.x, m_Pos.y)) // this only works as long as projectile is not moving to fast
			{
					//GameServer()->CreateSound(CurPos, m_SoundImpact);
					if (m_Explosive) 
					{
						GameServer()->CreateExplosion(m_Pos, m_Owner, WEAPON_GRENADE, false, TAKEDAMAGEMODE_NOINFECTION);
					}
					Reset();
					return;
			}
		}
	} 
	else //Target died before impact -> explode
	{
		GameServer()->CreateExplosion(m_Pos, m_Owner, WEAPON_GRENADE, false, TAKEDAMAGEMODE_NOINFECTION);
		Reset();
	}
	
}


void CPlasma::Snap(int SnappingClient)
{
	if (NetworkClipped(SnappingClient))
		return;
	

	CNetObj_Laser *pObj = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(
		NETOBJTYPE_LASER, m_ID, sizeof(CNetObj_Laser)));
	
	if(!pObj)
		return;
	
	pObj->m_X = (int)m_Pos.x;
	pObj->m_Y = (int)m_Pos.y;
	pObj->m_FromX = (int)m_Pos.x;
	pObj->m_FromY = (int)m_Pos.y;
	pObj->m_StartTick = m_StartTick;
}

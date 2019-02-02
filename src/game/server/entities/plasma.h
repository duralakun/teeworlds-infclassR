/* (c) Shereef Marzouk. See "licence DDRace.txt" and the readme.txt in the root of the distribution for more information. */
#ifndef GAME_SERVER_ENTITIES_PLASMA_H
#define GAME_SERVER_ENTITIES_PLASMA_H

#include <game/server/entity.h>

class CPlasma: public CEntity
{

public:
	CPlasma(CGameWorld *pGameWorld, vec2 Pos, int Owner,int TrackedPlayer, vec2 Direction, bool Freeze, bool Explosive);
	
	int GetOwner() const;
	
	virtual void Reset();
// 	virtual vec2 GetPos(float Time);
	virtual void Tick();
	virtual void Snap(int SnappingClient);
	
public:
	int m_Owner;
private:
	int m_StartTick;
	int m_LifeSpan;
	vec2 m_Dir;
	int m_Freeze;
	bool m_Explosive;
	int m_TrackedPlayer;
	float m_InitialAmount;
};

#endif // GAME_SERVER_ENTITIES_PLASMA_H

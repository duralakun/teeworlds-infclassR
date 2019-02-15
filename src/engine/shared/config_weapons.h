#ifndef ENGINE_SHARED_WEAPON_PARAMS_H
#define ENGINE_SHARED_WEAPON_PARAMS_H
#undef ENGINE_SHARED_WEAPON_PARAMS_H // this file will be included several times

MACRO_CONFIG_INT(InfShockwaveAffectHumans, inf_shock_wave_affect_humans, 1, 0, 1, CFGFLAG_SERVER, "Explosion shockwave affect humans")

//Mines and bombs
MACRO_CONFIG_INT(InfSoldierBombs, inf_soldier_bombs, 3, 1, 16, CFGFLAG_SERVER, "Number of bombs for the soldier")
MACRO_CONFIG_INT(InfMercBombs, inf_merc_bombs, 15, 1, 100, CFGFLAG_SERVER, "Number of poison grenades for the mercenary")
MACRO_CONFIG_INT(InfMercLove, inf_merc_love, 1, 0, 1, CFGFLAG_SERVER, "Enables love bombs for the mercenary (hammer)")
MACRO_CONFIG_INT(InfMineLimit, inf_mine_limit, 2, 0, 1024, CFGFLAG_SERVER, "Maximum number of mines per player")
MACRO_CONFIG_INT(InfMineRadius, inf_mine_radius, 46, 0, 1024, CFGFLAG_SERVER, "Radius of mines")
MACRO_CONFIG_INT(InfScatterGrenadeRadius, inf_scatter_grenade_radius, 4, 0, 30, CFGFLAG_SERVER, "Radius of scatter grenade explosion")
MACRO_CONFIG_INT(InfSoldierBombDmgRadius, inf_soldier_bomb_dmg_radius, 180, 0, 180, CFGFLAG_SERVER, "explosion radius of soldier bombs")
MACRO_CONFIG_INT(InfSoldierBombDmgFactor, inf_soldier_bomb_dmg_factor, 10, 0, 10, CFGFLAG_SERVER, "damage of a single explosion, 10 == grenade explosion")

MACRO_CONFIG_INT(InfScientistMineBaseDmg, inf_scientist_base_dmg, 5, 0, 1024, CFGFLAG_SERVER, "Base damage of scientist mines")


//Walls
MACRO_CONFIG_INT(InfBarrierLifeSpan, inf_barrier_lifespan, 30, 0, 100, CFGFLAG_SERVER, "Barrier lifespan")
MACRO_CONFIG_INT(InfBarrierTimeReduce, inf_barrier_timereduce, 150, 0, 10000, CFGFLAG_SERVER, "Time to remove from a barrier lifespan when an infected dies (centisec)")
MACRO_CONFIG_INT(InfLooperBarrierTimeReduce, inf_looper_barrier_timereduce, 350, 0, 10000, CFGFLAG_SERVER, "Time to remove from a barrier lifespan when an infected dies (centisec)")
MACRO_CONFIG_INT(InfBarrierDamage, inf_barrier_damage, 0, 0, 20, CFGFLAG_SERVER, "0 kills zombies, bigger zero deals damage")

//Rifles
MACRO_CONFIG_INT(InfShotgunBlowback, inf_shotgun_blowback, 2, 0, 15, CFGFLAG_SERVER, "shotgun blowback")
MACRO_CONFIG_INT(InfMedicShotgunBlowback, inf_medic_shotgun_blowback, 10, 0, 15, CFGFLAG_SERVER, "medic shotgun blowback")
MACRO_CONFIG_INT(InfBioLaserDamage, inf_bio_laser_damage, 10, 0, 20, CFGFLAG_SERVER, "Damage in hearts")
MACRO_CONFIG_INT(InfBioLaserEnergy, inf_bio_laser_energy, 400, 0, 1000, CFGFLAG_SERVER, "Energy of biologist laser")
MACRO_CONFIG_INT(InfSniperLaserBaseDmg, inf_sniper_laser_base_dmg, 10, 0, 20, CFGFLAG_SERVER, "Damage in hearts")
MACRO_CONFIG_INT(InfSniperLockedLaserDmg, inf_sniper_locked_laser_dmg, 30, 0, 40, CFGFLAG_SERVER, "Damage in hearts")
MACRO_CONFIG_INT(InfLooperLaserDmg, inf_looper_laser_dmg, 5, 0, 20, CFGFLAG_SERVER, "Damage in hearts")
MACRO_CONFIG_INT(InfMercGunAmmoRegenTime, inf_merc_gun_ammo_regen_time, 125, 20, 2000, CFGFLAG_SERVER, "Regen time in milli-seconds")
MACRO_CONFIG_INT(InfMercMaxGunAmmo, inf_merc_max_gun_ammo, 40, 5, 80, CFGFLAG_SERVER, "Maximal Gun-Jetpack ammunition")
MACRO_CONFIG_INT(InfShotgunFireDelay, inf_shotgun_fire_delay, 500, 100, 2000, CFGFLAG_SERVER, "Fire delay in milli-seconds")

//Poison and damage and heal
MACRO_CONFIG_INT(InfPoisonDamage, inf_poison_damage, 8, 0, 1024, CFGFLAG_SERVER, "Damage deals by the poison grenades")
MACRO_CONFIG_INT(InfSlimeDuration, inf_slime_duration, 10, 0, 10000, CFGFLAG_SERVER, "How long Slug-Slime will stay in game (in seconds)")
MACRO_CONFIG_INT(InfSlimePoisonDuration, inf_slime_poison_duration, 5, 0, 10000, CFGFLAG_SERVER, "How long Slug-Slime will deal damage to humans (in seconds), BUG: when set to 1 second slime will deal damage very fast")
MACRO_CONFIG_INT(InfSlimeHealRate, inf_slime_heal_rate, 2, 0, 10000, CFGFLAG_SERVER, "Slug-Slime heals infected for X hearts every second")
MACRO_CONFIG_INT(InfMedicGrenadeRadius, inf_medic_grenade_radius, 4, 0, 30, CFGFLAG_SERVER, "Radius of medic heal grenade")

//Selfharm
MACRO_CONFIG_INT(InfScientistTpSelfharm, inf_scientist_tp_selfharm, 0, 0, 10000, CFGFLAG_SERVER, "Self damage on each teleportation")

//Hook related
MACRO_CONFIG_INT(InfBatDamage, inf_bat_damage, 3, 0, 10000, CFGFLAG_SERVER, "Damage taken by bat")
MACRO_CONFIG_INT(InfBatHookTime, inf_bat_hook_time, 5, 1, 10000, CFGFLAG_SERVER, "For how long bat will be able to hook humans (in seconds)")
MACRO_CONFIG_INT(InfSpiderHookTime, inf_spider_hook_time, 3, 1, 10000, CFGFLAG_SERVER, "For how long spiders will be able to hook humans (in seconds)")
MACRO_CONFIG_INT(InfSmokerHookDamage, inf_smoker_hook_damage, 3, 1, 10000, CFGFLAG_SERVER, "Damage taken by smoker (hook)")
MACRO_CONFIG_INT(InfSpiderCatchHumans, inf_spider_catch_humans, 1, 0, 1, CFGFLAG_SERVER, "Always catch humans with hook")

//Looper class config
MACRO_CONFIG_INT(InfSlowMotionWallDuration, inf_slow_motion_wall_duration, 30, 0, 1024, CFGFLAG_SERVER, "How long looper wall slow motion effect will slow down zombies (in centiSec)")
MACRO_CONFIG_INT(InfSlowMotionGunDuration, inf_slow_motion_gun_duration, 6, 0, 1024, CFGFLAG_SERVER, "How long looper gun slow motion effect will slow down zombies (in centiSec)")
MACRO_CONFIG_INT(InfLooperBarrierLifeSpan, inf_looper_barrier_life_span, 59, 0, 1024, CFGFLAG_SERVER, "How long looper barrier will last (in seconds)")
MACRO_CONFIG_INT(InfSlowMotionPercent, inf_slow_motion_percent, 65, 0, 90, CFGFLAG_SERVER, "Factor that manipulates the slowmotion intensity")
MACRO_CONFIG_INT(InfSlowMotionHookSpeed, inf_slow_motion_hook_speed, 30, 0, 100, CFGFLAG_SERVER, "Factor that manipulates the slowmotion hook speed")
MACRO_CONFIG_INT(InfSlowMotionHookAccel, inf_slow_motion_hook_accel, 15, 0, 100, CFGFLAG_SERVER, "Factor that manipulates the slowmotion hook acceleration")
MACRO_CONFIG_INT(InfSlowMotionMaxSpeed, inf_slow_motion_max_speed, 50, 0, 500, CFGFLAG_SERVER, "Create a speed limit while in slowmotion, make it 0 to disable it")
MACRO_CONFIG_INT(InfSlowMotionGravity, inf_slow_motion_gravity, 5, -100, 100, CFGFLAG_SERVER, "Modify gravity while in slowmotion")

//SuperWeapons
MACRO_CONFIG_INT(InfWhiteHoleMinimalKills, inf_white_hole_minimal_kills, 6, 0, 30, CFGFLAG_SERVER, "Minimal number of kills before white hole become available")
MACRO_CONFIG_INT(InfWhiteHoleProbability, inf_white_hole_probability, 20, 0, 100, CFGFLAG_SERVER, "Probability of super weapon being available after MinimalKill requirement")
MACRO_CONFIG_INT(InfWhiteHoleLifeSpan, inf_white_hole_life_span, 20, 0, 100, CFGFLAG_SERVER, "White hole life span")
MACRO_CONFIG_INT(InfWhiteHoleRadius, inf_white_hole_radius, 430, 0, 500, CFGFLAG_SERVER, "Radius of white holes")
MACRO_CONFIG_INT(InfWhiteHoleAffectsHumans, inf_white_hole_affects_humans, 1, 0, 1, CFGFLAG_SERVER, "Makes white holes suck in humans")
MACRO_CONFIG_INT(InfWhiteHoleNumParticles, inf_white_hole_num_particles, 100, 20, 500, CFGFLAG_SERVER, "Number of particles that will be used for a white hole animation")
MACRO_CONFIG_INT(InfWhiteHolePullStrength, inf_white_hole_pull_strength, 40, 0, 1000, CFGFLAG_SERVER, "How strong a white hole sucks players in")

MACRO_CONFIG_INT(InfStunGrenadeMinimalKills, inf_stun_grenade_minimal_kills, 2, 0, 30, CFGFLAG_SERVER, "Minimal number of kills before grenade stun ammunition can be found")
MACRO_CONFIG_INT(InfStunGrenadeProbability, inf_stun_grenade_probability, 30, 0, 100, CFGFLAG_SERVER, "Probability of super weapon being available after MinimalKill requirement")
MACRO_CONFIG_INT(InfWhiteHoleSpawnExpRadius, inf_white_hole_spawn_exp_radius, 5, 0, 30, CFGFLAG_SERVER, "Radius of white hole explosion on spawn")


//Turret
MACRO_CONFIG_INT(InfTurretEnable, inf_turret_enable, 1, 0, 1, CFGFLAG_SERVER, "If turrets are available")
MACRO_CONFIG_INT(InfTurretGive, inf_turret_give, 1, 0, 1000, CFGFLAG_SERVER, "Gives hero extra turrets")
MACRO_CONFIG_INT(InfTurretDuration, inf_turret_duration, 30, 0, 100, CFGFLAG_SERVER, "turret life span")
MACRO_CONFIG_INT(InfTurretSelfDestructDmg, inf_turret_self_destruct_dmg, 15, 0, 20, CFGFLAG_SERVER, "damage taken by zombie if turret is destroyed")
MACRO_CONFIG_INT(InfTurretRadarRange, inf_turret_radar_range, 800, 0, 1000, CFGFLAG_SERVER, "turret radar range")
MACRO_CONFIG_INT(InfTurretEnableLaser, inf_turret_enable_laser, 0, 0, 1, CFGFLAG_SERVER, "enable turret laser ammunition")
MACRO_CONFIG_INT(InfTurretEnablePlasma, inf_turret_enable_plasma, 1, 0, 1, CFGFLAG_SERVER, "enable turret plasma ammunition")
MACRO_CONFIG_INT(InfTurretPlasmaReloadDuration, inf_turret_plasma_reload_duration, 3, 0, 10, CFGFLAG_SERVER, "plasma ammo reload duration")
MACRO_CONFIG_INT(InfTurretLaserReloadDuration, inf_turret_laser_reload_duration, 1, 0, 10, CFGFLAG_SERVER, "laser ammo reload duration")
MACRO_CONFIG_INT(InfTurretPlasmaLifeSpan, inf_turret_plasma_life_span, 3, 0, 10, CFGFLAG_SERVER, "plasma life span")
MACRO_CONFIG_INT(InfTurretWarmUpDuration, inf_turret_warm_up_duration, 1, 0, 10, CFGFLAG_SERVER, "turret warm up duration")
MACRO_CONFIG_INT(InfTurretDmgFactor, inf_turret_dmg_factor, 9, 0, 10, CFGFLAG_SERVER, "how much damage a plasma turret does, 10 == grenade explosion")
MACRO_CONFIG_INT(InfTurretDmgHealthLaser, inf_turret_dmg_health_laser, 3, 0, 10, CFGFLAG_SERVER, "how much damage in life points a laser turret does")


#endif

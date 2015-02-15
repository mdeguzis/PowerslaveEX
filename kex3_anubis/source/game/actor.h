//
// Copyright(C) 2014-2015 Samuel Villarreal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//

#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "gameObject.h"
#include "sdNodes.h"
#include "world.h"
#include "spriteAnim.h"

typedef enum
{
    AT_INVALID      = -1,
    AT_PLAYER       = 0,
    AT_WATERSPLASH  = 124,
    NUMACTORTYPES
} actorType_t;

typedef enum
{
    AF_FLOORFRICTION    = BIT(0),
    AF_CEILINGFRICTION  = BIT(1),
    AF_SOLID            = BIT(2),
    AF_NOADVANCEFRAMES  = BIT(3),
    AF_RANDOMIZATION    = BIT(4),
    AF_FLASH            = BIT(5),
    AF_SHOOTABLE        = BIT(6),
    AF_FULLBRIGHT       = BIT(7),
    AF_MOVEABLE         = BIT(8),
    AF_TOUCHABLE        = BIT(9),
    AF_BOUNCY           = BIT(10),
    AF_INWATER          = BIT(11)
} actorFlags_t;

//-----------------------------------------------------------------------------
//
// kexActor
//
//-----------------------------------------------------------------------------

BEGIN_EXTENDED_KEX_CLASS(kexActor, kexGameObject);
public:
    kexActor(void);
    ~kexActor(void);

    virtual void                    Tick(void);
    virtual void                    OnRemove(void);
    virtual void                    OnTouch(kexActor *instigator);

    void                            Spawn(void);
    bool                            FindSector(const kexVec3 &pos);
    void                            LinkArea(void);
    void                            UnlinkArea(void);
    void                            ChangeAnim(spriteAnim_t *changeAnim);
    void                            ChangeAnim(const char *animName);
    void                            LinkSector(void);
    void                            UnlinkSector(void);
    void                            InflictDamage(kexActor *inflictor, const int amount);

    kexVec3                         &Velocity(void) { return velocity; }
    kexVec3                         &Movement(void) { return movement; }
    mapSector_t                     *Sector(void) { return sector; }
    const int                       SectorIndex(void);
    void                            SetSector(mapSector_t *s);
    mapActor_t                      *MapActor(void) { return mapActor; }
    kexLinklist<kexActor>           &SectorLink(void) { return sectorLink; }
    kexBBox                         &Bounds(void) { return bounds; }
    int                             &Type(void) { return type; }
    int16_t                         &Health(void) { return health; }
    void                            SetMapActor(mapActor_t *ma) { mapActor = ma; }
    float                           &Radius(void) { return radius; }
    float                           &Height(void) { return height; }
    float                           &StepHeight(void) { return stepHeight; }
    float                           &Scale(void) { return scale; }
    unsigned int                    &Flags(void) { return flags; }
    float                           &FloorHeight(void) { return floorHeight; }
    float                           &CeilingHeight(void) { return ceilingHeight; }
    spriteAnim_t                    *Anim(void) { return anim; }
    spriteFrame_t                   *Frame(void) { return &anim->frames[frameID]; }
    const int                       FrameID(void) const { return frameID; }
    float                           &Ticks(void) { return ticks; }
    void                            SetDefinition(kexDict *dict) { definition = dict; }
    float                           &AnimSpeed(void) { return animSpeed; }

    kexSDNodeRef<kexActor>          &AreaLink(void) { return areaLink; }

protected:
    void                            UpdateSprite(void);
    void                            UpdateMovement(void);

    kexDict                         *definition;
    kexSDNodeRef<kexActor>          areaLink;
    float                           radius;
    float                           height;
    float                           scale;
    float                           stepHeight;
    int16_t                         health;
    kexVec3                         velocity;
    kexVec3                         movement;
    kexLinklist<kexActor>           sectorLink;
    kexBBox                         bounds;
    mapSector_t                     *sector;
    mapActor_t                      *mapActor;
    spriteAnim_t                    *anim;
    spriteAnim_t                    *spawnAnim;
    spriteAnim_t                    *deathAnim;
    int16_t                         frameID;
    float                           ticks;
    float                           animSpeed;
    int                             flashTicks;
    int                             type;
    unsigned int                    flags;
    float                           floorHeight;
    float                           ceilingHeight;
END_KEX_CLASS();

#include "pickup.h"

#endif

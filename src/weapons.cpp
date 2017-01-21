//--------------------------------------------------------
//  Zelda Classic
//  by Jeremy Craner, 1999-2000
//
//  sprite.cc
//
//  Sprite classes:
//   - sprite:      base class for the guys and enemies in zelda.cc
//   - movingblock: the moving block class
//   - sprite_list: main container class for different groups of sprites
//   - item:        items class
//
//--------------------------------------------------------

#ifndef __GTHREAD_HIDE_WIN32API
#define __GTHREAD_HIDE_WIN32API 1
#endif                            //prevent indirectly including windows.h

#include "precompiled.h" //always first

#include <string.h>

#include "weapons.h"
#include "zelda.h"
#include "zsys.h"
#include "maps.h"
#include "tiles.h"
#include "pal.h"
#include "link.h"
#include "mem_debug.h"

extern LinkClass Link;
extern zinitdata zinit;
extern int directWpn;

/**************************************/
/***********  Weapon Class  ***********/
/**************************************/

byte boomframe[16] = {0,0,1,0,2,0,1,1,0,1,1,3,2,2,1,2};
byte bszboomflip[4] = {0,2,3,1};

//light up the screen if there is at least one "lit" weapon
//otherwise darken the screen
void checkLightSources()
{
    for(int i=0; i<Lwpns.Count(); i++)
    {
        if(((weapon *)Lwpns.spr(i))->isLit)
        {
            lighting(true);
            return;
        }
    }
    
    for(int i=0; i<Ewpns.Count(); i++)
    {
        if(((weapon *)Ewpns.spr(i))->isLit)
        {
            lighting(true);
            return;
        }
    }
    
    lighting(false);
}

void getdraggeditem(int j)
{
    item *it=(item*)items.spr(j);
    
    if(it==NULL)
        return;
        
    it->x = LinkX();
    it->y = LinkY();
    it->z = LinkZ();
    LinkCheckItems();
}

void weapon::seekLink()
{
    angular = true;
    angle = atan2(double(LinkY()-y),double(LinkX()-x));
    
    if(angle==-PI || angle==PI) dir=left;
    else if(angle==-PI/2) dir=up;
    else if(angle==PI/2)  dir=down;
    else if(angle==0)     dir=right;
    else if(angle<-PI/2)  dir=l_up;
    else if(angle<0)      dir=r_up;
    else if(angle>(PI/2))   dir=l_down;
    else                  dir=r_down;
    
    if(z>LinkZ()) z--;
    else if(z<LinkZ()) z++;
}

void weapon::seekEnemy(int j)
{
    angular = true;
    fix mindistance=(fix)1000000;
    fix tempdistance;
    
    if((j==-1)||(j>=GuyCount()))
    {
        j=-1;
        
        for(int i=0; i<GuyCount(); i++)
        {
            //        tempdistance=sqrt(pow(abs(x-GuyX(i)),2)+pow(abs(y-GuyY(i)),2));
            tempdistance=distance(x,y,GuyX(i),GuyY(i));
            
            if((tempdistance<mindistance)&&(GuyID(i)>=10) && !GuySuperman(i))
            {
                mindistance=tempdistance;
                j=i;
            }
        }
    }
    
    if(j==-1)
    {
        return;
    }
    
    angle = atan2(double(GuyY(j)-y),double(GuyX(j)-x));
    
    if(angle==-PI || angle==PI) dir=left;
    else if(angle==-PI/2) dir=up;
    else if(angle==PI/2)  dir=down;
    else if(angle==0)     dir=right;
    else if(angle<-PI/2)  dir=l_up;
    else if(angle<0)      dir=r_up;
    else if(angle>PI/2)   dir=l_down;
    else                  dir=r_down;
}

int weapon::seekEnemy2(int j)
{
    angular = true;
    fix mindistance=(fix)1000000;
    fix tempdistance;
    
    if((j==-1)||(j>=GuyCount()))
    {
        j=-1;
        
        for(int i=0; i<GuyCount(); i++)
        {
            //        tempdistance=sqrt(pow(abs(x-GuyX(i)),2)+pow(abs(y-GuyY(i)),2));
            tempdistance=distance(dummy_fix[0],dummy_fix[1],GuyX(i),GuyY(i));
            
            if((tempdistance<mindistance)&&(GuyID(i)>=10) && !GuySuperman(i))
            {
                mindistance=tempdistance;
                j=i;
            }
        }
    }
    
    if(j==-1)
    {
        return j;
    }
    
    //al_trace("Guy: %d, gx: %f, gy: %f, x: %f, y: %f\n", j, float(GuyX(j)), float(GuyY(j)), float(dummy_fix[0]), float(dummy_fix[1]));
    angle = atan2(double(GuyY(j)-dummy_fix[1]),double(GuyX(j)-dummy_fix[0]));
    
    if(angle==-PI || angle==PI) dir=left;
    else if(angle==-PI/2) dir=up;
    else if(angle==PI/2)  dir=down;
    else if(angle==0)     dir=right;
    else if(angle<-PI/2)  dir=l_up;
    else if(angle<0)      dir=r_up;
    else if(angle>PI/2)   dir=l_down;
    else                  dir=r_down;
    
    return j;
}

weapon::weapon(weapon const & other):
    sprite(other),
    power(other.power),
    type(other.type),
    dead(other.dead),
    clk2(other.clk2),
    misc2(other.misc2),
    ignorecombo(other.ignorecombo),
    isLit(other.isLit),
    parentid(other.parentid),
    parentitem(other.parentitem),
    dragging(other.dragging),
    step(other.step),
    bounce(other.bounce),
    ignoreLink(other.ignoreLink),
    flash(other.flash),
    wid(other.wid),
    aframe(other.aframe),
    csclk(other.csclk),
    o_tile(other.o_tile),
    o_cset(other.o_cset),
    o_speed(other.o_speed),
    o_type(other.o_type),
    frames(other.frames),
    o_flip(other.o_flip),
    temp1(other.temp1),
    behind(other.behind)

{
    for(int i=0; i<10; ++i)
    {
        dummy_int[i]=other.dummy_int[i];
        dummy_fix[i]=other.dummy_fix[i];
        dummy_float[i]=other.dummy_float[i];
        dummy_bool[i]=other.dummy_bool[i];
    }
    
    /*for (int i=0; i<8; ++i)
    {
      d[i]=other.d[i];
    }
    for (int i=0; i<2; ++i)
    {
      a[i]=other.a[i];
    }*/
}

// Let's dispose of some sound effects!
weapon::~weapon()
{
    // First, check for the existence of weapons that don't have parentitems
    // but make looping sounds anyway.
    if(parentitem<0 && get_bit(quest_rules, qr_MORESOUNDS))
    {
        //I am reasonably confident that I fixed these expressions. ~pkmnfrk
        if(id==ewBrang && Ewpns.idCount(ewBrang) > 0)
            return;
            
        if(id==wWind && Lwpns.idCount(wWind) > 0)
            return;
    }
    
    // Check each Lwpn to see if this weapon's sound is also allocated by it.
    if(parentitem>=0)
    {
        for(int i=0; i<Lwpns.Count(); i++)
        {
            weapon *w = ((weapon *)Lwpns.spr(i));
            
            if(w->getUID() == getUID())  // Itself!
            {
                continue;
            }
            
            int wparent = w->parentitem;
            
            if(wparent>=0 && (itemsbuf[wparent].family == itype_brang || itemsbuf[wparent].family == itype_nayruslove
                              || itemsbuf[wparent].family == itype_hookshot || itemsbuf[wparent].family == itype_cbyrna))
            {
                if(itemsbuf[wparent].usesound == itemsbuf[parentitem].usesound)
                    return;
            }
        }
    }
    
    switch(id)
    {
    case wWind:
        stop_sfx(WAV_ZN1WHIRLWIND);
        break;
        
    case ewBrang:
        //stop_sfx(WAV_BRANG); //causes a bug -L
        break;
        
    case wBrang:
    case wCByrna:
        if(parentitem>=0)
        {
            stop_sfx(itemsbuf[parentitem].usesound);
        }
        
        break;
        
    case wSSparkle:
    case wFSparkle:
        if(parentitem>=0 && itemsbuf[parentitem].family==itype_cbyrna)
        {
            stop_sfx(itemsbuf[parentitem].usesound);
        }
        
        break;
    }
}

weapon::weapon(fix X,fix Y,fix Z,int Id,int Type,int pow,int Dir, int Parentitem, int prntid, bool isDummy) : sprite(), parentid(prntid)
{
    x=X;
    y=Y;
    z=Z;
    id=Id;
    type=Type;
    power=pow;
    parentitem=Parentitem;
    dir=zc_max(Dir,0);
    clk=clk2=flip=misc=misc2=0;
    frames=flash=wid=aframe=csclk=0;
    ignorecombo=-1;
    step=0;
    dead=-1;
    bounce=ignoreLink=false;
    yofs=playing_field_offset - 2;
    dragging=-1;
    hxsz=15;
    hysz=15;
    hzsz=8;
    isLit = false;
    
    int defaultw, itemid = parentitem;
    
    //We might need to clear scriptrange. -Z
    scriptrange = -1; //we'll try -1 so that 0 does not interfere.
    //Pewrhaps check the weapon editor properties, and see if it has a range; only for weapons
    //that use misc1 for this. 
    //scriptrange = 
    
    if(id>wEnemyWeapons)
    {
        canfreeze=true;
        
        if(id!=ewBrang)
        {
            if(Type&2)
            {
                misc=(Type>>3)-1;
                type &= ~2;
            }
            else
                misc=-1;
        }
    }
    
    switch(id)
    {
    case wSword: // Link's sword
    {
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_sword);
        }
        
        if(itemid >-1)
            defaultw = itemsbuf[itemid].wpn;
        else
            defaultw = wSWORD;
            
        hxsz=hysz=15;
        LOADGFX(defaultw);
        break;
    }
    
    case wWand: // Link's wand, as well as the Cane itself
    {
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_wand);
        }
        
        if(itemid >-1)
            defaultw = itemsbuf[itemid].wpn;
        else
            defaultw = wWAND;
            
        hxsz=15;
        hysz=15; //hysz=24;
        LOADGFX(defaultw);
        break;
    }
    
    case wHammer:
    {
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_hammer);
        }
        
        if(itemid >-1)
            defaultw = itemsbuf[itemid].wpn;
        else
            defaultw = wHAMMER;
            
        hxsz=15;
        hysz=24;
        LOADGFX(defaultw);
        break;
    }
    
    case wCByrna: // The Cane's beam
    {
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_cbyrna);
        }
        
        if(itemid >-1)
            defaultw = itemsbuf[itemid].wpn3;
        else
            defaultw = wCBYRNA;
            
        LOADGFX(defaultw);
        int speed = parentitem>-1 ? zc_max(itemsbuf[parentitem].misc1,1) : 1;
        int qty = parentitem>-1 ? zc_max(itemsbuf[parentitem].misc3,1) : 1;
        clk = (int)((((2*type*PI)/qty)
                     // Appear on top of the cane's hook
                     + (dir==right? 3*PI/2 : dir==left? PI/2 : dir==down ? 0 : PI))*speed);
        type = 0;
        
        if(parentitem>-1)
        {
            cont_sfx(itemsbuf[parentitem].usesound);
        }
        
        break;
    }
    
    case wWhistle:
        xofs=1000;                                            // don't show
        x=y=hxofs=hyofs=0;
        hxsz=hysz=255;                                        // hit the whole screen
        break;
        
    case wWind:
    {
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_whistle);
        }
        
        if(itemid >-1)
            defaultw = itemsbuf[itemid].wpn;
        else
            defaultw = wWIND;
            
        LOADGFX(defaultw);
        
        if(get_bit(quest_rules,qr_MORESOUNDS))
            cont_sfx(WAV_ZN1WHIRLWIND);
            
        clk=-14;
        step=2;
        break;
    }
    
    case wBeam:
    case wRefBeam:
        step = 3;
        
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_sword);
        }
        
        if(itemid>-1 && id!=wRefBeam)
            defaultw = itemsbuf[itemid].wpn3;
        else
            defaultw = ewSWORD;
            
        LOADGFX(defaultw);
        flash = 1;
        cs = 6;
        
        switch(dir)
        {
        case down:
            flip=get_bit(quest_rules,qr_SWORDWANDFLIPFIX)?3:2;
            
        case up:
            hyofs=2;
            hysz=12;
            break;
            
        case left:
            flip=1;
            
        case right: /*tile=o_tile+((frames>1)?frames:1)*/
            update_weapon_frame(((frames>1)?frames:1),o_tile);
            hxofs=2;
            hxsz=12;
            yofs = playing_field_offset+(BSZ ? 3 : 1);
            break;
        }
        
        if(id==wRefBeam)
        {
            ignorecombo=(((int)y&0xF0)+((int)x>>4));
        }
        
        break;
        
    case wArrow:
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_arrow);
        }
        
        if(itemid >-1)
            defaultw = itemsbuf[itemid].wpn;
        else
            defaultw = wARROW;
            
        LOADGFX(defaultw);
        step=3;
        
        switch(dir)
        {
        case down:
            flip=2;
            
        case up:
            hyofs=2;
            hysz=12;
            break;
            
        case left:
            flip=1;
            
        case right: /*tile=o_tile+((frames>1)?frames:1)*/
            update_weapon_frame(((frames>1)?frames:1),o_tile);
            yofs=playing_field_offset + 1;
            hyofs=2;
            hysz=14;
            hxofs=2;
            hxsz=12;
            break;
        }
        
        if(itemid >-1) {
		
		misc = itemsbuf[itemid].misc1;
		
		/*
		if ( scriptrange <= 0 ) scriptrange =  itemsbuf[itemid].misc1;
		else if ( scriptrange > 0 ) {
			misc = scriptrange; 
		}
		*/
		
		/*
		if ( scriptrange > 0 ) {
			misc = scriptrange; 
		}
		else misc =  itemsbuf[itemid].misc1;
		*/
		
	}
            
        break;
        
    case wSSparkle:
        LOADGFX(type ? type : wSSPARKLE);
        step=0;
        break;
        
    case wFSparkle:
        LOADGFX(type ? type : wFSPARKLE);
        step=0;
        break;
        
    case wFire:
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_candle);
        }
        
        switch(type)
        {
        case 3: // Din's Fire. This uses magicitem rather than itemid
            if(magicitem >-1 && !isDummy)
                defaultw = itemsbuf[magicitem].wpn5;
            else defaultw = wFIRE;
            
            break;
            
        case 2: // Wand
            if(itemid>-1 && !isDummy)
                defaultw = itemsbuf[itemid].wpn2;
            else defaultw = wFIRE;
            if ( itemsbuf[parentitem].misc1 > 0 ) power = itemsbuf[parentitem].misc1; 
	    //The book sets the damage of the fire that the wand creates.
            break;
            
        case 0:
        case 1: // Candles
            if(itemid>-1 && !isDummy)
            {
                defaultw = itemsbuf[itemid].wpn3;
                break;
            }
            
        default:
            defaultw = wFIRE;
        }
        
        LOADGFX(defaultw);
        step = (type<2)?.5:0;
        hxofs = hyofs=1;
        hxsz = hysz = 14;
        
        if(BSZ)
            yofs+=2;
            
        break;
        
    case wLitBomb:
    case wBomb:
    {
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_bomb);
        }
        
        if(itemid >-1)
        {
            defaultw = itemsbuf[itemid].wpn;
            misc = (id==wBomb ? 1 : itemsbuf[itemid].misc1);
        }
        else
        {
            defaultw = wBOMB;
            misc = (id==wBomb ? 1 : 50);
        }
        
        LOADGFX(defaultw);
        hxofs=hyofs=4;
        hxsz=hysz=8;
        break;
    }
    
    case wLitSBomb:
    case wSBomb:
    {
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_sbomb);
        }
        
        if(parentitem>-1)
        {
            defaultw = itemsbuf[itemid].wpn;
            misc = (id==wSBomb ? 1 : itemsbuf[itemid].misc1);
        }
        else
        {
            defaultw = wSBOMB;
            misc = (id==wSBomb ? 1 : 50);
        }
        
        LOADGFX(defaultw);
        hxofs=hyofs=4;
        hxsz=hysz=8;
        break;
    }
    
    case wBait:
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_bait);
        }
        
        if ( QHeader.zelda_version < 0x250 ) {
		LOADGFX(itemsbuf[iBait].wpn);
		
	}
	else { 
		if(itemid >-1)
		    defaultw = itemsbuf[itemid].wpn;
		else
		    defaultw = wBAIT;
		    
		LOADGFX(defaultw);
	}
        break;
        
    case wMagic:
    {
        itemid = current_item_id(itype_book);
        bool book = true;
        
        if(itemid<0)
        {
            itemid = directWpn>-1 ? directWpn : current_item_id(itype_wand);
            book = false;
        }
        
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_wand);
            book = false;
        }
        
        if(itemid >-1)
            // Book Magic sprite is wpn, Wand Magic sprite is wpn3.
            defaultw = book ? itemsbuf[itemid].wpn : itemsbuf[itemid].wpn3;
        else
            defaultw = wMAGIC;
            
        LOADGFX(defaultw);
        step = (BSZ ? 3 : 2.5);
        
        switch(dir)
        {
        case down:
            flip=2;
            
        case up:
            hyofs=2;
            hysz=12;
            break;
            
        case left:
            flip=1;
            
        case right: /*tile=o_tile+((frames>1)?frames:1)*/
            update_weapon_frame(((frames>1)?frames:1),o_tile);
            hxofs=2;
            hxsz=12;
            break;
        }
        
        break;
    }
    
    case wBrang:
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_brang);
        }
        
        if(itemid >-1)
            defaultw = itemsbuf[itemid].wpn;
        else
            defaultw = wBRANG;
            
        LOADGFX(defaultw);
        hxofs=4;
        hxsz=7;
        hyofs=2;
        hysz=11;
        dummy_bool[0]=false;                                  //grenade armed?
        break;
        
    case wHookshot:
        hookshot_used=true;
        
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_hookshot);
        }
        
        if(itemid >-1)
            defaultw = itemsbuf[itemid].wpn;
        else
            defaultw = wHSHEAD;
            
        LOADGFX(defaultw);
        step = 4;
        clk2=256;
        
        switch(dir)
        {
        case down:
            flip=2;
            xofs+=4;
            yofs+=1;
            hyofs=2;
            hysz=12;
            break;
            
        case up:
            yofs+=3;
            xofs-=5;
            hyofs=2;
            hysz=12;
            break;
            
        case left:
            flip=1; /*tile=o_tile+((frames>1)?frames:1)*/update_weapon_frame(((frames>1)?frames:1),o_tile);
            xofs+=2;
            yofs=playing_field_offset+4;
            hxofs=2;
            hxsz=12;
            break;
            
        case right: /*tile=o_tile+((frames>1)?frames:1)*/
            update_weapon_frame(((frames>1)?frames:1),o_tile);
            xofs-=2;
            yofs=playing_field_offset+4;
            hxofs=2;
            hxsz=12;
            break;
        }
        
        break;
        
    case wHSHandle:
        step = 0;
        
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_hookshot);
        }
        
        if(itemid >-1)
            defaultw = itemsbuf[itemid].wpn4;
        else
            defaultw = wHSHANDLE;
            
        LOADGFX(defaultw);
        
        switch(dir)
        {
        case down:
            flip=2;
            xofs+=4;
            yofs+=1;
            hyofs=2;
            hysz=12;
            break;
            
        case up:
            yofs+=3;
            xofs-=5;
            hyofs=2;
            hysz=12;
            break;
            
        case left:
            flip=1; /*tile=o_tile+((frames>1)?frames:1)*/update_weapon_frame(((frames>1)?frames:1),o_tile);
            xofs+=2;
            yofs=playing_field_offset+4;
            hxofs=2;
            hxsz=12;
            break;
            
        case right: /*tile=o_tile+((frames>1)?frames:1)*/
            update_weapon_frame(((frames>1)?frames:1),o_tile);
            xofs-=2;
            yofs=playing_field_offset+4;
            hxofs=2;
            hxsz=12;
            break;
        }
        
        break;
        
    case wHSChain:
    {
        if(isDummy || itemid<0)
        {
            itemid = getCanonicalItemID(itemsbuf, itype_hookshot);
        }
        
        if(itemid >-1)
            defaultw = (dir<left) ? itemsbuf[itemid].wpn3 : itemsbuf[itemid].wpn2;
        else
            defaultw = (dir<left) ? wHSCHAIN_V : wHSCHAIN_H;
            
        step = 0;
        
        switch(dir)
        {
        case down:
            LOADGFX(defaultw);
            xofs+=4;
            yofs-=7;
            break;
            
        case up:
            LOADGFX(defaultw);
            xofs-=5;
            yofs+=11;
            break;
            
        case left:
            LOADGFX(defaultw);
            xofs+=10;
            yofs=playing_field_offset+4;
            break;
            
        case right:
            LOADGFX(defaultw);
            xofs-=10;
            yofs=playing_field_offset+4;
            break;
	
	//Try drawing diagonal. -Z
	case r_up:
		LOADGFX(defaultw);
		xofs-=10;
		yofs+=7;
		break;
	case r_down:
		LOADGFX(defaultw);
		xofs-=10;
		yofs-=7;
		break;
	case l_up:
		LOADGFX(defaultw);
		xofs+=10;
		yofs+=7;
		break;
	case l_down:
		LOADGFX(defaultw);
		xofs+=10;
		yofs-=7;
		break;
        }
    }
    break;
    
    case ewLitBomb:
    case ewBomb:
        LOADGFX(ewBOMB);
        hxofs=0;
        hxsz=16;
        
		if(get_bit(quest_rules, qr_OFFSETEWPNCOLLISIONFIX))
		{
			hyofs=0;
			hysz=16;
		}
        
        if(id==ewBomb)
            misc=2;
        else
            step=3;
            
        switch(dir)
        {
        case down:
            flip=2;
            
        case up:
            break;
            
        case left:
            flip=1;
            
        case right: /*tile=o_tile+((frames>1)?frames:1)*/
            update_weapon_frame(((frames>1)?frames:1),o_tile);
            break;
        }
        
        break;
        
    case ewLitSBomb:
    case ewSBomb:
        LOADGFX(ewSBOMB);
        hxofs=0;
        hxsz=16;
		if(get_bit(quest_rules, qr_OFFSETEWPNCOLLISIONFIX))
		{
			hyofs=0;
			hysz=16;
		}
        
        if(id==ewSBomb)
            misc=2;
        else
            step=3;
            
        switch(dir)
        {
        case down:
            flip=2;
            
        case up:
            break;
            
        case left:
            flip=1;
            
        case right: /*tile=o_tile+((frames>1)?frames:1)*/
            update_weapon_frame(((frames>1)?frames:1),o_tile);
            break;
        }
        
        break;
        
    case ewBrang:
        if(get_bit(quest_rules, qr_OFFSETEWPNCOLLISIONFIX))
        {
            hxofs=0;
            hxsz=16;
			hyofs=0;
			hysz=16;
        }
        else
        {
            hxofs=4;
            hxsz=8;
        }
        
        wid = zc_min(zc_max(current_item(itype_brang),1),3)-1+wBRANG;
        LOADGFX(wid);
        break;
        
    case ewFireball2:
        if(dir < 8)
            misc=dir;
        else
        {
            misc = -1;
        }
        
        //fallthrough
    case ewFireball:
    case wRefFireball:
        LOADGFX(ewFIREBALL);
        step=1.75;
        
        if(Type&2)
        {
            seekLink();
        }
        else misc=-1;
        
        break;
        
    case ewRock:
        LOADGFX(ewROCK);
        
        if(get_bit(quest_rules, qr_OFFSETEWPNCOLLISIONFIX))
        {
            hxofs=0;
            hxsz=16;
			hyofs=0;
			hysz=16;
        }
        else
        {
            hxofs=4;
            hxsz=8;
        }
        
        step=3;
        break;
        
    case ewArrow:
        LOADGFX(ewARROW);
        step=2;
        
        switch(dir)
        {
        case down:
            flip=2;
            
        case up:
            xofs=-4;
            hxsz=8;
            break;
            
        case left:
            flip=1;
            
        case right: /*tile=o_tile+((frames>1)?frames:1)*/
            update_weapon_frame(((frames>1)?frames:1),o_tile);
            yofs=playing_field_offset+1;
            break;
        }
        
        break;
        
    case ewSword:
        LOADGFX(ewSWORD);
        
        if(get_bit(quest_rules, qr_OFFSETEWPNCOLLISIONFIX))
        {
            hxofs=0;
            hxsz=16;
			hyofs=0;
			hysz=16;
        }
        else
        {
            hxofs=4;
            hxsz=8;
        }
        
        step=3;
        
        switch(dir)
        {
        case down:
            flip=2;
            
        case up:
            break;
            
        case left:
            flip=1;
            
        case right: /*tile=o_tile+((frames>1)?frames:1)*/
            update_weapon_frame(((frames>1)?frames:1),o_tile);
            yofs=playing_field_offset+1;
            break;
        }
        
        break;
        
    case wRefMagic:
    case ewMagic:
        LOADGFX(ewMAGIC);
        
        if(get_bit(quest_rules, qr_OFFSETEWPNCOLLISIONFIX))
        {
            hxofs=0;
            hxsz=16;
			hyofs=0;
			hysz=16;
        }
        else
        {
            hxofs=4;
            hxsz=8;
        }
        
        step=3;
        
        switch(dir)
        {
        case down:
            flip=2;
            
        case up:
            break;
            
        case left:
            flip=1;
            
        case right: /*tile=o_tile+((frames>1)?frames:1)*/
            update_weapon_frame(((frames>1)?frames:1),o_tile);
            yofs=playing_field_offset+1;
            break;
        }
        
        if(id==wRefMagic)
        {
            ignorecombo=(((int)y&0xF0)+((int)x>>4));
        }
        
        break;
        
    case ewFlame:
    case ewFlame2:
        if(id==ewFlame)
            LOADGFX(ewFLAME);
        else
            LOADGFX(ewFLAME2);
            
        if(dir==255)
        {
            step=2;
            seekLink();
        }
        else
        {
            /*if(Dir<0)
            {
            	step = 0;
            }*/
            if(dir>right)
            {
                step = .707;
            }
            else
            {
                step = 1;
            }
        }
        
		if(get_bit(quest_rules, qr_OFFSETEWPNCOLLISIONFIX))
		{
			hxofs=hyofs=0;
			hxsz=hysz=16;
		}
		else
		{
			hxofs = hyofs=1; // hof of 1 means that link can use the 'half-tile trick'.
			hxsz = hysz = 14;
		}
        
        if(BSZ)
            yofs+=2;
            
        break;
        
    case ewFireTrail:
        LOADGFX(ewFIRETRAIL);
        step=0;
        dir=-1;
        
        if(get_bit(quest_rules, qr_OFFSETEWPNCOLLISIONFIX))
		{
			hxofs=hyofs=0;
			hxsz=hysz=16;
		}
		else
		{
			hxofs = hyofs=1; // hof of 1 means that link can use the 'half-tile trick'.
			hxsz = hysz = 15;
		}
        
        if(BSZ)
            yofs+=2;
            
        break;
        
    case ewWind:
        if(get_bit(quest_rules, qr_OFFSETEWPNCOLLISIONFIX))
		{
			hxofs=hyofs=0;
			hxsz=hysz=16;
		}
		
        LOADGFX(ewWIND);
        clk=0;
        step=3;
        break;
        
    case wPhantom:
        switch(type)
        {
        case pDINSFIREROCKET:
            if(get_bit(quest_rules,qr_MORESOUNDS))
                sfx(WAV_ZN1ROCKETUP,(int)x);
                
            LOADGFX(itemsbuf[parentitem].wpn);
            step = 4;
            break;
            
        case pDINSFIREROCKETRETURN:
            if(get_bit(quest_rules,qr_MORESOUNDS))
                sfx(WAV_ZN1ROCKETDOWN,(int)x);
                
            LOADGFX(itemsbuf[parentitem].wpn2);
            step = 4;
            break;
            
        case pDINSFIREROCKETTRAIL:
            LOADGFX(itemsbuf[parentitem].wpn3);
            break;
            
        case pDINSFIREROCKETTRAILRETURN:
            LOADGFX(itemsbuf[parentitem].wpn4);
            break;
            
        case pMESSAGEMORE:
            LOADGFX(iwMore);
            break;
            
        case pNAYRUSLOVEROCKET1:
            LOADGFX(itemsbuf[parentitem].wpn);
            
            if(get_bit(quest_rules,qr_MORESOUNDS))
                sfx(WAV_ZN1ROCKETUP,(int)x);
                
            step = 4;
            drawstyle=itemsbuf[parentitem].flags & ITEM_FLAG2 ? 1 : 0;
            break;
            
        case pNAYRUSLOVEROCKETRETURN1:
            LOADGFX(itemsbuf[parentitem].wpn2);
            
            if(get_bit(quest_rules,qr_MORESOUNDS))
                sfx(WAV_ZN1ROCKETDOWN,(int)x);
                
            step = 4;
            drawstyle=itemsbuf[parentitem].flags & ITEM_FLAG2 ? 1 : 0;
            break;
            
        case pNAYRUSLOVEROCKETTRAIL1:
            LOADGFX(itemsbuf[parentitem].wpn3);
            drawstyle=itemsbuf[parentitem].flags & ITEM_FLAG2 ? 1 : 0;
            break;
            
        case pNAYRUSLOVEROCKETTRAILRETURN1:
            LOADGFX(itemsbuf[parentitem].wpn4);
            drawstyle=itemsbuf[parentitem].flags & ITEM_FLAG2 ? 1 : 0;
            break;
            
        case pNAYRUSLOVEROCKET2:
            LOADGFX(itemsbuf[parentitem].wpn6);
            step = 4;
            drawstyle=itemsbuf[parentitem].flags & ITEM_FLAG2 ? 1 : 0;
            break;
            
        case pNAYRUSLOVEROCKETRETURN2:
            LOADGFX(itemsbuf[parentitem].wpn7);
            step = 4;
            drawstyle=itemsbuf[parentitem].flags & ITEM_FLAG2 ? 1 : 0;
            break;
            
        case pNAYRUSLOVEROCKETTRAIL2:
            LOADGFX(itemsbuf[parentitem].wpn8);
            drawstyle=itemsbuf[parentitem].flags & ITEM_FLAG2 ? 1 : 0;
            break;
            
        case pNAYRUSLOVEROCKETTRAILRETURN2:
            LOADGFX(itemsbuf[parentitem].wpn9);
            drawstyle=itemsbuf[parentitem].flags & ITEM_FLAG2 ? 1 : 0;
            break;
            
        default:
            tile=0;
            break;
        }
        
        break;
        
    default:
        LOADGFX(0);
        break;
    }
    
    if(id>wEnemyWeapons && id!=ewBrang && (Type&4)!=0)  // Increase speed of Aquamentus 2 fireballs
    {
        step *=2;
    }
}

void weapon::LOADGFX(int wpn)
{
    if(wpn<0)
        return;
        
    wid = wpn;
    flash = wpnsbuf[wid].misc&3;
    tile  = wpnsbuf[wid].tile;
    cs = wpnsbuf[wid].csets&15;
    o_tile = wpnsbuf[wid].tile;
    o_cset = wpnsbuf[wid].csets;
    o_flip=(wpnsbuf[wid].misc>>2)&3;
    o_speed = wpnsbuf[wid].speed;
    o_type = wpnsbuf[wid].type;
    frames = wpnsbuf[wid].frames;
    temp1 = wpnsbuf[wFIRE].tile;
    behind = (wpnsbuf[wid].misc&WF_BEHIND)!=0;
}

bool weapon::Dead()
{
    return dead!=-1;
}

bool weapon::clip()
{
    int c[4];
    int d2=isdungeon();
    int nb1 = get_bit(quest_rules,qr_NOBORDER) ? 16 : 0;
    int nb2 = get_bit(quest_rules,qr_NOBORDER) ? 8 : 0;
    
    if(id>wEnemyWeapons && id!=ewBrang)
    {
        c[0] = d2?32:(16-nb1);
        c[1] = d2?128:(144+nb1);
        c[2] = d2?32:(16-nb1);
        c[3] = d2?208:(224+nb1);
    }
    else if(id==wHookshot||id==wHSChain)
    {
        c[0] = d2?8:0;
        c[1] = d2?152:160;
        c[2] = d2?8:0;
        c[3] = d2?248:256;
    }
    else
    {
        c[0] = d2?18:2;
        c[1] = d2?144:160;
        c[2] = d2?20:4;
        c[3] = d2?220:236;
    }
    
    if(id==wSSparkle || id==wFSparkle)
    {
        c[0] = 0;
        c[1] = 176;
        c[2] = 0;
        c[3] = 256;
    }
    
    if(id==ewFlame)
    {
        c[0] = d2?32:(16-nb1);
        c[1] = d2?128:(144+nb1);
        c[2] = d2?32:(16-nb1);
        c[3] = d2?208:(224+nb1);
    }
    
    if(id==ewFireTrail)
    {
        c[0] = d2?32:(16-nb1);
        c[1] = d2?128:(144+nb1);
        c[2] = d2?32:(16-nb1);
        c[3] = d2?208:(224+nb1);
    }
    
    if(id==ewWind)
    {
        c[0] = d2?32:(16-nb1);
        c[1] = d2?128:(144+nb1);
        c[2] = d2?32:(16-nb1);
        c[3] = d2?208:(224+nb1);
    }
    
    if(x < c[2])
        if(dir==left || dir==l_up || dir==l_down)
            return true;
            
    if(x > c[3])
        if(dir==right || dir==r_up || dir==r_down)
            return true;
            
    if(y < c[0])
        if(dir==up || dir==l_up || dir==r_up)
            return true;
            
    if(y > c[1])
        if(dir==down || dir==l_down || dir==r_down)
            return true;
            
    if(id>wEnemyWeapons)
    {
        if((x<(8-nb2) && dir==left)
                || (y<(8-nb2) && dir==up)
                || (x>(232+nb2) && dir==right)
                || (y>(168+nb2) && dir==down))
            return true;
    }
    
    if(x<0||y<0||x>240||y>176)
        return true;
        
    return false;
}

bool weapon::blocked()
{
    return blocked(8, 8);
}

bool weapon::blocked(int xOffset, int yOffset)
{
    int wx = x+xOffset;
    int wy = y+yOffset;
    
    if(id == wPhantom || id == wHSHandle || id == wHSChain)  // Sanity check
    {
        return false;
    }
    
    if(get_bit(combo_class_buf[COMBOTYPE(wx,wy)].block_weapon,id)
            || get_bit(combo_class_buf[FFCOMBOTYPE(wx,wy)].block_weapon, id))
    {
        if(parentitem<0 || (combo_class_buf[COMBOTYPE(wx,wy)].block_weapon_lvl >=
                            itemsbuf[parentitem].fam_type))
        {
            return true;
        }
    }
    
    switch(dir)
    {
    case up:
        wy-=8;
        break;
        
    case down:
        wy+=8;
        break;
        
    case left:
        wx-=8;
        break;
        
    case right:
        wx+=8;
        break;
    }
    
    if(get_bit(combo_class_buf[COMBOTYPE(wx,wy)].block_weapon,id)
            || get_bit(combo_class_buf[FFCOMBOTYPE(wx,wy)].block_weapon, id))
    {
        if(parentitem<0 || (combo_class_buf[COMBOTYPE(wx,wy)].block_weapon_lvl >=
                            itemsbuf[parentitem].fam_type))
        {
            return true;
        }
    }
    
    return false;
}

bool weapon::animate(int)
{
    // do special timing stuff
    bool hooked=false;
    
    // fall down
    switch(id)
    {
    case wFire:
    
        // Din's Fire shouldn't fall
        if(parentitem>=0 && itemsbuf[parentitem].family==itype_dinsfire && !(itemsbuf[parentitem].flags & ITEM_FLAG3))
        {
            break;
        }
        
    case wLitBomb:
    case wLitSBomb:
    case wBait:
    case ewFlame:
    case ewFireTrail:
        if(tmpscr->flags7&fSIDEVIEW)
        {
            if(!_walkflag(x,y+16,0))
            {
                y+=fall/100;
                
                if(fall <= (int)zinit.terminalv)
                {
                    fall += zinit.gravity;
                }
            }
            else
            {
                if(fall!=0 && !(step>0 && dir==up))  // Don't fix pos if still moving through solidness
                    y-=(int)y%8; // Fix position
                    
                fall = 0;
            }
            
            if(y>192) dead=0;  // Out of bounds
        }
        else
        {
            z-=fall/100;
            
            if(z<=0)
            {
                z = fall = 0;
            }
            else if(fall <= (int)zinit.terminalv)
            {
                fall += zinit.gravity;
            }
        }
    }
    
    if(id>wEnemyWeapons && id!=ewBrang && id != ewFireball2 && id != ewBomb && id != ewSBomb)
        switch(misc)
        {
        case up:
            y-=.5;
            break;
            
        case down:
            y+=.5;
            break;
            
        case left:
            x-=.5;
            break;
            
        case right:
            x+=.5;
            break;
            
        case 4:
            y-=1;
            break;
            
        case 5:
            y+=1;
            break;
            
        case 6:
            x-=1;
            break;
            
        case 7:
            x+=1;
            break;
            //case l_up:  y-=.354; x-=.354; break;
            //case r_up:  y-=.354; x+=.354; break;
            //case l_down:y+=.354; x-=.354; break;
            //case r_down:y+=.354; x+=.354; break;
        }
        
    switch(id)
    {
        // Link's weapons
    case wSword:
    case wWand:
    case wHammer:
        if(LinkAction()!=attacking && LinkAction()!=ischarging && !LinkCharged())
        {
            dead=0;
        }
        
        break;
        
    case wCByrna:
    {
        if(blocked())
        {
            dead=0;
        }
        
        int speed = parentitem>-1 ? zc_max(itemsbuf[parentitem].misc1,1) : 1;
        int radius = parentitem>-1 ? zc_max(itemsbuf[parentitem].misc2,8) : 8;
        double xdiff = -(sin((double)clk/speed) * radius);
        double ydiff = (cos((double)clk/speed) * radius);
        
        double ddir=atan2(double(ydiff),double(xdiff));
        
        if((ddir<=(((-5)*PI)/8))&&(ddir>(((-7)*PI)/8)))
            dir=r_up;
        else if((ddir<=(((-3)*PI)/8))&&(ddir>(((-5)*PI)/8)))
            dir=right;
        else if((ddir<=(((-1)*PI)/8))&&(ddir>(((-3)*PI)/8)))
            dir=r_down;
        else if((ddir<=(((1)*PI)/8))&&(ddir>(((-1)*PI)/8)))
            dir=down;
        else if((ddir<=(((3)*PI)/8))&&(ddir>(((1)*PI)/8)))
            dir=l_down;
        else if((ddir<=(((5)*PI)/8))&&(ddir>(((3)*PI)/8)))
            dir=left;
        else if((ddir<=(((7)*PI)/8))&&(ddir>(((5)*PI)/8)))
            dir=l_up;
        else
            dir=up;
            
        x = (fix)((double)LinkX() + xdiff);
        y = (fix)((double)LinkY() + ydiff);
        z = LinkZ();
        
        if(parentitem>-1)
            sfx(itemsbuf[parentitem].usesound,pan(int(x)),true,false);
    }
    break;
    
    case wBeam:
    case wRefBeam:
        for(int i2=0; i2<=zc_min(type-1,3) && dead!=23; i2++)
        {
            if(findentrance(x,y,mfSWORDBEAM+i2,true)) dead=23;
        }
        
        if(blocked())
        {
            dead=23;
        }
        
    case ewSword:
        if(blocked())
        {
            dead=0;
        }
        
        if(get_bit(quest_rules,qr_SWORDMIRROR))
        {
            int checkx=0, checky=0;
            
            switch(dir)
            {
            case up:
                checkx=x+7;
                checky=y+8;
                break;
                
            case down:
                checkx=x+7;
                checky=y;
                break;
                
            case left:
                checkx=x+8;
                checky=y+7;
                break;
                
            case right:
                checkx=x;
                checky=y+7;
                break;
            }
            
            if(ignorecombo==(((int)checky&0xF0)+((int)checkx>>4)))
                break;
                
            if(hitcombo(checkx,checky,cMIRROR))
            {
                id = wRefBeam;
                dir ^= 1;
                
                if(dir&2)
                    flip ^= 1;
                else
                    flip ^= 2;
                    
                ignoreLink=false;
                ignorecombo=(((int)checky&0xF0)+((int)checkx>>4));
                y=(int)y&0xF0;
                x=(int)x&0xF0;
            }
            
            if(hitcombo(checkx,checky,cMIRRORSLASH))
            {
                id = wRefBeam;
                dir = 3-dir;
                {
                    if(dir==right)
                        flip &= ~1; // not horiz
                    else if(dir==left)
                        flip |= 1;  // horiz
                    else if(dir==up)
                        flip &= ~2; // not vert
                    else if(dir==down)
                        flip |= 2;  // vert
                }
                tile=o_tile;
                
                if(dir&2)
                {
                    if(frames>1)
                    {
                        tile+=frames;
                    }
                    else
                    {
                        ++tile;
                    }
                }
                
                ignoreLink=false;
                ignorecombo=(((int)checky&0xF0)+((int)checkx>>4));
                y=(int)y&0xF0;
                x=(int)x&0xF0;
            }
            
            if(hitcombo(checkx,checky,cMIRRORBACKSLASH))
            {
                id = wRefBeam;
                dir ^= 2;
                {
                    if(dir==right)
                        flip &= ~1; // not horiz
                    else if(dir==left)
                        flip |= 1;  // horiz
                    else if(dir==up)
                        flip &= ~2; // not vert
                    else if(dir==down)
                        flip |= 2;  // vert
                }
                tile=o_tile;
                
                if(dir&2)
                {
                    if(frames>1)
                    {
                        tile+=frames;
                    }
                    else
                    {
                        ++tile;
                    }
                }
                
                ignoreLink=false;
                ignorecombo=(((int)checky&0xF0)+((int)checkx>>4));
                y=(int)y&0xF0;
                x=(int)x&0xF0;
            }
            
            if(hitcombo(checkx,checky,cMAGICPRISM))
            {
                int newx, newy;
                newy=(int)y&0xF0;
                newx=(int)x&0xF0;
                
                for(int tdir=0; tdir<4; tdir++)
                {
                    if(dir!=(tdir^1))
                    {
                        weapon *w=new weapon(*this);
                        w->dir=tdir;
                        w->x=newx;
                        w->y=newy;
                        w->z=z;
                        w->id=wRefBeam;
                        w->parentid=parentid;
                        w->parentitem=parentitem;
                        w->ignorecombo=(((int)checky&0xF0)+((int)checkx>>4));
                        w->hyofs = w->hxofs = 0;
                        //also set up the magic's correct animation -DD
                        w->flip=0;
                        
                        switch(w->dir)
                        {
                        case down:
                            w->flip=2;
                            
                        case up:
                            w->tile = w->o_tile;
                            w->hyofs=2;
                            w->hysz=12;
                            break;
                            
                        case left:
                            w->flip=1;
                            
                        case right:
                            w->tile=w->o_tile+((w->frames>1)?w->frames:1);
                            w->hxofs=2;
                            w->hxsz=12;
                            break;
                        }
                        
                        Lwpns.add(w);
                    }
                }
                
                dead=0;
            }
            
            if(hitcombo(checkx,checky,cMAGICPRISM4))
            {
                int newx, newy;
                newy=(int)y&0xF0;
                newx=(int)x&0xF0;
                
                for(int tdir=0; tdir<4; tdir++)
                {
                    weapon *w=new weapon(*this);
                    w->dir=tdir;
                    w->x=newx;
                    w->y=newy;
                    w->z=z;
                    w->id=wRefBeam;
                    w->parentid=parentid;
                    w->parentitem=parentitem;
                    w->hyofs = w->hxofs = 0;
                    w->ignorecombo=(((int)checky&0xF0)+((int)checkx>>4));
                    //also set up the magic's correct animation -DD
                    w->flip=0;
                    
                    switch(w->dir)
                    {
                    case down:
                        w->flip=2;
                        
                    case up:
                        w->tile = w->o_tile;
                        w->hyofs=2;
                        w->hysz=12;
                        break;
                        
                    case left:
                        w->flip=1;
                        
                    case right:
                        w->tile=w->o_tile+((w->frames>1)?w->frames:1);
                        w->hxofs=2;
                        w->hxsz=12;
                        break;
                    }
                    
                    Lwpns.add(w);
                }
                
                dead=0;
            }
        }
        
        break;
        
    case wWhistle:
        if(clk)
        {
            dead=1;
        }
        
        break;
        
    case wWind:
    {
        if(blocked())
        {
            dead=1;
        }
        
        int wrx;
        
        if(get_bit(quest_rules,qr_NOARRIVALPOINT))
            wrx=tmpscr->warpreturnx[0];
        else wrx=tmpscr->warparrivalx;
        
        int wry;
        
        if(get_bit(quest_rules,qr_NOARRIVALPOINT))
            wry=tmpscr->warpreturny[0];
        else wry=tmpscr->warparrivaly;
        
        if(type==1 && dead==-1 && x==(int)wrx && y==(int)wry)
        {
            dead=2;
        }
        else if(LinkAction() !=inwind && ((dir==right && x>=240) || (dir==down && y>=160) || (dir==left && x<=0) || (dir==up && y<=0)))
        {
            stop_sfx(WAV_ZN1WHIRLWIND);
            dead=1;
        }
        else if(get_bit(quest_rules,qr_MORESOUNDS))
            sfx(WAV_ZN1WHIRLWIND,pan(int(x)),true,false);
            
        if(get_bit(quest_rules,qr_WHIRLWINDMIRROR))
            goto mirrors;
            
        break;
    }
    
    case wFire:
    {
        if(blocked())
        {
            dead=1;
        }
        
        if(parentitem<0 || (parentitem>-1 && itemsbuf[parentitem].family!=itype_book))
        {
            if(clk==32)
            {
                step=0;
                
                if(parentitem<0 || !(itemsbuf[parentitem].flags & ITEM_FLAG2))
                {
                    isLit = true;
                    checkLightSources();
                }
            }
            
            if(clk==94)
            {
                dead=1;
                
                if((parentitem<0 || !(itemsbuf[parentitem].flags & ITEM_FLAG2)) &&
                   get_bit(quest_rules,qr_TEMPCANDLELIGHT) &&
                   (Lwpns.idCount(wFire) + Ewpns.idCount(ewFlame))==1)
                {
                    isLit = false;
                    checkLightSources();
                }
            }
            
            if(clk==94 || get_bit(quest_rules,qr_INSTABURNFLAGS))
            {
                findentrance(x,y,mfBCANDLE,true);
                
                if(type>0)
                {
                    findentrance(x,y,mfRCANDLE,true);
                }
                
                if(type>2)
                {
                    findentrance(x,y,mfDINSFIRE,true);
                }
            }
        }                                                     //wand fire
        else
        {
            if(clk==1)
            {
                isLit = true;
                checkLightSources();
            }
            
            if(clk==80)
            {
                dead=1;
                findentrance(x,y,mfBCANDLE,true);
                findentrance(x,y,mfRCANDLE,true);
                findentrance(x,y,mfWANDFIRE,true);
                
                if(get_bit(quest_rules,qr_TEMPCANDLELIGHT) && (Lwpns.idCount(wFire) + Ewpns.idCount(ewFlame))==1)
                {
                    isLit=false;
                    checkLightSources();
                }
            }
        }
        
        // Killed by script?
        if(dead==0 && get_bit(quest_rules,qr_TEMPCANDLELIGHT) && (Lwpns.idCount(wFire) + Ewpns.idCount(ewFlame))==1)
        {
            isLit=false;
            checkLightSources();
        }
        
        break;
    }
    
    case wLitBomb:
    case wBomb:
    case ewLitBomb:
    case ewBomb:
    case ewLitSBomb:
    case ewSBomb:
    case wLitSBomb:
    case wSBomb:
    {
        if(!misc)
        {
            break;
        }
        
        // Naaah.
        /*if (blocked())
        {
          dead=1;
        }*/
        if(clk==(misc-2) && step==0)
        {
            id = (id>wEnemyWeapons ? (id==ewLitSBomb||id==ewSBomb ? ewSBomb : ewBomb)
                      : parentitem>-1 ? ((itemsbuf[parentitem].family==itype_sbomb) ? wSBomb:wBomb)
                      : (id==wLitSBomb||id==wSBomb ? wSBomb : wBomb));
            hxofs=2000;
        }
        
        if(clk==(misc-1) && step==0)
    {	//The hardcoded bomb sound. -Z
            sfx((id>=wEnemyWeapons || parentitem<0) ? WAV_BOMB :
                itemsbuf[parentitem].usesound,pan(int(x)));
                
            if(id==wSBomb || id==wLitSBomb || id==ewSBomb || id==ewLitSBomb)
            {
                hxofs=hyofs=-16;
                hxsz=hysz=48;
            }
            else
            {
                hxofs=hyofs=-8;
                hxsz=hysz=32;
            }
            
            hzsz=16;
        }
        
        int boomend = (misc+(((id == wBomb || id == wSBomb || id == wLitBomb || id == wLitSBomb) &&
                              (parentitem>-1 && itemsbuf[parentitem].flags & ITEM_FLAG1)) ? 35 : 31));
                              
        if(clk==boomend && step==0)
        {
            hxofs=2000;
        }
        
        if(id<wEnemyWeapons)
        {
            if(clk==(misc-1))
            {
                int f1 = (id==wSBomb || id==wLitSBomb) ? 16 : 0; // Large SBomb triggerbox
                
                for(int tx=-f1; tx<=f1; tx+=8)  // -16,-8,0,8,16
                {
                    int f2 = 0;
                    
                    if(tx==-8 || tx==8)
                        f2 = f1;
                        
                    for(int ty=-f2; ty<=f2; ty+=32)
                    {
                        findentrance(x+tx,y+ty+(tmpscr->flags7&fSIDEVIEW?2:-3),mfBOMB,true);
                        
                        if(id==wSBomb || id==wLitSBomb)
                        {
                            findentrance(x+tx,y+ty+(tmpscr->flags7&fSIDEVIEW?2:-3),mfSBOMB,true);
                        }
                        
                        findentrance(x+tx,y+ty+(tmpscr->flags7&fSIDEVIEW?2:-3),mfSTRIKE,true);
                    }
                }
            }
            
            if(!get_bit(quest_rules,qr_NOBOMBPALFLASH))
            {
                if(!usebombpal)
                {
                    if(clk==misc || clk==misc+5)
                    {
                    
                        usebombpal=true;
                        memcpy(tempbombpal, RAMpal, PAL_SIZE*sizeof(RGB));
                        
                        //grayscale entire screen
                        if(get_bit(quest_rules,qr_FADE))
                        {
                            for(int i=CSET(0); i < CSET(15); i++)
                            {
                                int g = zc_min((RAMpal[i].r*42 + RAMpal[i].g*75 + RAMpal[i].b*14) >> 7, 63);
                                g = (g >> 1) + 32;
                                RAMpal[i] = _RGB(g,g,g);
                            }
                            
                        }
                        else
                        {
                            // this is awkward. NES Z1 converts colors based on the global
                            // NES palette. Something like RAMpal[i] = NESpal( reverse_NESpal(RAMpal[i]) & 0x30 );
                            for(int i=CSET(0); i < CSET(15); i++)
                            {
                                RAMpal[i] = NESpal(reverse_NESpal(RAMpal[i]) & 0x30);
                            }
                        }
                        
                        refreshpal = true;
                    }
                }
                
                if((clk==misc+4 || clk==misc+9) && usebombpal)
                {
                    // undo grayscale
                    usebombpal=false;
                    memcpy(RAMpal, tempbombpal, PAL_SIZE*sizeof(RGB));
                    refreshpal = true;
                }
            }
            
            if(clk==misc+30)
            {
                bombdoor(x,y);
            }
        }
        
        if(clk==misc+34)
        {
            if(step==0)
            {
                dead=1;
            }
        }
        
        break;
    }
    
    case wArrow:
    {
        if(dead>0)
        {
            break;
        }
        
        if(misc>0 && clk > misc)
        {
            dead=4;
        }
	
	if(scriptrange>0 && clk > scriptrange)
        {
            dead=4;
        }
        
        if(findentrance(x,y,mfSTRIKE,true))
        {
            dead=4;
        }
        
        if(findentrance(x,y,mfARROW,true))
        {
            dead=4;
        }
        
        if(current_item(itype_arrow)>1)
        {
            if(findentrance(x,y,mfSARROW,true))
            {
                dead=4;
            }
        }
        
        if(current_item(itype_arrow)>=3)
        {
            if(findentrance(x,y,mfGARROW,true))
            {
                dead=4;
            }
        }
        
        if(blocked())
        {
            dead=4;
        }
        
        break;
    }
    
    case wSSparkle:
        if(blocked())  //no spakle area?
        {
            dead=1;
        }
        
        if(clk>=frames*o_speed-1) //(((wpnsbuf[wSSPARKLE].frames) * (wpnsbuf[wSSPARKLE].speed))-1))
        {
            dead=1;
        }
        
        break;
        
    case wFSparkle:
        if(blocked())  //no sparkle area?
        {
            dead=1;
        }
        
        if(clk>=frames*o_speed-1) //(((wpnsbuf[wFSPARKLE].frames) * (wpnsbuf[wFSPARKLE].speed))-1))
        {
            dead=1;
        }
        
        break;
        
    case wBait:
        if(blocked())  //no bait area?
        {
            dead=23;
        }
        
        if(parentitem>-1 && clk>=itemsbuf[parentitem].misc1)
        {
            dead=1;
        }
        
        break;
      //THe lw_brang definition: -Z  
    case wBrang:
    {
        if(dead==0)  // Set by ZScript
        {
            stop_sfx(itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].usesound);
            break;
        }
        
        else if(dead==1) // Set by ZScript
        {
            onhit(false);
        }
        
        int deadval=(itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].flags & ITEM_FLAG3)?-2:1;
        
        for(int i=0; i<current_item(itype_brang); i++)
        {
            if(findentrance(x,y,mfBRANG+i,true)) dead=deadval;
        }
        
	//piercing boomerang goes here. -Z
	
        if(findentrance(x,y,mfSTRIKE,true)) dead=deadval;
        
        if(blocked())
        {
            dead=deadval;
            onhit(false);
        }
        
        ++clk2;
	
	
	//scriptrange is now -1
        int range = itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].misc1;
	if ( scriptrange < 0 ) scriptrange =  itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].misc1;
	else if ( scriptrange >= 0 ) {
		range = scriptrange; 
	}
	
	//This sets zscript l->Range to the editor value if it is still the default (-1)
	//If the user write to l->Range, it updates.

	
	/*
		if ( scriptrange <= 0 ) {
			//Stop the range from unsetting. 
			scriptrange = itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].misc1;
			range = itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].misc1;
		}
		if ( scriptrange > 0 ) range = scriptrange;
		else range = itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].misc1;
	*/
        
        if(range && clk2>=range)
        {
            if(deadval==1)
            {
                misc=1;
            }
            else
            {
                dead=deadval;
            }
        }
        
        if(range && clk2>range-18 && clk2<range+16)
        {
            step=1;
        }
        else if(misc)
        {
            step=2;
        }
        else
        {
            step=3;
        }
        
        if(clk==0)                                            // delay a frame
        {
            ++clk;
            sfx(itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].usesound,pan(int(x)),true);
            return false;
        }
        
        if(clk==1)                                            // then check directional input
        {
            if(Up())
            {
                dir=up;
                
                if(Left())  dir=l_up;
                
                if(Right()) dir=r_up;
            }
            else if(Down())
            {
                dir=down;
                
                if(Left())  dir=l_down;
                
                if(Right()) dir=r_down;
            }
            else if(Left())
            {
                dir=left;
            }
            else if(Right())
            {
                dir=right;
            }
        }
        
        if(dead==1)
        {
            dead=-1;
            misc=1;
        }
        
        if(dead==-2)
        {
            misc=1;
        }
        
        if(misc==1)                                           // returning
        {
            if((abs(LinkY()-y)<7 && abs(LinkX()-x)<7)||dead==-2)
            {
                if(dead!=-2)
                {
                    CatchBrang();
                }
                
                if(Lwpns.idCount(wBrang)<=1 && (!get_bit(quest_rules, qr_MORESOUNDS) || !Ewpns.idCount(ewBrang)))
                    stop_sfx(itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].usesound);
                    
                /*if (dummy_bool[0])
                {
                    add_grenade(x,y,z,0,-1); //TODO: Super bombs as well?
                    dummy_bool[0]=false;
                }*/
                if(dragging!=-1)
                {
                    getdraggeditem(dragging);
                }
                
                return true;
            }
            
            seekLink();
        }
        
        sfx(itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].usesound,pan(int(x)),true,false);
        
        break;
    }
    
    case wHookshot:
    {
	//    	//Is this intentionally *16, so that length is in tiles?
	//int  maxlength = parentitem>-1 ? 16*itemsbuf[parentitem].misc1 : 0;
	    int  maxlength = parentitem>-1 ? 2*itemsbuf[parentitem].misc1 : 0; //2* value seems to match the desired range. 
        if(dead==0)  // Set by ZScript
        {
            hookshot_used = false;
            
            for(int i=0; i<chainlinks.Count(); i++)
            {
                chainlinks.del(chainlinks.idFirst(wHSChain));
            }
        }
        if ( scriptrange < 0 ) scriptrange =  maxlength; //scriptrange inits at -1
	else if ( scriptrange > -1 ) { maxlength = scriptrange; } //20JAN17, was >= 0 before. 
		//If the user sets it, change it.
	
	/*
	//copied over from boomerang. 
	if(clk==0)                                            // delay a frame
        {
            ++clk;
            return false;
        }
        
        if(clk==1)                                            // then check directional input
        {
            if(Up())
            {
                dir=up;
                
                if(Left() && (itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_hookshot)].flags&ITEM_FLAG2) )  dir=l_up;
                
                if(Right() && (itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_hookshot)].flags&ITEM_FLAG2) ) dir=r_up;
            }
            else if(Down())
            {
                dir=down;
                
                if(Left() && (itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_hookshot)].flags&ITEM_FLAG2) )  dir=l_down;
                
                if(Right() && (itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_hookshot)].flags&ITEM_FLAG2) ) dir=r_down;
            }
            else if(Left())
            {
                dir=left;
		if(Up() && (itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_hookshot)].flags&ITEM_FLAG2) )  dir=l_up;
		if(Down() && (itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_hookshot)].flags&ITEM_FLAG2) )  dir=l_down;
                
            }
            else if(Right())
            {
                dir=right;
		if(Up() && (itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_hookshot)].flags&ITEM_FLAG2) )  dir=r_up;
		if(Down() && (itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_hookshot)].flags&ITEM_FLAG2) )  dir=r_down;
            }
        }
	
	*/
	if ( (itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_hookshot)].flags&ITEM_FLAG2) && misc2 == 0 ) {
	    if(Up())
	    {
		dir=up;
		
		if(Left() )  dir=l_up;
		
		if(Right() ) dir=r_up;
		    misc2 = 1; //to prevent wagging it all over the screen, we set it once. 
	    }
	    else if(Down())
	    {
		dir=down;
		
		if(Left() )  dir=l_down;
		
		if(Right() ) dir=r_down;
		     misc2 = 1; //to prevent wagging it all over the screen, we set it once. 
	    }
	    else if(Left())
	    {
		dir=left;
		if(Up() )  dir=l_up;
		if(Down() )  dir=l_down;
		     misc2 = 1; //to prevent wagging it all over the screen, we set it once. 
		
	    }
	    else if(Right())
	    {
		dir=right;
		if(Up() )  dir=r_up;
		if(Down() )  dir=r_down;
		     misc2 = 1; //to prevent wagging it all over the screen, we set it once. 
	    }
	}
        // Hookshot grab and retract code
        if(misc==0)
        {
		
		
		
	    
	    //If the hookshot has extended to maxlength, retract it.
            if((abs(LinkX()-x)>maxlength)||(abs(LinkY()-y)>maxlength))
            {
                dead=1;  //causes it to retract.
            }
            
	    //If it hits a block object, retract it.
            if(findentrance(x,y,mfSTRIKE,true)) dead=1;
            
            if(findentrance(x,y,mfHOOKSHOT,true)) dead=1;
            
	    
	    //Look for grab combos based on direction.
	    //...but where is the support for diagonal and angular? Oh, right, no-one ever thought of this.
	    // /sarcasm -Z
	    
	    //This is the issue with weapons that predate angular movement, in general.
	    
	    /*
	    int tempdir = dir;
	    
	    if ( key[KEY_LEFT] && key[KEY_UP] ) tempdir = l_up;
	    if ( key[KEY_LEFT] && key[KEY_DOWN] ) tempdir = l_down;
	    if ( key[KEY_RIGHT] && key[KEY_UP] ) tempdir = r_up;
	    if ( key[KEY_RIGHT] && key[KEY_DOWN] ) tempdir = r_down;
	    */
	    
            if(dir==up)
            {
		    //It would have been nice to comment these coordinates... 
		    //...so that we know *why* the values were used.
                if((combobuf[MAPCOMBO(x+2,y+7)].type==cHSGRAB))
                {
                    hooked=true;
                }
                
                if(get_bit(quest_rules, qr_HOOKSHOTLAYERFIX))
                    hooked = hooked || (combobuf[MAPCOMBO2(0,x+2,y+7)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+2,y+7)].type==cHSGRAB);
                    
		//Retracts if the hookshot hits illegal spaces, solid spaces, and such.
                if(!hooked && _walkflag(x+2,y+7,1) && !ishookshottable((int)x+2,(int)y+7))
                {
                    dead=1;
                }
            }
            
            if(dir==down)
            {
                if((combobuf[MAPCOMBO(x+12,y+12)].type==cHSGRAB))
                {
                    hooked=true;
                }
                
                if(get_bit(quest_rules, qr_HOOKSHOTLAYERFIX))
                    hooked = hooked || (combobuf[MAPCOMBO2(0,x+12,y+12)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+12,y+12)].type==cHSGRAB);
                    
                if(!hooked && _walkflag(x+12,y+12,1) && !ishookshottable((int)x+12,(int)y+12))
                {
                    dead=1;
                }
            }
            
            if(dir==left)
            {
		    //this is why it would be nice to know the specific reasons for the values
		    //.., old rules grabbed at a higher y position
                if(get_bit(quest_rules, qr_OLDHOOKSHOTGRAB))
                {
                    if(combobuf[MAPCOMBO(x+6,y+7)].type==cHSGRAB)
                    {
                        hooked=true;
                    }
                }
                else if(combobuf[MAPCOMBO(x+6,y+13)].type==cHSGRAB)
                {
                    hooked=true;
                }
                
                if(get_bit(quest_rules, qr_HOOKSHOTLAYERFIX))
                    hooked = hooked || (combobuf[MAPCOMBO2(0,x+6,y+13)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+6,y+13)].type==cHSGRAB);
                    
                if(!hooked && _walkflag(x+6,y+13,1) && !ishookshottable((int)x+6,(int)y+13))
                {
                    dead=1;
                }
            }
            
            if(dir==right)
            {
		    
                if(get_bit(quest_rules, qr_OLDHOOKSHOTGRAB))
                {
                    if(combobuf[MAPCOMBO(x+9,y+7)].type==cHSGRAB)
                    {
                        hooked=true;
                    }
                }
                else if((combobuf[MAPCOMBO(x+9,y+13)].type==cHSGRAB))
                {
                    hooked=true;
                }
                
                if(get_bit(quest_rules, qr_HOOKSHOTLAYERFIX))
                    hooked = hooked || (combobuf[MAPCOMBO2(0,x+9,y+13)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+9,y+13)].type==cHSGRAB);
                    
                if(!hooked && _walkflag(x+9,y+13,1) && !ishookshottable((int)x+9,(int)y+13))
                {
                    dead=1;
                }
            }
	    
	    /*
	    if ( dir == angular ) {} //Diagonal or angular
	    
	    */ 

	    //in 2.50.x, if the user sets the hookshot direction to a diagonal, it flat-out refuses to grab. -Z
		//! -Z Hookshot diagonals. Will need bugtesting galore. 
		if ( dir == r_down ) 
		{
			if(get_bit(quest_rules, qr_OLDHOOKSHOTGRAB))
			{	//right						//down
				if( (combobuf[MAPCOMBO(x+9,y+7)].type==cHSGRAB) || (combobuf[MAPCOMBO(x+12,y+12)].type==cHSGRAB) )
				{
					hooked=true;
				}
			}

					//right						//down
			else if( ( (combobuf[MAPCOMBO(x+9,y+13)].type==cHSGRAB)) || (combobuf[MAPCOMBO(x+12,y+12)].type==cHSGRAB) )
			{
				hooked=true;
			}

			if(get_bit(quest_rules, qr_HOOKSHOTLAYERFIX))			//right
			{
				hooked = hooked || (combobuf[MAPCOMBO2(0,x+9,y+13)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+9,y+13)].type==cHSGRAB ) || 
				//down
				(combobuf[MAPCOMBO2(0,x+12,y+12)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+12,y+12)].type==cHSGRAB);
			}
                    
			//right
			if(!hooked &&  ( ( ( _walkflag(x+9,y+13,1) && !ishookshottable((int)x+9,(int)y+13)) ) ||
				//down
				(_walkflag(x+12,y+12,1) && !ishookshottable((int)x+12,(int)y+12)) ) )
			{
			    dead=1;
			}
		    
		    
		}
		if ( dir == l_down ) 
		{
			if(get_bit(quest_rules, qr_OLDHOOKSHOTGRAB))
			{	//left						//down
				if( (combobuf[MAPCOMBO(x+6,y+7)].type==cHSGRAB) || (combobuf[MAPCOMBO(x+12,y+12)].type==cHSGRAB) )
				{
					hooked=true;
				}
			}
			

					//left						//down
			else if( ( (combobuf[MAPCOMBO(x+6,y+13)].type==cHSGRAB)) || (combobuf[MAPCOMBO(x+12,y+12)].type==cHSGRAB) )
			{
				hooked=true;
			}

			if(get_bit(quest_rules, qr_HOOKSHOTLAYERFIX))
			{
							//left
				hooked = hooked || (combobuf[MAPCOMBO2(0,x+6,y+13)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+6,y+13)].type==cHSGRAB) || 
					//down
				(combobuf[MAPCOMBO2(0,x+12,y+12)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+12,y+12)].type==cHSGRAB);
			}
			//left
			if(!hooked && ( ( ( _walkflag(x+6,y+13,1) && !ishookshottable((int)x+6,(int)y+13)) ) ||
				//down
				(_walkflag(x+12,y+12,1) && !ishookshottable((int)x+12,(int)y+12)) ) )
			{
				dead=1;
			}
		    
		    
		}
		if ( dir == r_up ) 
		{
		        if(get_bit(quest_rules, qr_OLDHOOKSHOTGRAB))
			{	//right						//up
			    if( (combobuf[MAPCOMBO(x+9,y+7)].type==cHSGRAB) || (combobuf[MAPCOMBO(x+2,y+7)].type==cHSGRAB) )
				{
					hooked=true;
				}
			}

					//right						//up
			else if( ( (combobuf[MAPCOMBO(x+9,y+13)].type==cHSGRAB)) || (combobuf[MAPCOMBO(x+2,y+7)].type==cHSGRAB) )
			{
				hooked=true;
			}

			if(get_bit(quest_rules, qr_HOOKSHOTLAYERFIX))			//right
			{
				hooked = hooked || (combobuf[MAPCOMBO2(0,x+9,y+13)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+9,y+13)].type==cHSGRAB ) || 
				//up
				(combobuf[MAPCOMBO2(0,x+2,y+7)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+2,y+7)].type==cHSGRAB);
			}
			//right
			if(!hooked &&  ( ( ( _walkflag(x+9,y+13,1) && !ishookshottable((int)x+9,(int)y+13)) ) ||
				//up
				(_walkflag(x+2,y+7,1) && !ishookshottable((int)x+2,(int)y+7)) ) )
			{
				dead=1;
			}
		}
		if ( dir == l_up ) 
		{
		        if(get_bit(quest_rules, qr_OLDHOOKSHOTGRAB))
			{	//left						//up
				if( (combobuf[MAPCOMBO(x+6,y+7)].type==cHSGRAB) || (combobuf[MAPCOMBO(x+2,y+7)].type==cHSGRAB) )
				{
					hooked=true;
				}
			}

					//left						//up
			else if( ( (combobuf[MAPCOMBO(x+6,y+13)].type==cHSGRAB)) || (combobuf[MAPCOMBO(x+2,y+7)].type==cHSGRAB) )
			{
				hooked=true;
			}

			if(get_bit(quest_rules, qr_HOOKSHOTLAYERFIX))			//left
			{
				hooked = hooked || (combobuf[MAPCOMBO2(0,x+6,y+13)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+6,y+13)].type==cHSGRAB) || 
				//up
				(combobuf[MAPCOMBO2(0,x+2,y+7)].type==cHSGRAB) || (combobuf[MAPCOMBO2(1,x+2,y+7)].type==cHSGRAB);
			}
							//left
			if(!hooked && ( ( ( _walkflag(x+6,y+13,1) && !ishookshottable((int)x+6,(int)y+13)) ) ||
				//up
				(_walkflag(x+2,y+7,1) && !ishookshottable((int)x+2,(int)y+7)) ) )
			{
				dead=1;
			}
		}
        }
        
        if(hooked==true)
        {
            misc=1;
            pull_link=true;
            step=0;
        }
        
        ++clk2;
        
        if(clk==0)                                            // delay a frame
        {
            ++clk;
            
            if(parentitem>-1)
            {
                sfx(itemsbuf[parentitem].usesound,pan(int(x)),true);
            }
            
            return false;
        }
        
        if(dead==1)
        {
            dead=-1;
            
            if(step > 0)
                step = -step;
                
            misc=1;
        }
        
        if(misc==1)                                           // returning
        {
            if((dir<left && abs(LinkY()-y)<9) || (dir >= left && abs(LinkX()-x)<9))
            {
                hookshot_used=false;
                
                if(pull_link)
                {
                    hs_fix=true;
                }
                
                pull_link=false;
                chainlinks.clear();
                CatchBrang();
                
                if(parentitem>-1)
                {
                    stop_sfx(itemsbuf[parentitem].usesound);
                }
                
                if(dragging!=-1)
                {
                    getdraggeditem(dragging);
                }
                
                return true;
            }
        }
        
        if(parentitem>-1)
        {
            sfx(itemsbuf[parentitem].usesound,pan(int(x)),true,false);
        }
        
        if(blocked())
        {
            //not on the return!! -DD
            if(dead != -1)
                dead=1;
        }
    }
    break;
    
    case wHSHandle:
        if(hookshot_used==false)
        {
            dead=0;
        }
        
        if(blocked())  //no hookshot handle area?
        {
            hookshot_used=false;
            dead=0;
        }
        
        break;
        
    case wPhantom:
        switch(type)
        {
        case pDINSFIREROCKET:
            if(y <= -200)
                dead = 1;
                
            break;
            
        case pDINSFIREROCKETRETURN:                                             //Din's Fire Rocket return
            if(y>=casty)
            {
                dead=1;
                castnext=true;
            }
            
            break;
            
        case pDINSFIREROCKETTRAIL:                                             //Din's Fire Rocket trail
            if(clk>=(((wpnsbuf[wDINSFIRES1A].frames) * (wpnsbuf[wDINSFIRES1A].speed))-1))
            {
                dead=0;
            }
            
            break;
            
        case pDINSFIREROCKETTRAILRETURN:                                             //Din's Fire Rocket return trail
            if(clk>=(((wpnsbuf[wDINSFIRES1B].frames) * (wpnsbuf[wDINSFIRES1B].speed))-1))
            {
                dead=0;
            }
            
            break;
            
        case pNAYRUSLOVEROCKETRETURN1:                                             //Nayru's Love Rocket return
            if(x>=castx)
            {
                dead=1;
                castnext=true;
            }
            
            break;
            
        case pNAYRUSLOVEROCKETTRAIL1:                                             //Nayru's Love Rocket trail
            if(clk>=(((wpnsbuf[wNAYRUSLOVES1A].frames) * (wpnsbuf[wNAYRUSLOVES1A].speed))-1))
            {
                dead=0;
            }
            
            break;
            
        case pNAYRUSLOVEROCKETTRAILRETURN1:                                             //Nayru's Love Rocket return trail
            if(clk>=(((wpnsbuf[wNAYRUSLOVES1B].frames) * (wpnsbuf[wNAYRUSLOVES1B].speed))-1))
            {
                dead=0;
            }
            
            break;
            
        case pNAYRUSLOVEROCKETRETURN2:                                             //Nayru's Love Rocket return
            if(x<=castx)
            {
                dead=0;
                castnext=true;
            }
            
            break;
            
        case pNAYRUSLOVEROCKETTRAIL2:                                             //Nayru's Love Rocket trail
            if(clk>=(((wpnsbuf[wNAYRUSLOVES2A].frames) * (wpnsbuf[wNAYRUSLOVES2A].speed))-1))
            {
                dead=0;
            }
            
            break;
            
        case pNAYRUSLOVEROCKETTRAILRETURN2:                                             //Nayru's Love Rocket return trail
            if(clk>=(((wpnsbuf[wNAYRUSLOVES2B].frames) * (wpnsbuf[wNAYRUSLOVES2B].speed))-1))
            {
                dead=0;
            }
            
            break;
            
        }
        
        if(blocked()) //not really sure this is needed
        {
            dead=1;
        }
        
        break;
        
    case wRefMagic:
    case wMagic:
    case ewMagic:
    {
        if((id==wMagic)&&(findentrance(x,y,mfWANDMAGIC,true))) dead=0;
        
        if((id==wRefMagic)&&(findentrance(x,y,mfREFMAGIC,true))) dead=0;
        
        if((id!=ewMagic)&&(findentrance(x,y,mfSTRIKE,true))) dead=0;
        
        if((id==wMagic && current_item(itype_book) &&
                itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_book)].flags&ITEM_FLAG1) && get_bit(quest_rules,qr_INSTABURNFLAGS))
        {
            findentrance(x,y,mfBCANDLE,true);
            findentrance(x,y,mfRCANDLE,true);
            findentrance(x,y,mfWANDFIRE,true);
        }
        
mirrors:
        int checkx=0, checky=0;
        
        switch(dir)
        {
        case up:
            checkx=x+7;
            checky=y+8;
            break;
            
        case down:
            checkx=x+7;
            checky=y;
            break;
            
        case left:
            checkx=x+8;
            checky=y+7;
            break;
            
        case right:
            checkx=x;
            checky=y+7;
            break;
        }
        
        if(ignorecombo!=(((int)checky&0xF0)+((int)checkx>>4)))
        {
            if(hitcombo(checkx,checky,cMIRROR))
            {
                weapon *w=new weapon(*this);
                
                if(id==ewMagic)
                {
                    Lwpns.add(w);
                    dead=0;
                }
                else
                {
                    w=this;
                }
                
                
                w->dir ^= 1;
                
                if(w->id != wWind)
                {
                    w->id = wRefMagic;
                    
                    if(w->dir&2)
                        w->flip ^= 1;
                    else
                        w->flip ^= 2;
                }
                
                w->ignoreLink=false;
                w->ignorecombo=(((int)checky&0xF0)+((int)checkx>>4));
                w->y=checky&0xF0;
                w->x=checkx&0xF0;
            }
            
            if(hitcombo(checkx,checky,cMIRRORSLASH))
            {
                weapon *w=new weapon(*this);
                
                if(id==ewMagic)
                {
                    Lwpns.add(w);
                    dead=0;
                }
                else
                {
                    w=this;
                }
                
                w->dir = 3-w->dir;
                
                if(w->id != wWind)
                {
                    w->id = wRefMagic;
                    
                    if((w->dir==1)||(w->dir==2))
                        w->flip ^= 3;
                }
                
                w->tile=w->o_tile;
                
                if(w->dir&2)
                {
                    if(w->frames>1)
                    {
                        w->tile+=w->frames;
                    }
                    else
                    {
                        ++w->tile;
                    }
                }
                
                w->ignoreLink=false;
                w->ignorecombo=(((int)checky&0xF0)+((int)checkx>>4));
                w->y=checky&0xF0;
                w->x=checkx&0xF0;
            }
            
            if(hitcombo(checkx,checky,cMIRRORBACKSLASH))
            {
                weapon *w=new weapon(*this);
                
                if(id==ewMagic)
                {
                    Lwpns.add(w);
                    dead=0;
                }
                else
                {
                    w=this;
                }
                
                w->dir ^= 2;
                
                if(w->id != wWind)
                {
                    w->id = wRefMagic;
                    
                    if(w->dir&1)
                        w->flip ^= 2;
                    else
                        w->flip ^= 1;
                }
                
                w->tile=w->o_tile;
                
                if(w->dir&2)
                {
                    if(w->frames>1)
                    {
                        w->tile+=w->frames;
                    }
                    else
                    {
                        ++w->tile;
                    }
                }
                
                w->ignoreLink=false;
                w->ignorecombo=(((int)checky&0xF0)+((int)checkx>>4));
                w->y=checky&0xF0;
                w->x=checkx&0xF0;
            }
            
            if(hitcombo(checkx,checky,cMAGICPRISM) && (id != wWind))
            {
                int newx, newy;
                newy=checky&0xF0;
                newx=checkx&0xF0;
                
                for(int tdir=0; tdir<4; tdir++)
                {
                    if(dir!=(tdir^1))
                    {
                        weapon *w=new weapon(*this);
                        w->dir=tdir;
                        w->x=newx;
                        w->y=newy;
                        w->z=z;
                        w->id=wRefMagic;
                        w->parentid=parentid;
                        w->parentitem=parentitem;
                        w->flip = 0;
                        w->ignoreLink = false;
                        w->hyofs = w->hxofs = 0;
                        w->ignorecombo=(((int)checky&0xF0)+((int)checkx>>4));
                        
                        //also set up the magic's correct animation -DD
                        switch(w->dir)
                        {
                        case down:
                            w->flip=2;
                            
                        case up:
                            w->tile = w->o_tile;
                            w->hyofs=2;
                            w->hysz=12;
                            break;
                            
                        case left:
                            w->flip=1;
                            
                        case right:
                            w->tile=w->o_tile+((w->frames>1)?w->frames:1);
                            w->hxofs=2;
                            w->hxsz=12;
                            break;
                        }
                        
                        Lwpns.add(w);
                    }
                }
                
                dead=0;
            }
            
            if(hitcombo(checkx,checky,cMAGICPRISM4) && (id != wWind))
            {
                int newx, newy;
                newy=checky&0xF0;
                newx=checkx&0xF0;
                
                for(int tdir=0; tdir<4; tdir++)
                {
                    weapon *w=new weapon(*this);
                    w->dir=tdir;
                    w->x=newx;
                    w->y=newy;
                    w->z=z;
                    w->id=wRefMagic;
                    w->parentid=parentid;
                    w->parentitem=parentitem;
                    w->flip = 0;
                    w->ignoreLink = false;
                    w->hyofs = w->hxofs = 0;
                    w->ignorecombo=(((int)checky&0xF0)+((int)checkx>>4));
                    
                    //also set up the magic's correct animation -DD
                    switch(w->dir)
                    {
                    case down:
                        w->flip=2;
                        
                    case up:
                        w->tile = w->o_tile;
                        w->hyofs=2;
                        w->hysz=12;
                        break;
                        
                    case left:
                        w->flip=1;
                        
                    case right:
                        w->tile=w->o_tile+((w->frames>1)?w->frames:1);
                        w->hxofs=2;
                        w->hxsz=12;
                        break;
                    }
                    
                    Lwpns.add(w);
                }
                
                dead=0;
            }
            
            if(blocked(0, 0))
            {
                dead=0;
            }
        }
    }
    break;
    
    // enemy weapons
    case ewFireball2:
        switch(misc)
        {
        case up:
            y-=.5;
            break;
            
        case down:
            y+=.5;
            break;
            
        case left:
            x-=.5;
            break;
            
        case right:
            x+=.5;
            break;
            
        case l_up:
            y-=.354;
            x-=.354;
            break;
            
        case r_up:
            y-=.354;
            x+=.354;
            break;
            
        case l_down:
            y+=.354;
            x-=.354;
            break;
            
        case r_down:
            y+=.354;
            x+=.354;
            break;
        }
        
        //fallthrough
    case wRefFireball:
    case ewFireball:
    {
        if((id==wRefFireball)&&(findentrance(x,y,mfREFFIREBALL,true))) dead=0;
        
        if((id==wRefFireball)&&(findentrance(x,y,mfSTRIKE,true))) dead=0;
        
        if(blocked())
        {
            dead=0;
        }
        
        if(clk<16)
        {
            ++clk;
            
            if(dead>0)
                --dead;
                
            return dead==0;
        }
        
        break;
    }
    
    case ewFlame:
    {
        if(clk==32)
        {
            step=0;
            misc = -1; // Don't drift diagonally anymore
            isLit=true;
            checkLightSources();
        }
        
        if(clk==126)
        {
            dead=1;
            
            if(get_bit(quest_rules,qr_TEMPCANDLELIGHT))
            {
                isLit=false;
                checkLightSources();
            }
        }
        
        if(blocked())
        {
            dead=1;
        }
        
        // Killed by script?
        if(dead==0 && get_bit(quest_rules,qr_TEMPCANDLELIGHT) && (Lwpns.idCount(wFire) + Ewpns.idCount(ewFlame))==1)
        {
            isLit=false;
            checkLightSources();
        }
        
        break;
    }
    
    case ewFireTrail:
    {
        if(clk==32)
        {
            step=0;  //should already be 0, but still...
            isLit=true;
            checkLightSources();
        }
        
        if(clk==640)
        {
            dead=1;
            
            if(get_bit(quest_rules,qr_TEMPCANDLELIGHT))
            {
                isLit=false;
                checkLightSources();
            }
        }
        
        if(blocked())
        {
            dead=1;
        }
        
        break;
    }
    
    case ewBrang:
    {
        if(clk==0)
        {
            misc2=(dir<left)?y:x;                               // save home position
            
            if(dummy_bool[0]==true)
            {
                seekLink();
            }
            //!ZoriaRPG Some brang stuff to mend. Sound. 
            if(get_bit(quest_rules,qr_MORESOUNDS))
            {
                //if (step!=0)
                sfx(WAV_BRANG, pan(int(x)), true);
                //else
                ;//stop_sfx(WAV_BRANG);
            }
        }
        
        ++clk2;
        
        if(clk2==45&&!dummy_bool[0])
        {
            misc=1;
            dir^=1;
        }
        
        if(dummy_bool[0])
        {
            step=5;
        }
        else
        {
            if(clk2>27 && clk2<61)
            {
                step=1;
            }
            else if(misc)
            {
                step=2;
            }
            else
            {
                step=3;
            }
        }
        
        bool killrang = false;
        
        if(misc==1)                                           // returning
        {
            if(dummy_bool[0]==true)
            {
                //no parent
                if(parentid < 0)
                    return true;
                    
                //find parent
                int index = -1;
                
                for(int i=0; i<guys.Count(); i++)
                    if(guys.spr(i)->getUID()==parentid)
                    {
                        index = i;
                        break;
                    }
                    
                //parent is not a guy
                if(index < 0)
                    return true;
                    
                seekEnemy(index);
                
                if((abs(x-GuyX(index))<7)&&(abs(y-GuyY(index))<7))
                {
                    if(get_bit(quest_rules,qr_MORESOUNDS) && !Lwpns.idCount(wBrang) && Ewpns.idCount(ewBrang)<=1)
                    {
                        stop_sfx(WAV_BRANG);
                    }
                    
                    return true;
                }
            }
            else
            {
                switch(dir)
                {
                case up:
                    if(y<misc2) killrang=true;
                    
                    break;
                    
                case down:
                    if(y>misc2) killrang=true;
                    
                    break;
                    
                case left:
                    if(x<misc2) killrang=true;
                    
                    break;
                    
                case right:
                    if(x>misc2) killrang=true;
                    
                    break;
                }
            }
        }
        else if(blocked())
        {
            //only obey block flags before the bounce
            dead=1;
        }
        
        //if the boomerang is not on its way home, it bounces
        if(dead==1 && misc != 1)
        {
            dead=-1;
            misc=1;
            dir^=1;
            clk2=zc_max(46,90-clk2);
        }
        
        //otherwise it disappears
        if(killrang || dead==1)
        {
            if(get_bit(quest_rules,qr_MORESOUNDS) && !Lwpns.idCount(wBrang) && Ewpns.idCount(ewBrang)<=1)
            {
                stop_sfx(WAV_BRANG);
            }
            
            dead = 1;
        }
    }
    }
    
    // move sprite, check clipping
    if(dead==-1 && clk>=0)
    {
        move(step);
        
        if(clip())
        {
            onhit(true);
        }
        else if(id==ewRock)
        {
            if(_walkflag(x,y,2) || _walkflag(x,y+8,2))
            {
                onhit(true);
            }
        }
    }
    else if(dead==-10) // Scripting hack thing related to weapon->DeadState
    {
        if(clip())
        {
            onhit(true);
        }
    }
    
    if(bounce)
    {
        switch(dir)
        {
        case up:
            x-=1;
            y+=2;
            break;
            
        case down:
            x+=1;
            y-=2;
            break;
            
        case left:
            x+=2;
            y-=1;
            break;
            
        case right:
            x-=2;
            y-=1;
            break;
        }
    }
    
    // update clocks
    ++clk;
    
    if(dead>0)
    {
        --dead;
    }
    
    return dead==0;
}

void weapon::onhit(bool clipped)
{
    onhit(clipped, 0, -1);
}

void weapon::onhit(bool clipped, int special, int linkdir)
{
    if((scriptcoldet&1) == 0)
    {
        // These won't hit anything, but they can still go too far offscreen...
        // Unless the compatibility rule is set.
        if(get_bit(quest_rules, qr_OFFSCREENWEAPONS) || !clipped)
            return;
        goto offscreenCheck;
    }
    
    if(special==2)                                            // hit Link's mirror shield
    {
        switch(id)
        {
        case ewFireball2:
        case ewFireball:
            id = wRefFireball;
            ignoreLink=true;
            goto reflect;
            
        case ewRock:
        case ewSword:
        case wRefBeam:
        case ewMagic:
        case wRefMagic:
            //otherwise he can get hit by the newly-created projectile if he's walking into it fast enough -DD
            ignoreLink=true;
            id = ((id==ewMagic || id==wRefMagic) ? wRefMagic : id==ewRock ? wRefRock : wRefBeam);
            goto reflect;
            
        case wScript1:
        case wScript2:
        case wScript3:
        case wScript4:
        case wScript5:
        case wScript6:
        case wScript7:
        case wScript8:
        case wScript9:
        case wScript10:
            // If this isn't set, the weapon may reflect repeatedly
            ignoreLink=true;
reflect:

            if(angular) switch(linkdir)
                {
                case up:
                    angle += (PI - angle) * 2.0;
                    break;
                    
                case down:
                    angle = -angle;
                    break;
                    
                case left:
                    angle += ((-PI/2) - angle) * 2.0;
                    break;
                    
                case right:
                    angle += ((PI/2) - angle) * 2.0;
                    break;
                    
                default:
                    angle += PI;
                    break;
                }
            else
            {
                dir ^= 1;
                
                if(dir&2)
                    flip ^= 1;
                else
                    flip ^= 2;
            }
            
            return;
        }
    }
    
    if(special>=1)                                            // hit Link's shield
    {
        switch(id)
        {
        case ewRock:
        case ewMagic:
        case ewArrow:
        case ewSword:
            bounce=true;
            dead=16;
            return;
            
        case ewBrang:
            if(misc==0)
            {
                clk2=256;
                misc=1;
                dir^=1;
            }
            
            return;
        }
    }
    
offscreenCheck:
    switch(id)
    {
    case wSword:
    case wWand:
    case wHammer:
        break;
        
    case ewBomb:
        step=0;
        break;
        
    case ewLitBomb:
        step=0;
        misc=50;
        clk=misc-3;
        hxofs=hyofs=-7;
        hxsz=hysz=30;
        break;
        
    case ewSBomb:
        step=0;
        break;
        
    case ewLitSBomb:
        step=0;
        misc=50;
        clk=misc-3;
        hxofs=hyofs=-16;
        hxsz=hysz=48;
        break;
        
    case wLitBomb:
        if(!clipped) dead=1;
        
    case wLitSBomb:
        if(!clipped) dead=1;
        
    case wWhistle:
    case wBomb:
    case wSBomb:
    case wBait:
    case wFire:
    case wHSHandle:
    case wPhantom:
        break;                                   // don't worry about clipping or hits with these
        
    case ewFireTrail:
        if(!clipped) dead=1;
        
        break;
        
    case ewFlame:
        if(!clipped) dead=1;
        
        break;
        
    case wRefBeam:
    case wBeam:
        dead=23;
        break;
        
    case wArrow:
        dead=4;
        break;                           //findentrance(x,y,mfARROW,true); break;
        
    case ewArrow:
        dead=clipped?4:1;
        break;
        
    case wCByrna:
    
        // byrna keeps going
        if(parentitem<0 || !(itemsbuf[parentitem].flags&ITEM_FLAG1))
            dead=0;
            
        break;
        
    case wWind:
        if(x>=240)
            dead=2;
            
        break;
        
    case wBrang:
        if(misc==0) //&& itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].flags&&ITEM_FLAG5 == false
        { //adding piercing here did not work. -Z
            clk2=256;
            int deadval=(itemsbuf[parentitem>-1 ? parentitem : current_item_id(itype_brang)].flags & ITEM_FLAG3)?-2:4;
            
            if(clipped)
            {
                dead=deadval;
            }
            else
            {
                if(deadval==-2)
                {
                    dead=deadval;
                }
                
                misc=1;
                /*
                  if (current_item(itype_brang,true)>1) {
                  if (dummy_bool[0]) {
                  add_grenade(x,y,z,current_item(itype_brang,true)>2);
                  dummy_bool[0]=false;
                  }
                  }
                  */
            }
        }
        
        break;
        
    case wHookshot:
        if(misc==0)
        {
            clk2=256;
            
            if(clipped)
                dead=4;
            else
                dead=1;
        }
        
        break;
        
    case ewBrang:
        if(misc==0)
        {
            clk2=256;
            dead=4;
        }
        
        break;
        
    case wRefMagic:
    case wMagic:
        dead=1; //remove the dead part to make the wand only die when clipped
        
        if(((id==wMagic && current_item(itype_book) &&
                (itemsbuf[current_item_id(itype_book)].flags&ITEM_FLAG1))) && Lwpns.idCount(wFire)<2)
        {
            Lwpns.add(new weapon(x,y,z,wFire,2,1*DAMAGE_MULTIPLIER,0,current_item_id(itype_book),-1));
            sfx(WAV_FIRE,pan(x));
        }
        
        break;
        
    case ewWind:
        if(clipped)
        {
            if(misc==999)                                       // in enemy wind
            {
                ewind_restart=true;
            }
            
            dead=1;
        }
        
        break;
        
    default:
        dead=1;
    }
}

// override hit detection to check for invicibility, etc
bool weapon::hit(sprite *s)
{
    if(!(scriptcoldet&1)) return false;
    
    if(id==ewBrang && misc)
        return false;
        
    return (dead!=-1&&dead!=-10) ? false : sprite::hit(s);
}

bool weapon::hit(int tx,int ty,int tz,int txsz2,int tysz2,int tzsz2)
{
    if(!(scriptcoldet&1)) return false;
    
    if(id==ewBrang && misc)
        return false;
        
    return (dead!=-1&&dead!=-10) ? false : sprite::hit(tx,ty,tz,txsz2,tysz2,tzsz2);
}

void weapon::update_weapon_frame(int change, int orig)
{
    if(extend > 2)
    {
        byte extra_rows=(tysz-1)*(((orig%TILES_PER_ROW)+(txsz*change))/TILES_PER_ROW);
        tile=orig+(txsz*change)+(extra_rows*TILES_PER_ROW);
    }
    else
        tile=orig+change;
}

void weapon::draw(BITMAP *dest)
{
    if(flash==1)
    {
        if(!BSZ)
        {
            cs = (id==wBeam || id==wRefBeam) ? 6 : o_cset&15;
            cs += frame&3;
        }
        else
        {
            if(id==wBeam || id==wRefBeam)
                cs = ((frame>>2)&1)+7;
            else
            {
                cs = o_cset&15;
                
                if(++csclk >= 12)
                    csclk = 0;
                    
                cs += csclk>>2;
            }
        }
    }
    
    if(flash>1)
    {
        if(++csclk >= (o_speed<<1))
            csclk = 0;
            
        cs = o_cset&15;
        
        if(csclk >= o_speed)
            cs = o_cset>>4;
    }
    
    if(frames)
    {
        if(id!=wBrang && id!=ewBrang)  // Brangs use clk2 for adjusting boomerang's flight range.
        {
            if(++clk2 >= o_speed)
            {
                clk2 = 0;
                
                if(frames>1 && ++aframe >= frames)
                {
                    aframe = 0;
                }
            }
        }
        else
        {
            if((clk2 % zc_max(1, o_speed))==0)
            {
                if(frames>1 && ++aframe >= frames)
                {
                    aframe = 0;
                }
            }
        }
        
        //tile = o_tile+aframe;
        update_weapon_frame(aframe,o_tile);
    }
    
    // do special case stuff
    switch(id)
    {
    case wSword:
    case wHammer:
        if(get_bit(quest_rules,qr_LINKFLICKER)&&((getClock()||LinkHClk())&&(frame&1)) ||
                Link.getDontDraw() || tmpscr->flags3&fINVISLINK)
            return;
            
    case wBeam:
    case wRefBeam:
    {
        if(dead==-1) break;
        
        // draw the beam shards
        int ofs=23-dead;
        int f = frame&3;
        int type2 = o_type;
        //tile = o_tile+((frames?frames:1)*2);
        update_weapon_frame(((frames?frames:1)*2),o_tile);
        
        if(type2)
            cs = o_cset>>4;
            
        if(type2==3 && (f&2))
            ++tile;
            
        if(!type2 || f==0 || (type2>1 && f==3)) overtile16(dest,tile,x-2-ofs,y+playing_field_offset-2-ofs-(z+zofs),cs,0);
        
        if(!type2 || f==2 || (type2>1 && f==1)) overtile16(dest,tile,x+2+ofs,y+playing_field_offset-2-ofs-(z+zofs),cs,1);
        
        if(!type2 || f==1 || (type2>1 && f==2)) overtile16(dest,tile,x-2-ofs,y+playing_field_offset+2+ofs-(z+zofs),cs,2);
        
        if(!type2 || f==3 || (type2>1 && f==0)) overtile16(dest,tile,x+2+ofs,y+playing_field_offset+2+ofs-(z+zofs),cs,3);
    }
    
    return;                                               // don't draw sword
    
    case wBomb:
    case wSBomb:
    case ewBomb:
    case ewSBomb:
    {
        if(!misc || clk<misc-2) break;
        
        // draw the explosion
        int id2=0;
        int boomframes = 0;
        
        switch(id)
        {
        case wBomb:
        {
            id2=wBOOM;
            
            if(parentitem>-1)
            {
                id2=itemsbuf[parentitem].wpn2; //This sets the explosion sprite, but because it is linked to itemdata
						//it may not work with script generated explosions. -Z
		    //Perhaps it would be better to add a special case to createlweapon and createeweapon to 
		    //use a usesprite value with wpns.add
            }
            
            break;
        }
        
        case wSBomb:
        {
            id2=wSBOOM;
            
            if(parentitem>-1)
            {
                id2=itemsbuf[parentitem].wpn2;
            }
            
            break;
        }
        
        case ewBomb:
            id2=ewBOOM;
            break;
            
        case ewSBomb:
            id2=ewSBOOM;
            break;
        }
        
        tile = wpnsbuf[id2].tile;
        cs = wpnsbuf[id2].csets&15;
        boomframes = wpnsbuf[id2].frames;
        
        if(boomframes != 0)
        {
            //equally divide up the explosion time among the frames
            int perframe = (boomframes >= 34 ? 1 : (boomframes + 34)/boomframes);
            
            if(clk > misc)
                tile += (clk-misc)/perframe;
                
            //update_weapon_frame((clk-misc)/perframe,tile);
        }
        else if(clk>misc+22)
        {
            ++tile;
            //update_weapon_frame(1,tile);
        }
        
        overtile16(dest,tile,x+((clk&1)?7:-7),y+yofs-13-(z+zofs),cs,0);
        overtile16(dest,tile,x,y+yofs-(z+zofs),cs,0);
        overtile16(dest,tile,x+((clk&1)?-14:14),y+yofs-(z+zofs),cs,0);
        overtile16(dest,tile,x+((clk&1)?-7:7),y+yofs+14-(z+zofs),cs,0);
        
        if(id==wSBomb||id==ewSBomb)
        {
            overtile16(dest,tile,x+((clk&1)?7:-7),y+yofs-27-(z+zofs),cs,0);
            overtile16(dest,tile,x+((clk&1)?-21:21),y+yofs-13-(z+zofs),cs,0);
            overtile16(dest,tile,x+((clk&1)?-28:28),y+yofs-(z+zofs),cs,0);
            overtile16(dest,tile,x+((clk&1)?21:-21),y+yofs+14-(z+zofs),cs,0);
            overtile16(dest,tile,x+((clk&1)?-7:7),y+yofs+28-(z+zofs),cs,0);
        }
        else
        {
            ;
        }
        
        if(get_debug() && key[KEY_O])
            rectfill(dest,x+hxofs,y+hyofs+yofs-(z+zofs),
                     x+hxofs+hxsz-1,y+hyofs+hysz-1+yofs,vc(id));
                     
        return;                                               // don't draw bomb
    }
    
    case wArrow:
    case ewArrow:
        if(dead>0 && !bounce)
        {
            cs=7;
            tile=54;
            flip=0;
        }
        
        break;
        
    case ewFireTrail:
    case ewFlame:
    case wFire:
    
        //if no animation, flip tile
        if(frames==0)
            flip = o_flip & (clk>>2);
            
        break;
        
    case ewBrang:
    case wBrang:
        cs = o_cset&15;
        
        if(parentitem<0 || !(itemsbuf[parentitem].flags & ITEM_FLAG1))
        {
            tile = o_tile;
            
            if(BSZ)
                flip = bszboomflip[(clk>>2)&3];
            else
            {
                //tile = boomframe[clk&0xE] + o_tile;
                update_weapon_frame(boomframe[clk&0xE],o_tile);
                flip = boomframe[(clk&0xE)+1];
            }
            
            if(parentitem>=0 && itemsbuf[parentitem].flags & ITEM_FLAG2)
            {
                update_weapon_frame((BSZ?1:4)*dir,tile);
            }
        }
        else
        {
            if(parentitem>=0 && itemsbuf[parentitem].flags & ITEM_FLAG2)
            {
                update_weapon_frame(zc_max(frames,1)*dir,tile);
            }
        }
        
        if(dead>0)
        {
            if(parentitem>=0 && itemsbuf[parentitem].flags & ITEM_FLAG1)
            {
                tile=o_tile+(frames*(itemsbuf[parentitem].flags & ITEM_FLAG2)?8:1);
            }
            else
            {
                cs=7;
                tile=54;
                flip=0;
            }
        }
        
        break;
        
    case wHookshot:
        break;
        
    case wWind:
        if(frames==0)
            flip ^= o_flip;
            
        if((dead!=-1) && !BSZ)
            tile = temp1;//wpnsbuf[wFIRE].tile;
            
        break;
        
    case ewWind:
        /*
          if(wpnsbuf[wid].frames==0)
          flip ^= (wpnsbuf[wid].misc>>2)&3;
          */
        break;
        
    case wPhantom:
        switch(type)
        {
        case pNAYRUSLOVEROCKET1:
        case pNAYRUSLOVEROCKETRETURN1:
        case pNAYRUSLOVEROCKETTRAIL1:
        case pNAYRUSLOVEROCKETTRAILRETURN1:
        case pNAYRUSLOVEROCKET2:
        case pNAYRUSLOVEROCKETRETURN2:
        case pNAYRUSLOVEROCKETTRAIL2:
        case pNAYRUSLOVEROCKETTRAILRETURN2:
            if(parentitem>=0 && (itemsbuf[parentitem].flags & ITEM_FLAG1 ? 1 : 0)&&!(frame&1))
            {
                return;
            }
            
            break;
        }
        
        break;
    }
    
    // draw it
    sprite::draw(dest);
}

void putweapon(BITMAP *dest,int x,int y,int weapon_id, int type, int dir, int &aclk, int &aframe, int parentid)
{
    weapon temp((fix)x,(fix)y,(fix)0,weapon_id,type,0,dir,-1,parentid,true);
    temp.ignorecombo=((dir==up?y+8:y)&0xF0)+((dir==left?x+8:x)>>4); // Lens hints can sometimes create real weapons without this
    temp.ignoreLink=true;
    temp.yofs=0;
    temp.clk2=aclk;
    temp.aframe=aframe;
    temp.animate(0);
    temp.draw(dest);
    aclk=temp.clk2;
    aframe=temp.aframe;
}

/*** end of weapons.cpp ***/


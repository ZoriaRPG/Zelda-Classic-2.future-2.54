//--------------------------------------------------------
//  Zelda Classic
//  by Jeremy Craner, 1999-2000
//
//  zelda.cc
//
//  Main code for Zelda Classic. Originally written in
//  SPHINX C--, now rewritten in DJGPP with Allegro.
//
//--------------------------------------------------------

#include "precompiled.h" //always first

#include <stdio.h>
#include "zc_alleg.h"
#include "zdefs.h"
#include "zelda.h"
#include "items.h"
#include "pal.h"

extern int dlevel;
extern void flushItemCache();
extern zinitdata zinit;
extern void Z_eventlog(char *format,...);
extern void ringcolor(bool forceDefault);

// Debug variables: these log certain operations on gamedata when active.
// Should help me debug those item bugs.

// #define DEBUG_GD_ITEMS
// #define DEBUG_GD_COUNTERS
//#define DEBUG_GD_HCP

void gamedata::Clear()
{
    isclearing=true;
    std::fill(_name, _name+9, 0);
    _quest=0;
    _deaths=0;
    _cheat=0;
    std::fill(item, item+MAXITEMS, false);
    std::fill(items_off, items_off+MAXITEMS, 0);
    std::fill(_maxcounter, _maxcounter+32, 0);
    std::fill(_counter, _counter+32, 0);
    std::fill(_dcounter, _dcounter+32, 0);
    std::fill(version, version+9, 0);
    std::fill(title, title+65, 0);
    _hasplayed=false;
    _time=0;
    _timevalid=false;
	_throttle=false;
    std::fill(lvlitems, lvlitems+MAXLEVELS, 0);
    std::fill(lvlkeys, lvlkeys+MAXLEVELS, 0);
    _continue_scrn=0;
    _continue_dmap=0;
    std::fill(_generic, _generic+256, 0);
    std::fill(visited, visited+MAXDMAPS, 0);
    std::fill(bmaps, bmaps+MAXDMAPS*64, 0);
    std::fill(maps, maps+MAXMAPS2*MAPSCRSNORMAL, 0);
    std::fill(guys, guys+MAXMAPS2*MAPSCRSNORMAL, 0);
    std::fill(qstpath, qstpath+2048, 0);
    std::fill(icon, icon+128, 0);
    std::fill(pal, pal+48, 0);
    
    for(int i=0; i<MAXDMAPS*MAPSCRSNORMAL; i++) std::fill(screen_d[i], screen_d[i]+8, 0);
    
    std::fill(global_d, global_d+256, 0);
    globalRAM.clear();
    awpn=0;
    bwpn=0;
    isclearing=false;
}

void gamedata::Copy(const gamedata& g)
{
    for(byte i = 0; i < 9; i++)
        _name[i] = g._name[i];
        
    _quest = g._quest;
    _deaths = g._deaths;
    _cheat = g._cheat;
    
    for(word i = 0; i < MAXITEMS; i++)
    {
        item[i] = g.item[i];
        items_off[i] = g.items_off[i];
    }
    
    for(byte i = 0; i < 32; i++)
    {
        _maxcounter[i] = g._maxcounter[i];
        _counter[i] = g._counter[i];
        _dcounter[i] = g._dcounter[i];
    }
    
    for(byte i = 0; i < 9; i++)
        version[i] = g.version[i];
        
    for(byte i = 0; i < 65; i++)
        title[i] = g.title[i];
        
    _hasplayed = g._hasplayed;
    _time = g._time;
    _timevalid = g._timevalid;
    _throttle = g._throttle;
    
    for(word i = 0; i < MAXLEVELS; i++)
    {
        lvlitems[i] = g.lvlitems[i];
        lvlkeys[i] = g.lvlkeys[i];
    }
    
    _continue_scrn = g._continue_scrn;
    _continue_dmap = g._continue_dmap;
    
    for(word i = 0; i < 256; i++)
        _generic[i] = g._generic[i];
        
    for(word i = 0; i < MAXDMAPS; i++)
        visited[i] = g.visited[i];
        
    for(word i = 0; i < MAXDMAPS*64; i++)
        bmaps[i] = g.bmaps[i];
        
    for(dword i = 0; i < MAXMAPS2*MAPSCRSNORMAL; i++)
    {
        maps[i] = g.maps[i];
        guys[i] = g.guys[i];
    }
    
    for(word i = 0; i < 2048; i++)
        qstpath[i] = g.qstpath[i];
        
    for(byte i = 0; i < 128; i++)
        icon[i] = g.icon[i];
        
    for(byte i = 0; i < 48; i++)
        pal[i] = g.pal[i];
        
    for(dword i = 0; i < MAXDMAPS*MAPSCRSNORMAL; i++)
        for(byte j = 0; j < 8; j++)
            screen_d[i][j] = g.screen_d[i][j];
            
    for(word i = 0; i < 256; i++)
        global_d[i] = g.global_d[i];
        
    awpn = g.awpn;
    bwpn = g.bwpn;
}

char *gamedata::get_name()
{
    return _name;
}
void gamedata::set_name(char *n)
{
    strncpy(_name, n, 8);
    _name[8]='\0';
    return;
}

byte gamedata::get_quest()
{
    return _quest;
}
void gamedata::set_quest(byte q)
{
    _quest=q;
    return;
}
void gamedata::change_quest(short q)
{
    _quest+=q;
    return;
}

word gamedata::get_counter(byte c)
{
    if(c>=32)  // Sanity check
        return 0;
        
    return _counter[c];
}

void gamedata::set_counter(word change, byte c)
{
#ifdef DEBUG_GD_COUNTERS
    al_trace("Changing counter %i from %i to %i\n", c, _counter[c], change);
#endif
    
    if(c>=32)  // Sanity check
        return;
        
    if(game!=NULL)
    {
        int ringID=current_item_id(itype_ring, true);
        _counter[c]=zc_max(change, 0);
        
        // ringcolor is very slow, so make sure the ring has actually changed
        if(ringID!=current_item_id(itype_ring, true))
            ringcolor(false);
    }
    else
        _counter[c]=zc_max(change, 0);
        
    return;
}

void gamedata::change_counter(short change, byte c)
{
#ifdef DEBUG_GD_COUNTERS
    al_trace("Changing counter %i from %i by %i\n", c, _counter[c], change);
#endif
    
    if(c>=32)  // Sanity check
        return;
        
    if(game!=NULL)
    {
        int ringID=current_item_id(itype_ring, true);
        _counter[c]=vbound(_counter[c]+change, 0, _maxcounter[c]);
        
        if(ringID!=current_item_id(itype_ring, true))
            ringcolor(false);
    }
    else
        _counter[c]=vbound(_counter[c]+change, 0, _maxcounter[c]);
        
    return;
}

word gamedata::get_maxcounter(byte c)
{
    if(c>=32)  // Sanity check
        return 0;
        
    return _maxcounter[c];
}

void gamedata::set_maxcounter(word change, byte c)
{
#ifdef DEBUG_GD_COUNTERS

    if(c==0) al_trace("Changing max counter %i from %i to %i\n", c, _maxcounter[c], change);
    
#endif
    
    if(c==2)
    {
        set_maxbombs(change);
        return;
    }
    
    if(c>=32)  // Sanity check
        return;
        
    _maxcounter[c]=change;
    return;
}

void gamedata::change_maxcounter(short change, byte c)
{
#ifdef DEBUG_GD_COUNTERS
    al_trace("Changing max counter %i from %i by +%i\n", c, _maxcounter[c], change);
#endif
    
    if(c==2)
    {
        change_maxbombs(change);
        return;
    }
    
    if(c>=32)  // Sanity check
        return;
        
    _maxcounter[c]=zc_max(0, _maxcounter[c]+change);
    return;
}

short gamedata::get_dcounter(byte c)
{
    if(c>=32)  // Sanity check
        return 0;
        
    return _dcounter[c];
}

void gamedata::set_dcounter(short change, byte c)
{
#ifdef DEBUG_GD_COUNTERS

    if(c==0)
        al_trace("Changing D counter %i from %i to %i\n", c, _dcounter[c], change);
        
#endif
        
    if(c>=32)  // Sanity check
        return;
        
    if(game!=NULL)
    {
        int ringID=current_item_id(itype_ring, true);
        _dcounter[c]=change;
        
        if(ringID!=current_item_id(itype_ring, true))
            ringcolor(false);
    }
    else
        _dcounter[c]=change;
        
    return;
}

void gamedata::change_dcounter(short change, byte c)
{
#ifdef DEBUG_GD_COUNTERS

    if(c==0) al_trace("Changing D counter %i from %i by %i\n", c, _dcounter[c], change);
    
#endif
    
    if(c>=32)  // Sanity check
        return;
        
    if(game!=NULL)
    {
        int ringID=current_item_id(itype_ring, true);
        _dcounter[c]+=change;
        
        if(ringID!=current_item_id(itype_ring, true))
            ringcolor(false);
    }
    else
        _dcounter[c]+=change;
        
    return;
}

short gamedata::get_generic(byte c)
{
    return _generic[c];
}

void gamedata::set_generic(byte change, byte c)
{
    _generic[c]=change;
    return;
}

void gamedata::change_generic(short change, byte c)
{
    _generic[c]+=change;
    return;
}

word gamedata::get_life()
{
    return get_counter(0);
}
void gamedata::set_life(word l)
{
    if(l <= 0) l = 0;
    
    set_counter(l, 0);
    return;
}
void gamedata::change_life(short l)
{
    change_counter(l, 0);
    
    if(_dcounter[0] <= 0) _dcounter[0] = 0;
    
    return;
}

word gamedata::get_maxlife()
{
    return get_maxcounter(0);
}
void gamedata::set_maxlife(word m)
{
    set_maxcounter(m, 0);
    return;
}
void gamedata::change_maxlife(short m)
{
    change_maxcounter(m, 0);
    return;
}

short gamedata::get_drupy()
{
    return get_dcounter(1);
}
void gamedata::set_drupy(short d)
{
    set_dcounter(d, 1);
    return;
}
void gamedata::change_drupy(short d)
{
    change_dcounter(d, 1);
    return;
}

word gamedata::get_rupies()
{
    return get_counter(1);
}
word gamedata::get_spendable_rupies()
{
    if(get_bit(quest_rules, qr_SHOPCHEAT) || get_dcounter(1)>=0)
        return get_counter(1);
    else
        return get_counter(1)+get_dcounter(1);
}
void gamedata::set_rupies(word r)
{
    set_counter(r, 1);
    return;
}
void gamedata::change_rupies(short r)
{
    change_counter(r, 1);
    return;
}

word gamedata::get_maxarrows()
{
    return get_maxcounter(3);
}
void gamedata::set_maxarrows(word a)
{
    set_maxcounter(a, 3);
}
void gamedata::change_maxarrows(short a)
{
    change_maxcounter(a, 3);
    return;
}

word gamedata::get_arrows()
{
    return get_counter(3);
}
void gamedata::set_arrows(word a)
{
    set_counter(a, 3);
}
void gamedata::change_arrows(short a)
{
    change_counter(a, 3);
    return;
}

word gamedata::get_deaths()
{
    return _deaths;
}
void gamedata::set_deaths(word d)
{
    _deaths=d;
    return;
}
void gamedata::change_deaths(short d)
{
    _deaths+=d;
    return;
}

word gamedata::get_keys()
{
    return get_counter(5);
}
void gamedata::set_keys(word k)
{
    set_counter(k, 5);
    return;
}
void gamedata::change_keys(short k)
{
    change_counter(k, 5);
    return;
}

word gamedata::get_bombs()
{
    return get_counter(2);
}
void gamedata::set_bombs(word k)
{
    set_counter(k, 2);
    return;
}
void gamedata::change_bombs(short k)
{
    change_counter(k, 2);
    return;
}

word gamedata::get_maxbombs()
{
    return get_maxcounter(2);
}
void gamedata::set_maxbombs(word b, bool setSuperBombs)
{
    _maxcounter[2]=b;
    int div = zinit.bomb_ratio;
    
    if(div != 0 && setSuperBombs)
        set_maxcounter(b/div,6);
        
    return;
}
void gamedata::change_maxbombs(short b)
{
    _maxcounter[2]+=b;
    int div = zinit.bomb_ratio;
    
    if(div != 0)
        change_maxcounter(b/div,6);
        
    return;
}

word gamedata::get_sbombs()
{
    return get_counter(6);
}
void gamedata::set_sbombs(word k)
{
    set_counter(k, 6);
    return;
}
void gamedata::change_sbombs(short k)
{
    change_counter(k, 6);
    return;
}

word gamedata::get_wlevel()
{
    return get_generic(3);
}
void gamedata::set_wlevel(word l)
{
    set_generic(l, 3);
    return;
}
void gamedata::change_wlevel(short l)
{
    change_generic(l, 3);
    return;
}

byte gamedata::get_cheat()
{
    return _cheat;
}
void gamedata::set_cheat(byte c)
{
    _cheat=c;
    return;
}
void gamedata::change_cheat(short c)
{
    _cheat+=c;
    return;
}

byte gamedata::get_hasplayed()
{
    return _hasplayed;
}
void gamedata::set_hasplayed(byte p)
{
    _hasplayed=p;
    return;
}
void gamedata::change_hasplayed(short p)
{
    _hasplayed+=p;
    return;
}

dword gamedata::get_time()
{
    return _time;
}
void gamedata::set_time(dword t)
{
    _time=t;
    return;
}
void gamedata::change_time(long long t)
{
    _time+=t;
    return;
}

byte gamedata::get_timevalid()
{
    return _timevalid;
}
void gamedata::set_timevalid(byte t)
{
    _timevalid=t;
    return;
}
void gamedata::change_timevalid(short t)
{
    _timevalid+=t;
    return;
}

byte gamedata::get_throttle()
{
    return _throttle;
}
void gamedata::set_throttle(byte t)
{
    _throttle=t;
    return;
}
void gamedata::change_throttle(short t)
{
    _throttle+=t;
    return;
}

byte gamedata::get_HCpieces()
{
    return get_generic(0);
}
void gamedata::set_HCpieces(byte p)
{
#ifdef DEBUG_GD_HCP
    al_trace("Setting HCP to %i\n",p);
#endif
    
    set_generic(p, 0);
    return;
}
void gamedata::change_HCpieces(short p)
{
#ifdef DEBUG_GD_HCP
    al_trace("Changing HCP by %d to %d\n",p, get_generic(0));
#endif
    change_generic(p, 0);
    return;
}

byte gamedata::get_continue_scrn()
{
    return _continue_scrn;
}
void gamedata::set_continue_scrn(byte s)
{
    if(!isclearing && _continue_scrn != s) Z_eventlog("Continue screen set to %x\n", s);
    
    _continue_scrn=s;
    return;
}
void gamedata::change_continue_scrn(short s)
{
    if(!isclearing && s!=0) Z_eventlog("Continue screen set to %x\n", _continue_scrn+s);
    
    _continue_scrn+=s;
    return;
}

word gamedata::get_continue_dmap()
{
    return _continue_dmap;
}
void gamedata::set_continue_dmap(word d)
{
    if(!isclearing && _continue_dmap!=d) Z_eventlog("Continue DMap set to %d\n", d);
    
    _continue_dmap=d;
    return;
}
void gamedata::change_continue_dmap(short d)
{
    if(!isclearing && d!=0) Z_eventlog("Continue DMap set to %d\n", _continue_dmap+d);
    
    _continue_dmap+=d;
    return;
}


word gamedata::get_maxmagic()
{
    return get_maxcounter(4);
}
void gamedata::set_maxmagic(word m)
{
    set_maxcounter(m, 4);
    return;
}
void gamedata::change_maxmagic(short m)
{
    change_maxcounter(m, 4);
    return;
}

word gamedata::get_magic()
{
    return get_counter(4);
}
void gamedata::set_magic(word m)
{
    set_counter(m, 4);
    return;
}
void gamedata::change_magic(short m)
{
    change_counter(m, 4);
    return;
}

short gamedata::get_dmagic()
{
    return get_dcounter(4);
}
void gamedata::set_dmagic(short d)
{
    set_dcounter(d, 4);
    return;
}
void gamedata::change_dmagic(short d)
{
    change_dcounter(d, 4);
    return;
}

byte gamedata::get_magicdrainrate()
{
    return get_generic(1);
}
void gamedata::set_magicdrainrate(byte r)
{
    set_generic(r, 1);
    return;
}
void gamedata::change_magicdrainrate(short r)
{
    change_generic((char)r, 1);
    return;
}

byte gamedata::get_canslash()
{
    return get_generic(2);
}
void gamedata::set_canslash(byte s)
{
    set_generic(s, 2);
    return;
}
void gamedata::change_canslash(short s)
{
    change_generic(s, 2);
    return;
}

byte gamedata::get_lkeys()
{
    return lvlkeys[dlevel];
}

/*bool gamedata::get_item(int id)
{
return item[id];
}*/

byte gamedata::get_hcp_per_hc()
{
    return get_generic(4);
}

void gamedata::set_hcp_per_hc(byte val)
{
    set_generic(val, 4);
}

byte gamedata::get_cont_hearts()
{
    return get_generic(5);
}

void gamedata::set_cont_hearts(byte val)
{
    set_generic(val, 5);
}

bool gamedata::get_cont_percent()
{
    return get_generic(6) != 0;
}

void gamedata::set_cont_percent(bool ispercent)
{
    set_generic(ispercent ? 1 : 0, 6);
}
void gamedata::set_item(int id, bool value)
{
    set_item_no_flush(id, value);
    flushItemCache();
}

/*
void gamedata::set_item_off(int id, bool value)
{
    items_off[id] = value;
    flushItemCache();
}
*/

void gamedata::set_item_no_flush(int id, bool value)
{
    if(!isclearing && !(value == item[id]))
        Z_eventlog("%sed item %i: %s\n", value ? "Gain" : "Remov", id, item_string[id]);
        
    item[id]=value;
}

/*** end of gamedata.cpp ***/


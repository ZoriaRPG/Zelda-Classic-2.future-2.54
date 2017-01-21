directItem
directItemA
directItemB
//these are if Link is *using* an item. 

<Link->Eaten

//link.h
 inlikelike; // 1 = Like Like. 2 = Taking damage while trapped
 
    int getEaten();
    void setEaten(int i);
    
    void stopCaneOfByrna();
    
    void red_shift(); //is this link death>
    
    //LINK.CPP
    
    int link_animation_speed = 1; //lower is faster animation
    
    //void LinkClass::linkstep() { lstep = lstep<(BSZ?27:11) ? lstep+1 : 0; }
void LinkClass::linkstep()
{
    lstep = lstep<((zinit.linkanimationstyle==las_bszelda)?27:11) ? lstep+1 : 0;
}


stomping=false;
didstuff, //played the whistle? used the blue candle?
 reset_swordcharge();
  blowcnt,  //number of times whistle blown on this screen.
void checktouchblk();
bool edge_of_dmap(int side);
 void getTriforce(int id);
 void ganon_intro();
    void saved_Zelda();
 virtual void drawshadow(BITMAP* dest, bool translucent);
   int  getLStep();
    int  getCharging();
    void setCharging(int new_charging);
    bool isCharged();
    int  getAttackClk();
    void  setAttackClk(int new_clk);
    int  getSwordClk();
    int  getItemClk();
    void  setSwordClk(int newclk);
    void  setItemClk(int newclk);
    fix  getModifiedX();
    fix  getModifiedY();
    int  getDir();
    void setDir(int new_dir);
    int  getHitDir();
    void setHitDir(int new_dir);
    int  getClk();
    int  getPushing();
    bool getClock();
    void setClock(bool state)
    void setHClk(int newhclk);
    int getHClk();
    void setNayrusLoveShieldClk(int newclk);
    int getNayrusLoveShieldClk();
    int getHoverClk();
    int getHoldClk();
    void do_lens();
int touchcombo(int x,int y);

//These have handlers, but no ZASM?
void LinkClass::setNayrusLoveShieldClk(int newclk)
{
    NayrusLoveShieldClk=newclk;
    
    if(decorations.idCount(dNAYRUSLOVESHIELD)==0)
    {
        decoration *dec;
        decorations.add(new dNayrusLoveShield(LinkX(), LinkY(), dNAYRUSLOVESHIELD, 0));
        decorations.spr(decorations.Count()-1)->misc=0;
        decorations.add(new dNayrusLoveShield(LinkX(), LinkY(), dNAYRUSLOVESHIELD, 0));
        dec=(decoration *)decorations.spr(decorations.Count()-1);
        decorations.spr(decorations.Count()-1)->misc=1;
    }
}

int LinkClass::getNayrusLoveShieldClk()
{
    return NayrusLoveShieldClk;
}

int LinkClass::getHoverClk()
{
    return hoverclk;
}

int LinkClass::getHoldClk()
{
    return holdclk;
}

int  LinkClass::getLStep()
{
    return lstep;
}
int  LinkClass::getCharging()
{
    return charging;
}
bool LinkClass::isCharged()
{
    return spins>0;
}
int  LinkClass::getAttackClk()
{
    return attackclk;
}
void  LinkClass::setAttackClk(int new_clk)
{
    attackclk=new_clk;
}
void LinkClass::setCharging(int new_charging)
{
    charging=new_charging;
}
int  LinkClass::getSwordClk()
{
    return swordclk;
}
int  LinkClass::getItemClk()
{
    return itemclk;
}
void LinkClass::setSwordClk(int newclk)
{
    swordclk=newclk;
}
void LinkClass::setItemClk(int newclk)
{
    itemclk=newclk;
}


int  LinkClass::getClk()
{
    return clk;
}
int  LinkClass::getPushing()
{
    return pushing;
}
void LinkClass::Catch()
{
    if(!inwallm && (action==none || action==walking))
    {
        action=attacking;
        attackclk=0;
        attack=wCatching;
    }
}

bool LinkClass::getClock()
{
    return superman;
}
void LinkClass::setClock(bool state)
{
    superman=state;
}

hoverclk

 linktile(&tile, &flip, &extend, is_moving()?ls_swim:ls_float, dir, zinit.linkanimationstyle);
tile += anim_3_4(lstep,7)*(extend==2?2:1);

item_tile_mod(shieldModify); //LTm


hitshield=true;//ifa weapon hits links shield

hclk //determines if link was hit. inv frames

inwallm //in a wallmaster]]
NayrusLoveShieldClk
heart_beep //bool? determines if the beep playsa
heart_beep_timer
 cont_sfx(WAV_ER); //hardcoded sfx


sfx(WAV_OUCH,pan(int(x))); // we need to change this, to be able to play sound 0, or disable ita

paymagiccost(itemid); //Modify this with an extra version that counts by 30 frames

void do_lens()



void do_lens()
{
    int itemid = lensid >= 0 ? lensid : directWpn>-1 ? directWpn : current_item_id(itype_lens);
    
    if(itemid<0)
        return;
        
    if(isWpnPressed(itype_lens) && !LinkItemClk() && !lensclk && checkmagiccost(itemid))
    {
        if(lensid<0)
        {
            lensid=itemid;
            
            if(get_bit(quest_rules,qr_MORESOUNDS)) sfx(itemsbuf[itemid].usesound);
        }
        
        paymagiccost(itemid);
        
        if(dowpn>=0 && itemsbuf[dowpn].script != 0 && !did_scriptl)
        {
            ZScriptVersion::RunScript(SCRIPT_ITEM, itemsbuf[dowpn].script, dowpn & 0xFFF);
            did_scriptl=true;
        }
        
        lensclk = 12;
    }
    else
    {
        did_scriptl=false;
        
        if(lensid>-1 && !(isWpnPressed(itype_lens) && !LinkItemClk() && checkmagiccost(itemid)))
        {
            lensid=-1;
            lensclk = 0;
            
            if(get_bit(quest_rules,qr_MORESOUNDS)) sfx(WAV_ZN1LENSOFF);
        }
    }
}

autostep
   pushing=push+1;
is_on_conveyor
slowcharging ^ slowcombo
can_deploy_ladder()
void LinkClass::exitcave()
 ringcolor(false);

  show_subscreen_life=true;
    show_subscreen_numbers=true;

int LinkClass::lookahead(int destscr, int d2)                       // Helper for scrollscr that gets next combo on next screen.
{
    // Can use destscr for scrolling warps,
    // but assumes currmap is correct.
	
	int LinkClass::lookaheadflag(int destscr, int d2)
	
	}

// Used to find out if an item family is attached to one of the buttons currently pressed.
bool isWpnPressed(int wpn)
{
    if((wpn==getItemFamily(itemsbuf,Bwpn&0xFFF)) && DrunkcBbtn()) return true;
    
    if((wpn==getItemFamily(itemsbuf,Awpn&0xFFF)) && DrunkcAbtn()) return true;
    
    return false;
}

// Used for the 'Pickup Hearts' item pickup condition.
bool canget(int id)
{
    return id>=0 && (game->get_maxlife()>=(itemsbuf[id].pickup_hearts*HP_PER_HEART));
}

//tf pickup anim


void LinkClass::getTriforce(int id2)

 guys.clear();
    items.clear();
    Ewpns.clear();
    Lwpns.clear();
    Sitems.clear();
    chainlinks.clear();
    decorations.clear();
    

void LinkClass::saved_Zelda()
{
    Playing=Paused=false;
    action=won;
    Quit=qWON;
    hclk=0;
    x = 136;
    y = (isdungeon() && currscr<128) ? 75 : 73;
    z = fall = spins = 0;
    dir=left;
}

/// QR stuff


bool no_subscreen()
{
    return (tmpscr->flags3&fNOSUBSCR)!=0;
}

      
      if(get_bit(quest_rules,qr_OUCHBOMBS))
	      
//global
      sfx(itemsbuf[itemid].usesound);
      stop_sfx(WAV_ER);
      
      stop_sfx() can kill any sound!
      bool no_subscreen();
bool is_zquest();
bool screenIsScrolling();
      
      screen_scale
      byte use_debug_console=0
      currgame=0,
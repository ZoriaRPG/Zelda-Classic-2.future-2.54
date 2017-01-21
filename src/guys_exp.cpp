//invisibility

flags |= guy_invisible

int hclk
bool itemguy, count_enemy, dying, ceiling, leader, scored, script_spawned;
    fix  step, floor_y;
    
    
    case NOACTIVESUBSC:
	ret=Link.stopSubscreenFalling()?10000:0;
	break;
    
    case NOACTIVESUBSC:
	Link.stopSubscreenFalling((value/10000)?1:0);
	break;
    
    short wdp, wpn;
    
    int getEnemyInvincible();
    void setEnemyInvincible(int v);
    
     case NPCINVINC:
        if(GuyH::loadNPC(ri->guyref, "npc->InvFrames") != SH::_NoError)
            ret = -10000;
        else
	ret = (int)GuyH::getNPC()->hclk * 10000;
            
        break;
	
	case NPCSUPERMAN:
        if(GuyH::loadNPC(ri->guyref, "npc->Invincible") != SH::_NoError)
            ret = -10000;
        else
	ret = (int)GuyH::getNPC()->superman * 10000;
            
        break;
	
	case NPCDD:
    {
        int a = ri->d[0] / 10000;
        
        if(GuyH::loadNPC(ri->guyref, "npc->Attributes") != SH::_NoError ||
                BC::checkBounds(a, 0, 11, "npc->Attributes") != SH::_NoError)
		GuyH::getNPCDMisc(a) = value * 10000;
    }
    break;
	
    case NPCINVINC:
    {
        if(GuyH::loadNPC(ri->guyref, "npc->InvFrames") == SH::_NoError)
            GuyH::getNPC()->hclk = (int)value/10000;
    }
    break;
    
    case NPCSUPERMAN:
    {
        if(GuyH::loadNPC(ri->guyref, "npc->Invincible") == SH::_NoError)
            GuyH::getNPC()->superman = (int)value/10000;
    }
    break;
    
    case NPCWPN:
        if(GuyH::loadNPC(ri->guyref, "npc->Weapon") != SH::_NoError)
            ret = -10000;
        else
	ret = (short)GuyH::getNPC()->wpn * 10000;
            
        break;
	
	
    case NPCWPN:
    {
        if(GuyH::loadNPC(ri->guyref, "npc->Weapon") == SH::_NoError)
            GuyH::getNPC()->wpn = (short)value/10000;
    }
    break;
    
    case NPCWPNDMG:
        if(GuyH::loadNPC(ri->guyref, "npc->WeaponDamage") != SH::_NoError)
            ret = -10000;
        else
	ret = (short)GuyH::getNPC()->wdp * 10000;
            
        break;
	
	
    case NPCWPNDMG:
    {
        if(GuyH::loadNPC(ri->guyref, "npc->WeaponDamage") == SH::_NoError)
            GuyH::getNPC()->wdp = (short)value/10000;
    }
    break;
    
    case NPCHASITEM:
        if(GuyH::loadNPC(ri->guyref, "npc->HasItem") != SH::_NoError)
            ret = 0;
        else
	ret = GuyH::getNPC()->itemguy?10000:0;
            
        break;
	
	
    case NPCHASITEM:
    {
        if(GuyH::loadNPC(ri->guyref, "npc->HasItem") == SH::_NoError)
            GuyH::getNPC()->iteguy = (value/10000)?1:0;
    }
    break;
    
    short getEnemyWeapon();
    short getEnemyWeaponDamage();
    void setEnemyWeapon(short wpn);
    void setEnemyWeaponDamage(short wdp);
    
    
    bool getEnemyHasItem();
    void setEnemyHasItem(bool v);
    
    bool getEnemyBeatable();
    void setEnemyBeatable(bool v);
    
    bool getEnemySying();
    void setEnemyDying(bool v);
    
    bool getEnemyCeiling();
    void setEnemyCeiling(bool v);
    
    bool getEnemyLeader();
    void setEnemyLeader(bool v);
    
    bool getEnemyScored();
    void setEnemyScored(bool v);
    
    bool getEnemyScriptSpawned();
    void setEnemyScriptSpawned(bool v);
    
    int getEnemyCarryingItem();
    void setEnemyCarryingItem(int itm);
    guycarryingitem
    
    void setEnemyFlag(int flag, bool value);
    bool getEnemyFlag(int flag);
    void setEnemyFlag2(int flag, bool value);
    bool getEnemyFlag2(int flag);
    
    flags flags2
    
    case NPCSTEP:
        if(GuyH::loadNPC(ri->guyref, "npc->Step") != SH::_NoError)
            ret = -10000;
        else
            ret = long(GuyH::getNPC()->step * fix(100.0)) * 10000;
            
        break;
	
	
    case NPCSTEP:
    {
        if(GuyH::loadNPC(ri->guyref, "npc->Step") == SH::_NoError)
            GuyH::getNPC()->step = fix(value / 10000) / fix(100.0);
    }
    break;
    
    case NPCSTEP:
        if(GuyH::loadNPC(ri->guyref, "npc->Step") != SH::_NoError)
            ret = -10000;
        else
            ret = long(GuyH::getNPC()->step * fix(100.0)) * 10000;
            
        break;
	
	
    case NPCSTEP:
    {
        if(GuyH::loadNPC(ri->guyref, "npc->Step") == SH::_NoError)
            GuyH::getNPC()->step = fix(value / 10000) / fix(100.0);
    }
    break;
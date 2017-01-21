//Link.h

bool diagonalMovement;
    bool bigHitbox;
    ladderx\
    
    swordclk, //sword jinx timeout.
        itemclk, 
	
	  void setX(int new_x);
    void setY(int new_y);
    void setZ(int new_Z);
    
    
bool  LinkClass::getDiagMove()
{
    return diagonalMovement;
}
void LinkClass::setDiagMove(bool newdiag)
{
    diagonalMovement=newdiag;
}

bool  LinkClass::getBigHitbox()
{
    return bigHitbox;
}
void LinkClass::setBigHitbox(bool newbighitbox)
{
    bigHitbox=newbighitbox;
}

 case LINKDIAG:
	ret=getDiagMove()?10000:0;
	break;
 
 case LINKDIAG:
	ret=Link.getDiagMove()?10000:0;
	break;
    
    case LINKBIGHITBOX:
	ret=Link.getBigHitbox()?10000:0;
	break;
    
    case LINKEQUIP:
        ret = ((Awpn&0xFF)|((Bwpn&0xFF)<<8))*10000;
        break;
    
    
     game->set_timevalid((value/10000)?1:0);
    
     disableClickToFreeze=value==0;
    
    ((value/10000)!=0)?true:false;
    
    find LINKZOFS
    
    case LINKTILE:
        ret = (int)(Link.tile)*10000;
        break;
    
        #define LINKDIAG             0x0249
#define LINKBIGHITBOX             0x024A
    case INPUTPRESSAXISRIGHT:
        button_press[17]=((value/10000)!=0)?true:false;
        break;
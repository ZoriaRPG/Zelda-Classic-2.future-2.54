LoadLevelPalette(int dmap)

 if(BC::checkDMapID(ID, "Game->SetDMapPalette") == SH::_NoError)
        {


 case CURLEVEL:
        ret=DMaps[get_currdmap()].level*10000;
        break;
 
 
 case DMAPLEVELD:
        GET_DMAP_VAR(level,   "Game->DMapLevel")    break;
        
 
 case DMAPLEVELPAL:
	GET_DMAP_VAR(color,   "Game->DMapLevelPalette")    break; case DMAPLEVELPAL:
	SET_DMAP_VAR(color,   "Game->DMapLevelPalette")    break;
 
 
 
#define GET_DMAP_VAR(member, str) \
{ \
    int ID = ri->d[0] / 10000; \
    if(BC::checkDMapID(ID, str) != SH::_NoError) \
        ret = -10000; \
    else \
        ret = DMaps[ID].member * 10000; \
}
 
 //Can we make setters for these?
 
 
void do_getmessage(const bool v)
{
    long ID = SH::get_arg(sarg1, v) / 10000;
    long arrayptr = get_register(sarg2) / 10000;
    
    if(BC::checkMessage(ID, "Game->GetMessage") != SH::_NoError)
        return;
        
    if(ArrayH::setArray(arrayptr, string(MsgStrings[ID].s)) == SH::_Overflow)
        Z_scripterrlog("Array supplied to 'Game->GetMessage' not large enough\n");
}

void do_getdmapname(const bool v)
{
    long ID = SH::get_arg(sarg1, v) / 10000;
    long arrayptr = get_register(sarg2) / 10000;
    
    if(BC::checkDMapID(ID, "Game->GetDMapName") != SH::_NoError)
        return;
        
    if(ArrayH::setArray(arrayptr, string(DMaps[ID].name)) == SH::_Overflow)
        Z_scripterrlog("Array supplied to 'Game->GetDMapName' not large enough\n");
}

void do_getdmaptitle(const bool v)
{
    long ID = SH::get_arg(sarg1, v) / 10000;
    long arrayptr = get_register(sarg2) / 10000;
    
    if(BC::checkDMapID(ID, "Game->GetDMapTitle") != SH::_NoError)
        return;
        
    if(ArrayH::setArray(arrayptr, string(DMaps[ID].title)) == SH::_Overflow)
        Z_scripterrlog("Array supplied to 'Game->GetDMapTitle' not large enough\n");
}

void do_getdmapintro(const bool v)
{
    long ID = SH::get_arg(sarg1, v) / 10000;
    long arrayptr = get_register(sarg2) / 10000;
    
    if(BC::checkDMapID(ID, "Game->GetDMapIntro") != SH::_NoError)
        return;
        
    if(ArrayH::setArray(arrayptr, string(DMaps[ID].intro)) == SH::_Overflow)
        Z_scripterrlog("Array supplied to 'Game->GetDMapIntro' not large enough\n");
}
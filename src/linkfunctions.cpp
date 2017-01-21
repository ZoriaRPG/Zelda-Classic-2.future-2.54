void do_getsidewarpdmap(const bool v)
{
    long warp = SH::get_arg(sarg1, v) / 10000;
    
    if(BC::checkBounds(warp, -1, 3, "Screen->GetSideWarpDMap") != SH::_NoError)
    {
        set_register(sarg1, -10000);
        return;
    }
    
    set_register(sarg1, tmpscr->sidewarpdmap[warp]*10000);
}


void do_get_enh_music_track(const bool v)
{
    long ID = SH::get_arg(sarg1, v) / 10000;
    
    if(BC::checkDMapID(ID, "Game->GetDMapMusicTrack") != SH::_NoError)
        return;
        
    set_register(sarg1, (DMaps[ID].tmusictrack+1)*10000);
}

void set_link_extend(bool v)
{
    int state   = SH::read_stack(ri->sp + 2) / 10000;
    int extend = SH::read_stack(ri->sp + 1) / 10000;
    int dir   = SH::read_stack(ri->sp) / 10000;
    Link.setExtend(vbound(state,1,14),vbound(dir,0,16),vbound(extend,0,16));
}

void get_link_extend(bool v)
{
    int state   = SH::read_stack(ri->sp + 1) / 10000;
    int dir   = SH::read_stack(ri->sp) / 10000;
    int extend = Link.getExtend(state, dir);
    set_register(sarg1, extend*10000);
}

string OGetSideWarpType::toString()
{
    return "GETSIDEWARPTYPE " + getArgument()->toString();
}

string OSetLinkTile::toString()
{
    return "SETLINKTILE";
}

string OSetLinkExtend::toString()
{
    return "SETLINKEXTEND";
}
string OGetLinkExtend::toString()
{
    return "GETLINKEXTEND " + getArgument()->toString();
}

 //int GetDMapMusicTrack(game, int)
    {
        int id = memberids["GetDMapMusicTrack"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        Opcode *first = new OPopRegister(new VarArgument(EXP1));
        first->setLabel(label);
        code.push_back(first);
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OGetDMapMusicTrack(new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label]=code;
    }
    
    
class OGetDMapMusicTrack : public UnaryOpcode
{
public:
    OGetDMapMusicTrack(Argument *A) : UnaryOpcode(A) {}
    string toString();
    Opcode *clone()
    {
        return new OGetDMapMusicTrack(a->clone());
    }
};

string OGetDMapMusicTrack::toString()
{
    return "GETMUSICTRACK " + getArgument()->toString();
}

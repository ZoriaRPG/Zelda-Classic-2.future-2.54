tx += Link.getLinkHitXOffset();
		ty += Link.getLinkHitYOffset();
		tz += Link.getLinkHitZOffset();
		txsz += Link.getLinkHitWidth();
		tysz += Link.getLinkHitHeight();
		tzsz += Link.getLinkHitZHeight();


//We also need to be able to set Link's flip
// enum {spr_tile, spr_flip, spr_extend};
zinit.linkanimationstyle //holds the style to use
link_animation_speed //the walk anim speed
zinit.link_swim_speed

 set_bit(quest_rules, qr_LTTPCOLLISION, (linktile_dlg[5].flags&D_SELECTED)?1:0);
        set_bit(quest_rules, qr_LTTPWALK, (linktile_dlg[76].flags&D_SELECTED)?1:0);
        zinit.link_swim_speed=(linktile_dlg[95].d1==0)?50:67;
	
	private:
		
	Link. hclk,     //damage blinking timeout.
	 attack,   //current attack wpnid.
        attackid, //current attack itemid.
	
	slashxofs, slashyofs; // used by positionSword() and draw()
    byte skipstep,lstep,
     int sdir; // scrolling direction
     
     fix entry_x, entry_y; // When drowning, re-create Link here
     
     bool startwpn(int itemid);
     
      void getTriforce(int id);
      
      void gameover();
    void ganon_intro();
    
    bool agonyflag(int flag);
    int ringpower(int dmg);
    void addsparkle(int wpn);
    void addsparkle2(int type1, int type2);
    
    public:
    
    void linkstep();
    
    fix  getX();
    fix  getY();
    fix  getZ();
    fix  getFall();
    fix  getXOfs();
    fix  getYOfs();
    void setXOfs(int newxofs);
    void setYOfs(int newyofs);
    int  getHXOfs();
    int  getHYOfs();
    int  getHXSz();
    int  getHYSz();
    
        int  getLStep();
    
     bool can_deploy_ladder();
    
    void setHClk(int newhclk);
    int getHClk();
    
    void do_lens();
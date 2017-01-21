////////////////////////////
/// Scripted Lock Blocks ///
/// v0.3 - 25-Nov-2016   ///
/// By: ZoriaRPG         ///
////////////////////////////

//Main Settings

const int USE_CUSTOM_KEYS = 1; //If se to '1', the script will require a custom key type, tied to
			//a script counter, configured below. 

//User Settings
const int CBM_LOCKBLOCK2 = 888; //The combo used by the special lockblock. 

const int TIMER_WALK_UNLOCK = 50; //The number of frames that Link must push against the lockblock to open it.
const int CR_LOCKBLOCKKEY = 7; //Script 1
const int SFX_SPEC_LOCKBLOCK = 9; //The sound to play when unlocking a lockblock.
const int CR_MAX_LOCKBLOCKKEY = 32; //The maximum number of special keys that Link may have. Used only with the item script.

const int SCREEN_D_SPECIALLOCKBLOCK = 7;

//In the event that you want to know how to script a key, too. 
item script SpecialLockBlockKey{
	void run(){
		if ( Game->MCounter[CR_LOCKBLOCKKEY] < CR_MAX_LOCKBLOCKKEY ) Game->MCounter[CR_LOCKBLOCKKEY] = CR_MAX_LOCKBLOCKKEY;
		Game->Counter[CR_LOCKBLOCKKEY]++;
	}
}


//Flags for up to four lock blocks.
const int SPC_LOCK_1 = 0001b;
const int SPC_LOCK_2 = 0010b;
const int SPC_LOCK_3 = 0100b;
const int SPC_LOCK_4 = 1000b;

ffc script SpecialLockBlock{
	void run(int block){
		int cmb;
		int timer = TIMER_WALK_UNLOCK;
		if ( Screen->D[SCREEN_D_SPECIALLOCKBLOCK] ) {
			for ( int q = 0; q < 176; q++ ) {
				if ( LockBlockFlag(SPC_LOCK_1) && Screen->ComboD[q] == CBM_LOCKBLOCK2 ) Screen->ComboD[q]++;
				if ( LockBlockFlag(SPC_LOCK_2) && Screen->ComboD[q] == CBM_LOCKBLOCK2 + 2 ) Screen->ComboD[q]++;
				if ( LockBlockFlag(SPC_LOCK_3) && Screen->ComboD[q] == CBM_LOCKBLOCK2 + 4 ) Screen->ComboD[q]++;
				if ( LockBlockFlag(SPC_LOCK_4) && Screen->ComboD[q] == CBM_LOCKBLOCK2 + 6 ) Screen->ComboD[q]++;
			}			
		}
		while ( true ) {
			
			if ( 
				( !USE_CUSTOM_KEYS && ( Game->Counter[CR_KEYS] || Game->LKeys[Game->GetCurLevel()] ) ) ||
				( USE_CUSTOM_KEYS && Game->Counter[CR_LOCKBLOCKKEY] ) ) 
			{
				if ( Link->Dir == DIR_UP ){
					cmb = Screen->ComboD[ ___AdjacentCombo(ComboAt(Link->X+8, Link->Y+8),1) ];
					
					if ( cmb == CBM_LOCKBLOCK2 || cmb == CBM_LOCKBLOCK2 +2 || cmb == CBM_LOCKBLOCK2 + 4 || cmb == CBM_LOCKBLOCK2 +6 ) {
						if ( timer && Link->InputUp ) timer--;
						if ( timer <= 0 ) { 
							if ( USE_CUSTOM_KEYS ) Game->Counter[CR_LOCKBLOCKKEY]--; 
							if ( !USE_CUSTOM_KEYS ) {
								if ( Game->LKeys[Game->GetCurLevel()] ) Game->LKeys[Game->GetCurLevel()]--;
								else Game->Counter[CR_KEYS]--;
							}
							if ( SFX_SPEC_LOCKBLOCK ) Game->PlaySound(SFX_SPEC_LOCKBLOCK); 
							Screen->ComboD[ ___AdjacentCombo(ComboAt(Link->X+8, Link->Y+8),1) ]++; 
							if ( cmb == CBM_LOCKBLOCK2 ) {
								LockBlockFlag(SPC_LOCK_1,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 2 ) {
								LockBlockFlag(SPC_LOCK_2,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 4 ) {
								LockBlockFlag(SPC_LOCK_3,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 6 ) {
								LockBlockFlag(SPC_LOCK_4,true);
							}
							timer = TIMER_WALK_UNLOCK; 
							Link->InputUp = false; 
						}
					}
					else timer = TIMER_WALK_UNLOCK;
				}
				else if ( Link->Dir == DIR_DOWN ){
					cmb = Screen->ComboD[ ___AdjacentCombo(ComboAt(Link->X+8, Link->Y+8),5) ];
					
					if ( cmb == CBM_LOCKBLOCK2 || cmb == CBM_LOCKBLOCK2 +2 || cmb == CBM_LOCKBLOCK2 + 4 || cmb == CBM_LOCKBLOCK2 +6 ) {
						if ( timer > 0 && Link->InputDown ) timer--;
						if ( timer <= 0 ) { 
							if ( USE_CUSTOM_KEYS ) Game->Counter[CR_LOCKBLOCKKEY]--; 
							if ( !USE_CUSTOM_KEYS ) {
								if ( Game->LKeys[Game->GetCurLevel()] ) Game->LKeys[Game->GetCurLevel()]--;
								else Game->Counter[CR_KEYS]--;
							}
							if ( SFX_SPEC_LOCKBLOCK ) Game->PlaySound(SFX_SPEC_LOCKBLOCK); 
							Screen->ComboD[ ___AdjacentCombo(ComboAt(Link->X+8, Link->Y+8),5) ]++; 
							if ( cmb == CBM_LOCKBLOCK2 ) {
								LockBlockFlag(SPC_LOCK_1,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 2 ) {
								LockBlockFlag(SPC_LOCK_2,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 4 ) {
								LockBlockFlag(SPC_LOCK_3,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 6 ) {
								LockBlockFlag(SPC_LOCK_4,true);
							}
							timer = TIMER_WALK_UNLOCK; 
							Link->InputDown = false; 
						}
					}
					else timer = TIMER_WALK_UNLOCK;
				}
				else if ( Link->Dir == DIR_LEFT ) {
					cmb = Screen->ComboD[ ___AdjacentCombo(ComboAt(Link->X+8, Link->Y+8),7) ];
					if ( cmb == CBM_LOCKBLOCK2 || cmb == CBM_LOCKBLOCK2 +2 || cmb == CBM_LOCKBLOCK2 + 4 || cmb == CBM_LOCKBLOCK2 +6 ) {
						if ( timer > 0 && Link->InputLeft ) timer--;
						if ( timer <= 0 ) { 
							if ( USE_CUSTOM_KEYS ) Game->Counter[CR_LOCKBLOCKKEY]--; 
							if ( !USE_CUSTOM_KEYS ) {
								if ( Game->LKeys[Game->GetCurLevel()] ) Game->LKeys[Game->GetCurLevel()]--;
								else Game->Counter[CR_KEYS]--;
							}
							if ( SFX_SPEC_LOCKBLOCK ) Game->PlaySound(SFX_SPEC_LOCKBLOCK); 
							Screen->ComboD[ ___AdjacentCombo(ComboAt(Link->X+8, Link->Y+8),7) ]++; 
							if ( cmb == CBM_LOCKBLOCK2 ) {
								LockBlockFlag(SPC_LOCK_1,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 2 ) {
								LockBlockFlag(SPC_LOCK_2,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 4 ) {
								LockBlockFlag(SPC_LOCK_3,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 6 ) {
								LockBlockFlag(SPC_LOCK_4,true);
							}
							timer = TIMER_WALK_UNLOCK; 
							Link->InputLeft = false; 
						}
					}
					else timer = TIMER_WALK_UNLOCK;
				}
				else if ( Link->Dir == DIR_RIGHT ) {
					cmb = Screen->ComboD[ ___AdjacentCombo(ComboAt(Link->X+8, Link->Y+8),3)];
					if ( cmb == CBM_LOCKBLOCK2 || cmb == CBM_LOCKBLOCK2 +2 || cmb == CBM_LOCKBLOCK2 + 4 || cmb == CBM_LOCKBLOCK2 +6 ) {
						if ( timer > 0 && Link->InputRight ) timer--;
						if ( timer <= 0 ) { 
							if ( USE_CUSTOM_KEYS ) Game->Counter[CR_LOCKBLOCKKEY]--; 
							if ( !USE_CUSTOM_KEYS ) {
								if ( Game->LKeys[Game->GetCurLevel()] ) Game->LKeys[Game->GetCurLevel()]--;
								else Game->Counter[CR_KEYS]--;
							}
							if ( SFX_SPEC_LOCKBLOCK ) Game->PlaySound(SFX_SPEC_LOCKBLOCK); 
							Screen->ComboD[ ___AdjacentCombo(ComboAt(Link->X+8, Link->Y+8),3) ]++; 
							if ( cmb == CBM_LOCKBLOCK2 ) {
								LockBlockFlag(SPC_LOCK_1,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 2 ) {
								LockBlockFlag(SPC_LOCK_2,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 4 ) {
								LockBlockFlag(SPC_LOCK_3,true);
							}
							if ( cmb == CBM_LOCKBLOCK2 + 6 ) {
								LockBlockFlag(SPC_LOCK_4,true);
							}
							timer = TIMER_WALK_UNLOCK; 
							Link->InputRight = false; 
						}
					}
					else timer = TIMER_WALK_UNLOCK;
					
				}
				
			}
			else timer = TIMER_WALK_UNLOCK;
			Waitframe();
		}
	}

	void LockBlockFlag(int flag, bool state){
		if(state) Screen->D[SCREEN_D_SPECIALLOCKBLOCK] |= flag;
		else Screen->D[SCREEN_D_SPECIALLOCKBLOCK] &= ~flag;
	}

	bool LockBlockFlag(int flag){
		return (Screen->D[SCREEN_D_SPECIALLOCKBLOCK]&flag) != 0;
	}

	//Constants for AdjacentCombo()

	//const int CMB_UPLEFT    = 0;
	//const int CMB_UP        = 1;
	//const int CMB_UPRIGHT   = 2;
	//const int CMB_RIGHT     = 3;
	//const int CMB_DOWNRIGHT = 4;
	//const int CMB_DOWN      = 5;
	//const int CMB_DOWNLEFT  = 6;
	//const int CMB_LEFT      = 7;
	//const int CMB_LEFTUP    = 0; //Not 8, as those are dir + shield

	//Returns the Nuth combo index of a combo based on a central point, and a direction.
	//For example, combo 22 + COMBO_UPRIGHT returns '7', 
	//as combo 7 is to the upper-right of combo 22.
	int ___AdjacentCombo(int cmb, int dir){
	    int combooffsets[13]={-0x11,-0x10,-0x0F,1,0x11,0x10,0x0F,-1,-0x10};
	    if ( cmb % 16 == 0 ) combooffsets[9] = 1;
	    if ( (cmb & 15) == 1 ) combooffsets[10] = 1; 
	    if ( cmb < 0x10 ) combooffsets[11] = 1; //if it's the top row
	    if ( cmb > 0xAF ) combooffsets[12] = 1; //if it's on the bottom row
	    if ( combooffsets[9] && ( dir == 7 || dir == 1 || dir == 4 || dir == 0 ) ) return 0; //if the left columb
	    if ( combooffsets[10] && ( dir == 3 || dir == 2 || dir == 4 ) ) return 0; //if the right column
	    if ( combooffsets[11] && ( dir == 2 || dir == 2 || dir == 1 ) ) return 0; //if the top row
	    if ( combooffsets[12] && ( dir == 5 || dir == 4 || dir == 6 ) ) return 0; //if the bottom row
	    else if ( cmb >= 0 && cmb <= 176 ) return cmb + combooffsets[dir];
	    else return -1;
	}
}


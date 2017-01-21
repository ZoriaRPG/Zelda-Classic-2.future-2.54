int LinkClass::getSprite(int action){
	
int LinkClass::getSprite(int action){ //Converts an action into its sprite
	if (z>0 || isSideview()) && jumping2>0 && jumping2<24 && game->get_life()>0 && action!=rafting) return 6;
	else{ 
		switch(action){
			case won:
			case walking:
			case none:
			case gothit:
			case rafting:
			case scrolling:
			case freeze: 
			case dying:
			case hopping:
			case inwind: //no special sprite
				return 1;
			
			case swimhit:
			case swimming:
				return 3;
			
			case drowning:
				if ( drownclk > 60 ) return 2;
				else return 4;
			
			case attacking:
				if ( attack==wHammer ) return 9;
				else return 8;
			
			case casting:
				return 10;
			
			case ischarging:
				return 7;
			
			case landhold1:
				return 11;
			case landhold2:
				return 12;
			case waterhold1:
				return 13;
			case waterhold2:
				return 14;
				
			default: 
				return 1;
		}
	}
}

		
		
		case 0: //LA_NON
		case 1: //LA_WALK
			case 9: //scrolling
			
		case 2: //attacking
			
		case 3: //frozen
			
		case 4: //hole1land
			
		case 5: //hold2land
			
		case 6: //rafting
		case 7: //hurtland
			
		case 8: //inwind
			
		
			
		case 10: //winning
			
		case 11: //swimming
			
		case 12: //hopping
			
		case 13: //hurtwater
			
		case 14: //hold1water
			
		case 15: //hold2water
			
		case 16: //casting
			
		case 17: //cavewalkup
			
		case 18: //cavewalkdown
			
		case 19: dying
			
		case 20: //drowning
			
		case 21: 
			//Undefined
		return 1;
			
		case 22: //charging
			
		case 23: //spinning
			
		case 24: //diving
		
		
		case 1: 
			walkspr[dir][spr_extend] = value;
			break;
		case 2: 
			floatspr[dir][spr_extend] = value;
			break;
		case 3: 
			swimspr[dir][spr_extend] = value;
			break;
		case 4: 
			divespr[dir][spr_extend] = value;
			break;
		case 5:
			slashspr[dir][spr_extend] = value;
			break;
		case 6:
			jumpspr[dir][spr_extend] = value;
			break;
		case 7: 
			chargespr[dir][spr_extend] = value;
			break;
		case 8:
			stabspr[dir][spr_extend] = value;
			break;
		case 9: 
			poundspr[dir][spr_extend] = value;
			break;
		case 10: 
			castingspr[spr_extend] = value;
			break;
		case 11: 
			holdspr[spr_landhold][spr_hold1][spr_extend] = value;
			break;
		case 12: 
			holdspr[spr_landhold][spr_hold2][spr_extend] = value;
			break;
		case 13: 
			holdspr[spr_waterhold][spr_hold1][spr_extend] = value;
			break;
		case 14: 
			holdspr[spr_waterhold][spr_hold2][spr_extend] = value;
		
		default: break;
	}
}
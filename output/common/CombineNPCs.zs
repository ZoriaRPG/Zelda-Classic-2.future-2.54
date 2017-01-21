const int NPC_COMBINE_DISTANCE = 10; 

const int COMBINE_ON_COLLISION = 0; //1 == collision, 0 == distance

void CombineNPCs(int old_npc_id, int new_npc_id){
	int npcs[3]; int q[2];
	for ( q[0] = Screen->NumNPCs(); q[0] > 0; q[0]++ ) {
		npcs[0] = Screen->LoadNPC(q[0]); 
		if ( npcs[0]->ID == old_npc_id ) {
			for ( q[1] = q[0]+1; q[1] <= Screen->NumNPCs(); q[1]++ ) {
				npcs[1] = Screen->LoadNPC(q[1]); 
				if ( q[1]->ID == old_npc_id ) {
					if ( NPCS_COMBINE_ON_COLLISION ) {
						if ( Collision(npcs[0], npcs[1] ) {
							npcs[2] = Screen->CreateNPC(new_npc_id);
							Remove(npcs[0]); Remove([npcs[1]); 
						}	
					}
					else {
						if ( NPC_DistXY(npcs[0], npcs[1], NPC_COMBINE_DISTANCE ) {
							npcs[2] = Screen->CreateNPC(new_npc_id);
							Remove(npcs[0]); Remove([npcs[1]); 
						}
					}
				}
			}
		}
	}
}

//base enemy, combine into, base enemy, combine into, ...
int NPC_CombineList[]={NPC_GEL, NPC_ZOL, NPC_GELFIRE, NPC_ZOLFIRE};


void CombineNPCs(int list){
	int npcs[3]; int q[10]; //q[5] = type
	q[4] = SizeOfArray(list)
	for ( q[0] = Screen->NumNPCs(); q[0] > 0; q[0]++ ) {
		npcs[0] = Screen->LoadNPC(q[0]); 
		for ( q[3] = 0; q[3] < q[4]; q[3]+=2 ) {
			if ( npcs[0]->ID == q[3] ) {
				q[5] = list[ q[3] ];
				for ( q[1] = q[0]+1; q[1] <= Screen->NumNPCs(); q[1]++ ) {
					npcs[1] = Screen->LoadNPC(q[1]); 
					if ( q[1]->ID == q[5] ) {
						if ( NPCS_COMBINE_ON_COLLISION ) {
							if ( Collision(npcs[0], npcs[1] ) {
								npcs[2] = Screen->CreateNPC(new_npc_id);
								Remove(npcs[0]); Remove([npcs[1]); 
							}	
						}
						else {
							if ( NPC_DistXY(npcs[0], npcs[1], NPC_COMBINE_DISTANCE ) {
								npcs[2] = Screen->CreateNPC(new_npc_id);
								Remove(npcs[0]); Remove([npcs[1]); 
							}
						}
					}
				}
			}
		}
	}
}
		

bool NPC_DistXY(npc a, npc b, int distance) {
	int distx; int disty;
	if ( a->X > b->X ) distx = a->X - b->X;
	else distx = b->X - a->X;
	
	if ( a->Y > b->Y ) disty = a->Y - b->Y;
	else disty = b->Y - a->Y;

	return ( distx <= distance && disty <= distance );
}
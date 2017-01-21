void setuplinktiles(int style)
{
    old_floatspr = wpnsbuf[iwSwim].tile;
    old_slashspr = wpnsbuf[iwLinkSlash].tile;
    linkspr = 4;
    
    switch(style)
    {
    case 0:                                                 //normal
        walkspr[up][spr_tile]=linkspr+20;
        walkspr[up][spr_flip]=0;
        walkspr[up][spr_extend]=0;
        walkspr[down][spr_tile]=linkspr+18;
        walkspr[down][spr_flip]=0;
        walkspr[down][spr_extend]=0;
        walkspr[left][spr_tile]=linkspr+16;
        walkspr[left][spr_flip]=1;
        walkspr[left][spr_extend]=0;
        walkspr[right][spr_tile]=linkspr+16;
        walkspr[right][spr_flip]=0;
        walkspr[right][spr_extend]=0;
        
        stabspr[up][spr_tile]=linkspr+23;
        stabspr[up][spr_flip]=0;
        stabspr[up][spr_extend]=0;
        stabspr[down][spr_tile]=linkspr+22;
        stabspr[down][spr_flip]=0;
        stabspr[down][spr_extend]=0;
        stabspr[left][spr_tile]=linkspr+21;
        stabspr[left][spr_flip]=1;
        stabspr[left][spr_extend]=0;
        stabspr[right][spr_tile]=linkspr+21;
        stabspr[right][spr_flip]=0;
        stabspr[right][spr_extend]=0;
        
        slashspr[up][spr_tile]=old_slashspr;
        slashspr[up][spr_flip]=0;
        slashspr[up][spr_extend]=0;
        slashspr[down][spr_tile]=old_slashspr+1;
        slashspr[down][spr_flip]=0;
        slashspr[down][spr_extend]=0;
        slashspr[left][spr_tile]=old_slashspr+2;
        slashspr[left][spr_flip]=0;
        slashspr[left][spr_extend]=0;
        slashspr[right][spr_tile]=old_slashspr+3;
        slashspr[right][spr_flip]=0;
        slashspr[right][spr_extend]=0;
        
        floatspr[up][spr_tile]=old_floatspr + 4;
        floatspr[up][spr_flip]=0;
        floatspr[up][spr_extend]=0;
        floatspr[down][spr_tile]=old_floatspr + 2;
        floatspr[down][spr_flip]=0;
        floatspr[down][spr_extend]=0;
        floatspr[left][spr_tile]=old_floatspr;
        floatspr[left][spr_flip]=1;
        floatspr[left][spr_extend]=0;
        floatspr[right][spr_tile]=old_floatspr;
        floatspr[right][spr_flip]=0;
        floatspr[right][spr_extend]=0;
        
        swimspr[up][spr_tile]=old_floatspr + 4;
        swimspr[up][spr_flip]=0;
        swimspr[up][spr_extend]=0;
        swimspr[down][spr_tile]=old_floatspr + 2;
        swimspr[down][spr_flip]=0;
        swimspr[down][spr_extend]=0;
        swimspr[left][spr_tile]=old_floatspr;
        swimspr[left][spr_flip]=1;
        swimspr[left][spr_extend]=0;
        swimspr[right][spr_tile]=old_floatspr;
        swimspr[right][spr_flip]=0;
        swimspr[right][spr_extend]=0;
        
        divespr[up][spr_tile]=old_floatspr + 8;
        divespr[up][spr_flip]=0;
        divespr[up][spr_extend]=0;
        divespr[down][spr_tile]=old_floatspr + 8;
        divespr[down][spr_flip]=0;
        divespr[down][spr_extend]=0;
        divespr[left][spr_tile]=old_floatspr + 8;
        divespr[left][spr_flip]=0;
        divespr[left][spr_extend]=0;
        divespr[right][spr_tile]=old_floatspr + 8;
        divespr[right][spr_flip]=0;
        divespr[right][spr_extend]=0;
        
        poundspr[up][spr_tile]=linkspr+3;
        poundspr[up][spr_flip]=0;
        poundspr[up][spr_extend]=0;
        poundspr[down][spr_tile]=linkspr+2;
        poundspr[down][spr_flip]=0;
        poundspr[down][spr_extend]=0;
        poundspr[left][spr_tile]=linkspr+1;
        poundspr[left][spr_flip]=1;
        poundspr[left][spr_extend]=0;
        poundspr[right][spr_tile]=linkspr+1;
        poundspr[right][spr_flip]=0;
        poundspr[right][spr_extend]=0;
        
// Alter these when default sprites are created.
        jumpspr[up][spr_tile]=linkspr+24;
        jumpspr[up][spr_flip]=0;
        jumpspr[up][spr_extend]=0;
        jumpspr[down][spr_tile]=linkspr+19;
        jumpspr[down][spr_flip]=0;
        jumpspr[down][spr_extend]=0;
        jumpspr[left][spr_tile]=linkspr+16;
        jumpspr[left][spr_flip]=1;
        jumpspr[left][spr_extend]=0;
        jumpspr[right][spr_tile]=linkspr+16;
        jumpspr[right][spr_flip]=0;
        jumpspr[right][spr_extend]=0;
        
// Alter these when default sprites are created.
        chargespr[up][spr_tile]=linkspr+24;
        chargespr[up][spr_flip]=0;
        chargespr[up][spr_extend]=0;
        chargespr[down][spr_tile]=linkspr+19;
        chargespr[down][spr_flip]=0;
        chargespr[down][spr_extend]=0;
        chargespr[left][spr_tile]=linkspr+16;
        chargespr[left][spr_flip]=1;
        chargespr[left][spr_extend]=0;
        chargespr[right][spr_tile]=linkspr+16;
        chargespr[right][spr_flip]=0;
        chargespr[right][spr_extend]=0;
        
        castingspr[spr_tile]=linkspr;
        castingspr[spr_flip]=0;
        castingspr[spr_extend]=0;
        
        holdspr[spr_landhold][spr_hold1][spr_tile]=linkspr+30;
        holdspr[spr_landhold][spr_hold1][spr_flip]=0;
        holdspr[spr_landhold][spr_hold1][spr_extend]=0;
        holdspr[spr_landhold][spr_hold2][spr_tile]=linkspr+25;
        holdspr[spr_landhold][spr_hold2][spr_flip]=0;
        holdspr[spr_landhold][spr_hold2][spr_extend]=0;
        
        holdspr[spr_waterhold][spr_hold1][spr_tile]=old_floatspr+7;
        holdspr[spr_waterhold][spr_hold1][spr_flip]=0;
        holdspr[spr_waterhold][spr_hold1][spr_extend]=0;
        holdspr[spr_waterhold][spr_hold2][spr_tile]=old_floatspr+6;
        holdspr[spr_waterhold][spr_hold2][spr_flip]=0;
        holdspr[spr_waterhold][spr_hold2][spr_extend]=0;
        break;
        
    case 1:                                                 //BS
        walkspr[up][spr_tile]=linkspr+24;
        walkspr[up][spr_flip]=0;
        walkspr[up][spr_extend]=0;
        walkspr[down][spr_tile]=linkspr+19;
        walkspr[down][spr_flip]=0;
        walkspr[down][spr_extend]=0;
        walkspr[left][spr_tile]=linkspr+16;
        walkspr[left][spr_flip]=1;
        walkspr[left][spr_extend]=0;
        walkspr[right][spr_tile]=linkspr+16;
        walkspr[right][spr_flip]=0;
        walkspr[right][spr_extend]=0;
        
        stabspr[up][spr_tile]=linkspr+27;
        stabspr[up][spr_flip]=0;
        stabspr[up][spr_extend]=0;
        stabspr[down][spr_tile]=linkspr+23;
        stabspr[down][spr_flip]=0;
        stabspr[down][spr_extend]=0;
        stabspr[left][spr_tile]=linkspr+22;
        stabspr[left][spr_flip]=1;
        stabspr[left][spr_extend]=0;
        stabspr[right][spr_tile]=linkspr+22;
        stabspr[right][spr_flip]=0;
        stabspr[right][spr_extend]=0;
        
        slashspr[up][spr_tile]=old_slashspr;
        slashspr[up][spr_flip]=0;
        slashspr[up][spr_extend]=0;
        slashspr[down][spr_tile]=old_slashspr+1;
        slashspr[down][spr_flip]=0;
        slashspr[down][spr_extend]=0;
        slashspr[left][spr_tile]=old_slashspr+2;
        slashspr[left][spr_flip]=0;
        slashspr[left][spr_extend]=0;
        slashspr[right][spr_tile]=old_slashspr+3;
        slashspr[right][spr_flip]=0;
        slashspr[right][spr_extend]=0;
        
        floatspr[up][spr_tile]=old_floatspr+6;
        floatspr[up][spr_flip]=0;
        floatspr[up][spr_extend]=0;
        floatspr[down][spr_tile]=old_floatspr+3;
        floatspr[down][spr_flip]=0;
        floatspr[down][spr_extend]=0;
        floatspr[left][spr_tile]=old_floatspr;
        floatspr[left][spr_flip]=1;
        floatspr[left][spr_extend]=0;
        floatspr[right][spr_tile]=old_floatspr;
        floatspr[right][spr_flip]=0;
        floatspr[right][spr_extend]=0;
        
        swimspr[up][spr_tile]=old_floatspr+6;
        swimspr[up][spr_flip]=0;
        swimspr[up][spr_extend]=0;
        swimspr[down][spr_tile]=old_floatspr+3;
        swimspr[down][spr_flip]=0;
        swimspr[down][spr_extend]=0;
        swimspr[left][spr_tile]=old_floatspr;
        swimspr[left][spr_flip]=1;
        swimspr[left][spr_extend]=0;
        swimspr[right][spr_tile]=old_floatspr;
        swimspr[right][spr_flip]=0;
        swimspr[right][spr_extend]=0;
        
        divespr[up][spr_tile]=old_floatspr + 11;
        divespr[up][spr_flip]=0;
        divespr[up][spr_extend]=0;
        divespr[down][spr_tile]=old_floatspr + 11;
        divespr[down][spr_flip]=0;
        divespr[down][spr_extend]=0;
        divespr[left][spr_tile]=old_floatspr + 11;
        divespr[left][spr_flip]=0;
        divespr[left][spr_extend]=0;
        divespr[right][spr_tile]=old_floatspr + 11;
        divespr[right][spr_flip]=0;
        divespr[right][spr_extend]=0;
        
        poundspr[up][spr_tile]=linkspr+3;
        poundspr[up][spr_flip]=0;
        poundspr[up][spr_extend]=0;
        poundspr[down][spr_tile]=linkspr+2;
        poundspr[down][spr_flip]=0;
        poundspr[down][spr_extend]=0;
        poundspr[left][spr_tile]=linkspr+1;
        poundspr[left][spr_flip]=1;
        poundspr[left][spr_extend]=0;
        poundspr[right][spr_tile]=linkspr+1;
        poundspr[right][spr_flip]=0;
        poundspr[right][spr_extend]=0;
        
// Alter these when default sprites are created.
        jumpspr[up][spr_tile]=linkspr+24;
        jumpspr[up][spr_flip]=0;
        jumpspr[up][spr_extend]=0;
        jumpspr[down][spr_tile]=linkspr+19;
        jumpspr[down][spr_flip]=0;
        jumpspr[down][spr_extend]=0;
        jumpspr[left][spr_tile]=linkspr+16;
        jumpspr[left][spr_flip]=1;
        jumpspr[left][spr_extend]=0;
        jumpspr[right][spr_tile]=linkspr+16;
        jumpspr[right][spr_flip]=0;
        jumpspr[right][spr_extend]=0;
        
// Alter these when default sprites are created.
        chargespr[up][spr_tile]=linkspr+24;
        chargespr[up][spr_flip]=0;
        chargespr[up][spr_extend]=0;
        chargespr[down][spr_tile]=linkspr+19;
        chargespr[down][spr_flip]=0;
        chargespr[down][spr_extend]=0;
        chargespr[left][spr_tile]=linkspr+16;
        chargespr[left][spr_flip]=1;
        chargespr[left][spr_extend]=0;
        chargespr[right][spr_tile]=linkspr+16;
        chargespr[right][spr_flip]=0;
        chargespr[right][spr_extend]=0;
        
        castingspr[spr_tile]=linkspr;
        castingspr[spr_flip]=0;
        castingspr[spr_extend]=0;
        
        holdspr[spr_landhold][spr_hold1][spr_tile]=linkspr+29;
        holdspr[spr_landhold][spr_hold1][spr_flip]=0;
        holdspr[spr_landhold][spr_hold1][spr_extend]=0;
        holdspr[spr_landhold][spr_hold2][spr_tile]=linkspr+28;
        holdspr[spr_landhold][spr_hold2][spr_flip]=0;
        holdspr[spr_landhold][spr_hold2][spr_extend]=0;
        
        holdspr[spr_waterhold][spr_hold1][spr_tile]=old_floatspr+10;
        holdspr[spr_waterhold][spr_hold1][spr_flip]=0;
        holdspr[spr_waterhold][spr_hold1][spr_extend]=0;
        holdspr[spr_waterhold][spr_hold2][spr_tile]=old_floatspr+9;
        holdspr[spr_waterhold][spr_hold2][spr_flip]=0;
        holdspr[spr_waterhold][spr_hold2][spr_extend]=0;
        break;
        
    default:
        break;
    }
}
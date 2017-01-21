//--------------------------------------------------------
//  Zelda Classic
//  by Jeremy Craner, 1999-2000
//
//  subscr.cc
//
//  Subscreen code for zelda.cc
//
//--------------------------------------------------------

#ifndef __GTHREAD_HIDE_WIN32API
#define __GTHREAD_HIDE_WIN32API 1
#endif                            //prevent indirectly including windows.h

#include "precompiled.h" //always first

#include <map>

#include "gui.h"
#include "subscr.h"
#include "zq_subscr.h"
#include "jwin.h"
#include "zquest.h"
#include "zsys.h"
#include "zq_misc.h"
#include "tiles.h"
#include "qst.h"
#include "init.h"
#include <assert.h>
#include "mem_debug.h"

#ifndef _MSC_VER
#include <strings.h>
#endif
#include <string.h>

#ifdef _MSC_VER
#define stricmp _stricmp
#endif

extern void large_dialog(DIALOG *d);
extern void large_dialog(DIALOG *d, float RESIZE_AMT);

using namespace std;

int curr_subscreen_object;
char *str_oname;
subscreen_group *css;
bool sso_selection[MAXSUBSCREENITEMS];
static int propCopySrc=-1;

void replacedp(DIALOG &d, const char *newdp, size_t size=256);

gamedata *game;

//extern char *itemlist(int index, int *list_size)
extern int bii_cnt;

void delete_subscreen(int subscreenidx);


const char *colortype_str[14] =
{
    "Misc. Color", "Sys. Color", "CSet 0", "CSet 1", "CSet 2", "CSet 3", "CSet 4", "CSet 5", "CSet 6", "CSet 7", "CSet 8", "CSet 9", "CSet 10", "CSet 11"
};

const char *colortypelist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = 14;
        return NULL;
    }
    
    return colortype_str[index];
}

int d_cs_color_proc(int msg,DIALOG *d,int c)
{
    //these are here to bypass compiler warnings about unused arguments
    c=c;
    
    int w=(d->w-4)/16;
    
    switch(msg)
    {
    case MSG_DRAW:
        //rectfill(screen, d->x+2, d->y+2, d->x+d->w-3, d->y+d->h-3, jwin_pal[jcBOX]);
        //top blank part
        rectfill(screen, d->x, d->y, d->x+(w*16)+3, d->y+1, jwin_pal[jcBOX]);
        jwin_draw_frame(screen,d->x,d->y+2,w*16+4, d->h-4, FR_DEEP);
        
        for(int i=0; i<16; ++i)
        {
            rectfill(screen, d->x+2+(w*i), d->y+4, d->x+2+(w*(i+1))-1, d->y+d->h-5, ((d-2)->d1-2)*16+i);
        }
        
        // right end
        rectfill(screen, d->x+(w*16)+4, d->y, d->x+d->w-1, d->y+d->h-1, jwin_pal[jcBOX]);
        // bottom part
        rectfill(screen, d->x, d->y+d->h-2, d->x+(w*16)+3, d->y+d->h-1, jwin_pal[jcBOX]);
        
        //indicator lines
        hline(screen, d->x+2+(w*d->d1), d->y, d->x+2+(w*(d->d1+1))-1, jwin_pal[jcBOXFG]);
        hline(screen, d->x+2+(w*d->d1), d->y+d->h-1, d->x+2+(w*(d->d1+1))-1, jwin_pal[jcBOXFG]);
        
        break;
        
    case MSG_CLICK:
        d->d1=vbound((gui_mouse_x()-d->x-2)/w,0,15);
        d->flags|=D_DIRTY;
        break;
    }
    
    return D_O_K;
}

int d_sys_color_proc(int msg,DIALOG *d,int c)
{
    //these are here to bypass compiler warnings about unused arguments
    c=c;
    
    int w=(d->w-4)/17;
    
    switch(msg)
    {
    case MSG_DRAW:
        //rectfill(screen, d->x+2, d->y+2, d->x+d->w-3, d->y+d->h-3, jwin_pal[jcBOX]);
        //top blank part
        rectfill(screen, d->x, d->y, d->x+(w*17)+3, d->y+1, jwin_pal[jcBOX]);
        jwin_draw_frame(screen,d->x,d->y+2,w*17+4, d->h-4, FR_DEEP);
        
        for(int i=0; i<17; ++i)
        {
            rectfill(screen, d->x+2+(w*i), d->y+4, d->x+2+(w*(i+1))-1, d->y+d->h-5, vc(zc_max(0,i-1)));
        }
        
        line(screen, d->x+2, d->y+4, d->x+2+w-1, d->y+d->h-5, vc(15));
        line(screen, d->x+2, d->y+d->h-5, d->x+2+w-1, d->y+4, vc(15));
        // right end
        rectfill(screen, d->x+(w*17)+4, d->y, d->x+d->w-1, d->y+d->h-1, jwin_pal[jcBOX]);
        // bottom part
        rectfill(screen, d->x, d->y+d->h-2, d->x+(w*17)+3, d->y+d->h-1, jwin_pal[jcBOX]);
        
        //indicator lines
        hline(screen, d->x+2+(w*(d->d1+1)), d->y, d->x+2+(w*(d->d1+2))-1, jwin_pal[jcBOXFG]);
        hline(screen, d->x+2+(w*(d->d1+1)), d->y+d->h-1, d->x+2+(w*(d->d1+2))-1, jwin_pal[jcBOXFG]);
        
        break;
        
    case MSG_CLICK:
        d->d1=vbound((gui_mouse_x()-d->x-2)/w,0,16)-1;
        d->flags|=D_DIRTY;
        break;
    }
    
    return D_O_K;
}

void update_ctl_proc(DIALOG *d, int ct)
{
    switch(ct)
    {
    case 0:
        d->proc=jwin_droplist_proc;
        break;
        
    case 1:
        d->proc=d_sys_color_proc;
        break;
        
    default:
        d->proc=d_cs_color_proc;
        break;
    }
    
    d->flags|=D_DIRTY;
}

int d_ctl_proc(int msg,DIALOG *d,int c)
{
    int old_d1=d->d1;
    int ret=jwin_droplist_proc(msg, d, c);
    
    if(d->d1!=old_d1)
    {
        update_ctl_proc(d+2, d->d1);
    }
    
    return ret;
}

int d_csl2_proc(int msg,DIALOG *d,int c);

void update_csl_proc(DIALOG *d, int cs)
{
    switch(cs)
    {
    case 0:
        d->proc=jwin_text_proc;
        d->fg=jwin_pal[jcBOXFG];
        d->bg=jwin_pal[jcBOX];
        (d+1)->proc=d_csl2_proc;
        (d+1)->fg=0;
        (d+1)->bg=0;
        //(d+59)->fg=subscreen_cset(&misc,(d-1)->d1?(d-1)->d1-1:ssctMISC, (d+1)->d1);
        break;
        
    default:
        d->proc=d_box_proc;
        d->fg=jwin_pal[jcBOX];
        d->bg=jwin_pal[jcBOX];
        (d+1)->proc=d_box_proc;
        (d+1)->fg=jwin_pal[jcBOX];
        (d+1)->bg=jwin_pal[jcBOX];
        break;
    }
    
    d->flags|=D_DIRTY;
    (d+1)->flags|=D_DIRTY;
}

int d_csl_proc(int msg,DIALOG *d,int c)
{
    int old_d1=d->d1;
    int ret=jwin_droplist_proc(msg, d, c);
    
    if(d->d1!=old_d1)
    {
        update_csl_proc(d+1, d->d1);
        (d+60)->fg=subscreen_cset(&misc,d->d1?d->d1-1:ssctMISC, (d+2)->d1);
    }
    
    return ret;
}

int d_csl2_proc(int msg,DIALOG *d,int c)
{
    int old_d1=d->d1;
    int ret=jwin_droplist_proc(msg, d, c);
    
    if(d->d1!=old_d1)
    {
        (d+58)->fg=subscreen_cset(&misc,(d-2)->d1?(d-2)->d1-1:ssctMISC, d->d1);
    }
    
    return ret;
}

int jwin_fontdrop_proc(int msg,DIALOG *d,int c)
{
    int old_d1=d->d1;
    int ret=jwin_droplist_proc(msg, d, c);
    
    if(d->d1!=old_d1)
    {
        (d+3)->dp2=ss_font(d->d1);
        (d+3)->flags|=D_DIRTY;
        
        if((d+3)->proc!=d_dummy_proc)
        {
            rectfill(screen, (d+3)->x, (d+3)->y, (d+3)->x+(d+3)->w-1, (d+3)->y+(d+3)->h-1, jwin_pal[jcBOX]);
        }
        
        (d+3)->h=text_height(ss_font(d->d1))+8;
        (d+49)->dp2=ss_font(d->d1);
        (d+49)->flags|=D_DIRTY;
        
        if((d+49)->proc!=d_dummy_proc)
        {
            rectfill(screen, (d+49)->x, (d+49)->y, (d+49)->x+(d+49)->w-1, (d+49)->y+(d+49)->h-1, jwin_pal[jcBOX]);
        }
        
        (d+49)->h=text_height(ss_font(d->d1))+8;
    }
    
    return ret;
}

const char *misccolor_str[ssctMAX] =
{
    "Text", "Caption", "Overworld BG", "Dungeon BG", "Dungeon FG", "Cave FG", "BS Dark", "BS Goal", "Compass (Lt)", "Compass (Dk)",
    "SS BG", "SS Shadow", "Tri. Frame", "Big Map BG", "Big Map FG", "Link's Pos", "Message Text"
};

const char *misccolorlist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = ssctMAX;
        return NULL;
    }
    
    return misccolor_str[index];
}

const char *csettype_str[13] =
{
    "Misc. CSet", "CSet 0", "CSet 1", "CSet 2", "CSet 3", "CSet 4", "CSet 5", "CSet 6", "CSet 7", "CSet 8", "CSet 9", "CSet 10", "CSet 11"
};

const char *csettypelist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = 13;
        return NULL;
    }
    
    return csettype_str[index];
}

const char *misccset_str[sscsMAX] =
{
    "Triforce", "Tri. Frame", "Overworld Map", "Dungeon Map", "Blue Frame", "HC Piece", "SS Vine"
};

const char *misccsetlist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = sscsMAX;
        return NULL;
    }
    
    return misccset_str[index];
}

const char *spectile_str[ssmstMAX+1] =
{
    "None", "SS Vine", "Magic Meter"
};

const char *spectilelist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = ssmstMAX+1;
        return NULL;
    }
    
    return spectile_str[index];
}

const char *ssfont_str[ssfMAX] =
{
    "Zelda NES", "SS 1", "SS 2", "SS 3", "SS 4", "BS Time", "Small", "Small Prop.", "LttP Small", "Link's Awakening", "Link to the Past",
    "Goron", "Zoran", "Hylian 1", "Hylian 2", "Hylian 3", "Hylian 4", "Proportional", "Oracle", "Oracle Proportional", "Phantom", "Phantom Proportional"
};

const char *ssfontlist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = ssfMAX;
        return NULL;
    }
    
    return ssfont_str[index];
}

const char *shadowstyle_str[sstsMAX] =
{
    "None", "Shadow", "Shadow (U)", "Shadow (O)", "Shadow (+)", "Shadow (X)", "Shadowed", "Shadowed (U)", "Shadowed (O)", "Shadowed (+)", "Shadowed (X)"
};

const char *shadowstylelist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = sstsMAX;
        return NULL;
    }
    
    return shadowstyle_str[index];
}

const char *alignment_str[3] =
{
    "Left", "Center", "Right"
};

const char *alignmentlist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = 3;
        return NULL;
    }
    
    return alignment_str[index];
}

const char *wrapping_str[2] =
{
    "Character", "Word"
};

const char *wrappinglist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = 2;
        return NULL;
    }
    
    return wrapping_str[index];
}

const char *gaugeshow_str[3] =
{
    "Always", "1/2", "Normal"
};

const char *rows_str[2] =
{
    "Two", "Three"
};

const char *gaugeshowlist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = 3;
        return NULL;
    }
    
    return gaugeshow_str[index];
}

const char *rowslist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = 2;
        return NULL;
    }
    
    return rows_str[index];
}

const char *button_str[2] =
{
    "A", "B"
};

const char *buttonlist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = 2;
        return NULL;
    }
    
    return button_str[index];
}

const char *icounter_str[sscMAX] =
{
    "Rupees", "Bombs", "Super Bombs", "Arrows", "Gen. Keys w/Magic", "Gen. Keys w/o Magic", "Level Keys w/Magic",
    "Level Keys w/o Magic", "Any Keys w/Magic", "Any Keys w/o Magic", "Script 1", "Script 2", "Script 3", "Script 4",
    "Script 5", "Script 6", "Script 7", "Script 8", "Script 9", "Script 10", "Script 11", "Script 12", "Script 13",
    "Script 14", "Script 15", "Script 16", "Script 17", "Script 18", "Script 19", "Script 20", "Script 21",
    "Script 22", "Script 23", "Script 24", "Script 25"
};

const char *icounterlist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = sscMAX;
        return NULL;
    }
    
    return icounter_str[index];
}


int d_stilelist_proc(int msg,DIALOG *d,int c)
{
    int old_d1=d->d1;
    int ret=jwin_droplist_proc(msg, d, c);
    
    if(d->d1!=old_d1)
    {
        (d-14)->h=is_large?32:16;
        (d-15)->h=(d-14)->h+4;
        
        switch(d->d1-1)
        {
        case ssmstSSVINETILE:
            (d-15)->w=52;
            (d-14)->w=48;
            (d-14)->d1=wpnsbuf[iwSubscreenVine].tile;
            break;
            
        case ssmstMAGICMETER:
            (d-15)->w=148;
            (d-14)->w=144;
            (d-14)->d1=wpnsbuf[iwMMeter].tile;
            break;
            
        case -1:
        default:
            (d-15)->w=20;
            (d-14)->w=16;
            break;
        }
        
        (d-14)->w*=is_large?2:1;
        (d-15)->w=(d-14)->w+4;
        (d-14)->bg=vbound((d-14)->bg,0,((d-14)->w-1)>>2);
        (d-17)->flags|=D_DIRTY;
        (d-15)->flags|=D_DIRTY;
        (d-14)->flags|=D_DIRTY;
        (d-1)->flags|=D_DIRTY;
        d->flags|=D_DIRTY;
    }
    
    return ret;
}



static int ssop_location_list[] =
{
    // dialog control number
    5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,212,213, -1
};

static int ssop_color_list[] =
{
    // dialog control number
    35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, -1
};

static int ssop_attributes_list[] =
{
    // dialog control number
    95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, -1
};

static TABPANEL sso_properties_tabs[] =
{
    // (text)
    { (char *)"Location",    D_SELECTED,  ssop_location_list,   0, NULL },
    { (char *)"Color",       0,           ssop_color_list,      0, NULL },
    { (char *)"Attributes",  0,           ssop_attributes_list, 0, NULL },
    { NULL,                  0,           NULL,                 0, NULL }
};

DIALOG *sso_properties_dlg;

int jwin_tflpcheck_proc(int msg,DIALOG *d,int c)
{
    bool selected=(d->flags&D_SELECTED)!=0;
    int ret= is_large ? jwin_checkfont_proc(msg,d,c) : jwin_check_proc(msg, d, c);
    bool new_selected=(d->flags&D_SELECTED)!=0;
    
    if(new_selected!=selected)
    {
        (d-3)->w=(new_selected?32:16)*(is_large+1);
        (d-3)->h=(new_selected?48:16)*(is_large+1);
        (d-4)->w=(d-3)->w+4;
        (d-4)->h=(d-3)->h+4;
//    (d-5)->x=((d-4)->x)+(((d-4)->w)/2);
        (d-6)->w=(new_selected?112:96)*(is_large+1);
        (d-6)->h=(new_selected?112:48)*(is_large+1);
        (d-7)->w=(d-6)->w+4;
        (d-7)->h=(d-6)->h+4;
//    (d-8)->x=((d-7)->x)+(((d-7)->w)/2);
        (d-3)->flags|=D_DIRTY;
        (d-4)->flags|=D_DIRTY;
        (d-5)->flags|=D_DIRTY;
        (d-6)->flags|=D_DIRTY;
        (d-7)->flags|=D_DIRTY;
        (d-8)->flags|=D_DIRTY;
        (d-9)->flags|=D_DIRTY;
    }
    
    return ret;
}

int jwin_lscheck_proc(int msg,DIALOG *d,int c)
{
    bool selected=(d->flags&D_SELECTED)!=0;
    int ret=is_large ? jwin_checkfont_proc(msg,d,c) : jwin_check_proc(msg, d, c);
    bool new_selected=(d->flags&D_SELECTED)!=0;
    
    if(new_selected!=selected || msg==MSG_START)
    {
        (d-6)->w=(new_selected?32:16)*(is_large+1);
        (d-6)->h=(new_selected?48:16)*(is_large+1);
        (d-7)->w=(d-6)->w+4;
        (d-7)->h=(d-6)->h+4;
        (d-6)->flags|=D_DIRTY;
        (d-7)->flags|=D_DIRTY;
        (d-8)->flags|=D_DIRTY;
        (d-9)->flags|=D_DIRTY;
    }
    
    return ret;
}

int d_qtile_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_DRAW:
    {
        int dw = d->w;
        int dh = d->h;
        
        if(is_large)
        {
            dw /= 2;
            dh /= 2;
        }
        
        BITMAP *buf = create_bitmap_ex(8,dw,dh);
        
        if(buf)
        {
            clear_bitmap(buf);
            
            for(int y=0; y<dh; y+=16)
            {
                for(int x=0; x<dw; x+=16)
                {
                    puttile16(buf,d->d1+(y>>4)*20+(x>>4),x,y,d->fg,d->d2);
                }
            }
            
            int t=d->bg>>2;
            int t2=d->bg-(t<<2);
            rect(buf,
                 (t<<4)+((t2&1)<<3) ,
                 ((t2&2)<<2),
                 (t<<4)+((t2&1)<<3)+7,
                 ((t2&2)<<2)+7, jwin_pal[jcTITLER]);
            stretch_blit(buf,screen,0,0,dw,dh,d->x-is_large,d->y-is_large,dw*(is_large?2:1),dh*(is_large?2:1));
            destroy_bitmap(buf);
        }
        
        //textprintf_ex(screen, pfont, d->x,d->y, vc(15), -1, "%d", d->bg);
        return D_O_K;
    }
    break;
    
    case MSG_CLICK:
    {
        int old_fg=d->fg;
        
        if(gui_mouse_b()&2)  //right mouse button
        {
            int old_bg=d->bg;
            int mx=vbound(gui_mouse_x()-d->x,0,d->w-1);
            int my=vbound(gui_mouse_y()-d->y,0,d->h-1);
            
            if(is_large)
            {
                mx/=2;
                my/=2;
            }
            
            int t=mx>>4;
            d->bg=(t<<2)+((my>>3)<<1)+((mx-(t<<4))>>3);
            
            if(d->bg!=old_bg)
            {
                d->flags|=D_DIRTY;
            }
            
            return D_O_K;
        }
        
        int ret=d_maptile_proc(msg, d, c);
        
        if(d->fg!=old_fg)
        {
            (d-60)->d1=d->fg+1;
            (d-60)->d2=(d-60)->d1;
            update_csl_proc(d-59, d->fg+1);
        }
        
        d->flags|=D_DIRTY;
        return ret;
    }
    break;
    }
    
    return d_maptile_proc(msg, d, c);
}

int d_spectile_proc(int msg,DIALOG *d,int c)
{
    int d1=d->d1;
    int ret=d_qtile_proc(msg,d,c);
    
    if(d1!=d->d1)
    {
        (d+14)->d1=0;
        (d+14)->d2=0;
        (d+14)->flags|=D_DIRTY;
        d->w=16*(is_large+1);
        (d-1)->w=d->w+4;
        d->flags|=D_DIRTY;
        (d-1)->flags|=D_DIRTY;
        (d-3)->flags|=D_DIRTY;
    }
    
    return ret;
}

int d_tileblock_proc(int msg,DIALOG *d,int c)
{
    int old_fg=d->fg;
    int ret=d_maptile_proc(msg, d, c);
    
    switch(msg)
    {
    case MSG_CLICK:
        if(d->fg!=old_fg)
        {
            (d-60)->d1=d->fg+1;
            (d-60)->d2=(d-60)->d1;
            update_csl_proc(d-59, d->fg+1);
        }
        
        d->flags|=D_DIRTY;
        break;
    }
    
    return ret;
}


extern int d_alltriggerbutton_proc(int msg,DIALOG *d,int c);
extern int d_comboa_radio_proc(int msg,DIALOG *d,int c);
extern int d_comboabutton_proc(int msg,DIALOG *d,int c);
extern int d_jbutton_proc(int msg,DIALOG *d,int c);
extern int d_kbutton_proc(int msg,DIALOG *d,int c);
extern int d_listen_proc(int msg,DIALOG *d,int c);
extern int d_savemidi_proc(int msg,DIALOG *d,int c);
extern int d_ssdn_btn_proc(int msg,DIALOG *d,int c);
extern int d_ssdn_btn2_proc(int msg,DIALOG *d,int c);
extern int d_ssdn_btn3_proc(int msg,DIALOG *d,int c);
extern int d_ssdn_btn4_proc(int msg,DIALOG *d,int c);
extern int d_sslt_btn_proc(int msg,DIALOG *d,int c);
extern int d_sslt_btn2_proc(int msg,DIALOG *d,int c);
extern int d_sslt_btn3_proc(int msg,DIALOG *d,int c);
extern int d_sslt_btn4_proc(int msg,DIALOG *d,int c);
extern int d_ssrt_btn_proc(int msg,DIALOG *d,int c);
extern int d_ssrt_btn2_proc(int msg,DIALOG *d,int c);
extern int d_ssrt_btn3_proc(int msg,DIALOG *d,int c);
extern int d_ssrt_btn4_proc(int msg,DIALOG *d,int c);
extern int d_ssup_btn_proc(int msg,DIALOG *d,int c);
extern int d_ssup_btn2_proc(int msg,DIALOG *d,int c);
extern int d_ssup_btn3_proc(int msg,DIALOG *d,int c);
extern int d_ssup_btn4_proc(int msg,DIALOG *d,int c);
extern int d_triggerbutton_proc(int msg,DIALOG *d,int c);

void dummy_dialog_proc(DIALOG *d)
{
    replacedp(*d,NULL);
    d->proc=d_dummy_proc;
    d->x=-1;
    d->y=-1;
    d->w=0;
    d->h=0;
}


void extract_colortype(DIALOG *d, subscreen_object *tempsso, int ct)
{
    switch(ct)
    {
    case 3:
        switch(tempsso->colortype3)
        {
        case ssctMISC:
            d->d1=0;
            break;
            
        case ssctSYSTEM:
            d->d1=1;
            break;
            
        default:
            d->d1=tempsso->colortype3+2;
            break;
        }
        
        break;
        
    case 2:
        switch(tempsso->colortype2)
        {
        case ssctMISC:
            d->d1=0;
            break;
            
        case ssctSYSTEM:
            d->d1=1;
            break;
            
        default:
            d->d1=tempsso->colortype2+2;
            break;
        }
        
        break;
        
    case 1:
    default:
        switch(tempsso->colortype1)
        {
        case ssctMISC:
            d->d1=0;
            break;
            
        case ssctSYSTEM:
            d->d1=1;
            break;
            
        default:
            d->d1=tempsso->colortype1+2;
            break;
        }
        
        break;
    }
}

void insert_colortype(DIALOG *d, subscreen_object *tempsso, int ct)
{
    switch(ct)
    {
    case 3:
        switch(d->d1)
        {
        case 0:
            tempsso->colortype3=ssctMISC;
            break;
            
        case 1:
            tempsso->colortype3=ssctSYSTEM;
            break;
            
        default:
            tempsso->colortype3=d->d1-2;
            break;
        }
        
        break;
        
    case 2:
        switch(d->d1)
        {
        case 0:
            tempsso->colortype2=ssctMISC;
            break;
            
        case 1:
            tempsso->colortype2=ssctSYSTEM;
            break;
            
        default:
            tempsso->colortype2=d->d1-2;
            break;
        }
        
        break;
        
    case 1:
    default:
        switch(d->d1)
        {
        case 0:
            tempsso->colortype1=ssctMISC;
            break;
            
        case 1:
            tempsso->colortype1=ssctSYSTEM;
            break;
            
        default:
            tempsso->colortype1=d->d1-2;
            break;
        }
        
        break;
    }
}

void extract_cset(DIALOG *d, subscreen_object *tempsso, int ct)
{
    switch(ct)
    {
    case 3:
        switch(tempsso->colortype3)
        {
        case ssctMISC:
            d->d1=0;
            break;
            
        default:
            d->d1=tempsso->colortype3+1;
            break;
        }
        
        break;
        
    case 2:
        switch(tempsso->colortype2)
        {
        case ssctMISC:
            d->d1=0;
            break;
            
        default:
            d->d1=tempsso->colortype2+1;
            break;
        }
        
        break;
        
    case 1:
    default:
        switch(tempsso->colortype1)
        {
        case ssctMISC:
            d->d1=0;
            break;
            
        default:
            d->d1=tempsso->colortype1+1;
            break;
        }
        
        break;
    }
}

void insert_cset(DIALOG *d, subscreen_object *tempsso, int ct)
{
    switch(ct)
    {
    case 3:
        switch(d->d1)
        {
        case 0:
            tempsso->colortype3=ssctMISC;
            break;
            
        default:
            tempsso->colortype3=d->d1-1;
            break;
        }
        
        break;
        
    case 2:
        switch(d->d1)
        {
        case 0:
            tempsso->colortype2=ssctMISC;
            break;
            
        default:
            tempsso->colortype2=d->d1-1;
            break;
        }
        
        break;
        
    case 1:
    default:
        switch(d->d1)
        {
        case 0:
            tempsso->colortype1=ssctMISC;
            break;
            
        default:
            tempsso->colortype1=d->d1-1;
            break;
        }
        
        break;
    }
}

static DIALOG sso_raw_data_dlg[] =
{
    // (dialog proc)     (x)   (y)   (w)   (h)   (fg)     (bg)    (key)    (flags)     (d1)           (d2)     (dp)
    { jwin_win_proc,     60-12,   40,   200+24,  148,  vc(14),  vc(1),  0,       D_EXIT,          0,             0, (void *) "Raw Data", NULL, NULL },
    { d_timer_proc,         0,    0,     0,    0,    0,       0,       0,       0,          0,          0,         NULL, NULL, NULL },
    { jwin_textbox_proc,       72-12,   60+4,   176+24+1,  92+4,   jwin_pal[jcTEXTFG],  jwin_pal[jcTEXTBG],  0,       D_EXIT,     0,             0,      NULL, NULL, NULL },
    { jwin_button_proc,     130,   163,  61,   21,   vc(14),  vc(1),  13,      D_EXIT,     0,             0, (void *) "OK", NULL, NULL },
    { NULL,                 0,    0,    0,    0,   0,       0,       0,       0,          0,             0,       NULL,                           NULL,  NULL }
};

static ListData gaugeshow_list(gaugeshowlist, &font);
static ListData rows_list(rowslist, &font);
static ListData itemclass_list(item_class_list, &font);

int sso_raw_data(subscreen_object *tempsso)
{
    char raw_text[65535];
    char title[80];
    sprintf(title, "Raw Data for Object #%d", curr_subscreen_object);
    sprintf(raw_text, "Type:  %d\nPosition:  %d\nX:  %d\nY:  %d\nW:  %d\nH:  %d\nColor Type 1:  %d\nColor 1:  %d\nColor Type 2:  %d\nColor 2:  %d\nColor Type 3:  %d\nColor 3:  %d\nD1:  %d\nD2:  %d\nD3:  %d\nD4:  %d\nD5:  %d\nD6:  %d\nD7:  %d\nD8:  %d\nD9:  %d\nD10:  %d\nFrames:  %d\nSpeed:  %d\nDelay:  %d\nFrame:  %d\nDp1:  %s",
            tempsso->type, tempsso->pos, tempsso->x, tempsso->y, tempsso->w, tempsso->h, tempsso->colortype1, tempsso->color1, tempsso->colortype2, tempsso->color2, tempsso->colortype3, tempsso->color3, tempsso->d1, tempsso->d2, tempsso->d3, tempsso->d4, tempsso->d5, tempsso->d6, tempsso->d7, tempsso->d8, tempsso->d9, tempsso->d10, tempsso->frames, tempsso->speed, tempsso->delay, tempsso->frame, tempsso->dp1!=NULL?(char *)tempsso->dp1:"NULL");
    sso_raw_data_dlg[0].dp2=lfont;
    sso_raw_data_dlg[2].dp=raw_text;
    sso_raw_data_dlg[2].d2=0;
    
    if(is_large)
        large_dialog(sso_raw_data_dlg);
        
    zc_popup_dialog(sso_raw_data_dlg,2);
    return D_O_K;
}

static ListData wrapping_list(wrappinglist, &font);
static ListData alignment_list(alignmentlist, &font);
static ListData shadowstyle_list(shadowstylelist, &font);
static ListData misccolor_list(misccolorlist, &font);
static ListData spectile_list(spectilelist, &font);
static ListData ssfont_list(ssfontlist, &font);
static ListData colortype_list(colortypelist, &font);
static ListData item_list(itemlist, &font);

static DIALOG sso_master_properties_dlg[] =
{
    // (dialog proc)       (x)   (y)    (w)     (h)   (fg)                (bg)              (key)    (flags)     (d1)           (d2)     (dp)
    { jwin_win_proc,          0,    0,   320,    240,  vc(0),              vc(11),           0,       D_EXIT,     0,             0, (void *) "Invalid Object Properties", NULL, NULL },
    { jwin_button_proc,      90,  215,    61,     21,  vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "OK", NULL, NULL },
    { jwin_button_proc,     170,  215,    61,     21,  vc(0),              vc(11),           27,      D_EXIT,     0,             0, (void *) "Cancel", NULL, NULL },
    { jwin_tab_proc,          4,   25,   312,    185,  0,                  0,                0,       0,          0,             0, (void *) sso_properties_tabs, NULL, (void *)sso_properties_dlg },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 5
    { jwin_text_proc,         8,   49,    42,     16,  0,                  0,                0,       0,          0,             0, (void *) "Display:", NULL, NULL },
    //{ jwin_droplist_proc,    45,   45,   150,     16,  0,                  0,                0,       0,          0,             0,       (void *) displaylist, NULL, NULL },
    { jwin_check_proc,       50,   48,    60,      9,  0,                  0,                0,       0,          0,             0, (void *) "Active Up", NULL, NULL },
    { jwin_text_proc,         8,   67,   186,     16,  0,                  0,                0,       0,          0,             0, (void *) "X:", NULL, NULL },
    { jwin_edit_proc,        23,   63,    31,     16,  0,                  0,                0,       0,          4,             0,       NULL, NULL, NULL },
    { jwin_text_proc,         8,   85,   186,     16,  0,                  0,                0,       0,          0,             0, (void *) "Y:", NULL, NULL },
    // 10
    { jwin_edit_proc,        23,   81,    31,     16,  0,                  0,                0,       0,          4,             0,       NULL, NULL, NULL },
    { jwin_text_proc,        68,   67,   186,     16,  0,                  0,                0,       0,          0,             0, (void *) "W:", NULL, NULL },
    { jwin_edit_proc,        83,   63,    26,     16,  0,                  0,                0,       0,          3,             0,       NULL, NULL, NULL },
    { jwin_text_proc,        68,   85,   186,     16,  0,                  0,                0,       0,          0,             0, (void *) "H:", NULL, NULL },
    { jwin_edit_proc,        83,   81,    26,     16,  0,                  0,                0,       0,          3,             0,       NULL, NULL, NULL },
    // 15
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 20
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 25
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 30
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 35
    { jwin_frame_proc,        8,   48,   144,     48,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_ETCHED,     0,       NULL, NULL, NULL },
    { jwin_text_proc,        12,   45,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) " Foreground Color ", NULL, NULL },
    { jwin_text_proc,        16,   59,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Type:", NULL, NULL },
    { d_ctl_proc,            46,   55,    88,     16,  0,                  0,                0,       0,          0,             0, (void *) &colortype_list, NULL, NULL },
    { jwin_text_proc,        16,   77,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Color:", NULL, NULL },
    // 40
    { jwin_droplist_proc,    46,   73,    98,     16,  0,                  0,                0,       0,          0,             0, (void *) &misccolor_list, NULL, NULL },
    
    { jwin_frame_proc,        8,  103,   144,     48,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_ETCHED,     0,       NULL, NULL, NULL },
    { jwin_text_proc,        12,  100,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) " Background Color ", NULL, NULL },
    { jwin_text_proc,        16,  114,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Type:", NULL, NULL },
    { d_ctl_proc,            46,  110,    88,     16,  0,                  0,                0,       0,          0,             0, (void *) &colortype_list, NULL, NULL },
    // 45
    { jwin_text_proc,        16,  132,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Color:", NULL, NULL },
    { jwin_droplist_proc,    46,  128,    98,     16,  0,                  0,                0,       0,          0,             0, (void *) &misccolor_list, NULL, NULL },
    
    { jwin_frame_proc,        8,  158,   144,     48,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_ETCHED,     0,       NULL, NULL, NULL },
    { jwin_text_proc,        12,  155,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) " Shadow Color ", NULL, NULL },
    { jwin_text_proc,        16,  169,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Type:", NULL, NULL },
    // 50
    { d_ctl_proc,            46,  165,    88,     16,  0,                  0,                0,       0,          0,             0, (void *) &colortype_list, NULL, NULL },
    { jwin_text_proc,        16,  187,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Color:", NULL, NULL },
    { jwin_droplist_proc,    46,  183,    98,     16,  0,                  0,                0,       0,          0,             0, (void *) &misccolor_list, NULL, NULL },
    
    { jwin_frame_proc,      168,   48,   144,     48,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_ETCHED,     0,       NULL, NULL, NULL },
    { jwin_text_proc,       172,   45,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) " Foreground Color ", NULL, NULL },
    // 55
    { jwin_text_proc,       176,   59,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Type:", NULL, NULL },
    { d_ctl_proc,           206,   55,    88,     16,  0,                  0,                0,       0,          0,             0, (void *) &colortype_list, NULL, NULL },
    { jwin_text_proc,       176,   77,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Color:", NULL, NULL },
    { jwin_droplist_proc,   206,   73,    98,     16,  0,                  0,                0,       0,          0,             0, (void *) &misccolor_list, NULL, NULL },
    
    { jwin_frame_proc,      168,  103,   144,     48,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_ETCHED,     0,       NULL, NULL, NULL },
    // 60
    { jwin_text_proc,       172,  100,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) " Background Color ", NULL, NULL },
    { jwin_text_proc,       176,  114,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Type:", NULL, NULL },
    { d_ctl_proc,           206,  110,    88,     16,  0,                  0,                0,       0,          0,             0, (void *) &colortype_list, NULL, NULL },
    { jwin_text_proc,       176,  132,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Color:", NULL, NULL },
    { jwin_droplist_proc,   206,  128,    98,     16,  0,                  0,                0,       0,          0,             0, (void *) &misccolor_list, NULL, NULL },
    
    // 65
    { jwin_frame_proc,      168,  158,   144,     48,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_ETCHED,     0,       NULL, NULL, NULL },
    { jwin_text_proc,       172,  155,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) " Shadow Color ", NULL, NULL },
    { jwin_text_proc,       176,  169,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Type:", NULL, NULL },
    { d_ctl_proc,           206,  165,    88,     16,  0,                  0,                0,       0,          0,             0, (void *) &colortype_list, NULL, NULL },
    { jwin_text_proc,       176,  187,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Color:", NULL, NULL },
    // 70
    { jwin_droplist_proc,   206,  183,    98,     16,  0,                  0,                0,       0,          0,             0, (void *) &misccolor_list, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 75
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 80
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 85
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 90
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { jwin_ctext_proc,      160,  122,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       D_DISABLED, 0,             0, (void *) "Part of Attributes", NULL, NULL },
    // 95
    { d_box_proc,             8,   45,   156,    122,  vc(4),                  vc(4),                0,       0,          0,             0,       NULL, NULL, NULL },
    { jwin_text_proc,         8,   45,    70,     36,  0,                  0,                0,       D_DISABLED, 0,             0, (void *) "TILE", NULL, NULL },
    { jwin_frame_proc,        8,   51,    20,     20,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_DEEP,       0,       NULL, NULL, NULL },
    { d_maptile_proc,        10,   53,    16,     16,  0,                  0,                0,       0,          0,             0,       NULL, (void*)1, NULL },
    { jwin_text_proc,       128,   45,    70,     36,  0,                  0,                0,       D_DISABLED, 0,             0, (void *) "TILE", NULL, NULL },
    // 100
    { jwin_frame_proc,      128,   51,    36,     52,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_DEEP,       0,       NULL, NULL, NULL },
    { d_maptile_proc,       130,   53,    32,     48,  0,                  0,                0,       0,          0,             0,       NULL, (void*)1, NULL },
    { jwin_check_proc,      166,  109,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Overlay", NULL, NULL },
    { jwin_check_proc,      166,  119,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Transparent", NULL, NULL },
    { jwin_tflpcheck_proc,  166,  129,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Large Pieces", NULL, NULL },
    // 105
    { jwin_text_proc,       166,   55,    96,      8,  vc(14),             vc(1),            0,       0,          0,             0, (void *) "Frames:", NULL, NULL },
    { jwin_text_proc,       166,   73,    96,      8,  vc(14),             vc(1),            0,       0,          0,             0, (void *) "Speed:", NULL, NULL },
    { jwin_text_proc,       166,   91,    96,      8,  vc(14),             vc(1),            0,       0,          0,             0, (void *) "Delay:", NULL, NULL },
    { jwin_edit_proc,       215,   51,    35,     16,  vc(12),             vc(1),            0,       0,          2,             0,       NULL, NULL, NULL },
    { jwin_edit_proc,       215,   69,    35,     16,  vc(12),             vc(1),            0,       0,          3,             0,       NULL, NULL, NULL },
    // 110
    { jwin_edit_proc,       215,   87,    35,     16,  vc(12),             vc(1),            0,       0,          3,             0,       NULL, NULL, NULL },
    { jwin_text_proc,         8,   79,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Special Tile:", NULL, NULL },
    { d_stilelist_proc,      65,   75,    92,     16,  0,                  0,                0,       0,          0,             0, (void *) &spectile_list, NULL, NULL },
    { jwin_text_proc,         8,   97,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Offset:", NULL, NULL },
    { jwin_edit_proc,        65,   93,    69,     16,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 115
    { jwin_text_proc,         8,   55,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Font:", NULL, NULL },
    { jwin_text_proc,         8,   73,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Style:", NULL, NULL },
    { jwin_text_proc,         8,   91,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Alignment:", NULL, NULL },
    { jwin_text_proc,         8,  105,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Text:", NULL, NULL },
    { jwin_fontdrop_proc,    55,   51,   110,     16,  0,                  0,                0,       0,          0,             0, (void *) &ssfont_list, NULL, NULL },
    // 120
    { jwin_droplist_proc,    55,   69,   110,     16,  0,                  0,                0,       0,          0,             0, (void *) &shadowstyle_list, NULL, NULL },
    { jwin_droplist_proc,    55,   87,   110,     16,  0,                  0,                0,       0,          0,             0, (void *) &alignment_list, NULL, NULL },
    { jwin_edit_proc,         8,  115,   146,     16,  0,                  0,                0,       0,          255,           0,       NULL, NULL, NULL },
    { jwin_text_proc,       166,   55,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Wrapping:", NULL, NULL },
    { jwin_text_proc,       166,   73,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Tab Size:", NULL, NULL },
    // 125
    { jwin_droplist_proc,   212,   51,    83,     16,  0,                  0,                0,       0,          0,             0, (void *) &wrapping_list, NULL, NULL },
    { jwin_edit_proc,       212,   69,    83,     16,  0,                  0,                0,       0,          2,             0,       NULL, NULL, NULL },
    { jwin_text_proc,         8,   55,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Item Class:", NULL, NULL },
    { jwin_text_proc,         8,   73,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Position:", NULL, NULL },
    { jwin_text_proc,         8,   91,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Up Select:", NULL, NULL },
    // 130
    { jwin_text_proc,         8,  109,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Down Select:", NULL, NULL },
    { jwin_text_proc,         8,  127,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Left Select:", NULL, NULL },
    { jwin_text_proc,         8,  145,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Right Select:", NULL, NULL },
    { jwin_droplist_proc,    68,   51,   101,     16,  0,                  0,                0,       0,          0,             0, (void *) &itemclass_list, NULL, NULL },
    { jwin_edit_proc,        68,   69,    83,     16,  0,                  0,                0,       0,          2,             0,       NULL, NULL, NULL },
    // 135
    { jwin_edit_proc,        68,   87,    83,     16,  0,                  0,                0,       0,          2,             0,       NULL, NULL, NULL },
    { jwin_edit_proc,        68,  105,    83,     16,  0,                  0,                0,       0,          2,             0,       NULL, NULL, NULL },
    { jwin_edit_proc,        68,  123,    83,     16,  0,                  0,                0,       0,          2,             0,       NULL, NULL, NULL },
    { jwin_edit_proc,        68,  141,    83,     16,  0,                  0,                0,       0,          2,             0,       NULL, NULL, NULL },
    { jwin_check_proc,       68,  177,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Invisible", NULL, NULL },
    // 140
    { jwin_check_proc,      166,  139,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Show Compass", NULL, NULL },
    { jwin_check_proc,      166,  149,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Large", NULL, NULL },
    { jwin_ctext_proc,       18,   45,    70,     36,  0,                  0,                0,       D_DISABLED, 0,             0, (void *) "NOT", NULL, NULL },
    { jwin_ctext_proc,       18,   51,    70,     36,  0,                  0,                0,       D_DISABLED, 0,             0, (void *) "LAST", NULL, NULL },
    { jwin_frame_proc,        8,   57,    20,     20,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_DEEP,       0,       NULL, NULL, NULL },
    // 145
    { d_qtile_proc,          10,   59,    16,     16,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { jwin_ctext_proc,       56,   51,    70,     36,  0,                  0,                0,       D_DISABLED, 0,             0, (void *) "LAST", NULL, NULL },
    { jwin_frame_proc,       46,   57,    20,     20,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_DEEP,       0,       NULL, NULL, NULL },
    { d_qtile_proc,          48,   59,    16,     16,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 150
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { jwin_ctext_proc,       18,  101,    70,     36,  0,                  0,                0,       D_DISABLED, 0,             0, (void *) "CAP", NULL, NULL },
    { jwin_frame_proc,        8,  107,    20,     20,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_DEEP,       0,       NULL, NULL, NULL },
    { d_qtile_proc,          10,  109,    16,     16,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { jwin_ctext_proc,       56,   95,    70,     36,  0,                  0,                0,       D_DISABLED, 0,             0, (void *) "AFTER", NULL, NULL },
    // 155
    { jwin_ctext_proc,       56,  101,    70,     36,  0,                  0,                0,       D_DISABLED, 0,             0, (void *) "CAP", NULL, NULL },
    { jwin_frame_proc,       46,  107,    20,     20,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_DEEP,       0,       NULL, NULL, NULL },
    { d_qtile_proc,          48,  109,    16,     16,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { jwin_check_proc,        8,   78,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Mod", NULL, NULL },
    { jwin_check_proc,       46,   78,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Mod", NULL, NULL },
    // 160
    { jwin_check_proc,        8,  128,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Mod", NULL, NULL },
    { jwin_check_proc,       46,  128,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Mod", NULL, NULL },
    { jwin_text_proc,       166,  109,    96,      8,  vc(14),             vc(1),            0,       0,          0,             0, (void *) "Show:", NULL, NULL },
    { jwin_droplist_proc,   215,  105,    68,     16,  0,                  0,                0,       0,          0,             0, (void *) &gaugeshow_list, NULL, NULL },
    { jwin_text_proc,       166,  133,    96,      8,  vc(14),             vc(1),            0,       0,          0,             0, (void *) "Container:", NULL, NULL },
    // 165
    { jwin_edit_proc,       215,  129,    35,     16,  vc(12),             vc(1),            0,       0,          3,             0,       NULL, NULL, NULL },
    { jwin_check_proc,      166,  147,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Unique Last", NULL, NULL },
    { jwin_text_proc,       166,   91,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Infinite Character:", NULL, NULL },
    { jwin_edit_proc,       253,   87,    58,     16,  0,                  0,                0,       0,          1,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 170
    { jwin_ctext_proc,      160,  122,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       D_DISABLED, 0,             0, (void *) "Part of Attributes", NULL, NULL },
    { jwin_check_proc,        8,   51,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Show 1", NULL, NULL },
    { jwin_check_proc,        8,   63,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Show 2", NULL, NULL },
    { jwin_check_proc,        8,   75,   128,      9,  vc(14),             vc(1),            0,       0,          1,             0, (void *) "Show 3", NULL, NULL },
    { jwin_text_proc,         8,   51,    96,      8,  vc(14),             vc(1),            0,       0,          0,             0, (void *) "Rows:", NULL, NULL },
    // 175
    { jwin_droplist_proc,    57,   47,    68,     16,  0,                  0,                0,       0,          0,             0, (void *) &rows_list, NULL, NULL },
    { jwin_droplist_proc,    68,  159,     128,     16,  0,                  0,                0,       0,          3,             0, (void *) &item_list, NULL, NULL },
    { jwin_text_proc,         8,  163,    48,      8,  jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) "Item Override:", NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 180
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 185
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 190
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 195
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 200
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 205
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 210
    { d_dummy_proc,           0,    0,     0,      0,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_timer_proc,         0,    0,     0,    0,    0,       0,       0,       0,          0,          0,         NULL, NULL, NULL },
    { jwin_check_proc,      115,   48,    70,      9,  0,                  0,                0,       0,          0,             0, (void *) "Active Down", NULL, NULL },
    { jwin_check_proc,      190,   48,    70,      9,  0,                  0,                0,       0,          0,             0, (void *) "Active Scrolling", NULL, NULL },
    { NULL,                 0,    0,    0,    0,   0,       0,       0,       0,          0,             0,       NULL,                           NULL,  NULL }
};

void replacedp(DIALOG &d, const char *newdp, size_t size)
{
    if((d.proc==d_alltriggerbutton_proc)||
            (d.proc==d_button_proc)||
            (d.proc==d_check_proc)||
            (d.proc==d_comboa_radio_proc)||
            (d.proc==d_comboabutton_proc)||
            (d.proc==d_ctext_proc)||
            (d.proc==d_edit_proc)||
            (d.proc==d_jbutton_proc)||
            (d.proc==d_kbutton_proc)||
            (d.proc==d_listen_proc)||
            (d.proc==d_savemidi_proc)||
            (d.proc==d_ssdn_btn_proc)||
            (d.proc==d_ssdn_btn2_proc)||
            (d.proc==d_ssdn_btn3_proc)||
            (d.proc==d_ssdn_btn4_proc)||
            (d.proc==d_sslt_btn_proc)||
            (d.proc==d_sslt_btn2_proc)||
            (d.proc==d_sslt_btn3_proc)||
            (d.proc==d_sslt_btn4_proc)||
            (d.proc==d_ssrt_btn_proc)||
            (d.proc==d_ssrt_btn2_proc)||
            (d.proc==d_ssrt_btn3_proc)||
            (d.proc==d_ssrt_btn4_proc)||
            (d.proc==d_ssup_btn_proc)||
            (d.proc==d_ssup_btn2_proc)||
            (d.proc==d_ssup_btn3_proc)||
            (d.proc==d_ssup_btn4_proc)||
            (d.proc==d_text_proc)||
            (d.proc==d_tri_edit_proc)||
            (d.proc==d_triggerbutton_proc)||
            (d.proc==jwin_button_proc)||
            (d.proc==jwin_check_proc)||
            (d.proc==jwin_ctext_proc)||
            (d.proc==jwin_radio_proc)||
            (d.proc==jwin_rtext_proc)||
            (d.proc==jwin_text_proc)||
            (d.proc==jwin_win_proc) ||
            (d.proc==jwin_edit_proc))
    {
        if(d.dp != NULL)
            zc_free(d.dp);
            
        if(newdp != NULL)
        {
            size = zc_max(size, strlen((char *)newdp)+1);
            d.dp = zc_malloc(size);
            strcpy((char*)d.dp, newdp);
        }
        else
            d.dp = NULL;
    }
    else
    {
        d.dp = (void *)newdp;
    }
}

int sso_properties(subscreen_object *tempsso)
{
    copy_dialog(&sso_properties_dlg, sso_master_properties_dlg);
    char title[256], x_str[256],y_str[256],w_str[256],h_str[256],f_str[256],s_str[256],d_str[256];
    int x_stri=0, y_stri=0, w_stri=0, h_stri=0,f_stri=0,s_stri=0,d_stri=0;
    char buf[256], buf2[256], buf3[256], buf4[256], buf5[256];
    int bufi=0, buf2i=0, buf3i=0,buf4i=0,buf5i=0;
    memset(title, 0, 256);
    memset(x_str, 0, 256);
    memset(y_str, 0, 256);
    memset(w_str, 0, 256);
    memset(h_str, 0, 256);
    memset(f_str, 0, 256);
    memset(s_str, 0, 256);
    memset(d_str, 0, 256);
    memset(buf, 0, 256);
    memset(buf2, 0, 256);
    memset(buf3, 0, 256);
    memset(buf4, 0, 256);
    memset(buf5, 0, 256);
    sprintf(title, "%s Properties (Object #%d)", sso_name(tempsso->type), curr_subscreen_object);
    sprintf(x_str, "invalid");
    sprintf(y_str, "invalid");
    sprintf(w_str, "invalid");
    sprintf(h_str, "invalid");
    int ret=-1;
    
    replacedp(sso_properties_dlg[0],title);
    sso_properties_dlg[0].dp2=lfont;
    
    //for everything
    sso_properties_dlg[6].flags = (tempsso->pos & sspUP) != 0 ? D_SELECTED : 0;
    sso_properties_dlg[212].flags = (tempsso->pos & sspDOWN) != 0 ? D_SELECTED : 0;
    sso_properties_dlg[213].flags = (tempsso->pos & sspSCROLLING) != 0 ? D_SELECTED : 0;
    
    sprintf(x_str, "%d", tempsso->x);
    sprintf(y_str, "%d", tempsso->y);
    sprintf(w_str, "%d", sso_w(tempsso));
    sprintf(h_str, "%d", sso_h(tempsso));
    replacedp(sso_properties_dlg[8],x_str);
    x_stri=8;
    replacedp(sso_properties_dlg[10],y_str);
    y_stri=10;
    replacedp(sso_properties_dlg[12],w_str);
    w_stri=12;
    replacedp(sso_properties_dlg[14],h_str);
    h_stri=14;
    sso_properties_dlg[95].bg=jwin_pal[jcBOX];
    sso_properties_dlg[95].fg=jwin_pal[jcBOX];
    sso_properties_dlg[96].dp2=spfont;
    sso_properties_dlg[99].dp2=spfont;
    replacedp(sso_properties_dlg[108],x_str);
    x_stri=108;
    replacedp(sso_properties_dlg[109],x_str);
    x_stri=109;
    replacedp(sso_properties_dlg[110],x_str);
    x_stri=110;
    replacedp(sso_properties_dlg[114],x_str);
    x_stri=114;
    replacedp(sso_properties_dlg[122],x_str);
    x_stri=112;
    sso_properties_dlg[122].dp2=ss_font(ssfZELDA);
    sso_properties_dlg[122].h=text_height(ss_font(ssfZELDA))+8;
    replacedp(sso_properties_dlg[126],x_str);
    x_stri=126;
    replacedp(sso_properties_dlg[134],x_str);
    x_stri=134;
    replacedp(sso_properties_dlg[135],x_str);
    x_stri=134;
    replacedp(sso_properties_dlg[136],x_str);
    x_stri=136;
    replacedp(sso_properties_dlg[137],x_str);
    x_stri=137;
    replacedp(sso_properties_dlg[138],x_str);
    x_stri=138;
    sso_properties_dlg[142].dp2=spfont;
    sso_properties_dlg[143].dp2=spfont;
    sso_properties_dlg[147].dp2=spfont;
    sso_properties_dlg[151].dp2=spfont;
    sso_properties_dlg[154].dp2=spfont;
    sso_properties_dlg[155].dp2=spfont;
    replacedp(sso_properties_dlg[165],x_str);
    x_stri=165;
    sso_properties_dlg[168].dp2=ss_font(ssfZELDA);
    sso_properties_dlg[168].h=text_height(ss_font(ssfZELDA))+8;
    replacedp(sso_properties_dlg[168],x_str);
    x_stri=168;
    
    if(biic_cnt==-1)
        build_biic_list();
        
    if(is_large && !sso_properties_dlg[0].d1)
    {
        sso_properties_dlg[126].proc = sso_properties_dlg[136].proc = sso_properties_dlg[137].proc =
                                           sso_properties_dlg[138].proc = jwin_droplist_proc; // jwin_edit_proc, but sometimes jwin_droplist_proc
        large_dialog(sso_properties_dlg);
        sso_properties_dlg[126].proc = sso_properties_dlg[136].proc = sso_properties_dlg[137].proc =
                                           sso_properties_dlg[138].proc = jwin_edit_proc;
                                           
        sso_properties_dlg[95].w=(156*2)+1; // d_box_proc
        sso_properties_dlg[95].h=(122*2)+1;
        
        sso_properties_dlg[97].x = sso_properties_dlg[98].x-2; // d_frame_proc
        sso_properties_dlg[97].y = sso_properties_dlg[98].y-2;
        
        for(int i = 99; i <= 104; i++)
            sso_properties_dlg[i].x += (i >=102 ? 80:64);
            
        for(int i = 158; i <= 162; i++)
            sso_properties_dlg[i].y += 8;
            
        sso_properties_dlg[100].x = sso_properties_dlg[101].x-2; // d_frame_proc
        sso_properties_dlg[100].y = sso_properties_dlg[101].y-2;
    }
    
    //item specific
    switch(tempsso->type)
    {
    case ssoNONE:
    {
        // I'd just disable it entirely if I knew how...
        dummy_dialog_proc(sso_properties_dlg+6);
        
        for(int i=11; i<=213; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
    }
    break;
    
    case sso2X2FRAME:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=41; i<=94; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=99; i<=101; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=104; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
//      draw_block_flip(dest,x,y,css->objects[i].d1,subscreen_cset(misc, css->objects[i].colortype1, css->objects[i].color1),css->objects[i].w,css->objects[i].h,css->objects[i].d2,css->objects[i].d3,css->objects[i].d4);
        char cset_caption1[80];
        char cset_caption2[80];
        char scset_caption[80];
        sprintf(cset_caption1, " CSet ");
        sprintf(cset_caption2, "CSet:");
        sprintf(scset_caption, "Type:");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", tempsso->w);
        sprintf(h_str, "%d", tempsso->h);
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        
        
        replacedp(sso_properties_dlg[36],cset_caption1);
        replacedp(sso_properties_dlg[37],cset_caption2);
        
        ListData csettype_list(csettypelist, is_large ? &lfont_l : &font);
        sso_properties_dlg[38].proc=d_csl_proc;
        //A dubious cast, but I think correct -DD
        replacedp(sso_properties_dlg[38],(char *)&csettype_list);
        
        replacedp(sso_properties_dlg[39],scset_caption);
        
        extract_cset(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].proc=d_csl2_proc;
        ListData misccset_list(misccsetlist, is_large? &lfont_l : &font);
        replacedp(sso_properties_dlg[40],(char *)&misccset_list);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_csl_proc(sso_properties_dlg+39, sso_properties_dlg[38].d1);
        //sso_properties_dlg[98].fg=sso_properties_dlg[38].d1?sso_properties_dlg[38].d1-1:sso_properties_dlg[40].d1;
        sso_properties_dlg[98].fg=subscreen_cset(&misc,sso_properties_dlg[38].d1?sso_properties_dlg[38].d1-1:ssctMISC, sso_properties_dlg[40].d1);
        
        sso_properties_dlg[98].d1=tempsso->d1;
        sso_properties_dlg[98].d2=tempsso->d2;
        sso_properties_dlg[98].proc=d_tileblock_proc;
        sso_properties_dlg[98].w=is_large?64:32;
        sso_properties_dlg[98].h=is_large?64:32;
        sso_properties_dlg[97].w=sso_properties_dlg[98].w+4;
        sso_properties_dlg[97].h=sso_properties_dlg[98].h+4;
        sso_properties_dlg[102].flags=tempsso->d3?D_SELECTED:0;
        sso_properties_dlg[103].flags=tempsso->d4?D_SELECTED:0;
    }
    break;
    
    case ssoTEXT:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=53; i<=114; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=123; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char b_color_caption[80];
        sprintf(t_color_caption, " Text Color ");
        sprintf(s_color_caption, " Shadow Color ");
        sprintf(b_color_caption, " Background Color ");
        buf[0]=0;
        
        if(tempsso->dp1!=NULL)
        {
            strcpy(buf, (char *)tempsso->dp1);
        }
        
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[48],b_color_caption);
        
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        extract_colortype(sso_properties_dlg+50, tempsso, 3);
        sso_properties_dlg[52].d1=tempsso->color3;
        update_ctl_proc(sso_properties_dlg+52, sso_properties_dlg[50].d1);
        
        sso_properties_dlg[119].d1=tempsso->d1;
        sso_properties_dlg[120].d1=tempsso->d3;
        sso_properties_dlg[121].d1=tempsso->d2;
        replacedp(sso_properties_dlg[122],buf);
        bufi=122;
        sso_properties_dlg[122].dp2=ss_font(tempsso->d1);
        sso_properties_dlg[122].h=text_height(ss_font(tempsso->d1))+8;
    }
    break;
    
    case ssoLINE:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=41; i<=101; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=104; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char lc_color_caption[80];
        sprintf(lc_color_caption, " Line Color ");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],lc_color_caption);
        
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        sso_properties_dlg[102].flags|=(tempsso->d3)?D_SELECTED:0;
        sso_properties_dlg[103].flags|=(tempsso->d4)?D_SELECTED:0;
    }
    break;
    
    case ssoRECT:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=47; i<=101; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=104; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char ol_color_caption[80];
        char f_color_caption[80];
        char filled_caption[80];
        sprintf(ol_color_caption, " Outline Color ");
        sprintf(f_color_caption, " Fill Color ");
        sprintf(filled_caption, "Filled");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],ol_color_caption);
        replacedp(sso_properties_dlg[42],f_color_caption);
        
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        sso_properties_dlg[102].flags|=(tempsso->d1)?D_SELECTED:0;
        replacedp(sso_properties_dlg[102],filled_caption);
        sso_properties_dlg[103].flags|=(tempsso->d2)?D_SELECTED:0;
    }
    break;
    
    case ssoBSTIME:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=53; i<=114; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        dummy_dialog_proc(sso_properties_dlg+118);
        
        for(int i=122; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char b_color_caption[80];
        sprintf(t_color_caption, " Text Color ");
        sprintf(s_color_caption, " Shadow Color ");
        sprintf(b_color_caption, " Background Color ");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[48],b_color_caption);
        
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        extract_colortype(sso_properties_dlg+50, tempsso, 3);
        sso_properties_dlg[52].d1=tempsso->color3;
        update_ctl_proc(sso_properties_dlg+52, sso_properties_dlg[50].d1);
        
        sso_properties_dlg[119].d1=tempsso->d1;
        sso_properties_dlg[120].d1=tempsso->d3;
        sso_properties_dlg[121].d1=tempsso->d2;
    }
    break;
    
    case ssoTIME:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=53; i<=114; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        dummy_dialog_proc(sso_properties_dlg+118);
        
        for(int i=122; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char b_color_caption[80];
        sprintf(t_color_caption, " Text Color ");
        sprintf(s_color_caption, " Shadow Color ");
        sprintf(b_color_caption, " Background Color ");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[48],b_color_caption);
        
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        extract_colortype(sso_properties_dlg+50, tempsso, 3);
        sso_properties_dlg[52].d1=tempsso->color3;
        update_ctl_proc(sso_properties_dlg+52, sso_properties_dlg[50].d1);
        
        sso_properties_dlg[119].d1=tempsso->d1;
        sso_properties_dlg[120].d1=tempsso->d3;
        sso_properties_dlg[121].d1=tempsso->d2;
    }
    break;
    
    case ssoSSTIME:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=53; i<=114; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        dummy_dialog_proc(sso_properties_dlg+118);
        
        for(int i=122; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char b_color_caption[80];
        sprintf(t_color_caption, " Text Color ");
        sprintf(s_color_caption, " Shadow Color ");
        sprintf(b_color_caption, " Background Color ");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[48],b_color_caption);
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        extract_colortype(sso_properties_dlg+50, tempsso, 3);
        sso_properties_dlg[52].d1=tempsso->color3;
        update_ctl_proc(sso_properties_dlg+52, sso_properties_dlg[50].d1);
        
        sso_properties_dlg[119].d1=tempsso->d1;
        sso_properties_dlg[120].d1=tempsso->d3;
        sso_properties_dlg[121].d1=tempsso->d2;
    }
    break;
    
    case ssoMAGICMETER:
    {
        for(int i=11; i<=93; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=95; i<=169; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=171; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char no_prop[80];
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(no_prop, "No Properties Available");
        
        //Bad! You must use replacedp or you will run into major pointer problems... -DD
        //sso_properties_dlg[8].dp=x_str;
        //sso_properties_dlg[10].dp=y_str;
        //sso_properties_dlg[94].dp=no_prop;
        //sso_properties_dlg[170].dp=no_prop;
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[94],no_prop);
        replacedp(sso_properties_dlg[170],no_prop);
        
    }
    break;
    
    case ssoLIFEMETER:
    {
        for(int i=11; i<=93; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=95; i<=138; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=140; i<=173; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=176; i<=210; i++)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char bs_style[80];
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(bs_style, "BS-Zelda Style");
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[139],bs_style);
        sso_properties_dlg[139].flags=tempsso->d2?D_SELECTED:0;
        sso_properties_dlg[175].d1 = tempsso->d3;
    }
    break;
    
    case ssoBUTTONITEM:
    {
        for(int i=15; i<=102; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=104; i<=114; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=116; i<=118; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=120; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char button_caption[80];
        sprintf(button_caption, "Button:");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        
        sso_properties_dlg[103].flags|=(tempsso->d2)?D_SELECTED:0;
        
        replacedp(sso_properties_dlg[115],button_caption);
        ListData button_list(buttonlist, is_large? &lfont_l : &font);
        replacedp(sso_properties_dlg[119],(char *)&button_list);
        
        sso_properties_dlg[119].d1=tempsso->d1;
    }
    break;
    
    case ssoICON:
    {
    }
    break;
    
    case ssoCOUNTER:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=53; i<=114; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        dummy_dialog_proc(sso_properties_dlg+118);
        dummy_dialog_proc(sso_properties_dlg+122);
        
        for(int i=127; i<=129; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=133; i<=135; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        dummy_dialog_proc(sso_properties_dlg+139);
        
        for(int i=142; i<=166; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=169; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char b_color_caption[80];
        char item_1_caption[80];
        char item_2_caption[80];
        char item_3_caption[80];
        char digits_caption[80];
        char zero_caption[80];
        char selected_caption[80];
        char infinite_caption[80];
        
        sprintf(t_color_caption, " Text Color ");
        sprintf(s_color_caption, " Shadow Color ");
        sprintf(b_color_caption, " Background Color ");
        
        sprintf(item_1_caption, "Item 1:");
        sprintf(item_2_caption, "Item 2:");
        sprintf(item_3_caption, "Item 3:");
        sprintf(infinite_caption, "Infinite:");
        sprintf(digits_caption, "Digits:");
        sprintf(zero_caption, "Show Zero");
        sprintf(selected_caption, "Only Selected");
        
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        
        sprintf(buf, "%d", tempsso->d4);
        sprintf(buf2, "%c", tempsso->d5);
        
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[48],b_color_caption);
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        extract_colortype(sso_properties_dlg+50, tempsso, 3);
        sso_properties_dlg[52].d1=tempsso->color3;
        update_ctl_proc(sso_properties_dlg+52, sso_properties_dlg[50].d1);
        
        sso_properties_dlg[119].d1=tempsso->d1;
        sso_properties_dlg[120].d1=tempsso->d3;
        sso_properties_dlg[121].d1=tempsso->d2;
        replacedp(sso_properties_dlg[123],digits_caption);
        replacedp(sso_properties_dlg[124],infinite_caption);
        
        //why, guys, why?!?? :(
        sso_properties_dlg[125].dp = NULL;
        sso_properties_dlg[125].proc=jwin_edit_proc;
        replacedp(sso_properties_dlg[125],buf);
        bufi = 125;
        sso_properties_dlg[125].d1 = 255;
        sso_properties_dlg[125].x-=8;
        sso_properties_dlg[125].w+=24;
        
        //Infinite Item
        if(bii_cnt==-1)
        {
            build_bii_list(true);
        }
        
        int index=tempsso->d10;
        int itemid = 0;
        
        for(int i=0; i<bii_cnt; i++)
        {
            if(bii[i].i == index)
            {
                itemid = i;
                break;
            }
        }
        
        sso_properties_dlg[126].proc=jwin_droplist_proc;
        replacedp(sso_properties_dlg[126],(char *)&item_list);
        sso_properties_dlg[126].d1=itemid;
        sso_properties_dlg[126].x-=8;
        sso_properties_dlg[126].w+=24;
        
        replacedp(sso_properties_dlg[130],item_1_caption);
        replacedp(sso_properties_dlg[131],item_2_caption);
        replacedp(sso_properties_dlg[132],item_3_caption);
        sso_properties_dlg[136].proc=jwin_droplist_proc;
        ListData icounter_list(icounterlist, is_large ? &lfont_l : &font);
        replacedp(sso_properties_dlg[136],(char *)&icounter_list);
        sso_properties_dlg[136].d1=tempsso->d7;
        sso_properties_dlg[136].x-=13;
        sso_properties_dlg[136].w+=56;
        sso_properties_dlg[137].proc=jwin_droplist_proc;
        replacedp(sso_properties_dlg[137],(char *)&icounter_list);
        sso_properties_dlg[137].d1=tempsso->d8;
        sso_properties_dlg[137].x-=13;
        sso_properties_dlg[137].w+=56;
        sso_properties_dlg[138].proc=jwin_droplist_proc;
        replacedp(sso_properties_dlg[138],(char *)&icounter_list);
        sso_properties_dlg[138].d1=tempsso->d9;
        sso_properties_dlg[138].x-=13;
        sso_properties_dlg[138].w+=56;
        replacedp(sso_properties_dlg[168],buf2);
        buf2i=168;
        sso_properties_dlg[168].dp2=ss_font(tempsso->d1);
        sso_properties_dlg[168].h=text_height(ss_font(tempsso->d1))+8;
        replacedp(sso_properties_dlg[140],zero_caption);
        sso_properties_dlg[140].flags=tempsso->d6&1?D_SELECTED:0;
        sso_properties_dlg[140].x += 40;
        replacedp(sso_properties_dlg[141],selected_caption);
        sso_properties_dlg[141].flags=tempsso->d6&2?D_SELECTED:0;
        sso_properties_dlg[141].x += 40;
        
    }
    break;
    
    case ssoCOUNTERS:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=53; i<=114; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        dummy_dialog_proc(sso_properties_dlg+117);
        dummy_dialog_proc(sso_properties_dlg+118);
        dummy_dialog_proc(sso_properties_dlg+121);
        dummy_dialog_proc(sso_properties_dlg+122);
        dummy_dialog_proc(sso_properties_dlg+123);
        dummy_dialog_proc(sso_properties_dlg+125);
        
        for(int i=127; i<=139; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=141; i<=166; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=169; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char b_color_caption[80];
        char item_caption[80];
        char digits_caption[80];
        char x_caption[80];
        
        sprintf(t_color_caption, " Text Color ");
        sprintf(s_color_caption, " Shadow Color ");
        sprintf(b_color_caption, " Background Color ");
        
        sprintf(item_caption, "Item:");
        sprintf(digits_caption, "Digits:");
        sprintf(x_caption, "Use X");
        
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        
        sprintf(buf, "%d", tempsso->d4);
        sprintf(buf2, "%c", tempsso->d5);
        
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[48],b_color_caption);
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        extract_colortype(sso_properties_dlg+50, tempsso, 3);
        sso_properties_dlg[52].d1=tempsso->color3;
        update_ctl_proc(sso_properties_dlg+52, sso_properties_dlg[50].d1);
        
        sso_properties_dlg[119].d1=tempsso->d1;
        sso_properties_dlg[120].d1=tempsso->d3;
        replacedp(sso_properties_dlg[124],digits_caption);
        replacedp(sso_properties_dlg[126],buf);
        bufi=126;
        sso_properties_dlg[126].x-=8;
        sso_properties_dlg[126].w+=24;
        replacedp(sso_properties_dlg[168],buf2);
        buf2i=168;
        sso_properties_dlg[168].dp2=ss_font(tempsso->d1);
        sso_properties_dlg[168].h=text_height(ss_font(tempsso->d1))+8;
        replacedp(sso_properties_dlg[140],x_caption);
        sso_properties_dlg[140].flags=tempsso->d2?D_SELECTED:0;
        
    }
    break;
    
    case ssoMINIMAPTITLE:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=53; i<=114; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        dummy_dialog_proc(sso_properties_dlg+118);
        
        for(int i=122; i<=210; ++i)
        {
            if(i!=139) dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char b_color_caption[80];
        char map_rule_caption[80];
        sprintf(t_color_caption, " Text Color ");
        sprintf(s_color_caption, " Shadow Color ");
        sprintf(b_color_caption, " Background Color ");
        sprintf(map_rule_caption, "Invisible w/o Dungeon Map");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[48],b_color_caption);
        replacedp(sso_properties_dlg[139],map_rule_caption);
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        extract_colortype(sso_properties_dlg+50, tempsso, 3);
        sso_properties_dlg[52].d1=tempsso->color3;
        update_ctl_proc(sso_properties_dlg+52, sso_properties_dlg[50].d1);
        
        sso_properties_dlg[119].d1=tempsso->d1;
        sso_properties_dlg[120].d1=tempsso->d3;
        sso_properties_dlg[121].d1=tempsso->d2;
        sso_properties_dlg[139].flags=tempsso->d4?D_SELECTED:0;
    }
    break;
    
    case ssoMINIMAP:
    {
        for(int i=11; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=53; i<=170; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=174; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char b_color_caption[80];
        char show1[80];
        char show2[80];
        char show3[80];
        sprintf(t_color_caption, " Link Color ");
        sprintf(s_color_caption, " C. Blink Color ");
        sprintf(b_color_caption, " C. Const Color ");
        sprintf(show1, " Show Map ");
        sprintf(show2, " Show Link ");
        sprintf(show3, " Show Compass ");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[48],b_color_caption);
        replacedp(sso_properties_dlg[171],show1);
        replacedp(sso_properties_dlg[172],show2);
        replacedp(sso_properties_dlg[173],show3);
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        extract_colortype(sso_properties_dlg+50, tempsso, 3);
        sso_properties_dlg[52].d1=tempsso->color3;
        update_ctl_proc(sso_properties_dlg+52, sso_properties_dlg[50].d1);
        
        sso_properties_dlg[171].flags=tempsso->d1?D_SELECTED:0;
        sso_properties_dlg[172].flags=tempsso->d2?D_SELECTED:0;
        sso_properties_dlg[173].flags=tempsso->d3?D_SELECTED:0;
    }
    break;
    
    case ssoLARGEMAP:
    {
        for(int i=11; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=47; i<=138; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=140; i<=170; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=174; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char show1[80];
        char show2[80];
        char show3[80];
        char bs_style[80];
        sprintf(t_color_caption, " Room Color ");
        sprintf(s_color_caption, " Link Color ");
        sprintf(show1, " Show Map ");
        sprintf(show2, " Show Rooms ");
        sprintf(show3, " Show Link ");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(bs_style, "Large");
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[139],bs_style);
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[171],show1);
        replacedp(sso_properties_dlg[172],show2);
        replacedp(sso_properties_dlg[173],show3);
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        sso_properties_dlg[171].flags=tempsso->d1?D_SELECTED:0;
        sso_properties_dlg[172].flags=tempsso->d2?D_SELECTED:0;
        sso_properties_dlg[173].flags=tempsso->d3?D_SELECTED:0;
        
        sso_properties_dlg[139].flags=tempsso->d10?D_SELECTED:0;
    }
    break;
    
    case ssoCLEAR:
    {
        for(int i=7; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=41; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char ss_color_caption[80];
        sprintf(ss_color_caption, " Subscreen Color ");
        replacedp(sso_properties_dlg[36],ss_color_caption);
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
    }
    break;
    
    case ssoCURRENTITEM:
    {
        for(int i=15; i<=93; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=95; i<=126; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=140; i<=175; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=178; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", tempsso->w);
        sprintf(h_str, "%d", tempsso->h);
        
        sprintf(buf,  "%d", tempsso->d3);
        sprintf(buf2, "%d", tempsso->d4);
        sprintf(buf3, "%d", tempsso->d5);
        sprintf(buf4, "%d", tempsso->d6);
        sprintf(buf5, "%d", tempsso->d7);
        
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        
        replacedp(sso_properties_dlg[134],buf);
        bufi=134;
        replacedp(sso_properties_dlg[135],buf2);
        buf2i=135;
        replacedp(sso_properties_dlg[136],buf3);
        buf3i=136;
        replacedp(sso_properties_dlg[137],buf4);
        buf4i=137;
        replacedp(sso_properties_dlg[138],buf5);
        buf5i=138;
        // Item Override droplist
        
        build_bii_list(true);
        int index=tempsso->d8-1;
        int itemid = 0;
        
        for(int i=0; i<bii_cnt; i++)
        {
            if(bii[i].i == index)
            {
                itemid = i;
                break;
            }
        }
        
        sso_properties_dlg[176].proc=jwin_droplist_proc;
        replacedp(sso_properties_dlg[176],(char *)&item_list);
        sso_properties_dlg[176].d1 = itemid;
        
        for(int j=0; j<biic_cnt; j++)
        {
            if(biic[j].i == tempsso->d1)
                sso_properties_dlg[133].d1 = j;
        }
        
        sso_properties_dlg[139].flags=tempsso->d2?0:D_SELECTED;
    }
    break;
    
    case ssoITEM:
    {
    }
    break;
    
    case ssoTRIFRAME:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=47; i<=94; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=105; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char fo_color_caption[80];
        char n_color_caption[80];
        char show_frame_caption[80];
        char show_pieces_caption[80];
        sprintf(fo_color_caption, " Frame Outline Color ");
        sprintf(n_color_caption, " Number Color ");
        sprintf(show_frame_caption, "Show Frame");
        sprintf(show_pieces_caption, "Show Pieces");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],fo_color_caption);
        replacedp(sso_properties_dlg[42],n_color_caption);
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        sso_properties_dlg[98].w=(tempsso->d7?112:96)*(is_large+1);
        sso_properties_dlg[98].h=(tempsso->d7?112:48)*(is_large+1);
        sso_properties_dlg[97].w=sso_properties_dlg[98].w+4;
        sso_properties_dlg[97].h=sso_properties_dlg[98].h+4;
        sso_properties_dlg[98].d1=tempsso->d1;
        sso_properties_dlg[98].fg=tempsso->d2;
        sso_properties_dlg[101].w=(tempsso->d7?32:16)*(is_large+1);
        sso_properties_dlg[101].h=(tempsso->d7?48:16)*(is_large+1);
        sso_properties_dlg[100].w=sso_properties_dlg[101].w+4;
        sso_properties_dlg[100].h=sso_properties_dlg[101].h+4;
        sso_properties_dlg[101].d1=tempsso->d3;
        sso_properties_dlg[101].fg=tempsso->d4;
        replacedp(sso_properties_dlg[102],show_frame_caption);
        sso_properties_dlg[102].flags=tempsso->d5?D_SELECTED:0;
        replacedp(sso_properties_dlg[103],show_pieces_caption);
        sso_properties_dlg[103].flags=tempsso->d6?D_SELECTED:0;
        sso_properties_dlg[104].flags=tempsso->d7?D_SELECTED:0;
    }
    break;
    
    case ssoTRIFORCE:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=41; i<=94; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=99; i<=101; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=104; i<=163; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=166; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char cset_caption1[80];
        char cset_caption2[80];
        char scset_caption[80];
        char piece_caption[80];
        sprintf(cset_caption1, " CSet ");
        sprintf(cset_caption2, "CSet:");
        sprintf(scset_caption, "Type:");
        sprintf(piece_caption, "Piece #:");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", tempsso->w);
        sprintf(h_str, "%d", tempsso->h);
        sprintf(buf, "%d", tempsso->d5);
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        
        replacedp(sso_properties_dlg[36],cset_caption1);
        replacedp(sso_properties_dlg[37],cset_caption2);
        sso_properties_dlg[38].proc=d_csl_proc;
        ListData csettype_list(csettypelist, is_large ? &lfont_l : &font);
        replacedp(sso_properties_dlg[38],(char *)&csettype_list);
        replacedp(sso_properties_dlg[39],scset_caption);
        
        extract_cset(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].proc=d_csl2_proc;
        ListData misccset_list(misccsetlist, is_large ? &lfont_l : &font);
        replacedp(sso_properties_dlg[40],(char *)&misccset_list);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_csl_proc(sso_properties_dlg+39, sso_properties_dlg[38].d1);
        //sso_properties_dlg[98].fg=sso_properties_dlg[38].d1?sso_properties_dlg[38].d1-1:sso_properties_dlg[40].d1;
        sso_properties_dlg[98].fg=subscreen_cset(&misc,sso_properties_dlg[38].d1?sso_properties_dlg[38].d1-1:ssctMISC, sso_properties_dlg[40].d1);
        
        sso_properties_dlg[98].d1=tempsso->d1;
        sso_properties_dlg[98].d2=tempsso->d2;
        sso_properties_dlg[98].w=is_large?32:16;
        sso_properties_dlg[98].h=is_large?32:16;
        sso_properties_dlg[97].w=sso_properties_dlg[98].w+4;
        sso_properties_dlg[97].h=sso_properties_dlg[98].h+4;
        sso_properties_dlg[98].proc=d_tileblock_proc;
        sso_properties_dlg[102].flags=tempsso->d3?D_SELECTED:0;
        sso_properties_dlg[103].flags=tempsso->d4?D_SELECTED:0;
        replacedp(sso_properties_dlg[164],piece_caption);
        replacedp(sso_properties_dlg[165],buf);
        bufi=165;
    }
    break;
    
    case ssoTILEBLOCK:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=41; i<=94; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=99; i<=101; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=104; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
//      draw_block_flip(dest,x,y,css->objects[i].d1,subscreen_cset(misc, css->objects[i].colortype1, css->objects[i].color1),css->objects[i].w,css->objects[i].h,css->objects[i].d2,css->objects[i].d3,css->objects[i].d4);
        char cset_caption1[80];
        char cset_caption2[80];
        char scset_caption[80];
        sprintf(cset_caption1, " CSet ");
        sprintf(cset_caption2, "CSet:");
        sprintf(scset_caption, "Type:");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", tempsso->w);
        sprintf(h_str, "%d", tempsso->h);
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        
        sso_properties_dlg[38].proc=d_csl_proc;
        ListData csettype_list(csettypelist, is_large ? &lfont_l : &font);
        replacedp(sso_properties_dlg[36],cset_caption1);
        replacedp(sso_properties_dlg[37],cset_caption2);
        replacedp(sso_properties_dlg[38],(char *)&csettype_list);
        replacedp(sso_properties_dlg[39],scset_caption);
        
        extract_cset(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].proc=d_csl2_proc;
        ListData misccset_list(misccsetlist, is_large ? &lfont_l : &font);
        replacedp(sso_properties_dlg[40],(char *)&misccset_list);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_csl_proc(sso_properties_dlg+39, sso_properties_dlg[38].d1);
        sso_properties_dlg[98].fg=subscreen_cset(&misc,sso_properties_dlg[38].d1?sso_properties_dlg[38].d1-1:ssctMISC, sso_properties_dlg[40].d1);
        
        sso_properties_dlg[98].d1=tempsso->d1;
        sso_properties_dlg[98].d2=tempsso->d2;
        sso_properties_dlg[98].w=is_large?32:16;
        sso_properties_dlg[98].h=is_large?32:16;
        sso_properties_dlg[97].w=sso_properties_dlg[98].w+4;
        sso_properties_dlg[97].h=sso_properties_dlg[98].h+4;
        sso_properties_dlg[98].proc=d_tileblock_proc;
        sso_properties_dlg[102].flags=tempsso->d3?D_SELECTED:0;
        sso_properties_dlg[103].flags=tempsso->d4?D_SELECTED:0;
    }
    break;
    
    case ssoMINITILE:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=41; i<=94; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=99; i<=101; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=104; i<=110; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=113; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
//      draw_block_flip(dest,x,y,css->objects[i].d1,subscreen_cset(misc, css->objects[i].colortype1, css->objects[i].color1),css->objects[i].w,css->objects[i].h,css->objects[i].d2,css->objects[i].d3,css->objects[i].d4);
        char cset_caption1[80];
        char cset_caption2[80];
        char scset_caption[80];
        sprintf(cset_caption1, " CSet ");
        sprintf(cset_caption2, "CSet:");
        sprintf(scset_caption, "Type:");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", tempsso->w);
        sprintf(h_str, "%d", tempsso->h);
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        
        sso_properties_dlg[38].proc=d_csl_proc;
        ListData csettype_list(csettypelist, is_large ? &lfont_l : &font);
        replacedp(sso_properties_dlg[36],cset_caption1);
        replacedp(sso_properties_dlg[37],cset_caption2);
        replacedp(sso_properties_dlg[38],(char *)&csettype_list);
        replacedp(sso_properties_dlg[39],scset_caption);
        
        
        extract_cset(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].proc=d_csl2_proc;
        ListData misccset_list(misccsetlist, is_large ? &lfont_l : &font);
        replacedp(sso_properties_dlg[40],(char *)&misccset_list);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_csl_proc(sso_properties_dlg+39, sso_properties_dlg[38].d1);
        //sso_properties_dlg[98].fg=sso_properties_dlg[38].d1?sso_properties_dlg[38].d1-1:sso_properties_dlg[40].d1;
        sso_properties_dlg[98].fg=subscreen_cset(&misc,sso_properties_dlg[38].d1?sso_properties_dlg[38].d1-1:ssctMISC, sso_properties_dlg[40].d1);
        
        if(tempsso->d1!=-1)
        {
            sso_properties_dlg[98].d1=tempsso->d1>>2;
            sso_properties_dlg[98].bg=vbound(tempsso->d1-(sso_properties_dlg[98].d1<<2)+tempsso->d3,0,3);
            sso_properties_dlg[112].d1=0;
            sso_properties_dlg[112].d2=0;
            sso_properties_dlg[97].w=20;
            sso_properties_dlg[98].w=16;
        }
        else
        {
            switch(tempsso->d2)
            {
            case ssmstSSVINETILE:
                sso_properties_dlg[98].d1=wpnsbuf[iwSubscreenVine].tile;
                sso_properties_dlg[97].w=52;
                sso_properties_dlg[98].w=48;
                break;
                
            case ssmstMAGICMETER:
                sso_properties_dlg[98].d1=wpnsbuf[iwMMeter].tile;
                sso_properties_dlg[97].w=148;
                sso_properties_dlg[98].w=144;
                break;
                
            default:
                sso_properties_dlg[97].w=20;
                sso_properties_dlg[98].w=16;
            }
            
            sso_properties_dlg[98].bg=tempsso->d3;
            sso_properties_dlg[112].d1=tempsso->d2+1;
            sso_properties_dlg[112].d2=sso_properties_dlg[112].d1;
        }
        
        sso_properties_dlg[98].w*=(is_large?2:1);
        sso_properties_dlg[97].w=sso_properties_dlg[98].w+4;
        sso_properties_dlg[98].h=is_large?32:16;
        sso_properties_dlg[97].h=sso_properties_dlg[98].h+4;
        sso_properties_dlg[98].d2=tempsso->d4;
        sso_properties_dlg[98].proc=d_spectile_proc;
        sso_properties_dlg[102].flags=tempsso->d5?D_SELECTED:0;
        sso_properties_dlg[103].flags=tempsso->d6?D_SELECTED:0;
    }
    break;
    
    case ssoSELECTOR1:
    case ssoSELECTOR2:
    {
        for(int i=11; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=41; i<=94; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=99; i<=101; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=105; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
//      draw_block_flip(dest,x,y,css->objects[i].d1,subscreen_cset(misc, css->objects[i].colortype1, css->objects[i].color1),css->objects[i].w,css->objects[i].h,css->objects[i].d2,css->objects[i].d3,css->objects[i].d4);
        char cset_caption1[80];
        char cset_caption2[80];
        char scset_caption[80];
        char large_caption[80];
        sprintf(cset_caption1, " CSet ");
        sprintf(cset_caption2, "CSet:");
        sprintf(scset_caption, "Type:");
        sprintf(large_caption, "Large");
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        
        ListData csettype_list(csettypelist, is_large ? &lfont_l : &font);
        sso_properties_dlg[38].proc=d_csl_proc;
        replacedp(sso_properties_dlg[36],cset_caption1);
        replacedp(sso_properties_dlg[37],cset_caption2);
        replacedp(sso_properties_dlg[38],(char *)&csettype_list);
        replacedp(sso_properties_dlg[39],scset_caption);
        
        extract_cset(sso_properties_dlg+38, tempsso, 1);
        ListData misccset_list(misccsetlist,is_large ? &lfont_l : &font);
        sso_properties_dlg[40].proc=d_csl2_proc;
        replacedp(sso_properties_dlg[40],(char *)&misccset_list);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_csl_proc(sso_properties_dlg+39, sso_properties_dlg[38].d1);
        //sso_properties_dlg[98].fg=sso_properties_dlg[38].d1?sso_properties_dlg[38].d1-1:sso_properties_dlg[40].d1;
        sso_properties_dlg[98].fg=subscreen_cset(&misc,sso_properties_dlg[38].d1?sso_properties_dlg[38].d1-1:ssctMISC, sso_properties_dlg[40].d1);
        
        sso_properties_dlg[98].d1=tempsso->d1;
        sso_properties_dlg[98].d2=tempsso->d2;
        sso_properties_dlg[98].proc=d_tileblock_proc;
        sso_properties_dlg[98].w=is_large?64:32;
        sso_properties_dlg[98].h=is_large?64:32;
        sso_properties_dlg[97].w=sso_properties_dlg[98].w+4;
        sso_properties_dlg[97].h=sso_properties_dlg[98].h+4;
        sso_properties_dlg[102].flags=tempsso->d3?D_SELECTED:0;
        sso_properties_dlg[103].flags=tempsso->d4?D_SELECTED:0;
        replacedp(sso_properties_dlg[104],large_caption);
        sso_properties_dlg[104].proc=jwin_lscheck_proc;
        sso_properties_dlg[104].flags=tempsso->d5?D_SELECTED:0;
    }
    break;
    
    case ssoMAGICGAUGE:
    {
        for(int i=15; i<=93; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=95; i<=104; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=111; i<=141; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=167; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        
        sprintf(f_str, "%d", tempsso->d6);
        sprintf(s_str, "%d", tempsso->d7);
        sprintf(d_str, "%d", tempsso->d8);
        // container
        sprintf(buf, "%d", tempsso->d1);
        
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        
        replacedp(sso_properties_dlg[108],f_str);
        f_stri=108;
        replacedp(sso_properties_dlg[109],s_str);
        s_stri=109;
        replacedp(sso_properties_dlg[110],d_str);
        d_stri=110;
        
        sso_properties_dlg[145].d1=(tempsso->d2)>>2;
        sso_properties_dlg[145].d2=0;
        sso_properties_dlg[145].fg=tempsso->colortype1;
        sso_properties_dlg[145].bg=(tempsso->d2)%4;
        sso_properties_dlg[144].w = sso_properties_dlg[145].w+4;
        sso_properties_dlg[144].h = sso_properties_dlg[145].h+4;
        sso_properties_dlg[144].x = sso_properties_dlg[145].x-3;
        sso_properties_dlg[144].y = sso_properties_dlg[145].y-3;
        
        sso_properties_dlg[149].d1=(tempsso->d3)>>2;
        sso_properties_dlg[149].d2=0;
        sso_properties_dlg[149].fg=tempsso->color1;
        sso_properties_dlg[149].bg=(tempsso->d3)%4;
        sso_properties_dlg[148].w = sso_properties_dlg[149].w+4;
        sso_properties_dlg[148].h = sso_properties_dlg[149].h+4;
        sso_properties_dlg[148].x = sso_properties_dlg[149].x-3;
        sso_properties_dlg[148].y = sso_properties_dlg[149].y-3;
        
        sso_properties_dlg[153].d1=(tempsso->d4)>>2;
        sso_properties_dlg[153].d2=0;
        sso_properties_dlg[153].fg=tempsso->colortype2;
        sso_properties_dlg[153].bg=(tempsso->d4)%4;
        sso_properties_dlg[152].w = sso_properties_dlg[153].w+4;
        sso_properties_dlg[152].h = sso_properties_dlg[153].h+4;
        sso_properties_dlg[152].x = sso_properties_dlg[153].x-3;
        sso_properties_dlg[152].y = sso_properties_dlg[153].y-3;
        
        sso_properties_dlg[157].d1=(tempsso->d5)>>2;
        sso_properties_dlg[157].d2=0;
        sso_properties_dlg[157].fg=tempsso->color2;
        sso_properties_dlg[157].bg=(tempsso->d5)%4;
        sso_properties_dlg[156].w = sso_properties_dlg[157].w+4;
        sso_properties_dlg[156].h = sso_properties_dlg[157].h+4;
        sso_properties_dlg[156].x = sso_properties_dlg[157].x-3;
        sso_properties_dlg[156].y = sso_properties_dlg[157].y-3;
        
        sso_properties_dlg[158].flags=((tempsso->d10)&1)?D_SELECTED:0;
        sso_properties_dlg[159].flags=((tempsso->d10)&2)?D_SELECTED:0;
        sso_properties_dlg[160].flags=((tempsso->d10)&4)?D_SELECTED:0;
        sso_properties_dlg[161].flags=((tempsso->d10)&8)?D_SELECTED:0;
        sso_properties_dlg[163].d1=tempsso->d9;
        replacedp(sso_properties_dlg[165],buf);
        bufi=165;
        sso_properties_dlg[166].flags=((tempsso->d10)&16)?D_SELECTED:0;
    }
    break;
    
    case ssoLIFEGAUGE:
    {
        for(int i=15; i<=93; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=95; i<=104; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=111; i<=141; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=167; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        
        sprintf(f_str, "%d", tempsso->d6);
        sprintf(s_str, "%d", tempsso->d7);
        sprintf(d_str, "%d", tempsso->d8);
        // container
        sprintf(buf, "%d", tempsso->d1);
        
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        
        replacedp(sso_properties_dlg[108],f_str);
        f_stri=108;
        replacedp(sso_properties_dlg[109],s_str);
        s_stri=109;
        replacedp(sso_properties_dlg[110],d_str);
        d_stri=110;
        
        sso_properties_dlg[145].d1=(tempsso->d2)>>2;
        sso_properties_dlg[145].d2=0;
        sso_properties_dlg[145].fg=tempsso->colortype1;
        sso_properties_dlg[145].bg=(tempsso->d2)%4;
        sso_properties_dlg[144].w = sso_properties_dlg[145].w+4;
        sso_properties_dlg[144].h = sso_properties_dlg[145].h+4;
        sso_properties_dlg[144].x = sso_properties_dlg[145].x-3;
        sso_properties_dlg[144].y = sso_properties_dlg[145].y-3;
        
        sso_properties_dlg[149].d1=(tempsso->d3)>>2;
        sso_properties_dlg[149].d2=0;
        sso_properties_dlg[149].fg=tempsso->color1;
        sso_properties_dlg[149].bg=(tempsso->d3)%4;
        sso_properties_dlg[148].w = sso_properties_dlg[149].w+4;
        sso_properties_dlg[148].h = sso_properties_dlg[149].h+4;
        sso_properties_dlg[148].x = sso_properties_dlg[149].x-3;
        sso_properties_dlg[148].y = sso_properties_dlg[149].y-3;
        
        sso_properties_dlg[153].d1=(tempsso->d4)>>2;
        sso_properties_dlg[153].d2=0;
        sso_properties_dlg[153].fg=tempsso->colortype2;
        sso_properties_dlg[153].bg=(tempsso->d4)%4;
        sso_properties_dlg[152].w = sso_properties_dlg[153].w+4;
        sso_properties_dlg[152].h = sso_properties_dlg[153].h+4;
        sso_properties_dlg[152].x = sso_properties_dlg[153].x-3;
        sso_properties_dlg[152].y = sso_properties_dlg[153].y-3;
        
        sso_properties_dlg[157].d1=(tempsso->d5)>>2;
        sso_properties_dlg[157].d2=0;
        sso_properties_dlg[157].fg=tempsso->color2;
        sso_properties_dlg[157].bg=(tempsso->d5)%4;
        sso_properties_dlg[156].w = sso_properties_dlg[157].w+4;
        sso_properties_dlg[156].h = sso_properties_dlg[157].h+4;
        sso_properties_dlg[156].x = sso_properties_dlg[157].x-3;
        sso_properties_dlg[156].y = sso_properties_dlg[157].y-3;
        
        sso_properties_dlg[158].flags=((tempsso->d10)&1)?D_SELECTED:0;
        sso_properties_dlg[159].flags=((tempsso->d10)&2)?D_SELECTED:0;
        sso_properties_dlg[160].flags=((tempsso->d10)&4)?D_SELECTED:0;
        sso_properties_dlg[161].flags=((tempsso->d10)&8)?D_SELECTED:0;
        sso_properties_dlg[163].d1=tempsso->d9;
        replacedp(sso_properties_dlg[165],buf);
        bufi=165;
        sso_properties_dlg[166].flags=((tempsso->d10)&16)?D_SELECTED:0;
    }
    break;
    
    case ssoTEXTBOX:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=53; i<=114; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=127; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char b_color_caption[80];
        sprintf(t_color_caption, " Text Color ");
        sprintf(s_color_caption, " Shadow Color ");
        sprintf(b_color_caption, " Background Color ");
        strcpy(buf, (char *)tempsso->dp1);
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", tempsso->w);
        sprintf(h_str, "%d", tempsso->h);
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[48],b_color_caption);
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        extract_colortype(sso_properties_dlg+50, tempsso, 3);
        sso_properties_dlg[52].d1=tempsso->color3;
        update_ctl_proc(sso_properties_dlg+52, sso_properties_dlg[50].d1);
        
        sso_properties_dlg[119].d1=tempsso->d1;
        sso_properties_dlg[120].d1=tempsso->d3;
        sso_properties_dlg[121].d1=tempsso->d2;
        replacedp(sso_properties_dlg[122],buf);
        bufi=122;
        sso_properties_dlg[122].dp2=ss_font(tempsso->d1);
        sso_properties_dlg[122].h=text_height(ss_font(tempsso->d1))+8;
        sso_properties_dlg[125].d1=tempsso->d4;
        sprintf(buf2, "%d", tempsso->d5);
        replacedp(sso_properties_dlg[126],buf2);
        buf2i=126;
    }
    break;
    
    case ssoCURRENTITEMTILE:
    {
    }
    break;
    
    case ssoSELECTEDITEMTILE:
    {
    }
    break;
    
    case ssoCURRENTITEMTEXT:
    {
    }
    break;
    
    case ssoCURRENTITEMNAME:
    {
    }
    break;
    
    case ssoSELECTEDITEMNAME:
    {
        for(int i=15; i<=34; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=53; i<=114; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        for(int i=127; i<=210; ++i)
        {
            dummy_dialog_proc(sso_properties_dlg+i);
        }
        
        char t_color_caption[80];
        char s_color_caption[80];
        char b_color_caption[80];
        sprintf(t_color_caption, " Text Color ");
        sprintf(s_color_caption, " Shadow Color ");
        sprintf(b_color_caption, " Background Color ");
        buf[0]=0;
        sprintf(x_str, "%d", tempsso->x);
        sprintf(y_str, "%d", tempsso->y);
        sprintf(w_str, "%d", sso_w(tempsso));
        sprintf(h_str, "%d", sso_h(tempsso));
        replacedp(sso_properties_dlg[8],x_str);
        x_stri=8;
        replacedp(sso_properties_dlg[10],y_str);
        y_stri=10;
        replacedp(sso_properties_dlg[12],w_str);
        w_stri=12;
        replacedp(sso_properties_dlg[14],h_str);
        h_stri=14;
        replacedp(sso_properties_dlg[36],t_color_caption);
        replacedp(sso_properties_dlg[42],s_color_caption);
        replacedp(sso_properties_dlg[48],b_color_caption);
        
        extract_colortype(sso_properties_dlg+38, tempsso, 1);
        sso_properties_dlg[40].d1=tempsso->color1;
        update_ctl_proc(sso_properties_dlg+40, sso_properties_dlg[38].d1);
        
        extract_colortype(sso_properties_dlg+44, tempsso, 2);
        sso_properties_dlg[46].d1=tempsso->color2;
        update_ctl_proc(sso_properties_dlg+46, sso_properties_dlg[44].d1);
        
        extract_colortype(sso_properties_dlg+50, tempsso, 3);
        sso_properties_dlg[52].d1=tempsso->color3;
        update_ctl_proc(sso_properties_dlg+52, sso_properties_dlg[50].d1);
        
        sso_properties_dlg[119].d1=tempsso->d1;
        sso_properties_dlg[120].d1=tempsso->d3;
        sso_properties_dlg[121].d1=tempsso->d2;
        replacedp(sso_properties_dlg[122],buf);
        bufi=122;
        sso_properties_dlg[122].dp2=ss_font(tempsso->d1);
        sso_properties_dlg[122].h=text_height(ss_font(tempsso->d1))+8;
        sso_properties_dlg[125].d1=tempsso->d4;
        sprintf(buf2, "%d", tempsso->d5);
        replacedp(sso_properties_dlg[126],buf2);
        buf2i=126;
    }
    break;
    
    case ssoCURRENTITEMCLASSTEXT:
    {
    }
    break;
    
    case ssoCURRENTITEMCLASSNAME:
    {
    }
    break;
    
    case ssoSELECTEDITEMCLASSNAME:
    {
    }
    break;
    
    default:
    {
    }
    break;
    }
    
    ret=zc_popup_dialog(sso_properties_dlg,2);
    
    //Bad idea
    //leaks memory -DD
    /*if (ret==2)
    {
      return -1;
    }*/
    
    if(ret != 2)
    {
        //for everything
        tempsso->pos = 0;
        
        if((sso_properties_dlg[6].flags & D_SELECTED) != 0)
            tempsso->pos |= sspUP;
            
        if((sso_properties_dlg[212].flags & D_SELECTED) != 0)
            tempsso->pos |= sspDOWN;
            
        if((sso_properties_dlg[213].flags & D_SELECTED) != 0)
            tempsso->pos |= sspSCROLLING;
            
        //item specific
        switch(tempsso->type)
        {
        case ssoNONE:
        {
        }
        break;
        
        case sso2X2FRAME:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            
            insert_cset(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            tempsso->d1=sso_properties_dlg[98].d1;
            tempsso->d2=sso_properties_dlg[98].d2;
            tempsso->d3=sso_properties_dlg[102].flags&D_SELECTED?1:0;
            tempsso->d4=sso_properties_dlg[103].flags&D_SELECTED?1:0;
        }
        break;
        
        case ssoTEXT:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            insert_colortype(sso_properties_dlg+50, tempsso, 3);
            tempsso->color3=sso_properties_dlg[52].d1;
            
            tempsso->d1=sso_properties_dlg[119].d1;
            tempsso->d3=sso_properties_dlg[120].d1;
            tempsso->d2=sso_properties_dlg[121].d1;
            
            if(tempsso->dp1!=NULL)
            {
                //zc_free((char *)(tempsso->dp1));
                delete[]((char *)(tempsso->dp1));
            }
            
            //(tempsso->dp1)=(char *)zc_malloc(strlen((char *)sso_properties_dlg[bufi].dp)+1);
            tempsso->dp1 = new char[strlen((char *)sso_properties_dlg[bufi].dp)+1];
            strcpy((char *)tempsso->dp1, (char *)sso_properties_dlg[bufi].dp);
        }
        break;
        
        case ssoLINE:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            tempsso->d1=(sso_properties_dlg[102].flags&D_SELECTED)?1:0;
            tempsso->d2=(sso_properties_dlg[103].flags&D_SELECTED)?1:0;
        }
        break;
        
        case ssoRECT:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            tempsso->d1=(sso_properties_dlg[102].flags&D_SELECTED)?1:0;
            tempsso->d2=(sso_properties_dlg[103].flags&D_SELECTED)?1:0;
        }
        break;
        
        case ssoBSTIME:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            insert_colortype(sso_properties_dlg+50, tempsso, 3);
            tempsso->color3=sso_properties_dlg[52].d1;
            
            tempsso->d1=sso_properties_dlg[119].d1;
            tempsso->d3=sso_properties_dlg[120].d1;
            tempsso->d2=sso_properties_dlg[121].d1;
        }
        break;
        
        case ssoTIME:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            insert_colortype(sso_properties_dlg+50, tempsso, 3);
            tempsso->color3=sso_properties_dlg[52].d1;
            
            tempsso->d1=sso_properties_dlg[119].d1;
            tempsso->d3=sso_properties_dlg[120].d1;
            tempsso->d2=sso_properties_dlg[121].d1;
        }
        break;
        
        case ssoSSTIME:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            insert_colortype(sso_properties_dlg+50, tempsso, 3);
            tempsso->color3=sso_properties_dlg[52].d1;
            
            tempsso->d1=sso_properties_dlg[119].d1;
            tempsso->d3=sso_properties_dlg[120].d1;
            tempsso->d2=sso_properties_dlg[121].d1;
        }
        break;
        
        case ssoMAGICMETER:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
        }
        break;
        
        case ssoLIFEMETER:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->d2=(sso_properties_dlg[139].flags&D_SELECTED)?1:0;
            tempsso->d3= sso_properties_dlg[175].d1;
        }
        break;
        
        case ssoBUTTONITEM:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            tempsso->d2=(sso_properties_dlg[103].flags&D_SELECTED)?1:0;
            tempsso->d1=sso_properties_dlg[119].d1;
        }
        break;
        
        case ssoICON:
        {
        }
        break;
        
        case ssoCOUNTER:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            insert_colortype(sso_properties_dlg+50, tempsso, 3);
            tempsso->color3=sso_properties_dlg[52].d1;
            
            tempsso->d1=sso_properties_dlg[119].d1;
            tempsso->d3=sso_properties_dlg[120].d1;
            tempsso->d2=sso_properties_dlg[121].d1;
            
            tempsso->d4=atoi((char *)sso_properties_dlg[bufi].dp);
            tempsso->d5=((char *)sso_properties_dlg[buf2i].dp)[0];
            tempsso->d6=(sso_properties_dlg[140].flags&D_SELECTED?1:0)+(sso_properties_dlg[141].flags&D_SELECTED?2:0);
            tempsso->d7=sso_properties_dlg[136].d1;
            tempsso->d8=sso_properties_dlg[137].d1;
            tempsso->d9=sso_properties_dlg[138].d1;
            tempsso->d10=bii[sso_properties_dlg[126].d1].i;
        }
        break;
        
        case ssoCOUNTERS:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            insert_colortype(sso_properties_dlg+50, tempsso, 3);
            tempsso->color3=sso_properties_dlg[52].d1;
            
            tempsso->d1=sso_properties_dlg[119].d1;
            tempsso->d3=sso_properties_dlg[120].d1;
            
            tempsso->d4=atoi((char *)sso_properties_dlg[bufi].dp);
            tempsso->d5=((char *)sso_properties_dlg[buf2i].dp)[0];
            tempsso->d2=sso_properties_dlg[140].flags&D_SELECTED?1:0;
        }
        break;
        
        case ssoMINIMAPTITLE:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            insert_colortype(sso_properties_dlg+50, tempsso, 3);
            tempsso->color3=sso_properties_dlg[52].d1;
            
            tempsso->d1=sso_properties_dlg[119].d1;
            tempsso->d3=sso_properties_dlg[120].d1;
            tempsso->d2=sso_properties_dlg[121].d1;
            tempsso->d4=(sso_properties_dlg[139].flags&D_SELECTED)?1:0;
        }
        break;
        
        case ssoMINIMAP:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            insert_colortype(sso_properties_dlg+50, tempsso, 3);
            tempsso->color3=sso_properties_dlg[52].d1;
            
            tempsso->d1=(sso_properties_dlg[171].flags&D_SELECTED)?1:0;
            tempsso->d2=(sso_properties_dlg[172].flags&D_SELECTED)?1:0;
            tempsso->d3=(sso_properties_dlg[173].flags&D_SELECTED)?1:0;
        }
        break;
        
        case ssoLARGEMAP:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            tempsso->d1=(sso_properties_dlg[171].flags&D_SELECTED)?1:0;
            tempsso->d2=(sso_properties_dlg[172].flags&D_SELECTED)?1:0;
            tempsso->d3=(sso_properties_dlg[173].flags&D_SELECTED)?1:0;
            tempsso->d10=(sso_properties_dlg[139].flags&D_SELECTED)?1:0;
        }
        break;
        
        case ssoCLEAR:
        {
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
        }
        break;
        
        case ssoCURRENTITEM:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            tempsso->d3=atoi((char *)sso_properties_dlg[bufi].dp);
            tempsso->d4=atoi((char *)sso_properties_dlg[buf2i].dp);
            tempsso->d5=atoi((char *)sso_properties_dlg[buf3i].dp);
            tempsso->d6=atoi((char *)sso_properties_dlg[buf4i].dp);
            tempsso->d7=atoi((char *)sso_properties_dlg[buf5i].dp);
            tempsso->d8=vbound(bii[sso_properties_dlg[176].d1].i+1, 0, 255);
            
            tempsso->d1=vbound(biic[sso_properties_dlg[133].d1].i, 0, 255);
            tempsso->d2=sso_properties_dlg[139].flags&D_SELECTED?0:1;
            tempsso->d8=vbound(tempsso->d8,0,256);
        }
        break;
        
        case ssoITEM:
        {
        }
        break;
        
        case ssoTRIFRAME:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            tempsso->d1=sso_properties_dlg[98].d1;
            tempsso->d2=sso_properties_dlg[98].fg;
            tempsso->d3=sso_properties_dlg[101].d1;
            tempsso->d4=sso_properties_dlg[101].fg;
            tempsso->d5=(sso_properties_dlg[102].flags&D_SELECTED)?1:0;
            tempsso->d6=(sso_properties_dlg[103].flags&D_SELECTED)?1:0;
            tempsso->d7=(sso_properties_dlg[104].flags&D_SELECTED)?1:0;
        }
        break;
        
        case ssoTRIFORCE:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            
            insert_cset(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            tempsso->d1=sso_properties_dlg[98].d1;
            tempsso->d2=sso_properties_dlg[98].d2;
            tempsso->d3=sso_properties_dlg[102].flags&D_SELECTED?1:0;
            tempsso->d4=sso_properties_dlg[103].flags&D_SELECTED?1:0;
            tempsso->d5=atoi((char *)sso_properties_dlg[bufi].dp);
        }
        break;
        
        case ssoTILEBLOCK:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            
            insert_cset(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            tempsso->d1=sso_properties_dlg[98].d1;
            tempsso->d2=sso_properties_dlg[98].d2;
            tempsso->d3=sso_properties_dlg[102].flags&D_SELECTED?1:0;
            tempsso->d4=sso_properties_dlg[103].flags&D_SELECTED?1:0;
        }
        break;
        
        case ssoMINITILE:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_cset(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            switch(sso_properties_dlg[112].d1-1)
            {
            case ssmstSSVINETILE:
            case ssmstMAGICMETER:
                tempsso->d1=-1;
                tempsso->d2=sso_properties_dlg[112].d1-1;
                tempsso->d3=sso_properties_dlg[98].bg;
                break;
                
            case -1:
            default:
                tempsso->d1=(sso_properties_dlg[98].d1<<2)+sso_properties_dlg[98].bg;
                tempsso->d2=0;
                tempsso->d3=0;
                break;
            }
            
            tempsso->d4=sso_properties_dlg[98].d2;
            tempsso->d5=sso_properties_dlg[102].flags&D_SELECTED?1:0;
            tempsso->d6=sso_properties_dlg[103].flags&D_SELECTED?1:0;
        }
        break;
        
        case ssoSELECTOR1:
        case ssoSELECTOR2:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            //tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            //tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            
            insert_cset(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            tempsso->d1=sso_properties_dlg[98].d1;
            tempsso->d2=sso_properties_dlg[98].d2;
            tempsso->d3=sso_properties_dlg[102].flags&D_SELECTED?1:0;
            tempsso->d4=sso_properties_dlg[103].flags&D_SELECTED?1:0;
            tempsso->d5=sso_properties_dlg[104].flags&D_SELECTED?1:0;
        }
        break;
        
        case ssoMAGICGAUGE:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            tempsso->d6=atoi((char *)sso_properties_dlg[f_stri].dp);
            tempsso->d7=atoi((char *)sso_properties_dlg[s_stri].dp);
            tempsso->d8=atoi((char *)sso_properties_dlg[d_stri].dp);
            
            tempsso->d2=(sso_properties_dlg[145].d1<<2)+sso_properties_dlg[145].bg;
            tempsso->colortype1=sso_properties_dlg[145].fg;
            
            tempsso->d3=(sso_properties_dlg[149].d1<<2)+sso_properties_dlg[149].bg;
            tempsso->color1=sso_properties_dlg[149].fg;
            
            tempsso->d4=(sso_properties_dlg[153].d1<<2)+sso_properties_dlg[153].bg;
            tempsso->colortype2=sso_properties_dlg[153].fg;
            
            tempsso->d5=(sso_properties_dlg[157].d1<<2)+sso_properties_dlg[157].bg;
            tempsso->color2=sso_properties_dlg[157].fg;
            
            tempsso->d10=((sso_properties_dlg[158].flags&D_SELECTED)?1:0)+
                         ((sso_properties_dlg[159].flags&D_SELECTED)?2:0)+
                         ((sso_properties_dlg[160].flags&D_SELECTED)?4:0)+
                         ((sso_properties_dlg[161].flags&D_SELECTED)?8:0)+
                         ((sso_properties_dlg[166].flags&D_SELECTED)?16:0);
                         
            tempsso->d9=sso_properties_dlg[163].d1;
            tempsso->d1=atoi((char *)sso_properties_dlg[bufi].dp);
        }
        break;
        
        case ssoLIFEGAUGE:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            tempsso->d6=atoi((char *)sso_properties_dlg[f_stri].dp);
            tempsso->d7=atoi((char *)sso_properties_dlg[s_stri].dp);
            tempsso->d8=atoi((char *)sso_properties_dlg[d_stri].dp);
            
            tempsso->d2=(sso_properties_dlg[145].d1<<2)+sso_properties_dlg[145].bg;
            tempsso->colortype1=sso_properties_dlg[145].fg;
            
            tempsso->d3=(sso_properties_dlg[149].d1<<2)+sso_properties_dlg[149].bg;
            tempsso->color1=sso_properties_dlg[149].fg;
            
            tempsso->d4=(sso_properties_dlg[153].d1<<2)+sso_properties_dlg[153].bg;
            tempsso->colortype2=sso_properties_dlg[153].fg;
            
            tempsso->d5=(sso_properties_dlg[157].d1<<2)+sso_properties_dlg[157].bg;
            tempsso->color2=sso_properties_dlg[157].fg;
            
            tempsso->d10=((sso_properties_dlg[158].flags&D_SELECTED)?1:0)+
                         ((sso_properties_dlg[159].flags&D_SELECTED)?2:0)+
                         ((sso_properties_dlg[160].flags&D_SELECTED)?4:0)+
                         ((sso_properties_dlg[161].flags&D_SELECTED)?8:0)+
                         ((sso_properties_dlg[166].flags&D_SELECTED)?16:0);
                         
            tempsso->d9=sso_properties_dlg[163].d1;
            tempsso->d1=atoi((char *)sso_properties_dlg[bufi].dp);
        }
        break;
        
        case ssoTEXTBOX:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            insert_colortype(sso_properties_dlg+50, tempsso, 3);
            tempsso->color3=sso_properties_dlg[52].d1;
            
            tempsso->d1=sso_properties_dlg[119].d1;
            tempsso->d3=sso_properties_dlg[120].d1;
            tempsso->d2=sso_properties_dlg[121].d1;
            
            if(tempsso->dp1!=NULL)
            {
                //zc_free((char *)(tempsso->dp1));
                delete[]((char *)(tempsso->dp1));
            }
            
            //(tempsso->dp1)=(char *)zc_malloc(strlen((char *)sso_properties_dlg[bufi].dp)+1);
            tempsso->dp1 = new char[strlen((char *)sso_properties_dlg[bufi].dp)+1];
            strcpy((char *)tempsso->dp1, (char *)sso_properties_dlg[bufi].dp);
            tempsso->d4=sso_properties_dlg[125].d1;
            tempsso->d5=atoi((char *)sso_properties_dlg[buf2i].dp);
        }
        break;
        
        case ssoCURRENTITEMTILE:
        {
        }
        break;
        
        case ssoSELECTEDITEMTILE:
        {
        }
        break;
        
        case ssoCURRENTITEMTEXT:
        {
        }
        break;
        
        case ssoCURRENTITEMNAME:
        {
        }
        break;
        
        case ssoSELECTEDITEMNAME:
        {
            tempsso->x=atoi((char *)sso_properties_dlg[x_stri].dp);
            tempsso->y=atoi((char *)sso_properties_dlg[y_stri].dp);
            tempsso->w=atoi((char *)sso_properties_dlg[w_stri].dp);
            tempsso->h=atoi((char *)sso_properties_dlg[h_stri].dp);
            
            insert_colortype(sso_properties_dlg+38, tempsso, 1);
            tempsso->color1=sso_properties_dlg[40].d1;
            
            insert_colortype(sso_properties_dlg+44, tempsso, 2);
            tempsso->color2=sso_properties_dlg[46].d1;
            
            insert_colortype(sso_properties_dlg+50, tempsso, 3);
            tempsso->color3=sso_properties_dlg[52].d1;
            
            tempsso->d1=sso_properties_dlg[119].d1;
            tempsso->d3=sso_properties_dlg[120].d1;
            tempsso->d2=sso_properties_dlg[121].d1;
            tempsso->d4=sso_properties_dlg[125].d1;
            tempsso->d5=atoi((char *)sso_properties_dlg[buf2i].dp);
        }
        break;
        
        case ssoCURRENTITEMCLASSTEXT:
        {
        }
        break;
        
        case ssoCURRENTITEMCLASSNAME:
        {
        }
        break;
        
        case ssoSELECTEDITEMCLASSNAME:
        {
        }
        break;
        
        default:
        {
        }
        break;
        }
        
    }
    
    free_dialog(&sso_properties_dlg);
    //for(map<int, char *>::iterator it = itemclassnames.begin(); it != itemclassnames.end(); it++)
    //  delete[] it->second;
    //itemclassnames.clear();
    return (ret==2) ? -1 : 0;
}

int onBringToFront();
int onBringForward();
int onSendBackward();
int onSendToBack();
int onReverseArrangement();
int onAlignLeft();
int onAlignCenter();
int onAlignRight();
int onAlignTop();
int onAlignMiddle();
int onAlignBottom();
int onDistributeLeft();
int onDistributeCenter();
int onDistributeRight();
int onDistributeTop();
int onDistributeMiddle();
int onDistributeBottom();
int onGridSnapLeft();
int onGridSnapCenter();
int onGridSnapRight();
int onGridSnapTop();
int onGridSnapMiddle();
int onGridSnapBottom();
void copySSOProperties(subscreen_object& src, subscreen_object& dest);

int onSubscreenObjectProperties()
{
    if(curr_subscreen_object >= 0)
    {
        if(sso_properties(&(css->objects[curr_subscreen_object]))!=-1)
        {
            for(int i=0; i<MAXSUBSCREENITEMS; i++)
            {
                if(!sso_selection[i])
                    continue;
                
                copySSOProperties(css->objects[curr_subscreen_object], css->objects[i]);
            }
        }
    }
    
    return D_O_K;
}

int onSubscreenObjectRawProperties()
{
    if(curr_subscreen_object >= 0)
    {
        sso_raw_data(&(css->objects[curr_subscreen_object]));
    }
    
    return D_O_K;
}

int onNewSubscreenObject();

int onDeleteSubscreenObject()
{
    int objs=ss_objects(css);
    
    if(objs==0)
    {
        return D_O_K;
    }
    
    for(int i=curr_subscreen_object; i<objs-1; ++i)
    {
        css->objects[i]=css->objects[i+1];
        sso_selection[i]=sso_selection[i+1];
    }
    
    if(css->objects[objs-1].dp1!=NULL)
    {
        //No, don't do this.  css->objects[objs-2] is pointing at this.  Leave it be.
        //delete [] (char *)css->objects[objs-1].dp1;
        css->objects[objs-1].dp1=NULL;
    }
    
    css->objects[objs-1].type=ssoNULL;
    sso_selection[objs-1]=false;
    
    if(propCopySrc==curr_subscreen_object)
        propCopySrc=-1;
    else if(propCopySrc>curr_subscreen_object)
        propCopySrc--;
    
    if(curr_subscreen_object==objs-1)
    {
        --curr_subscreen_object;
    }
    
    update_sso_name();
    update_up_dn_btns();
    
    return D_O_K;
}

int onAddToSelection()
{
    if(curr_subscreen_object >= 0)
    {
        sso_selection[curr_subscreen_object]=true;
    }
    
    return D_O_K;
}

int onRemoveFromSelection()
{
    if(curr_subscreen_object >= 0)
    {
        sso_selection[curr_subscreen_object]=false;
    }
    
    return D_O_K;
}

int onInvertSelection()
{
    for(int i=0; i<ss_objects(css); ++i)
    {
        sso_selection[i]=!sso_selection[i];
    }
    
    return D_O_K;
}

int onClearSelection()
{
    for(int i=0; i<MAXSUBSCREENITEMS; ++i)
    {
        sso_selection[i]=false;
    }
    
    return D_O_K;
}

int onDuplicateSubscreenObject()
{
    int objs=ss_objects(css);
    
    if(objs==0)
    {
        return D_O_K;
    }
    
    int counter=0;
    
    for(int i=0; i<objs; ++i)
    {
        int c=objs+counter;
        
        if(sso_selection[i]||i==curr_subscreen_object)
        {
            if(css->objects[c].dp1!=NULL)
            {
                delete [](char *)css->objects[c].dp1;
            }
            
            css->objects[c]=css->objects[i];
            
            if(css->objects[c].dp1!=NULL)
            {
                //No, don't do this.  css->objects[i] is pointing at this.  Leave it be.
                //delete [] (char *)css->objects[c].dp1;
                css->objects[c].dp1=NULL;
            }
            
            if(css->objects[i].dp1!=NULL)
            {
                //css->objects[c].dp1=zc_malloc(strlen((char *)css->objects[i].dp1)+1);
                css->objects[c].dp1= new char[strlen((char *)css->objects[i].dp1)+1];
                strcpy((char *)css->objects[c].dp1,(char *)css->objects[i].dp1);
            }
            else
            {
                //css->objects[c].dp1=zc_malloc(2);
                css->objects[c].dp1 = new char[2];
                ((char *)css->objects[c].dp1)[0]=0;
            }
            
            css->objects[c].x+=zc_max(zinit.ss_grid_x>>1,4);
            css->objects[c].y+=zc_max(zinit.ss_grid_y>>1,4);
            ++counter;
        }
    }
    
    update_sso_name();
    update_up_dn_btns();
    
    return D_O_K;
}

static int onToggleInvis();
static int onEditGrid();
static int onSelectionOptions();
static int onShowHideGrid();


static MENU subscreen_rc_menu[] =
{
    { (char *)"Properties ",       NULL,  NULL, 0, NULL },
    { (char *)"Inspect ",          NULL,  NULL, 0, NULL },
    { (char *)"Copy Properties ",  NULL,  NULL, 0, NULL },
    { (char *)"Paste Properties ", NULL,  NULL, 0, NULL },
    { NULL,                        NULL,  NULL, 0, NULL }
};


int d_subscreen_proc(int msg,DIALOG *d,int)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        for(int i=ss_objects(css)-1; i>=0; --i)
        {
            int x=sso_x(&css->objects[i])*(1+is_large);
            int y=sso_y(&css->objects[i])*(1+is_large);
            int w=sso_w(&css->objects[i])*(1+is_large);
            int h=sso_h(&css->objects[i])*(1+is_large);
            
            switch(get_alignment(&css->objects[i]))
            {
            case sstaCENTER:
                x-=(w/2);
                break;
                
            case sstaRIGHT:
                x-=w;
                break;
                
            case sstaLEFT:
            default:
                break;
            }
            
            if(isinRect(gui_mouse_x(),gui_mouse_y(),d->x+x, d->y+y, d->x+x+w-1, d->y+y+h-1))
            {
                if(key[KEY_LSHIFT]||key[KEY_RSHIFT])
                {
                    if(sso_selection[i]==true)
                    {
                        sso_selection[i]=false;
                    }
                    else
                    {
                        sso_selection[curr_subscreen_object]=true;
                        curr_subscreen_object=i;
                        update_sso_name();
                        update_up_dn_btns();
                    }
                }
                else
                {
                    onClearSelection();
                    curr_subscreen_object=i;
                    update_sso_name();
                    update_up_dn_btns();
                }
                
                break;
            }
        }
        
        if(gui_mouse_b()&2) //right mouse button
        {
            object_message(d,MSG_DRAW,0);
            
            // Disable "Paste Properties" if the copy source is invalid
            if(propCopySrc<0 || css->objects[propCopySrc].type==ssoNULL)
                subscreen_rc_menu[3].flags|=D_DISABLED;
            else
                subscreen_rc_menu[3].flags&=~D_DISABLED;
            
            int m = popup_menu(subscreen_rc_menu,gui_mouse_x(),gui_mouse_y());
            
            switch(m)
            {
            case 0: // Properties
                onSubscreenObjectProperties();
                break;
                
            case 1: // Inspect
                onSubscreenObjectRawProperties();
                break;
            
            case 2: // Copy Properties
                propCopySrc=curr_subscreen_object;
                break;
                
            case 3: // Paste Properties
                if(propCopySrc>=0) // Hopefully unnecessary)
                {
                    copySSOProperties(css->objects[propCopySrc], css->objects[curr_subscreen_object]);
                    for(int i=0; i<MAXSUBSCREENITEMS; i++)
                    {
                        if(!sso_selection[i])
                            continue;
                        
                        copySSOProperties(css->objects[propCopySrc], css->objects[i]);
                    }
                }
                break;
            }
        }
        
        return D_O_K;
    }
    break;
    
    case MSG_VSYNC:
        d->flags|=D_DIRTY;
        break;
        
    case MSG_DRAW:
    {
        Sitems.animate();
        BITMAP *buf = create_bitmap_ex(8,d->w,d->h);//In Large Mode, this is actually 2x as large as needed, but whatever.
        
        if(buf)
        {
            clear_bitmap(buf);
            show_custom_subscreen(buf, &misc, (subscreen_group *)(d->dp), 0, 0, true, sspUP | sspDOWN | sspSCROLLING);
            
            for(int i=0; i<MAXSUBSCREENITEMS; ++i)
            {
                if(sso_selection[i])
                {
                    sso_bounding_box(buf, css, i, vc(zinit.ss_bbox_2_color));
                }
            }
            
            sso_bounding_box(buf, css, curr_subscreen_object, vc(zinit.ss_bbox_1_color));
            
            if(zinit.ss_flags&ssflagSHOWGRID)
            {
                for(int x=zinit.ss_grid_xofs; x<d->w; x+=zinit.ss_grid_x)
                {
                    for(int y=zinit.ss_grid_yofs; y<d->h; y+=zinit.ss_grid_y)
                    {
                        buf->line[y][x]=vc(zinit.ss_grid_color);
                    }
                }
            }
            
            if(is_large)
            {
                stretch_blit(buf,screen,0,0,d->w/(1+is_large),d->h/(1+is_large),d->x,d->y,d->w,d->h);
            }
            else
            {
                blit(buf,screen,0,0,d->x,d->y,d->w,d->h);
            }
            
            destroy_bitmap(buf);
        }
    }
    break;
    
    case MSG_WANTFOCUS:
        return D_WANTFOCUS;
        break;
    }
    
    return D_O_K;
}

int onSSUp();
int onSSDown();
int onSSLeft();
int onSSRight();
int onSSPgDn();
int onSSPgUp();

int d_ssup_btn_proc(int msg,DIALOG *d,int c);
int d_ssdn_btn_proc(int msg,DIALOG *d,int c);
int d_sslt_btn_proc(int msg,DIALOG *d,int c);
int d_ssrt_btn_proc(int msg,DIALOG *d,int c);

int onSSUp()
{
    int delta=(key[KEY_LSHIFT]||key[KEY_RSHIFT])?-zinit.ss_grid_y:-1;
    
    for(int i=0; i<MAXSUBSCREENITEMS; ++i)
    {
        if(sso_selection[i]&&i!=curr_subscreen_object)
        {
            if(key[KEY_ZC_LCONTROL] || key[KEY_ZC_RCONTROL])
            {
                css->objects[i].h+=delta;
            }
            else
            {
                css->objects[i].y+=delta;
            }
        }
    }
    
    if(key[KEY_ZC_LCONTROL] || key[KEY_ZC_RCONTROL])
    {
        css->objects[curr_subscreen_object].h+=delta;
    }
    else
    {
        css->objects[curr_subscreen_object].y+=delta;
    }
    
    return D_O_K;
}

int onSSDown()
{
    int delta=(key[KEY_LSHIFT]||key[KEY_RSHIFT])?zinit.ss_grid_y:1;
    
    for(int i=0; i<MAXSUBSCREENITEMS; ++i)
    {
        if(sso_selection[i]&&i!=curr_subscreen_object)
        {
            if(key[KEY_ZC_LCONTROL] || key[KEY_ZC_RCONTROL])
            {
                css->objects[i].h+=delta;
            }
            else
            {
                css->objects[i].y+=delta;
            }
        }
    }
    
    if(key[KEY_ZC_LCONTROL] || key[KEY_ZC_RCONTROL])
    {
        css->objects[curr_subscreen_object].h+=delta;
    }
    else
    {
        css->objects[curr_subscreen_object].y+=delta;
    }
    
    return D_O_K;
}

int onSSLeft()
{
    int delta=(key[KEY_LSHIFT]||key[KEY_RSHIFT])?-zinit.ss_grid_x:-1;
    
    for(int i=0; i<MAXSUBSCREENITEMS; ++i)
    {
        if(sso_selection[i]&&i!=curr_subscreen_object)
        {
            if(key[KEY_ZC_LCONTROL] || key[KEY_ZC_RCONTROL])
            {
                css->objects[i].w+=delta;
            }
            else
            {
                css->objects[i].x+=delta;
            }
        }
    }
    
    if(key[KEY_ZC_LCONTROL] || key[KEY_ZC_RCONTROL])
    {
        css->objects[curr_subscreen_object].w+=delta;
    }
    else
    {
        css->objects[curr_subscreen_object].x+=delta;
    }
    
    return D_O_K;
}

int onSSRight()
{
    int delta=(key[KEY_LSHIFT]||key[KEY_RSHIFT])?zinit.ss_grid_x:1;
    
    for(int i=0; i<MAXSUBSCREENITEMS; ++i)
    {
        if(sso_selection[i]&&i!=curr_subscreen_object)
        {
            if(key[KEY_ZC_LCONTROL] || key[KEY_ZC_RCONTROL])
            {
                css->objects[i].w+=delta;
            }
            else
            {
                css->objects[i].x+=delta;
            }
        }
    }
    
    if(key[KEY_ZC_LCONTROL] || key[KEY_ZC_RCONTROL])
    {
        css->objects[curr_subscreen_object].w+=delta;
    }
    else
    {
        css->objects[curr_subscreen_object].x+=delta;
    }
    
    return D_O_K;
}

int d_ssup_btn2_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        onSSUp();
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_ssdn_btn2_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        onSSDown();
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_sslt_btn2_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        onSSLeft();
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_ssrt_btn2_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        onSSRight();
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_ssup_btn3_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        
        for(int i=0; i<MAXSUBSCREENITEMS; ++i)
        {
            if(sso_selection[i]&&i!=curr_subscreen_object)
            {
                --css->objects[i].h;
            }
        }
        
        --css->objects[curr_subscreen_object].h;
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_ssdn_btn3_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        
        for(int i=0; i<MAXSUBSCREENITEMS; ++i)
        {
            if(sso_selection[i]&&i!=curr_subscreen_object)
            {
                ++css->objects[i].h;
            }
        }
        
        ++css->objects[curr_subscreen_object].h;
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_sslt_btn3_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        
        for(int i=0; i<MAXSUBSCREENITEMS; ++i)
        {
            if(sso_selection[i]&&i!=curr_subscreen_object)
            {
                --css->objects[i].w;
            }
        }
        
        --css->objects[curr_subscreen_object].w;
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_ssrt_btn3_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        
        for(int i=0; i<MAXSUBSCREENITEMS; ++i)
        {
            if(sso_selection[i]&&i!=curr_subscreen_object)
            {
                ++css->objects[i].w;
            }
        }
        
        ++css->objects[curr_subscreen_object].w;
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int Bweapon(int pos)
{
    int p=-1;
    
    for(int i=0; css->objects[i].type!=ssoNULL; ++i)
    {
        if(css->objects[i].type==ssoCURRENTITEM && css->objects[i].d3==pos)
        {
            p=i;
            break;
        }
    }
    
    if(p==-1)
    {
        return 0;
    }
    
    int family = 0;
    bool bow = false;
    
    switch(css->objects[p].d1)
    {
    case itype_arrow:
    case itype_bowandarrow:
        if(current_item(itype_bow) && current_item(itype_arrow))
        {
            bow=(css->objects[p].d1==itype_bowandarrow);
            family=itype_arrow;
        }
        
        break;
        
    case itype_letterpotion:
        if(current_item(itype_potion))
            family=itype_potion;
        else if(current_item(itype_letter))
            family=itype_letter;
        
        break;
        
    case itype_sword:
    {
        if(!get_bit(quest_rules,qr_SELECTAWPN))
            break;
            
        family=itype_sword;
    }
    break;
    
    default:
        family=css->objects[p].d1;
    }
    
    for(int i=0; i<MAXITEMS; i++)
    {
        if(itemsbuf[i].family==family) return i+(bow ? 0xF000 : 0);
    }
    
    return 0;
}

void selectBwpn(int xstep, int ystep)
{
    if((xstep==0)&&(ystep==0))
    {
        Bwpn=Bweapon(Bpos);
        update_subscr_items();
        
        if(Bwpn)
        {
            return;
        }
        
        xstep=1;
    }
    
    if((xstep==8)&&(ystep==8))
    {
        Bwpn=Bweapon(Bpos);
        update_subscr_items();
        
        if(Bwpn)
        {
            return;
        }
        
        xstep=-1;
    }
    
    int pos = Bpos;
    int tries=0;
    
    do
    {
        int p=-1;
        
        for(int i=0; css->objects[i].type!=ssoNULL; ++i)
        {
            if(css->objects[i].type==ssoCURRENTITEM)
            {
                if(css->objects[i].d3==Bpos)
                {
                    p=i;
                    break;
                }
            }
        }
        
        if(p!=-1)
        {
            if(xstep!=0)
            {
                Bpos=xstep<0?css->objects[p].d6:css->objects[p].d7;
            }
            else
            {
                Bpos=ystep<0?css->objects[p].d4:css->objects[p].d5;
            }
        }
        
        Bwpn = Bweapon(Bpos);
        update_subscr_items();
        
        if(Bwpn)
        {
            return;
        }
    }
    while(Bpos!=pos && ++tries<0x100);
    
    if(!Bwpn)
        Bpos=0;
}


int d_ssup_btn4_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        selectBwpn(0, -1);
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_ssdn_btn4_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        selectBwpn(0, 1);
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_sslt_btn4_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        selectBwpn(-1, 0);
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_ssrt_btn4_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        selectBwpn(1, 0);
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

const char *sso_type[ssoMAX]=
{
    "ssoNULL", "ssoNONE", "sso2X2FRAME", "ssoTEXT", "ssoLINE", "ssoRECT", "ssoBSTIME", "ssoTIME", "ssoSSTIME", "ssoMAGICMETER", "ssoLIFEMETER", "ssoBUTTONITEM", "ssoICON", "ssoCOUNTER",
    "ssoCOUNTERS", "ssoMINIMAPTITLE", "ssoMINIMAP", "ssoLARGEMAP", "ssoCLEAR", "ssoCURRENTITEM", "ssoITEM", "ssoTRIFRAME", "ssoTRIFORCE", "ssoTILEBLOCK", "ssoMINITILE", "ssoSELECTOR1", "ssoSELECTOR2",
    "ssoMAGICGAUGE", "ssoLIFEGAUGE", "ssoTEXTBOX", "ssoCURRENTITEMTILE", "ssoSELECTEDITEMTILE", "ssoCURRENTITEMTEXT", "ssoCURRENTITEMNAME", "ssoSELECTEDITEMNAME", "ssoCURRENTITEMCLASSTEXT",
    "ssoCURRENTITEMCLASSNAME", "ssoSELECTEDITEMCLASSNAME"
};

const char *sso_textstyle[sstsMAX]=
{
    "sstsNORMAL", "sstsSHADOW", "sstsSHADOWU", "sstsOUTLINE8", "sstsOUTLINEPLUS", "sstsOUTLINEX", "sstsSHADOWED", "sstsSHADOWEDU", "sstsOUTLINED8", "sstsOUTLINEDPLUS", "sstsOUTLINEDX"
};

const char *sso_fontname[ssfMAX]=
{
    "ssfZELDA", "ssfSS1", "ssfSS2", "ssfSS3", "ssfSS4", "ssfZTIME", "ssfSMALL", "ssfSMALLPROP", "ssfZ3SMALL", "ssfGBLA", "ssfZ3",
    "ssfGORON", "ssfZORAN", "ssfHYLIAN1", "ssfHYLIAN2", "ssfHYLIAN3", "ssfHYLIAN4", "ssfPROP", "ssfGBORACLE", "ssfGBORACLEP",
    "ssfDSPHANTOM", "ssfDSPHANTOMP"
};

const char *sso_colortype[2]=
{
    "ssctSYSTEM", "ssctMISC"
};

const char *sso_specialcolor[ssctMAX]=
{
    "ssctTEXT", "ssctCAPTION", "ssctOVERWBG", "ssctDNGNBG", "ssctDNGNFG", "ssctCAVEFG", "ssctBSDK", "ssctBSGOAL", "ssctCOMPASSLT", "ssctCOMPASSDK", "ssctSUBSCRBG", "ssctSUBSCRSHADOW",
    "ssctTRIFRAMECOLOR", "ssctBMAPBG", "ssctBMAPFG", "ssctLINKDOT", "ssctMSGTEXT"
};

const char *sso_specialcset[sscsMAX]=
{
    "sscsTRIFORCECSET", "sscsTRIFRAMECSET", "sscsOVERWORLDMAPCSET", "sscsDUNGEONMAPCSET", "sscsBLUEFRAMECSET", "sscsHCPIECESCSET", "sscsSSVINECSET"
};

const char *sso_specialtile[ssmstMAX]=
{
    "ssmstSSVINETILE", "ssmstMAGICMETER"
};

const char *sso_counterobject[sscMAX]=
{
    "sscRUPEES", "sscBOMBS", "sscSBOMBS", "sscARROWS", "sscGENKEYMAGIC", "sscGENKEYNOMAGIC", "sscLEVKEYMAGIC",
    "sscLEVKEYNOMAGIC", "sscANYKEYMAGIC", "sscANYKEYNOMAGIC", "sscSCRIPT1", "sscSCRIPT2", "sscSCRIPT3", "sscSCRIPT4",
    "sscSCRIPT5", "sscSCRIPT6", "sscSCRIPT7", "sscSCRIPT8", "sscSCRIPT9", "sscSCRIPT10"
};

const char *sso_alignment[3]=
{
    "sstaLEFT", "sstaCENTER", "sstaRIGHT"
};


bool save_subscreen_code(char *path)
{
    PACKFILE *f = pack_fopen_password(path,F_WRITE,"");
    
    if(!f)
    {
        return false;
    }
    
    int ssobjs=ss_objects(css);
    char buf[512];
    memset(buf,0,512);
    sprintf(buf, "subscreen_object exported_subscreen[%d]=\n", ssobjs);
    pack_fputs(buf, f);
    
    if(pack_ferror(f))
    {
        pack_fclose(f);
        return false;
    }
    
    pack_fputs("{\n", f);
    
    if(pack_ferror(f))
    {
        pack_fclose(f);
        return false;
    }
    
    for(int i=0; i<ssobjs; ++i)
    {
//    pack_fputs("{\n", f);
        sprintf(buf, "  { %s, %d, %d, %d, %d, %d, ",
                sso_type[css->objects[i].type], css->objects[i].pos, css->objects[i].x, css->objects[i].y, css->objects[i].w, css->objects[i].h);
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        if(css->objects[i].colortype1>=ssctSYSTEM)
        {
            sprintf(buf, "%s, ", sso_colortype[css->objects[i].colortype1==ssctSYSTEM?0:1]);
            pack_fputs(buf, f);
            
            if(pack_ferror(f))
            {
                pack_fclose(f);
                return false;
            }
            
            if(css->objects[i].colortype1==ssctMISC)
            {
                int t=css->objects[i].type;
                
                if(t==sso2X2FRAME||t==ssoCURRENTITEMTILE||t==ssoICON||t==ssoMINITILE||t==ssoSELECTEDITEMTILE||t==ssoSELECTOR1||t==ssoSELECTOR2||t==ssoTRIFORCE||t==ssoTILEBLOCK)
                {
                    sprintf(buf, "%s, ", sso_specialcset[css->objects[i].color1]);
                    pack_fputs(buf, f);
                    
                    if(pack_ferror(f))
                    {
                        pack_fclose(f);
                        return false;
                    }
                }
                else
                {
                    sprintf(buf, "%s, ", sso_specialcolor[css->objects[i].color1]);
                    pack_fputs(buf, f);
                    
                    if(pack_ferror(f))
                    {
                        pack_fclose(f);
                        return false;
                    }
                }
            }
            else
            {
                sprintf(buf, "%d, ", css->objects[i].color1);
                pack_fputs(buf, f);
                
                if(pack_ferror(f))
                {
                    pack_fclose(f);
                    return false;
                }
            }
        }
        else
        {
            sprintf(buf, "%d, %d, ", css->objects[i].colortype1, css->objects[i].color1);
            pack_fputs(buf, f);
            
            if(pack_ferror(f))
            {
                pack_fclose(f);
                return false;
            }
        }
        
        if(css->objects[i].colortype2>=ssctSYSTEM)
        {
            sprintf(buf, "%s, ", sso_colortype[css->objects[i].colortype2==ssctSYSTEM?0:1]);
            pack_fputs(buf, f);
            
            if(pack_ferror(f))
            {
                pack_fclose(f);
                return false;
            }
            
            if(css->objects[i].colortype2==ssctMISC)
            {
                int t=css->objects[i].type;
                
                if(t==sso2X2FRAME||t==ssoCURRENTITEMTILE||t==ssoICON||t==ssoMINITILE||t==ssoSELECTEDITEMTILE||t==ssoSELECTOR1||t==ssoSELECTOR2||t==ssoTRIFORCE||t==ssoTILEBLOCK)
                {
                    sprintf(buf, "%s, ", sso_specialcset[css->objects[i].color2]);
                    pack_fputs(buf, f);
                    
                    if(pack_ferror(f))
                    {
                        pack_fclose(f);
                        return false;
                    }
                }
                else
                {
                    sprintf(buf, "%s, ", sso_specialcolor[css->objects[i].color2]);
                    pack_fputs(buf, f);
                    
                    if(pack_ferror(f))
                    {
                        pack_fclose(f);
                        return false;
                    }
                }
            }
            else
            {
                sprintf(buf, "%d, ", css->objects[i].color2);
                pack_fputs(buf, f);
                
                if(pack_ferror(f))
                {
                    pack_fclose(f);
                    return false;
                }
            }
        }
        else
        {
            sprintf(buf, "%d, %d, ", css->objects[i].colortype2, css->objects[i].color2);
            pack_fputs(buf, f);
            
            if(pack_ferror(f))
            {
                pack_fclose(f);
                return false;
            }
        }
        
        if(css->objects[i].colortype3>=ssctSYSTEM)
        {
            sprintf(buf, "%s, ", sso_colortype[css->objects[i].colortype3==ssctSYSTEM?0:1]);
            pack_fputs(buf, f);
            
            if(pack_ferror(f))
            {
                pack_fclose(f);
                return false;
            }
            
            if(css->objects[i].colortype3==ssctMISC)
            {
                int t=css->objects[i].type;
                
                if(t==sso2X2FRAME||t==ssoCURRENTITEMTILE||t==ssoICON||t==ssoMINITILE||t==ssoSELECTEDITEMTILE||t==ssoSELECTOR1||t==ssoSELECTOR2||t==ssoTRIFORCE||t==ssoTILEBLOCK)
                {
                    sprintf(buf, "%s, ", sso_specialcset[css->objects[i].color3]);
                    pack_fputs(buf, f);
                    
                    if(pack_ferror(f))
                    {
                        pack_fclose(f);
                        return false;
                    }
                }
                else
                {
                    sprintf(buf, "%s, ", sso_specialcolor[css->objects[i].color3]);
                    pack_fputs(buf, f);
                    
                    if(pack_ferror(f))
                    {
                        pack_fclose(f);
                        return false;
                    }
                }
            }
            else
            {
                sprintf(buf, "%d, ", css->objects[i].color3);
                pack_fputs(buf, f);
                
                if(pack_ferror(f))
                {
                    pack_fclose(f);
                    return false;
                }
            }
        }
        else
        {
            sprintf(buf, "%d, %d, ", css->objects[i].colortype3, css->objects[i].color3);
            pack_fputs(buf, f);
            
            if(pack_ferror(f))
            {
                pack_fclose(f);
                return false;
            }
        }
        
        switch(css->objects[i].type)
        {
        case ssoCURRENTITEM:
            sprintf(buf, "%s, ", itype_names[css->objects[i].d1]);
            break;
            
        case ssoCOUNTER:
        case ssoCOUNTERS:
        case ssoTEXT:
        case ssoTEXTBOX:
        case ssoMINIMAPTITLE:
        case ssoSELECTEDITEMNAME:
        case ssoTIME:
        case ssoSSTIME:
        case ssoBSTIME:
            sprintf(buf, "%s, ", sso_fontname[css->objects[i].d1]);
            break;
            
        default:
            sprintf(buf, "%d, ", css->objects[i].d1);
            break;
        }
        
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        switch(css->objects[i].type)
        {
        case ssoCOUNTER:
        case ssoTEXT:
        case ssoTEXTBOX:
        case ssoMINIMAPTITLE:
        case ssoSELECTEDITEMNAME:
        case ssoTIME:
        case ssoSSTIME:
        case ssoBSTIME:
            sprintf(buf, "%s, ", sso_alignment[css->objects[i].d2]);
            break;
            
        case ssoMINITILE:
            if(css->objects[i].d1==-1)
            {
                sprintf(buf, "%s, ", sso_specialtile[css->objects[i].d2]);
            }
            else
            {
                sprintf(buf, "%d, ", css->objects[i].d2);
            }
            
            break;
            
        default:
            sprintf(buf, "%d, ", css->objects[i].d2);
            break;
        }
        
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        switch(css->objects[i].type)
        {
        case ssoCOUNTER:
        case ssoCOUNTERS:
        case ssoTEXT:
        case ssoTEXTBOX:
        case ssoMINIMAPTITLE:
        case ssoSELECTEDITEMNAME:
        case ssoTIME:
        case ssoSSTIME:
        case ssoBSTIME:
            sprintf(buf, "%s, ", (char *)sso_textstyle[css->objects[i].d3]);
            break;
            
        default:
            sprintf(buf, "%d, ", css->objects[i].d3);
            break;
        }
        
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        sprintf(buf, "%d, ", css->objects[i].d4);
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        switch(css->objects[i].type)
        {
        case ssoCOUNTER:
        case ssoCOUNTERS:
            sprintf(buf, "\'%c\', ", css->objects[i].d5);
            break;
            
        default:
            sprintf(buf, "%d, ", css->objects[i].d5);
            break;
        }
        
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        sprintf(buf, "%d, ", css->objects[i].d6);
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        switch(css->objects[i].type)
        {
        case ssoCOUNTER:
            sprintf(buf, "%s, ", sso_counterobject[css->objects[i].d7]);
            break;
            
        default:
            sprintf(buf, "%d, ", css->objects[i].d7);
            break;
        }
        
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        sprintf(buf, "%d, ", css->objects[i].d8);
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        sprintf(buf, "%d, ", css->objects[i].d9);
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        sprintf(buf, "%d, ", css->objects[i].d10);
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        sprintf(buf, "%d, ", css->objects[i].frames);
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        sprintf(buf, "%d, ", css->objects[i].speed);
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        sprintf(buf, "%d, ", css->objects[i].delay);
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        sprintf(buf, "%d, ", css->objects[i].frame);
        pack_fputs(buf, f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
        
        
        if(!css->objects[i].dp1)
        {
            pack_fputs("NULL", f);
            
            if(pack_ferror(f))
            {
                pack_fclose(f);
                return false;
            }
        }
        else
        {
            pack_fputs("(void *)\"", f);
            
            if(pack_ferror(f))
            {
                pack_fclose(f);
                return false;
            }
            
            pack_fputs((char *)css->objects[i].dp1, f);
            
            if(pack_ferror(f))
            {
                pack_fclose(f);
                return false;
            }
            
            pack_fputs("\"", f);
            
            if(pack_ferror(f))
            {
                pack_fclose(f);
                return false;
            }
        }
        
        pack_fputs(" },\n", f);
        
        if(pack_ferror(f))
        {
            pack_fclose(f);
            return false;
        }
    }
    
    pack_fputs("  { ssoNULL }\n", f);
    
    if(pack_ferror(f))
    {
        pack_fclose(f);
        return false;
    }
    
    pack_fputs("};\n", f);
    
    if(pack_ferror(f))
    {
        pack_fclose(f);
        return false;
    }
    
    pack_fclose(f);
    return true;
}



int onExport_Subscreen_Code()
{
    if(!getname("Export Subscreen Code (.zss)","zss",NULL,datapath,false))
        return D_O_K;
        
    char buf[80],buf2[80],name[13];
    extract_name(temppath,name,FILENAME8_3);
    
    if(save_subscreen_code(temppath))
    {
        sprintf(buf,"ZQuest");
        sprintf(buf2,"Saved %s",name);
    }
    else
    {
        sprintf(buf,"Error");
        sprintf(buf2,"Error saving %s",name);
    }
    
    jwin_alert(buf,buf2,NULL,NULL,"O&K",NULL,'k',0,lfont);
    return D_O_K;
}

int onActivePassive();

static MENU ss_arrange_menu[] =
{
    { (char *)"Bring to Front",       onBringToFront,          NULL, 0, NULL },
    { (char *)"Bring Forward",        onBringForward,          NULL, 0, NULL },
    { (char *)"Send Backward",        onSendBackward,          NULL, 0, NULL },
    { (char *)"Send to Back",         onSendToBack,            NULL, 0, NULL },
    { (char *)"Reverse",              onReverseArrangement,    NULL, 0, NULL },
    { NULL,                           NULL,                    NULL, 0, NULL }
};

static MENU ss_grid_snap_menu[] =
{
    { (char *)"Left Edges",           onGridSnapLeft,          NULL, 0, NULL },
    { (char *)"Horizontal Centers",   onGridSnapCenter,        NULL, 0, NULL },
    { (char *)"Right Edges",          onGridSnapRight,         NULL, 0, NULL },
    { (char *)"",                     NULL,                    NULL, 0, NULL },
    { (char *)"Top Edges",            onGridSnapTop,           NULL, 0, NULL },
    { (char *)"Vertical Centers",     onGridSnapMiddle,        NULL, 0, NULL },
    { (char *)"Bottom Edges",         onGridSnapBottom,        NULL, 0, NULL },
    { NULL,                           NULL,                    NULL, 0, NULL }
};

static MENU ss_align_menu[] =
{
    { (char *)"Left Edges",           onAlignLeft,             NULL, 0, NULL },
    { (char *)"Horizontal Centers",   onAlignCenter,           NULL, 0, NULL },
    { (char *)"Right Edges",          onAlignRight,            NULL, 0, NULL },
    { (char *)"",                     NULL,                    NULL, 0, NULL },
    { (char *)"Top Edges",            onAlignTop,              NULL, 0, NULL },
    { (char *)"Vertical Centers",     onAlignMiddle,           NULL, 0, NULL },
    { (char *)"Bottom Edges",         onAlignBottom,           NULL, 0, NULL },
    { (char *)"",                     NULL,                    NULL, 0, NULL },
    { (char *)"To Grid",              NULL,                    ss_grid_snap_menu, 0, NULL },
    { NULL,                           NULL,                    NULL, 0, NULL }
};

static MENU ss_distribute_menu[] =
{
    { (char *)"Left Edges",           onDistributeLeft,             NULL, 0, NULL },
    { (char *)"Horizontal Centers",   onDistributeCenter,           NULL, 0, NULL },
    { (char *)"Right Edges",          onDistributeRight,            NULL, 0, NULL },
    { (char *)"",                     NULL,                         NULL, 0, NULL },
    { (char *)"Top Edges",            onDistributeTop,              NULL, 0, NULL },
    { (char *)"Vertical Centers",     onDistributeMiddle,           NULL, 0, NULL },
    { (char *)"Bottom Edges",         onDistributeBottom,           NULL, 0, NULL },
    { NULL,                           NULL,                         NULL, 0, NULL }
};

static MENU ss_edit_menu[] =
{
    { (char *)"&New\tIns",           onNewSubscreenObject,                 NULL, 0, NULL },
    { (char *)"&Delete\tDel",        onDeleteSubscreenObject,              NULL, 0, NULL },
    { (char *)"",                    NULL,                                 NULL, 0, NULL },
    { (char *)"&Duplicate",          onDuplicateSubscreenObject,           NULL, 0, NULL },
    { (char *)"",                    NULL,                                 NULL, 0, NULL },
    { (char *)"&Properties",         onSubscreenObjectProperties,          NULL, 0, NULL },
    { (char *)"",                    NULL,                                 NULL, 0, NULL },
    { (char *)"&Arrange",            NULL,                                 ss_arrange_menu, 0, NULL },
    { (char *)"Al&ign",              NULL,                                 ss_align_menu, 0, NULL },
    { (char *)"Dis&tribute",         NULL,                                 ss_distribute_menu, 0, NULL },
    { (char *)"",                    NULL,                                 NULL, 0, NULL },
    { (char *)"Switch Active/Passive",              onActivePassive,                      NULL, 0, NULL },
    { (char *)"",                    NULL,                                 NULL, 0, NULL },
    { (char *)"&Take Snapshot\tZ",   onSnapshot,                           NULL, 0, NULL },
    { (char *)"",                    NULL,                                 NULL, 0, NULL },
    { (char *)"E&xport as Code\tX",  onExport_Subscreen_Code,              NULL, 0, NULL },
    { NULL,                          NULL,                                 NULL, 0, NULL }
};

static MENU ss_view_menu[] =
{
    { (char *)"Show in&visible items",           onToggleInvis,                 NULL, 0, NULL },
    { (char *)"&Edit grid",                      onEditGrid,                    NULL, 0, NULL },
    { (char *)"&Show grid",                      onShowHideGrid,                NULL, 0, NULL },
    { NULL,                                 NULL,                          NULL, 0, NULL }
};

static MENU ss_selection_menu[] =
{
    { (char *)"&Add to Selection\tA",       onAddToSelection,                 NULL, 0, NULL },
    { (char *)"&Remove from Selection\tR",  onRemoveFromSelection,            NULL, 0, NULL },
    { (char *)"&Invert Selection\tI",       onInvertSelection,                NULL, 0, NULL },
    { (char *)"&Clear Selection\tC",        onClearSelection,                 NULL, 0, NULL },
    { (char *)"",                           NULL,                             NULL, 0, NULL },
    { (char *)"&Options",                   onSelectionOptions,               NULL, 0, NULL },
    { NULL,                                 NULL,                             NULL, 0, NULL }
};

static MENU subscreen_menu[] =
{
    { (char *)"&Edit",               NULL,                                 ss_edit_menu, 0, NULL },
    { (char *)"&View",               NULL,                                 ss_view_menu, 0, NULL },
    { (char *)"&Selection",          NULL,                                 ss_selection_menu, 0, NULL },
    { NULL,                         NULL,                                 NULL, 0, NULL }
};


static DIALOG subscreen_dlg[] =
{
    // (dialog proc)       (x)   (y)    (w)     (h)   (fg)                (bg)              (key)    (flags)     (d1)           (d2)     (dp)
    { jwin_win_proc,        0,    0,      320,    240,  vc(0),              vc(11),           0,       D_EXIT,     0,             0, (void *) "Subscreen Editor", NULL, NULL },
    { jwin_button_proc,     192,  215,    61,     21,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "OK", NULL, NULL },
    { jwin_button_proc,     255,  215,    61,     21,   vc(0),              vc(11),           27,      D_EXIT,     0,             0, (void *) "Cancel", NULL, NULL },
    { jwin_frame_proc,      4,    37,     260,    172,  0,                  0,                0,       0,          FR_DEEP,       0,       NULL, NULL, NULL },
    { d_subscreen_proc,     6,    39,     256,    168,  0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    // 5
    { d_box_proc,           11,   211,    181,    8,    0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { jwin_text_proc,       11,   211,    181,    16,   0,                  0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { jwin_text_proc,       4,    225,    30,     16,   0,                  0,                0,       0,          0,             0, (void *) "Name:", NULL, NULL },
    { jwin_edit_proc,       34,   221,    155,    16,   0,                  0,                0,       0,          64,            0,       NULL, NULL, NULL },
    
    { d_ssup_btn_proc,      284,  23,     15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x88", NULL, NULL },
    { d_ssdn_btn_proc,      284,  53,     15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x89", NULL, NULL },
    { d_sslt_btn_proc,      269,  38,     15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x8A", NULL, NULL },
    { d_ssrt_btn_proc,      299,  38,     15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x8B", NULL, NULL },
    
    { d_ssup_btn2_proc,     284,  70,     15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x88", NULL, NULL },
    { d_ssdn_btn2_proc,     284,  100,    15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x89", NULL, NULL },
    { d_sslt_btn2_proc,     269,  85,     15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x8A", NULL, NULL },
    { d_ssrt_btn2_proc,     299,  85,     15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x8B", NULL, NULL },
    
    { d_ssup_btn3_proc,     284,  117,    15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x98", NULL, NULL },
    { d_ssdn_btn3_proc,     284,  147,    15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x99", NULL, NULL },
    { d_sslt_btn3_proc,     269,  132,    15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x9A", NULL, NULL },
    { d_ssrt_btn3_proc,     299,  132,    15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x9B", NULL, NULL },
    
    { d_ssup_btn4_proc,     284,  164,    15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x88", NULL, NULL },
    { d_ssdn_btn4_proc,     284,  194,    15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x89", NULL, NULL },
    { d_sslt_btn4_proc,     269,  179,    15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x8A", NULL, NULL },
    { d_ssrt_btn4_proc,     299,  179,    15,     15,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "\x8B", NULL, NULL },
    
    { jwin_menu_proc,       4,    23,     0,      13,    0,                 0,                0,       0,          0,             0, (void *) subscreen_menu, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                0,       0,          KEY_UP,        0, (void *) onSSUp, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                0,       0,          KEY_DOWN,      0, (void *) onSSDown, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                0,       0,          KEY_LEFT,      0, (void *) onSSLeft, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                0,       0,          KEY_RIGHT,     0, (void *) onSSRight, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                0,       0,          KEY_PGUP,      0, (void *) onSSPgUp, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                0,       0,          KEY_PGDN,      0, (void *) onSSPgDn, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                'a',     0,          0,             0, (void *) onAddToSelection, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                'r',     0,          0,             0, (void *) onRemoveFromSelection, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                'i',     0,          0,             0, (void *) onInvertSelection, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                'c',     0,          0,             0, (void *) onClearSelection, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                0,       0,          KEY_INSERT,    0, (void *) onNewSubscreenObject, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                0,       0,          KEY_DEL,       0, (void *) onDeleteSubscreenObject, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                'd',     0,          0,             0, (void *) onDuplicateSubscreenObject, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                'e',     0,          0,             0, (void *) onSubscreenObjectProperties, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                'z',     0,          0,             0, (void *) onSnapshot, NULL, NULL },
    { d_keyboard_proc,      0,     0,     0,       0,    0,                 0,                'x',     0,          0,             0, (void *) onExport_Subscreen_Code, NULL, NULL },
    { d_vsync_proc,         0,     0,     0,       0,    0,                 0,                0,       0,          0,             0,       NULL, NULL, NULL },
    { d_timer_proc,         0,    0,     0,    0,    0,       0,       0,       0,          0,          0,         NULL, NULL, NULL },
    { NULL,                 0,    0,    0,    0,   0,       0,       0,       0,          0,             0,       NULL,                           NULL,  NULL }
};

int onActivePassive()
{
    if(css->ss_type == sstACTIVE)
    {
        css->ss_type = sstPASSIVE;
        subscreen_dlg[3].h=60*(1+is_large)-(is_large?4:0);
        subscreen_dlg[4].h=subscreen_dlg[3].h-4;
    }
    else if(css->ss_type == sstPASSIVE)
    {
        css->ss_type = sstACTIVE;
        subscreen_dlg[3].h=172*(1+is_large)-(is_large?4:0);
        subscreen_dlg[4].h=subscreen_dlg[3].h-4;
    }
    
    return D_REDRAW;
}


const char *color_str[16] =
{
    "Black", "Blue", "Green", "Cyan", "Red", "Magenta", "Brown", "Light Gray",
    "Dark Gray", "Light Blue", "Light Green", "Light Cyan", "Light Red", "Light Magenta", "Yellow", "White"
};

const char *colorlist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = 16;
        return NULL;
    }
    
    return color_str[index];
}

static ListData color_list(colorlist, &font);

static DIALOG grid_dlg[] =
{
    // (dialog proc)       (x)   (y)    (w)     (h)   (fg)                (bg)              (key)    (flags)     (d1)           (d2)     (dp)
    { jwin_win_proc,        0,    0,      158,    120,  vc(0),              vc(11),           0,       D_EXIT,     0,             0, (void *) "Edit Grid Properties", NULL, NULL },
    { jwin_button_proc,     18,    95,    61,     21,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "OK", NULL, NULL },
    { jwin_button_proc,     81,    95,    61,     21,   vc(0),              vc(11),           27,      D_EXIT,     0,             0, (void *) "Cancel", NULL, NULL },
    { jwin_text_proc,       6,     29,    186,    16,   0,                  0,                0,       0,          0,             0, (void *) "X Size:", NULL, NULL },
    { jwin_edit_proc,       42,    25,     26,    16,   0,                  0,                0,       0,          3,             0,       NULL, NULL, NULL },
    // 5
    { jwin_text_proc,       6,     49,    186,    16,   0,                  0,                0,       0,          0,             0, (void *) "Y Size:", NULL, NULL },
    { jwin_edit_proc,       42,    45,     26,    16,   0,                  0,                0,       0,          3,             0,       NULL, NULL, NULL },
    { jwin_text_proc,       78,    29,    186,    16,   0,                  0,                0,       0,          0,             0, (void *) "X Offset:", NULL, NULL },
    { jwin_edit_proc,       126,   25,     26,    16,   0,                  0,                0,       0,          3,             0,       NULL, NULL, NULL },
    { jwin_text_proc,       78,    49,    186,    16,   0,                  0,                0,       0,          0,             0, (void *) "Y Offset:", NULL, NULL },
    // 10
    { jwin_edit_proc,       126,   45,     26,    16,   0,                  0,                0,       0,          3,             0,       NULL, NULL, NULL },
    { jwin_text_proc,       6,     69,    186,    16,   0,                  0,                0,       0,          0,             0, (void *) "Color:", NULL, NULL },
    { jwin_droplist_proc,   36,    65,    116,    16,   0,                  0,                0,       0,          0,             0, (void *) &color_list, NULL, NULL },
    { d_timer_proc,         0,    0,     0,    0,    0,       0,       0,       0,          0,          0,         NULL, NULL, NULL },
    { NULL,                 0,    0,    0,    0,   0,       0,       0,       0,          0,             0,       NULL,                           NULL,  NULL }
};

static DIALOG sel_options_dlg[] =
{
    // (dialog proc)       (x)    (y)    (w)     (h)   (fg)                (bg)              (key)    (flags)     (d1)           (d2)     (dp)
    { jwin_win_proc,        0,     0,    225,   120,   vc(0),              vc(11),           0,       D_EXIT,     0,             0, (void *) "Selection Options", NULL, NULL },
    { jwin_button_proc,     51,    95,    61,    21,   vc(0),              vc(11),           13,      D_EXIT,     0,             0, (void *) "OK", NULL, NULL },
    { jwin_button_proc,    114,    95,    61,    21,   vc(0),              vc(11),           27,      D_EXIT,     0,             0, (void *) "Cancel", NULL, NULL },
    { jwin_frame_proc,       6,    28,   213,    51,   jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          FR_ETCHED,     0,       NULL, NULL, NULL },
    { jwin_text_proc,       10,    25,    48,     8,   jwin_pal[jcBOXFG],  jwin_pal[jcBOX],  0,       0,          0,             0, (void *) " Selection Outlines ", NULL, NULL },
    // 5
    { jwin_text_proc,       14,    41,   186,    16,   0,                  0,                0,       0,          0,             0, (void *) "Primary Color:", NULL, NULL },
    { jwin_droplist_proc,   94,    37,   116,    16,   0,                  0,                0,       0,          0,             0, (void *) &color_list, NULL, NULL },
    { jwin_text_proc,       14,    61,   186,    16,   0,                  0,                0,       0,          0,             0, (void *) "Secondary Color:", NULL, NULL },
    { jwin_droplist_proc,   94,    57,   116,    16,   0,                  0,                0,       0,          0,             0, (void *) &color_list, NULL, NULL },
    { d_timer_proc,         0,    0,     0,    0,    0,       0,       0,       0,          0,          0,         NULL, NULL, NULL },
    { NULL,                 0,    0,    0,    0,   0,       0,       0,       0,          0,             0,       NULL,                           NULL,  NULL }
};

const char *sso_str[ssoMAX]=
{
    "NULL", "(None)", "2x2 Frame", "Text", "Line", "Rectangle", "BS-Zelda Time", "Game Time", "Game Time (Quest Rule)", "Magic Meter", "Life Meter",
    "Button Item", "-Icon (Not Implemented)", "Counter", "Counter Block", "Minimap Title", "Minimap", "Large Map", "Erase Subscreen", "Current Item", "-Item (Not Implemented)",
    "Triforce Frame", "Triforce Piece", "Tile Block", "Minitile", "Selector 1", "Selector 2", "Magic Gauge Piece", "Life Gauge Piece", "Text Box", "-Current Item -> Tile (Not Implemented)",
    "-Selected Item -> Tile (Not Implemented)", "-Current Item -> Text (Not Implemented)", "-Current Item Name (Not Implemented)", "Selected Item Name",
    "-Current Item Class -> Text (Not Implemented)", "-Current Item Class Name (Not Implemented)", "-Selected Item Class Name (Not Implemented)"
};

char *sso_name(int type)
{
    char *tempname;
    tempname=(char*)zc_malloc(255);
    
    if(type>=0 && type <ssoMAX)
    {
        sprintf(tempname, "%s", sso_str[type]);
    }
    else
    {
        sprintf(tempname, "INVALID OBJECT!  type=%d", type);
    }
    
    return tempname;
}

char *sso_name(subscreen_object *tempss, int id)
{
    return sso_name(tempss[id].type);
}

sso_struct bisso[ssoMAX];
int bisso_cnt=-1;

void build_bisso_list()
{
    int start=1;
    bisso_cnt=0;
    
    for(int i=start; i<ssoMAX; i++)
    {
        if(sso_str[i][0]!='-')
        {
            bisso[bisso_cnt].s = (char *)sso_str[i];
            bisso[bisso_cnt].i = i;
            ++bisso_cnt;
        }
    }
    
    for(int i=start; i<bisso_cnt-1; i++)
    {
        for(int j=i+1; j<bisso_cnt; j++)
        {
            if(stricmp(bisso[i].s,bisso[j].s)>0)
            {
                std::swap(bisso[i],bisso[j]);
            }
        }
    }
}

const char *ssolist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = bisso_cnt;
        return NULL;
    }
    
    return bisso[index].s;
}

static ListData sso_list(ssolist, &font);

static DIALOG ssolist_dlg[] =
{
    // (dialog proc)      (x)   (y)   (w)   (h)   (fg)     (bg)    (key)    (flags)     (d1)           (d2)     (dp)
    { jwin_win_proc,        0,    0,   255,  148,  vc(14),  vc(1),  0,       D_EXIT,          0,             0, (void *) "Select Object Type", NULL, NULL },
    { d_timer_proc,         0,    0,     0,    0,    0,       0,       0,       0,          0,          0,         NULL, NULL, NULL },
    { jwin_abclist_proc,    4,   24,   247,  95,   jwin_pal[jcTEXTFG],  jwin_pal[jcTEXTBG],  0,       D_EXIT,     0,             0, (void *) &sso_list, NULL, NULL },
    { jwin_button_proc,    65,  123,  61,   21,   vc(14),  vc(1),  13,      D_EXIT,     0,             0, (void *) "OK", NULL, NULL },
    { jwin_button_proc,   128,  123,  61,   21,   vc(14),  vc(1),  27,      D_EXIT,     0,             0, (void *) "Cancel", NULL, NULL },
    { NULL,                 0,    0,    0,    0,   0,       0,       0,       0,          0,             0,       NULL,                           NULL,  NULL }
};

int onNewSubscreenObject()
{
    subscreen_object tempsso;
    int ret=-1;
    ssolist_dlg[0].dp2=lfont;
    build_bisso_list();
    
    if(is_large)
        large_dialog(ssolist_dlg);
        
    ret=zc_popup_dialog(ssolist_dlg,2);
    
    if(ret!=0&&ret!=4)
    {
        memset(&tempsso,0,sizeof(subscreen_object));
        //tempsso.dp1=(char *)zc_malloc(2);
        tempsso.dp1 = new char[2];
        ((char *)tempsso.dp1)[0]=0;
        tempsso.type=bisso[ssolist_dlg[2].d1].i;
        tempsso.pos = sspUP | sspDOWN | sspSCROLLING;
        tempsso.w=1;
        tempsso.h=1;
        
        if(tempsso.type==ssoCURRENTITEM)  // Should not be invisible!
            tempsso.d2 = 1;
            
        int temp_cso=curr_subscreen_object;
        curr_subscreen_object=ss_objects(css);
        
        if(sso_properties(&tempsso)!=-1)
        {
            if(css->objects[curr_subscreen_object].dp1!=NULL)
            {
                delete [](char *)css->objects[curr_subscreen_object].dp1;
                css->objects[curr_subscreen_object].dp1=NULL;
            }
            
            css->objects[curr_subscreen_object]=tempsso;
            update_sso_name();
            update_up_dn_btns();
        }
        else
        {
            curr_subscreen_object=temp_cso;
        }
    }
    
    return D_O_K;
}


void align_objects(subscreen_group *tempss, bool *selection, int align_type)
{
    int l=sso_x(&tempss->objects[curr_subscreen_object]);
    int t=sso_y(&tempss->objects[curr_subscreen_object]);
    int w=sso_w(&tempss->objects[curr_subscreen_object]);
    int h=sso_h(&tempss->objects[curr_subscreen_object]);
    
    switch(get_alignment(&tempss->objects[curr_subscreen_object]))
    {
    case sstaCENTER:
        l-=(w/2);
        break;
        
    case sstaRIGHT:
        l-=w;
        break;
        
    case sstaLEFT:
    default:
        break;
    }
    
    int r=l+w-1;
    int b=t+h-1;
    int c=l+w/2;
    int m=t+h/2;
    
    for(int i=0; i<MAXSUBSCREENITEMS; ++i)
    {
        if(selection[i]&&i!=curr_subscreen_object)
        {
            int tl=sso_x(&tempss->objects[i]);
            int tt=sso_y(&tempss->objects[i]);
            int tw=sso_w(&tempss->objects[i]);
            int th=sso_h(&tempss->objects[i]);
            
            switch(get_alignment(&tempss->objects[i]))
            {
            case sstaCENTER:
                tl-=(tw/2);
                break;
                
            case sstaRIGHT:
                tl-=tw;
                break;
                
            case sstaLEFT:
            default:
                break;
            }
            
            int tr=tl+tw-1;
            int tb=tt+th-1;
            int tc=tl+tw/2;
            int tm=tt+th/2;
            
            switch(align_type)
            {
            case ssoaBOTTOM:
                tempss->objects[i].y+=b-tb;
                break;
                
            case ssoaMIDDLE:
                tempss->objects[i].y+=m-tm;
                break;
                
            case ssoaTOP:
                tempss->objects[i].y+=t-tt;
                break;
                
            case ssoaRIGHT:
                tempss->objects[i].x+=r-tr;
                break;
                
            case ssoaCENTER:
                tempss->objects[i].x+=c-tc;
                break;
                
            case ssoaLEFT:
            default:
                tempss->objects[i].x+=l-tl;
                break;
            }
        }
    }
}

void grid_snap_objects(subscreen_group *tempss, bool *selection, int snap_type)
{
    for(int i=0; i<MAXSUBSCREENITEMS; ++i)
    {
        if(selection[i]||i==curr_subscreen_object)
        {
            int tl=sso_x(&tempss->objects[i]);
            int tt=sso_y(&tempss->objects[i]);
            int tw=sso_w(&tempss->objects[i]);
            int th=sso_h(&tempss->objects[i]);
            
            switch(get_alignment(&tempss->objects[i]))
            {
            case sstaCENTER:
                tl-=(tw/2);
                break;
                
            case sstaRIGHT:
                tl-=tw;
                break;
                
            case sstaLEFT:
            default:
                break;
            }
            
            int tr=tl+tw-1;
            int tb=tt+th-1;
            int tc=tl+tw/2;
            int tm=tt+th/2;
            int l1=(tl-zinit.ss_grid_xofs)/zinit.ss_grid_x*zinit.ss_grid_x+zinit.ss_grid_xofs;
            int l2=l1+zinit.ss_grid_x;
            int c1=(tc-zinit.ss_grid_xofs)/zinit.ss_grid_x*zinit.ss_grid_x+zinit.ss_grid_xofs;
            int c2=c1+zinit.ss_grid_x;
            int r1=(tr-zinit.ss_grid_xofs)/zinit.ss_grid_x*zinit.ss_grid_x+zinit.ss_grid_xofs;
            int r2=r1+zinit.ss_grid_x;
            
            int t1=(tt-zinit.ss_grid_yofs)/zinit.ss_grid_y*zinit.ss_grid_y+zinit.ss_grid_yofs;
            int t2=t1+zinit.ss_grid_y;
            int m1=(tm-zinit.ss_grid_yofs)/zinit.ss_grid_y*zinit.ss_grid_y+zinit.ss_grid_yofs;
            int m2=m1+zinit.ss_grid_y;
            int b1=(tb-zinit.ss_grid_yofs)/zinit.ss_grid_y*zinit.ss_grid_y+zinit.ss_grid_yofs;
            int b2=b1+zinit.ss_grid_y;
            
            switch(snap_type)
            {
            case ssosBOTTOM:
                tempss->objects[i].y+=(abs(b1-tb)>abs(b2-tb))?(b2-tb):(b1-tb);
                break;
                
            case ssosMIDDLE:
                tempss->objects[i].y+=(abs(m1-tm)>abs(m2-tm))?(m2-tm):(m1-tm);
                break;
                
            case ssosTOP:
                tempss->objects[i].y+=(abs(t1-tt)>abs(t2-tt))?(t2-tt):(t1-tt);
                break;
                
            case ssosRIGHT:
                tempss->objects[i].x+=(abs(r1-tr)>abs(r2-tr))?(r2-tr):(r1-tr);
                break;
                
            case ssosCENTER:
                tempss->objects[i].x+=(abs(c1-tc)>abs(c2-tc))?(c2-tc):(c1-tc);
                break;
                
            case ssosLEFT:
            default:
                tempss->objects[i].x+=(abs(l1-tl)>abs(l2-tl))?(l2-tl):(l1-tl);
                break;
            }
        }
    }
}

typedef struct dist_obj
{
    int index;
    int l;
    int t;
    int w;
    int h;
    int r;
    int b;
    int c;
    int m;
} dist_obj;

void distribute_objects(subscreen_group *tempss, bool *selection, int distribute_type)
{
    //these are here to bypass compiler warnings about unused arguments
    selection=selection;
    
    int count=0;
    dist_obj temp_do[MAXSUBSCREENITEMS];
    
    for(int i=0; i<MAXSUBSCREENITEMS; ++i)
    {
        if(sso_selection[i]==true||i==curr_subscreen_object)
        {
            temp_do[count].index=i;
            temp_do[count].l=sso_x(&tempss->objects[i]);
            temp_do[count].t=sso_y(&tempss->objects[i]);
            temp_do[count].w=sso_w(&tempss->objects[i]);
            temp_do[count].h=sso_h(&tempss->objects[i]);
            
            switch(get_alignment(&tempss->objects[i]))
            {
            case sstaCENTER:
                temp_do[count].l-=(temp_do[count].w/2);
                break;
                
            case sstaRIGHT:
                temp_do[count].l-=temp_do[count].w;
                break;
                
            case sstaLEFT:
            default:
                break;
            }
            
            temp_do[count].r=temp_do[count].l+temp_do[count].w-1;
            temp_do[count].b=temp_do[count].t+temp_do[count].h-1;
            temp_do[count].c=temp_do[count].l+temp_do[count].w/2;
            temp_do[count].m=temp_do[count].t+temp_do[count].h/2;
            ++count;
        }
    }
    
    if(count<3)
    {
        return;
    }
    
    //sort all objects in order of position, then index (yeah, bubble sort; sue me)
    dist_obj tempdo2;
    
    for(int j=0; j<count-1; j++)
    {
        for(int k=0; k<count-1-j; k++)
        {
            switch(distribute_type)
            {
            case ssodBOTTOM:
                if(temp_do[k+1].b<temp_do[k].b||((temp_do[k+1].b==temp_do[k].b)&&(temp_do[k+1].index<temp_do[k].index)))
                {
                    tempdo2=temp_do[k];
                    temp_do[k]=temp_do[k+1];
                    temp_do[k+1]=tempdo2;
                }
                
                break;
                
            case ssodMIDDLE:
                if(temp_do[k+1].m<temp_do[k].m||((temp_do[k+1].m==temp_do[k].m)&&(temp_do[k+1].index<temp_do[k].index)))
                {
                    tempdo2=temp_do[k];
                    temp_do[k]=temp_do[k+1];
                    temp_do[k+1]=tempdo2;
                }
                
                break;
                
            case ssodTOP:
                if(temp_do[k+1].t<temp_do[k].t||((temp_do[k+1].t==temp_do[k].t)&&(temp_do[k+1].index<temp_do[k].index)))
                {
                    tempdo2=temp_do[k];
                    temp_do[k]=temp_do[k+1];
                    temp_do[k+1]=tempdo2;
                }
                
                break;
                
            case ssodRIGHT:
                if(temp_do[k+1].r<temp_do[k].r||((temp_do[k+1].r==temp_do[k].r)&&(temp_do[k+1].index<temp_do[k].index)))
                {
                    tempdo2=temp_do[k];
                    temp_do[k]=temp_do[k+1];
                    temp_do[k+1]=tempdo2;
                }
                
                break;
                
            case ssodCENTER:
                if(temp_do[k+1].c<temp_do[k].c||((temp_do[k+1].c==temp_do[k].c)&&(temp_do[k+1].index<temp_do[k].index)))
                {
                    tempdo2=temp_do[k];
                    temp_do[k]=temp_do[k+1];
                    temp_do[k+1]=tempdo2;
                }
                
                break;
                
            case ssodLEFT:
            default:
                if(temp_do[k+1].l<temp_do[k].l||((temp_do[k+1].l==temp_do[k].l)&&(temp_do[k+1].index<temp_do[k].index)))
                {
                    tempdo2=temp_do[k];
                    temp_do[k]=temp_do[k+1];
                    temp_do[k+1]=tempdo2;
                }
                
                break;
            }
        }
    }
    
    int ld=temp_do[count-1].l-temp_do[0].l;
    int td=temp_do[count-1].t-temp_do[0].t;
    int rd=temp_do[count-1].r-temp_do[0].r;
    int bd=temp_do[count-1].b-temp_do[0].b;
    int cd=temp_do[count-1].c-temp_do[0].c;
    int md=temp_do[count-1].m-temp_do[0].m;
    
    for(int i=1; i<count-1; ++i)
    {
        switch(distribute_type)
        {
        case ssodBOTTOM:
            tempss->objects[temp_do[i].index].y+=bd*i/(count-1)-temp_do[i].b+temp_do[0].b;
            break;
            
        case ssodMIDDLE:
            tempss->objects[temp_do[i].index].y+=md*i/(count-1)-temp_do[i].m+temp_do[0].m;
            break;
            
        case ssodTOP:
            tempss->objects[temp_do[i].index].y+=td*i/(count-1)-temp_do[i].t+temp_do[0].t;
            break;
            
        case ssodRIGHT:
            tempss->objects[temp_do[i].index].x+=rd*i/(count-1)-temp_do[i].r+temp_do[0].r;
            break;
            
        case ssodCENTER:
            tempss->objects[temp_do[i].index].x+=cd*i/(count-1)-temp_do[i].c+temp_do[0].c;
            break;
            
        case ssodLEFT:
        default:
            tempss->objects[temp_do[i].index].x+=ld*i/(count-1)-temp_do[i].l+temp_do[0].l;
            break;
        }
    }
    
}

int onBringToFront()
{
    while(curr_subscreen_object<ss_objects(css)-1)
    {
        onBringForward();
    }
    
    return D_O_K;
}

int onSendToBack()
{
    while(curr_subscreen_object>0)
    {
        onSendBackward();
    }
    
    return D_O_K;
}

int onReverseArrangement()
{
    int i=0;
    int j=MAXSUBSCREENITEMS-1;
    subscreen_object tempsso;
    
    sso_selection[curr_subscreen_object]=true;
    
    while(true)
    {
        while(i<MAXSUBSCREENITEMS && !sso_selection[i])
            i++;
            
        while(j>=0 && !sso_selection[j])
            j--;
            
        if(i>=j)
        {
            sso_selection[curr_subscreen_object]=false;
            return D_O_K;
        }
        
        if(curr_subscreen_object==i)
            curr_subscreen_object=j;
        else if(curr_subscreen_object==j)
            curr_subscreen_object=i;
            
        tempsso=css->objects[i];
        css->objects[i]=css->objects[j];
        css->objects[j]=tempsso;
        
        i++;
        j--;
    }
}

int onAlignLeft()
{
    align_objects(css, sso_selection, ssoaLEFT);
    return D_O_K;
}

int onAlignCenter()
{
    align_objects(css, sso_selection, ssoaCENTER);
    return D_O_K;
}

int onAlignRight()
{
    align_objects(css, sso_selection, ssoaRIGHT);
    return D_O_K;
}

int onAlignTop()
{
    align_objects(css, sso_selection, ssoaTOP);
    return D_O_K;
}

int onAlignMiddle()
{
    align_objects(css, sso_selection, ssoaMIDDLE);
    return D_O_K;
}

int onAlignBottom()
{
    align_objects(css, sso_selection, ssoaBOTTOM);
    return D_O_K;
}

int onDistributeLeft()
{
    distribute_objects(css, sso_selection, ssodLEFT);
    return D_O_K;
}

int onDistributeCenter()
{
    distribute_objects(css, sso_selection, ssodCENTER);
    return D_O_K;
}

int onDistributeRight()
{
    distribute_objects(css, sso_selection, ssodRIGHT);
    return D_O_K;
}

int onDistributeTop()
{
    distribute_objects(css, sso_selection, ssodTOP);
    return D_O_K;
}

int onDistributeMiddle()
{
    distribute_objects(css, sso_selection, ssodMIDDLE);
    return D_O_K;
}

int onDistributeBottom()
{
    distribute_objects(css, sso_selection, ssodBOTTOM);
    return D_O_K;
}

int onGridSnapLeft()
{
    grid_snap_objects(css, sso_selection, ssosLEFT);
    return D_O_K;
}

int onGridSnapCenter()
{
    grid_snap_objects(css, sso_selection, ssosCENTER);
    return D_O_K;
}

int onGridSnapRight()
{
    grid_snap_objects(css, sso_selection, ssosRIGHT);
    return D_O_K;
}

int onGridSnapTop()
{
    grid_snap_objects(css, sso_selection, ssosTOP);
    return D_O_K;
}

int onGridSnapMiddle()
{
    grid_snap_objects(css, sso_selection, ssosMIDDLE);
    return D_O_K;
}

int onGridSnapBottom()
{
    grid_snap_objects(css, sso_selection, ssosBOTTOM);
    return D_O_K;
}

static int onToggleInvis()
{
    bool show=!(zinit.ss_flags&ssflagSHOWINVIS);
    zinit.ss_flags&=~ssflagSHOWINVIS;
    zinit.ss_flags|=(show?ssflagSHOWINVIS:0);
    ss_view_menu[0].flags=zinit.ss_flags&ssflagSHOWINVIS?D_SELECTED:0;
    return D_O_K;
}

static int onEditGrid()
{
    grid_dlg[0].dp2=lfont;
    char xsize[4];
    char ysize[4];
    char xoffset[4];
    char yoffset[4];
    sprintf(xsize, "%d", zc_max(zinit.ss_grid_x,1));
    sprintf(ysize, "%d", zc_max(zinit.ss_grid_y,1));
    sprintf(xoffset, "%d", zinit.ss_grid_xofs);
    sprintf(yoffset, "%d", zinit.ss_grid_yofs);
    grid_dlg[4].dp=xsize;
    grid_dlg[6].dp=ysize;
    grid_dlg[8].dp=xoffset;
    grid_dlg[10].dp=yoffset;
    grid_dlg[12].d1=zinit.ss_grid_color;
    
    if(is_large)
        large_dialog(grid_dlg);
        
    int ret = zc_popup_dialog(grid_dlg,2);
    
    if(ret==1)
    {
        zinit.ss_grid_x=zc_max(atoi(xsize),1);
        zinit.ss_grid_xofs=atoi(xoffset);
        zinit.ss_grid_y=zc_max(atoi(ysize),1);
        zinit.ss_grid_yofs=atoi(yoffset);
        zinit.ss_grid_color=grid_dlg[12].d1;
    }
    
    return D_O_K;
}

static int onShowHideGrid()
{
    bool show=!(zinit.ss_flags&ssflagSHOWGRID);
    zinit.ss_flags&=~ssflagSHOWGRID;
    zinit.ss_flags|=(show?ssflagSHOWGRID:0);
    ss_view_menu[2].flags=zinit.ss_flags&ssflagSHOWGRID?D_SELECTED:0;
    return D_O_K;
}

int onSelectionOptions()
{
    sel_options_dlg[0].dp2=lfont;
    sel_options_dlg[6].d1=zinit.ss_bbox_1_color;
    sel_options_dlg[8].d1=zinit.ss_bbox_2_color;
    
    if(is_large)
        large_dialog(sel_options_dlg);
        
    int ret = zc_popup_dialog(sel_options_dlg,2);
    
    if(ret==1)
    {
        zinit.ss_bbox_1_color=sel_options_dlg[6].d1;
        zinit.ss_bbox_2_color=sel_options_dlg[8].d1;
    }
    
    return D_O_K;
}


void update_up_dn_btns()
{
    if(curr_subscreen_object<1)
    {
        subscreen_dlg[10].flags|=D_DISABLED;
    }
    else
    {
        subscreen_dlg[10].flags&=~D_DISABLED;
    }
    
    if(curr_subscreen_object>=ss_objects(css)-1)
    {
        subscreen_dlg[9].flags|=D_DISABLED;
    }
    else
    {
        subscreen_dlg[9].flags&=~D_DISABLED;
    }
    
    subscreen_dlg[9].flags|=D_DIRTY;
    subscreen_dlg[10].flags|=D_DIRTY;
}

int onSSCtrlPgUp()
{
    return onBringForward();
}

int onSSCtrlPgDn()
{
    return onSendBackward();
}

int onSendBackward()
{
    subscreen_object tempsso;
    bool tempsel;
    
    if(curr_subscreen_object>0)
    {
        tempsso=css->objects[curr_subscreen_object];
        tempsel=sso_selection[curr_subscreen_object];
        
        css->objects[curr_subscreen_object]=css->objects[curr_subscreen_object-1];
        sso_selection[curr_subscreen_object]=sso_selection[curr_subscreen_object-1];
        
        css->objects[curr_subscreen_object-1]=tempsso;
        sso_selection[curr_subscreen_object-1]=tempsel;
        
        --curr_subscreen_object;
        update_sso_name();
    }
    
    update_up_dn_btns();
    return D_O_K;
}

int onSSPgDn()
{
    if(key[KEY_ZC_LCONTROL] || key[KEY_ZC_RCONTROL])
    {
        return onSSCtrlPgDn();
    }
    else
    {
        --curr_subscreen_object;
        
        if(curr_subscreen_object<0)
        {
            curr_subscreen_object=ss_objects(css)-1;
        }
        
        update_sso_name();
        update_up_dn_btns();
    }
    
    return D_O_K;
}

// Send forward
int onBringForward()
{
    subscreen_object tempsso;
    bool tempsel;
    
    if(curr_subscreen_object<ss_objects(css)-1)
    {
        tempsso=css->objects[curr_subscreen_object];
        tempsel=sso_selection[curr_subscreen_object];
        
        css->objects[curr_subscreen_object]=css->objects[curr_subscreen_object+1];
        sso_selection[curr_subscreen_object]=sso_selection[curr_subscreen_object+1];
        
        css->objects[curr_subscreen_object+1]=tempsso;
        sso_selection[curr_subscreen_object+1]=tempsel;
        
        ++curr_subscreen_object;
        update_sso_name();
    }
    
    update_up_dn_btns();
    return D_O_K;
}


int onSSPgUp()
{
    if(key[KEY_ZC_LCONTROL] || key[KEY_ZC_RCONTROL])
    {
        return onSSCtrlPgUp();
    }
    else
    {
        if(ss_objects(css)>0)
        {
            ++curr_subscreen_object;
            
            if(curr_subscreen_object>=ss_objects(css))
            {
                curr_subscreen_object=0;
            }
        }
        
        update_sso_name();
        update_up_dn_btns();
    }
    
    return D_O_K;
}

int d_ssup_btn_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        return onSSCtrlPgUp();
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_ssdn_btn_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        return onSSCtrlPgDn();
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_sslt_btn_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        onSSPgDn();
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}

int d_ssrt_btn_proc(int msg,DIALOG *d,int c)
{
    switch(msg)
    {
    case MSG_CLICK:
    {
        jwin_button_proc(msg, d, c);
        onSSPgUp();
        return D_O_K;
    }
    break;
    }
    
    return jwin_button_proc(msg, d, c);
}



void edit_subscreen()
{
    game = new gamedata;
    game->Clear();
    game->set_time(0);
    resetItems(game,&zinit,true);
    
    //so that these will show up on the subscreen -DD
    if(game->get_bombs() == 0)
        game->set_bombs(1);
        
    if(game->get_sbombs() == 0)
        game->set_sbombs(1);
        
    if(game->get_arrows() == 0)
        game->set_arrows(1);
        
    subscreen_dlg[0].dp2=lfont;
    load_Sitems(&misc);
    curr_subscreen_object=0;
    propCopySrc=-1;
    subscreen_group tempss;
    memset(&tempss, 0, sizeof(subscreen_group));
    int i;
    
    for(i=0; i<MAXSUBSCREENITEMS; i++)
    {
        memcpy(&tempss.objects[i],&css->objects[i],sizeof(subscreen_object));
        
        switch(css->objects[i].type)
        {
        case ssoTEXT:
        case ssoTEXTBOX:
        case ssoCURRENTITEMTEXT:
        case ssoCURRENTITEMCLASSTEXT:
            tempss.objects[i].dp1 = NULL;
            tempss.objects[i].dp1 = new char[strlen((char*)css->objects[i].dp1)+1];
            strcpy((char*)tempss.objects[i].dp1,(char*)css->objects[i].dp1);
            break;
            
        default:
            break;
        }
    }
    
    tempss.ss_type=css->ss_type;
    sprintf(tempss.name, css->name);
    
    if(ss_objects(css)==0)
    {
        curr_subscreen_object=-1;
    }
    
    onClearSelection();
    ss_view_menu[0].flags=zinit.ss_flags&ssflagSHOWINVIS?D_SELECTED:0;
    ss_view_menu[2].flags=zinit.ss_flags&ssflagSHOWGRID?D_SELECTED:0;
    
    if(css->objects[0].type==ssoNULL)
    {
        css->objects[0].type=ssoNONE;
    }
    
    subscreen_dlg[4].dp=(void *)css;
    subscreen_dlg[5].fg=jwin_pal[jcBOX];
    subscreen_dlg[5].bg=jwin_pal[jcBOX];
    str_oname=(char *)zc_malloc(255);
    subscreen_dlg[6].dp=(void *)str_oname;
    subscreen_dlg[8].dp=(void *)(css->name);
    update_sso_name();
    subscreen_dlg[10].flags|=D_DISABLED;
    
    if(css->ss_type==sstPASSIVE)
    {
        subscreen_dlg[21].flags|=D_DISABLED;
        subscreen_dlg[22].flags|=D_DISABLED;
        subscreen_dlg[23].flags|=D_DISABLED;
        subscreen_dlg[24].flags|=D_DISABLED;
    }
    else
    {
        subscreen_dlg[21].flags&=~D_DISABLED;
        subscreen_dlg[22].flags&=~D_DISABLED;
        subscreen_dlg[23].flags&=~D_DISABLED;
        subscreen_dlg[24].flags&=~D_DISABLED;
    }
    
    selectBwpn(0, 0);
    
    if(is_large)
    {
        bool enlarge = subscreen_dlg[0].d1==0;
        
        if(enlarge)
        {
            large_dialog(subscreen_dlg,2);
            subscreen_dlg[4].y-=32;
            subscreen_dlg[3].y-=31;
            subscreen_dlg[3].x+=1;
            
            if(css->ss_type == sstPASSIVE)
                subscreen_dlg[3].h=60*(1+is_large)-(is_large?4:0);
            else if(css->ss_type == sstACTIVE)
                subscreen_dlg[3].h=172*(1+is_large)-(is_large?4:0);
                
            subscreen_dlg[4].h=subscreen_dlg[3].h-4;
        }
    }
    
    int ret = zc_popup_dialog(subscreen_dlg,2);
    
    if(ret==1)
    {
        saved=false;
        zinit.subscreen=ssdtMAX;
    }
    else
    {
        reset_subscreen(css);
        int j;
        
        for(j=0; j<MAXSUBSCREENITEMS; j++)
        {
            memcpy(&css->objects[j],&tempss.objects[j],sizeof(subscreen_object));
            
            switch(tempss.objects[j].type)
            {
            case ssoTEXT:
            case ssoTEXTBOX:
            case ssoCURRENTITEMTEXT:
            case ssoCURRENTITEMCLASSTEXT:
                css->objects[j].dp1 = NULL;
                css->objects[j].dp1 = new char[strlen((char*)tempss.objects[j].dp1)+1];
                strcpy((char*)css->objects[j].dp1,(char*)tempss.objects[j].dp1);
                break;
                
            default:
                break;
            }
        }
        
        css->ss_type=tempss.ss_type;
        sprintf(css->name, tempss.name);
        reset_subscreen(&tempss);
    }
    
    delete game;
    game=NULL;
}

const char *allsubscrtype_str[30] =
{
    "Original (Top, Triforce)", "Original (Top, Map)",
    "New Subscreen (Top, Triforce)", "New Subscreen (Top, Map)",
    "Revision 2 (Top, Triforce)", "Revision 2 (Top, Map)",
    "BS Zelda Original (Top, Triforce)", "BS Zelda Original (Top, Map)",
    "BS Zelda Modified (Top, Triforce)", "BS Zelda Modified (Top, Map)",
    "BS Zelda Enhanced (Top, Triforce)", "BS Zelda Enhanced (Top, Map)",
    "BS Zelda Complete (Top, Triforce)", "BS Zelda Complete (Top, Map)",
    "Zelda 3 (Top)",
    "Original (Bottom, Magic)", "Original (Bottom, No Magic)",
    "New Subscreen (Bottom, Magic)", "New Subscreen (Bottom, No Magic)",
    "Revision 2 (Bottom, Magic)", "Revision 2 (Bottom, No Magic)",
    "BS Zelda Original (Bottom, Magic)", "BS Zelda Original (Bottom, No Magic)",
    "BS Zelda Modified (Bottom, Magic)", "BS Zelda Modified (Bottom, No Magic)",
    "BS Zelda Enhanced (Bottom, Magic)", "BS Zelda Enhanced (Bottom, No Magic)",
    "BS Zelda Complete (Bottom, Magic)", "BS Zelda Complete (Bottom, No Magic)",
    "Zelda 3 (Bottom)"
};

const char *activesubscrtype_str[16] =
{
    "Blank",
    "Original (Top, Triforce)", "Original (Top, Map)",
    "New Subscreen (Top, Triforce)", "New Subscreen (Top, Map)",
    "Revision 2 (Top, Triforce)", "Revision 2 (Top, Map)",
    "BS Zelda Original (Top, Triforce)", "BS Zelda Original (Top, Map)",
    "BS Zelda Modified (Top, Triforce)", "BS Zelda Modified (Top, Map)",
    "BS Zelda Enhanced (Top, Triforce)", "BS Zelda Enhanced (Top, Map)",
    "BS Zelda Complete (Top, Triforce)", "BS Zelda Complete (Top, Map)",
    "Zelda 3 (Top)"
};

const char *activelist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = 16;
        return NULL;
    }
    
    return activesubscrtype_str[index];
}

const char *passivesubscrtype_str[16] =
{
    "Blank",
    "Original (Bottom, Magic)", "Original (Bottom, No Magic)",
    "New Subscreen (Bottom, Magic)", "New Subscreen (Bottom, No Magic)",
    "Revision 2 (Bottom, Magic)", "Revision 2 (Bottom, No Magic)",
    "BS Zelda Original (Bottom, Magic)", "BS Zelda Original (Bottom, No Magic)",
    "BS Zelda Modified (Bottom, Magic)", "BS Zelda Modified (Bottom, No Magic)",
    "BS Zelda Enhanced (Bottom, Magic)", "BS Zelda Enhanced (Bottom, No Magic)",
    "BS Zelda Complete (Bottom, Magic)", "BS Zelda Complete (Bottom, No Magic)",
    "Zelda 3 (Bottom)"
};

const char *passivelist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = 16;
        return NULL;
    }
    
    return passivesubscrtype_str[index];
}

const char *activepassive_str[sstMAX] =
{
    "Active", "Passive"
};

const char *activepassivelist(int index, int *list_size)
{
    if(index<0)
    {
        *list_size = sstMAX;
        return NULL;
    }
    
    return activepassive_str[index];
}

static ListData passive_list(passivelist, &font);
static ListData active_list(activelist, &font);

int sstype_drop_proc(int msg,DIALOG *d,int c)
{
    int tempd1=d->d1;
    int ret=jwin_droplist_proc(msg,d,c);
    
    if(tempd1!=d->d1)
    {
        (d+1)->dp=(d->d1)?(void*)&passive_list:(void*)&active_list;
        object_message(d+1,MSG_START,0);
        (d+1)->flags|=D_DIRTY;
    }
    
    return ret;
}

static ListData activepassive_list(activepassivelist, &font);

static DIALOG sstemplatelist_dlg[] =
{
    // (dialog proc)         (x)   (y)   (w)   (h)   (fg)     (bg)    (key)    (flags)     (d1)           (d2)     (dp)
    { jwin_win_proc,          0,    0,   265,  87,  vc(14),  vc(1),  0,       D_EXIT,          0,             0, (void *) "New Subscreen", NULL, NULL },
    { d_timer_proc,         0,    0,     0,    0,    0,       0,       0,       0,          0,          0,         NULL, NULL, NULL },
    { jwin_text_proc,         4,   28,     8,   8,   0,                  0,                0,       0,          0,             0, (void *) "Type:", NULL, NULL },
    { jwin_text_proc,         4,   46,     8,   8,   0,                  0,                0,       0,          0,             0, (void *) "Template:", NULL, NULL },
    { sstype_drop_proc,      33,   24,    72,  16,   jwin_pal[jcTEXTFG],  jwin_pal[jcTEXTBG],  0,         0,     0,             0, (void *) &activepassive_list, NULL, NULL },
    { jwin_droplist_proc,    50,   42,   211,  16,   jwin_pal[jcTEXTFG],  jwin_pal[jcTEXTBG],  0,         0,     0,             0, (void *) &active_list, NULL, NULL },
    { jwin_button_proc,      61,   62,    61,   21,   vc(14),  vc(1),  13,      D_EXIT,     0,             0, (void *) "OK", NULL, NULL },
    { jwin_button_proc,     142,   62,    61,   21,   vc(14),  vc(1),  27,      D_EXIT,     0,             0, (void *) "Cancel", NULL, NULL },
    { NULL,                 0,    0,    0,    0,   0,       0,       0,       0,          0,             0,       NULL,                           NULL,  NULL }
};

bool show_new_ss=true;

const char *subscreenlist(int index, int *list_size)
{
    if(index<0)
    {
        int j=0;
        
        while(custom_subscreen[j].objects[0].type!=ssoNULL)
        {
            ++j;
        }
        
        *list_size = j+(show_new_ss?1:0);
        sprintf(custom_subscreen[j].name, "<New>");
        return NULL;
    }
    
    return custom_subscreen[index].name;
}

const char *subscreenlist_a(int index, int *list_size)
{
    if(index<0)
    {
        int i=0, j=0;
        
        while(custom_subscreen[j].objects[0].type!=ssoNULL)
        {
            if(custom_subscreen[j].ss_type==sstACTIVE)
            {
                ++i;
            }
            
            ++j;
        }
        
        *list_size = i;
        return NULL;
    }
    
//  return custsubscrtype_str[index];
    int i=-1, j=0;
    
    while(custom_subscreen[j].objects[0].type!=ssoNULL&&i!=index)
    {
        if(custom_subscreen[j].ss_type==sstACTIVE)
        {
            ++i;
        }
        
        ++j;
    }
    
    return custom_subscreen[j-1].name;
}

const char *subscreenlist_b(int index, int *list_size)
{
    if(index<0)
    {
        int i=0, j=0;
        
        while(custom_subscreen[j].objects[0].type!=ssoNULL)
        {
            if(custom_subscreen[j].ss_type==sstPASSIVE)
            {
                ++i;
            }
            
            ++j;
        }
        
        *list_size = i;
        return NULL;
    }
    
//  return custsubscrtype_str[index];
    int i=-1, j=0;
    
    while(custom_subscreen[j].name[0]&&i!=index)
    {
        if(custom_subscreen[j].ss_type==sstPASSIVE)
        {
            ++i;
        }
        
        ++j;
    }
    
    return custom_subscreen[j-1].name;
}

static ListData subscreen_list(subscreenlist, &font);

DIALOG sslist_dlg[] =
{
    // (dialog proc)     (x)   (y)   (w)   (h)   (fg)     (bg)    (key)    (flags)     (d1)           (d2)     (dp)
    { jwin_win_proc,     0,   0,   234,  148,  vc(14),  vc(1),  0,       D_EXIT,          0,             0, (void *) "Select Subscreen", NULL, NULL },
    { d_timer_proc,         0,    0,     0,    0,    0,       0,       0,       0,          0,          0,         NULL, NULL, NULL },
    { jwin_abclist_proc,    12,   24,   211,  95,   jwin_pal[jcTEXTFG],  jwin_pal[jcTEXTBG],  0,       D_EXIT,     0,             0, (void *) &subscreen_list, NULL, NULL },
    { jwin_button_proc,     12,   123,  61,   21,   vc(14),  vc(1),  13,      D_EXIT,     0,             0, (void *) "Edit", NULL, NULL },
    { jwin_button_proc,     85,  123,  61,   21,   vc(14),  vc(1),  KEY_DEL,     D_EXIT,     0,             0, (void *) "Delete", NULL, NULL },
    { jwin_button_proc,     158,  123,  61,   21,   vc(14),  vc(1),  27,      D_EXIT,     0,             0, (void *) "Done", NULL, NULL },
    { NULL,                 0,    0,    0,    0,   0,       0,       0,       0,          0,             0,       NULL,                           NULL,  NULL }
};

int onEditSubscreens()
{
    int ret=-1;
    sslist_dlg[0].dp2=lfont;
    sstemplatelist_dlg[0].dp2=lfont;
    
    if(is_large)
        large_dialog(sslist_dlg);
        
    while(ret!=0&&ret!=5)
    {
        ret=zc_popup_dialog(sslist_dlg,2);
        
        if(ret==4)
        {
            int confirm = jwin_alert("Confirm Delete", "You are about to delete the selected subscreen!", "Are you sure?", NULL, "OK", "Cancel", KEY_ENTER, KEY_ESC, lfont);
            
            if(confirm==1)
            {
                delete_subscreen(sslist_dlg[2].d1);
                saved=false;
            }
        }
        else if(ret==2 || ret ==3)
        {
            if(custom_subscreen[sslist_dlg[2].d1].ss_type==sstACTIVE)
            {
                subscreen_dlg[3].h=172*(1+is_large)-(is_large?4:0);
                subscreen_dlg[4].h=subscreen_dlg[3].h-4;
            }
            else if(custom_subscreen[sslist_dlg[2].d1].ss_type==sstPASSIVE)
            {
                subscreen_dlg[3].h=60*(1+is_large)-(is_large?4:0);
                subscreen_dlg[4].h=subscreen_dlg[3].h-4;
                //iu;hukl;kh;
            }
            else
            {
                subscreen_dlg[3].h=20*(1+is_large);
                subscreen_dlg[4].h=subscreen_dlg[3].h-4;
            }
            
            css = &custom_subscreen[sslist_dlg[2].d1];
            bool edit_it=true;
            
            if(css->objects[0].type==ssoNULL)
            {
                if(is_large)
                    large_dialog(sstemplatelist_dlg);
                    
                ret=zc_popup_dialog(sstemplatelist_dlg,4);
                
                if(ret==6)
                {
                    if(sstemplatelist_dlg[5].d1<15)
                    {
                        if(sstemplatelist_dlg[5].d1 != 0)
                        {
                            subscreen_object *tempsub;
                            
                            if(sstemplatelist_dlg[4].d1==0)
                            {
                                tempsub = default_subscreen_active[(sstemplatelist_dlg[5].d1-1)/2][(sstemplatelist_dlg[5].d1-1)&1];
                            }
                            else
                            {
                                tempsub = default_subscreen_passive[(sstemplatelist_dlg[5].d1-1)/2][(sstemplatelist_dlg[5].d1-1)&1];
                            }
                            
                            int i;
                            
                            for(i=0; (i<MAXSUBSCREENITEMS&&tempsub[i].type!=ssoNULL); i++)
                            {
                                switch(tempsub[i].type)
                                {
                                case ssoTEXT:
                                case ssoTEXTBOX:
                                case ssoCURRENTITEMTEXT:
                                case ssoCURRENTITEMCLASSTEXT:
                                    if(css->objects[i].dp1 != NULL) delete [](char *)css->objects[i].dp1;
                                    
                                    memcpy(&css->objects[i],&tempsub[i],sizeof(subscreen_object));
                                    css->objects[i].dp1 = NULL;
                                    css->objects[i].dp1 = new char[strlen((char*)tempsub[i].dp1)+1];
                                    strcpy((char*)css->objects[i].dp1,(char*)tempsub[i].dp1);
                                    break;
                                    
                                default:
                                    memcpy(&css->objects[i],&tempsub[i],sizeof(subscreen_object));
                                    break;
                                }
                            }
                        }
                        
                        if(sstemplatelist_dlg[4].d1==0)
                        {
                            css->ss_type=sstACTIVE;
                            sprintf(css->name, activesubscrtype_str[sstemplatelist_dlg[5].d1]);
                            subscreen_dlg[3].h=172*(1+is_large);
                            subscreen_dlg[4].h=subscreen_dlg[3].h-4;
                        }
                        else
                        {
                            css->ss_type=sstPASSIVE;
                            sprintf(css->name, passivesubscrtype_str[sstemplatelist_dlg[5].d1]);
                            subscreen_dlg[3].h=60*(1+is_large);
                            subscreen_dlg[4].h=subscreen_dlg[3].h-4;
                        }
                    }
                    else //Z3
                    {
                        subscreen_object *tempsub;
                        
                        if(sstemplatelist_dlg[4].d1==0)
                        {
                            tempsub = z3_active_a;
                        }
                        else
                        {
                            tempsub = z3_passive_a;
                        }
                        
                        int i;
                        
                        for(i=0; (i<MAXSUBSCREENITEMS&&tempsub[i].type!=ssoNULL); i++)
                        {
                            switch(tempsub[i].type)
                            {
                            case ssoTEXT:
                            case ssoTEXTBOX:
                            case ssoCURRENTITEMTEXT:
                            case ssoCURRENTITEMCLASSTEXT:
                                if(css->objects[i].dp1 != NULL) delete [](char *)css->objects[i].dp1;
                                
                                memcpy(&css->objects[i],&tempsub[i],sizeof(subscreen_object));
                                css->objects[i].dp1 = NULL;
                                css->objects[i].dp1 = new char[strlen((char*)tempsub[i].dp1)+1];
                                strcpy((char*)css->objects[i].dp1,(char*)tempsub[i].dp1);
                                break;
                                
                            default:
                                memcpy(&css->objects[i],&tempsub[i],sizeof(subscreen_object));
                                break;
                            }
                        }
                        
                        if(sstemplatelist_dlg[4].d1==0)
                        {
                            css->ss_type=sstACTIVE;
                            sprintf(css->name, activesubscrtype_str[sstemplatelist_dlg[5].d1]);
                            subscreen_dlg[3].h=172*(1+is_large);
                            subscreen_dlg[4].h=subscreen_dlg[3].h-4;
                            
                        }
                        else
                        {
                            css->ss_type=sstPASSIVE;
                            sprintf(css->name, passivesubscrtype_str[sstemplatelist_dlg[5].d1]);
                            subscreen_dlg[3].h=60*(1+is_large);
                            subscreen_dlg[4].h=subscreen_dlg[3].h-4;
                        }
                    }
                }
                else
                {
                    edit_it=false;
                }
            }
            
            if(edit_it)
            {
                edit_subscreen();
            }
        }
    }
    
    position_mouse_z(0);
    return D_O_K;
}

void update_sso_name()
{
    if(curr_subscreen_object<0)
    {
        sprintf(str_oname, "No object selected");
    }
    else
    {
        sprintf(str_oname, "%3d:  %s", curr_subscreen_object, sso_name(css->objects, curr_subscreen_object));
    }
    
    subscreen_dlg[5].flags|=D_DIRTY;
    subscreen_dlg[6].flags|=D_DIRTY;
}

void center_zq_subscreen_dialogs()
{
    jwin_center_dialog(grid_dlg);
    jwin_center_dialog(sel_options_dlg);
    jwin_center_dialog(sslist_dlg);
    jwin_center_dialog(ssolist_dlg);
    jwin_center_dialog(sso_master_properties_dlg);
    jwin_center_dialog(sstemplatelist_dlg);
    jwin_center_dialog(subscreen_dlg);
}

void delete_subscreen(int subscreenidx)
{
    if(custom_subscreen[subscreenidx].objects[0].type == ssoNULL)
        return;
        
    //delete
    reset_subscreen(&custom_subscreen[subscreenidx]);
    
    //and move all other subscreens up
    for(int i=subscreenidx+1; i<MAXCUSTOMSUBSCREENS; i++)
    {
        memcpy(&custom_subscreen[i-1], &custom_subscreen[i], sizeof(subscreen_group));
    }
    
    //fix dmaps
    int dmap_count=count_dmaps();
    
    for(int i=0; i<dmap_count; i++)
    {
        //decrement
        if(DMaps[i].active_subscreen > subscreenidx)
            DMaps[i].active_subscreen--;
            
        if(DMaps[i].passive_subscreen > subscreenidx)
            DMaps[i].passive_subscreen--;
    }
}

// These were defined in ffscript.h; no need for them here
#undef DELAY
#undef WIDTH
#undef HEIGHT

#define D1        0x00000001
#define D2        0x00000002
#define D3        0x00000004
#define D4        0x00000008
#define D5        0x00000010
#define D6        0x00000020
#define D7        0x00000040
#define D8        0x00000080
#define D9        0x00000100
#define D10       0x00000200
#define D1_TO_D10 0x000003FF
#define COLOR1    0x00000400
#define COLOR2    0x00000800
#define COLOR3    0x00001000
#define FRAMES    0x00002000
#define FRAME     0x00004000
#define SPEED     0x00008000
#define DELAY     0x00010000
#define WIDTH     0x00020000
#define HEIGHT    0x00040000

// This function does the actual copying. Name sucks, but whatever.
// what controls which properties are copied. Type, x, y, and dp1
// are never copied. The active up/down/scrolling flags from pos
// are always copied, but the rest of it is not.
void doCopySSOProperties(subscreen_object& src, subscreen_object& dest, int what)
{
    dest.pos&=~(sspUP|sspDOWN|sspSCROLLING);
    dest.pos|=src.pos&(sspUP|sspDOWN|sspSCROLLING);
    
    // Actually, I think pos is nothing but those three flags...
    
    if(what&WIDTH)
        dest.w=src.w;
    if(what&HEIGHT)
        dest.h=src.h;
    
    if(what&D1)
        dest.d1=src.d1;
    if(what&D2)
        dest.d2=src.d2;
    if(what&D3)
        dest.d3=src.d3;
    if(what&D4)
        dest.d4=src.d4;
    if(what&D5)
        dest.d5=src.d5;
    if(what&D6)
        dest.d6=src.d6;
    if(what&D7)
        dest.d7=src.d7;
    if(what&D8)
        dest.d8=src.d8;
    if(what&D9)
        dest.d9=src.d9;
    if(what&D10)
        dest.d10=src.d10;
    
    if(what&COLOR1)
    {
        dest.colortype1=src.colortype1;
        dest.color1=src.color1;
    }
    if(what&COLOR2)
    {
        dest.colortype2=src.colortype2;
        dest.color2=src.color2;
    }
    if(what&COLOR3)
    {
        dest.colortype3=src.colortype3;
        dest.color3=src.color3;
    }
    
    if(what&FRAMES)
        dest.frames=src.frames;
    if(what&FRAME)
        dest.frame=src.frame;
    if(what&SPEED)
        dest.speed=src.speed;
    if(what&DELAY)
        dest.delay=src.delay;
}

// Copies one object's properties to another. Selects properties depending on
// the object type; some things are deliberately skipped, like which heart
// container a life gauge piece corresponds to.
void copySSOProperties(subscreen_object& src, subscreen_object& dest)
{
    if(src.type!=dest.type || &src==&dest)
        return;
    
    switch(src.type)
    {
        case sso2X2FRAME:
            doCopySSOProperties(src, dest, D1|D2|D3|D4|COLOR1);
            break;
            
        case ssoTEXT:
            doCopySSOProperties(src, dest, D1|D2|D3|COLOR1|COLOR2|COLOR3);
            break;
            
        case ssoLINE:
            doCopySSOProperties(src, dest, D1|D2|COLOR1|WIDTH|HEIGHT);
            break;
            
        case ssoRECT:
            doCopySSOProperties(src, dest, D1|D2|COLOR1|COLOR2|WIDTH|HEIGHT);
            break;
            
        case ssoBSTIME:
        case ssoTIME:
        case ssoSSTIME:
            doCopySSOProperties(src, dest, D1|D2|D3|COLOR1|COLOR2|COLOR3);
            break;
            
        case ssoMAGICMETER: // Full meter
            // No properties but pos
            doCopySSOProperties(src, dest, 0);
            break;
            
        case ssoLIFEMETER:
            doCopySSOProperties(src, dest, D2|D3);
            break;
            
        case ssoBUTTONITEM:
            doCopySSOProperties(src, dest, D2);
            break;
            
        case ssoCOUNTER: // Single counter
            doCopySSOProperties(src, dest, D1|D2|D3|D4|D5|D6|COLOR1|COLOR2|COLOR3);
            break;
            
        case ssoCOUNTERS: // Counter block
            doCopySSOProperties(src, dest, D1|D2|D3|D4|D5|COLOR1|COLOR2|COLOR3);
            break;
            
        case ssoMINIMAPTITLE:
            doCopySSOProperties(src, dest, D1|D2|D3|D4|COLOR1|COLOR2|COLOR3);
            break;
            
        case ssoMINIMAP:
            doCopySSOProperties(src, dest, D1|D2|D3|COLOR1|COLOR2|COLOR3);
            break;
            
        case ssoLARGEMAP:
            doCopySSOProperties(src, dest, D1|D2|D3|D10|COLOR1|COLOR2);
            break;
            
        case ssoCLEAR:
            doCopySSOProperties(src, dest, COLOR1);
            break;
            
        case ssoCURRENTITEM:
            // Only the invisible flag
            doCopySSOProperties(src, dest, D2);
            break;
            
        case ssoTRIFRAME:
            doCopySSOProperties(src, dest, D1|D2|D3|D4|D5|D6|D7|COLOR1|COLOR2);
            break;
            
        case ssoTRIFORCE: // Single piece
            doCopySSOProperties(src, dest, D1|D2|D3|D4|COLOR1);
            break;
            
        case ssoTILEBLOCK:
            doCopySSOProperties(src, dest, D1|D2|D3|D4|COLOR1|WIDTH|HEIGHT);
            break;
            
        case ssoMINITILE:
            // Does this one work at all?
            doCopySSOProperties(src, dest, D1|D2|D3|D4|D5|D6|COLOR1|WIDTH|HEIGHT);
            break;
            
        case ssoSELECTOR1:
        case ssoSELECTOR2:
            doCopySSOProperties(src, dest, D1|D2|D3|D4|D5|COLOR1);
            break;
            
        case ssoMAGICGAUGE: // Single piece
            // Skip magic container (d1)
            doCopySSOProperties(src, dest, (D1_TO_D10&~D1)|COLOR1|COLOR2|WIDTH|HEIGHT);
            break;
            
        case ssoLIFEGAUGE: // Single piece
            // Skip heart container (d1)
            doCopySSOProperties(src, dest, (D1_TO_D10&~D1)|COLOR1|COLOR2|WIDTH|HEIGHT);
            break;
            
        case ssoTEXTBOX:
        case ssoSELECTEDITEMNAME:
            doCopySSOProperties(src, dest, D1|D2|D3|D4|D5|COLOR1|COLOR2|COLOR3|WIDTH|HEIGHT);
            break;
    }
}

/*** end of subscr.cc ***/


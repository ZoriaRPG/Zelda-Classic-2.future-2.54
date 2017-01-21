//--------------------------------------------------------
//  Zelda Classic
//  by Jeremy Craner, 1999-2000
//
//  zsys.cc
//
//  System functions, etc.
//
//--------------------------------------------------------

#include "precompiled.h" //always first

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "zc_alleg.h"
#include <allegro/internal/aintern.h>
#include <string>

using std::string;

#ifdef ALLEGRO_DOS
#include <conio.h>
#endif

#include "zdefs.h"
#include "zsys.h"
#include "zc_sys.h"
#include "jwin.h"
#include "mem_debug.h"

#ifdef _MSC_VER
#define stricmp _stricmp
#endif

//#ifdef _ZQUEST_SCALE_
extern volatile int myvsync;
extern int zqwin_scale;
extern BITMAP *hw_screen;
//#endif

extern bool is_zquest();
bool zconsole = false;

char *time_str_long(dword time)
{
    static char s[16];
    
    dword decs = (time%60)*100/60;
    dword secs = (time/60)%60;
    dword mins = (time/3600)%60;
    dword hours = time/216000;
    
    sprintf(s,"%ld:%02ld:%02ld.%02ld",hours,mins,secs,decs);
    return s;
}

char *time_str_med(dword time)
{
    static char s[16];
    
    dword secs = (time/60)%60;
    dword mins = (time/3600)%60;
    dword hours = time/216000;
    
    sprintf(s,"%ld:%02ld:%02ld",hours,mins,secs);
    return s;
}

char *time_str_short(dword time)
{
    static char s[16];
    
    dword mins = (time/3600)%60;
    dword hours = time/216000;
    
    sprintf(s,"%ld:%02ld",hours,mins);
    return s;
}

char *time_str_short2(dword time)
{
    static char s[16];
    
    dword mins = (time/3600)%60;
    dword hours = time/216000;
    
    sprintf(s,"%02ld%s%02ld",hours,(time%60)<30?":":";",mins);
    return s;
}

void extract_name(char *path,char *name,int type)
{
    int l=(int)strlen(path);
    int i=l;
    
    while(i>0 && path[i-1]!='/' && path[i-1]!='\\')
        --i;
        
    int n=0;
    
    if(type==FILENAME8__)
    {
        while(i<l && n<8 && path[i]!='.')
            name[n++]=path[i++];
    }
    else if(type==FILENAME8_3)
    {
        while(i<l && n<12)
            name[n++]=path[i++];
    }
    else
    {
        while(i<l)
            name[n++]=path[i++];
    }
    
    name[n]=0;
}

void temp_name(char temporaryname[])
{
    int tempnum;
    
    for(int i=0; i<1000; ++i)
    {
        sprintf(temporaryname, "%s", "00000000.tmp");
        
        for(int j=0; j<8; ++j)
        {
            tempnum=rand()%62;
            
            if(tempnum<26)
            {
                temporaryname[j]='A'+tempnum;
            }
            else if(tempnum<52)
            {
                temporaryname[j]='a'+tempnum-26;
            }
            else
            {
                temporaryname[j]='0'+tempnum-52;
            }
        }
        
        if(!exists(temporaryname))
        {
            return;
        }
    }
}

int bound(int &x,int low,int high)
{
    if(x<low) x=low;
    
    if(x>high) x=high;
    
    return x;
}

char *snapshotformat_str[ssfmtMAX][2]=
{
    { (char *)"BMP", (char *)"bmp"},
    { (char *)"GIF", (char *)"gif"},
    { (char *)"JPG", (char *)"jpg"},
    { (char *)"PNG", (char *)"png"},
    { (char *)"PCX", (char *)"pcx"},
    { (char *)"TGA", (char *)"tga"},
};

const char *snapshotformatlist(int index, int *list_size)
{
    if(index>=0)
    {
        bound(index,0,ssfmtMAX);
        return snapshotformat_str[index][0];
    }
    
    *list_size=ssfmtMAX;
    return NULL;
}


//Allegro's make_relative_filename doesn't handle uppercase/lowercase too well for drive letters
char *zc_make_relative_filename(char *dest, const char *path, const char *filename, int size)
{
#ifdef ALLEGRO_LINUX
    return make_relative_filename(dest, path, filename, size);
#elif defined(ALLEGRO_MACOSX)
    return make_relative_filename(dest, path, filename, size);
#else
    char *tpath = new char[size+1];
    make_relative_filename(dest, path, filename, size);
    
    if(dest[0]==0) //can't make relative path
    {
        sprintf(tpath, "%s", path);
        int temp = ugetc(tpath);
    
        if(ugetat(tpath, 1) == DEVICE_SEPARATOR)
        {
            if((temp >= 'A') && (temp <= 'Z'))
            {
                usetat(tpath,0,utolower(temp));
            }
            else if((temp >= 'a') && (temp <= 'a'))
            {
                usetat(tpath,0,utoupper(temp));
            }
    
            make_relative_filename(dest, tpath, filename, size);
        }
    }
    
    delete[] tpath;
    return dest;
#endif
}



void chop_path(char *path)
{
    int p = (int)strlen(path);
    int f = (int)strlen(get_filename(path));
    
    if(f<p)
        path[p-f]=0;
}

int vbound(int x,int low,int high)
{
    assert(low <= high);
    
    if(x<low) return low;
    
    if(x>high) return high;
    
    return x;
}

float vbound(float x,float low,float high)
{
    if(x<low) return low;
    
    if(x>high) return high;
    
    return x;
}

int used_switch(int argc,char *argv[],const char *s)
{
    // assumes a switch won't be in argv[0]
    for(int i=1; i<argc; i++)
        if(stricmp(argv[i],s)==0)
            return i;
            
    return 0;
}
//There is some hardcore constant truncation here...
#ifdef _MSC_VER
#pragma warning(disable: 4309)
#pragma warning(disable: 4310)
#endif


char zeldapwd[8]  = { char('N'+11),char('0'+22),char('S'+33),char('7'+44),char('1'+55),char('M'+66),char('3'+77), char(0 +88) };
//char zquestpwd[8] = { 'C'+11,'a'+22,'o'+33,'M'+44,'e'+55,'i'+66,'7'+77, 0 +88 };
//char zquestpwd[8] = { 'N'+11,'g'+22,'o'+33,'m'+44,'o'+55,'n'+66,'g'+77, 0 +88 };
//char zquestpwd[8] = { 'C'+11,'a'+22,'n'+33,'t'+44,'i'+55,'k'+66,'a'+77,0+88 };
char zquestpwd[8] = { char('S'+11),char('3'+22),char('('+33),char('r'+44),char('3'+55),char('7'+66),char('!'+77), char(0 +88) };
char datapwd[8]   = { char('l'+11),char('o'+22),char('n'+33),char('g'+44),char('t'+55),char('a'+66),char('n'+77),char(0+88) };

#ifdef _MSC_VER
#pragma warning(default: 4309)
#endif

void resolve_password(char *pwd)
{
    for(int i=0; i<8; i++)
        pwd[i]-=(i+1)*11;
}

void set_bit(byte *bitstr,int bit,byte val)
{
    bitstr += bit>>3;
    byte mask = 1 << (bit&7);
    
    if(val)
        *bitstr |= mask;
    else
        *bitstr &= ~mask;
}

int get_bit(byte *bitstr,int bit)
{
    bitstr += bit>>3;
    return ((*bitstr) >> (bit&7))&1;
}

void Z_error(const char *format,...)
{
    char buf[256];
    
    va_list ap;
    va_start(ap, format);
    vsprintf(buf, format, ap);
    va_end(ap);
    
#if defined(ALLEGRO_DOS ) || defined(ALLEGRO_MAXOSX)
    printf("%s\n",buf);
#endif
    al_trace("%s\n",buf);
    exit(1);
}

void Z_message(const char *format,...)
{
    char buf[2048];
    
    va_list ap;
    va_start(ap, format);
    vsprintf(buf, format, ap);
    va_end(ap);
    
#if defined(ALLEGRO_DOS ) || defined(ALLEGRO_MAXOSX)
    printf("%s",buf);
#endif
    al_trace("%s",buf);
    
    if(zconsole)
        printf("%s",buf);
}

void Z_title(const char *format,...)
{
    char buf[256];
    va_list ap;
    va_start(ap, format);
    vsprintf(buf, format, ap);
    va_end(ap);
    
#ifdef ALLEGRO_DOS
    text_info ti;
    gettextinfo(&ti);
    int w = ti.screenwidth;
    
    int len = strlen(buf);
    
    if(len>w)
        printf("%s\n",buf);
    else
    {
        char title[81];
        
        for(int i=0; i<w; i++)
            title[i]=' ';
            
        title[w]=0;
        
        int center = (w - len) >> 1;
        memcpy(title+center,buf,len);
        
        printf("\n");
        textattr(0x4E);
        cprintf("%s",title);
        textattr(0x07);
        
        for(int i=0; i<w; i++)
            cprintf(" ");
    }
    
#else
    al_trace("%s\n",buf);
    
    if(zconsole)
        printf("%s\n",buf);
    
#endif
}

int anim_3_4(int clk, int speed)
{
    clk /= speed;
    
    switch(clk&3)
    {
    case 0:
    case 2:
        clk = 0;
        break;
        
    case 1:
        clk = 1;
        break;
        
    case 3:
        clk = 2;
        break;
    }
    
    return clk;
}

/**********  Encryption Stuff  *****************/

//#define MASK 0x4C358938
static int seed = 0;
//#define MASK 0x91B2A2D1
//static int seed = 7351962;
static int enc_mask[ENC_METHOD_MAX]= {0x4C358938,0x91B2A2D1,0x4A7C1B87,0xF93941E6,0xFD095E94};
static int pvalue[ENC_METHOD_MAX]= {0x62E9,0x7D14,0x1A82,0x02BB,0xE09C};
static int qvalue[ENC_METHOD_MAX]= {0x3619,0xA26B,0xF03C,0x7B12,0x4E8F};

static int rand_007(int method)
{
    short BX = seed >> 8;
    short CX = (seed & 0xFF) << 8;
    signed char AL = seed >> 24;
    signed char C = AL >> 7;
    signed char D = BX >> 15;
    AL <<= 1;
    BX = (BX << 1) | C;
    CX = (CX << 1) | D;
    CX += seed & 0xFFFF;
    BX += (seed >> 16) + C;
    //  CX += 0x62E9;
    //  BX += 0x3619 + D;
    CX += pvalue[method];
    BX += qvalue[method] + D;
    seed = (BX << 16) + CX;
    return (CX << 16) + BX;
}

void encode_007(byte *buf, dword size, dword key2, word *check1, word *check2, int method)
{
    dword i;
    byte *p;
    
    *check1 = 0;
    *check2 = 0;
    
    p = buf;
    
    for(i=0; i<size; i++)
    {
        *check1 += *p;
        *check2 = (*check2 << 4) + (*check2 >> 12) + *p;
        ++p;
    }
    
    p = buf;
    seed = key2;
    
    for(i=0; i<size; i+=2)
    {
        byte q = rand_007(method);
        *p ^= q;
        ++p;
        
        if(i+1 < size)
        {
            *p += q;
            ++p;
        }
    }
}

bool decode_007(byte *buf, dword size, dword key2, word check1, word check2, int method)
{
    dword i;
    word c1 = 0, c2 = 0;
    byte *p;
    
    p = buf;
    seed = key2;
    
    for(i=0; i<size; i+=2)
    {
        unsigned char q = rand_007(method);
        *p ^= q;
        ++p;
        
        if(i+1 < size)
        {
            *p -= q;
            ++p;
        }
    }
    
    p = buf;
    
    for(i=0; i<size; i++)
    {
        c1 += *p;
        c2 = (c2 << 4) + (c2 >> 12) + *p;
        ++p;
    }
    
    return (c1 == check1) && (c2 == check2);
}

//
// RETURNS:
//   0 - OK
//   1 - srcfile not opened
//   2 - destfile not opened
//
int encode_file_007(const char *srcfile, const char *destfile, int key2, const char *header, int method)
{
    FILE *src, *dest;
    int tog = 0, c, r=0;
    short c1 = 0, c2 = 0;
    
    seed = key2;
    src = fopen(srcfile, "rb");
    
    if(!src)
        return 1;
        
    dest = fopen(destfile, "wb");
    
    if(!dest)
    {
        fclose(src);
        return 2;
    }
    
    
    // write the header
    if(header)
    {
        for(c=0; header[c]; c++)
            fputc(header[c], dest);
    }
    
    // write the key, XORed with MASK
    key2 ^= enc_mask[method];
    fputc(key2>>24, dest);
    fputc((key2>>16)&255, dest);
    fputc((key2>>8)&255, dest);
    fputc(key2&255, dest);
    
    // encode the data
    while((c=fgetc(src)) != EOF)
    {
        c1 += c;
        c2 = (c2 << 4) + (c2 >> 12) + c;
        
        if(tog)
            c += r;
        else
        {
            r = rand_007(method);
            c ^= r;
        }
        
        tog ^= 1;
        
        fputc(c, dest);
    }
    
    // write the checksums
    r = rand_007(method);
    c1 ^= r;
    c2 += r;
    fputc(c1>>8, dest);
    fputc(c1&255, dest);
    fputc(c2>>8, dest);
    fputc(c2&255, dest);
    
    fclose(src);
    fclose(dest);
    return 0;
}

//
// RETURNS:
//   0 - OK
//   1 - srcfile not opened
//   2 - destfile not opened
//   3 - scrfile too small
//   4 - srcfile EOF
//   5 - checksum mismatch
//   6 - header mismatch
//
int decode_file_007(const char *srcfile, const char *destfile, const char *header, int method, bool packed, const char *password)
{
    FILE *normal_src=NULL, *dest=NULL;
    PACKFILE *packed_src=NULL;
    int tog = 0, c, r=0, err;
    long size, i;
    short c1 = 0, c2 = 0, check1, check2;
    
    // open files
    size = file_size_ex_password(srcfile, password);
    
    if(size < 1)
    {
        return 1;
    }
    
    size -= 8;                                                // get actual data size, minus key and checksums
    
    if(size < 1)
    {
        return 3;
    }
    
    if(!packed)
    {
        normal_src = fopen(srcfile, "rb");
        
        if(!normal_src)
        {
            return 1;
        }
    }
    else
    {
        packed_src = pack_fopen_password(srcfile, F_READ_PACKED,password);
        
        if(errno==EDOM)
        {
            packed_src = pack_fopen_password(srcfile, F_READ,password);
        }
        
        if(!packed_src)
        {
            return 1;
        }
    }
    
    dest = fopen(destfile, "wb");
    
    if(!dest)
    {
        if(packed)
        {
            pack_fclose(packed_src);
        }
        else
        {
            fclose(normal_src);
        }
        
        return 2;
    }
    
    // read the header
    err = 4;
    
    if(header)
    {
        for(i=0; header[i]; i++)
        {
            if(packed)
            {
                if((c=pack_getc(packed_src)) == EOF)
                {
                    goto error;
                }
            }
            else
            {
                if((c=fgetc(normal_src)) == EOF)
                {
                    goto error;
                }
            }
            
            if((c&255) != header[i])
            {
                err = 6;
                goto error;
            }
            
            --size;
        }
    }
    
    // read the key
    if(packed)
    {
        if((c=pack_getc(packed_src)) == EOF)
        {
            goto error;
        }
    }
    else
    {
        if((c=fgetc(normal_src)) == EOF)
        {
            goto error;
        }
    }
    
    seed = c << 24;
    
    if(packed)
    {
        if((c=pack_getc(packed_src)) == EOF)
        {
            goto error;
        }
    }
    else
    {
        if((c=fgetc(normal_src)) == EOF)
        {
            goto error;
        }
    }
    
    seed += (c & 255) << 16;
    
    if(packed)
    {
        if((c=pack_getc(packed_src)) == EOF)
        {
            goto error;
        }
    }
    else
    {
        if((c=fgetc(normal_src)) == EOF)
        {
            goto error;
        }
    }
    
    seed += (c & 255) << 8;
    
    if(packed)
    {
        if((c=pack_getc(packed_src)) == EOF)
        {
            goto error;
        }
    }
    else
    {
        if((c=fgetc(normal_src)) == EOF)
        {
            goto error;
        }
    }
    
    seed += c & 255;
    seed ^= enc_mask[method];
    
    // decode the data
    for(i=0; i<size; i++)
    {
        if(packed)
        {
            if((c=pack_getc(packed_src)) == EOF)
            {
                goto error;
            }
        }
        else
        {
            if((c=fgetc(normal_src)) == EOF)
            {
                goto error;
            }
        }
        
        if(tog)
        {
            c -= r;
        }
        else
        {
            r = rand_007(method);
            c ^= r;
        }
        
        tog ^= 1;
        
        c &= 255;
        c1 += c;
        c2 = (c2 << 4) + (c2 >> 12) + c;
        
        fputc(c, dest);
    }
    
    // read checksums
    if(packed)
    {
        if((c=pack_getc(packed_src)) == EOF)
        {
            goto error;
        }
    }
    else
    {
        if((c=fgetc(normal_src)) == EOF)
        {
            goto error;
        }
    }
    
    check1 = c << 8;
    
    if(packed)
    {
        if((c=pack_getc(packed_src)) == EOF)
        {
            goto error;
        }
    }
    else
    {
        if((c=fgetc(normal_src)) == EOF)
        {
            goto error;
        }
    }
    
    check1 += c & 255;
    
    if(packed)
    {
        if((c=pack_getc(packed_src)) == EOF)
        {
            goto error;
        }
    }
    else
    {
        if((c=fgetc(normal_src)) == EOF)
        {
            goto error;
        }
    }
    
    check2 = c << 8;
    
    if(packed)
    {
        if((c=pack_getc(packed_src)) == EOF)
        {
            goto error;
        }
    }
    else
    {
        if((c=fgetc(normal_src)) == EOF)
        {
            goto error;
        }
    }
    
    check2 += c & 255;
    
    // verify checksums
    r = rand_007(method);
    check1 ^= r;
    check2 -= r;
    check1 &= 0xFFFF;
    check2 &= 0xFFFF;
    
    if(check1 != c1 || check2 != c2)
    {
        err = 5;
        goto error;
    }
    
    if(packed)
    {
        pack_fclose(packed_src);
    }
    else
    {
        fclose(normal_src);
    }
    
    fclose(dest);
    return 0;
    
error:

    if(packed)
    {
        pack_fclose(packed_src);
    }
    else
    {
        fclose(normal_src);
    }
    
    fclose(dest);
    delete_file(destfile);
    return err;
}

void copy_file(const char *src, const char *dest)
{
    int c;
    FILE *fin, *fout;
    fin = fopen(src, "rb");
    fout = fopen(dest, "wb");
    
    while((c=fgetc(fin)) != EOF)
        fputc(c, fout);
        
    fclose(fin);
    fclose(fout);
}
/*
#define BOX_W     MIN(512, SCREEN_W-16)
#define BOX_H     MIN(256, (SCREEN_H-64)&0xFFF0)

#define BOX_L     ((SCREEN_W - BOX_W) / 2)
#define BOX_R     ((SCREEN_W + BOX_W) / 2)
#define BOX_T     ((SCREEN_H - BOX_H) / 2)
#define BOX_B     ((SCREEN_H + BOX_H) / 2)
*/
static int box_x = 0;
static int box_y = 0;
static bool box_active=false;
static int box_store_x = 0;
static FONT *box_title_font=font;
static FONT *box_message_font=font;
static int box_style=0;
static int box_titlebar_height=0;
static int box_message_height=0;
static int box_w=304;
static int box_h=176;
static int box_l=8;
static int box_r=312;
static int box_t=32;
static int box_b=208;
static bool box_log=true;
static char box_log_msg[480];
static int box_msg_pos=0;
static int box_store_pos=0;
/*
  static int jwin_pal[jcMAX] =
  {
  vc(11),vc(15),vc(4),vc(7),vc(6),vc(0),
  192,223,vc(14),vc(15),vc(0),vc(1),vc(14)
  };
  */
int onSnapshot2()
{
    char buf[20];
    int num=0;
    
    do
    {
        sprintf(buf, "zelda%03d.bmp", ++num);
    }
    while(num<999 && exists(buf));
    
    PALETTE temppal;
    get_palette(temppal);
    BITMAP *tempbmp=create_bitmap_ex(8,screen->w, screen->h);
    blit(screen,tempbmp,0,0,0,0,screen->w,screen->h);
    save_bitmap(buf,screen,temppal);
    destroy_bitmap(tempbmp);
    return D_O_K;
}

void set_default_box_size()
{
    int screen_w=SCREEN_W;
    int screen_h=SCREEN_H;
    
    if(zqwin_scale>1)
    {
        screen_w/=zqwin_scale;
        screen_h/=zqwin_scale;
    }
    
    box_w=MIN(512, screen_w-16);
    box_h=MIN(256, (screen_h-64)&0xFFF0);
    
    box_l=(screen_w-box_w)/2;
    box_t=(screen_h-box_h)/2;
    box_r=box_l+box_w;
    box_b=box_t+box_h;
}

/* starts outputting a progress message */
void box_start(int style, const char *title, FONT *title_font, FONT *message_font, bool log)
{
    box_style=style;
    box_title_font=(title_font!=NULL)?title_font:font;
    box_message_font=(message_font!=NULL)?message_font:font;
    box_message_height=text_height(box_message_font);
    box_titlebar_height=title?text_height(box_title_font)+2:0;
    set_default_box_size();
    /*
    box_w=BOX_W;
    box_h=BOX_H;
    box_l=BOX_L;
    box_r=BOX_R;
    box_t=BOX_T;
    box_b=BOX_B;
    */
    box_log=log;
    memset(box_log_msg, 0, 480);
    box_msg_pos=0;
    box_store_pos=0;
    scare_mouse();
    
    jwin_draw_win(screen, box_l, box_t, box_r-box_l, box_b-box_t, FR_WIN);
    
    if(title!=NULL)
    {
        zc_swap(font,box_title_font);
        jwin_draw_titlebar(screen, box_l+3, box_t+3, box_r-box_l-6, 18, title, false);
        zc_swap(font,box_title_font);
        box_titlebar_height=18;
    }
    
    unscare_mouse();
    
    box_store_x = box_x = box_y = 0;
    box_active = true;
    box_t+=box_titlebar_height;
    box_h-=box_titlebar_height;
    box_log=log;
    memset(box_log_msg, 0, 480);
    box_msg_pos=0;
    box_store_pos=0;
}

/* outputs text to the progress message */
void box_out(const char *msg)
{
    string remainder = "";
    string temp(msg);
    
    if(box_active)
    {
        scare_mouse();
        //do primitive text wrapping
        unsigned int i;
        
        for(i=0; i<temp.size(); i++)
        {
            int length = text_length(box_message_font,temp.substr(0,i).c_str());
            
            if(length > box_r-box_l-16)
            {
                i = zc_max(i-1,0);
                break;
            }
        }
        
        set_clip_rect(screen, box_l+8, box_t+1, box_r-8, box_b-1);
        textout_ex(screen, box_message_font, temp.substr(0,i).c_str(), box_l+8+box_x, box_t+(box_y+1)*box_message_height, gui_fg_color, gui_bg_color);
        set_clip_rect(screen, 0, 0, SCREEN_W-1, SCREEN_H-1);
        unscare_mouse();
        remainder = temp.substr(i,temp.size()-i);
    }
    
    if(box_log)
    {
        sprintf(box_log_msg+box_msg_pos, "%s", msg);
    }
    
    box_x += text_length(box_message_font, msg);
    box_msg_pos+=(int)strlen(msg);
    
    if(remainder != "")
    {
        bool oldlog = box_log;
        box_log = false;
        box_eol();
        box_out(remainder.c_str());
        box_log = oldlog;
    }
    
    //	#ifdef _ZQUEST_SCALE_
    if(is_zquest())
    {
        //if(myvsync)
        {
            if(zqwin_scale > 1)
            {
                stretch_blit(screen, hw_screen, 0, 0, screen->w, screen->h, 0, 0, hw_screen->w, hw_screen->h);
            }
            else
            {
                blit(screen, hw_screen, 0, 0, 0, 0, screen->w, screen->h);
            }
            
            myvsync=0;
        }
    }
    
    //	#endif
}

/* remembers the current x position */
void box_save_x()
{
    if(box_active)
    {
        box_store_x=box_x;
    }
    
    box_store_pos=box_msg_pos;
}

/* remembers the current x position */
void box_load_x()
{
    if(box_active)
    {
        box_x=box_store_x;
    }
    
    box_msg_pos=box_store_pos;
}

/* outputs text to the progress message */
void box_eol()
{
    if(box_active)
    {
        box_x = 0;
        box_y++;
        
        if((box_y+2)*box_message_height >= box_h)
        {
            scare_mouse();
            blit(screen, screen, box_l+8, box_t+(box_message_height*2), box_l+8, box_t+(box_message_height), box_w-16, box_y*box_message_height);
            rectfill(screen, box_l+8, box_t+box_y*box_message_height, box_l+box_w-8, box_t+(box_y+1)*box_message_height, gui_bg_color);
            unscare_mouse();
            box_y--;
        }
    }
    
    box_msg_pos = 0;
    
    if(box_log)
    {
        al_trace("%s", box_log_msg);
        al_trace("\n");
        memset(box_log_msg, 0, 480);
    }
    
    //	#ifdef _ZQUEST_SCALE_
    if(is_zquest())
    {
        //if(myvsync)
        {
            if(zqwin_scale > 1)
            {
                stretch_blit(screen, hw_screen, 0, 0, screen->w, screen->h, 0, 0, hw_screen->w, hw_screen->h);
            }
            else
            {
                blit(screen, hw_screen, 0, 0, 0, 0, screen->w, screen->h);
            }
            
            myvsync=0;
        }
    }
    
    //	#endif
}

/* ends output of a progress message */
void box_end(bool pause)
{
    if(box_active)
    {
        if(pause)
        {
            box_eol();
            box_out("-- press a key --");
            
            do
            {
                //        poll_mouse();
            }
            while(gui_mouse_b());
            
            do
            {
                //        poll_mouse();
            }
            while((!keypressed()) && (!gui_mouse_b()));
            
            do
            {
                //        poll_mouse();
            }
            while(gui_mouse_b());
            
            clear_keybuf();
        }
        
        box_active = false;
    }
}

/* pauses box output */
void box_pause()
{
    if(box_active)
    {
        box_save_x();
        box_out("-- press a key --");
        
        do
        {
            //        poll_mouse();
        }
        while(gui_mouse_b());
        
        do
        {
            //        poll_mouse();
        }
        while((!keypressed()) && (!gui_mouse_b()));
        
        do
        {
            //        poll_mouse();
        }
        while(gui_mouse_b());
        
        clear_keybuf();
        box_load_x();
    }
}

// Checking for double clicks is complicated. The user could release the
// mouse button at almost any point, and I might miss it if I am doing some
// other processing at the same time (eg. sending the single-click message).
// To get around this I install a timer routine to do the checking for me,
// so it will notice double clicks whenever they happen.

volatile int dclick_status, dclick_time;

// dclick_check:
//  Double click checking user timer routine.

void dclick_check(void)
{
    if(dclick_status==DCLICK_NOT)
    {
        if(gui_mouse_b())
        {
            dclick_status = DCLICK_START;           // let's go!
            dclick_time = 0;
            return;
        }
    }
    else if(dclick_status==DCLICK_START)                 // first click...
    {
        if(!gui_mouse_b())
        {
            dclick_status = DCLICK_RELEASE;           // aah! released first
            dclick_time = 0;
            return;
        }
    }
    else if(dclick_status==DCLICK_RELEASE)          // wait for second click
    {
        if(gui_mouse_b())
        {
            dclick_status = DCLICK_AGAIN;             // yes! the second click
            dclick_time = 0;
            return;
        }
    }
    else
    {
        return;
    }
    
    // timeout?
    if(dclick_time++ > 10)
    {
        dclick_status = DCLICK_NOT;
    }
}

END_OF_FUNCTION(dclick_check)

void lock_dclick_function()
{
    LOCK_FUNCTION(dclick_check);
}


void textout_shadow_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    if(bg!=-1)
    {
        rectfill(bmp, x, y, x+text_length(f, s), y+text_height(f), bg);
    }
    
    textout_ex(bmp, f, s, x+1, y, shadow, -1);
    textout_ex(bmp, f, s, x+1, y+1, shadow, -1);
    textout_ex(bmp, f, s, x, y+1, shadow, -1);
}

void textout_shadow_centre_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    textout_shadow_ex(bmp, f, s, x-(text_length(f, s)/2), y, shadow, bg);
}

void textout_shadow_right_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    textout_shadow_ex(bmp, f, s, x-text_length(f, s), y, shadow, bg);
}

void textout_shadow_u_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    if(bg!=-1)
    {
        rectfill(bmp, x-1, y, x+text_length(f, s), y+text_height(f), bg);
    }
    
    textout_ex(bmp, f, s, x+1, y, shadow, -1);
    textout_ex(bmp, f, s, x+1, y+1, shadow, -1);
    textout_ex(bmp, f, s, x, y+1, shadow, -1);
    textout_ex(bmp, f, s, x-1, y+1, shadow, -1);
    textout_ex(bmp, f, s, x-1, y, shadow, -1);
}

void textout_shadow_centre_u_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    textout_shadow_u_ex(bmp, f, s, x-(text_length(f, s)/2), y, shadow, bg);
}

void textout_shadow_right_u_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    textout_shadow_u_ex(bmp, f, s, x-text_length(f, s), y, shadow, bg);
}

void textout_shadow_o_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    if(bg!=-1)
    {
        rectfill(bmp, x-1, y-1, x+text_length(f, s), y+text_height(f), bg);
    }
    
    textout_ex(bmp, f, s, x+1, y-1, shadow, -1);
    textout_ex(bmp, f, s, x+1, y, shadow, -1);
    textout_ex(bmp, f, s, x+1, y+1, shadow, -1);
    textout_ex(bmp, f, s, x, y+1, shadow, -1);
    textout_ex(bmp, f, s, x-1, y+1, shadow, -1);
    textout_ex(bmp, f, s, x-1, y, shadow, -1);
    textout_ex(bmp, f, s, x-1, y-1, shadow, -1);
    textout_ex(bmp, f, s, x, y-1, shadow, -1);
}

void textout_shadow_centre_o_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    textout_shadow_o_ex(bmp, f, s, x-(text_length(f, s)/2), y, shadow, bg);
}

void textout_shadow_right_o_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    textout_shadow_o_ex(bmp, f, s, x-text_length(f, s), y, shadow, bg);
}

void textout_shadow_plus_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    if(bg!=-1)
    {
        rectfill(bmp, x-1, y-1, x+text_length(f, s), y+text_height(f), bg);
    }
    
    textout_ex(bmp, f, s, x+1, y, shadow, -1);
    textout_ex(bmp, f, s, x, y+1, shadow, -1);
    textout_ex(bmp, f, s, x-1, y, shadow, -1);
    textout_ex(bmp, f, s, x, y-1, shadow, -1);
}

void textout_shadow_centre_plus_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    textout_shadow_plus_ex(bmp, f, s, x-(text_length(f, s)/2), y, shadow, bg);
}

void textout_shadow_right_plus_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    textout_shadow_plus_ex(bmp, f, s, x-text_length(f, s), y, shadow, bg);
}

void textout_shadow_x_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    if(bg!=-1)
    {
        rectfill(bmp, x-1, y-1, x+text_length(f, s), y+text_height(f), bg);
    }
    
    textout_ex(bmp, f, s, x+1, y-1, shadow, -1);
    textout_ex(bmp, f, s, x+1, y+1, shadow, -1);
    textout_ex(bmp, f, s, x-1, y+1, shadow, -1);
    textout_ex(bmp, f, s, x-1, y-1, shadow, -1);
}

void textout_shadow_centre_x_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    textout_shadow_x_ex(bmp, f, s, x-(text_length(f, s)/2), y, shadow, bg);
}

void textout_shadow_right_x_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int shadow, int bg)
{
    textout_shadow_x_ex(bmp, f, s, x-text_length(f, s), y, shadow, bg);
}

void textout_shadowed_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadow_ex(bmp, f, s, x, y, shadow, bg);
    textout_ex(bmp, f, s, x, y, color, -1);
}

void textout_shadowed_centre_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadowed_ex(bmp, f, s, x-(text_length(f, s)/2), y, color, shadow, bg);
}

void textout_shadowed_right_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadowed_ex(bmp, f, s, x-text_length(f, s), y, color, shadow, bg);
}

void textout_shadowed_u_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadow_u_ex(bmp, f, s, x, y, shadow, bg);
    textout_ex(bmp, f, s, x, y, color, -1);
}

void textout_shadowed_centre_u_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadowed_u_ex(bmp, f, s, x-(text_length(f, s)/2), y, color, shadow, bg);
}

void textout_shadowed_right_u_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadowed_u_ex(bmp, f, s, x-text_length(f, s), y, color, shadow, bg);
}

void textout_shadowed_o_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadow_o_ex(bmp, f, s, x, y, shadow, bg);
    textout_ex(bmp, f, s, x, y, color, -1);
}

void textout_shadowed_centre_o_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadowed_o_ex(bmp, f, s, x-(text_length(f, s)/2), y, color, shadow, bg);
}

void textout_shadowed_right_o_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadowed_o_ex(bmp, f, s, x-text_length(f, s), y, color, shadow, bg);
}

void textout_shadowed_plus_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadow_plus_ex(bmp, f, s, x, y, shadow, bg);
    textout_ex(bmp, f, s, x, y, color, -1);
}

void textout_shadowed_centre_plus_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadowed_plus_ex(bmp, f, s, x-(text_length(f, s)/2), y, color, shadow, bg);
}

void textout_shadowed_right_plus_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadowed_plus_ex(bmp, f, s, x-text_length(f, s), y, color, shadow, bg);
}

void textout_shadowed_x_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadow_x_ex(bmp, f, s, x, y, shadow, bg);
    textout_ex(bmp, f, s, x, y, color, -1);
}

void textout_shadowed_centre_x_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadowed_x_ex(bmp, f, s, x-(text_length(f, s)/2), y, color, shadow, bg);
}

void textout_shadowed_right_x_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int shadow, int bg)
{
    textout_shadowed_x_ex(bmp, f, s, x-text_length(f, s), y, color, shadow, bg);
}

void textprintf_shadow_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_ex(bmp, f, buf, x, y, shadow, bg);
}

void textprintf_shadow_centre_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_ex(bmp, f, buf, x-(text_length(f, buf)/2), y, shadow, bg);
}

void textprintf_shadow_right_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_ex(bmp, f, buf, x-text_length(f, buf), y, shadow, bg);
}


void textprintf_shadow_u_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_u_ex(bmp, f, buf, x, y, shadow, bg);
}

void textprintf_shadow_centre_u_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_u_ex(bmp, f, buf, x-(text_length(f, buf)/2), y, shadow, bg);
}

void textprintf_shadow_right_u_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_u_ex(bmp, f, buf, x-text_length(f, buf), y, shadow, bg);
}


void textprintf_shadow_o_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_o_ex(bmp, f, buf, x, y, shadow, bg);
}

void textprintf_shadow_centre_o_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_o_ex(bmp, f, buf, x-(text_length(f, buf)/2), y, shadow, bg);
}

void textprintf_shadow_right_o_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_o_ex(bmp, f, buf, x-text_length(f, buf), y, shadow, bg);
}







void textprintf_shadow_plus_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_plus_ex(bmp, f, buf, x, y, shadow, bg);
}

void textprintf_shadow_centre_plus_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_plus_ex(bmp, f, buf, x-(text_length(f, buf)/2), y, shadow, bg);
}

void textprintf_shadow_right_plus_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_plus_ex(bmp, f, buf, x-text_length(f, buf), y, shadow, bg);
}

void textprintf_shadow_x_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_x_ex(bmp, f, buf, x, y, shadow, bg);
}

void textprintf_shadow_centre_x_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_x_ex(bmp, f, buf, x-(text_length(f, buf)/2), y, shadow, bg);
}

void textprintf_shadow_right_x_ex(BITMAP *bmp, const FONT *f, int x, int y, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadow_x_ex(bmp, f, buf, x-text_length(f, buf), y, shadow, bg);
}















void textprintf_shadowed_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_ex(bmp, f, buf, x, y, color, shadow, bg);
}

void textprintf_shadowed_centre_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_ex(bmp, f, buf, x-(text_length(f, buf)/2), y, color, shadow, bg);
}

void textprintf_shadowed_right_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_ex(bmp, f, buf, x-text_length(f, buf), y, color, shadow, bg);
}

void textprintf_shadowed_u_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_u_ex(bmp, f, buf, x, y, color, shadow, bg);
}

void textprintf_shadowed_centre_u_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_u_ex(bmp, f, buf, x-(text_length(f, buf)/2), y, color, shadow, bg);
}

void textprintf_shadowed_right_u_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_u_ex(bmp, f, buf, x-text_length(f, buf), y, color, shadow, bg);
}

void textprintf_shadowed_o_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_o_ex(bmp, f, buf, x, y, color, shadow, bg);
}

void textprintf_shadowed_centre_o_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_o_ex(bmp, f, buf, x-(text_length(f, buf)/2), y, color, shadow, bg);
}

void textprintf_shadowed_right_o_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_o_ex(bmp, f, buf, x-text_length(f, buf), y, color, shadow, bg);
}

void textprintf_shadowed_plus_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_plus_ex(bmp, f, buf, x, y, color, shadow, bg);
}

void textprintf_shadowed_centre_plus_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_plus_ex(bmp, f, buf, x-(text_length(f, buf)/2), y, color, shadow, bg);
}

void textprintf_shadowed_right_plus_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_plus_ex(bmp, f, buf, x-text_length(f, buf), y, color, shadow, bg);
}


void textprintf_shadowed_x_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_x_ex(bmp, f, buf, x, y, color, shadow, bg);
}

void textprintf_shadowed_centre_x_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_x_ex(bmp, f, buf, x-(text_length(f, buf)/2), y, color, shadow, bg);
}

void textprintf_shadowed_right_x_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int shadow, int bg, const char *format, ...)
{
    char buf[512];
    va_list ap;
    ASSERT(bmp);
    ASSERT(f);
    ASSERT(format);
    
    va_start(ap, format);
    uvszprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    
    textout_shadowed_x_ex(bmp, f, buf, x-text_length(f, buf), y, color, shadow, bg);
}
/*
  void dclick_check(void)
  {
  if (dclick_status==DCLICK_START) {              // first click...
  if (!gui_mouse_b()) {
  dclick_status = DCLICK_RELEASE;           // aah! released first
  dclick_time = 0;
  return;
  }
  }
  else if (dclick_status==DCLICK_RELEASE) {       // wait for second click
  if (gui_mouse_b()) {
  dclick_status = DCLICK_AGAIN;             // yes! the second click
  dclick_time = 0;
  return;
  }
  }
  else
  {
  return;
  }

  // timeout?
  if (dclick_time++ > 10)
  {
  dclick_status = DCLICK_NOT;
  }
  }
  */


extern int d_alltriggerbutton_proc(int msg,DIALOG *d,int c);
#ifndef _MSC_VER
//Inconsistent DLL linkage... what the fuck
extern int d_button_proc(int msg,DIALOG *d,int c);
extern int d_check_proc(int msg,DIALOG *d,int c);
extern int d_ctext_proc(int msg,DIALOG *d,int c);
extern int d_text_proc(int msg,DIALOG *d,int c);
#endif
extern int d_comboa_radio_proc(int msg,DIALOG *d,int c);
extern int d_comboabutton_proc(int msg,DIALOG *d,int c);
extern int d_dummy_proc(int msg,DIALOG *d,int c);
extern int d_jbutton_proc(int msg,DIALOG *d,int c);
extern int d_kbutton_proc(int msg,DIALOG *d,int c);
extern int d_listen_proc(int msg,DIALOG *d,int c);
extern int d_savemidi_proc(int msg,DIALOG *d,int c);
extern int d_ssdn_btn_proc(int msg,DIALOG *d,int c);
extern int d_ssdn_btn2_proc(int msg,DIALOG *d,int c);
extern int d_ssdn_btn3_proc(int msg,DIALOG *d,int c);
extern int d_sslt_btn_proc(int msg,DIALOG *d,int c);
extern int d_sslt_btn2_proc(int msg,DIALOG *d,int c);
extern int d_sslt_btn3_proc(int msg,DIALOG *d,int c);
extern int d_ssrt_btn_proc(int msg,DIALOG *d,int c);
extern int d_ssrt_btn2_proc(int msg,DIALOG *d,int c);
extern int d_ssrt_btn3_proc(int msg,DIALOG *d,int c);
extern int d_ssup_btn_proc(int msg,DIALOG *d,int c);
extern int d_ssup_btn2_proc(int msg,DIALOG *d,int c);
extern int d_ssup_btn3_proc(int msg,DIALOG *d,int c);
extern int d_tri_edit_proc(int msg,DIALOG *d,int c);
extern int d_triggerbutton_proc(int msg,DIALOG *d,int c);
extern int jwin_button_proc(int msg,DIALOG *d,int c);
extern int jwin_check_proc(int msg,DIALOG *d,int c);
extern int jwin_ctext_proc(int msg,DIALOG *d,int c);
extern int jwin_radio_proc(int msg,DIALOG *d,int c);
extern int jwin_rtext_proc(int msg,DIALOG *d,int c);
extern int jwin_text_proc(int msg,DIALOG *d,int c);
extern int jwin_win_proc(int msg,DIALOG *d,int c);

//extern DIALOG *sso_properties_dlg;

void copy_dialog(DIALOG **to, DIALOG *from)
{
    int count=0;
    
    for(count=1; from[count].proc!=NULL; ++count)
    {
        /* do nothing */
    }
    
    (*to)=(DIALOG*)zc_malloc((count+1)*sizeof(DIALOG));
    memcpy((*to),from,sizeof(DIALOG)*(count+1));
    
    for(int i=0; i<count; ++i)
    {
        if((from[i].dp!=NULL)&&
                ((from[i].proc==d_alltriggerbutton_proc)||
                 (from[i].proc==d_button_proc)||
                 (from[i].proc==d_check_proc)||
                 (from[i].proc==d_comboa_radio_proc)||
                 (from[i].proc==d_comboabutton_proc)||
                 (from[i].proc==d_ctext_proc)||
                 (from[i].proc==d_dummy_proc)||
                 (from[i].proc==d_jbutton_proc)||
                 (from[i].proc==d_kbutton_proc)||
                 (from[i].proc==d_listen_proc)||
                 (from[i].proc==d_savemidi_proc)||
                 (from[i].proc==d_ssdn_btn_proc)||
                 (from[i].proc==d_ssdn_btn2_proc)||
                 (from[i].proc==d_ssdn_btn3_proc)||
                 (from[i].proc==d_sslt_btn_proc)||
                 (from[i].proc==d_sslt_btn2_proc)||
                 (from[i].proc==d_sslt_btn3_proc)||
                 (from[i].proc==d_ssrt_btn_proc)||
                 (from[i].proc==d_ssrt_btn2_proc)||
                 (from[i].proc==d_ssrt_btn3_proc)||
                 (from[i].proc==d_ssup_btn_proc)||
                 (from[i].proc==d_ssup_btn2_proc)||
                 (from[i].proc==d_ssup_btn3_proc)||
                 (from[i].proc==d_text_proc)||
                 (from[i].proc==d_tri_edit_proc)||
                 (from[i].proc==d_triggerbutton_proc)||
                 (from[i].proc==jwin_button_proc)||
                 (from[i].proc==jwin_check_proc)||
                 (from[i].proc==jwin_ctext_proc)||
                 (from[i].proc==jwin_edit_proc) ||
                 (from[i].proc==jwin_radio_proc)||
                 (from[i].proc==jwin_rtext_proc)||
                 (from[i].proc==jwin_text_proc)||
                 (from[i].proc==jwin_win_proc)))
        {
            (*to)[i].dp=zc_malloc(strlen((char *)from[i].dp)+1);
            strcpy((char *)(*to)[i].dp,(char *)from[i].dp);
        }
        
        if((from[i].proc==d_tab_proc)||
                (from[i].proc==jwin_tab_proc))
        {
            (*to)[i].dp3=(void *)(*to);
        }
        
        /*
            case d_bitmap_proc:
            case d_box_proc:
            case d_combo_proc:
            case d_comboa_proc:
            case d_comboacheck_proc:
            case d_comboalist_proc:
            case d_comboat_proc:
            case d_cset_proc:
            case d_cstile_proc:
            case d_ctile_proc:
            case d_ctl_proc:
            case d_dmaplist_proc:
            case d_dmapscrsel_proc:
            case d_dropcancel_proc:
            case d_dropdmaplist_proc:
            case d_dropdmaptypelist_proc:
            case d_edit_proc:
            case d_editbox_proc:
            case d_grid_proc:
            case d_hexedit_proc:
            case d_intro_edit_proc:
            case d_itile_proc:
            case d_keyboard_proc:
            case d_list_proc:
            case d_ltile_proc:
            case d_maptile_proc:
            case d_maxbombsedit_proc:
            case d_bombratioedit_proc:
            case d_midilist_proc:
            case d_misccolors_hexedit_proc:
            case d_misccolors_proc:
            case d_misccolors_tab_proc:
            case d_msg_edit_proc:
            case d_musiclist_proc:
            case d_nbmenu_proc:
            case d_nilist_proc:
            case d_scombo_proc:
            case d_scroll_bmp_proc:
            case d_sel_scombo_proc:
            case d_showedit_proc:
            case d_subscreen_proc:
            case d_tab_proc:
            case d_ticsedit_proc:
            case d_title_edit_proc:
            case d_tri_frame_proc:
            case d_vsync_proc:
            case d_warpbutton_proc:
            case d_warpdestsel_proc:
            case d_warplist_proc:
            case d_wclist_proc:
            case d_wflag_proc:
            case d_xmaplist_proc:
            case d_yield_proc:
            case fs_dlist_proc:
            case fs_edit_proc:
            case fs_elist_proc:
            case fs_flist_proc:
            case jwin_abclist_proc:
            case jwin_as_droplist_proc:
            case jwin_droplist_proc:
            case jwin_edit_proc:
            case jwin_frame_proc:
            case jwin_guitest_proc:
            case jwin_hexedit_proc:
            case jwin_list_proc:
            case jwin_menu_proc:
            case jwin_numedit_proc:
            case jwin_slider_proc:
            case jwin_tab_proc:
            case jwin_textbox_proc:
            case jwin_vline_proc:
        */
    }
}

void free_dialog(DIALOG **dlg)
{
    int count=0;
    
    for(count=1; (*dlg)[count].proc!=NULL; ++count)
    {
        /* do nothing */
    }
    
    for(int i=0; i<count+1; ++i)
    {
        if(((*dlg)[i].dp!=NULL)&&
                (((*dlg)[i].proc==d_alltriggerbutton_proc)||
                 ((*dlg)[i].proc==d_button_proc)||
                 ((*dlg)[i].proc==d_check_proc)||
                 ((*dlg)[i].proc==d_comboa_radio_proc)||
                 ((*dlg)[i].proc==d_comboabutton_proc)||
                 ((*dlg)[i].proc==d_ctext_proc)||
                 ((*dlg)[i].proc==d_edit_proc)||
                 ((*dlg)[i].proc==d_jbutton_proc)||
                 ((*dlg)[i].proc==d_kbutton_proc)||
                 ((*dlg)[i].proc==d_listen_proc)||
                 ((*dlg)[i].proc==d_savemidi_proc)||
                 ((*dlg)[i].proc==d_ssdn_btn_proc)||
                 ((*dlg)[i].proc==d_ssdn_btn2_proc)||
                 ((*dlg)[i].proc==d_ssdn_btn3_proc)||
                 ((*dlg)[i].proc==d_sslt_btn_proc)||
                 ((*dlg)[i].proc==d_sslt_btn2_proc)||
                 ((*dlg)[i].proc==d_sslt_btn3_proc)||
                 ((*dlg)[i].proc==d_ssrt_btn_proc)||
                 ((*dlg)[i].proc==d_ssrt_btn2_proc)||
                 ((*dlg)[i].proc==d_ssrt_btn3_proc)||
                 ((*dlg)[i].proc==d_ssup_btn_proc)||
                 ((*dlg)[i].proc==d_ssup_btn2_proc)||
                 ((*dlg)[i].proc==d_ssup_btn3_proc)||
                 ((*dlg)[i].proc==d_text_proc)||
                 ((*dlg)[i].proc==d_tri_edit_proc)||
                 ((*dlg)[i].proc==d_triggerbutton_proc)||
                 ((*dlg)[i].proc==jwin_button_proc)||
                 ((*dlg)[i].proc==jwin_check_proc)||
                 ((*dlg)[i].proc==jwin_ctext_proc)||
                 ((*dlg)[i].proc==jwin_edit_proc)||
                 ((*dlg)[i].proc==jwin_radio_proc)||
                 ((*dlg)[i].proc==jwin_rtext_proc)||
                 ((*dlg)[i].proc==jwin_text_proc)||
                 ((*dlg)[i].proc==jwin_win_proc)))
        {
            zc_free((*dlg)[i].dp);
        }
        
        
        /*
            case d_bitmap_proc:
            case d_box_proc:
            case d_combo_proc:
            case d_comboa_proc:
            case d_comboacheck_proc:
            case d_comboalist_proc:
            case d_comboat_proc:
            case d_cset_proc:
            case d_cstile_proc:
            case d_ctile_proc:
            case d_ctl_proc:
            case d_dmaplist_proc:
            case d_dmapscrsel_proc:
            case d_dropcancel_proc:
            case d_dropdmaplist_proc:
            case d_dropdmaptypelist_proc:
            case d_editbox_proc:
            case d_grid_proc:
            case d_hexedit_proc:
            case d_intro_edit_proc:
            case d_itile_proc:
            case d_keyboard_proc:
            case d_list_proc:
            case d_ltile_proc:
            case d_maptile_proc:
            case d_maxbombsedit_proc:
            case d_bombratioedit_proc:
            case d_midilist_proc:
            case d_misccolors_hexedit_proc:
            case d_misccolors_proc:
            case d_misccolors_tab_proc:
            case d_msg_edit_proc:
            case d_musiclist_proc:
            case d_nbmenu_proc:
            case d_nilist_proc:
            case d_scombo_proc:
            case d_scroll_bmp_proc:
            case d_sel_scombo_proc:
            case d_showedit_proc:
            case d_subscreen_proc:
            case d_tab_proc:
            case d_ticsedit_proc:
            case d_title_edit_proc:
            case d_tri_frame_proc:
            case d_vsync_proc:
            case d_warpbutton_proc:
            case d_warpdestsel_proc:
            case d_warplist_proc:
            case d_wclist_proc:
            case d_wflag_proc:
            case d_xmaplist_proc:
            case d_yield_proc:
            case fs_dlist_proc:
            case fs_edit_proc:
            case fs_elist_proc:
            case fs_flist_proc:
            case jwin_abclist_proc:
            case jwin_as_droplist_proc:
            case jwin_droplist_proc:
            case jwin_frame_proc:
            case jwin_guitest_proc:
            case jwin_hexedit_proc:
            case jwin_list_proc:
            case jwin_menu_proc:
            case jwin_numedit_proc:
            case jwin_slider_proc:
            case jwin_tab_proc:
            case jwin_textbox_proc:
            case jwin_vline_proc:
        */
    }
    
    memset((*dlg),0,sizeof(DIALOG)*(count+1));
    zc_free((*dlg));
}

/*static char * packpasswrd = NULL;
void setPackfilePassword(const char *newpwd)
{
	if(newpwd==NULL)
		packpasswrd = NULL;
	else
	{
		int len = (int)strlen(newpwd);
		if(packpasswrd != NULL)
			delete[] packpasswrd;
		packpasswrd = new char[len+1];
		strcpy(packpasswrd, newpwd);
	}
	packfile_password(packpasswrd);
}

char * getCurPackfilePassword()
{
	if(packpasswrd == NULL)
		return NULL;
	int len = (int)strlen(packpasswrd);
	char *ret = new char[len+1];
	strcpy(ret, packpasswrd);
	return ret;
}*/

// A lot of crashes in ZQuest can be traced to rect(). Hopefully, this will help.
void safe_rect(BITMAP *bmp, int x1, int y1, int x2, int y2, int color)
{
    rect(bmp, vbound(x1, 0, bmp->w-1), vbound(y1, 0, bmp->h-1), vbound(x2, 0, bmp->w-1), vbound(y2, 0, bmp->h-1), color);
}

//computes the positive gcd of two integers (using Euclid's algorithm)

int gcd(int a, int b)
{
    a = abs(a);
    b = abs(b);
    
    if(b == 0)
        return a;
        
    int res = a%b;
    
    while(res != 0)
    {
        a = b;
        b = res;
        res = a%b;
    }
    
    return b;
}

//computes the positive lcm of two integers
int lcm(int a, int b)
{
    return a*b/gcd(a,b);
}

//Fun fact: Allegro used to be in control of allegro.log. This caused
//problems, because it would hold on to a file handle. Even if we blank
//the contents of the log, it will still write to the end, causing
//lots of nulls.

//No more!


FILE * trace_file;

int zc_trace_handler(const char * msg)
{
    if(trace_file == 0)
    {
        trace_file = fopen("allegro.log", "a+");
        
        if(0==trace_file)
        {
            return 0; // blargh.
        }
    }
    
    fprintf(trace_file, "%s", msg);
    fflush(trace_file);
    return 1;
}

void zc_trace_clear()
{
    if(trace_file)
    {
        fclose(trace_file);
    }
    
    trace_file = fopen("allegro.log", "w");
    ASSERT(trace_file);
}



void do_drawintr(BITMAP *bmp, int *sdci, int xoffset, int yoffset)
{
    //sdci[1]=layer
    //sdci[2]=x
    //sdci[3]=y
    //sdci[4]=font
    //sdci[5]=color
    //sdci[6]=bg color
    //sdci[7]=strech x (width)
    //sdci[8]=stretch y (height)
    //sdci[9]=integer
    //sdci[10]=num decimal places
    //sdci[11]=opacity
    
    int x=sdci[2]/10000;
    int y=sdci[3]/10000;
    int font_index=sdci[4]/10000;
    int color=sdci[5]/10000;
    int bg_color=sdci[6]/10000; //-1 = transparent
    int w=sdci[7]/10000;
    int h=sdci[8]/10000;
    float number=static_cast<float>(sdci[9])/10000.0f;
    int decplace=sdci[10]/10000;
    int opacity=sdci[11]/10000;
    
    //safe check
    if(bg_color < -1) bg_color = -1;
    
    if(w>512) w=512; //w=vbound(w,0,512);
    
    if(h>512) h=512; //h=vbound(h,0,512);
    
    char numbuf[15];
    
    switch(decplace)
    {
    default:
    case 0:
        sprintf(numbuf,"%d",int(number));
        break;
        
    case 1:
        sprintf(numbuf,"%.01f",number);
        break;
        
    case 2:
        sprintf(numbuf,"%.02f",number);
        break;
        
    case 3:
        sprintf(numbuf,"%.03f",number);
        break;
        
    case 4:
        sprintf(numbuf,"%.04f",number);
        break;
    }
    
    if(w>0&&h>0)//stretch
    {
	FONT* font = get_zc_font(font_index);
        BITMAP *pbmp = subBmp = script_drawing_commands.AquireSubBitmap(text_length(font, numbuf), text_height(font));
	    //script_drawing_commands.GetSmallTextureBitmap(w,h);
        
        if(opacity < 128)
        {
            if(w>128||h>128)
            {
                clear_bitmap(prim_bmp);
                
                textout_ex(pbmp, get_zc_font(font_index), numbuf, 0, 0, color, bg_color);
                stretch_sprite(prim_bmp, pbmp, 0, 0, w, h);
                draw_trans_sprite(bmp, prim_bmp, x+xoffset, y+yoffset);
            }
            else
            {
                BITMAP *pbmp2 = create_sub_bitmap(prim_bmp,0,0,w,h);
                clear_bitmap(pbmp2);
                
                textout_ex(pbmp, get_zc_font(font_index), numbuf, 0, 0, color, bg_color);
                stretch_sprite(pbmp2, pbmp, 0, 0, w, h);
                draw_trans_sprite(bmp, pbmp2, x+xoffset, y+yoffset);
                
                destroy_bitmap(pbmp2);
            }
        }
        else // no opacity
        {
            textout_ex(pbmp, get_zc_font(font_index), numbuf, 0, 0, color, bg_color);
            stretch_sprite(bmp, pbmp, x+xoffset, y+yoffset, w, h);
        }
        
    }
    else //no stretch
    {
        if(opacity < 128)
        {
            FONT* font = get_zc_font(font_index);
            BITMAP *pbmp = create_sub_bitmap(prim_bmp, 0, 0, text_length(font, numbuf), text_height(font));
            clear_bitmap(pbmp);
            
            textout_ex(pbmp, font, numbuf, 0, 0, color, bg_color);
            draw_trans_sprite(bmp, pbmp, x+xoffset, y+yoffset);
            
            destroy_bitmap(pbmp);
        }
        else // no opacity
        {
            textout_ex(bmp, get_zc_font(font_index), numbuf, x+xoffset, y+yoffset, color, bg_color);
        }
    }
}


void do_drawstringr(BITMAP *bmp, int i, int *sdci, int xoffset, int yoffset)
{
    //sdci[1]=layer
    //sdci[2]=x
    //sdci[3]=y
    //sdci[4]=font
    //sdci[5]=color
    //sdci[6]=bg color
    //sdci[7]=format_option
    //sdci[8]=string
    //sdci[9]=opacity
    
    std::string* str = (std::string*)script_drawing_commands[i].GetPtr();
    
    if(!str)
    {
        al_trace("String pointer is null! Internal error. \n");
        return;
    }
    
    int x=sdci[2]/10000;
    int y=sdci[3]/10000;
    FONT* font=get_zc_font(sdci[4]/10000);
    int color=sdci[5]/10000;
    int bg_color=sdci[6]/10000; //-1 = transparent
    int format_type=sdci[7]/10000;
    int opacity=sdci[9]/10000;
    //sdci[8] not needed :)
    
    //safe check
    if(bg_color < -1) bg_color = -1;
    
    if(opacity < 128)
    {
        int width=zc_min(text_length(font, str->c_str()), 512);
        BITMAP *pbmp = create_sub_bitmap(prim_bmp, 0, 0, width, text_height(font));
        clear_bitmap(pbmp);
        textout_ex(pbmp, font, str->c_str(), 0, 0, color, bg_color);
        if(format_type == 2)   // right-sided text
            x-=width;
        else if(format_type == 1)   // centered text
            x-=width/2;
        draw_trans_sprite(bmp, pbmp, x+xoffset, y+yoffset);
        destroy_bitmap(pbmp);
    }
    else // no opacity
    {
        if(format_type == 2)   // right-sided text
        {
            textout_right_ex(bmp, font, str->c_str(), x+xoffset, y+yoffset, color, bg_color);
        }
        else if(format_type == 1)   // centered text
        {
            textout_centre_ex(bmp, font, str->c_str(), x+xoffset, y+yoffset, color, bg_color);
        }
        else // standard left-sided text
        {
            textout_ex(bmp, font, str->c_str(), x+xoffset, y+yoffset, color, bg_color);
        }
    }
}


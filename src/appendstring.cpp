//not needed
//static stringappend_dlg_list(stringappendlist, &font);

static DIALOG appendstring_sel_dlg[] =
{
    { jwin_win_proc,        0,    0,    200, 159, vc(14),   vc(1),      0,       D_EXIT,     0,             0, (void *) "Start String", NULL, NULL },
    { jwin_text_proc,       8,    80,   36,  8,   vc(14),   vc(1),     0,       0,          0,             0, (void *) "Name:", NULL, NULL },
    { jwin_edit_proc,       44,   80-4, 146, 16,  vc(12),   vc(1),     0,       0,          19,            0,       NULL, NULL, NULL },
    { d_timer_proc,         0,    0,     0,    0,    0,       0,       0,       0,          0,          0,         NULL, NULL, NULL },
    { NULL,                 0,    0,    0,    0,   0,       0,       0,       0,          0,             0,       NULL,                           NULL,  NULL }
};


int onAppendMessage()
{
    char name[6]="";
	int start = atoi(name);
    
    appendstring_sel_dlg[0].dp2 = lfont;
    appendstring_sel_dlg[2].dp = name;
    appendstring_sel_dlg[5].d1 = 0;
    
    if(is_large)
        large_dialog(appendstring_sel_dlg);
        
    int ret=zc_popup_dialog(appendstring_sel_dlg,0);
    
    if(ret==3)
    {
        onAppend_Msgs(start);
    }
    
    return D_O_K;
}



static DIALOG ffscript_sel_dlg[] =
{
    { jwin_win_proc,        0,    0,    200, 159, vc(14),   vc(1),      0,       D_EXIT,     0,             0, (void *) "Choose Slot And Name", NULL, NULL },
    { jwin_text_proc,       8,    80,   36,  8,   vc(14),   vc(1),     0,       0,          0,             0, (void *) "Name:", NULL, NULL },
    { jwin_edit_proc,       44,   80-4, 146, 16,  vc(12),   vc(1),     0,       0,          19,            0,       NULL, NULL, NULL },
    { jwin_button_proc,     35,   132,  61,   21, vc(14),   vc(1),     13,       D_EXIT,     0,             0, (void *) "Load", NULL, NULL },
    { jwin_button_proc,     104,  132,  61,   21, vc(14),   vc(1),     27,       D_EXIT,     0,             0, (void *) "Cancel", NULL, NULL },
    { jwin_droplist_proc,   26,   45,   146,   16, jwin_pal[jcTEXTFG],  jwin_pal[jcTEXTBG],  0,       0,          1,             0, (void *) &ffscript_sel_dlg_list, NULL, NULL },
    { d_timer_proc,         0,    0,     0,    0,    0,       0,       0,       0,          0,          0,         NULL, NULL, NULL },
    { NULL,                 0,    0,    0,    0,   0,       0,       0,       0,          0,             0,       NULL,                           NULL,  NULL }
};
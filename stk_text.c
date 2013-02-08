#include <stk_text.h>


stk_widget *stk_text_new(stk_widget *parent_win, int x, int y, uint w, uint h,
                                                  const char *label, int type)
{
    stk_widget *new_txt  = (stk_widget*) malloc(sizeof(stk_widget));
    int screen;

    XGCValues gcval;
    long fg, bg;
    XSetWindowAttributes setwinattr;
    new_txt->dsp = display;
    new_txt->fontname = "7x13";

    screen = DefaultScreen(new_txt->dsp);
    fg = BlackPixel(new_txt->dsp, screen);
    bg = WhitePixel(new_txt->dsp, screen);
    
    gcval.foreground = fg;
    gcval.background = bg;
    new_txt->gc2 = XCreateGC(new_txt->dsp, parent_win->win, GCForeground |
                                                  GCBackground, &gcval);

    setwinattr.backing_store = Always;

    new_txt->font_info = XLoadQueryFont(new_txt->dsp, new_txt->fontname);

    if(new_txt->fontname != NULL)
        XSetFont(display, new_txt->gc2, new_txt->font_info->fid);
    else
      perror("XLoadQueryFont");

    if(new_txt->dsp)
    {
        new_txt->win = XCreateSimpleWindow(new_txt->dsp, parent_win->win, x, y, w,
                                                                  h, 2, fg, bg);

        new_txt->mask =  ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
                         ButtonMotionMask | EnterWindowMask | LeaveWindowMask | PointerMotionMask | 
                         FocusChangeMask | ColormapChangeMask | StructureNotifyMask | PropertyChangeMask | VisibilityChangeMask;

        XChangeWindowAttributes(new_txt->dsp, new_txt->win, CWBackingStore,
                                                              &setwinattr);
        
        XSelectInput(new_txt->dsp, new_txt->win, new_txt->mask);
        XMapWindow(new_txt->dsp, new_txt->win);


        new_txt->x = x;
        new_txt->y = y;
        new_txt->w = w;
        new_txt->h = h;
        new_txt->ext = NULL;
        new_txt->handler = &stk_text_handle;

        if(label)
            new_txt->label = label;


        stk_widget_insert((void*)new_txt); 

        return new_txt;
    }
    else
        return NULL;
}


void stk_text_append(stk_widget *txt, char c)
{
    int len = 0;
    char *new_string = NULL;

    if(txt->ext == NULL)
    {
        txt->ext = (char*)malloc(sizeof(char));
         txt->ext[0] = c;
    }
    else
    {
        len = strlen(txt->ext);
        new_string = (char*)realloc(txt->ext, len + sizeof(char));
        if(new_string)
        {
            new_string[len] = c;
            txt->ext = new_string;
        }
    }
}



void stk_text_delete(stk_widget *txt)
{
    int len = 0;
    char *new_string = NULL;

    if(txt->ext == NULL)
    {
        return;
    }
    else
    {
        len = strlen(txt->ext);
        new_string = (char*)realloc(txt->ext, sizeof(char)*(len - sizeof(char)));
        if(new_string)
        {
            new_string[len - 1] = 0;
            txt->ext = new_string;
            len = strlen(new_string);
        }
    }
}


void stk_text_expose(stk_widget *txt, void *arg)
{
    XClearWindow(txt->dsp, txt->win);
    XFlush(txt->dsp);
}



void stk_text_keys(stk_widget *txt, XKeyEvent *event, KeySym *key)
{
    KeySym keysym = (KeySym)&key;
    char c;

    XLookupString(event, &c, sizeof(char), &keysym, NULL);
   

    if((keysym >= XK_space) && (keysym <= XK_asciitilde))
    {
        
        stk_text_append(txt, c);
        printf("%s\n", txt->ext);

        printf ("Ascii key:- ");
        if (event->state & ShiftMask)
               printf("(Shift) %c\n", c);
        else
            if(event->state & LockMask)
                printf("(Caps Lock) %c\n", c);
        else
            if(event->state & ControlMask)
                printf("(Control) %c\n", 'a'+ c-1);

        else
            printf("%c\n", c) ;
    }
    else 
        if((keysym >= XK_Shift_L) && (keysym <= XK_Hyper_R))
        {
            printf ("modifier key: - ");
                switch (keysym){
                    case XK_Shift_L: printf("Left Shift\n"); break;
                    case XK_Shift_R: printf("Right Shift\n"); break;
                    case XK_Control_L: printf("Left Control\n"); break;
                    case XK_Control_R: printf("Right Control\n"); break;
                    case XK_Caps_Lock: printf("Caps Lock\n"); break;
                    case XK_Shift_Lock: printf("Shift Lock\n"); break;
                    case XK_Meta_L: printf("Left Meta\n"); break;
                    case XK_Meta_R: printf("Right Meta\n"); break;
        }
    }
    else
        if((keysym >= XK_Left) && (keysym <= XK_Down))
        {
             printf("Arrow Key:-");
             switch(keysym){
             case XK_Left: printf("Left\n"); break;
             case XK_Up: printf("Up\n"); break;
             case XK_Right: printf("Right\n"); break;
             case XK_Down: printf("Down\n"); break; 
        }
    }
    else
        if((keysym == XK_BackSpace) || (keysym == XK_Delete))
        {
            stk_text_delete(txt);
            stk_text_redraw(STK_TEXT_EXPOSE, txt, NULL);
        }
        else
            if ((keysym >= XK_KP_0) && (keysym <= XK_KP_9)){
                printf("Number pad key %d\n", (int)(keysym -  XK_KP_0));
   }
}


char *stk_text_get_text(stk_widget *txt)
{
    return txt->ext;
}


void stk_text_redraw(int dtype, stk_widget *txt, void *args)
{ 
    
    STKEvent *ev;

    if(args)
         ev = (STKEvent*)args;

    switch(dtype)
    {
        case STK_TEXT_EXPOSE:
            stk_text_expose(txt, NULL);
            break;

        case STK_TEXT_PRESS:
            XSetInputFocus(txt->dsp, txt->win, RevertToNone, CurrentTime);
            break;

        case STK_TEXT_RELEASE:
            break;

        case STK_TEXT_KEYPRESS:
        {
            KeySym keysym;
            stk_text_expose(txt, NULL);
            stk_text_keys(txt, &ev->xkey, &keysym);
            {     
                int hcenter = (txt->font_info->descent) + (txt->h / 2);
                int sw, begin;

                if(txt->ext)
                {
                    sw = XTextWidth(txt->font_info, txt->ext, strlen(txt->ext));
                    if(sw > txt->w)
                    {
                        begin = txt->w - sw;
                        printf("Overflow begin %d\n", begin);
                    }
                    else
                        begin = 2;
                    
                    XDrawString(txt->dsp, txt->win, txt->gc2, begin, hcenter,
                                                 txt->ext, strlen(txt->ext));
                }
            }
        }
            break;

        case STK_TEXT_KEYRELEASE:
            break;


        case STK_TEXT_ENTER:
        case STK_TEXT_LEAVE:
        default:
            break;
    }
}



void stk_text_handle(STKEvent *event, void *warg)
{
  stk_widget *wg = (stk_widget*)warg;

    switch(event->type)
    {
        case Expose:
            stk_text_redraw(STK_TEXT_EXPOSE, wg, NULL);
            break;
        case LeaveNotify:
            break;

        case ButtonPress:
            stk_text_redraw(STK_TEXT_PRESS, wg, NULL);
            break;

        case ButtonRelease:
            stk_text_redraw(STK_TEXT_RELEASE, wg, NULL);
            break;

        case KeyPress:
            stk_text_redraw(STK_TEXT_KEYPRESS, wg, event);
            break;

        case KeyRelease:
            stk_text_redraw(STK_TEXT_KEYRELEASE, wg, NULL);
            break;
    }
}

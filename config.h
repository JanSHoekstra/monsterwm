/* see LICENSE for copyright and license */

#include <X11/XF86keysym.h>

#ifndef CONFIG_H
#define CONFIG_H

/** modifiers **/
#define MOD1            Mod1Mask    /* ALT key */
#define MOD4            Mod4Mask    /* Super/Windows key */
#define CONTROL         ControlMask /* Control key */
#define SHIFT           ShiftMask   /* Shift key */

/** generic settings **/
#define MASTER_SIZE     0.50
#define SHOW_PANEL      True      /* show panel by default on exec */
#define TOP_PANEL       True      /* False means panel is on bottom */
#define PANEL_HEIGHT    18        /* 0 for no space for panel, thus no panel */
#define DEFAULT_MODE    GRID      /* initial layout/mode: TILE MONOCLE BSTACK GRID FLOAT */
#define ATTACH_ASIDE    True      /* False means new window is master */
#define FOLLOW_WINDOW   False     /* follow the window when moved to a different desktop */
#define FOLLOW_MOUSE    True     /* focus the window the mouse just entered */
#define CLICK_TO_FOCUS  True      /* focus an unfocused window when clicked  */
#define FOCUS_BUTTON    Button3   /* mouse button to be used along with CLICK_TO_FOCUS */
#define BORDER_WIDTH    2         /* window border width */
#define FOCUS           "#ff950e" /* focused window border color    */
#define UNFOCUS         "#444444" /* unfocused window border color  */
#define MINWSZ          50        /* minimum window size in pixels  */
#define DEFAULT_DESKTOP 0         /* the desktop to focus initially */
#define DESKTOPS        6         /* number of desktops - edit DESKTOPCHANGE keys to suit */

/**
 * open applications to specified desktop with specified mode.
 * if desktop is negative, then current is assumed
 */
static const AppRule rules[] = { \
    /*  class     desktop  follow  float */
    { "MPlayer",     3,    True,   False },
    { "Gimp",        0,    False,  True  },
};

/* helper for spawning shell commands */
#define SHCMD(cmd) {.com = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/**
 * custom commands
 * must always end with ', NULL };'
 */
static const char *termcmd[] = { "st",     NULL };
static const char *menucmd[] = { "dmenu_run", NULL };

static const char *mutecmd[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
static const char *miccmd[] = { "amixer", "set", "Capture", "toggle", NULL };

// Pulse
//static const char *mutecmd[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };
//static const char *volupcmd[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
//static const char *voldowncmd[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };

static const char *brupcmd[] = { "xbacklight", "-inc", "10", NULL };
static const char *brdowncmd[] = { "xbacklight", "-dec", "10", NULL };

#define DESKTOPCHANGE(K,N) \
    {  MOD1,             K,              change_desktop, {.i = N}}, \
    {  MOD1|ShiftMask,   K,              client_to_desktop, {.i = N}},

/**
 * keyboard shortcuts
 */
static Key keys[] = {
    /* modifier          key            function           argument */
    {  MOD1,             XK_b,          togglepanel,       {NULL}},
    {  MOD1,             XK_BackSpace,  focusurgent,       {NULL}},
    {  MOD1|SHIFT,       XK_c,          killclient,        {NULL}},
    {  MOD1,             XK_j,          next_win,          {NULL}},
    {  MOD1,             XK_k,          prev_win,          {NULL}},
    {  MOD1,             XK_h,          resize_master,     {.i = -30}}, /* decrease size in px */
    {  MOD1,             XK_l,          resize_master,     {.i = +30}}, /* increase size in px */
    {  MOD1,             XK_o,          resize_stack,      {.i = -30}}, /* shrink   size in px */
    {  MOD1,             XK_p,          resize_stack,      {.i = +30}}, /* grow     size in px */
    {  MOD1|CONTROL,     XK_h,          rotate,            {.i = -1}},
    {  MOD1|CONTROL,     XK_l,          rotate,            {.i = +1}},
    {  MOD1|SHIFT,       XK_h,          rotate_filled,     {.i = -1}},
    {  MOD1|SHIFT,       XK_l,          rotate_filled,     {.i = +1}},
    {  MOD1,             XK_Tab,        last_desktop,      {NULL}},
    {  MOD1,             XK_Return,     swap_master,       {NULL}},
    {  MOD1|SHIFT,       XK_j,          move_down,         {NULL}},
    {  MOD1|SHIFT,       XK_k,          move_up,           {NULL}},
    {  MOD1|SHIFT,       XK_t,          switch_mode,       {.i = TILE}},
    {  MOD1|SHIFT,       XK_m,          switch_mode,       {.i = MONOCLE}},
    {  MOD1|SHIFT,       XK_b,          switch_mode,       {.i = BSTACK}},
    {  MOD1|SHIFT,       XK_g,          switch_mode,       {.i = GRID}},
    {  MOD1|SHIFT,       XK_f,          switch_mode,       {.i = FLOAT}},
    {  MOD1|CONTROL,     XK_r,          quit,              {.i = 0}}, /* quit with exit value 0 */
    {  MOD1|CONTROL,     XK_q,          quit,              {.i = 1}}, /* quit with exit value 1 */
    {  MOD1,             XK_z,          spawn,             {.com = termcmd}},
    {  MOD1,             XK_space,      spawn,             {.com = menucmd}},
    {  MOD4,             XK_j,          moveresize,        {.v = (int []){   0,  25,   0,   0 }}}, /* move down  */
    {  MOD4,             XK_k,          moveresize,        {.v = (int []){   0, -25,   0,   0 }}}, /* move up    */
    {  MOD4,             XK_l,          moveresize,        {.v = (int []){  25,   0,   0,   0 }}}, /* move right */
    {  MOD4,             XK_h,          moveresize,        {.v = (int []){ -25,   0,   0,   0 }}}, /* move left  */
    {  MOD4|SHIFT,       XK_j,          moveresize,        {.v = (int []){   0,   0,   0,  25 }}}, /* height grow   */
    {  MOD4|SHIFT,       XK_k,          moveresize,        {.v = (int []){   0,   0,   0, -25 }}}, /* height shrink */
    {  MOD4|SHIFT,       XK_l,          moveresize,        {.v = (int []){   0,   0,  25,   0 }}}, /* width grow    */
    {  MOD4|SHIFT,       XK_h,          moveresize,        {.v = (int []){   0,   0, -25,   0 }}}, /* width shrink  */
       DESKTOPCHANGE(    XK_1,                             0)
       DESKTOPCHANGE(    XK_2,                             1)
       DESKTOPCHANGE(    XK_3,                             2)
       DESKTOPCHANGE(    XK_4,                             3)
       DESKTOPCHANGE(    XK_5,                             4)
       DESKTOPCHANGE(    XK_6,                             5)
    {0,                  XF86XK_AudioMute, spawn,          {.com = mutecmd} },
	{0,                  XF86XK_AudioLowerVolume, spawn,   {.com = voldowncmd } },
	{0,                  XF86XK_AudioRaiseVolume, spawn,   {.com = volupcmd } },
	{0,                  XF86XK_MonBrightnessUp, spawn,    {.com = brupcmd} },
	{0,                  XF86XK_MonBrightnessDown, spawn,  {.com = brdowncmd} },
};

/**
 * mouse shortcuts
 */
static Button buttons[] = {
    {  MOD1,    Button1,     mousemotion,   {.i = MOVE}},
    {  MOD1,    Button3,     mousemotion,   {.i = RESIZE}},
    {  MOD4,    Button3,     spawn,         {.com = menucmd}},
};
#endif

/* vim: set expandtab ts=4 sts=4 sw=4 : */

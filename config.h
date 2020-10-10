/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;       /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const int swallowfloating    = 0;       /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 1;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 1;  /* systray spacing */
static const int systraypinningfailfirst = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;       /* 0 means no systray */
static const int showbar            = 1;       /* 0 means no bar */
static const int topbar             = 1;       /* 0 means bottom bar */
static const char *fonts[]          = { "DroidSansMono Nerd Font:pixelsize=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "DroidSansMono Nerd Font:pixelsize=12:antialias=true:autohint=true";
static const char col_bg0[]         = "#0C0D0E";
static const char col_bg1[]         = "#17191A";
static const char col_bg3[]         = "#202425";
static const char col_fg0[]         = "#B0B9C0";
static const char col_fg1[]         = "#BCC7CE";
static const char col_fg2[]         = "#C3CED5";
static const char col_border[]      = "#757D84";

static const char *colors[][3]      = {
	/*                fg       bg       border     */
	[SchemeNorm]  = { col_fg0, col_bg0, col_bg1 },
	[SchemeSel]   = { col_fg2, col_bg3, col_border },
	[SchemeTitle] = { col_fg1, col_bg1, col_bg0 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *      WM_CLASS(STRING) = instance, class
	 *      WM_NAME(STRING) = title
	*/
	/* class            instance        title           tag     center  float   term    swallow monitor scratch */
	{ "St",             "st",           NULL,           0,      1,      0,      1,      0,      -1,     't' },
	{ "floating",       NULL,           NULL,           0,      1,      1,      1,      0,      -1,     'f' },
	{ "floating-alt",   NULL,           NULL,           0,      0,      1,      1,      0,      0,      'o' },
	{ "term-scratch",   NULL,           "scratchpad",   0,      1,      1,      1,      1,      -1,     's' },
	{ "term-scratch",   NULL,           "calculator",   0,      0,      1,      0,      1,      0,      'c' },
	{ "St",             NULL,           "ncmpcpp",      0,      1,      0,      0,      0,      1,      'm' },
	{ "mpv",            NULL,           NULL,           0,      1,      1,      0,      0,      -1,     'v' },
	{ "Sxiv",           NULL,           NULL,           0,      1,      1,      0,      0,      -1,     0   },
	{ "Zathura",        NULL,           NULL,           0,      1,      0,      0,      1,      -1,     0   },
	{ "tabbed",         NULL,           NULL,           0,      1,      0,      0,      1,      -1,     0   },
	{ "qBittorrent",    NULL,           NULL,           0,      1,      1,      0,      1,      -1,     0   },
	{ "Gimp",           NULL,           NULL,           0,      1,      0,      0,      0,      -1,     0   },
	{ "Nextcloud",      NULL,           NULL,           0,      0,      1,      0,      1,      0,      0   },
	{ "Chromium",       NULL,           NULL,           1,      0,      0,      0,      -1,     -1,     0   },
	{ "Firefox",        "Navigator",    NULL,           0,      0,      0,      0,      -1,     -1,     0   },
	{ "Firefox",        "Browser",      NULL,           0,      1,      1,      0,      -1,     -1,     0   },
	{ "Firefox",        "Places",       NULL,           0,      1,      1,      0,      -1,     -1,     0   },
	{ NULL,             NULL,           "Event Tester", 0,      0,      1,      0,      1,      -1,     0   },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "[]=",    tile },    /* first entry is default */
	{ "><>",    NULL },    /* no layout function means floating behavior */
	{ "[M]",    monocle },
	{ "[D]",    deck },
	{ "[=]",    bstack },
	{ "[#]",    grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTMOD Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "1"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg0, "-nf", col_fg0, "-sb", col_bg3, "-sf", col_fg1, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *termfloatcmd0[] = { "st", "-c", "floating", "-g", "120x40", NULL };
static const char *termfloatcmd1[] = { "st", "-c", "floating-alt", "-g", "120x40", NULL };
static const char *filecmd[] = { "st", "-t", "nnn", "-e", "n3", NULL };
static const char *htopcmd[] = { "st", "-c", "floating", "-g", "190x45", "-e", "htop", NULL };
static const char *cointopcmd[] = { "st", "-c", "floating", "-g", "176x44", "-e", "cointop", NULL };
/* primary scratchpads */
static const char *scratchpadcmd[] = { "s", "st", "-t", "scratchpad", "-c", "term-scratch", "-g", "135x40", NULL };
static const char *calculatorcmd[] = { "c", "calc.sh", NULL };
static const char *mpvcmd[] = { "v", "mpv", NULL };
/* vacant scratchpads */
static const char *addtermcmd[]  = { "t", "st", NULL };
static const char *addfloatcmd[]  = { "f", "st", "-c", "floating", NULL };

/* additional keysyms */
#include <X11/XF86keysym.h>

static Key keys[] = {
	/* MODIFIER             KEY             FUNCTION        ARGUMENT */
	/* commands */
	{ MODKEY,               XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY|ALTMOD,        XK_Return,      spawn,          {.v = termfloatcmd0 } },
	{ MODKEY|ShiftMask,     XK_f,           spawn,          {.v = termfloatcmd1 } },
	{ MODKEY|ShiftMask,     XK_Return,      spawn,          {.v = filecmd } },
	{ MODKEY,               XK_semicolon,   spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_t,           spawn,          {.v = htopcmd } },
	{ MODKEY,               XK_r,           spawn,          {.v = cointopcmd } },
	{ MODKEY|ALTMOD,        XK_b,           spawn,          SHCMD("$BROWSER") },
	{ MODKEY|ALTMOD,        XK_v,           spawn,          SHCMD("st -e $EDITOR") },
	{ MODKEY|ALTMOD,        XK_m,           spawn,          SHCMD("st -e neomutt") },
	{ MODKEY|ALTMOD,        XK_n,           spawn,          SHCMD("st -e newsboat") },
	{ MODKEY|ALTMOD,        XK_d,           spawn,          SHCMD("st -e podboat") },
	{ MODKEY|ALTMOD,        XK_t,           spawn,          SHCMD("st -e tmux") },
	{ MODKEY|ALTMOD,        XK_r,           spawn,          SHCMD("doc-exec") },
	{ MODKEY|ALTMOD,        XK_p,           spawn,          SHCMD("mpd-client") },
	{ MODKEY|ALTMOD,        XK_f,           spawn,          SHCMD("libreoffice") },
	{ MODKEY|ALTMOD,        XK_s,           spawn,          SHCMD("jail tastyworks") },
	{ MODKEY|ALTMOD,        XK_o,           spawn,          SHCMD("tor-launch.sh") },
	{ MODKEY|ALTMOD,        XK_equal,       spawn,          SHCMD("sudo vpn toggle &") },
	{ MODKEY|ControlMask,   XK_b,           spawn,          SHCMD("websearch.sh") },
	{ MODKEY|ControlMask,   XK_m,           spawn,          SHCMD("mediasearch.sh") },
	{ MODKEY|ControlMask,   XK_v,           spawn,          SHCMD("yt.sh") },
	{ MODKEY|ControlMask,   XK_p,           spawn,          SHCMD("passmenu") },
	{ MODKEY|ControlMask,   XK_slash,       spawn,          SHCMD("emenu") },
	{ MODKEY,               XK_grave,       spawn,          SHCMD("econfig") },
	{ MODKEY,               XK_x,           spawn,          SHCMD("clipout") },
	{ MODKEY,               XK_w,           spawn,          SHCMD("blink.sh") },
	{ MODKEY,               XK_Insert,      spawn,          SHCMD("mnt &") },
	{ MODKEY,               XK_Delete,      spawn,          SHCMD("mnt -u &") },
	/* window controls */
	{ MODKEY,               XK_Tab,         togglebar,      {0} },
	{ MODKEY,               XK_a,           togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,               XK_c,           togglescratch,  {.v = calculatorcmd } },
	{ MODKEY,               XK_v,           togglescratch,  {.v = mpvcmd } },
	{ MODKEY,               XK_equal,       togglescratch,  {.v = addtermcmd } },
	{ MODKEY|ALTMOD,        XK_space,       togglescratch,  {.v = addfloatcmd } },
	{ MODKEY,               XK_j,           focusstack,     {.i = +1 } },
	{ MODKEY,               XK_k,           focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_j,           pushdown,       {0} },
	{ MODKEY|ShiftMask,     XK_k,           pushup,         {0} },
	{ MODKEY|ControlMask,   XK_j,           inplacerotate,  {.i = -2} },
	{ MODKEY|ControlMask,   XK_k,           inplacerotate,  {.i = +2} },
	{ MODKEY|ControlMask,   XK_h,           setmfact,       {.f = -0.01} },
	{ MODKEY|ControlMask,   XK_l,           setmfact,       {.f = +0.01} },
	{ MODKEY|ShiftMask,     XK_equal,       incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_minus,       incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,   XK_space,       zoom,           {0} },
	{ MODKEY,               XK_apostrophe,  view,           {0} },
	{ MODKEY,               XK_b,           warp,           {0} },
	{ MODKEY,               XK_q,           killclient,     {0} },
	{ MODKEY|ShiftMask,     XK_b,           killclient,     {0} },
	{ MODKEY|ShiftMask,     XK_Escape,      killunsel,      {0} },
	{ ALTMOD|ControlMask,   XK_h,           setlayout,      {.v = &layouts[0]} },
	{ ALTMOD|ControlMask,   XK_f,           setlayout,      {.v = &layouts[1]} },
	{ ALTMOD|ControlMask,   XK_u,           setlayout,      {.v = &layouts[2]} },
	{ ALTMOD|ControlMask,   XK_i,           setlayout,      {.v = &layouts[3]} },
	{ ALTMOD|ControlMask,   XK_b,           setlayout,      {.v = &layouts[4]} },
	{ ALTMOD|ControlMask,   XK_g,           setlayout,      {.v = &layouts[5]} },
	{ ALTMOD|ControlMask,   XK_l,           setlayout,      {0} },
	{ ALTMOD|ControlMask,   XK_space,       togglefloating, {0} },
	{ ALTMOD|ControlMask,   XK_Return,      togglefullscr,  {0} },
	{ MODKEY,               XK_0,           view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,           tag,            {.ui = ~0 } },
	{ MODKEY,               XK_space,       focusmon,       {.i = +1 }  },
	{ MODKEY|ShiftMask,     XK_space,       tagmon,         {.i = +1 }  },
	{ MODKEY,               XK_h,           viewtoleft,     {0} },
	{ MODKEY,               XK_l,           viewtoright,    {0} },
	{ MODKEY|ShiftMask,     XK_h,           tagtoleft,      {0} },
	{ MODKEY|ShiftMask,     XK_l,           tagtoright,     {0} },
	TAGKEYS(                XK_y,                            0)
	TAGKEYS(                XK_u,                            1)
	TAGKEYS(                XK_i,                            2)
	TAGKEYS(                XK_o,                            3)
	TAGKEYS(                XK_p,                            4)
	TAGKEYS(                XK_6,                            5)
	TAGKEYS(                XK_7,                            6)
	TAGKEYS(                XK_8,                            7)
	TAGKEYS(                XK_9,                            8)
	{ MODKEY|ShiftMask,     XK_q,           quit,           {0} },
	/* media controls */
	{ 0,                    XK_Pause,                   spawn,      SHCMD("mpc toggle") },
	{ 0,                    XF86XK_AudioMute,           spawn,      SHCMD("vol -m") },
	{ 0,                    XF86XK_AudioLowerVolume,    spawn,      SHCMD("vol -c -5") },
	{ 0,                    XF86XK_AudioRaiseVolume,    spawn,      SHCMD("vol -c +5") },
	{ ControlMask,          XF86XK_AudioLowerVolume,    spawn,      SHCMD("vol -c -2") },
	{ ControlMask,          XF86XK_AudioRaiseVolume,    spawn,      SHCMD("vol -c +2") },
	{ ShiftMask,            XF86XK_AudioLowerVolume,    spawn,      SHCMD("vol -c -10") },
	{ ShiftMask,            XF86XK_AudioRaiseVolume,    spawn,      SHCMD("vol -c +10") },
	{ MODKEY,               XF86XK_Back,                spawn,      SHCMD("vol -c -1") },
	{ MODKEY,               XF86XK_Forward,             spawn,      SHCMD("vol -c +1") },
	{ 0,                    XF86XK_AudioPlay,           spawn,      SHCMD("mpc toggle") },
	{ 0,                    XF86XK_AudioStop,           spawn,      SHCMD("mpc stop") },
	{ 0,                    XF86XK_AudioPrev,           spawn,      SHCMD("mpc prev") },
	{ 0,                    XF86XK_AudioNext,           spawn,      SHCMD("mpc next") },
	{ MODKEY,               XK_Left,                    spawn,      SHCMD("mpc seek -15") },
	{ MODKEY,               XK_Right,                   spawn,      SHCMD("mpc seek +15") },
	{ MODKEY,               XK_Down,                    spawn,      SHCMD("mpc seek -60") },
	{ MODKEY,               XK_Up,                      spawn,      SHCMD("mpc seek +60") },
	{ MODKEY|ControlMask,   XK_Left,                    spawn,      SHCMD("mpc repeat") },
	{ MODKEY|ControlMask,   XK_Right,                   spawn,      SHCMD("mpc consume") },
	{ MODKEY|ControlMask,   XK_Down,                    spawn,      SHCMD("mpc seek 0%") },
	{ MODKEY|ControlMask,   XK_Up,                      spawn,      SHCMD("mpc rescan") },
	{ MODKEY,               XK_backslash,               spawn,      SHCMD("mpc toggle") },
	{ MODKEY|ControlMask,   XK_backslash,               spawn,      SHCMD("mpc clear") },
	{ MODKEY,               XK_BackSpace,               spawn,      SHCMD("mpc seek 0%") },
	{ MODKEY,               XK_Pause,                   spawn,      SHCMD("mpv-ctl.sh toggle") },
	{ MODKEY,               XK_Break,                   spawn,      SHCMD("mpv-ctl.sh toggle") },
	/* miscellaneous */
	{ 0,                            XK_Print,           spawn,      SHCMD("capture.sh -0") },
	{ MODKEY,                       XK_Print,           spawn,      SHCMD("capture.sh -1") },
	{ MODKEY|ControlMask,           XK_Print,           spawn,      SHCMD("capture.sh -2") },
	{ 0,                            XF86XK_ScreenSaver, spawn,      SHCMD("slock") },
	{ MODKEY|ShiftMask,             XK_F11,             spawn,      SHCMD("refresh dwmblocks") },
	{ MODKEY|ShiftMask,             XK_F12,             spawn,      SHCMD("refresh dunst") },
	{ MODKEY|ALTMOD|ControlMask,    XK_q,               spawn,      SHCMD("prompt-shutdown.sh -s") },
	{ MODKEY|ALTMOD|ControlMask,    XK_r,               spawn,      SHCMD("prompt-shutdown.sh -r") },
};

static const char *rootmenu[] = { "xmenu-run -r", NULL };
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click            event mask          button      function        argument */
	{ ClkLtSymbol,      0,                  Button1,    setlayout,      {0} },
	{ ClkLtSymbol,      0,                  Button3,    setlayout,      {.v = &layouts[2]} },
	{ ClkClientWin,     MODKEY,             Button1,    movemouse,      {0} },
	{ ClkClientWin,     MODKEY,             Button2,    togglefloating, {0} },
	{ ClkClientWin,     MODKEY,             Button3,    resizemouse,    {0} },
	{ ClkClientWin,     MODKEY|ControlMask, Button3,    killclient,     {0} },
	{ ClkTagBar,        0,                  Button1,    view,           {0} },
	{ ClkTagBar,        0,                  Button3,    toggleview,     {0} },
	{ ClkTagBar,        MODKEY,             Button1,    tag,            {0} },
	{ ClkTagBar,        MODKEY,             Button2,    toggletag,      {0} },
	{ ClkWinTitle,      0,                  Button2,    zoom,           {0} },
	{ ClkRootWin,       0,                  Button3,    spawn,          {.v = rootmenu } },
	{ ClkStatusText,    0,                  Button1,    sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,    0,                  Button2,    sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,    0,                  Button3,    sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,    0,                  Button4,    sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,    0,                  Button5,    sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,    MODKEY,             Button1,    sigdwmblocks,   {.i = 6} },
	{ ClkStatusText,    MODKEY,             Button2,    sigdwmblocks,   {.i = 7} },
	{ ClkStatusText,    MODKEY,             Button3,    sigdwmblocks,   {.i = 8} },
};

/* dwmc client */
/* function definitions */
void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
};

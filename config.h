/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int swterminheritfs    = 1;        /* 1 terminal inherits fullscreen on unswallow, 0 otherwise */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = {
		"sans-serif:size=16:hinting=true:antialias=true:autohint=false:hintstyle=hintnone:rgba=rgb:lcdfilter=lcdefault:fontformat=TrueType",
		"OpenMoji:size=16:hinting=true:antialias=true:autohint=false:hintstyle=hintfull:rgba=rgb:lcdfilter=lcdefault:fontformat=TrueType"
		"Material Design Icons Desktop:size=16:hinting=true:antialias=true:autohint=false:hintstyle=hintfull:rgba=rgb:lcdfilter=lcdefault:fontformat=TrueType"
};
static const char dmenufont[]       = "sans-serif:size=16:hinting=true:antialias=true:autohint=false:hintstyle=hintnone:rgba=rgb:lcdfilter=lcdefault:fontformat=TrueType";
/* colors */
static const char col_black[]       = "#000000";
static const char col_red[]         = "#FF0000";
static const char col_green[]       = "#00FF00";
static const char col_yellow[]      = "#FFFF00";
static const char col_white[]       = "#FFFFFF";
static const char *colors[][3]      = {
    /*                      fg         bg        border   */
    [SchemeNorm]    = { col_white,  col_black,  col_red   },
    [SchemeSel]     = { col_white,  col_black,  col_green },
    [SchemeStatus]  = { col_white,  col_black,  NULL  },
};

/* status bar */
static const Block blocks[] = {
	/* fg     command				interval	signal */
	{ col_white, "sb-clock",			1,		1},
	{ col_white, "sb-volume",			1,		2},
	{ col_white, "sb-memory",			1,		3},
	{ col_white, "sb-cpu",		 		1,		4},
/*	{ col_white, "sb-doppler",			0,		6},*/
};

/* inverse the order of the blocks, comment to disable */
#define INVERSED	1
/* delimeter between blocks commands. NULL character ('\0') means no delimeter. */
static char delimiter[] = " | ";
/* max number of character that one block command can output */
#define CMDLENGTH	50
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "St",       NULL,       NULL,            0,         0,          1,           0,        -1 },
	{ NULL,       NULL,       "Event Tester",  0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_white, "-sb", col_black, "-sf", col_green, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *prtscrcmd[] = { "flameshot", "gui", NULL};
static const char *roficmd[] = { "/home/justcausewhynot/.config/rofi/scripts/launcher_t1" };
static const char *play_pausecmd[] = { "playerctl", "play-pause", NULL };
static const char *previouscmd[] = { "playerctl", "previous", NULL };
static const char *nextcmd[] = { "playerctl", "next", NULL };
static const char *ffcmd[] = { "playerctl", "position", "15+", NULL };
static const char *rrcmd[] = { "playerctl", "position", "15-", NULL };
static const char *shiftplayercmd[] = { "playerctld", "shift", NULL };
static const char *unshiftplayercmd[] = { "playerctld", "unshift", NULL };
static const char *sxcs[]= { "sxc", NULL };

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_u,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = roficmd } },
	{ 0,                            XK_Print,  spawn,          {.v = prtscrcmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = shiftplayercmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = unshiftplayercmd } },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          {.v = ffcmd } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = rrcmd } },
	{ 0,                     XF86XK_AudioPlay, spawn,          {.v = play_pausecmd } },
	{ 0,                     XF86XK_AudioPrev, spawn,          {.v = previouscmd } },
	{ 0,                     XF86XK_AudioNext, spawn,          {.v = nextcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscreen, {0} },
	{ MODKEY|Mod1Mask,              XK_f,      togglefakefullscreen, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sendstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,              Button2,        sendstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,              Button3,        sendstatusbar,   {.i = 3 } },
	{ ClkStatusText,        0,              Button4,        sendstatusbar,   {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        sendstatusbar,   {.i = 5 } },
	{ ClkStatusText,        ShiftMask,      Button1,        sendstatusbar,   {.i = 6 } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


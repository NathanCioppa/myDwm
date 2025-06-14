/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int margin    = 10;
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_black[]       = "#000000";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_main[]        = "#d6a3ff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_gray2 },
	[SchemeSel]  = { col_gray2, col_main,  col_main  },
};

static const unsigned int baralpha = 0xd8;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3]      = {
    /*               fg      bg       border     */
    [SchemeNorm] = { OPAQUE, 0x8c,    OPAQUE },
    [SchemeSel]  = { OPAQUE, OPAQUE,  OPAQUE },
};

static const char HomeClass[] = "MAGIHome";
static const char MasterTerminalChildClass[] = "MasterTerminalRedirect";

/* tagging */
static const char *tags[] = { "Home", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		     instance    title       tags mask     isfloating   monitor */
	{ MasterTerminalChildClass,  NULL,       NULL,       0,            0,            1 },
	{ HomeClass,                 NULL,       NULL,       0,            0,            0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define SUPERKEY Mod4Mask
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ SUPERKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ SUPERKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ SUPERKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ SUPERKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray2, "-nf", col_gray3, "-sb", col_main, "-sf", col_gray2, NULL };

static const char *dmenuBluetooth[] = { "dmenu_bluetooth", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray2, "-nf", col_gray3, "-sb", col_main, "-sf", col_gray2, NULL };

static const char *volumeUp[] = { "volumeUp", "5", NULL };
static const char *volumeUpFine[] = { "volumeUp", "1", NULL };
static const char *volumeDown[] = { "volumeDown", "5", NULL };
static const char *volumeDownFine[] = { "volumeDown", "1", NULL };

static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = dmenuBluetooth } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ SUPERKEY,                       XK_b,      togglebar,      {0} },
	{ SUPERKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ SUPERKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ SUPERKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ SUPERKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ SUPERKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ SUPERKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ SUPERKEY,                       XK_Return, zoom,           {0} },
	{ SUPERKEY,                       XK_Tab,    cycleTagsRight, {0} },
	{ SUPERKEY|ShiftMask,		XK_Tab,    cycleTagsLeft,  {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ SUPERKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ SUPERKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ SUPERKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ SUPERKEY,                       XK_space,  setlayout,      {0} },
	{ SUPERKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ SUPERKEY,                       XK_minus,      view,       {.ui = ~0 } },
	{ SUPERKEY|ShiftMask,             XK_minus,      tag,        {.ui = ~0 } },
	{ SUPERKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ SUPERKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ SUPERKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ SUPERKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(			XK_0,			   0)
	TAGKEYS(                        XK_1,                      1)
	TAGKEYS(                        XK_2,                      2)
	TAGKEYS(                        XK_3,                      3)
	TAGKEYS(                        XK_4,                      4)
	TAGKEYS(                        XK_5,                      5)
	TAGKEYS(                        XK_6,                      6)
	TAGKEYS(                        XK_7,                      7)
	TAGKEYS(                        XK_8,                      8)
	TAGKEYS(                        XK_9,                      9)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{MODKEY,			XK_equal,  spawn,	   {.v = volumeUp } },
	{MODKEY|ShiftMask,		XK_equal,  spawn,	   {.v = volumeUpFine } },
	{MODKEY,			XK_minus,  spawn,	   {.v = volumeDown } },
	{MODKEY|ShiftMask,		XK_minus,  spawn,	   {.v = volumeDownFine } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int hidevacanttags     = 1;    /* 1 means hide empty tags / 0: show every tag */
static const unsigned int snap      = 8;       /* snap pixel */
static const unsigned int gappih    = 4;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 4;       /* vert inner gap between windows */
static const unsigned int gappoh    = 9;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 9;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:pixelsize=11" };
static const char dmenufont[]       = "JetBrains Mono:pixelsize=11";
#include "/home/xemadp/.cache/wal/colors-wal-dwm-no-urg.h"

static const char *const autostart[] = {
	"walcur", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "st-float",     NULL,       NULL,       0,            1,           -1 },
	{ NULL,     "st-float",       NULL,       0,            1,           -1 },
};

/* window swallowing */
static const int swaldecay = 3;
static const int swalretroactive = 1;
static const char swalsymbol[] = ">S<";
/* layout(s) */
static const float mfact     = 0.59; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "unfloat.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle }, 	 /* 1 */
	{ "[@]",      spiral },          /* 2 */ 
	{ "[\\]",     dwindle },         /* 3 */ 
	{ "H[]",      deck },            /* 4 */ 
	{ "TTT",      bstack },          /* 5 */ 
	{ "===",      bstackhoriz },     /* 6 */ 
	{ "HHH",      grid },            /* 7 */ 
	{ "###",      nrowgrid },        /* 8 */ 
	{ "---",      horizgrid },       /* 9 */ 
	{ ":::",      gaplessgrid },     /* 10 */
	{ "|M|",      centeredmaster },  /* 11 */
	{ ">M>",      centeredfloatingmaster },    /* 12 */    
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", norm_border, "-sf", norm_bg, NULL }; 
static const char *termcmd[]  = { "st", NULL };


/* Keybindigs 
 * Super+p               : dmenu_run
 * Super+r               : ranger (Floating)
 * Super+z               : Terminal ( st ) (Floating)
 * Super+y               : ytfzf
 * Super+n               : newsboat
 * Super+Shift+n         : ncmpcpp (Floating)
 * Super+w               : random wallpaper
 * Super+c               : Open .configs (Floating)
 * Super+[               : lower volume (needs pamixer)
 * Super+]               : increase volume "
 * Super+comma           : prev song                               |
 * Super+period          : next song                               |
 * Super+Shift+p         : toggle song playing                     | managed by my mpcdunst script
 * Super+Shift+s         : toggle mpd shuffle                      |        
 * Super+Shift+i         : increase floating window size by 10             |
 * Super+Shift+d         : decrease floating window size by 10             |
 * Super+Shift+l         : increase floating window horizontal size by 10  | managed by my windowsresize script
 * Super+Shift+h         : decrease floating window horizontal size by 10  |
 * Printscreen           : take a screenshot and also copy the image into clipboard.            |
 * Super+Printscreen     : take a screenshot(selection) and also copy the image into clipboard. | managed by my scrotcp script
 */

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,                spawn,          SHCMD("dmenu_run -c -l 10") },
	{ MODKEY,                       XK_z,                spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_r,                spawn,          SHCMD("st -n 'st-float' -g '120x30' -e ranger") },
	{ MODKEY,                       XK_y,                spawn,          SHCMD("st -e ytfzf -f -t -l -s") },
	{ MODKEY|ShiftMask,             XK_y,                spawn,          SHCMD("st -e ytfzf -f -t -l -s -d") },
	{ MODKEY,                       XK_n,                spawn,          SHCMD("st -e newsboat")},
	{ MODKEY|ShiftMask,             XK_n,                spawn,          SHCMD("st -n 'st-float' -g '120x30' -e ncmpcpp")},
	{ MODKEY,                       XK_w,                spawn,          SHCMD("randwal")	},
	{ MODKEY,                       XK_c,                spawn,          SHCMD("st -e ranger ~/.config/") },
	{ MODKEY,                       XK_bracketleft,      spawn,          SHCMD("pamixer -d 5") },
	{ MODKEY,                       XK_bracketright,     spawn,          SHCMD("pamixer -i 5") },
	{ MODKEY,                       XK_comma,            spawn,          SHCMD("mpc prev") },
	{ MODKEY,                       XK_period,           spawn,          SHCMD("mpc next") },
	{ MODKEY|ShiftMask,             XK_p,                spawn,          SHCMD("mpcdunst t") },
	{ MODKEY|ShiftMask,             XK_s,                spawn,          SHCMD("mpcdunst r") },
	{ MODKEY|ShiftMask,             XK_i,                spawn,          SHCMD("windowresize i 10") },
	{ MODKEY|ShiftMask,             XK_d,                spawn,          SHCMD("windowresize d 10") },
	{ MODKEY|ShiftMask,             XK_l,                spawn,          SHCMD("windowresize ix 10") },
	{ MODKEY|ShiftMask,             XK_h,                spawn,          SHCMD("windowresize dx 10") },
	{ NULL,                         XK_Print,            spawn,          SHCMD("scrotcp") },
	{ MODKEY,                       XK_Print,            spawn,          SHCMD("scrotcp -s") },
	{ MODKEY,                       XK_b,                togglebar,      {0} },
	{ MODKEY,                       XK_j,                focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                focusstack,     {.i = -1 } },
 	{ MODKEY|ShiftMask,             XK_j,								 movestack,      {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_k,								 movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,                incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                setmfact,       {.f = -0.005} },
	{ MODKEY,                       XK_l,                setmfact,       {.f = +0.005} },
	{ MODKEY,                       XK_Return, setlayout,           {0} },
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus,  incrigaps,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_x,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_u,      unfloatvisible, {.v = &layouts[0]} },
	{ MODKEY,                       XK_space,  zoom,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
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
static Button buttons[] = {
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
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      swalmouse,      {0} },
};

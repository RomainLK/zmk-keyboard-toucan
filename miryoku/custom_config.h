// Copyright 2021 Manna Harbour
// https://github.com/manna-harbour/miryoku



#define MIRYOKU_KLUDGE_MOUSEKEYSPR
#define MIRYOKU_CLIPBOARD_WIN

#define U_MRDO &kp LS(LG(Z))
#define U_MPST &kp LG(V)
#define U_MCPY &kp LG(C)
#define U_MCUT &kp LG(X)
#define U_MUND &kp LG(Z)

#define MIRYOKU_LAYER_BASE \
&kp Q,             &kp W,             &kp F,             &kp P,             &kp B,             &kp J,             &kp L,             &kp U,             &kp Y,             &kp SQT,           \
U_MT(LGUI, A),     U_MT(LALT, R),     U_MT(LCTRL, S),    U_MT(LSHFT, T),    &kp G,             &kp M,             U_MT(LSHFT, N),    U_MT(LCTRL, E),    U_MT(LALT, I),     U_MT(LGUI, O),     \
U_LT(U_BUTTON, Z), U_MT(RALT, X),     &kp C,             &kp D,             &kp V,             &kp K,             &kp H,             &kp COMMA,         U_MT(RALT, DOT),   U_LT(U_BUTTON, SLASH),\
U_NP,              U_NP,              U_LT(U_MEDIA, ESC),U_LT(U_NAV, SPACE),U_LT(U_MOUSE, TAB),U_LT(U_NUM, RET),  U_LT(U_SYM, BSPC), U_LT(U_FUN, DEL),  U_NP,              U_NP


#define MIRYOKU_LAYER_NAV \
U_NA,              &kp PSCRN,     &kp LC(S),         &kp F5,            &kp F12,           U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             \
&kp LGUI,          &kp LALT,          &kp LCTRL,         &kp LSHFT,         U_NA,              &u_caps_word,      &kp LEFT,          &kp DOWN,          &kp UP,            &kp RIGHT,         \
U_UND,             U_CUT,             U_CPY,             &kp BSPC,          U_PST,             &kp INS,           &kp HOME,          &kp PG_DN,         &kp PG_UP,         &kp END,           \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              &kp RET,           &kp BSPC,          &kp DEL,           U_NP,              U_NP


#define MIRYOKU_LAYER_SYM \
&kp PRCNT,         &kp HASH,          &kp SEMI,         &kp COLON,          &kp EXCL,          U_NA,              &u_to_U_BASE,      &u_to_U_EXTRA,     &u_to_U_TAP,       U_BOOT,            \
&kp AT,            &kp DLLR,          &kp LBRC,         &kp RBRC,           &kp PIPE,          U_NA,              &kp LSHFT,         &kp LCTRL,         &kp LALT,          &kp LGUI,          \
&kp TILDE,         &kp CARET,         &kp LBKT,         &kp RBKT,           &kp AMPS,          U_NA,              &u_to_U_SYM,       &u_to_U_NAV,       &kp RALT,          U_NA,              \
U_NP,              U_NP,              &kp LPAR,         &kp RPAR,           &kp UNDER,         U_NA,              U_NA,              U_NA,              U_NP,              U_NP

#define MIRYOKU_LAYER_MEDIA \
U_BOOT,            &u_to_U_TAP,       &u_to_U_EXTRA,     &u_to_U_BASE,      &u_to_U_MBASE,              &kp KP_NUMLOCK,         U_RGB_EFF,         &kp C_VOL_UP,      U_RGB_HUI,         U_RGB_SAI,         \
&kp LGUI,          &kp LALT,          &kp LCTRL,         &kp LSHFT,         U_NA,              U_EP_TOG,          &kp C_PREV,        &kp C_VOL_DN,      &kp C_NEXT,        U_RGB_BRI,         \
U_NA,              &kp RALT,          &u_to_U_FUN,       &u_to_U_MEDIA,     U_NA,              &u_out_tog,        &u_bt_sel_0,       &u_bt_sel_1,       &u_bt_sel_2,       &u_bt_sel_3,       \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              &kp C_STOP,        &kp C_PP,          &kp C_MUTE,        U_NP,              U_NP


#define MIRYOKU_LAYER_NUM \
&kp ASTRK,         &kp N7,            &kp N8,            &kp N9,            &kp PLUS,          U_NA,              &u_to_U_BASE,      &u_to_U_EXTRA,     &u_to_U_TAP,       U_BOOT,            \
&euro_sign,        &kp N4,            &kp N5,            &kp N6,            &kp EQUAL,         U_NA,              &kp LSHFT,         &kp LCTRL,         &kp LALT,          &kp LGUI,          \
&kp GRAVE,         &kp N1,            &kp N2,            &kp N3,            &kp BSLH,          U_NA,              &u_to_U_NUM,       &u_to_U_MOUSE,       &kp RALT,          U_NA,              \
U_NP,              U_NP,              &kp DOT,           &kp N0,            &kp MINUS,         U_NA,              U_NA,              U_NA,              U_NP,              U_NP



#define MIRYOKU_LAYER_BUTTON \
U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             \
&kp LGUI,          &kp LALT,          &kp LCTRL,         &kp LSHFT,         U_NU,              U_NU,              &kp LSHFT,         &kp LCTRL,         &kp LALT,          &kp LGUI,          \
U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             \
U_NP,              U_NP,              U_BTN3,            U_BTN1,            U_BTN2,            U_BTN2,            U_BTN1,            U_BTN3,            U_NP,              U_NP


// MAC

#define MIRYOKU_LAYER_MBASE \
&kp Q,             &kp W,             &kp F,             &kp P,             &kp B,             &kp J,             &kp L,             &kp U,             &kp Y,             &kp SQT,           \
U_MT(LCTRL, A),    U_MT(LALT, R),     U_MT(LGUI, S),     U_MT(LSHFT, T),    &kp G,             &kp M,             U_MT(LSHFT, N),    U_MT(LGUI, E),    U_MT(LALT, I),     U_MT(LCTRL, O),     \
U_LT(U_MBUTTON, Z), U_MT(RALT, X),     &kp C,             &kp D,             &kp V,             &kp K,             &kp H,             &kp COMMA,         U_MT(RALT, DOT),   U_LT(U_MBUTTON, SLASH),\
U_NP,              U_NP,              U_LT(U_MMEDIA, ESC),U_LT(U_MNAV, SPACE),U_LT(U_MMOUSE, TAB),U_LT(U_MNUM, RET),  U_LT(U_MSYM, BSPC), U_LT(U_MFUN, DEL),  U_NP,              U_NP

#define MIRYOKU_LAYER_MMEDIA \
U_BOOT,            &u_to_U_TAP,       &u_to_U_EXTRA,     &u_to_U_BASE,      U_NA,              U_RGB_TOG,         U_RGB_EFF,         U_RGB_HUI,         U_RGB_SAI,         U_RGB_BRI,         \
&kp LCTRL,          &kp LALT,          &kp LGUI,         &kp LSHFT,         U_NA,              U_EP_TOG,          &kp C_PREV,        &kp C_VOL_DN,      &kp C_VOL_UP,      &kp C_NEXT,        \
U_NA,              &kp RALT,          &u_to_U_MFUN,       &u_to_U_MMEDIA,     U_NA,              &u_out_tog,        &u_bt_sel_0,       &u_bt_sel_1,       &u_bt_sel_2,       &u_bt_sel_3,       \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              &kp C_STOP,        &kp C_PP,          &kp C_MUTE,        U_NP,              U_NP


#define MIRYOKU_LAYER_MBUTTON \
U_MUND,             U_MCUT,             U_MCPY,             U_MPST,             U_MRDO,             U_MRDO,             U_MPST,             U_MCPY,             U_MCUT,             U_MUND,             \
&kp LCTRL,          &kp LALT,           &kp LGUI,           &kp LSHFT,          U_NU,               U_NU,               &kp LSHFT,          &kp LGUI,           &kp LALT,           &kp LCTRL,          \
U_MUND,             U_MCUT,             U_MCPY,             U_MPST,             U_MRDO,             U_MRDO,             U_MPST,             U_MCPY,             U_MCUT,             U_MUND,             \
U_NP,               U_NP,               U_BTN3,             U_BTN1,             U_BTN2,             U_BTN2,             U_BTN1,             U_BTN3,             U_NP,               U_NP


#define MIRYOKU_LAYER_MNAV \
U_NA,              &kp LG(LS(N4)),    &kp LG(S),         &kp LG(R),                    &kp LG(LA(I)),                    U_MRDO,            U_MPST,            U_MCPY,            U_MCUT,            U_MUND,             \
&kp LCTRL,         &kp LALT,          &kp LGUI,          &kp LSHFT,                    U_NA,                              &u_caps_word,      &kp LEFT,          &kp DOWN,          &kp UP,            &kp RIGHT,         \
U_MUND,            U_MCUT,            U_MCPY,            &kp BSPC,                     U_MPST,                            &kp INS,           &kp HOME,          &kp PG_DN,         &kp PG_UP,         &kp END,           \
U_NP,              U_NP,              U_NA,              U_NA,                         U_NA,                              &kp RET,           &kp BSPC,          &kp DEL,           U_NP,              U_NP



#define MIRYOKU_LAYER_MMOUSE \
U_BOOT,            &u_to_U_TAP,       &u_to_U_EXTRA,     &u_to_U_BASE,      U_NA,              U_MRDO,            U_MPST,            U_MCPY,            U_MCUT,            U_MUND,             \
&kp LCTRL,         &kp LALT,          &kp LGUI,          &kp LSHFT,         U_NA,              U_NU,              U_MS_L,            U_MS_D,            U_MS_U,            U_MS_R,             \
U_NA,              &kp RALT,          &u_to_U_MNUM,      &u_to_U_MMOUSE,    U_NA,              U_NU,              U_WH_L,            U_WH_D,            U_WH_U,            U_WH_R,            \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              U_BTN2,            U_BTN1,            U_BTN3,            U_NP,              U_NP

#define MIRYOKU_LAYER_MSYM \
&kp PRCNT,         &kp LA(N3),          &kp SEMI,         &kp COLON,          &kp EXCL,          U_NA,              &u_to_U_BASE,      &u_to_U_EXTRA,    &u_to_U_TAP,       U_BOOT,            \
&kp AT,            &kp DLLR,          &kp LBRC,         &kp RBRC,           &kp PIPE,          U_NA,              &kp LSHFT,         &kp LGUI,         &kp LALT,          &kp LCTRL,          \
&kp TILDE,         &kp CARET,         &kp LBKT,         &kp RBKT,           &kp AMPS,          U_NA,              &u_to_U_MSYM,      &u_to_U_MNAV,     &kp RALT,          U_NA,              \
U_NP,              U_NP,              &kp LPAR,         &kp RPAR,           &kp UNDER,         U_NA,              U_NA,              U_NA,              U_NP,              U_NP


#define MIRYOKU_LAYER_MNUM \
&kp ASTRK,         &kp N7,            &kp N8,            &kp N9,            &kp PLUS,          U_NA,              &u_to_U_BASE,      &u_to_U_EXTRA,     &u_to_U_TAP,       U_BOOT,            \
&kp LA(N2),         &kp N4,            &kp N5,            &kp N6,            &kp EQUAL,         U_NA,              &kp LSHFT,         &kp LGUI,          &kp LALT,          &kp LCTRL,          \
&kp GRAVE,         &kp N1,            &kp N2,            &kp N3,            &kp BSLH,          U_NA,              &u_to_U_MNUM,      &u_to_U_MMOUSE,    &kp RALT,          U_NA,              \
U_NP,              U_NP,              &kp DOT,           &kp N0,            &kp MINUS,         U_NA,              U_NA,              U_NA,              U_NP,              U_NP


#define MIRYOKU_LAYER_MFUN \
&kp F12,           &kp F7,            &kp F8,            &kp F9,            &kp PSCRN,         U_NA,              &u_to_U_BASE,      &u_to_U_EXTRA,     &u_to_U_TAP,       U_BOOT,            \
&kp F11,           &kp F4,            &kp F5,            &kp F6,            &kp SLCK,          U_NA,              &kp LSHFT,         &kp LCTRL,         &kp LALT,          &kp LCTRL,          \
&kp F10,           &kp F1,            &kp F2,            &kp F3,            &kp PAUSE_BREAK,   U_NA,              &u_to_U_MFUN,      &u_to_U_MMEDIA,    &kp RALT,          U_NA,              \
U_NP,              U_NP,              &kp K_APP,         &kp SPACE,         &kp TAB,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP




#define MIRYOKU_LAYER_LIST \
MIRYOKU_X(BASE,   "Base") \
MIRYOKU_X(EXTRA,  "Extra") \
MIRYOKU_X(TAP,    "Tap") \
MIRYOKU_X(BUTTON, "Button") \
MIRYOKU_X(NAV,    "Nav") \
MIRYOKU_X(MOUSE,  "Mouse") \
MIRYOKU_X(MEDIA,  "Media") \
MIRYOKU_X(NUM,    "Num") \
MIRYOKU_X(SYM,    "Sym") \
MIRYOKU_X(FUN,    "Fun") \
MIRYOKU_X(MBASE,   "MBase") \
MIRYOKU_X(MBUTTON,   "MButton") \
MIRYOKU_X(MMEDIA,   "MMedia") \
MIRYOKU_X(MNAV,    "MNav") \
MIRYOKU_X(MMOUSE,    "MMouse") \
MIRYOKU_X(MSYM,    "MSym") \
MIRYOKU_X(MNUM,    "MNum") \
MIRYOKU_X(MFUN,    "MFun") \
// MIRYOKU_X(NUM_MAC,    "MNum") \
// MIRYOKU_X(SYM_MAC,    "MSym") \
// MIRYOKU_X(FUN_MAC,    "MFun")
//TODO define all other layers 


#define MIRYOKU_LAYERMAPPING_MBASE MIRYOKU_MAPPING
#define MIRYOKU_LAYERMAPPING_MMEDIA MIRYOKU_MAPPING
#define MIRYOKU_LAYERMAPPING_MBUTTON MIRYOKU_MAPPING
#define MIRYOKU_LAYERMAPPING_MNAV MIRYOKU_MAPPING
#define MIRYOKU_LAYERMAPPING_MMOUSE MIRYOKU_MAPPING
#define MIRYOKU_LAYERMAPPING_MSYM MIRYOKU_MAPPING
#define MIRYOKU_LAYERMAPPING_MNUM MIRYOKU_MAPPING
#define MIRYOKU_LAYERMAPPING_MFUN MIRYOKU_MAPPING


#define U_BASE   0
#define U_EXTRA  1
#define U_TAP    2
#define U_BUTTON 3
#define U_NAV    4
#define U_MOUSE  5
#define U_MEDIA  6
#define U_NUM    7
#define U_SYM    8
#define U_FUN    9
#define U_MBASE   10
#define U_MBUTTON   11
#define U_MMEDIA   12
#define U_MNAV   13
#define U_MMOUSE   14
#define U_MSYM   15
#define U_MNUM   16
#define U_MFUN   17
// #define UM_EXTRA  11
// #define UM_TAP    12
// #define UM_BUTTON 13
// #define UM_NAV    14
// #define UM_MOUSE  15
// #define UM_MEDIA  16
// #define UM_NUM    17
// #define UM_SYM    18
// #define UM_FUN    19
// #define U_GAME   10
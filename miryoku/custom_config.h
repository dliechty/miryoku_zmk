// Copyright 2021 Manna Harbour
// https://github.com/manna-harbour/miryoku

/ {
    behaviors {

        #define TYPING_STREAK_TERM 160 // global-quick-tap-ms
        #define KEY_REPEATING_TERM 300 // "tap then hold" for key auto-repeat
        #define HOMEY_TAPPING_TERM 200 // TAPPING_TERM + ALLOW_CROSSOVER_AFTER
        #define INDEX_TAPPING_TERM 180
        #define THUMB_TAPPING_TERM 200

        #define HOMEY_HOLDING_TYPE "tap-preferred"
        #define INDEX_HOLDING_TYPE "tap-preferred"
        #define THUMB_HOLDING_TYPE "balanced"
        
        //
        //
        // |------------------------|------------------------|
        // | LEFT_HAND_KEYS         |        RIGHT_HAND_KEYS |
        // |                        |                        |
        // |    0  1  2  3  4  5    |       6  7  8  9 10 11 |
        // |   12 13 14 15 16 17    |      18 19 20 21 22 23 |
        // |   24 25 26 27 28 29    |      30 31 32 33 34 35 |
        // |            36 37 38    |   39 40 41             |
        // |------------------------|------------------------|
        //
        #define LEFT_HAND_KEYS      \
              0  1  2  3  4  5      \
             12 13 14 15 16 17      \
             24 25 26 27 28 29
        #define RIGHT_HAND_KEYS     \
                                               6  7  8  9 10 11    \
                                              18 19 20 21 22 23    \
                                              30 31 32 33 34 35
        #define THUMB_KEYS          \
                       36 37 38          39 40 41
        //
        // Home row mod-tap keys for all except index fingers
        //
        homey_left: miryoku_home_row_mods_left_hand {
            compatible = "zmk,behavior-hold-tap";
            label = "HOME_ROW_MODS_LEFT_HAND";
            flavor = HOMEY_HOLDING_TYPE;
            hold-trigger-key-positions = <RIGHT_HAND_KEYS THUMB_KEYS>;
            hold-trigger-on-release; // wait for other home row mods
            tapping-term-ms = <HOMEY_TAPPING_TERM>;
            quick-tap-ms = <TYPING_STREAK_TERM>;
            global-quick-tap; // with typing streak
            #binding-cells = <2>;
            bindings = <&kp>, <&kp>;
        };
        homey_right: miryoku_home_row_mods_right_hand {
            compatible = "zmk,behavior-hold-tap";
            label = "HOME_ROW_MODS_RIGHT_HAND";
            flavor = HOMEY_HOLDING_TYPE;
            hold-trigger-key-positions = <LEFT_HAND_KEYS THUMB_KEYS>;
            hold-trigger-on-release; // wait for other home row mods
            tapping-term-ms = <HOMEY_TAPPING_TERM>;
            quick-tap-ms = <TYPING_STREAK_TERM>;
            global-quick-tap; // with typing streak
            #binding-cells = <2>;
            bindings = <&kp>, <&kp>;
        };
        //
        // Special home row mod-tap keys for the index fingers
        //
        index_left: miryoku_home_row_mods_left_index_shift {
            compatible = "zmk,behavior-hold-tap";
            label = "HOME_ROW_MODS_LEFT_INDEX_SHIFT";
            flavor = INDEX_HOLDING_TYPE;
            hold-trigger-key-positions = <RIGHT_HAND_KEYS THUMB_KEYS>;
            //hold-trigger-on-release; // don't wait for other mods
            tapping-term-ms = <INDEX_TAPPING_TERM>;
            quick-tap-ms = <KEY_REPEATING_TERM>; // enable repeat
            //global-quick-tap; // no typing streak
            #binding-cells = <2>;
            bindings = <&kp>, <&kp>;
        };
        index_right: miryoku_home_row_mods_right_index_shift {
            compatible = "zmk,behavior-hold-tap";
            label = "HOME_ROW_MODS_RIGHT_INDEX_SHIFT";
            flavor = INDEX_HOLDING_TYPE;
            hold-trigger-key-positions = <LEFT_HAND_KEYS THUMB_KEYS>;
            //hold-trigger-on-release; // don't wait for other mods
            tapping-term-ms = <INDEX_TAPPING_TERM>;
            quick-tap-ms = <KEY_REPEATING_TERM>; // enable repeat
            //global-quick-tap; // no typing streak
            #binding-cells = <2>;
            bindings = <&kp>, <&kp>;
        };
        //
        // Thumb cluster hold-tap keys for Miryoku layers
        //
        thumb: miryoku_thumb_layer {
            compatible = "zmk,behavior-hold-tap";
            label = "MIRYOKU_LAYER_TAP_WITH_REPEAT";
            flavor = THUMB_HOLDING_TYPE;
            tapping-term-ms = <THUMB_TAPPING_TERM>;
            quick-tap-ms = <KEY_REPEATING_TERM>; // enable repeat
            //global-quick-tap; // no typing streak
            #binding-cells = <2>;
            bindings = <&mo>, <&kp>;
        };

    };
};

#define IND_L(MOD, TAP) &index_left MOD TAP
#define IND_R(MOD, TAP) &index_right MOD TAP

#define HMY_L(MOD, TAP) &homey_left MOD TAP
#define HMY_R(MOD, TAP) &homey_right MOD TAP

#define THMB(MOD, TAP) &thumb MOD TAP

#define MIRYOKU_LAYER_BASE \
&kp Q,             &kp W,             &kp F,             &kp P,             &kp B,             &kp J,             &kp L,             &kp U,             &kp Y,             &kp SQT,              \
HMY_L(LGUI, A),    HMY_L(LALT, R),    HMY_L(LCTRL, S),   IND_L(LSHFT, T),   &kp G,             &kp M,             IND_R(LSHFT, N),   HMY_R(LCTRL, E),   HMY_R(LALT, I),    HMY_R(LGUI, O),       \
U_LT(U_BUTTON, Z), U_MT(RALT, X),     &kp C,             &kp D,             &kp V,             &kp K,             &kp H,             &kp COMMA,         U_MT(RALT, DOT),   U_LT(U_BUTTON, SLASH),\
U_NP,              U_NP,              THMB(U_MEDIA, ESC),THMB(U_NAV, SPACE),THMB(U_MOUSE, TAB),THMB(U_SYM, RET),  THMB(U_NUM, BSPC), THMB(U_FUN, DEL),  U_NP,              U_NP


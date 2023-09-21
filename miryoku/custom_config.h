// Copyright 2021 Manna Harbour
// https://github.com/manna-harbour/miryoku

/ {
    behaviors {

        //
        // Miryoku home row mods and thumb layer keys
        // https://sunaku.github.io/home-row-mods.html
        // https://github.com/urob/zmk-config#timeless-homerow-mods
        //
        // TYPING_STREAK_TERM defines how long you need to wait (milliseconds)
        // after typing before you can use home row mods again.  It prevents
        // unintended activation of home row mods when you're actively typing.
        //
        #define TYPING_STREAK_TERM 160 // global-quick-tap-ms
        //
        // KEY_REPEATING_TERM defines how much time you have left (milliseconds)
        // after tapping a key to hold it again in order to make it auto-repeat.
        //
        #define KEY_REPEATING_TERM 300 // "tap then hold" for key auto-repeat
        //
        // HOMEY_TAPPING_TERM defines how long you need to hold (milliseconds)
        // home row mod keys in order to send their modifiers to the computer
        // (i.e. "register" them) for mod-click mouse usage (e.g. Ctrl-Click).
        //
        // NOTE: The "balanced" flavor of ZMK hold-tap for home row mods already
        // provides instant modifier activation for keyboard-only usage, so this
        // setting is meant for combined keyboard/mouse usage such as mod-clicks.
        //
        #define HOMEY_TAPPING_TERM 280 // TAPPING_TERM + ALLOW_CROSSOVER_AFTER
        //
        // INDEX_TAPPING_TERM defines how long you need to hold (milliseconds)
        // index finger keys in order to send their modifiers to the computer
        // (i.e. "register" them) for mod-click mouse usage (e.g. Shift-Click).
        //
        // NOTE: The "tap-preferred" flavor of ZMK hold-tap for index finger keys
        // allows faster activation of the Shift modifier (without having to wait
        // for the modified key to be released as the "balanced" flavor requires).
        // Typing streaks and the `hold-trigger-on-release` setting are disabled
        // for the index fingers so as not to hinder their speed and dexterity.
        //
        // CAUTION: You'll need to perform inward rolls from pinky->ring->middle
        // fingers toward the index fingers when activating multiple modifiers
        // because `hold-trigger-on-release` is disabled for the index fingers.
        // Otherwise, you may be surprised that the index fingers' modifier is
        // sent immediately without the rest of your multi-mod chord when you
        // perform outward rolls from your index fingers toward your pinkies.
        //
        #define INDEX_TAPPING_TERM 180
        //
        // THUMB_TAPPING_TERM defines how long you need to hold (milliseconds)
        // a thumb key to activate a layer.  Shorter holds are treated as taps.
        //
        #define THUMB_TAPPING_TERM 200
        //
        //
        // |------------------------|------------------------|
        // | LEFT_HAND_KEYS         |        RIGHT_HAND_KEYS |
        // |                        |                        |
        // |    0  1  2  3  4       |       5  6  7  8  9    |
        // |   10 11 12 13 14       |      15 16 17 18 19    |
        // |   20 21 22 23 24       |      25 26 27 28 29    |
        // |            32 33 34    |   35 36 37             |
        // |------------------------|------------------------|
        //
        #define LEFT_HAND_KEYS      \
              0  1  2  3  4         \
             10 11 12 13 14         \
             20 21 22 23 24
        #define RIGHT_HAND_KEYS     \
                                               5  6  7  8  9    \
                                              15 16 17 18 19    \
                                              25 26 27 28 29
        #define THUMB_KEYS          \
                       32 33 34          35 36 37
        //
        // Home row mod-tap keys for all except index fingers
        //
        homey_left: miryoku_home_row_mods_left_hand {
            compatible = "zmk,behavior-hold-tap";
            label = "HOME_ROW_MODS_LEFT_HAND";
            flavor = "balanced";
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
            flavor = "balanced";
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
            flavor = "tap-preferred";
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
            flavor = "tap-preferred";
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
            flavor = "balanced";
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
&kp W,             &kp W,             &kp F,             &kp P,             &kp B,             &kp J,             &kp L,             &kp U,             &kp Y,             &kp SQT,           \
HMY_L(LGUI, A),     HMY_L(LALT, R),     HMY_L(LCTRL, S),    IND_L(LSHFT, T),    &kp G,             &kp M,             IND_R(LSHFT, N),    HMY_R(LCTRL, E),    HMY_R(LALT, I),     HMY_R(LGUI, O),     \
U_LT(U_BUTTON, Z), U_MT(RALT, X),     &kp C,             &kp D,             &kp V,             &kp K,             &kp H,             &kp COMMA,         U_MT(RALT, DOT),   U_LT(U_BUTTON, SLASH),\
U_NP,              U_NP,              THMB(U_MEDIA, ESC),THMB(U_NAV, SPACE),THMB(U_MOUSE, TAB),THMB(U_SYM, RET),  THMB(U_NUM, BSPC), THMB(U_FUN, DEL),  U_NP,              U_NP


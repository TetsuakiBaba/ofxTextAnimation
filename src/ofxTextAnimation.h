#pragma once

#include "ofMain.h"

#define OFX_TEXT_ANIMATION_TYPE_OUTLINE 1001
#define OFX_TEXT_ANIMATION_TYPE_FADE 1002
#define OFX_TEXT_ANIMATION_TYPE_TYPING 1003



#define OFX_TEXT_ANIMATION_STATUS_IN 1
#define OFX_TEXT_ANIMATION_STATUS_SHOW 2
#define OFX_TEXT_ANIMATION_STATUS_OUT 3
#define OFX_TEXT_ANIMATION_STATUS_NONE 4

class ofxTextAnimation{
public:
    ofxTextAnimation();
    ~ofxTextAnimation();
    void loadFont(string _str_font, int _size);
    void setText(string _text);
    void setLoop(bool _loop_status);
    void setAnimate(int _type, int _ms_in, int _ms_show, int _ms_out);
    void play();
    int getTimeMillis();
    void draw(int _x, int _y);
    void setColor(ofColor _color);
    
private:
    bool loop_status;
    string text;
    ofTrueTypeFont font;
    int type_animation;
    int ms_in;
    int ms_out;
    int ms_show;
    int status;
    unsigned long time_begin;
    ofColor color;
    int x;
    int y;
    float noise_x[1024];
    float noise_y[1024];
};

#include "ofxTextAnimation.h"

ofxTextAnimation::ofxTextAnimation()
{
    loop_status = true;
    type_animation = OFX_TEXT_ANIMATION_TYPE_FADE;
    status = OFX_TEXT_ANIMATION_STATUS_NONE;
    color = ofColor::white;
    
    for( int i = 0; i < 1024; i++ ){
        noise_x[i] = 0.0;
        noise_y[i] = 0.0;
    }
}


ofxTextAnimation::~ofxTextAnimation()
{
    
}

void ofxTextAnimation::setColor(ofColor _color)
{
    color = _color;
}
void ofxTextAnimation::loadFont(string _str_font, int _size)
{
    font.load(_str_font, _size, true, true, true);
}

void ofxTextAnimation::setLoop(bool _loop_status)
{
    loop_status = _loop_status;
}

void ofxTextAnimation::setAnimate(int _type, int _ms_in, int _ms_show, int _ms_out)
{
    type_animation = _type;
    ms_in = _ms_in;
    ms_show = _ms_show;
    ms_out = _ms_out;
}

void ofxTextAnimation::draw(int _x, int _y)
{
    switch( type_animation )
    {
        case OFX_TEXT_ANIMATION_TYPE_FADE:
            switch( status ){
                case OFX_TEXT_ANIMATION_STATUS_IN:

                    if( (ofGetElapsedTimeMillis()-time_begin) > ms_in ){
                        status = OFX_TEXT_ANIMATION_STATUS_SHOW;
                        ofSetColor(color, 255);
                        font.drawString(text, _x, _y);
                    }
                    else{
                        ofSetColor(color, 255*((ofGetElapsedTimeMillis()-time_begin)/(float)ms_in));
                        font.drawString(text, _x, _y);
                    }
                    break;
                case OFX_TEXT_ANIMATION_STATUS_SHOW:

                    if( (ofGetElapsedTimeMillis()-time_begin) > ms_in+ms_show ){
                        status = OFX_TEXT_ANIMATION_STATUS_OUT;
                        ofSetColor(color, 255);
                        font.drawString(text, _x, _y);
                    }
                    else{
                        ofSetColor(color, 255);
                        font.drawString(text, _x, _y);
                    }
                    break;
                case OFX_TEXT_ANIMATION_STATUS_OUT:

                    if( (ofGetElapsedTimeMillis()-time_begin) > ms_in+ms_show+ms_out){
                        if( loop_status == true ){
                            status = OFX_TEXT_ANIMATION_STATUS_IN;
                            time_begin = ofGetElapsedTimeMillis();
                        }
                        else{
                            status = OFX_TEXT_ANIMATION_STATUS_NONE;
                        }
                        ofSetColor(color, 0);
                        font.drawString(text, _x, _y);
                    }
                    else{
                        ofSetColor(color, 255-255*((ofGetElapsedTimeMillis()-(time_begin+ms_in+ms_show))/(float)(ms_out)));
                        font.drawString(text, _x, _y);
                    }
                    break;
                case OFX_TEXT_ANIMATION_STATUS_NONE:
                    time_begin = ofGetElapsedTimeMillis();
                    break;
            }
            break;
        case OFX_TEXT_ANIMATION_TYPE_OUTLINE:
            switch( status ){
                case OFX_TEXT_ANIMATION_STATUS_IN:
                    
                    if( (ofGetElapsedTimeMillis()-time_begin) > ms_in ){
                        status = OFX_TEXT_ANIMATION_STATUS_SHOW;
                        ofSetColor(color, 255);
                        font.drawString(text, _x, _y);
                    }
                    else{
                        int all_point = 0;
                        vector<ofTTFCharacter>paths = font.getStringAsPoints(text);
                        for( int i = 0; i < paths.size(); i++ ){
                            all_point = all_point + 50*paths[i].getOutline().size();
                        }
                        ofSetColor(color, 255);
                        int count = 0;
                        int count_stop = all_point*(ofGetElapsedTimeMillis()-time_begin)/(float)(ms_in);
                        ofSetColor(color, 255);
                        ofNoFill();
                        ofSetLineWidth(1.0);
                        for(int i = 0; i < paths.size(); i++ ){
                            vector<ofPolyline>p = paths[i].getOutline();
                            for( int j = 0; j < p.size(); j++ ){
                                p[j] = p[j].getResampledByCount(50);
                                ofBeginShape();
                                for( int k = 0; k < p[j].size(); k++ ){
                                    ofVertex(p[j][k].x+_x, p[j][k].y+_y);
                                    count++;
                                    if( count > count_stop ){
                                        k = p[j].size();
                                    }
                                }
                                ofEndShape();
                                if( count > count_stop ){
                                    j = p.size();
                                }
                            }
                            if( count > count_stop ){
                                i = paths.size();
                            }
                        }
                    }
                    break;
                case OFX_TEXT_ANIMATION_STATUS_SHOW:
                    
                    if( (ofGetElapsedTimeMillis()-time_begin) > ms_in+ms_show ){
                        status = OFX_TEXT_ANIMATION_STATUS_OUT;
                        ofSetColor(color, 255);
                        font.drawString(text, _x, _y);
                    }
                    else{
                        ofSetColor(color, 255);
                        font.drawString(text, _x, _y);
                    }
                    break;
                case OFX_TEXT_ANIMATION_STATUS_OUT:
                    
                    if( (ofGetElapsedTimeMillis()-time_begin) > ms_in+ms_show+ms_out){
                        if( loop_status == true ){
                            status = OFX_TEXT_ANIMATION_STATUS_IN;
                            time_begin = ofGetElapsedTimeMillis();
                        }
                        else{
                            status = OFX_TEXT_ANIMATION_STATUS_NONE;
                        }
                        ofSetColor(color, 0);
                        font.drawString(text, _x, _y);
                    }
                    else{
                        int all_point = 0;
                        vector<ofTTFCharacter>paths = font.getStringAsPoints(text);
                        for( int i = 0; i < paths.size(); i++ ){
                            all_point = all_point + 50*paths[i].getOutline().size();
                        }
                        ofSetColor(color, 255);
                        int count = 0;
                        int count_stop = all_point-all_point*(ofGetElapsedTimeMillis()-(time_begin+ms_show+ms_out))/(float)(ms_out);
                        ofSetColor(color, 255);
                        ofNoFill();
                        ofSetLineWidth(1.0);
                        for(int i = 0; i < paths.size(); i++ ){
                            vector<ofPolyline>p = paths[i].getOutline();
                            for( int j = 0; j < p.size(); j++ ){
                                p[j] = p[j].getResampledByCount(50);
                                ofBeginShape();
                                for( int k = 0; k < p[j].size(); k++ ){
                                    ofVertex(p[j][k].x+_x, p[j][k].y+_y);
                                    count++;
                                    if( count > count_stop ){
                                        k = p[j].size();
                                    }
                                }
                                ofEndShape();
                                if( count > count_stop ){
                                    j = p.size();
                                }
                            }
                            if( count > count_stop ){
                                i = paths.size();
                            }
                        }
                    }
                    break;
                case OFX_TEXT_ANIMATION_STATUS_NONE:
                    time_begin = ofGetElapsedTimeMillis();
                    break;
            }
            break;
            
        case OFX_TEXT_ANIMATION_TYPE_TYPING:
            switch( status ){
                case OFX_TEXT_ANIMATION_STATUS_IN:
                    
                    if( (ofGetElapsedTimeMillis()-time_begin) > ms_in ){
                        status = OFX_TEXT_ANIMATION_STATUS_SHOW;
                        ofSetColor(color, 255);
                        font.drawString(text, _x, _y);
                    }
                    else{
                        ofSetColor(color, 255);
                        int count = text.length()*(ofGetElapsedTimeMillis()-time_begin)/(float)ms_in;
                        font.drawString(text.substr(0,count), _x, _y);
                    }
                    break;
                case OFX_TEXT_ANIMATION_STATUS_SHOW:
                    
                    if( (ofGetElapsedTimeMillis()-time_begin) > ms_in+ms_show ){
                        status = OFX_TEXT_ANIMATION_STATUS_OUT;
                        ofSetColor(color, 255);
                        font.drawString(text, _x, _y);
                    }
                    else{
                        ofSetColor(color, 255);
                        font.drawString(text, _x, _y);
                    }
                    break;
                case OFX_TEXT_ANIMATION_STATUS_OUT:
                    
                    if( (ofGetElapsedTimeMillis()-time_begin) > ms_in+ms_show+ms_out){
                        if( loop_status == true ){
                            status = OFX_TEXT_ANIMATION_STATUS_IN;
                            time_begin = ofGetElapsedTimeMillis();
                        }
                        else{
                            status = OFX_TEXT_ANIMATION_STATUS_NONE;
                        }
                        ofSetColor(color, 0);
                        font.drawString(text, _x, _y);
                    }
                    else{
                        int count = text.length()-text.length()*(ofGetElapsedTimeMillis()-(time_begin+ms_in+ms_show))/(float)ms_out;
                        font.drawString(text.substr(0,count), _x, _y);
                    }
                    break;
                case OFX_TEXT_ANIMATION_STATUS_NONE:
                    time_begin = ofGetElapsedTimeMillis();
                    break;
            }
            break;

              
    }
}

void ofxTextAnimation::setText(string _text)
{
    text = _text;
}

void ofxTextAnimation::play()
{
    status = OFX_TEXT_ANIMATION_STATUS_IN;
    time_begin = ofGetElapsedTimeMillis();
}

int ofxTextAnimation::getTimeMillis()
{
    return ofGetElapsedTimeMillis()-time_begin;
}

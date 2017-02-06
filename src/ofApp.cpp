#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    shader[0].load("shaders/glow");
    shader[1].load("shaders/cloud");
    shader[2].load("shaders/voronoise");
    
    ofDisableArbTex();
    ofLoadImage(masks[0],"masks/01.png");
    ofLoadImage(masks[1],"masks/02.png");
    ofLoadImage(masks[2],"masks/03.png");
    ofEnableArbTex();
    
    fbo.allocate(masks[0].getWidth(),masks[0].getHeight(),GL_RGBA);
    
    ofParameterGroup g;
    g.add(u_01.set("u_01",0.,0.,10.));
    g.add(u_02.set("u_02",0.,0.,10.));
    g.add(u_03.set("u_03",0.,0.,10.));
    g.add(u_04.set("u_04",0.,0.,10.));
    g.add(u_color.set("u_color",ofColor(255,255,255),ofColor(0,0,0),ofColor(255,255,255)));
    
    gui.setup(g);
    
    gui.loadFromFile("settings.h");
    bools.resize(3);
}

//--------------------------------------------------------------
void ofApp::update(){

    float now = ofGetElapsedTimef();
    ofSetWindowTitle(ofToString(ofGetFrameRate(),1));
    fbo.begin();
    ofClear(0);
    ofBackground(0);
    for(int i = 0 ;i<3;i++){
        
        if(bools[i]){
            shader[i].begin();
            shader[i].setUniformTexture("mask",masks[i],1);
            shader[i].setUniform1f("iGlobalTime", now);
            shader[i].setUniform2f("iResolution", fbo.getWidth(),fbo.getHeight());
            
            shader[i].setUniform1f("u_01", u_01);
            shader[i].setUniform1f("u_02", u_02);
            shader[i].setUniform1f("u_03", u_03);
            shader[i].setUniform1f("u_04", u_04);
            shader[i].setUniform3f("u_color", ofVec3f(u_color->r/255.0f,u_color->g/255.0f,u_color->b/255.0f));
            masks[i].draw(0, 0);
            shader[i].end();
        }
    }
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.draw(0, 0, fbo.getWidth()/2,fbo.getHeight()/2);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key - '0' < 3)bools[key-'0']=!bools[key-'0'];
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

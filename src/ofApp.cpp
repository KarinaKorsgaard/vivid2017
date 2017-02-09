#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // load shaders
    shader[0].load("shaders/glow");
    shader[1].load("shaders/cloud");
    shader[2].load("shaders/voronoise");
    
    // load masks as textures
    ofDisableArbTex();
    ofLoadImage(masks[0],"masks/01.png");
    ofLoadImage(masks[1],"masks/02.png");
    ofLoadImage(masks[2],"masks/03.png");
    ofEnableArbTex();
    
    //allocate framebuffer
    fbo.allocate(masks[0].getWidth(),masks[0].getHeight(),GL_RGBA);
    
    
    // set up gui
    global.setName("gui");
    glow.setName("glow");
    glow.add(u_density.set("u_density",0.,0.,10.));
    glow.add(u_color1.set("u_color",ofColor(255,255,255),ofColor(0,0,0),ofColor(255,255,255)));

    cloud.setName("cloud");
    cloud.add(u_balance.set("u_balance",0.,0.,1.));
    cloud.add(u_contrast.set("u_contrast",0.,0.,10.));
    cloud.add(u_zoom.set("u_zoom",0.,0.,100.));
    cloud.add(u_color2.set("u_color",ofColor(255,255,255),ofColor(0,0,0),ofColor(255,255,255)));

    voro.setName("voronoise");
    voro.add(u_size.set("u_size",0.,10.,0.));
    voro.add(u_smooth.set("u_smooth",0.,0.,1.));
    voro.add(u_color3.set("u_color",ofColor(255,255,255),ofColor(0,0,0),ofColor(255,255,255)));
    
    global.add(glow);
    global.add(cloud);
    global.add(voro);
    
    gui.setup(global);

    gui.loadFromFile("settings.xml");

    // make vector of booleans for showing and hiding grids
    bools.resize(3);
}

//--------------------------------------------------------------
void ofApp::update(){

    // set window title to keep track of framerate
    ofSetWindowTitle(ofToString(ofGetFrameRate(),1));
    
    float now = ofGetElapsedTimef();
    
    // draw shaders to framebuffer
    fbo.begin();
    ofClear(0);
    ofBackground(0);
    
    for(int i = 0 ;i<3;i++){
        
        if(bools[i]){
            shader[i].begin();
            shader[i].setUniformTexture("mask",masks[i],1);
            shader[i].setUniform1f("iGlobalTime", now);
            shader[i].setUniform2f("iResolution", fbo.getWidth(),fbo.getHeight());
            
            ofColor c;
            if(i==0){
                shader[i].setUniform1f("u_density", u_density);
                c=u_color1;
            }
            if(i==1){
                shader[i].setUniform1f("u_balance", u_balance);
                shader[i].setUniform1f("u_contrast", u_contrast);
                shader[i].setUniform1f("u_zoom", u_zoom);
                c=u_color2;
            }
            if(i==2){
                shader[i].setUniform1f("u_size", u_size);
                shader[i].setUniform1f("u_smooth", u_smooth);
                c=u_color3;
            }
            
            shader[i].setUniform3f("u_color", ofVec3f(c.r/255.0f,c.g/255.0f,c.b/255.0f));
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

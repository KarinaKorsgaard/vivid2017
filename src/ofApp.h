#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAutoReloadedShader.h"
#include "ofxDmx.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofxPanel gui;
    ofParameter<float>u_size,u_smooth;
    ofParameter<float>u_density;
    ofParameter<float>u_balance,u_contrast,u_zoom;
     ofParameterGroup voro,cloud,glow,global;
    
    ofParameter<ofColor>u_color1,u_color2,u_color3;
    vector<bool>bools;
    
    
    ofFbo fbo;
    
    map<int,ofTexture>masks;
    map<int,ofxAutoReloadedShader>shader;
    
};

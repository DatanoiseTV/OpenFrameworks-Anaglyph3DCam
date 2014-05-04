#include "ofApp.h"

#define STRINGIFY(A) #A

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    int camWidth 		= 640;	// try to grab at this size.
	int camHeight 		= 480;
    
    // Grab Image from "Left" Camera
    vidGrabber1.setVerbose(true);
    vidGrabber1.setDeviceID(2); // <- Change your ID
    vidGrabber1.setDesiredFrameRate(24);
    vidGrabber1.initGrabber(camWidth,camHeight);
    
    
    // Grab Image from "Right" Camera
    vidGrabber2.setVerbose(true);
    vidGrabber2.setDeviceID(1); // <- Change your ID
    vidGrabber2.setDesiredFrameRate(24);
    vidGrabber2.initGrabber(camWidth, camHeight);
    
    // Allocate Framebuffer
    fbo.allocate(camWidth,camHeight);
    
    string shaderProgram = STRINGIFY(
                                     uniform sampler2DRect tex0;
                                     uniform sampler2DRect tex1;


                                     void main (void){
                                         vec2 pos = gl_TexCoord[0].st;
                                         
                                         vec4 left_Tex = texture2DRect(tex0, pos);
                                         vec4 right_Tex = texture2DRect(tex1, pos);

                                         
                                         vec4 color_l = vec4(1.0, left_Tex.g, left_Tex.b, 1.0);
                                         vec4 color_r = vec4(right_Tex.r, 1.0, 1.0, 1.0);
                                         
                                         vec4 anaglyph_output = vec4(color_l.rgb * color_r.rgb, 1.0);

                                         gl_FragColor =  anaglyph_output;
                                     }
    );
    
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader.linkProgram();
   
    // Clean Framebuffer to get rid of junk.
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber1.update();
    vidGrabber2.update();

    fbo.begin();
    ofClear(0, 0, 0,255);
    shader.begin();
    
    // Pass the video texture
    shader.setUniformTexture("tex0", vidGrabber1.getTextureReference() , 1 );
    shader.setUniformTexture("tex1", vidGrabber2.getTextureReference() , 2 );

    fbo.draw(0,0);
    shader.end();
    fbo.end();

    ofSetWindowTitle( ofToString( ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::gray);
    fbo.draw(0,0,1024,768);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key)
    {
        case 'q':
            exitApp();
            break;
    }
    
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

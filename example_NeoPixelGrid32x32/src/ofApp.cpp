#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    effect = 0;
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);
    grid32x32.setupLedGrid();
    
    // Load the dot image
    dot.loadImage("dot.png");
}
//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("ofxOPC:NeoPixelGrid32x32: FPS: " +ofToString((int)(ofGetFrameRate())));
    grid32x32.grabImageData(ofPoint(ofGetWidth()/2-115,ofGetHeight()/2-115));
    
    grid32x32.update();
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected())
    {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else
    {
        // Write out the first set of data
//        opcClient.writeChannel(1, grid32x32.colorData());
    }
    
    opcClient.update();
}
//--------------------------------------------------------------
void ofApp::draw()
{
    //Should be black otherwise the addon grabs the background pixels
    ofBackground(0);
    
    // As it says
    drawEffects(effect);
    
    // Visual Representation of the Grab Area
    grid32x32.drawGrabRegion(hide);
    
    grid32x32.drawGrid(120, 120);
    
    // Report Messages
    ofDrawBitmapStringHighlight("Output", 1,240);
    ofDrawBitmapStringHighlight("Input Area", ofGetWidth()/2-35,ofGetHeight()/2+120);
    ofDrawBitmapStringHighlight("Press Left and Right to Change Effect Mode", 5,ofGetHeight()-15);
    ofDrawBitmapStringHighlight("Is the Client Connected: " + ofToString(opcClient.isConnected()), 5,ofGetHeight()-30);
}
//--------------------------------------------------------------
void ofApp::exit()
{
    // Close Connection
    opcClient.close();
}
//--------------------------------------------------------------
void ofApp::drawEffects(int mode)
{
    switch (mode) {
        case 0:
        {
            // Mouse Circle
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofRect(mouseX,mouseY,320,320);
            ofPopStyle();
        }
            break;
            
        case 1:
        {
            // Like the processing example draw dot images and rotate
            int size = 180;
            ofPushMatrix();
            ofTranslate(0, 0);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
            ofRotateZ(ofGetElapsedTimeMillis()/10);
            ofPushMatrix();
            ofTranslate(-size,-size);
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofSetColor(0, 255,20);
            dot.draw(size/4, size/4, size,size);
            ofSetColor(255, 0,20);
            dot.draw((size/4*3), size/4, size,size);
            ofSetColor(0, 0,255);
            dot.draw(size/4, (size/4*3), size,size);
            ofSetColor(255, 0,255);
            dot.draw((size/4*3),(size/4*3), size,size);
            ofDisableBlendMode();
            ofPopMatrix();
            ofPopMatrix();
            ofPopMatrix();
        }
            break;
            
        case 2:
        {
            // Changes the color of a Circle
            ofPushStyle();
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofCircle(ofGetWidth()/2,ofGetHeight()/2,50);
            ofPopStyle();
        }
            break;
            
        case 3:
        {
            // Fade to full brightness then to zero
            ofPushStyle();
            ofSetColor((int)(128 + 128 * sin(ofGetElapsedTimef())));
            ofCircle(ofGetWidth()/2,ofGetHeight()/2,50);
            ofPopStyle();
        }
            break;
            
        case 4:
        {
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            float rotationAmount = ofGetElapsedTimeMillis()/10;
            ofSetColor(255, 0, 0);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            ofCircle(ofGetWidth()/2, ofGetHeight()/2-50, 50);
            ofPopMatrix();
            ofPopMatrix();
            ofSetColor(0, 0, 255);
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotateZ(-rotationAmount);
            ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            ofCircle(ofGetWidth()/2, ofGetHeight()/2+50, 50);
            ofPopMatrix();
            ofPopMatrix();
            ofDisableBlendMode();
        }
            break;
            
        case 5:
        {
            ofPushStyle();
            
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            float hue = fmodf(ofGetElapsedTimef()*10,255);
            ofColor c = ofColor::fromHsb(hue, 255, 255);
            ofSetColor(c);
            ofCircle(ofGetWidth()/2+5+(int)(250 * sin(ofGetElapsedTimef()*3)),ofGetHeight()/2,90);
            float hue1 = fmodf(ofGetElapsedTimef()*5,255);
            ofColor c1 = ofColor::fromHsb(hue1, 255, 255);
            ofSetColor(c1);
            ofCircle(ofGetWidth()/2+5+(int)(250 * sin(ofGetElapsedTimef()*2)),ofGetHeight()/2,90);
            ofDisableBlendMode();
            ofPopStyle();
        }
            break;
        default:
            break;
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == OF_KEY_LEFT)
    {
        effect--;
    }
    if (key == OF_KEY_RIGHT)
    {
        effect++;
    }
    // Retry Connecting to Server
    if (key == ' ')
    {
        opcClient.retryConnecting();
    }
    if (key == ' ')
    {
        hide = !hide;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    
}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
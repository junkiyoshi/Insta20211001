#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetCircleResolution(60);

	this->box2d.init();
	this->box2d.setGravity(0, 50);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->circle_list.size() - 1; i > -1; i--) {

		this->life_list[i] -= 1;

		if (this->life_list[i] < 0) {

			this->circle_list.erase(this->circle_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	for (int i = 0; i < 2; i++) {

		int deg = ofMap(ofNoise(ofGetFrameNum() * 0.01), 0, 1, 0, 720) + i * 180;
		auto location = glm::vec2(ofGetWidth() * 0.5 + 150 * cos(deg * DEG_TO_RAD), 200 + 150 * sin(deg * DEG_TO_RAD));
		auto radius = 10;
		auto circle = make_shared<ofxBox2dCircle>();
		circle->setPhysics(0.5, 0.03, 0.1);
		circle->setup(this->box2d.getWorld(), location.x, location.y, radius);
		this->circle_list.push_back(circle);
		this->radius_list.push_back(radius);
		this->life_list.push_back(200);

		ofColor color;
		color.setHsb((ofGetFrameNum() + i * 128) % 255, 130, 255);
		this->color_list.push_back(color);
	}

	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofTranslate(ofGetWidth() * -0.5, ofGetHeight() * -0.5);

	ofDrawCircle(glm::vec2(ofGetWidth() * 0.5, 200), 140);
	ofDrawCircle(glm::vec2(ofGetWidth() * 0.5, 200), 160);

	ofSetLineWidth(1);
	for (int i = 0; i < this->circle_list.size(); i++) {

		ofFill();
		ofSetColor(this->color_list[i]);
		ofDrawCircle(glm::vec2(this->circle_list[i]->getPosition()), this->radius_list[i]);

		ofNoFill();
		ofSetColor(39);
		ofDrawCircle(glm::vec2(this->circle_list[i]->getPosition()), this->radius_list[i]);

	}

	ofSetLineWidth(3);
	ofSetColor(39);
	ofDrawRectangle(0, 0, 720, 720);

	this->cam.end();
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
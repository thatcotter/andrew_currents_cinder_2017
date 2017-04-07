#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/Font.h"
#include "cinder/Rand.h"

#include "poScene.h"
#include "poShape.h"

#include "Button.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class poScen_UIApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    void onButtonStateChange(bool state);
    
    std::vector<ci::Color> palettes;
    std::vector<ButtonRef> buttons;
    
    po::scene::SceneRef mScene;
    po::scene::NodeContainerRef mNodeContainer;
    po::scene::ShapeRef mBackgroundShape;
    po::scene::ShapeRef whiteRect;
    
};

void poScen_UIApp::setup()
{
    setWindowSize(450, 600);
    
    mNodeContainer = po::scene::NodeContainer::create();
    mScene = po::scene::Scene::create(mNodeContainer);
    
    whiteRect = po::scene::Shape::createRect( getWindowWidth(), getWindowHeight()*0.33f);
    mNodeContainer->addChild(whiteRect);
    
    po::scene::ShapeRef buttonBG = po::scene::Shape::createRect(getWindowWidth(), getWindowHeight()*0.67f);
    buttonBG->setPosition( vec2( 0, getWindowHeight()*0.33f ) );
    buttonBG->setFillColor(ci::Color( 0.2f, 0.2f, 0.2f ));
    mNodeContainer->addChild(buttonBG);
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            Color tempColor = Color( ci::randFloat(), ci::randFloat(), ci::randFloat() );
            palettes.push_back(tempColor);
            
            ButtonRef temp = Button::create(vec2( (getWindowWidth()*0.25)*(i+0.1), (getWindowHeight()*0.4) + (j * getWindowWidth()*0.25f)), getWindowWidth()*0.1f, tempColor);
//            if( i == 0 && j == 0)
//            {
                temp->getButtonStateChangeSignal().connect(std::bind(&::poScen_UIApp::onButtonStateChange, this, std::placeholders::_1));
//            }
            buttons.push_back(temp);
            mNodeContainer->addChild(temp);
            
        }
    }
    
}

void poScen_UIApp::mouseDown( MouseEvent event )
{
}

void poScen_UIApp::onButtonStateChange(bool state)
{
    if(state){
//        ci::app::timeline().apply(&whiteRect->getFillColorAnim(), Color(0.f,0.f,0.f), 0.5f, ci::EaseOutExpo());
        for (int i = 0; i < buttons.size(); i++) {
            if (buttons[i]->getIsActivated()) {
                std::cout << buttons[i]->getColor() << std::endl;
                ci::app::timeline().apply(&whiteRect->getFillColorAnim(), buttons[i]->getColor(), 1.5f, ci::EaseOutExpo());
            }
            buttons[i]->inActivation();
        }
//        cout << "CLICK!" << endl;
    }else{
//        ci::app::timeline().apply(&mBackgroundShape->getFillColorAnim(), ci::Color(0,0,255), 0.5f, ci::EaseOutExpo());
    }
}

void poScen_UIApp::update()
{
    mScene->update();
}

void poScen_UIApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    mScene->draw();
}

CINDER_APP( poScen_UIApp, RendererGl(RendererGl::Options().msaa( 8 )) )

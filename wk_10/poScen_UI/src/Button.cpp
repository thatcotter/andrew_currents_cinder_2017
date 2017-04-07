//
//  Button.cpp
//  poScen_UI
//
//  Created by Andrew Cotter on 4/5/17.
//
//

#include "Button.hpp"

ButtonRef Button::create(ci::vec2 position, float radius, ci::Color btnColor)
{
    ButtonRef ref = std::shared_ptr<Button>( new Button());
    ref->setup( position, radius, btnColor);
    return ref;
}

Button::Button()
    :mColor(0.f, 0.f, 0.f),
    mRadius(0.f),
    mIsActivated(false)
{
}

void Button::setup(ci::vec2 position,float radius, ci::Color btnColor)
{
    mPosition = position;
    mRadius = radius;
    mColor = btnColor;
    mAnimationTime = 0.5f;
    
    this->addButtonCircle();
    
    //	Connect to mouse events
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Button::onMouseEvent, this, std::placeholders::_1));
    getSignal(po::scene::MouseEvent::UP_INSIDE).connect(std::bind(&Button::onMouseEvent, this, std::placeholders::_1));
    getSignal(po::scene::MouseEvent::UP).connect(std::bind(&Button::onMouseEvent, this, std::placeholders::_1));
}

void Button::addButtonCircle()
{
    mButtonCircle = po::scene::Shape::createCircle(mRadius * 2.f);
    mButtonCircle->setFillColor(mColor);
    mButtonCircle->setPosition(mPosition);
    
    this->addChild(mButtonCircle);
}

void Button::onMouseEvent(po::scene::MouseEvent &event)
{
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            mIsActivated = !mIsActivated;
            if (mIsActivated){
                
                mButtonStateChangeSignal.emit(true);
                std::cout << "Button Pressed!" << std::endl;
                
            }else{
                
                mButtonStateChangeSignal.emit(false);
                
            }
            break;
            
        case po::scene::MouseEvent::UP_INSIDE:
            mButtonStateChangeSignal.emit(false);
            break;
            
        case po::scene::MouseEvent::UP:
            mButtonStateChangeSignal.emit(false);
            break;
        default:
            break;
    }
}

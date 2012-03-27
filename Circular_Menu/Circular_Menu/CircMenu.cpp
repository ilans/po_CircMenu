#include "CircMenu.h"

const double PI = 3.141592;

CircMenu::CircMenu()
{
	amp			= 250.f;
	
	rangeBegin	= 0;
	rangeEnd	= 360;
	
	openDuration	= .45f;
	openDelay		= .1f;
	closeDuration	= .35f;
	closeDelay		= .1f;
	
	isOpen		= false;
	isPressed	= false;
	
	menuButton = new CircButton();
	menuButton->setBaseTexture(poGetTexture("buttons/Path_Icon_base.png"));
	menuButton->setIconTexture(poGetTexture("buttons/Path_Icon_icon.png"));
	menuButton->setHighlightTexture(poGetTexture("buttons/Path_Icon_highlight.png"));
	addChild(menuButton);
	
	addEvent(PO_MOUSE_DOWN_INSIDE_EVENT,this);
	addEvent(PO_MOUSE_MOVE_EVENT,this);
	addEvent(PO_MOUSE_UP_EVENT, this);

}

CircMenu::~CircMenu() 
{
}

void CircMenu::update() 
{
}

void CircMenu::addButton()
{
	CircButton *button = new CircButton(100);
	button->setBaseTexture(poGetTexture("buttons/Path_Icon_sm_base.png"));
	button->setIconTexture(poGetTexture("buttons/Path_Icon_sm_icon.png"));
	button->setHighlightTexture(poGetTexture("buttons/Path_Icon_sm_highlight.png"));
	buttons.push_back(button);
	addChild(buttons.back());
	moveChildToBack(buttons.back());
}

void CircMenu::setRange(int start, int end)
{
	rangeBegin = start;
	rangeEnd = end;
}

void CircMenu::setRange(CircMenuRange r)
{
	switch(r){
		case CIRC_MENU_QUART_TOP_LEFT:				setRange(180,270);		break;
		case CIRC_MENU_QUART_TOP_RIGHT:				setRange(270,360);		break;
		case CIRC_MENU_QUART_BOTTOM_LEFT:			setRange(90,180);		break;
		case CIRC_MENU_QUART_BOTTOM_RIGHT:			setRange(0,90);			break;
		case CIRC_MENU_HALF_TOP:					setRange(180,360);		break;
		case CIRC_MENU_HALF_BOTTOM:					setRange(0,180);		break;
		case CIRC_MENU_HALF_LEFT:					setRange(90,270);		break;
		case CIRC_MENU_HALF_RIGHT:					setRange(-90,90);		break;
		case CIRC_MENU_FULL:						setRange(0,360);		break;
	}
}

void CircMenu::open()
{
	if( buttons.size() > 0 )
	{
		for(int i=0; i<buttons.size(); i++){
			
			float theta = i * PI/180.f * (rangeEnd-rangeBegin)/(float)(buttons.size()-1);
			
			poPoint loc = poPoint(amp * cos(rangeBegin * PI/180.f + theta), amp * sin(rangeBegin * PI/180.f + theta), 0);
			
			buttons[i]->positionTween
				.set(loc)
				.setDelay(openDelay*i)
				.setDuration(openDuration)
				.setTweenFunction(PO_TWEEN_BACK_OUT_FUNC)
				.setExtraValues(3.f)
				.start();
			
			buttons[i]->icon->rotationTween
				.set(360)
				.setDelay(openDelay*i)
				.setDuration(openDuration)
				.setTweenFunction(PO_TWEEN_QUAD_INOUT_FUNC)
				.start();
		}
	}
	
	menuButton->icon->rotationTween
		.set(45)
		.setDelay(0)
		.setDuration(openDuration)
		.setTweenFunction(PO_TWEEN_QUAD_INOUT_FUNC)
		.start();
}

void CircMenu::close()
{
	if( buttons.size() > 0 )
	{
		for(int i=0; i<buttons.size(); i++){
						
			poPoint loc = poPoint( 0, 0, 0);
			
			buttons[i]->positionTween
				.set(loc)
				.setDelay(closeDelay*i)
				.setDuration(closeDuration)
				.setTweenFunction(PO_TWEEN_BACK_IN_FUNC)
				.start();
			
			buttons[i]->icon->rotationTween
				.set(0)
				.setDelay(closeDelay*i)
				.setDuration(closeDuration)
				.setTweenFunction(PO_TWEEN_QUAD_INOUT_FUNC)
				.start();
		}
	}
	
	menuButton->icon->rotationTween
		.set(0)
		.setDelay(0)
		.setDuration(closeDuration)
		.setTweenFunction(PO_TWEEN_QUAD_INOUT_FUNC)
		.start();
}

void CircMenu::eventHandler(poEvent *event)
{
	switch(event->type){
			
		case PO_MOUSE_DOWN_INSIDE_EVENT:
			isPressed = true;
			break;

		case PO_MOUSE_MOVE_EVENT:
			break;
			
		case PO_MOUSE_UP_EVENT:
			if(!isPressed) return;
			isOpen ? close() : open();
			isOpen = !isOpen;
			isPressed = false;
			break;
	}
}

void CircMenu::messageHandler(const std::string &msg, const poDictionary& dict) 
{
}
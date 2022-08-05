#include "Component.hpp"

// == CONSTRUCTOR/DESTRUCTOR ==
Component::Component() {}
Component::~Component() {}

// for component composition
void Component::initComponent() {}

// == MAIN FUNCTIONS ==
void Component::updateComponent(const float& dt) {}
void Component::renderComponent(sf::RenderTarget* targetWin) {}


#include "Component.hpp"

// == CONSTRUCTOR/DESTRUCTOR ==
VolE::Component::Component() {}
VolE::Component::~Component() {}

// for component composition
void VolE::Component::initComponent() {}

// == MAIN FUNCTIONS ==
void VolE::Component::updateComponent(const float& dt) {}
void VolE::Component::renderComponent(sf::RenderWindow& targetWin) {}


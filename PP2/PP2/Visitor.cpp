#include "Visitor.h"
#include "Entity.h"
#include "Player.h"
#include <string>
#include <iostream>

using namespace std;

void Visitor::Visit(Entity& E) {}

void Visitor::Visit(Player& P) {}

VisitorTalk::VisitorTalk(){
}

void VisitorTalk::Visit(Entity& E) {}

void VisitorTalk::Visit(Player& P) {
	cout << "\nI have found one of the rare items"<< endl;
}
/**
 * @file FishAngel.cpp
 * @author Bilal
 */


#include "pch.h"
#include "FishAngel.h"
#include "Aquarium.h"
#include <string>


using namespace std;

/// Fish Angel added on speed
/// in pixels per second
const double Speed = 900;

/// Fish filename
const wstring FishAngelImageName = L"images/angelfish.png";


/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishAngel::FishAngel(Aquarium *aquarium) : Fish(aquarium, FishAngelImageName)
{

    SetSpeed(GetSpeedX()+Speed, GetSpeedY()+Speed);

}


/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishAngel::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);
    itemNode->AddAttribute(L"type", L"angel");
    return itemNode;
}
/**
 * @file FishNemo.cpp
 * @author Bilal
 */

#include "pch.h"
#include "FishNemo.h"
#include "Aquarium.h"
#include <string>



using namespace std;

/// Fish Nemo speed multiplyer
/// in pixels per second
const double Speed = 10;

/// Fish filename
const wstring FishNemoImageName = L"images/nemo.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishNemo::FishNemo(Aquarium *aquarium) : Fish(aquarium,FishNemoImageName)
{
    SetSpeed(GetSpeedX()*Speed, GetSpeedY()*Speed);
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishNemo::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);
    itemNode->AddAttribute(L"type", L"nemo");
    return itemNode;
}


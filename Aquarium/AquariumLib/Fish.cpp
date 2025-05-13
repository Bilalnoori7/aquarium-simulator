/**
 * @file Fish.cpp
 * @author Bilal
 */

#include "pch.h"
#include "Fish.h"
#include <random>
#include "Aquarium.h"

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 20;

/// Maximum speed in the Y direction in
/// in pixels per second
const double MaxSpeedY = 50;

/// Minimum speed in the Y direction in
/// pixels per second
const double MinSpeedY = 20;

/// The  X edge threshold distance in pixels
const double XEdgeThreshold = 10;

/// The Y edge threshold distance in pixels
const double YEdgeThreshold = 30;

/**
 * Constructor
 * @param aquarium The aquarium we are in
 * @param filename Filename for the image we use
 */
Fish::Fish(Aquarium *aquarium, const std::wstring &filename) :
    Item(aquarium, filename)
{
    std::uniform_real_distribution<> distributionX(MinSpeedX, MaxSpeedX);
    std::uniform_real_distribution<> distributionY(MinSpeedY, MaxSpeedY);
    mSpeedX = distributionX(aquarium->GetRandom());
    mSpeedY =  distributionY(aquarium->GetRandom());

}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Fish::Update(double elapsed)
{
    SetLocation(GetX() + mSpeedX * elapsed,
            GetY() + mSpeedY * elapsed);

    double fishWidth= GetWidth();

    double fishHeight = GetHeight();

    int aquariumWidth = GetAquarium()->GetWidth();

    int aquariumHeight = GetAquarium()->GetHeight();



    if (mSpeedX > 0 && GetX() + fishWidth/2 >= aquariumWidth - XEdgeThreshold)
    {
        mSpeedX = -mSpeedX;
        SetMirror(true);
    }
    else if (mSpeedX < 0 && GetX() - fishWidth/2 <= XEdgeThreshold)
    {
        mSpeedX = -mSpeedX;
        SetMirror(false);

    }

    if (mSpeedY > 0 && GetY() + fishHeight/2 >= aquariumHeight - YEdgeThreshold)
    {
        mSpeedY = -mSpeedY;
    }

    else if (mSpeedY < 0 && GetY() - fishHeight/2 <= YEdgeThreshold)
    {
        mSpeedY = -mSpeedY;

    }

    
}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* Fish::XmlSave(wxXmlNode* node)
{
    auto itemNode= Item::XmlSave(node);

    itemNode->AddAttribute(L"speedX", wxString::FromDouble(mSpeedX));
    itemNode->AddAttribute(L"speedY", wxString::FromDouble(mSpeedY));

    return itemNode;
}


/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Fish::XmlLoad(wxXmlNode* node)
{

    Item::XmlLoad(node);

    node->GetAttribute(L"speedX", L"0").ToDouble(&mSpeedX);
    node->GetAttribute(L"speedY", L"0").ToDouble(&mSpeedY);

    SetMirror(mSpeedX < 0);
}
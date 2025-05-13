/**
 * @file Fish.h
 * @author Bilal
 *
 *
 */
 
#ifndef FISH_H
#define FISH_H

#include "Item.h"


/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class Fish : public Item
{

protected:

    Fish(Aquarium* aquarium, const std::wstring& filename);

private:

    /// Fish speed in the X direction
    /// in pixels per second
    double mSpeedX;

    /// Fish speed in the Y direction
    /// in pixels per second
    double mSpeedY;

public:

    /// Default constructor (disabled)
    Fish() = delete;

    /// Copy constructor (disabled)
    Fish(const Fish &) = delete;

    /// Assignment operator
    void operator=(const Fish &) = delete;

    void Update(double elapsed) override;

    wxXmlNode* XmlSave(wxXmlNode* node) override;

    void XmlLoad(wxXmlNode* node) override;


    /**
     * Get the speed of the fish
     * @return fish x speed
     */
    double GetSpeedX() const { return mSpeedX; }

    /**
     * Get the speed of the fish
     * @return fish y speed
     */
    double GetSpeedY() const{ return mSpeedY; }

    /**
     * Sets the speed of the fish
     * @param speedX the x speed to set
     * @param speedY the y speed to set
     */
    void SetSpeed(double speedX, double speedY) { mSpeedX = speedX; mSpeedY = speedY;}
};



#endif //FISH_H

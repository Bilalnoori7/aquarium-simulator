/**
 * @file FishAngel.h
 * @author Bilal
 *
 *
 */
 
#ifndef FISHANGEL_H
#define FISHANGEL_H

#include "Item.h"
#include "Fish.h"

/**
 * The class for FishAngel
 *
 */
class FishAngel : public Fish {
private:


public:

    /// Default constructor (disabled)
    FishAngel() = delete;

    /// Copy constructor (disabled)
    FishAngel(const FishAngel &) = delete;

    /// Assignment operator
    void operator=(const FishAngel &) = delete;

    ///public constructor
    FishAngel(Aquarium* aquarium);

    wxXmlNode* XmlSave(wxXmlNode* node) override;
};



#endif //FISHANGEL_H

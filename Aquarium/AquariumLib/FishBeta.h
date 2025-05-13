/**
 * @file FishBeta.h
 * @author Bilal
 *
 *
 */

#ifndef FISHBETA_H
#define FISHBETA_H

#include "Item.h"
#include "Fish.h"

/**
 * The class for FishBeta
 *
 */
class FishBeta : public Fish {
private:



public:
    /// Default constructor (disabled)
    FishBeta() = delete;

    /// Copy constructor (disabled)
    FishBeta(const FishBeta &) = delete;

    /// Assignment operator
    void operator=(const FishBeta &) = delete;

    ///public constructor
    FishBeta(Aquarium* aquarium);


    wxXmlNode* XmlSave(wxXmlNode* node) override;


};



#endif //FISHBETA_H

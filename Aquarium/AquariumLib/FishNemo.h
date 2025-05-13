/**
 * @file FishNemo.h
 * @author Bilal
 *
 *
 */
 
#ifndef FISHNEMO_H
#define FISHNEMO_H

#include "Item.h"
#include "Fish.h"

/**
 * Represents a FishNemo fish  in the application.
 *
 */
class FishNemo : public Fish{
private:



public:
    /// Default constructor (disabled)
    FishNemo() = delete;

    /// Copy constructor (disabled)
    FishNemo(const FishNemo &) = delete;

    /// Assignment operator
    void operator=(const FishNemo &) = delete;

    ///public constructor
    FishNemo(Aquarium* aquarium);
    wxXmlNode* XmlSave(wxXmlNode* node) override;
};



#endif //FISHNEMO_H

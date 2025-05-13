/**
 * @file DecorCastle.h
 * @author Bilal
 *
 *
 */
 
#ifndef CASTLE_H
#define CASTLE_H
#include "Item.h"

/**
 * Represents a DecorCastle item  in the application.
 *
 */
class DecorCastle : public Item  {
private:

public:
    /// Default constructor (disabled)
    DecorCastle() = delete;

    /// Copy constructor (disabled)
    DecorCastle(const DecorCastle &) = delete;

    /// Assignment operator
    void operator=(const DecorCastle &) = delete;

    ///public constructor
    DecorCastle(Aquarium* aquarium);
    wxXmlNode* XmlSave(wxXmlNode* node);
};



#endif //CASTLE_H

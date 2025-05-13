/**
 * @file Item.h
 * @author Bilal
 *
 *
 */
 
#ifndef ITEM_H
#define ITEM_H

class Aquarium;

/**
 * Base class for any item in our aquarium.
 */
class Item {

protected:
    Item(Aquarium *aquarium, const std::wstring &filename);


private:

    /// The underlying fish image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mItemBitmap;

    /// The aquarium this item is contained in
    Aquarium   *mAquarium;

    // Item location in the aquarium
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item



    bool mMirror = false;   ///< True mirrors the item image



public:
    virtual ~Item();

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * Get the width of the Item
     * @return Item width in pixels
     */
    double GetWidth() const { return mItemBitmap->GetWidth(); }

    /**
     * Get the width of the Item
     * @return Item width in pixels
     */
    double GetHeight() const { return mItemBitmap->GetHeight(); }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;


    virtual void Draw(wxDC *dc);

    virtual wxXmlNode* XmlSave(wxXmlNode* node);

    virtual void XmlLoad(wxXmlNode* node);

    void SetMirror(bool m);


    virtual bool HitTest(int x, int y);


    /**
     * Sets the active state of the object.
     * @param flag A boolean value where true activates and false dormants.
     *
    */
    virtual void IsActive(bool flag){};

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {};


    /**
     * Get the pointer to the Aquarium object
     * @return Pointer to Aquarium object
     */
    Aquarium *GetAquarium() { return mAquarium;  }




};



#endif //ITEM_H

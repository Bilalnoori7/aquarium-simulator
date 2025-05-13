/**
 * @file AquariumView.h
 * @author Bilal
 *
 *
 */
 
#ifndef AQUARIUMVIEW_H
#define AQUARIUMVIEW_H

#include "Aquarium.h"

/**
 * View class for our aquarium
 */
class AquariumView : public wxWindow {
private:
    /// The timer that allows for animation
    wxTimer mTimer;

    /// An object that describes our aquarium
    Aquarium  mAquarium;

    /// Any item we are currently dragging
    std::shared_ptr<Item> mGrabbedItem;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    void OnPaint(wxPaintEvent& event);

    void OnAddFishBetaFish(wxCommandEvent& event);

    void OnAddFishNemoFish(wxCommandEvent& event);

    void OnAddFishAngelFish(wxCommandEvent& event);

    void OnAddDecorCastle(wxCommandEvent& event);
    void OnFileSaveAs(wxCommandEvent& event);

    void OnLeftDown(wxMouseEvent& event);

    void OnLeftUp(wxMouseEvent& event);

    void OnMouseMove(wxMouseEvent& event);

    void OnDoubleClick(wxMouseEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);

public:
    void Initialize(wxFrame* parent);
};



#endif //AQUARIUMVIEW_H

/**
 * @file AquariumView.cpp
 * @author Bilal
 */

#include "pch.h"
#include "AquariumView.h"
#include <wx/dcbuffer.h>
#include "ids.h"
#include "FishBeta.h"
#include "FishNemo.h"
#include "FishAngel.h"
#include "DecorCastle.h"

/// Frame duration in milliseconds
const int FrameDuration = 30;

using namespace std;


/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void AquariumView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishNemoFish, this, IDM_ADDFISHNEMO);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishAngelFish, this, IDM_ADDFISHANGEL);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddDecorCastle, this, IDM_ADDDECORCASTLE);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileSaveAs, this, wxID_SAVEAS);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileOpen, this, wxID_OPEN);





    // Binds mouse handlers for left click, release, and movement events
    Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);
    Bind(wxEVT_LEFT_DCLICK, &AquariumView::OnDoubleClick, this);
    Bind (wxEVT_TIMER, &AquariumView::OnTimer, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    mStopWatch.Start();


}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void AquariumView::OnPaint(wxPaintEvent& event)
{
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;
    mAquarium.Update(elapsed);
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    mAquarium.OnDraw(&dc);
}


/**
 * Menu handler for Add Fish>Beta Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishBeta>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}


/**
 * Menu handler for Add Fish>Nemo Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishNemoFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishNemo>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}


/**
 * Menu handler for Add Fish>Angel Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishAngelFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishAngel>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu handler for Add Fish>castle Item
 * @param event Mouse event
 */
void AquariumView::OnAddDecorCastle(wxCommandEvent& event)
{
    auto castle= make_shared<DecorCastle>(&mAquarium);
    mAquarium.Add(castle);
    Refresh();
}

/**
 * Menu handler for Add File>Save as
 * @param event Mouse event
 */

void AquariumView::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, L"Save Aquarium file", L"", L"",
        L"Aquarium Files (*.aqua)|*.aqua", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();

    mAquarium.Save(filename);

}


/**
 * Handle the left mouse button down event
 * @param event
 */
void AquariumView::OnLeftDown(wxMouseEvent &event)
{
    mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());

    // Move the grabbed item to the end of the list
    if (mGrabbedItem != nullptr)
    {

        mAquarium.MoveItem(mGrabbedItem);
    }
}

/**
* Handle the left mouse button down event
* @param event
*/
void AquariumView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}


/**
* Handle the mouse move event
* @param event
*/
void AquariumView::OnMouseMove(wxMouseEvent &event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
        }
        else
        {
            // When the left button is released, we release the
            // item.
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }
}

/**
 * Handle the mouse double click event
 * @param event
 */
void AquariumView::OnDoubleClick(wxMouseEvent& event)
{
    mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());

}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void AquariumView::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, L"Load Aquarium file", L"", L"",
            L"Aquarium Files (*.aqua)|*.aqua", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    mAquarium.Load(filename);
    Refresh();

}

/**
 * Menu handler for a timer
 * @param event Mouse event
 */
void AquariumView::OnTimer(wxTimerEvent& event){
    Refresh();
}
/**
 * @file AquariumApp.cpp
 * @author Bilal Noori
 */

#include "pch.h"

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif


#include "AquariumApp.h"
#include <MainFrame.h>



/**
 * Initialize the application.
 *
 * Checks if the base wxApp initialization is successful.
 *
 * @return True if the initialization is successful, false otherwise
 */
/**
 * Initialize the application.
 * @return
 */
bool AquariumApp::OnInit()
{
    #ifdef WIN32
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}
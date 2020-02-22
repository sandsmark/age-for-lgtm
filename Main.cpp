#include "Main.h"
#include "Common.h"
#include "AGE_Copies.hpp"
#include "AGE_Frame.h"

#if __WXGTK3__
#include <glib.h>
#endif

IMPLEMENT_APP(AGE)

AGE_Frame *AGE_Frame::openEditors[4]{0};
Copies AGE_Frame::copies;

bool AGE::OnInit()
{
#if __WXGTK3__
    // shut gtk the fuck up, why the fuck is gtk still used anywhere
    g_log_set_default_handler([](const gchar*, GLogLevelFlags, const gchar*,gpointer){}, nullptr);
    g_log_set_writer_func([](GLogLevelFlags, const GLogField*, gsize, gpointer) {
            return G_LOG_WRITER_HANDLED;
        }, nullptr, nullptr);
#endif


    SetVendorName("Tapsa");
    SetAppName("AdvancedGenieEditor3");
    SetAppDisplayName("Advanced Genie Editor");
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxTGAHandler);

    wxToolTip::SetDelay(200);
    wxToolTip::SetAutoPop(32700);
    wxToolTip::SetReshow(1);

    wxString cmd1 = (wxApp::argc > 1) ? wxApp::argv[1] : "";
    AGE_Frame *window = new AGE_Frame("Advanced Genie Editor " + AGE_AboutDialog::AGE_VER, 0, cmd1);
    SetTopWindow(window);
    wxCommandEvent OpenFiles(wxEVT_COMMAND_MENU_SELECTED, window->eOpen);
    window->OnOpen(OpenFiles);

    return true;
}

// Fancy scaling :)
void AGE_Frame::FixSize(AGE_Frame *window)
{
    int ScrollerWidth = window->Units_ScrollSpace->GetMinSize().GetWidth();
    if(ScrollerWidth > 630)
    {
        int NewWidth = 270.0f * (ScrollerWidth / 630.0f) + ScrollerWidth;
        window->MinWindowWidth = NewWidth;
        window->SetSize(NewWidth, 870);
    }
    else
    {
        window->MinWindowWidth = 900;
        window->SetSize(900, 870);
    }
    window->Show(true);
    window->FixSizes();
}

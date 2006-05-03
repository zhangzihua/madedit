///////////////////////////////////////////////////////////////////////////////
// Name:        MadReplaceDialog.cpp
// Description:
// Author:      madedit@gmail.com
// Licence:     GPL
///////////////////////////////////////////////////////////////////////////////

#include "MadReplaceDialog.h"
#include "MadSearchDialog.h"

#include "MadEdit/MadEdit.h"

//Do not add custom headers.
//wx-dvcpp designer will remove them
////Header Include Start
////Header Include End

#include "../images/down.xpm"

MadReplaceDialog *g_ReplaceDialog=NULL;

//----------------------------------------------------------------------------
// MadReplaceDialog
//----------------------------------------------------------------------------
     //Add Custom Events only in the appropriate Block.
    // Code added in  other places will be removed by wx-dvcpp 
    ////Event Table Start
BEGIN_EVENT_TABLE(MadReplaceDialog,wxDialog)
	////Manual Code Start
	EVT_BUTTON(ID_WXBITMAPBUTTONRECENTFINDTEXT, MadReplaceDialog::WxBitmapButtonRecentFindTextClick)
	EVT_BUTTON(ID_WXBITMAPBUTTONRECENTREPLACETEXT, MadReplaceDialog::WxBitmapButtonRecentReplaceTextClick)
	EVT_MENU_RANGE(ID_RECENTFINDTEXT1, ID_RECENTFINDTEXT20, MadReplaceDialog::OnRecentFindText)
	EVT_MENU_RANGE(ID_RECENTREPLACETEXT1, ID_RECENTREPLACETEXT20, MadReplaceDialog::OnRecentReplaceText)
	////Manual Code End
	
	EVT_CLOSE(MadReplaceDialog::MadReplaceDialogClose)
	EVT_KEY_DOWN(MadReplaceDialog::MadReplaceDialogKeyDown)
	EVT_ACTIVATE(MadReplaceDialog::MadReplaceDialogActivate)
	EVT_BUTTON(ID_WXBUTTONCLOSE,MadReplaceDialog::WxButtonCloseClick)
	EVT_BUTTON(ID_WXBUTTONREPLACEALL,MadReplaceDialog::WxButtonReplaceAllClick)
	EVT_BUTTON(ID_WXBUTTONREPLACE,MadReplaceDialog::WxButtonReplaceClick)
	EVT_BUTTON(ID_WXBUTTONFINDNEXT,MadReplaceDialog::WxButtonFindNextClick)
	EVT_CHECKBOX(ID_WXCHECKBOXFINDHEX,MadReplaceDialog::WxCheckBoxFindHexClick)
END_EVENT_TABLE()
    ////Event Table End



MadReplaceDialog::MadReplaceDialog( wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style )
    : wxDialog( parent, id, title, position, size, style)
{
    CreateGUIControls();
}

MadReplaceDialog::~MadReplaceDialog() {} 

//static int gs_MinX=0;

static void ResizeItem(wxBoxSizer* sizer, wxWindow *item, int ax, int ay)
{
    int x, y;
    wxString str=item->GetLabel();
    item->GetTextExtent(str, &x, &y);
    item->SetSize(x+=ax, y+=ay);
    sizer->SetItemMinSize(item, x, y);
    
    //wxPoint pos=item->GetPosition();
    //if(pos.x + x > gs_MinX) gs_MinX = pos.x + x;
}

void MadReplaceDialog::CreateGUIControls(void)
{
    //Do not add custom Code here
    //wx-devcpp designer will remove them.
    //Add the custom code before or after the Blocks
    ////GUI Items Creation Start

	wxBoxSizer* WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(TRUE);

	wxBoxSizer* WxBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer1->Add(WxBoxSizer2,0,wxALIGN_TOP | wxALL,5);

	wxBoxSizer* WxBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer4,0,wxALIGN_LEFT | wxALL,5);

	wxBoxSizer* WxBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer5,0,wxALIGN_LEFT | wxALL,5);

	wxBoxSizer* WxBoxSizer6 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer2->Add(WxBoxSizer6,0,wxALIGN_LEFT | wxALL,5);

	WxCheckBoxMoveFocus = new wxCheckBox(this, ID_WXCHECKBOXMOVEFOCUS, _("&Move Focus to Editor Window"), wxPoint(5,5), wxSize(300,22), 0, wxDefaultValidator, _("WxCheckBoxMoveFocus"));
	WxBoxSizer6->Add(WxCheckBoxMoveFocus,0,wxALIGN_LEFT | wxALL,2);

	WxCheckBoxCaseSensitive = new wxCheckBox(this, ID_WXCHECKBOXCASESENSITIVE, _("&Case Sensitive"), wxPoint(5,37), wxSize(300,22), 0, wxDefaultValidator, _("WxCheckBoxCaseSensitive"));
	WxBoxSizer6->Add(WxCheckBoxCaseSensitive,0,wxALIGN_LEFT | wxALL,2);

	WxCheckBoxWholeWord = new wxCheckBox(this, ID_WXCHECKBOXWHOLEWORD, _("&Whole Word Only"), wxPoint(5,69), wxSize(300,22), 0, wxDefaultValidator, _("WxCheckBoxWholeWord"));
	WxBoxSizer6->Add(WxCheckBoxWholeWord,0,wxALIGN_LEFT | wxALL,2);

	WxCheckBoxRegex = new wxCheckBox(this, ID_WXCHECKBOXREGEX, _("Use Regular E&xpressions"), wxPoint(5,101), wxSize(300,22), 0, wxDefaultValidator, _("WxCheckBoxRegex"));
	WxBoxSizer6->Add(WxCheckBoxRegex,0,wxALIGN_LEFT | wxALL,2);

	WxCheckBoxFindHex = new wxCheckBox(this, ID_WXCHECKBOXFINDHEX, _("Find &Hex String (Example: BE 00 3A or BE003A)"), wxPoint(5,133), wxSize(300,22), 0, wxDefaultValidator, _("WxCheckBoxFindHex"));
	WxBoxSizer6->Add(WxCheckBoxFindHex,0,wxALIGN_LEFT | wxALL,2);

	wxBoxSizer* WxBoxSizer3 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer1->Add(WxBoxSizer3,0,wxALIGN_TOP | wxALL,5);

	WxButtonFindNext = new wxButton(this, ID_WXBUTTONFINDNEXT, _("Find &Next"), wxPoint(5,5), wxSize(100,28), 0, wxDefaultValidator, _("WxButtonFindNext"));
	WxBoxSizer3->Add(WxButtonFindNext,0,wxALIGN_LEFT | wxALL,5);

	WxButtonReplace = new wxButton(this, ID_WXBUTTONREPLACE, _("&Replace"), wxPoint(5,43), wxSize(100,28), 0, wxDefaultValidator, _("WxButtonReplace"));
	WxBoxSizer3->Add(WxButtonReplace,0,wxALIGN_LEFT | wxALL,5);

	WxButtonReplaceAll = new wxButton(this, ID_WXBUTTONREPLACEALL, _("Replace &All"), wxPoint(5,81), wxSize(100,28), 0, wxDefaultValidator, _("WxButtonReplaceAll"));
	WxBoxSizer3->Add(WxButtonReplaceAll,0,wxALIGN_LEFT | wxALL,5);

	WxButtonClose = new wxButton(this, ID_WXBUTTONCLOSE, _("Close"), wxPoint(5,119), wxSize(100,28), 0, wxDefaultValidator, _("WxButtonClose"));
	WxBoxSizer3->Add(WxButtonClose,0,wxALIGN_LEFT | wxALL,5);

	WxPopupMenuRecentReplaceText = new wxMenu(_("")  );

	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	this->SetTitle(_("Replace"));
	this->SetIcon(wxNullIcon);
	
    ////GUI Items Creation End
    
    this->SetPosition(wxPoint(300,100));

    int bw, bh;
    // find
    WxButtonFindNext->GetSize(&bw, &bh);

    m_FindText=new MadEdit(this, ID_MADEDIT1, wxPoint(0, 0), wxSize(400, bh));
    m_FindText->SetSingleLineMode(true);
    m_FindText->SetEncoding(wxT("UTF-32LE"));
    m_FindText->SetFixedWidthMode(false);
    m_FindText->SetRecordCaretMovements(false);
    m_FindText->SetInsertSpacesInsteadOfTab(false);
    m_FindText->SetWantTab(false);
    m_FindText->LoadDefaultSyntaxScheme();

    WxBoxSizer4->Add(m_FindText,0,wxALIGN_CENTER_HORIZONTAL | wxALL,0);
    WxBoxSizer4->SetItemMinSize(m_FindText, 400, bh);

    wxBitmap WxBitmapButtonRecentFindText_BITMAP (down_xpm);
    WxBitmapButtonRecentFindText = new wxBitmapButton(this, ID_WXBITMAPBUTTONRECENTFINDTEXT, WxBitmapButtonRecentFindText_BITMAP, wxPoint(0,0), wxSize(bh,bh), wxBU_AUTODRAW, wxDefaultValidator, _("WxBitmapButtonRecentFindText"));
    WxBoxSizer4->Add(WxBitmapButtonRecentFindText,0,wxALIGN_CENTER_HORIZONTAL | wxALL,0);

    // replace
    WxButtonReplace->GetSize(&bw, &bh);
    
    m_ReplaceText=new MadEdit(this, ID_MADEDIT2, wxPoint(0, 0), wxSize(400, bh));
    m_ReplaceText->SetSingleLineMode(true);
    m_ReplaceText->SetEncoding(wxT("UTF-32LE"));
    m_ReplaceText->SetFixedWidthMode(false);
    m_ReplaceText->SetRecordCaretMovements(false);
    m_ReplaceText->SetInsertSpacesInsteadOfTab(false);
    m_ReplaceText->SetWantTab(false);
    m_ReplaceText->LoadDefaultSyntaxScheme();

    WxBoxSizer5->Add(m_ReplaceText,0,wxALIGN_CENTER_HORIZONTAL | wxALL,0);
    WxBoxSizer5->SetItemMinSize(m_ReplaceText, 400, bh);
    
    WxBitmapButtonRecentReplaceText = new wxBitmapButton(this, ID_WXBITMAPBUTTONRECENTREPLACETEXT, WxBitmapButtonRecentFindText_BITMAP, wxPoint(0,0), wxSize(bh,bh), wxBU_AUTODRAW, wxDefaultValidator, _("WxBitmapButtonRecentReplaceText"));
    WxBoxSizer5->Add(WxBitmapButtonRecentReplaceText,0,wxALIGN_CENTER_HORIZONTAL | wxALL,0);

    // resize checkbox
    ResizeItem(WxBoxSizer6, WxCheckBoxMoveFocus, 25, 4);
    ResizeItem(WxBoxSizer6, WxCheckBoxCaseSensitive, 25, 4);
    ResizeItem(WxBoxSizer6, WxCheckBoxWholeWord, 25, 4);
    ResizeItem(WxBoxSizer6, WxCheckBoxRegex, 25, 4);
    ResizeItem(WxBoxSizer6, WxCheckBoxFindHex, 25, 4);

    GetSizer()->Fit(this);
    
    // connect to KeyDown event handler
    m_FindText->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    m_ReplaceText->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxMoveFocus->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxCaseSensitive->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxWholeWord->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxRegex->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxButtonFindNext->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxButtonReplace->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxButtonReplaceAll->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxButtonClose->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxBitmapButtonRecentFindText->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxBitmapButtonRecentReplaceText->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxFindHex->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));


    m_RecentReplaceText=new wxFileHistory(20, ID_RECENTREPLACETEXT1);
    m_RecentReplaceText->UseMenu(WxPopupMenuRecentReplaceText);

    wxConfigBase *m_Config=wxConfigBase::Get(false);
    wxString oldpath=m_Config->GetPath();
    m_Config->SetPath(wxT("/RecentReplaceText"));
    m_RecentReplaceText->Load(*m_Config);
    m_Config->SetPath(oldpath);

    
    if(g_SearchDialog!=NULL)
    {
        wxString text;
        g_SearchDialog->m_FindText->GetText(text, true);
        m_FindText->SetText(text);
    }

    if(m_RecentReplaceText->GetCount()>0)
    {
        wxString text=m_RecentReplaceText->GetHistoryFile(0);
        if(!text.IsEmpty())
        {
            m_ReplaceText->SetText(text);
        }
    }
    
    SetDefaultItem(WxButtonReplace);

}

void MadReplaceDialog::MadReplaceDialogClose(wxCloseEvent& event)
{
    // --> Don't use Close with a wxDialog,
    // use Destroy instead.
    if(event.CanVeto())
    {
        event.Veto();
        Show(false);
        return;
    }
    
    g_ReplaceDialog=NULL;
    Destroy();
}

/*
 * WxButtonCloseClick
 */
void MadReplaceDialog::WxButtonCloseClick(wxCommandEvent& event)
{
    Show(false);
}

/*
 * WxButtonFindNextClick
 */
void MadReplaceDialog::WxButtonFindNextClick(wxCommandEvent& event)
{   
    g_SearchDialog->WxCheckBoxMoveFocus->SetValue(WxCheckBoxMoveFocus->GetValue());
    g_SearchDialog->WxCheckBoxCaseSensitive->SetValue(WxCheckBoxCaseSensitive->GetValue());
    g_SearchDialog->WxCheckBoxWholeWord->SetValue(WxCheckBoxWholeWord->GetValue());
    g_SearchDialog->WxCheckBoxRegex->SetValue(WxCheckBoxRegex->GetValue());
    g_SearchDialog->WxCheckBoxFindHex->SetValue(WxCheckBoxFindHex->GetValue());
    //g_SearchDialog->WxCheckBoxFindHex->Show(WxCheckBoxFindHex->IsShown());
    g_SearchDialog->UpdateCheckBoxByCBHex(g_SearchDialog->WxCheckBoxFindHex->GetValue());
    
    wxString text;
    m_FindText->GetText(text, true);
    g_SearchDialog->m_FindText->SetText(text);
    
    wxCommandEvent e;
    g_SearchDialog->WxButtonFindNextClick(e);
}

void MadReplaceDialog::UpdateCheckBoxByCBHex(bool check)
{
    if(/*WxCheckBoxFindHex->IsShown() &&*/ check)
    {
        WxCheckBoxCaseSensitive->Disable();
        WxCheckBoxWholeWord->Disable();
        WxCheckBoxRegex->Disable();
    }
    else
    {
        WxCheckBoxCaseSensitive->Enable();
        WxCheckBoxWholeWord->Enable();
        WxCheckBoxRegex->Enable();
    }
}

/*
 * WxCheckBoxFindHexClick
 */
void MadReplaceDialog::WxCheckBoxFindHexClick(wxCommandEvent& event)
{
    UpdateCheckBoxByCBHex(event.IsChecked());
}

/*
 * MadReplaceDialogKeyDown
 */
void MadReplaceDialog::MadReplaceDialogKeyDown(wxKeyEvent& event)
{
    int key=event.GetKeyCode();
    
    //g_SearchDialog->SetTitle(wxString()<<key);
    
    switch(key)
    {
    case WXK_ESCAPE:
        g_ReplaceDialog->Show(false);
        return;
    case WXK_RETURN:
    case WXK_NUMPAD_ENTER:
        if((wxButton*)this!=g_ReplaceDialog->WxButtonFindNext && 
           (wxButton*)this!=g_ReplaceDialog->WxButtonReplace && 
           (wxButton*)this!=g_ReplaceDialog->WxButtonReplaceAll && 
           (wxButton*)this!=g_ReplaceDialog->WxButtonClose)
        {
            wxCommandEvent e;
            g_ReplaceDialog->WxButtonReplaceClick(e);
            return; // no skip
        }
        break;
    case WXK_DOWN:
        if((MadEdit*)this==g_ReplaceDialog->m_FindText)
        {
            int x,y,w,h;
            g_ReplaceDialog->m_FindText->GetPosition(&x, &y);
            g_ReplaceDialog->m_FindText->GetSize(&w, &h);
            g_ReplaceDialog->PopupMenu(g_SearchDialog->WxPopupMenuRecentFindText, x, y+h);
            return;
        }
        else if((MadEdit*)this==g_ReplaceDialog->m_ReplaceText)
        {
            int x,y,w,h;
            g_ReplaceDialog->m_ReplaceText->GetPosition(&x, &y);
            g_ReplaceDialog->m_ReplaceText->GetSize(&w, &h);
            g_ReplaceDialog->PopupMenu(g_ReplaceDialog->WxPopupMenuRecentReplaceText, x, y+h);
            return;
        }
        break;
    }
    
    event.Skip();
}

void MadReplaceDialog::WxBitmapButtonRecentFindTextClick(wxCommandEvent& event)
{
    PopupMenu(g_SearchDialog->WxPopupMenuRecentFindText);
}

void MadReplaceDialog::WxBitmapButtonRecentReplaceTextClick(wxCommandEvent& event)
{
    PopupMenu(WxPopupMenuRecentReplaceText);
}

void MadReplaceDialog::OnRecentFindText(wxCommandEvent& event)
{
    int idx=event.GetId()-ID_RECENTFINDTEXT1;
    wxString text=g_SearchDialog->m_RecentFindText->GetHistoryFile(idx);
    if(!text.IsEmpty())
    {
        m_FindText->SetText(text);
        m_FindText->SetFocus();
    }
}

void MadReplaceDialog::OnRecentReplaceText(wxCommandEvent& event)
{
    int idx=event.GetId()-ID_RECENTREPLACETEXT1;
    wxString text=m_RecentReplaceText->GetHistoryFile(idx);
    if(!text.IsEmpty())
    {
        m_ReplaceText->SetText(text);
        m_ReplaceText->SetFocus();
    }
}

/*
 * WxButtonReplaceClick
 */
void MadReplaceDialog::WxButtonReplaceClick(wxCommandEvent& event)
{
    extern MadEdit *g_ActiveMadEdit;

    if(g_ActiveMadEdit==NULL)
        return;
    
    wxString text;
    m_FindText->GetText(text, true);
    
    if(text.Len()>0)
    {
        wxString reptext;
        m_ReplaceText->GetText(reptext, true);
    
        g_SearchDialog->m_RecentFindText->AddFileToHistory(text);
        
        if(reptext.Len()>0)
        {
            m_RecentReplaceText->AddFileToHistory(reptext);
        }
        
        bool ok=true;
        if(/*WxCheckBoxFindHex->IsShown() &&*/ WxCheckBoxFindHex->GetValue())
        {
            ok=g_ActiveMadEdit->ReplaceHex(text, reptext);
        }
        else
        {
            ok=g_ActiveMadEdit->ReplaceText(text, reptext,
                WxCheckBoxRegex->GetValue(), 
                WxCheckBoxCaseSensitive->GetValue(), 
                WxCheckBoxWholeWord->GetValue());
        }

        if(ok)
        {
            if(!g_ActiveMadEdit->IsSelected()) // not found
            {
                wxMessageDialog dlg(this, _("Cannot find the matched string.\nReplace is finished."), wxT("MadEdit"));
                dlg.ShowModal();
                
                m_FindText->SetFocus();
            }
            else
            {
                if(WxCheckBoxMoveFocus->GetValue())
                {
                    ((wxFrame*)wxTheApp->GetTopWindow())->Raise();
                    g_ActiveMadEdit->SetFocus();
                }
            }
        }
    }
}

/*
 * WxButtonReplaceAllClick
 */
void MadReplaceDialog::WxButtonReplaceAllClick(wxCommandEvent& event)
{
    extern MadEdit *g_ActiveMadEdit;

    if(g_ActiveMadEdit==NULL)
        return;
    
    wxString text;
    m_FindText->GetText(text, true);
    
    if(text.Len()>0)
    {
        wxString reptext;
        m_ReplaceText->GetText(reptext, true);
    
        g_SearchDialog->m_RecentFindText->AddFileToHistory(text);
        
        if(reptext.Len()>0)
        {
            m_RecentReplaceText->AddFileToHistory(reptext);
        }
        
        int count=0;
        if(/*WxCheckBoxFindHex->IsShown() &&*/ WxCheckBoxFindHex->GetValue())
        {
            count=g_ActiveMadEdit->ReplaceHexAll(text, reptext);
        }
        else
        {
            count=g_ActiveMadEdit->ReplaceTextAll(text, reptext,
                WxCheckBoxRegex->GetValue(), 
                WxCheckBoxCaseSensitive->GetValue(), 
                WxCheckBoxWholeWord->GetValue());
        }

        if(count>=0)
        {
            wxString msg;
            if(count==0)
                msg=wxString(_("Cannot find any matched string."));
            else 
                msg=wxString::Format(_("%d string(s) were replaced."), count);

            wxMessageDialog dlg(this, msg, wxT("MadEdit"));
            dlg.ShowModal();
        }

        m_FindText->SetFocus();
    }
}

/*
 * MadReplaceDialogActivate
 */
void MadReplaceDialog::MadReplaceDialogActivate(wxActivateEvent& event)
{
    wxConfigBase *m_Config=wxConfigBase::Get(false);
    wxString oldpath=m_Config->GetPath();

    if(event.GetActive())
    {
        bool bb;
        m_Config->Read(wxT("/MadEdit/SearchMoveFocus"), &bb, false);
        WxCheckBoxMoveFocus->SetValue(bb);

        m_Config->Read(wxT("/MadEdit/SearchCaseSensitive"), &bb, false);
        WxCheckBoxCaseSensitive->SetValue(bb);

        m_Config->Read(wxT("/MadEdit/SearchWholeWord"), &bb, false);
        WxCheckBoxWholeWord->SetValue(bb);

        m_Config->Read(wxT("/MadEdit/SearchRegex"), &bb, false);
        WxCheckBoxRegex->SetValue(bb);

        m_Config->Read(wxT("/MadEdit/SearchHex"), &bb, false);
        WxCheckBoxFindHex->SetValue(bb);
        UpdateCheckBoxByCBHex(bb);
    }
    else
    {
        m_Config->Write(wxT("/MadEdit/SearchMoveFocus"), WxCheckBoxMoveFocus->GetValue());
        m_Config->Write(wxT("/MadEdit/SearchCaseSensitive"), WxCheckBoxCaseSensitive->GetValue());
        m_Config->Write(wxT("/MadEdit/SearchWholeWord"), WxCheckBoxWholeWord->GetValue());
        m_Config->Write(wxT("/MadEdit/SearchRegex"), WxCheckBoxRegex->GetValue());
        m_Config->Write(wxT("/MadEdit/SearchHex"), WxCheckBoxFindHex->GetValue());
    }

    m_Config->SetPath(oldpath);
}


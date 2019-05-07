///////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/filectrl.h
// Purpose:     wxGtkFileCtrl Header
// Author:      Diaa M. Sami
// Modified by:
// Created:     Aug-10-2007
// Copyright:   (c) Diaa M. Sami
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////


#ifndef _WX_GTK_FILECTRL_H_
#define _WX_GTK_FILECTRL_H_

#include "wx/control.h"
#include "wx/filectrl.h"

extern WXDLLIMPEXP_DATA_CORE(const char) wxFileSelectorDefaultWildcardStr[];

typedef struct _GtkFileChooser GtkFileChooser;

// [GTK] current problems:
// All methods(e.g. SetFilename(), SetPath(), etc) which change the state of
// the control result in events fired, such events should be suppressed.
// ------
// Sometimes a selection event(with 0 files) is fired before
// wxEVT_FILECTRL_FOLDERCHANGED, unfortunately this can hardly be detected!

// A wx wrapper for any Gtk object implementing the interface GtkFileChooser

class WXDLLIMPEXP_CORE wxGtkFileChooser
{
public:
    wxGtkFileChooser() { m_ignoreNextFilterEvent = false; }

    void SetWidget(GtkFileChooser *w);

    wxString GetPath() const;
    void GetPaths( wxArrayString& paths ) const;
    wxString GetDirectory() const;
    wxString GetFilename() const;
    void GetFilenames( wxArrayString& files ) const;
    int GetFilterIndex() const;

    bool SetPath( const wxString& path );
    bool SetDirectory( const wxString& dir );
    void SetWildcard( const wxString& wildCard );
    void SetFilterIndex( int filterIndex );

    bool HasFilterChoice() const;

    bool ShouldIgnoreNextFilterEvent() const { return m_ignoreNextFilterEvent; }

    wxString GetCurrentWildCard() const
       { return m_wildcards[GetFilterIndex()]; }

private:
    GtkFileChooser *m_widget;
    // First wildcard in filter, to be used when the user
    // saves a file without giving an extension.
    wxArrayString   m_wildcards;

    // If true, ignore the next event because it was generated by us and not
    // the user.
    bool m_ignoreNextFilterEvent;
};

#if wxUSE_FILECTRL

class WXDLLIMPEXP_CORE wxGtkFileCtrl: public wxControl,
            public wxFileCtrlBase
{
public:
    wxGtkFileCtrl () { Init(); }

    wxGtkFileCtrl ( wxWindow *parent,
                    wxWindowID id,
                    const wxString& defaultDirectory = wxEmptyString,
                    const wxString& defaultFilename = wxEmptyString,
                    const wxString& wildCard = wxString(wxFileSelectorDefaultWildcardStr, wxConvLibc),
                    long style = wxFC_DEFAULT_STYLE,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    const wxString& name = wxString(wxFileCtrlNameStr, wxConvLibc) )
    {
        Init();
        Create( parent, id, defaultDirectory, defaultFilename, wildCard, style, pos, size, name );
    }

    virtual ~wxGtkFileCtrl();

    bool Create( wxWindow *parent,
                 wxWindowID id,
                 const wxString& defaultDirectory = wxEmptyString,
                 const wxString& defaultFileName = wxEmptyString,
                 const wxString& wildCard = wxString(wxFileSelectorDefaultWildcardStr, wxConvLibc),
                 long style = wxFC_DEFAULT_STYLE,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 const wxString& name = wxString(wxFileCtrlNameStr, wxConvLibc) );

    virtual void SetWildcard( const wxString& wildCard ) wxOVERRIDE;
    virtual void SetFilterIndex( int filterIndex ) wxOVERRIDE;
    virtual bool SetDirectory( const wxString& dir ) wxOVERRIDE;
    virtual bool SetFilename( const wxString& name ) wxOVERRIDE;
    virtual bool SetPath( const wxString& path ) wxOVERRIDE;

    virtual wxString GetFilename() const wxOVERRIDE;
    virtual wxString GetDirectory() const wxOVERRIDE;
    virtual wxString GetWildcard() const wxOVERRIDE { return this->m_wildCard; }
    virtual wxString GetPath() const wxOVERRIDE;
    virtual void GetPaths( wxArrayString& paths ) const wxOVERRIDE;
    virtual void GetFilenames( wxArrayString& files ) const wxOVERRIDE;
    virtual int GetFilterIndex() const wxOVERRIDE { return m_fc.GetFilterIndex(); }

    virtual bool HasMultipleFileSelection() const wxOVERRIDE { return HasFlag( wxFC_MULTIPLE ); }
    virtual void ShowHidden(bool show) wxOVERRIDE;

    virtual bool HasFilterChoice() const
        { return m_fc.HasFilterChoice(); }


    // Implementation only from now on.
    bool GTKShouldIgnoreNextFilterEvent() const
        { return m_fc.ShouldIgnoreNextFilterEvent(); }

    bool    m_checkNextSelEvent;
    bool    m_ignoreNextFolderChangeEvent;

protected:
    GtkFileChooser     *m_fcWidget;
    wxGtkFileChooser    m_fc;
    wxString            m_wildCard;

private:
    void Init();

    wxDECLARE_DYNAMIC_CLASS(wxGtkFileCtrl);
};

#endif // wxUSE_FILECTRL

#endif // _WX_GTK_FILECTRL_H_


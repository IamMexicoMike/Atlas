#ifndef FRAMEMANIPULACION_H
#define FRAMEMANIPULACION_H

#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/panel.h>
#include <wx/statusbr.h>

#include <iostream>
#include <vector>
#include <memory>

#include <Database.h>
#include <PanelBasico.h>

class FrameManipulacion: public wxFrame
{
    public:
        FrameManipulacion(wxWindow* parent, wxWindowID id=-1);
        wxGrid* generarTabla(wxWindow* parent);
        virtual ~FrameManipulacion();

    private:

        //Handlers
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

        //Identificadores
        long ID_BCOMMIT;
        long ID_CBSELECCIONARTABLA;
        long ID_GTABLA;

        long ID_PANEL1;
        long idMenuSalir;
        long idMenuOpciones;
        long idMenuImprimir;
        long ID_STATUSBAR1;

        //Declaraciones
        wxMenuBar* mbBarraMenu;
        wxMenu* mArchivo;
        wxMenu* mOpciones;
        wxMenuItem* miImprimir;

        wxBoxSizer* bsPadre;
        wxBoxSizer* bsOpciones;

        wxPanel* Panel1;
        wxStatusBar* sbBarraEstatus;
        wxGrid* gTabla;
        wxButton* bCommit;
        wxComboBox* cbSeleccionarTabla;

        //PanelBasico* pbPanel;
        wxGrid* tabla;
};

#endif // FRAMEMANIPULACION_H

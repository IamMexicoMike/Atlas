#ifndef PANELBASICO_H
#define PANELBASICO_H

#include <wx/grid.h>
#include <wx/panel.h>

/* El panel donde vas a dibujar algunas cosas */
class PanelBasico: public wxPanel
{
public:
    wxGrid* grid;
    wxMenuItem* miArchivo;
    wxMenuItem* miAyuda;

    PanelBasico(wxFrame* parent); //ctor
    void paintEvent(wxPaintEvent & evt); //evento pintar
    void paintNow(); //función no usada
    void render(wxDC& dc); //renderear. re-implementado desde WxFrame?

    DECLARE_EVENT_TABLE() //este macro qué pedo?
};

#endif // PANELBASICO_H

#include "PanelBasico.h"

#include "wx/wx.h"

#include <iostream>
#include <string>

#include <Database.h>

using namespace std;

BEGIN_EVENT_TABLE(PanelBasico, wxPanel)
    EVT_PAINT(PanelBasico::paintEvent)
END_EVENT_TABLE()

PanelBasico::PanelBasico(wxFrame* parent) :
wxPanel(parent)
{
    string instr = "user=postgres dbname=test";
    Database db(instr);

    db.res = PQexec(db.conn, "SELECT * from lenguajes;");
    //db.res = PQexec(db.conn, "\\d");

    if (PQresultStatus(db.res) != PGRES_TUPLES_OK) {

        printf("No data retrieved\n");
        PQclear(db.res);
        exit(1);
    }

    int rows = PQntuples(db.res);
    int cols = PQnfields(db.res);
    int cols2 = PQnparams(db.res);

    printf("cols: %d, cols2: %d\n\n", cols, cols2);

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            printf("%s ", PQgetvalue(db.res, i, j));
        printf("\n");
    }

    // Create a wxGrid object
    grid = new wxGrid( this,
                    -1,
                    wxPoint( 0, 0 ),
                    wxSize( 500, 250 ) );
    // Then we call CreateGrid to set the dimensions of the grid
    // (100 rows and 10 columns in this example)
    grid->CreateGrid(rows, cols);
    // We can set the sizes of individual rows and columns
    // in pixels
    //grid->SetRowSize( 0, 60 );
    //grid->SetColSize( 1, 180 );
    // And set grid cell contents as strings
    for(int i=0; i < rows; ++i)
        for(int j=0; j<cols; ++j)
            grid->SetCellValue(i, j, PQgetvalue(db.res, i, j));
    /*
    grid->SetCellValue( 0, 0, "wxGrid is good" );
    // We can specify that some cells are read->only
    grid->SetCellValue( 0, 3, "This is read->only" );
    grid->SetReadOnly( 0, 3 );
    // Colours can be specified for grid cell contents
    grid->SetCellValue(3, 3, "green on grey");
    grid->SetCellTextColour(3, 3, *wxGREEN);
    grid->SetCellBackgroundColour(3, 3, *wxLIGHT_GREY);
    // We can specify the some cells will store numeric
    // values rather than strings. Here we set grid column 5
    // to hold floating point values displayed with width of 6
    // and precision of 2
    grid->SetColFormatFloat(5, 6, 2);
    grid->SetCellValue(0, 6, "3.1415");
    */
}


/* Evento para re-pintar */
void PanelBasico::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}


/* Esta función no es necesaria. Acostúmbrate a depender de paintEvent*/
void PanelBasico::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

/*No había o borraste la descripción. Es un método heredado?*/
void PanelBasico::render(wxDC&  dc)
{
    // dibuja texto
    dc.DrawText(wxT("Prueba_!"), 43, 60);

    // dibuja un circulo
    dc.SetBrush(*wxGREEN_BRUSH); // relleno verde
    dc.SetPen( wxPen( wxColor(255,0,0), 5)); // perímetro rojo de 5 pixeles de ancho
    dc.DrawCircle( wxPoint(43,43), 25 /*radio*/ );
}

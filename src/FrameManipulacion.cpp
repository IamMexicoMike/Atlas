#include "FrameManipulacion.h"
#include <wx/wx.h>

/*Esto es obscuro y feo. Entiéndelo*/
/*
BEGIN_EVENT_TABLE(FrameManipulacion,wxFrame)

    EventTable(FrameManipulacion)

END_EVENT_TABLE()

*/
FrameManipulacion::FrameManipulacion(wxWindow* parent,wxWindowID id) //ctor
{
    ID_CBSELECCIONARTABLA = wxNewId();
    idMenuImprimir = wxNewId();
    ID_STATUSBAR1 = wxNewId();


    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    bsPadre = new wxBoxSizer(wxHORIZONTAL);
    bsOpciones = new wxBoxSizer(wxVERTICAL);

    //Lado Izquierdo: Botón y ComboBox
    bCommit = new wxButton(this, 0, _("Commit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BCOMMIT"));
    cbSeleccionarTabla = new wxComboBox(this, ID_CBSELECCIONARTABLA, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CBSELECCIONARTABLA"));

    //Lado Derecho: Tabla (sin panel)
    tabla = generarTabla(this);

    //Llenamos padre: Incluye lado izquierdo y tabla del lado derecho
    bsPadre->Add(bsOpciones, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    bsPadre->Add(tabla.get(), 1, wxALIGN_LEFT);

    //Llenamos lado izquierdo
    bsOpciones->Add(bCommit, 1, wxALL|wxALIGN_TOP, 5);
    bsOpciones->Add(cbSeleccionarTabla, 1, wxALIGN_TOP, 5);

    SetSizer(bsPadre);
    mbBarraMenu = new wxMenuBar();
    mArchivo = new wxMenu();
    miImprimir = new wxMenuItem(mArchivo, idMenuImprimir, _("Impimir\tCtrl-I"), _("Imprimir la tabla"), wxITEM_NORMAL);
    mArchivo->Append(miImprimir);
    mbBarraMenu->Append(mArchivo, _("&Archivo"));
    mOpciones = new wxMenu();
    //MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    //Menu2->Append(MenuItem2);
    mbBarraMenu->Append(mOpciones, _("Opciones"));

    SetMenuBar(mbBarraMenu);
    sbBarraEstatus = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    sbBarraEstatus->SetFieldsCount(1,__wxStatusBarWidths_1);
    sbBarraEstatus->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(sbBarraEstatus);

    bsPadre->Fit(this);
    bsOpciones->Fit(this);
    //bsOpciones->SetSizeHints(this);
    bsPadre->SetSizeHints(this);
}

FrameManipulacion::~FrameManipulacion() //dtor
{
    //Destroy(FrameManipulacion) //macros...
}

std::unique_ptr<wxGrid> FrameManipulacion::generarTabla(wxWindow* parent)
{

    Database db("user=postgres dbname=test");

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

    const int TAM_POR_FILA {36};
    const int TAM_POR_COL {36};

    int w = cols*TAM_POR_COL;
    int h = rows*TAM_POR_FILA;

    // Creamos un wxGrid en un smart pointer
    std::unique_ptr<wxGrid> grid(new wxGrid(parent, -1, wxPoint(0, 0), wxSize(w, h)));

    //Creamos la tabla
    grid->CreateGrid(rows, cols);

    // Podemos establecer el tamaño de filas y columnas individuales
    //grid->SetRowSize( 0, 60 );
    //grid->SetColSize( 1, 180 );

    // Llenamos las casillas de la tabla
    for(int i=0; i < rows; ++i)
        for(int j=0; j<cols; ++j)
            grid->SetCellValue(i, j, PQgetvalue(db.res, i, j));

    return grid;
}

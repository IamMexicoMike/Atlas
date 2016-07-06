#include "wx/wx.h"
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/panel.h>
#include <wx/button.h>

#include <iostream>
#include <string>
#include <thread>
#include <memory>

#include <Database.h>
#include <FrameManipulacion.h>

#include "TextDrop.h"

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/button.hpp>

/*
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}
*/
void prueba_nana()
{
    using namespace nana;

    //
    //std::unique_ptr<FrameManipulacion> frame;
    //frame = make_unique<FrameManipulacion>(nullptr);
    //frame->Show();
    FrameManipulacion frame(nullptr);
    frame.Show();
    //

	form fm;
	place plc(fm);
	plc.div("<abc>");
	button a(fm, "DB"), b(fm); //Porqué sólo funciona sólo a veces?
	plc["abc"] << a << b;
	plc.collocate();
	fm.show();

	a.events().click([&plc]
	{
		plc.modify("abc", "margin=10 vert<efg>"); //modify the field 'abc' and add a new child field 'efg'.
		plc.collocate();
		//frame = new FrameManipulacion(nullptr);
        //frame->Show();


	});

	exec();
}


/*Tu parent debe ser un WxFrame*/

using namespace std;

/*Tu aplicación principal. Sólo puede haber una de este tipo*/
class aAplicacion: public wxApp
{
    bool OnInit();
};




/* implementación del método OnInit de wxApp. Sólo puede haber uno.
Consideremos susituir todos esos apuntadores colgantes por unique_ptr<T>.
Necesitas entender como un wxWidget parent destruye a sus hijos al salir; unique<ptr> se interpondrá? */
bool aAplicacion::OnInit()
{
    bool wxsOK=true;

        FrameManipulacion* frame = new FrameManipulacion(0);
        frame->Show();
        SetTopWindow(frame);

        //frame->SetSizer(sizer);
        //frame->SetAutoLayout(true);
        //frame->Show();

        TextDrop *td = new TextDrop(wxT("Text Drop"));
        td->Show(true);

    return wxsOK;
}


/*Esto da pie a toda una nueva manera de usar wxWidgets*/

int main(int argc, char** argv)
{
    std::cout << "sirve esto?" << std::endl;


    wxApp::SetInstance(new aAplicacion());
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();

    thread hilo(prueba_nana);

    wxTheApp->OnRun();
    wxTheApp->OnExit();

    hilo.join(); //supongo que necesitamos limpiar todo el desvergue
    wxEntryCleanup();


    std::cout << "sirve esto?" << std::endl;


}

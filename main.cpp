#include "wx/wx.h"
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/panel.h>
#include <wx/button.h>

#include <iostream>
#include <string>
#include <thread>

#include <Database.h>
#include <FrameManipulacion.h>

#include "TextDrop.h"

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/listbox.hpp>

void prueba_nana()
{
    using namespace nana;
        form fm;
        listbox lb(fm, nana::rectangle(5, 5, 280, 120));
        lb.append_header("Header", 100);
    // this will attemp to use
    // item_proxy cat_proxy::append (T &&t, bool set_value=false)
    // to add a value any of wchar_t[4]  = "int"
        // lb.at(0).append(STR("int"));
    lb.at(0).append({"int"});
    lb.at(0).append({"double"});
        lb.anyobj(0, 0, 10);
        lb.anyobj(0, 1, 0.1);
        int * pi = lb.anyobj<int>(0, 0);          // it returns a nullptr if there is not an int object specified.
    std::cout << "Index: (0,0) -> int value: " << *pi << std::endl;
        double * pd = lb.anyobj<double>(0, 1); // it returns a nullptr if there is not an double object specified.
    std::cout << "Index: (0,1) -> double value: " << *pd << std::endl;
        fm.show();
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


int main(int argc, char** argv)
{
    std::cout << "sirve esto?" << std::endl;


    wxApp::SetInstance(new aAplicacion());
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();

    thread hilo(prueba_nana);

    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();


    std::cout << "sirve esto?" << std::endl;

    hilo.join();
}

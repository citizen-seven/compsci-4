#include <wx/wx.h>

// Уже имеется абстрактный класс wxApp для создания
// приложения
// наше приложение будет наследником этого wxApp
// виртуальную функцию OnInit необходимо определить в нашем классе
class Begin: public wxApp{
public:
    virtual bool OnInit();
};

// Макрос для запуска приложения (вместо main)
// В скобках указыаем как называется наш класс-приложение
IMPLEMENT_APP(Begin)

// переопределяем виртуальную функцию OnInit
// именно она и запускает приложение
bool Begin::OnInit()
{
    // создаем динамический объект класса wxFrame (наше окно)
    //окно будет "пустое" размером 200х200 пикселов
    wxFrame *wind=new wxFrame(NULL,wxID_ANY,wxT("Begin.."),wxDefaultPosition,wxSize(200,200));
    // запуск. Окно будет видимое
    wind->Show(true);
    return true;
};
#include <wx/wx.h>
// Класс нашео приложения
class Begin: public wxApp{
public:
    virtual bool OnInit();
};

// Окошко было пустое. Поэтому расширим фрейм.
// Для этого создадим класс-наследник MyWin

class MyWin:public wxFrame{
    // Добавим элементы:
    
    wxMenuBar *menubar; // полоска для меню
    wxMenu *file; // менюшка  на полоске
    wxStatusBar *sb; // статус-бар
    // Пункты меню для открытия файла и
    // закрытия приложения
    wxMenuItem *load,*quit;
    wxString ss; // строка (пригодится)
    
public:
    // конструктор с заголовком окна
    MyWin(const wxString& title);
    
    // Функции, которые будут вызываться при выборе пунктов меню
    // Функция закрытия окна
    void OnQuit(wxCommandEvent& event);
    // функция загрузки файла
    void OnLoad(wxCommandEvent& event);
};
// Идентификаторы нужны всем элементам, которые будут обрабатываться обработчиками событий
// идентификатор пунткта меню
const int ID_MENU_LOAD =1002;

MyWin::MyWin(const wxString& title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(200,200)){
    // создали полоску для менюшки
    menubar = new wxMenuBar;
    // создали менюшку
    file = new wxMenu;
    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit"));
    load = new wxMenuItem(file, ID_MENU_LOAD, wxT("&Load"));
    file->Append(load);
    file->Append(quit);
    // закинули менюшку на полоску
    menubar->Append(file, wxT("&File"));
    // установили полоску в окно
    SetMenuBar(menubar);
    
    // Connect служит для соединения элемента приложения с обработчиком событий
    // подключили менюшку
    // wxID_EXIT - стандартный идентификатор для выключения приложения,
    // wxEVT_COMMAND_MENU_SELECTED - идентификатор действия (выбор пункта меню)
    // wxCommandEventHandler - обработчик событий, связанных с командами: меню, кнопки...
    // MyWin::OnQuit - функция, которая будет вызываться при этом событиии
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnQuit));
    // ID_MENU_LOAD - не стандартный идентификатор (сами определяли)
    // MyWin::OnLoad - функция, которая будет вызываться при этом событиии
    Connect(ID_MENU_LOAD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnLoad));
    
    sb=CreateStatusBar();
    sb->SetStatusText(wxString(wxT("что-то напишем и здесь")));
};

// Функция выключения окна
// Параметр - объект класса wxCommandEvent
// Можно использовать его методы
// Но здесь не нужно
void MyWin::OnQuit(wxCommandEvent& event){
    Close(true);
};

// Функция для загрузки
void MyWin::OnLoad(wxCommandEvent& event){
    // Ничего пока не происходит
    // просто будет сообщение
    wxMessageBox(wxT("Нажали"),wxT("Load"));
};

IMPLEMENT_APP(Begin)

bool Begin::OnInit()
{
    MyWin *wind=new MyWin(wxT("Begin.."));
    wind->Show(true);
    return true;
};
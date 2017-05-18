#include <wx/wx.h>
#include <wx/file.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/sstream.h>
#include <wx/string.h>


class Begin: public wxApp{
public:
    virtual bool OnInit();
};
// Нужен еще класс Draw
class Draw;
class MyWin;

class MyWin:public wxFrame{
    wxMenuBar *menubar; // полоска для меню
    wxMenu *file,*im; // менюшка  на полоске
    wxMenuItem *load,*quit; // открывалка  файла
    wxTextCtrl *tc; // текстовое окошко
    // Указатель на объект Draw
    Draw *dp;
    // панель
    // если элемнты помещать сразу на фрейм, то первый же объект
    // займет весь фрейм
    // для различных элементов есть wxPanel
    wxPanel *m_pan;
    // Это в "подвале" окошка
    wxStatusBar *sb; // статус бар
    // строка (для всех типов кодировки)
    wxString ss;
public:
    //  конструктор
    MyWin(const wxString& title);
    // две координаты для рисования
    wxPoint a;
    wxPoint b;
    // Функция закрытия окна
    void OnQuit(wxCommandEvent& event);
    // Загрузка файла с данными
    void OnLoad(wxCommandEvent& event);
};

// класс для рисования
// наследник wxPanel
class Draw: public wxPanel{
    // указатель на верхнее окно
    // это нужно для доступа к элементам (к a и b)
    MyWin *mn;
public:
    // в конструкторе указывается адрес объекта, который ее содержит
    Draw(wxPanel *parent, MyWin *main);
    // рисовалка
    void OnPaint(wxPaintEvent & event);
};
//иднтификаторы
// загрузка
const int ID_MENU_LOAD =1002;
// редактирование
const int ID_MENU_EDIT =1003;

// Конструктор фрейма
MyWin::MyWin(const wxString& title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(400,400)){
    // создали полоску для менюшки
    menubar = new wxMenuBar;
    // создали менюшку
    file = new wxMenu;
    
    // закинули менюшку на полоску
    // пока не работает (для "красоты")
    
    file->Append(wxID_ANY, wxT("&New"));
    
    file->AppendSeparator();
    // Для всех пунктор меню указывем идентификатор чтобы
    // связать обработчик событие с конкретным элементом
    // добавили к менюшке раздел quit
    quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit"));
    // добавили раздел load
    load = new wxMenuItem(file, ID_MENU_LOAD, wxT("&Load"));
    file->Append(load);
    file->Append(quit);
    // Это еще один пункт меню
    // пока тоже не работает
    im = new wxMenu;
    im->Append(wxID_ANY, wxT("Edit figure"));
    im->Append(wxID_ANY, wxT("Rotate 90"));
    // добавили оба пункта меню на полску меню
    menubar->Append(file, wxT("&File"));
    menubar->Append(im, wxT("&Edit"));
    
    // установили полоску в окно
    SetMenuBar(menubar);
    // подключили менюшку exit
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnQuit));
    // подключили load (идентификаторы такие же как и при создании каждого элемента)
    Connect(ID_MENU_LOAD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyWin::OnLoad));
    
    // создание панельки для текста, кнопок и рисовалки
    m_pan= new wxPanel(this,wxID_ANY);
    // это тоже панель, но наша.
    // помещаем ее нна панель m_pan и задаем указатель на главный фрейм
    dp=new Draw(m_pan,this);
    // это окошко для текста. Тоже помещаем на m_pan
    tc =  new wxTextCtrl(m_pan, -1, wxT(""), wxPoint(200, 10),wxSize(200,50));
    // статус-бар будет внизу окна
    sb=CreateStatusBar();
    sb->SetStatusText(wxString(wxT("что-то напишем и здесь")));
};


void MyWin::OnLoad(wxCommandEvent& event){
    // специальный класс для листания файлов
    wxFileDialog * openFileDialog = new wxFileDialog(this);
    // если все открывается, выберем имя файла
    // Только имя!!!
    if (openFileDialog->ShowModal() == wxID_OK){
        // Что выбрали, то и будет именем файла
        // Запоминаем в строку
        wxString fileName = openFileDialog->GetPath();
        // Загружаем содержимое в окно текста
        tc->LoadFile(fileName);
        // Теперь нужно получить данные из файла
        // Создаем объект - файловый поток
        wxFileInputStream input(fileName);
        // Чтобы он работал как текстовый файл, превращаем его в поток-текст
        wxTextInputStream intext(input);
        int  x1,y1,x2,y2;
        // "обычным" образом считываем данные
        intext>>x1>>y1>>x2>>y2;
        // Это были координаты
        a.x = x1;
        a.y = y1;
        b.x = x2;
        b.y = y2;
        // А еще можно сделать поток из строки
        // но к работе окна это отношения не имеет
        wxString a;
        // В строку записали текст
        a<<wxT("123 17 89 12.5");
        // превратили в поток
        wxStringInputStream st(a);
        // превратили в поток-текст
        wxTextInputStream in(st);
        int a1,a2,a3;
        float w;
        // получили данные
        in>>a1>>a2>>a3>>w;
        // Это нужно для перерисвки окна, когда будем рисовать фигуру
        dp->Refresh();
    }
    
};

void MyWin::OnQuit(wxCommandEvent& event){
    Close(true);
};

// Конструктор нашего Draw
Draw::Draw(wxPanel *parent, MyWin *fr):wxPanel(parent, -1,wxPoint(50,50),wxSize(100,100),wxBORDER_SUNKEN){
    // подключили панель к событиям рисования
    Connect(wxEVT_PAINT,wxPaintEventHandler(Draw::OnPaint));
    mn = fr;
};

// Свободная функция рисования прямоугольника
// Для рисования есть абстрактный класс wxDC
// У него много разных наследников
// Самый простой wxPaintDC
// Но мы сделаем функцию для всех наследников wxDC
void DrRec(wxPoint a, wxPoint b, wxDC * dc){
    dc->DrawRectangle(a, wxSize (abs(a.x-b.x),abs(a.y-b.y)));
};

// Функция OnPaint() сработает при любом рисовании окна:
// первое рисование, сложил-разложили
// или вызов функции Refresh()

void Draw::OnPaint(wxPaintEvent& event){
    // положили планшет wxPaintDC на нашу панель
    wxPaintDC dc(this);
    // Установили цвет заливки
    dc.SetBrush(wxBrush(wxColour(255,0,0)));
    // передали свободной функции координаты и указатель на планшет
    DrRec(mn->a,mn->b,&dc);
};

// запуск окна
IMPLEMENT_APP(Begin)

bool Begin::OnInit()
{
    MyWin *wind=new MyWin(wxT("Begin.."));
    wind->Show(true);
    return true;
};

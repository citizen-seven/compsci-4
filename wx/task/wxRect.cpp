#include <wx/wx.h>
#include <wx/file.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/sstream.h>
#include <wx/string.h>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Begin: public wxApp {
public:
    virtual bool OnInit();
};

class Draw;
class MyWin;

class Figure {
protected:
    wxColour color;
public:
    Figure(char _color);
    virtual void draw(wxDC* dc);
};

void Figure::draw(wxDC* dc) {
    assert(0);
}

Figure::Figure(char _color) {
    switch (_color) {
        case 'r':
            color = wxColour(255, 0, 0);
            break;
        case 'g':
            color = wxColour(0, 255, 0);
            break;
        case 'b':
            color = wxColour(0, 0, 255);
            break;
        default:
            assert(0);
    }
}

class Rectangle: public Figure {
    wxPoint a;
    wxPoint b;
    Rectangle();
public:
    Rectangle(int a_x, int a_y, int b_x, int b_y, char _color):
    Figure(_color), a(a_x, a_y), b(b_x, b_y) {};
    void draw(wxDC* dc);
};

void Rectangle::draw(wxDC* dc) {
    assert(dc);
    dc->SetBrush(wxBrush(color));
    dc->DrawRectangle(a, wxSize(abs(a.x-b.x), abs(a.y-b.y)));
}

class Circle: public Figure {
    wxPoint a;
    int rad;
    Circle();
public:
    Circle(int a_x, int a_y, int _rad, char _color):
    Figure(_color), a(a_x, a_y), rad(_rad) {};
    void draw(wxDC* dc);
};

void Circle::draw(wxDC* dc) {
    assert(dc);
    dc->SetBrush(wxBrush(color));
    dc->DrawCircle(a, rad);
}

class Triangle: public Figure {
    wxPoint a;
    wxPoint b;
    wxPoint c;
public:
    Triangle(int a_x, int a_y, int b_x, int b_y, int c_x, int c_y, char _color):
    Figure(_color), a(a_x, a_y), b(b_x, b_y), c(c_x, c_y) {};
    void draw(wxDC* dc);
};

void Triangle::draw(wxDC* dc) {
    assert(dc);
    dc->SetBrush(wxBrush(color));
    int lenC = sqrt(pow((a.x - b.x),2) + pow((a.y-b.y), 2));
    int lenB = sqrt(pow((a.x - c.x),2) + pow((a.y-c.y), 2));
    int lenA = sqrt(pow((c.x - b.x),2) + pow((c.y-b.y), 2));
    if (lenA + lenB <= lenC || lenB + lenC <= lenA || lenA + lenC <= lenB) {
        throw string("Incorrect triangle sides\n");
    }
    wxPoint point_array[3] = {a, b, c};
    dc->DrawPolygon(3, point_array);
    
}

class MyWin:public wxFrame {
    wxMenuBar *menubar; // полоска для меню
    wxMenu *file, *im; // менюшка  на полоске
    wxMenuItem *load, *quit; // открывалка  файла
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
    vector< Figure* > figure_array;
    // Функция закрытия окна
    void OnQuit(wxCommandEvent& event);
    // Загрузка файла с данными
    void OnLoad(wxCommandEvent& event);
};

// класс для рисования
// наследник wxPanel
class Draw: public wxPanel {
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
MyWin::MyWin(const wxString& title):
wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1200,650)) {
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
    m_pan = new wxPanel(this, wxID_ANY);
    // это тоже панель, но наша.
    // помещаем ее нна панель m_pan и задаем указатель на главный фрейм
    dp = new Draw(m_pan, this);
    // это окошко для текста. Тоже помещаем на m_pan
    tc =  new wxTextCtrl(m_pan, -1, wxT(""), wxPoint(850, 20),wxSize(300,300));
    // статус-бар будет внизу окна
    sb = CreateStatusBar();
    sb->SetStatusText(wxString(wxT("Программа, которая рисует фигуры")));
}


void MyWin::OnLoad(wxCommandEvent& event) {
    // специальный класс для листания файлов
    wxFileDialog * openFileDialog = new wxFileDialog(this);
    // если все открывается, выберем имя файла
    // Только имя!!!
    if (openFileDialog->ShowModal() == wxID_OK) {
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
        // "обычным" образом считываем данные
        while (!figure_array.empty()) {
            Figure* fig = figure_array.back();
            figure_array.pop_back();
            assert(fig);
            delete fig;
        }
        while (1) {
            char type = 0;
            intext >> type;
            if (!type) break;
            switch (type) {
                case 'r': {
                    int a_x = 0;
                    int a_y = 0;
                    int b_x = 0;
                    int b_y = 0;
                    char color = 0;
                    intext >> a_x >> a_y >> b_x >> b_y >> color;
                    figure_array.push_back(new Rectangle(a_x, a_y, b_x, b_y, color));
                    break;
                }
                case 'c': {
                    int a_x = 0;
                    int a_y = 0;
                    int rad = 0;
                    char color = 0;
                    intext >> a_x >> a_y >> rad >> color;
                    figure_array.push_back(new Circle(a_x, a_y, rad, color));
                    break;
                }
                case 't': {
                    int a_x = 0;
                    int a_y = 0;
                    int b_x = 0;
                    int b_y = 0;
                    int c_x = 0;
                    int c_y = 0;
                    char color = 0;
                    intext >> a_x >> a_y >> b_x >> b_y >> c_x >> c_y >> color;
                    figure_array.push_back(new Triangle(a_x, a_y, b_x,
                                    b_y, c_x, c_y, color ));
                        break;       
                }
            }
        }
        // Это нужно для перерисвки окна, когда будем рисовать фигуру
        dp->Refresh();
    }
}

void MyWin::OnQuit(wxCommandEvent& event) {
    Close(true);
}

// Конструктор нашего Draw
Draw::Draw(wxPanel *parent, MyWin *fr):
wxPanel(parent, -1, wxPoint(0,0), wxSize(800,600), wxBORDER_SUNKEN) {
    // подключили панель к событиям рисования
    Connect(wxEVT_PAINT, wxPaintEventHandler(Draw::OnPaint));
    mn = fr;
}

// Функция OnPaint() сработает при любом рисовании окна:
// первое рисование, сложил-разложили
// или вызов функции Refresh()

void Draw::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    for (vector<Figure*>::iterator it = mn->figure_array.begin();
            it != mn->figure_array.end(); ++it) {
        try {
            (*it)->draw(&dc);
        } catch (string err) {
            cout << "Error: " << err;
        }
    }
}

// запуск окна
IMPLEMENT_APP(Begin)

bool Begin::OnInit() {
    MyWin *wind = new MyWin(wxT("Figures"));
    wind->Show(true);
    return true;
}

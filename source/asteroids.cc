#include <cmath>
#include <ctime>
#include <iostream>
#include <cstring>

#include "window.h"
#include "digit7.h"
#include "GUI.h"

#define GAP 20

class MainWindow : public Window
{
public:
    MainWindow() {}
    ~MainWindow() {}

    void OnCreate();
    void OnDraw(Context *cr);
    void OnSizeChanged();
    bool OnKeyPress(uint64_t value);
    bool OnTimeout();
    void AdjustControls();
    void SetFps();

private:
    RGB         m_foreground;
    Digit7      *fps1, *fps2, *fps3;
};

void MainWindow::OnDraw(Context *cr)
{
	std::cout << "MainWindow::OnDraw()" << std::endl;

    // зальем прямоугольник окна цветом фона
    cr->SetColor(m_backColor);
    cr->FillRectangle(Point(0,0), GetInteriorSize());
}

void MainWindow::OnCreate()
{
    // начальные цвета
    m_foreground = RGB(1.0,1.0,1.0);
    SetBackColor(RGB(0.0, 0.0, 0.0));

    Point pt(20,20);
    Rect r(20,40);

    fps1 = new Digit7(0);
    fps1->SetColor(m_foreground);
    AddChild(fps1, pt, r);

    fps2 = new Digit7(1);
    fps2->SetColor(m_foreground);
    AddChild(fps2, pt + Point(30, 0), r);

    fps3 = new Digit7(0);
    fps3->SetColor(m_foreground);
    AddChild(fps3, pt + Point(50, 0), r);

	// AdjustControls();
	SetFps();
    CreateTimeout(this,1000);

    // фокус ввода
    CaptureKeyboard(this);
}

void MainWindow::OnSizeChanged()
{
	std::cout << "MainWindow::OnSizeChanged()" << std::endl;

    // AdjustControls();
}

bool MainWindow::OnKeyPress(uint64_t keyval)
{
    if(keyval == 'q')
    {
        DeleteMe();
    }
    else if(keyval == 'p' || keyval == 'P')
    {
        theGUI->Print();
    }
    return true;
}

bool MainWindow::OnTimeout()
{
	std::cout << "MainWindow::OnTimeout()" << std::endl;

	SetFps();
	ReDraw();
    return true;
}

void MainWindow::SetFps()
{
	time_t ct = time(NULL);
    struct tm *t = localtime(&ct);
    fps1->SetDigit(t->tm_hour/10);
    fps2->SetDigit(t->tm_hour%10);
    fps3->SetDigit(t->tm_min/10);
}

// функция main
int main(int argc, char **argv)
{
    MainWindow *pWindow = new MainWindow;

    int res = Run(argc, argv, pWindow, 800, 800);

    delete pWindow;

    return res;
}

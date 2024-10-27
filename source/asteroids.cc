#include <cmath>
#include <ctime>
#include <iostream>
#include <cstring>

#include "window.h"
#include "digit7.h"
#include "mesh.h"
#include "gameobject.h"
#include "GUI.h"

#define GAP 20
#define FPS 30.0
#define DT 1.0 / FPS

#define PLAYER_SPEED 150

int getDigitAtPos(int number, int pos)
{
    std::string str = std::to_string(std::abs(number));
    int ndig = str.length();
    if (pos > 0 && pos <= ndig) {
        return str.at(pos-1) - '0';
    } else {
        return 0;
    }
    
}

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
    void SetScore();

private:
    RGB         m_foreground;
    Digit7      *fps1, *fps2, *fps3;
    uint32_t m_totalFrames;
    float m_dt;

    GameObject *m_player;
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

    fps2 = new Digit7(0);
    fps2->SetColor(m_foreground);
    AddChild(fps2, pt + Point(30, 0), r);

    fps3 = new Digit7(0);
    fps3->SetColor(m_foreground);
    AddChild(fps3, pt + Point(60, 0), r);

	// AdjustControls();
	SetScore();
    CreateTimeout(this, 1000.0 / FPS);

    // фокус ввода
    CaptureKeyboard(this);

    // fps
    m_totalFrames = 0;
    float m_dt = 1.0 / FPS;

    // Игрок
    m_player = new GameObject(this, Point(400, 400), Rect(30, 30), MeshType::Player);
}

void MainWindow::OnSizeChanged()
{
	std::cout << "MainWindow::OnSizeChanged()" << std::endl;

    // AdjustControls();
}

bool MainWindow::OnKeyPress(uint64_t keyval)
{
    if(keyval == 'a')
    {
        m_player->Rotate(-0.1);
    }
    else if(keyval == 'd')
    {
        m_player->Rotate(0.1);
    }
    else if (keyval == 'w') 
    {
        m_player->SetVelocity(m_player->GetForward() * Point(PLAYER_SPEED, PLAYER_SPEED));
    }
    return true;
}

bool MainWindow::OnTimeout()
{
	std::cout << "MainWindow::OnTimeout()" << std::endl;
    m_totalFrames++;

    m_player->Update(DT);

    std::cout << m_player->GetForward().GetX() << " " << m_player->GetForward().GetY() << "\n";
    std::cout << m_player->GetPosition().GetX() << " " << m_player->GetPosition().GetY() << "\n";

	SetScore();
	ReDraw();
    return true;
}

void MainWindow::SetScore()
{
	time_t ct = time(NULL);
    struct tm *t = localtime(&ct);
    if (m_totalFrames >= 1000) {
        fps1->SetDigit(9);
        fps2->SetDigit(9);
        fps3->SetDigit(9);
    } else if (m_totalFrames >= 100) {
        fps1->SetDigit(getDigitAtPos(m_totalFrames, 1));
        fps2->SetDigit(getDigitAtPos(m_totalFrames, 2));
        fps3->SetDigit(getDigitAtPos(m_totalFrames, 3));
    } else if (m_totalFrames >= 10) {
        fps2->SetDigit(getDigitAtPos(m_totalFrames, 1));
        fps3->SetDigit(getDigitAtPos(m_totalFrames, 2));
    } else {
        fps3->SetDigit(getDigitAtPos(m_totalFrames, 1));
    }
}

// функция main
int main(int argc, char **argv)
{
    MainWindow *pWindow = new MainWindow;

    int res = Run(argc, argv, pWindow, 800, 800);

    delete pWindow;

    return res;
}

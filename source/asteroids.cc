#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>
#include <cstring>

#include "window.h"
#include "digit7.h"
#include "mesh.h"
#include "gameobjects.h"
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
    void SetHealth();

private:
    RGB         m_foreground;
    uint32_t m_totalFrames;
    float m_dt;

    // показатели счета
    Digit7 *num1, *num2, *num3;

    // показатели здоровья игрока
    Mesh *hp1, *hp2, *hp3;

    // игрок
    Player *m_player;

    // астероиды
    std::vector<Asteroid*> m_asteroids;
};

void MainWindow::OnDraw(Context *cr)
{
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

    num1 = new Digit7(0);
    num1->SetColor(m_foreground);
    AddChild(num1, pt, r);

    num2 = new Digit7(0);
    num2->SetColor(m_foreground);
    AddChild(num2, pt + Point(30, 0), r);

    num3 = new Digit7(0);
    num3->SetColor(m_foreground);
    AddChild(num3, pt + Point(60, 0), r);

	// AdjustControls();
	SetScore();
    CreateTimeout(this, 1000.0 / FPS);

    // фокус ввода
    CaptureKeyboard(this);

    // fps
    m_totalFrames = 0;
    float m_dt = 1.0 / FPS;

    // Игрок
    m_player = new Player(this, Point(400, 400), Rect(40, 40), 15, MeshType::Player);
    m_player->SetDrag(0.99);

    // Показатели здоровья
    hp1 = new Mesh(MeshType::Player);
    AddChild(hp1, pt + Point(-7, 55), Rect(35, 35));

    hp2 = new Mesh(MeshType::Player);
    AddChild(hp2, pt + Point(23, 55), Rect(35, 35));

    hp3 = new Mesh(MeshType::Player);
    AddChild(hp3, pt + Point(53, 55), Rect(35, 35));

    // Астероиды
    for (int i = 0; i < 10; i++)
    {   
        MeshType meshes[] = {MeshType::Asteroid1, MeshType::Asteroid2, MeshType::Asteroid3};
        int randS = rand()%30 + 30;
        Asteroid *asteroid = new Asteroid(this, Point(80 * i, 0), Rect(randS, randS), randS * 0.4, meshes[i % 3]);    
        asteroid->SetVelocity(Point(std::rand() % 200 - 100, std::rand() % 200 - 100));
        m_asteroids.push_back(asteroid);
    }
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
    m_totalFrames++;

    // Обновить игрока
    m_player->Update(DT);

    // Обновить астероиды
    for (int i = 0; i < m_asteroids.size(); i++)
    {
        m_asteroids[i]->Update(DT);
        m_asteroids[i]->Rotate(0.02 * -(i % 2 == 0));
    }

    // Просчитать столкновения
    GameObject *asteroids[m_asteroids.size()];
    for (int i = 0; i < m_asteroids.size(); i++)
    {
       asteroids[i] = m_asteroids[i];
    }
    m_player->EvaluateCollisions(asteroids, m_asteroids.size());

    // Обновить данные на экране
	SetScore();
    SetHealth();
	ReDraw();
    return true;
}

void MainWindow::SetScore()
{
	time_t ct = time(NULL);
    struct tm *t = localtime(&ct);
    if (m_totalFrames >= 1000) {
        num1->SetDigit(9);
        num2->SetDigit(9);
        num3->SetDigit(9);
    } else if (m_totalFrames >= 100) {
        num1->SetDigit(getDigitAtPos(m_totalFrames, 1));
        num2->SetDigit(getDigitAtPos(m_totalFrames, 2));
        num3->SetDigit(getDigitAtPos(m_totalFrames, 3));
    } else if (m_totalFrames >= 10) {
        num2->SetDigit(getDigitAtPos(m_totalFrames, 1));
        num3->SetDigit(getDigitAtPos(m_totalFrames, 2));
    } else {
        num3->SetDigit(getDigitAtPos(m_totalFrames, 1));
    }
}

void MainWindow::SetHealth()
{
    if (m_player->GetHealth() == 3)
    {
        hp1->SetActive(false);
    }

    if (m_player->GetHealth() == 2)
    {
        hp2->SetActive(false);
    }

    if (m_player->GetHealth() == 1)
    {
        hp3->SetActive(false);
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

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
#include "text.h"

#define GAP 20
#define FPS 30.0
#define DT  1.0 / FPS

#define PLAYER_SPEED      150
#define BULLET_SPEED      350
#define MIN_ASTEROID_SIZE 30

enum GameState
{
    Start,
    InGame,
    End
};

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
    bool OnLeftMouseButtonClick(const Point &Position);
    bool OnTimeout();
    void AdjustControls();
    void SetScore();
    void SetHealth();

    void CreateStartScreen();
    void CreateGame();
    void CreateEndGameScreen();

    void OnNotify(Window *child, uint32_t type, const Point &position);

private:
    RGB       m_foreground;
    uint32_t  m_score;
    float     m_dt;

    Digit7   *num1, *num2, *num3;         // показатели счета
    Mesh     *hp1, *hp2, *hp3;            // показатели здоровья игрока
    Player   *m_player;                   // игрок
    std::vector<Asteroid*> m_asteroids;   // астероиды
    std::vector<Bullet*>   m_bullets;     // пули

    GameState m_state;
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
    SetFrameColor(RGB(1, 1, 1));

    CreateStartScreen();

    CaptureKeyboard(this);
    CreateTimeout(this, 1000.0 / FPS);
}

void MainWindow::OnSizeChanged()
{
	std::cout << "MainWindow::OnSizeChanged()" << std::endl;
}

bool MainWindow::OnKeyPress(uint64_t keyval)
{
    switch(m_state)
    {
    case GameState::Start:
        if(keyval ==  GDK_KEY_space)
        {
            CreateGame();
        }
        break;

    case GameState::InGame:
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
        break;
    }
    
    return true;
}

bool MainWindow::OnTimeout()
{
    switch(m_state)
    {
    case GameState::Start:
        // Обновить астероиды
        for (int i = 0; i < m_asteroids.size(); i++)
        {
            m_asteroids[i]->Update(DT);
        }

        break;

    case GameState::InGame:
        // Обновить игрока
        m_player->Update(DT);

        // Обновить астероиды
        for (int i = 0; i < m_asteroids.size(); i++)
        {
            if (!m_asteroids[i]->GetMesh())
            {
                delete m_asteroids[i];
                m_asteroids.erase(m_asteroids.begin() + i);
                continue;
            }

            m_asteroids[i]->Update(DT);
        }

        // Обновить пули
        for (int i = 0; i < m_bullets.size(); i++)
        {
            m_bullets[i]->Update(DT);
            if (!m_bullets[i]->GetMesh())
            {
                delete m_bullets[i];
                m_bullets.erase(m_bullets.begin() + i);
            }
            
        }

        // Просчитать столкновения
        int n = m_asteroids.size();
        GameObject *asteroids[n];
        for (int i = 0; i < n; i++)
        {
            asteroids[i] = m_asteroids[i];
        }
        m_player->EvaluateCollisions(asteroids, n);

        for (int i = 0; i < m_bullets.size(); i++)
        {
            m_bullets[i]->EvaluateCollisions(asteroids, n);
        }

        // Обновить данные на экране
        SetScore();
        SetHealth();

        break;
    }
   
	ReDraw();
    CaptureKeyboard(this);
    return true;
}

bool MainWindow::OnLeftMouseButtonClick(const Point &Position)
{  
    switch(m_state)
    {
    case GameState::Start:
        break;

    case GameState::InGame:
        Bullet *bullet = new Bullet(this, m_player->GetPosition(), Rect(10, 10), 5.0, MeshType::Bullet);
        bullet->SetVelocity(m_player->GetForward() * Point(BULLET_SPEED, BULLET_SPEED));
        m_bullets.push_back(bullet);

        break;
    }
    return true;
}

void MainWindow::CreateStartScreen()
{
    m_state = GameState::Start;
    DeleteAllChildren();
    m_bullets.clear();
    m_asteroids.clear();
    SetFrameWidth(1);

    // текст названия
    Text *text1 = new Text("ASTEROIDS");
    text1->SetTextColor(RGB(1, 1, 1));
    text1->SetFont("Monospace", 80, 1, -1);
    text1->SetAlignment(TEXT_ALIGNH_CENTER|TEXT_ALIGNV_CENTER);
    text1->SetWrap(true);
    text1->SetFrameWidth(1);
    text1->SetFrameColor(RGB(1, 1, 1));
    AddChild(text1, Point(0, 0),Rect(800, 200));

    // текст начала игры
    Text *text2 = new Text("PRESS SPACE TO START");
    text2->SetTextColor(RGB(1, 1, 1));
    text2->SetFont("Monospace", 40, 1, -1);
    text2->SetAlignment(TEXT_ALIGNH_CENTER|TEXT_ALIGNV_CENTER);
    text2->SetWrap(true);
    text2->SetFrameWidth(1);
    text2->SetFrameColor(RGB(1, 1, 1));
    AddChild(text2, Point(0, 600),Rect(800, 200));

    // Астероиды
    for (int i = 0; i < 10; i++)
    {   
        MeshType meshes[] = {MeshType::Asteroid1, MeshType::Asteroid2, MeshType::Asteroid3};
        int randS = rand()%50 + 50;
        Asteroid *asteroid = new Asteroid(this, Point(80 * i, 0), Rect(randS, randS), randS * 0.4, meshes[i % 3]);    
        asteroid->SetVelocity(Point(std::rand() % 200 - 100, std::rand() % 200 - 100));
        m_asteroids.push_back(asteroid);
    }
}

void MainWindow::CreateGame()
{
    m_state = GameState::InGame;
    DeleteAllChildren();
    m_bullets.clear();
    m_asteroids.clear();
    SetFrameWidth(0);

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

    // Счет
    m_score = 0;
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
        int randS = rand()%50 + 50;
        Asteroid *asteroid = new Asteroid(this, Point(80 * i, 0), Rect(randS, randS), randS * 0.4, meshes[i % 3]);    
        asteroid->SetVelocity(Point(std::rand() % 200 - 100, std::rand() % 200 - 100));
        m_asteroids.push_back(asteroid);
    }
}

void MainWindow::SetScore()
{
	time_t ct = time(NULL);
    struct tm *t = localtime(&ct);
    if (m_score >= 1000) {
        num1->SetDigit(9);
        num2->SetDigit(9);
        num3->SetDigit(9);
    } else if (m_score >= 100) {
        num1->SetDigit(getDigitAtPos(m_score, 1));
        num2->SetDigit(getDigitAtPos(m_score, 2));
        num3->SetDigit(getDigitAtPos(m_score, 3));
    } else if (m_score >= 10) {
        num2->SetDigit(getDigitAtPos(m_score, 1));
        num3->SetDigit(getDigitAtPos(m_score, 2));
    } else {
        num3->SetDigit(getDigitAtPos(m_score, 1));
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

void MainWindow::OnNotify(Window *child, uint32_t type, const Point &position)
{
    switch (type)
    {
    case GameEvents::AsteroidDestroyed:
        m_score += 5;
        double s = child->GetSize().GetWidth();
        double x = child->GetPosition().GetX() + s * 0.5;
        double y = child->GetPosition().GetY() + s * 0.5;
        double childSize = s * 0.7;
        if (childSize > MIN_ASTEROID_SIZE)
        {
            for (int i = 0; i < 2; i++)
            {
                MeshType meshes[] = {MeshType::Asteroid1, MeshType::Asteroid2, MeshType::Asteroid3};
                Asteroid *asteroid = new Asteroid(this, Point(x, y), Rect(childSize, childSize), childSize * 0.4, meshes[((int)childSize + i) % 3]);    
                asteroid->SetVelocity(Point(std::rand() % 200 - 100, std::rand() % 200 - 100));
                m_asteroids.push_back(asteroid);
            }
        }
        break;
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

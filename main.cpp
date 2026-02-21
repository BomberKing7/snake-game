#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#include <stdlib.h>
int main()
{
  srand(time(NULL));
  int score = 2;
  int x = 600, y = 600;
  int l = x / 20, h = y / 20, s = l * h;
  Texture f, snake;
  f.loadFromFile("1C287A28A8FA629EB9BA26E681747360.png");
  snake.loadFromFile("3ADC4910740B791205C9BDA8EAFFEA22.png");
  bool snakeornot[s] = {0};
  int xt, yt;
  xt = rand() % l;
  yt = rand() % h;
  int position = xt + (l)*yt;
  snakeornot[position] = 1;

  RectangleShape field[s], sn[s], cube(Vector2f(20, 20));
  int vect = 1;
  for (int i = 0, ll = 0, hh = 0; hh < h; i++)
  {

    field[i] = cube;
    field[i].setTexture(&f);
    field[i].move(ll * 20, hh * 20);
    sn[i] = cube;
    sn[i].setTexture(&snake);
    sn[i].move(ll * 20, hh * 20);
    ll++;
    if (ll % l == 0)
    {
      ll = 0;
      hh++;
    }
  }
  bool goal[s] = {0};
  int zel[s];
  zel[0] = position;

  xt = rand() % s;
  while (snakeornot[xt] == 1)
  {
    xt = rand() % s;
  }
  goal[xt] = 1;

  RenderWindow window(VideoMode(x, y), "snake");

  bool death = 0;
  while (window.isOpen())
  {
    Event e;
    while (window.pollEvent(e))
    {
    }
    if (Keyboard::isKeyPressed(Keyboard::O))
    {
      window.close();
    }
    if (Keyboard::isKeyPressed(Keyboard::Up) && vect != 4)
    {
      vect = 2;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) && vect != 2)
    {
      vect = 4;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left) && vect != 3)
    {
      vect = 1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right) && vect != 1)
    {
      vect = 3;
    }

    sleep(milliseconds(150));
    switch (vect)
    {
    case 1:
    {
      snakeornot[position] = 0;
      if (position % l == 0)
      {
        position += l - 1;
      }
      else
      {
        position--;
      }
      if (snakeornot[position] == 1)
      {
        death = 1;
      }
      snakeornot[position] = 1;
      break;
    }
    case 2:
    {
      snakeornot[position] = 0;
      if (position / l == 0)
      {
        position += (h - 1) * l;
      }
      else
      {
        position -= (l);
      }
      if (snakeornot[position] == 1)
      {
        death = 1;
      }
      snakeornot[position] = 1;
      break;
    }
    case 3:
    {
      snakeornot[position] = 0;
      if (position % l == l - 1)
      {
        position -= l - 1;
      }
      else
      {
        position++;
      }
      if (snakeornot[position] == 1)
      {
        death = 1;
      }
      snakeornot[position] = 1;
      break;
    }
    case 4:
    {
      snakeornot[position] = 0;
      if (position / l == h - 1)
      {
        position -= (h - 1) * l;
      }
      else
      {
        position += (l);
      }
      if (snakeornot[position] == 1)
      {
        death = 1;
      }
      snakeornot[position] = 1;
      break;
    }
    default:;
    }
    if (death)
    {
      cout << "  you lost   " << endl;
      window.close();
    }

    if (goal[position] == 1)
    {
      score++;
      goal[position] = 0;
      xt = rand() % s;
      while (snakeornot[xt] == 1 || zel[xt] == 1)
      {
        xt = rand() % s;
      }
      goal[xt] = 1;
    }

    for (int i = 0; i < score; i++)
    {
      snakeornot[zel[i]] = 0;
    }
    for (int i = s - 1; i >= 0; i--)
    {
      zel[i] = zel[i - 1];
    }
    zel[0] = position;
    for (int i = 0; i < score; i++)
    {
      snakeornot[zel[i]] = 1;
    }

    window.clear();
    for (int i = 0; i < s; i++)
    {
      window.draw(field[i]);
      if (snakeornot[i] == 1 || goal[i] == 1)
      {
        window.draw(sn[i]);
      }
    }
    window.display();
  }
}

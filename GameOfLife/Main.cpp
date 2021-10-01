#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Map.h"

using namespace sf;

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game of life");

	Map map = Map();

	bool pause = false;
	bool mouseClick = false;
	bool stop = false;

	RectangleShape rectangle = RectangleShape(Vector2f(float(CELL_SIZE), float(CELL_SIZE)));
	rectangle.setFillColor(Color::Red);

	Clock clock;
	float time = 0;

	Vector2i mousePosition;

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen() && !stop)
	{
		time += clock.getElapsedTime().asSeconds();
		clock.restart();

		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
			{
				std::cout << "User close the game" << std::endl;
				window.close();
			}

			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				window.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			{
				if (pause)
				{
					pause = false;
					std::cout << "Resumed" << std::endl;
				}
				else
				{
					pause = true;
					std::cout << "Paused" << std::endl;
				}
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && pause)
				mouseClick = true;

		}

		if (!stop)
		{
			if (mouseClick)
			{
				mousePosition = Mouse::getPosition(window);

				if (map.cur_map[mousePosition.y / CELL_SIZE][mousePosition.x / CELL_SIZE] == 1)
					map.cur_map[mousePosition.y / CELL_SIZE][mousePosition.x / CELL_SIZE] = 0;
				else
					map.cur_map[mousePosition.y / CELL_SIZE][mousePosition.x / CELL_SIZE] = 1;

				window.clear(Color::Black);

				for (int i = 0; i < WINDOW_HEIGHT / CELL_SIZE; i++)
				{
					for (int j = 0; j < WINDOW_WIDTH / CELL_SIZE; j++)
					{
						if (map.cur_map[i][j] == 1)
						{
							rectangle.setPosition(float(j * CELL_SIZE), float(i * CELL_SIZE));
							window.draw(rectangle);
						}
					}
				}

				window.display();
				mouseClick = false;
			}

			if (!pause)
			{
				//generate life
				if (time >= TACT)
				{
					stop = !map.updateMap();	//function return answer about changes (if have changes that true)
					window.clear(Color::Black);

					for (int i = 0; i < WINDOW_HEIGHT / CELL_SIZE; i++)
					{
						for (int j = 0; j < WINDOW_WIDTH / CELL_SIZE; j++)
						{
							if (map.cur_map[i][j] == 1)
							{
								rectangle.setPosition(float(j * CELL_SIZE), float(i * CELL_SIZE));
								window.draw(rectangle);
							}
						}
					}

					time = 0;
					window.display();
				}

			}

			//The last message
			if(stop) std::cout << "Life has stabilize or all populations died." << std::endl;
		}
		
	}

	return 0;
}
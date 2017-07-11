#include "game.h"



game::game()
{
	window.create(sf::VideoMode(800, 600), "Ping!", sf::Style::Close);
	window.setFramerateLimit(60);

	//// Load fonts from file ////
	if (!font1.loadFromFile("Data/Fonts/pixel.ttf"))
	{
		std::cout << "Error: Font1 loadFromFile failed." << std::endl;
	}
	if (!font.loadFromFile("Data/Fonts/SFPixelate.ttf"))
	{
		std::cout << "Error: Font loadFromFile failed." << std::endl;
	}

	if (!music.openFromFile("Data/Audio/ping_music01.ogg"))
	{
		std::cout << "fucked" << std::endl;
	}
	music.setLoop(true);
}

game::~game()
{
}

void game::runGame()
{
	music.play();
	state = MENU;
	/*
		The GameLoop - stops when state == ENDS
			Switches GameStates
	*/
	while (state != END)
	{
		switch (state)
		{
		case MENU:
			menu();
			break;

		case GAME:
			play();
			break;

		case OPTIONS:
			options();
			break;

		case OVER:
			over();
			break;

		case END:
			break;
		}

		
	}
}

void game::menu()
{
	//// Text Setups ////
	sf::Text titleText("Ping", font1, 72);
	titleText.setOrigin(std::round(titleText.getLocalBounds().width / 2), 20);
	titleText.setPosition((window.getSize().x / 2), 60);
	titleText.setFillColor(sf::Color(245, 147, 51));

	sf::Text subtitleText(" Pong for loners.", font, 12);
	subtitleText.setOrigin(std::round(titleText.getLocalBounds().width / 2), 20);
	subtitleText.setPosition((window.getSize().x / 2), 145);
	subtitleText.setFillColor(sf::Color(245, 147, 51));

	sf::String menuTextString[3] = { "Play", "Options", "Exit" };
	sf::Text menuText(menuTextString[0], font, 28);
	menuText.setOrigin(std::round(menuText.getLocalBounds().width / 2), 20);
	menuText.setPosition((window.getSize().x / 2), 400);
	menuText.setFillColor(sf::Color(245, 147, 51));

	sf::Text toolTip("Press ENTER to select", font, 12);
	toolTip.setOrigin(std::round(toolTip.getLocalBounds().width / 2), 20);
	toolTip.setPosition((window.getSize().x / 2), 440);
	toolTip.setFillColor(sf::Color(245, 147, 51));

	//// Texture Setups ////
	sf::Texture arrow;
	arrow.loadFromFile("Data/Images/menuArrow.png");

	//// Sprites and Rects ////
	sf::Sprite menuArrowLeft(arrow);
	menuArrowLeft.setOrigin(menuArrowLeft.getLocalBounds().width / 2, 4);
	menuArrowLeft.setPosition((window.getSize().x / 2 + 50), 400);

	sf::Sprite menuArrowRight(arrow);
	menuArrowRight.setOrigin(menuArrowRight.getLocalBounds().width / 2, 4);
	menuArrowRight.setPosition((window.getSize().x / 2 - 45), 400);
	menuArrowRight.setScale(-1, 1);

	sf::Texture bg01t;
	bg01t.loadFromFile("Data/Images/01.png");
	sf::Sprite bg01(bg01t);

	//// MENU VARIABLES ////
	int menuSelect = 0;
	
	while (state == MENU)
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				state = END;
				break;

			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					state = END;
				}
				if (evnt.key.code == sf::Keyboard::A)
				{
					if (menuSelect > 0)
					{
						menuSelect -= 1;
					}
				}
				if (evnt.key.code == sf::Keyboard::D)
				{
					if (menuSelect < 2)
					{
						menuSelect += 1;
					}
				}
				if (evnt.key.code == sf::Keyboard::Return)
				{
					if (menuSelect == 0)
					{
						state = GAME;
					}
					else if (menuSelect == 1)
					{
						state = OPTIONS;
					}
					else if (menuSelect == 2)
					{
						state = END;
					}
				}
				break;
			}
		}

		//// Menu Rotate Strings with ARROW KEYS ////
		menuText.setString(menuTextString[menuSelect]);

		//// Drawing Here ////
		window.clear(sf::Color::Black);
		
		window.draw(bg01);
		window.draw(menuText);
		window.draw(titleText);
		window.draw(subtitleText);
		window.draw(toolTip);
		window.draw(menuArrowLeft);
		window.draw(menuArrowRight);

		window.display();
	}
}

void game::play()
{
	Player player1;
	Ball ball1;

	sf::Text scoreText("0", font, 24);
	scoreText.setOrigin(sf::Vector2f(scoreText.getLocalBounds().width / 2, 0));
	scoreText.setPosition(398, 285);
	scoreText.setFillColor(sf::Color(245, 147, 51));
	int score = 0;

	sf::Texture bg01t;
	bg01t.loadFromFile("Data/Images/01.png");
	sf::Sprite bg01(bg01t);

	sf::Texture bg02t;
	bg02t.loadFromFile("Data/Images/02.png");
	sf::Sprite bg02(bg02t);
	bg02.setOrigin(400, 300);
	bg02.setPosition(400, 300);
	bg02t.setSmooth(true);

	sf::Texture bg03t;
	bg03t.loadFromFile("Data/Images/03.png");
	sf::Sprite bg03(bg03t);
	bg03.setOrigin(400, 300);
	bg03.setPosition(400, 300);
	bg03t.setSmooth(true);

	sf::Texture bg04t;
	bg04t.loadFromFile("Data/Images/04.png");
	sf::Sprite bg04(bg04t);
	bg04.setOrigin(400, 300);
	bg04.setPosition(400, 300);
	bg04t.setSmooth(true);

	sf::Texture bg05t;
	bg05t.loadFromFile("Data/Images/05.png");
	sf::Sprite bg05(bg05t);
	bg05.setOrigin(400, 300);
	bg05.setPosition(400, 300);
	bg05t.setSmooth(true);

	sf::Texture bg06t;
	bg06t.loadFromFile("Data/Images/06.png");
	sf::Sprite bg06(bg06t);
	bg06.setOrigin(400, 300);
	bg06.setPosition(400, 300);
	bg06t.setSmooth(true);


	sf::Clock clock1;
	while (state == GAME)
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				state = END;
				break;

			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					state = END;
				}
				if (evnt.key.code == sf::Keyboard::Return)
				{
					state = MENU;
				}
				break;
			}
		}
		//// Updates ////
		player1.update(deltaTime);
		ball1.update(deltaTime, player1.getRect(), score);
		scoreText.setString(std::to_string(score));

		if (ball1.isOver == true)
		{
			scoreOverall = score;
			state = OVER;
		}

		bg02.rotate(deltaTime * 12.0f);
		bg03.rotate(deltaTime * -24.0f);
		bg04.rotate(deltaTime * 12.0f);
		bg05.rotate(deltaTime * -12.0f);

		//// Drawing ////
		window.clear(sf::Color::Black);

		window.draw(bg01);
		window.draw(bg02);
		window.draw(bg03);
		window.draw(bg04);
		window.draw(bg05);
		window.draw(bg06);

		window.draw(scoreText);
		player1.draw(window);
		ball1.draw(window);

		window.display();
		deltaTime = clock1.getElapsedTime().asSeconds();
		clock1.restart();
	}
	
}

void game::options()
{
	sf::Text titleText("Options", font1, 72);
	titleText.setOrigin(std::round(titleText.getLocalBounds().width / 2), 20);
	titleText.setPosition((window.getSize().x / 2), 60);
	titleText.setFillColor(sf::Color(245, 147, 51));

	sf::Text toolTip("Press ENTER to return", font, 12);
	toolTip.setOrigin(std::round(toolTip.getLocalBounds().width / 2), 20);
	toolTip.setPosition((window.getSize().x / 2), 440);
	toolTip.setFillColor(sf::Color(245, 147, 51));

	while (state == OPTIONS)
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				state = END;
				break;

			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Return)
				{
					state = MENU;
				}
				break;
			}
		}

		window.clear(sf::Color(15, 15, 15));

		window.draw(titleText);
		window.draw(toolTip);

		window.display();
	}
}

void game::over()
{
	sf::Text titleText("Final Score", font1, 72);
	titleText.setOrigin(std::round(titleText.getLocalBounds().width / 2), 20);
	titleText.setPosition((window.getSize().x / 2), 60);
	titleText.setFillColor(sf::Color(245, 147, 51));

	sf::Text scoreOverallText("Press ENTER to continue", font, 12);
	scoreOverallText.setOrigin(std::round(scoreOverallText.getLocalBounds().width / 2), 20);
	scoreOverallText.setPosition((window.getSize().x / 2), 440);
	scoreOverallText.setFillColor(sf::Color(245, 147, 51));

	sf::Text score(std::to_string(scoreOverall), font, 26);
	score.setOrigin(std::round(score.getLocalBounds().width / 2), 20);
	score.setPosition(window.getSize().x / 2, 300);
	score.setFillColor(sf::Color(245, 147, 51));
	
	while (state == OVER)
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				state = END;
				break;

			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Return)
				{
					state = MENU;
				}
				break;
			}
		}

		window.clear(sf::Color(15, 15, 15));

		window.draw(scoreOverallText);
		window.draw(titleText);
		window.draw(score);

		window.display();
	}
}
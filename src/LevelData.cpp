#include "LevelData.h"

//The c-tor of level data class
LevelData::LevelData()
{
    m_hearts.resize(LIVES);
    try
    {
        m_hearts[2].loadFromFile("alive hearts.png");
        m_hearts[1].loadFromFile("one dead heart.png");
        m_hearts[0].loadFromFile("two dead hearts.png");
    }
    catch (...)
    {
        std::cerr << "Can't load program files\n";
    }
	m_heartImg.setTexture(m_hearts[0]);
	m_font.loadFromFile("C:/Windows/Fonts/COOPBL.ttf");
}

//This function draws the level's data to the window
void LevelData::draw(sf::RenderWindow& window,const int img)
{
	m_heartImg.setTexture(m_hearts[img - 1]);
	window.draw(m_heartImg);
	window.draw(m_levelText);
	window.draw(m_scoreText);
}

//This function updates the level's data
void LevelData::update(const sf::Vector2f pos, const int currlevel, const int currScore)
{
	m_heartImg.setPosition(10 + abs(pos.x - POSITION_FITTER), 10);
	std::string level = "Level : " + std::to_string(currlevel);//calculating the number of levels
	m_levelText = sf::Text(level, m_font);
	m_levelText.setPosition(420 + abs(pos.x - POSITION_FITTER), 10);
	m_levelText.setFillColor(sf::Color::Black);

	std::string score = "Score : " + std::to_string(currScore);//calculating the score of the level
	m_scoreText = sf::Text(score, m_font);
	m_scoreText.setPosition(800 + abs(pos.x - POSITION_FITTER), 10);
	m_scoreText.setFillColor(sf::Color::Black);
}

//This function shows the result of the current level (win or lose)
void LevelData::showResult(const std::pair<sf::Texture,sf::Texture>& result)
{
	sf::Sprite resultImg(result.first);
    sf::Sprite playButtonImg(result.second);
    playButtonImg.setOrigin(float(result.second.getSize().x/2), float(result.second.getSize().y/2));
    playButtonImg.setPosition(float(result.first.getSize().x/2), float(result.first.getSize().y/1.3));
	sf::RenderWindow resultWindow(sf::VideoMode(result.first.getSize().x, result.first.getSize().y), "!! Result Window !!");

    while (resultWindow.isOpen())
    {
        resultWindow.clear(sf::Color(102,51,0));

        resultWindow.draw(resultImg);
        resultWindow.draw(playButtonImg);

        resultWindow.display();

        for (auto event = sf::Event{}; resultWindow.waitEvent(event); )
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                resultWindow.close();
                exit(0);
            case sf::Event::MouseButtonReleased: //if the user pressed the mouse button
            {
                auto location = resultWindow.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                if (playButtonImg.getGlobalBounds().contains(location))//if the start button is pressed then enter the loop
                {
                    resultWindow.close();
                    break;
                }
            }
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    exit(0);
                if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter)
                {
                    resultWindow.close();
                    break;
                }
            }
        }
    }
}
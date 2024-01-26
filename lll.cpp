#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 5.0f;

class Player {
public:
    Player() {
        player.setSize(sf::Vector2f(20, 20));
        player.setFillColor(sf::Color::Green);
        player.setPosition(WINDOW_WIDTH / 2 - 10, WINDOW_HEIGHT / 2 - 10);
    }

    void update(sf::RenderWindow& window) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move(0, -PLAYER_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move(0, PLAYER_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.move(-PLAYER_SPEED, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.move(PLAYER_SPEED, 0);
        }

        // Ограничение игрока в пределах окна
        sf::Vector2f playerPos = player.getPosition();
        if (playerPos.x < 0) player.setPosition(0, playerPos.y);
        if (playerPos.y < 0) player.setPosition(playerPos.x, 0);
        if (playerPos.x > WINDOW_WIDTH - player.getSize().x) player.setPosition(WINDOW_WIDTH - player.getSize().x, playerPos.y);
        if (playerPos.y > WINDOW_HEIGHT - player.getSize().y) player.setPosition(playerPos.x, WINDOW_HEIGHT - player.getSize().y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(player);
    }

private:
    sf::RectangleShape player;
};

class DoomGame {
public:
    DoomGame() {
        // Загрузка звуковых эффектов
        if (!shotBuffer.loadFromFile("shot.wav")) {
            std::cout << "Failed to load shot.wav" << std::endl;
        }
        shotSound.setBuffer(shotBuffer);

        // Загрузка музыки
        if (!music.openFromFile("doom_music.ogg")) {
            std::cout << "Failed to load doom_music.ogg" << std::endl;
        }
        music.setLoop(true);
        music.play();
    }

    void run() {
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Doom-style Game");
        Player player;

        // Основной игровой цикл
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                    // Выстрел
                    shotSound.play();
                }
            }

            // Обновление игры
            player.update(window);

            // Очистка экрана
            window.clear();

            // Отрисовка игровых объектов
            player.draw(window);

            // Обновление экрана
            window.display();
        }
    }

private:
    sf::SoundBuffer shotBuffer;
    sf::Sound shotSound;
    sf::Music music;
};

int main() {
    DoomGame game;
    game.run();

    return 0;
}

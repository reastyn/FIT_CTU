//
// Created by pjahoda on 29.4.18.
//

#include "View/Player.hpp"
#include <iostream>

namespace RG{
    namespace View {


        Player::Player() {
            clock = sf::Clock();
            player = sf::RectangleShape(sf::Vector2f(91.0f, 91.0f));
            animation = std::make_shared<Animation>("/usr/share/RG/assets/graphics/objects/characters/player.png", 91, 91, 12,
                                                    40.0f);
            this->time = 0;
            this->windowX = 0;
            this->windowY = 0;
            animation->setPosition(sf::Vector2f(this->x, this->y));
            animation->goToFrame(0);
            animation->startAnimation();
        }

        void Player::SetPosition(float x, float y) {
            this->x = x;
            this->y = y;
            animation->setPosition(sf::Vector2f(this->x*(windowX/1920), this->y*(windowY/1080)));
        }

        void Player::Update(float time) {
            if (time != 0) {
                this->time = time;
            }
            this->animation->update(this->clock.getElapsedTime().asMilliseconds());
        }

        void Player::UpdatePlayer(float absoluteX, float absoluteY) {
            if (absoluteX != this->x || absoluteY != this->y) {
                this->animation->setRotation(this->GetAngle(this->relativeMoveX,this->relativeMoveY));
                this->SetPosition(absoluteX,absoluteY);
                this->Update(time);
            }
        }

        float Player::GetAngle(float moveX, float moveY) {
            float angle = 0;
            if (moveY > 0 || moveY < 0) {
                if (moveY < 0) {
                    angle = 0;
                } else {
                    angle = 180;
                }

                if (moveX > 0) {
                    float tmp = 1;
                    if (angle == 180) {
                        tmp = -1;
                    }
                    angle += 45 * tmp;
                } else if (moveX < 0) {
                    float tmp = 1;
                    if (angle == 180) {
                        tmp = -1;
                    }
                    angle -= 45 * tmp;
                }
                if (angle < 0) { angle += 360.0; }
                if (angle > 360) { angle -= 360.0; }
            } else {
                if (moveX > 0) {
                    angle = 90;
                } else if (moveX < 0) {
                    angle = 270;
                }
            }
            return angle;
        }

        void Player::DrawPlayer(sf::RenderTarget &target) {
            this->animation->draw(target, sf::RenderStates());
        }

        void Player::SetPlayerScale(float windowWidth, float windowHeight){
            if(windowWidth != windowX || windowHeight != windowY) {
                float scaleX = (windowWidth / 20) / this->animation->getSize().x;
                float scaleY = (windowWidth / 20) / this->animation->getSize().x;
                this->animation->setScale(scaleX, scaleY);
                windowX = windowWidth;
                windowY = windowHeight;
            }
        }

        void RG::View::Player::SetPlayerSpeedX(float x) {
            this->relativeMoveX = x;
        }

        void RG::View::Player::SetPlayerSpeedY(float y) {
            this->relativeMoveY = y;
        }

        float RG::View::Player::GetPlayerSpeedX() {
            return this->relativeMoveX;
        }

        float RG::View::Player::GetPlayerSpeedY() {
            return this->relativeMoveY;
        }
    }
}

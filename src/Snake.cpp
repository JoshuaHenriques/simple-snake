#include "Snake.hpp"
#include "GamePlay.hpp"
#include <iostream>

Snake::Snake() : m_body(std::list<sf::Sprite>(4)) {
    // m_body.end() gets end of list + 1 so we use --
    m_head = ++m_body.rend();
    m_tail = m_body.rbegin();
}

Snake::~Snake() {

}

void Snake::Init(const sf::Texture& head, const sf::Texture& body, const sf::Texture& tail, const sf::Texture& texture) {
    float x = 32.f;
    // int cnt = 0;
    // makes the snake appear as a continuous body
    for (auto& piece : m_body) {
        piece.setTexture(texture);
        piece.setPosition({x, 32.f});
        x += 16.f;
    }

    // for(auto& piece : m_body) {
    //     switch (cnt) {
    //         case 0:
    //             piece.setTexture(tail);
    //             piece.setPosition({x, 32.f});
    //             break;
    //         case 1:
    //             piece.setTexture(body);
    //             piece.setPosition({x, 32.f});
    //             break;
    //         case 2:
    //             piece.setTexture(body);
    //             piece.setPosition({x, 32.f});
    //             break;
    //         case 3:
    //             piece.setTexture(head);
    //             piece.setPosition({x, 32.f});
    //             break;
    //         default:
    //             break;
    //     }
    //     x += 16.f;
    //     cnt++;
    // }

    // sf::Sprite headTexture;
    // sf::Sprite bodyTexture;
    // sf::Sprite body2Texture;
    // sf::Sprite tailTexture;
    
    // headTexture.setTexture(head);
    // headTexture.setPosition({80.f, 32.f});

    // bodyTexture.setTexture(body);
    // bodyTexture.setPosition({64.f, 32.f});

    // body2Texture.setTexture(body);
    // body2Texture.setPosition({48.f, 32.f});

    // tailTexture.setTexture(tail);
    // tailTexture.setPosition({32.f, 32.f});
    
    // m_body.push_front(tailTexture);
    // m_body.push_front(body2Texture);
    // m_body.push_front(bodyTexture);
    // m_body.push_front(headTexture);
}

void Snake::Move(const sf::Vector2f& direction) {
    // std::cout << "direction.x: " << direction.x << " direction.y: " << direction.y << std::endl;
    sf::Vector2f thisPosition = m_head->getPosition();
    // std::cout << "thisPosition.x: " << thisPosition.x << " thisPosition.y: " << thisPosition.y << std::endl;
    sf::Vector2f lastPosition = thisPosition; 
    // std::cout << "lastPosition.x: " << lastPosition.x << " lastPosition.y: " << lastPosition.y << std::endl;
    m_head->setPosition(thisPosition + direction);
    // std::cout << "m_head->getPosition().x: " << m_head->getPosition().x << " m_head->getPosition().y: " << m_head->getPosition().y << std::endl;
    
    for(auto piece = m_body.rbegin(); piece != m_body.rend(); ++piece) {
        if (m_head != piece) {
            thisPosition = piece->getPosition();
            // std::cout << "piece->getPosition().x: " << piece->getPosition().x << " piece->getPosition().y: " << piece->getPosition().y << std::endl;

            piece->setPosition(lastPosition);
            lastPosition = thisPosition;
        }
    }
    // m_tail->setPosition(m_head->getPosition() + direction);
    // m_head = m_tail;
    // ++m_tail;

    // if (m_tail == m_body.end()) m_tail = m_body.begin();
}

bool Snake::IsOn(const sf::Sprite &other) const {
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

bool Snake::IsIn(const float x, const float y) const {
    bool flag = false;

    for(auto piece = m_body.rbegin(); piece != m_body.rend(); ++piece) {
        if (m_head != piece) {
            flag = piece->getGlobalBounds().intersects({x, y, 16, 16});
            if(flag) {
                std::cout << "Flag: " << flag << std::endl;
                break;
            }
        }
    }

    return flag;
}

bool Snake::IsSelfIntersecting() const {
    bool flag = false;

    for(auto piece = m_body.rbegin(); piece != m_body.rend(); ++piece) {
        if (m_head != piece) {
            flag = IsOn(*piece);
            if(flag) break;
        }
    }

    return flag;
}

void Snake::Grow(const sf::Vector2f& direction) {
    sf::Sprite newPiece;
    newPiece.setTexture(*(std::next(m_body.begin())->getTexture()));
    newPiece.setPosition(m_head->getPosition());
    // right before the head
    m_head->setPosition(m_head->getPosition() + direction);
    m_head.base() = m_body.insert(--m_head.base(), newPiece);
    // m_head = m_body.insert(++m_head, newPiece);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(auto& piece: m_body) {
        target.draw(piece);
    }
}
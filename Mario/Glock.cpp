#include "stdafx.h"
#include "Glock.h"


void Glock::InitSprite()
{
    if (this->texture.loadFromFile("resources/models/muzzle_flash.png"))
    {
        this->sprite.setTexture(this->texture);
        this->sprite.setScale(0.19f, 0.19f);
    }
    else
    {   
        throw("Error loading bullet sprite\n");
    }

}
Glock::Glock(Texture& texture, Sprite& sprite,
    const bool isEquipped, unsigned magazine_size, float damage) : Item(&texture, &sprite, isEquipped)
{
    this->addAnimation("Shooting_left", 8.f, 0, 1, 0, 1, 64, 64);
    this->addAnimation("Shooting_right", 8.f, 0, 3, 0, 3, 64, 64);
    this->addAnimation("Shooting_up", 8.f, 0, 0, 0, 0, 64, 64);
    this->addAnimation("Shooting_down", 8.f, 1, 2, 1, 2, 64, 64);


    this->addAnimation("IDLE_gun", 8.f, 0, 2, 0, 2, 64, 64);
    this->addAnimation("WALK_RIGHT_gun", 8.f, 0, 3, 8, 3, 64, 64);
    this->addAnimation("WALK_LEFT_gun", 8.f, 0, 1, 8, 1, 64, 64);
    this->addAnimation("WALK_UP_gun", 8.f, 0, 0, 8, 0, 64, 64);
    this->addAnimation("WALK_DOWN_gun", 8.f, 1, 2, 8, 2, 64, 64);

    this->InitSprite();

    this->magazine_size = magazine_size;
    this->magazine_size_Max = magazine_size;
    this->damage = damage;
}



const int Glock::getMagazineSize() const
{
    return this->magazine_size;
}

void Glock::reload(unsigned int& magazineQuantity)
{
    
    if (magazineQuantity > 0)
    {

         int amount = this->magazine_size_Max - this->magazine_size;
         if (amount < magazineQuantity)
         {
                
                this->magazine_size += amount;
               magazineQuantity -= amount;
         }
            
         else
         {
                this->magazine_size += magazineQuantity;
                magazineQuantity = 0;
         }
            
          
    }
    
}

void Glock::reduceAmmo(const int* amount)
{
    if (!amount)
    {
        this->magazine_size--;
    }
    else
        this->magazine_size -= *amount;

}

void Glock::updateBulletPosition(const Vector2f& GunPosition)
{
    this->sprite.setPosition(GunPosition.x + this->sprite.getGlobalBounds().width + 20.f, GunPosition.y + 66.f);
}

void Glock::renderShooting(RenderTarget& target)
{
    static Clock shootingTimer;

    if (shootingTimer.getElapsedTime().asSeconds() < 0.5f)
    {
        this->bullets.push(&this->sprite);

        if (!this->bullets.empty() && this->bullets.top())
        {
            target.draw(*this->bullets.top());
        }
    }
    else
    {
        if (!this->bullets.empty() && this->bullets.top())
        {
            this->bullets.pop();
        }
        shootingTimer.restart();
    }
}


void Glock::updateUseAnimation(const float& dt, unsigned int Status, const Vector2f& GunPos)
{
    if (this->magazine_size > 0)
    {
        this->updateBulletPosition(GunPos);

        // Set the origin to the center of the sprite
        this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2, this->sprite.getLocalBounds().height / 2);

        static float degrees = 0.f;
        this->sprite.setRotation(degrees - degrees);

        switch (Status)
        {
        case 0:
            this->animationComponent->Play("Shooting_left", dt);
            this->sprite.setPosition(this->sprite.getPosition().x - 70.f, this->sprite.getPosition().y);
            degrees = 180.f;
            break;
        case 1:
            this->animationComponent->Play("Shooting_right", dt);
            degrees = 0.f;
            break;
        case 2:
            this->animationComponent->Play("Shooting_up", dt);
            this->sprite.setPosition(5000.f, 5000.f);
            degrees = 90.f;
            break;
        case 3:
            this->animationComponent->Play("Shooting_down", dt);
            this->sprite.setPosition(this->sprite.getPosition().x - 29.f, this->sprite.getPosition().y + 25.f);
            degrees = 270.f;
            break;
        }

        this->sprite.setRotation(degrees);
    }
    else
        this->magazine_size = 0;
}

void Glock::updateMovementAnimation(const short MovementStatus, const float &dt)
{
    switch (MovementStatus)
    {
        //Idle
    case 0:
        this->animationComponent->Play("IDLE_gun", dt);
        break;
        //UP movement
    case 1:
        this->animationComponent->Play("WALK_UP_gun", dt);
        break;


        //down movement
    case 2:
        this->animationComponent->Play("WALK_DOWN_gun", dt);
        break;


        //left movement
    case 3:
        this->animationComponent->Play("WALK_LEFT_gun", dt);
        break;

        //right movement
    case 4:
        this->animationComponent->Play("WALK_RIGHT_gun", dt);
        break;
    }
}

const float Glock::getDamage() const
{
    return this->damage;
}

void Glock::setDamage(const float damage)
{
    this->damage = damage;
}




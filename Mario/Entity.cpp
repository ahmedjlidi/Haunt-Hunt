#include "stdafx.h"
#include "Entity.h"


void Entity::InitVariables()
{
    this->movementcomponent = NULL;
    this->animationcomponent = NULL;

   
}

void Entity::InitKeyTime()
{
    this->keytime = 0.f;
    this->keytimeMax = 11.f;
}



void Entity::CreateSprite(Texture& texture)
{
    this->sprite.setTexture(texture);
}

void Entity::LoadTextures()
{

    
}

Entity::Entity()
{
    
    this->InitVariables();
    this->LoadTextures();
    this->InitKeyTime();
}

Entity::~Entity()
{
    delete this->movementcomponent;

    delete this->animationcomponent;

    delete this->hitboxcomponent;

    delete this->attributecomponent;

}



const Vector2f& Entity::getPosition()
{
    if (this->hitboxcomponent)
        return this->hitboxcomponent->getPosition();

    return this->sprite.getPosition();
}

const Vector2f Entity::getCenter() const noexcept
{
    if (this->hitboxcomponent)
        return
        this->hitboxcomponent->getPosition() +
        sf::Vector2f
        (
            this->hitboxcomponent->GlobalBounds().width / 2.f,
            this->hitboxcomponent->GlobalBounds().height / 2.f
        );

    return
        this->sprite.getPosition() +
        sf::Vector2f
        (
            this->sprite.getGlobalBounds().width / 2.f,
            this->sprite.getGlobalBounds().height / 2.f
        );
}

const Vector2u Entity::getGridPosition(const unsigned grid_size) const
{
    if (this->hitboxcomponent)
        return Vector2u
        (
            static_cast<unsigned>(this->hitboxcomponent->getPosition().x) / grid_size,
            static_cast<unsigned>(this->hitboxcomponent->getPosition().y / grid_size)
        );

    return Vector2u
    (
        static_cast<unsigned>(this->sprite.getPosition().x) / grid_size,
        static_cast<unsigned>(this->sprite.getPosition().y / grid_size)
    );
}

const FloatRect Entity::getGlobalbounds()const 
{
    if (this->hitboxcomponent)
        return this->hitboxcomponent->GlobalBounds();

    return this->sprite.getGlobalBounds();
}

const FloatRect Entity::getNextPositionBounds(const float &dt) const
{
    if (this->hitboxcomponent && this->movementcomponent)
    {
        return this->hitboxcomponent->getNextPosition(
            this->movementcomponent->getVelocity(),dt );
    }
    return FloatRect();
}

const Vector2f& Entity::getVelocity() const
{
    return this->movementcomponent->getVelocity();
}

const bool Entity::HP_is_0() const
{
    return this->healthcomponent->getHp() <= 0.f;
}

float& Entity::getHp()
{
    return this->healthcomponent->getHp();
}

void Entity::SetSpawnPosition(const float x, const float y)
{
    if (this->hitboxcomponent)
        this->hitboxcomponent->setPosition(Vector2f(x, y));
    else
        this->sprite.setPosition(x, y);
}

void Entity::updateHP(const float damage)
{
    this->healthcomponent->updateHp(damage);
}

void Entity::restorHp()
{
    this->healthcomponent->restoreHp();
}

const int Entity::CurrentRoom() const
{
    return 0;
}



bool Entity::getKeyTime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

void Entity::updateKeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
        this->keytime += 100.f * dt;
}



void Entity::createMovement(const float MaxVelocity, const float acceleration, const float deceleration)
{
	this->movementcomponent = new MoveMentComponent(this->sprite, MaxVelocity, acceleration,deceleration);
}

void Entity::createAnimationComponent(Texture& texture_sheet)
{
    this->animationcomponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitBoxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
    this->hitboxcomponent = new HitBoxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createAttributeComponent(const unsigned level)
{
    this->attributecomponent = new AttributeComponent(level);
}

void Entity::createInventoryComponent()
{
    this->invertorycomponent = new InventoryComponent();
}

void Entity::createHealthComponent(float hp, Vector2f size, Vector2f position)
{
    this->healthcomponent = new HealthComponent(hp, size, position);
}



void Entity::renderHPBar(RenderTarget& target)
{
    this->healthcomponent->render(target);
}

void Entity::stopVelocity(const short stop_velocity)
{
    this->movementcomponent->stopVelocity(stop_velocity);
}

void Entity::slowVelocity(const float offset)
{
    this->movementcomponent->slowVelocity(offset);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
    if (this->movementcomponent )
    {
        this->movementcomponent->move(dir_x, dir_y,dt);
    }
}

void Entity::update(const float& dt)
{
    if (this->movementcomponent)
    {
        this->movementcomponent->update(dt);
    }
    
    this->hitboxcomponent->update(dt);
}

void Entity::render(RenderTarget* target)
{
  
}


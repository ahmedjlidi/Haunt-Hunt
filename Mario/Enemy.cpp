#include "stdafx.h"
#include "Enemy.h"





Enemy::Enemy(float x, float y, Texture& texture_sheet, const bool patrol,
    const Vector2f PatrolPositionEnd, const Vector2f PatrolPositionStart,
    float hp, Vector2f interestRange,float damage, short type, const map<string, Sound>& sounds,const FloatRect& update_range)
      : patrol(patrol), damage(damage),
    PatrolPositionEnd(PatrolPositionEnd), PatrolPositionStart(PatrolPositionStart),updateRange(update_range)
    , hp(hp), interestRange(interestRange), type(type), sounds(sounds), audio(this->sounds["patrol"], 1500.f, 100.f)
{
    this->die = false;
    this->reachPatrolEnd = false;
    this->reachedPlayer = false;

    this->range.setSize(interestRange);
    this->range.setFillColor(Color::Transparent);
    this->range.setOutlineColor(Color::Red);
    this->range.setOutlineThickness(2.f);

    this->CurrentHP = this->hp;

    this->createHealthComponent(this->hp, Vector2f(60.f, 10.f), PatrolPositionStart);
	
}



void Enemy::deductHp(const float damage)
{
    this->healthcomponent->updateHp(-damage);
}

void Enemy::setState(ENEMYSTATES state)
{
    this->state = state;
}

void Enemy::ChangePatrolDirection()
{
    this->PatrolPositionEnd.x *= -1;
}

const bool Enemy::HasDied() const noexcept
{
    return this->healthcomponent->HP_is_0();
}

const int Enemy::getHp() const
{
    return this->healthcomponent->getHp();
}

const int Enemy::getState()
{
    return this->state;
}

const int Enemy::getType() const
{
    return this->type;
}

const float Enemy::getDamage() const
{
    return this->damage;
}



void Enemy::PlayAnimation(const string name, const float& dt)
{

}

void Enemy::updateState(const Vector2f playerPos)
{
    
    range.setPosition(playerPos.x - range.getSize().x / 2.f, playerPos.y - range.getSize().y / 2.f);

    if (range.getGlobalBounds().intersects(this->sprite.getGlobalBounds())
        )
    {
        this->setState(ENEMYSTATES::CHASE);
    }
    else if (this->healthcomponent->getHp() > 0.f && this->state != ENEMYSTATES::BEING_HIT)
        this->setState(ENEMYSTATES::PATROL);

    if (!this->die)
    {
        this->delay.restart();
    }
        
}


void Enemy::updatePatrolState(const float& dt, Entity& playerEntitty)
{
    if (!reachPatrolEnd)
    {
        bool reachedX = false;
        bool reachedY = false;
        if (this->getPosition().x > this->PatrolPositionEnd.x && !reachPatrolEnd)
        {
            if (this->getPosition().x - 1 <= this->PatrolPositionEnd.x)
            {
                reachPatrolEnd = true;
            }
            else
                this->move(-1, 0.f, dt);
        }
        else if (this->getPosition().x < this->PatrolPositionEnd.x && !reachPatrolEnd)
        {
            if (this->getPosition().x + 1 >= this->PatrolPositionEnd.x)
            {
                reachPatrolEnd = true;
            }
            else
                this->move(1, 0.f, dt);
        }
        else
            reachedX = true;

        if (this->getPosition().y > this->PatrolPositionEnd.y)
        {
            if (this->getPosition().y <= this->PatrolPositionEnd.y)
            {
                reachedY = true;
            }
            else
                this->move(0.f, -1.f, dt);
        }
        else if (this->getPosition().y < this->PatrolPositionEnd.y)
        {
            if (this->getPosition().y >= this->PatrolPositionEnd.y)
            {
                reachedY = true;
            }
            else
                this->move(0.f, +1.f, dt);
        }
        else
            reachedY = true;

        if (reachedX && reachedY)
        {
            reachPatrolEnd = true;
        }


        if (abs(this->getVelocity().x) <= 6.f)
        {
            if (this->Collisiondelay.getElapsedTime().asSeconds() >= 1.f)
            {
                if (this->CollisionCounter % 2 == 0)
                {
                    this->PatrolPositionEnd.x = this->getPosition().x + abs(this->PatrolPositionEnd.x);
                }
                else
                    this->PatrolPositionEnd.x = this->PatrolPositionStart.x - abs(this->PatrolPositionEnd.x);
                Collisiondelay.restart();
                ++CollisionCounter;
            }
        }
        else
        {
            Collisiondelay.restart();
        }
    }
    else
    {
        if (this->getPosition().x > this->PatrolPositionStart.x)
        {
            if (this->getPosition().x - 1 <= this->PatrolPositionStart.x)
            {
                reachPatrolEnd = false;
            }
            else
                this->move(-1, 0.f, dt);
        }
        else if (this->getPosition().x < this->PatrolPositionStart.x)
        {
            if (this->getPosition().x + 1 >= this->PatrolPositionStart.x)
            {
                reachPatrolEnd = false;
            }
            else
                this->move(1, 0.f, dt);
        }
        else
            reachPatrolEnd = false;


    }

    switch (this->movementcomponent->GetMovementStatus())
    {
        //Idle
    case 0:
        this->animationcomponent->Play("IDLE", dt);

        break;
        //UP movement
    case 1:
        if (abs(playerEntitty.getPosition().x >= this->getPosition().x))
        {
            this->animationcomponent->Play("WALK_RIGHT", dt);
        }
        else
            this->animationcomponent->Play("WALK_LEFT", dt);
        break;
        //down movement
    case 2:
        this->animationcomponent->Play("WALK_DOWN", dt);
        break;
        //left movement
    case 3:
        this->animationcomponent->Play("WALK_LEFT", dt);
        break;
        //right movement
    case 4:
        this->animationcomponent->Play("WALK_RIGHT", dt);
        break;

    }

    this->audio.update(playerEntitty.getPosition(), this->getPosition());

    if (this->healthcomponent->getHp() <= 0.f)
    {
        this->die = true;
    }

}


void Enemy::updateChaseState(const float& dt, Entity& playerEntitty)
{
    bool ReachedX = false;
    bool ReachedY = false;
    FloatRect AttackBounds = this->getGlobalbounds();

    if (AttackBounds.intersects(playerEntitty.getGlobalbounds())
        && playerEntitty.getGlobalbounds().top + playerEntitty.getGlobalbounds().width - 32
        >= this->getGlobalbounds().top)
    {
        reachedPlayer = true;
    }
    else

    {
        reachedPlayer = false;

        if (this->getPosition().x - 1 >= playerEntitty.getPosition().x
            && !reachedPlayer && !ReachedX)
        {
            ReachedX = false;
            this->move(-1, 0.f, dt);
        }
        else if (this->getPosition().x + 1 <= playerEntitty.getPosition().x
            && !reachedPlayer && !ReachedX)
        {
            ReachedX = false;
            this->move(1, 0.f, dt);
        }
        else
            ReachedX = true;

        if (this->getPosition().y - 1 >= playerEntitty.getPosition().y && !reachedPlayer && !ReachedY)
        {
            ReachedY = false;
            this->move(0.f, -1.f, dt);
        }
        else if (this->getPosition().y + 1 <= playerEntitty.getPosition().y && !reachedPlayer && !ReachedY)
        {
            ReachedY = false;
            this->move(0.f, 1.f, dt);
        }
        else
            ReachedY = true;

        if (ReachedY && ReachedX)
        {
            reachedPlayer = true;
        }
        else
        {
            ReachedY = false;
            ReachedX = false;
            reachedPlayer = false;
        }


        if (abs(this->getVelocity().x) <= 6.f && !reachedPlayer)
        {
            if (this->Collisiondelay.getElapsedTime().asSeconds() >= 1.f)
            {
                if (this->getPosition().y < playerEntitty.getPosition().y)
                {
                    this->move(0.f, -1.f, dt);
                }
                else
                    this->move(0.f, -1.f, dt);
            }
        }
        else
        {
            Collisiondelay.restart();
        }
    }

    switch (this->movementcomponent->GetMovementStatus())
    {
        //Idle
    case 0:
        this->animationcomponent->Play("ATTACK_LEFT", dt);
        this->state = ENEMYSTATES::ATTACK;
        break;
        //UP movement
    case 1:
        if (abs(playerEntitty.getPosition().x >= this->getPosition().x))
        {
            this->animationcomponent->Play("CHASE_RIGHT", dt);
        }
        else
            this->animationcomponent->Play("CHASE_LEFT", dt);
        break;
        //down movement
    case 2:
        if (abs(playerEntitty.getPosition().x >= this->getPosition().x))
        {
            this->animationcomponent->Play("CHASE_RIGHT", dt);
        }
        else
            this->animationcomponent->Play("CHASE_LEFT", dt);
        break;
        //left movement
    case 3:
        this->animationcomponent->Play("CHASE_LEFT", dt);
        break;
        //right movement
    case 4:

        this->animationcomponent->Play("CHASE_RIGHT", dt);
        break;

    }

    this->audio.update(playerEntitty.getPosition(), this->getPosition());

    if (this->healthcomponent->getHp() <= 0.f)
    {
        this->die = true;
        return;
    }
}



void Enemy::updateDeathState(const float& dt)
{
    if (this->delay.getElapsedTime().asSeconds() <= 1.5f)
    {

        this->animationcomponent->Play("DIE", dt);
    }
    else
    {
        this->state = ENEMYSTATES::ENEMY_DIE;
    }
}

void Enemy::renderHPBar(RenderTarget& target)
{
    Vector2f* position = new Vector2f(this->getPosition().x + 10.f, this->getPosition().y - 15.f);
    if (this->state == ENEMYSTATES::BEING_HIT)
    {
        this->hpBarDisplayTime.restart();     
    }
    if (this->hpBarDisplayTime.getElapsedTime().asSeconds() <= 1.5f)
        this->healthcomponent->render(target, position);
}


void Enemy::update(const float& dt, Entity& playerEntitty)
{
    this->updateRange.left = playerEntitty.getPosition().x - (this->updateRange.width / 2.f);
    this->updateRange.top = playerEntitty.getPosition().y - (this->updateRange.getSize().y / 2.f);


    if (this->state != ENEMYSTATES::ENEMY_DIE)
    {
        this->updateState(playerEntitty.getPosition());
        if (this->updateRange.intersects(this->getGlobalbounds()))
        {
            Entity::update(dt);
            if (this->state == ENEMYSTATES::PATROL)
            {
                this->audio.setSound(this->sounds["patrol"]);

                this->updatePatrolState(dt, playerEntitty);


            }
            else if (!this->die && (this->state == ENEMYSTATES::BEING_HIT || this->state == ENEMYSTATES::CHASE))
            {
                this->updateChaseState(dt, playerEntitty);
                this->audio.setSound(this->sounds["chase"]);

            }
            if (this->die)
            {
                this->updateDeathState(dt);
                this->audio.stop();

            }
        }
        else
        {
             delay.restart();
             Collisiondelay.restart();
             hpBarDisplayTime.restart();
        }
    }
}

 

void Enemy::render(RenderTarget& target, Shader* shader, Vector2f position, const bool showHitBox)
{
    if (this->updateRange.intersects(this->getGlobalbounds()))
    {
        if (shader)
        {

            shader->setUniform("hasTexture", true);
            shader->setUniform("lightPos", position);

            target.draw(this->sprite, shader);


        }
        else
            target.draw(this->sprite);
        this->renderHPBar(target);

        if (this->hitboxcomponent && showHitBox)
        {
            this->hitboxcomponent->render(&target);
            target.draw(this->range);
        }
    }
    
}

void Enemy::stopSound(const string name)
{
    this->audio.stop();
}

void Enemy::renderSoundRange(const string name, RenderTarget& target)
{
    this->audio.render(target);
}

void Enemy::playSound(const string name, const Vector2f& playerPos)
{
    this->audio.update(playerPos, this->getPosition());
}






















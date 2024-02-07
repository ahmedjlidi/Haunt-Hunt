#include "stdafx.h"
#include "Player.h"


void Player::InitVariables()
{

}

void Player::InitComponent(Texture& texture_sheet)
{
   //movement component
   this->createMovement(600.f, 2100.f, 1450.f);
   //animation component
   this->createAnimationComponent(texture_sheet);
   this->animationcomponent->AddAnimation("IDLE", 8.f, 9, 2, 9, 2, 64, 64);
   this->animationcomponent->AddAnimation("WALK_RIGHT", 8.f, 9, 3, 17, 3, 64, 64);
   this->animationcomponent->AddAnimation("WALK_LEFT", 8.f, 9, 1, 17, 1, 64, 64);
   this->animationcomponent->AddAnimation("WALK_UP", 8.f, 9, 0, 17, 0, 64, 64);
   this->animationcomponent->AddAnimation("WALK_DOWN", 8.f, 10, 2, 17, 2, 64, 64);
   //hitbox component
   this->createHitBoxComponent(this->sprite, 32, 24, 90, 64);
   //attribute component
   this->createAttributeComponent(0);
   //inventory component
   this->createInventoryComponent();
   this->createHealthComponent(250.f, Vector2f(300.f, 50.f), Vector2f(70.f, 40.f));
}

void Player::InitKeyTime()
{
    this->keytime = 0.f;
    this->keytimeMax = 15.f;
}

Player::Player(float x, float y, Texture &texture_sheet)
{
    this->InitVariables();
    this->SetSpawnPosition(x, y);
    this->InitComponent(texture_sheet);
    this->textureSheet = texture_sheet;
    this->InitKeyTime();
}

Player::~Player()
{

}

//inventory===============================================
void Player::addItem(const short ItemId)
{
    if(ItemId == ITEMS::GLOCK)
        this->invertorycomponent->addItem(ItemId, &this->textureSheet, &this->sprite);
    else if (ItemId == ITEMS::HERB)
    {
        this->invertorycomponent->addItem(ITEMS::HERB, &this->textureSheet, &this->sprite);
    }
    else if (ItemId == ITEMS::MAGAZINE)
    {
        this->invertorycomponent->addItem(ItemId, &this->textureSheet, &this->sprite);
    }
    else if (ItemId == ITEMS::KEY)
    {
        this->invertorycomponent->addItem(ItemId, &this->textureSheet, &this->sprite);
    }

    else if (ItemId == ITEMS::SPECIAL_KEY)
    {
        this->invertorycomponent->addItem(ItemId, &this->textureSheet, &this->sprite);
    }
    else if (ItemId == ITEMS::CRYSTAL)
    {
        this->invertorycomponent->addItem(ItemId, &this->textureSheet, &this->sprite);
    }
    else if (ItemId == ITEMS::MED_KIT)
    {
        this->invertorycomponent->addItem(ItemId, &this->textureSheet, &this->sprite);
    }
    else if (ItemId == ITEMS::UPGRADE_KIT)
    {
        this->invertorycomponent->addItem(ItemId, &this->textureSheet, &this->sprite);
    }


}


void Player::EquipItem(const short ItemId)
{
    this->invertorycomponent->EquipItem(ItemId);
}

Texture& Player::getCurrentItemTexture()
{
    return this->invertorycomponent->getCurrentItemTexture();
}

Texture& Player::getItemTexture(const short id) const
{
    return this->invertorycomponent->getItemTexture(id);
}

Item* Player::CurrentItem()
{
    return this->invertorycomponent->CurrentItem();
}

Item* Player::getItemInInventory(const short id) const
{
    return this->invertorycomponent->getItemInInventory(id);
}


const short Player::CurrentEquippedITemID()
{
    return this->invertorycomponent->CurrentEquippedItemID();
}

const bool Player::CurrentitemIsInInventory()
{
    return this->invertorycomponent->CurrentItemisInInventory();
}

const bool Player::itemIsInInventory(const short id)
{
    return this->invertorycomponent->itemisInInventory(id);
}
//==========================================================


const int Player::CurrentRoom() const
{
    return this->currentRoom;
}

void Player::setRoom(const short room)
{
    this->currentRoom = room;
}

const int Player::getState() const
{
    return this->state;
}

void Player::ChangepawnPosition(Vector2f position)
{
    float x = position.x, y = position.y;
    this->SetSpawnPosition(x,y);
}


void Player::update(const float& dt, const Vector2f& PlayerPos, const Vector2f& MousePos, const bool busy)
{
    this->updateKeytime(dt);
    //updating items that should disable or movement or has speccial animation here
    if (this->CurrentEquippedITemID() == ITEMS::GLOCK && this->invertorycomponent->CurrentItem() != nullptr)
    {
        this->state = PlayerState::HOLDING_GUN;
        if (this->getVelocity().x == 0 && this->getVelocity().y == 0.f 
            && Mouse::isButtonPressed(Mouse::Left) && !busy)
        {
            this->invertorycomponent->CurrentItem()->updateUseAnimation(dt, this->movementcomponent->getShootingStatus(PlayerPos
                , MousePos), PlayerPos);
            

            static Clock delay;

            if (delay.getElapsedTime().asSeconds() >= 0.5f && this->invertorycomponent->CurrentItem()->getMagazineSize() > 0)
            {
                this->state = PlayerState::SHOOTING;
                this->invertorycomponent->CurrentItem()->reduceAmmo();
                delay.restart();
            }
        }
        else
        {
            
            if (this->invertorycomponent->CurrentItem())
            {
                Entity::update(dt);
                this->invertorycomponent->CurrentItem()->updateMovementAnimation(this->movementcomponent->GetMovementStatus(),
                    dt);

                static Clock delay; 
                static bool reload;
                if (Keyboard::isKeyPressed(Keyboard::R)
                    &&this->invertorycomponent->CurrentItem()->getMagazineSize() < 15
                    && this->invertorycomponent->getItemInInventory(ITEMS::MAGAZINE)->getQuantity() > 0
                    && this->state != PlayerState::RELOADING)
                {
                    reload = true;
                    delay.restart();
                    this->state = PlayerState::RELOADING;
                }
                    
                
                if (reload && delay.getElapsedTime().asSeconds() >= 2.f && this->invertorycomponent->getItemInInventory(ITEMS::MAGAZINE))
                {
                    delay.restart();
                    reload = false;
                    
                    this->invertorycomponent->CurrentItem()->reload(this->invertorycomponent->getItemInInventory(ITEMS::MAGAZINE)->getQuantity());
                }
                
            } 
        }
    }

   
    
    //updating flashlight animations
    else
    {
        this->state = PlayerState::RUNNING;
        Entity::update(dt);
        switch (this->movementcomponent->GetMovementStatus())
        {
            //Idle
        case 0:
            this->animationcomponent->Play("IDLE", dt);
            this->state = PlayerState::Inactive;
            break;
            //UP movement
        case 1:
            this->animationcomponent->Play("WALK_UP", dt);
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
    }
}




void Player::render(RenderTarget* target, Shader* shader, Vector2f position, const bool busy, const bool showHitBox)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", position);//position is player center

        target->draw(this->sprite, shader);
        
    }
    else
        target->draw(this->sprite);

    if (this->hitboxcomponent && showHitBox)
    {
        this->hitboxcomponent->render(target);

    }
   
    //rendering muzzle flash if player shoots
    if (this->invertorycomponent->CurrentEquippedItemID() == ITEMS::GLOCK
        && Mouse::isButtonPressed(Mouse::Left) && 
        this->invertorycomponent->CurrentItem() != nullptr && this->getVelocity().x == 0.f &&
        this->getVelocity().y == 0.f && !busy && this->invertorycomponent->CurrentItem()->getMagazineSize() > 0
        )
    {
        this->invertorycomponent->CurrentItem()->renderShooting(*target);
    }

    
}







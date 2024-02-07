#include "stdafx.h"
#include "TileMap.h"



void TileMap::clear()
{
    if (!this->Map.empty())
    {
        for (int x = 0; x < this->Map.size(); x++)
        {
            for (int y = 0; y < this->Map[x].size(); y++)
            {
                for (int z = 0; z < this->Map[x][y].size(); z++)
                {
                    for (size_t k = 0; k < this->Map[x][y][z].size(); k++)
                    {
                        delete this->Map[x][y][z][k];
                        this->Map[x][y][z][k] = nullptr;
                    }
                    this->Map[x][y][z].clear();
                }
                this->Map[x][y].clear();
            }
            this->Map[x].clear();
        }
        this->Map.clear();
    }

}

TileMap::TileMap(float Grid_Size, unsigned width, unsigned height,
    Texture &texture) : texture(texture)

{
    this->GridSizef = Grid_Size;
    this->GridSize = static_cast<unsigned>(this->GridSizef);
    this->Maxsize.x = width;
    this->Maxsize.y = height;
    this->WorldMaxSize.x = static_cast<float>(width) * GridSize;
    this->WorldMaxSize.y = static_cast<float>(height) * GridSize;

    this->layers = 1;
    this->DamagingTile = false;

    
    
    this->Map.resize(this->Maxsize.x, std::vector< std::vector< std::vector<Tile*> > >());
    for (int x = 0; x < this->Maxsize.x; x++)
    {
        for (int y = 0; y < this->Maxsize.y; y++)
        {
            this->Map[x].resize(this->Maxsize.y, std::vector< std::vector<Tile*> >());

            for (int z = 0; z < this->layers; z++)
            {
                this->Map[x][y].resize(this->layers, std::vector<Tile*>());
            }
        }
    }

    this->collisionbox.setSize(Vector2f(this->GridSize, this->GridSizef));
    this->collisionbox.setFillColor(Color(241, 38, 38, 100));
    this->collisionbox.setOutlineThickness(-1.f);
    this->collisionbox.setOutlineColor(Color::Black);

    this->fromX = 0;
    this->toX = 0;
    this->fromY = 0;
    this->toY= 0;
    this->layer = 0;

    this->font.loadFromFile("resources/Fonts/Montserrat-Regular.ttf");
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(1.f);
    text.setCharacterSize(15.f);


}


TileMap::~TileMap()
{
    this->clear();
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z,
    const IntRect& texture_rect, bool collision, short type)
{
    if ((x < this->Maxsize.x && x >= 0) && 
        (y < this->Maxsize.y && y >= 0) &&
        (z < this->layers && z >=0))
    {
        
            this->Map[x][y][z].push_back ( new Tile(x, y,
                this->GridSizef, this->texture,texture_rect, collision, type));
        
    }

}



const Vector2f TileMap::getPlayerSpawnPosition(const short id) 
{
    return this->PlayerSpwanPosistions[id];
}

vector<Vector2f>& TileMap::getEnemySpawnPosition()
{
    return this->EnemySpawns;
}

vector<FloatRect*>& TileMap::ChestsPosition()
{
    return this->Chests;
}

vector<FloatRect*>& TileMap::LettersPosition()
{
    return this->Letters;
}

vector<FloatRect*>& TileMap::key_containersPosition()
{
    return this->key_containers;
}

vector<Vector2f> &TileMap::LightPositions()
{
    return this->lightPositions;
}

map<short, Door>& TileMap::DoorPositions()
{
    return this->doors;
}

const bool TileMap::empty(const unsigned x, const unsigned y, const unsigned z) const
{
    return this->Map[x][y][z].empty();
}





void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
    if ((x < this->Maxsize.x && x >= 0) &&
        (y < this->Maxsize.y && y >= 0) &&
        (z < this->layers && z >= 0))
    {
        if (!this->Map[x][y][z].empty())
        {
            delete this->Map[x][y][z][this->Map[x][y][z].size() - 1];
            this->Map[x][y][z].pop_back();
        }
    }
}

void TileMap::CheckCollision(Entity& entity,Vector2f& MousePos, const float& dt)
{
    const Vector2f* playerPos = &entity.getPosition();
    if (playerPos->x < 0)
    {
        entity.SetSpawnPosition(0.f, entity.getPosition().y);
        entity.stopVelocity(StopVelocity::STOP_VELOCITY_X);
    }
    else if (playerPos->x + entity.getGlobalbounds().width > this->WorldMaxSize.x)
    {
        entity.SetSpawnPosition(this->WorldMaxSize.x - entity.getGlobalbounds().width, entity.getPosition().y);
        entity.stopVelocity(StopVelocity::STOP_VELOCITY_X);

    }

    if (playerPos->y < 0.f)
    {
        entity.SetSpawnPosition(entity.getPosition().x, 0.f);
        entity.stopVelocity(StopVelocity::STOP_VELOCITY_Y);
    }
    else if (playerPos->y + entity.getGlobalbounds().height > this->WorldMaxSize.y)
    {

        entity.SetSpawnPosition(this->WorldMaxSize.x, entity.getPosition().y - entity.getGlobalbounds().height);
        entity.stopVelocity(StopVelocity::STOP_VELOCITY_Y);
    }
    for (size_t x = this->fromX; x < this->toX; x++) 
    {
        for (size_t y = this->fromY; y < this->toY; y++) 
        {

            for (auto& currentTile : this->Map[x][y][this->layer]) 
            {
                if (currentTile) 
                {
                    const FloatRect playerBounds = entity.getGlobalbounds();
                    const FloatRect wallBounds = currentTile->getGlobalBounds();
                    const FloatRect nextPositionBounds = entity.getNextPositionBounds(dt);

                    if (currentTile->Intersects(nextPositionBounds) && currentTile->getCollision()) {
                        if (playerBounds.left + playerBounds.width > wallBounds.left
                            && playerBounds.left < wallBounds.left
                            && playerBounds.top < wallBounds.top + wallBounds.height
                            && playerBounds.top + playerBounds.height > wallBounds.top
                            && entity.getVelocity().x != 0) {
                            entity.stopVelocity(StopVelocity::STOP_VELOCITY_X);
                            entity.SetSpawnPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                        }
                        else if (playerBounds.left < wallBounds.left + wallBounds.width
                            && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                            && playerBounds.top < wallBounds.top + wallBounds.height
                            && playerBounds.top + playerBounds.height > wallBounds.top
                            && entity.getVelocity().x != 0) {
                            entity.stopVelocity(StopVelocity::STOP_VELOCITY_X);
                            entity.SetSpawnPosition(wallBounds.left + wallBounds.width, playerBounds.top);
                        }
                        else if (playerBounds.top + playerBounds.height > wallBounds.top
                            && playerBounds.top < wallBounds.top
                            && playerBounds.left < wallBounds.left + wallBounds.width
                            && playerBounds.left + playerBounds.width > wallBounds.left) {
                            entity.stopVelocity(StopVelocity::STOP_VELOCITY_Y);
                            entity.SetSpawnPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                        }
                        else if (playerBounds.top < wallBounds.top + wallBounds.height
                            && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                            && playerBounds.left < wallBounds.left + wallBounds.width
                            && playerBounds.left + playerBounds.width > wallBounds.left) {
                            entity.stopVelocity(StopVelocity::STOP_VELOCITY_Y);
                            entity.SetSpawnPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                        }
                    }
                     else if (currentTile->Intersects(playerBounds)) 
                     {
                        if (currentTile->GetTypes() == TileTypes::DAMAGING) 
                        {
                            entity.slowVelocity(0.99f);
                            this->DamagingTile = true;
                        }
                        else 
                        {
                            this->DamagingTile = false;
                        }
                    }
                }
            }
        }
    }
}

void TileMap::DeleteMap()
{
    for (size_t x = 0; x < this->Maxsize.x; x++)
    {
        for (size_t y = 0; y < this->Maxsize.y; y++)
        {

            for (size_t z = 0; z < this->layers; z++)
            {
                for (size_t k = 0; k < this->Map[x][y][this->layer].size(); k++)
                {
                    this->Map[x][y][z][k] = nullptr;
                }
            }  
        }
    }
}

void TileMap::addSpawnPosition(Vector2f pos)
{
    
    int keyToAdd = 0;

    // Find the next available integer key
    while (PlayerSpwanPosistions.find(keyToAdd) != PlayerSpwanPosistions.end()) 
    {
        ++keyToAdd;
    }

    // Add the entry with the determined key
    PlayerSpwanPosistions[keyToAdd] = pos;

}

void TileMap::deleteSpawnPosition(Vector2f position)
{
    for (auto it = PlayerSpwanPosistions.begin(); it != PlayerSpwanPosistions.end();) {
        if (it->second == position)
        {
            it = PlayerSpwanPosistions.erase(it);
        }
        else 
        {
            ++it;
        }
    }
}

void TileMap::addDoor(const Vector2f& pos, short type)
{
    int keyToAdd = 0;

    // Find the next available integer key
    while (doors.find(keyToAdd) != doors.end())
    {
        ++keyToAdd;
    }

    // Add the entry with the determined key
    doors[keyToAdd].bounds = FloatRect(pos.x, pos.y, GridSizef,GridSizef);
    doors[keyToAdd].type = type;
}

void TileMap::DeleteDoor(Vector2f position)
{
    for (auto it = doors.begin(); it != doors.end();)
    {
        if (it->second.bounds == FloatRect(position.x, position.y, GridSizef, GridSizef))
        {
            it = doors.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void TileMap::setDoorType(const int index, const short type)
{
    this->doors[index].type = type;
}



const Texture& TileMap::getTextureSheet()const
{
    return this->texture;
}

const short TileMap::GetTileTypes() const
{
    return this->Type;
}


void TileMap::UpdateChests(const Vector2f MousePos) noexcept
{
    
}


const bool TileMap::hasOpenChest() const noexcept
{
    return this->openChest;
}

vector<FloatRect*>* TileMap::ChestTiles()
{
    return &this->Chests;
}

bool TileMap::isDamageTile() const noexcept
{
    return this->DamagingTile;
}



void TileMap::saveMap(const string file_name)
{
    ofstream outfile;
    outfile.open(file_name);

    if (!outfile.is_open())
    {
        cerr << "Error Saving map\n";
    }
    else
    {
        outfile << this->Maxsize.x << " " << this->Maxsize.y << endl
                << this->GridSize << "\n"
                << this->layers << "\n";

        for (size_t x = 0; x < this->Maxsize.x; x++)
        {
            for (size_t y = 0; y < this->Maxsize.y; y++)
            {

                for (size_t z = 0; z < this->layers; z++)
                {
                    for (size_t k = 0; k < this->Map[x][y][z].size(); k++)
                    {
                        if (this->Map[x][y][z][k])
                            outfile << x << " " << y << " " << z << " " << this->Map[x][y][z][k]->GetAsString() << " ";
                    }
                }
            }
        }
        outfile.close();


        ofstream playerSpawnInfo;
        playerSpawnInfo.open("PlayerSpawn.slmp");
        if (!playerSpawnInfo.is_open())
        {
            cerr << "Error Saving PlayerSpawn Positions\n";
        }
        else
        {
           
              for (const auto& e : this->PlayerSpwanPosistions)
              {
                  playerSpawnInfo << e.first << " " << e.second.x<<" " << e.second.y << "\n";
;             }
        } 
        playerSpawnInfo.close();


        ofstream doorsPos;
        doorsPos.open("doorsPos.slmp");
        if (!doorsPos.is_open())
        {
            cerr << "Error Saving PlayerSpawn Positions\n";
        }
        else
        {

            for (const auto& e : this->doors)
            {
                doorsPos << e.first << " " << e.second.bounds.left << " " << e.second.bounds.top
                    << " " << e.second.bounds.width << " " << e.second.bounds.height << " " << e.second.type<<"\n";
                
            }
        }

    }
}

void TileMap::LoadMap(const string file_name)
{
    ifstream file;
    file.open(file_name);

    if (!file.is_open())
    {
        throw  "Error Loading map\n";
    }
    else
    {
        Vector2u size;
        unsigned grid_size = 0;
        unsigned layers = 0;

        unsigned x = 0;
        unsigned y = 0;
        unsigned z = 0;

        unsigned Trx = 0;
        unsigned TrY = 0;
        bool collision = false;
        short type = 0;


        file >> size.x >> size.y >> grid_size >> layers;
       
        this->GridSizef = static_cast<float>(grid_size);
        this->GridSize = static_cast<unsigned>(grid_size);
        this->Maxsize.x = size.x;
        this->Maxsize.y = size.y;
        this->layers = layers;

        this->Map.resize(this->Maxsize.x, std::vector< std::vector< std::vector<Tile*> > >());
        for (int x = 0; x < this->Maxsize.x; x++)
        {
            for (int y = 0; y < this->Maxsize.y; y++)
            {
                this->Map[x].resize(this->Maxsize.y, std::vector< std::vector<Tile*> >());

                for (int z = 0; z < this->layers; z++)
                {
                    for (int k = 0; k < this->Map[x][y].size(); k++)
                    {
                        this->Map[x][y].resize(this->layers, std::vector<Tile*>());
                    }
                }
            }
        }

        for (size_t x = 0; x < this->Maxsize.x; x++)
        {
            for (size_t y = 0; y < this->Maxsize.y; y++)
            {

                for (size_t z = 0; z < this->layers; z++)
                {
                    for (size_t k = 0; k < this->Map[x][y][this->layer].size(); k++)
                    {
                        this->Map[x][y][z][k] = nullptr;
                    }
                }
            }
        }

        while (file >> x >> y >> z >> Trx >> TrY >> collision >> type)
        {
             if (type == TileTypes::ENEMYSPAWN)
            {
                this->EnemySpawns.push_back(Vector2f(static_cast<float>(x) * GridSize, static_cast<float>(y) * GridSize));

            }
            else if (type == TileTypes::Chest)
            {

                this->Chests.push_back(new FloatRect
                (
                      static_cast<float>(x) * GridSizef
                    , static_cast<float>(y) * GridSizef
                    , GridSize
                    , GridSize
                ));
            }
            else if (type == TileTypes::KEY_CONTAINER)
            {

                 this->key_containers.push_back(new FloatRect
                 (
                     static_cast<float>(x) * GridSizef
                     , static_cast<float>(y) * GridSizef
                     , GridSize
                     , GridSize
                 ));
            }
            else if (type == TileTypes::LETTER)
            {

                 this->Letters.push_back(new FloatRect
                 (
                     static_cast<float>(x) * GridSizef
                     , static_cast<float>(y) * GridSizef
                     , GridSize
                     , GridSize
                 ));
            }
            else if (type == TileTypes::LIGHT)
             {

                 this->lightPositions.push_back(Vector2f(static_cast<float>(x)
                     * GridSize, static_cast<float>(y) * GridSize));

             }
            


            this->Map[x][y][z].push_back(new Tile(x, y,GridSizef,
                this->texture, IntRect(Trx, TrY, this->GridSize, this->GridSize), collision, type));
        }
        this->Type = type;
        file.close();

        ifstream PlayerSpawn;
        PlayerSpawn.open("PlayerSpawn.slmp");
        if (!PlayerSpawn.is_open())
        {
            cerr << "Error Saving PlayerSpawn Positions\n";
        }
        short id = 0;
        float Posx = 0,  Posy = 0;
        
        while (PlayerSpawn >> id >> x >> y)
        {
            this->PlayerSpwanPosistions[id] = Vector2f(x, y);
        }   
        PlayerSpawn.close();

        ifstream doorsPos;
        doorsPos.open("doorsPos.slmp");
        if (!doorsPos.is_open())
        {
            cerr << "Error Saving PlayerSpawn Positions\n";
        }
        short door_id = 0;
        FloatRect bounds;
        int door_type = 0;
        while (doorsPos >> door_id >> bounds.left >> bounds.top>>bounds.width>>bounds.height
            >> door_type)
        {
            this->doors[door_id].bounds = bounds;
            this->doors[door_id].type = door_type;
        }
    }
}

void TileMap::update()
{

}

void TileMap::render(RenderTarget& target, Vector2i* PlayerGridPos,
    bool debug_mode, Shader* shader, Vector2f Position)
{
    if (PlayerGridPos)
    {
        this->layer = 0;
        this->fromX = PlayerGridPos->x - 9;
        if (this->fromX < 0)
        {
            this->fromX = 0;
        }
        else if (this->fromX >= this->Maxsize.x)
        {
            this->fromX = this->Maxsize.x;

        }
        this->toX = PlayerGridPos->x + 10;
        if (this->toX < 0)
        {
            this->toX = 0;
        }
        else if (this->toX >= this->Maxsize.x)
        {
            this->toX = this->Maxsize.x;

        }

        this->fromY = PlayerGridPos->y - 5;
        if (this->fromY < 0)
        {
            this->fromY = 0;
        }
        else if (this->fromY >= this->Maxsize.y)
        {
            this->fromY = this->Maxsize.y;

        }

        this->toY = PlayerGridPos->y + 7;
        if (this->toY < 0)
        {
            this->toY = 0;
        }
        else if (this->fromY >= this->Maxsize.y)
        {
            this->toY = this->Maxsize.y;

        }

        for (size_t x = this->fromX; x < this->toX; x++)
        {
            for (size_t y = this->fromY; y < this->toY; y++)
            {
                for (auto& currentTile : this->Map[x][y][this->layer])
                {
                    if (x < this->Maxsize.x && y < this->Maxsize.y)
                    {
                        if (currentTile->GetTypes() == TileTypes::OverLap)
                        {
                            this->overlappingTiles.push(currentTile);
                        }
                        else
                        {
                            if(shader && currentTile->GetTypes() != TileTypes::LIGHT)
                                currentTile->render(target, shader, Position);
                            else
                                currentTile->render(target);

                            if (currentTile->GetTypes() == TileTypes::LIGHT)
                            {

                                this->effect->render(target, *currentTile, shader);
                            }
                               
                        }
                        if (debug_mode)
                        {
                            if (currentTile->getCollision())
                            {
                                this->collisionbox.setPosition(currentTile->GetPosition());
                                target.draw(this->collisionbox);
                            }
                        }
                    }
                }
            }
        }

        /*for (const auto& e : this->PlayerSpwanPosistions)
        {
            cout << e.first << ": " << e.second.x << " " << e.second.y << "\n";
        }*/
    }
    
    else
    {

        for (auto& x : this->Map)
        {
            for (auto& y : x)
            {
                for (auto& z : y)
                {
                    for (auto& k : z)
                    {
                        if (k != nullptr)
                        {
                            if (k->GetTypes() == TileTypes::OverLap)
                            {
                                this->overlappingTiles.push(k);
                            }
                            else
                                k->render(target);
                            if (debug_mode)
                            {
                                this->collisionbox.setPosition(k->GetPosition());
                                switch (k->GetTypes())
                                {
                                case TileTypes::DEFAULT:
                                    text.setString("");
                                     break;
                                case TileTypes::DAMAGING:
                                    text.setString("Slow");
                                    break;
                                case TileTypes::OverLap:
                                    text.setString("Overlap");
                                    break;
                                case TileTypes::Chest:
                                    text.setString("Chest");
                                    break;
                                case TileTypes::PlayerSpawn:
                                    text.setString("PlayerSpawn");
                                    break;
                                case TileTypes::ENEMYSPAWN:
                                    text.setString("EnemySpawn");
                                    break;
                                case TileTypes::DOOR:
                                    text.setString("Door");
                                    break;
                                case TileTypes::LIGHT:
                                    text.setString("Light");
                                    break;

                                case TileTypes::KEY_CONTAINER:
                                    text.setString("key container");
                                    break;

                                case TileTypes::LETTER:
                                    text.setString("Letter");
                                    break;
                                }
                                
                                text.setPosition(k->GetPosition().x + 30.f, k->GetPosition().y);
                                if (k->getCollision())
                                {
                                    this->collisionbox.setFillColor(Color(241, 38, 38, 100));
                                    target.draw(this->collisionbox);
                                    
                                }
                                else if (k->GetTypes() == TileTypes::PlayerSpawn)
                                {
                                   
                                    this->collisionbox.setFillColor(Color(104, 24, 214, 100)); 
                                    target.draw(this->collisionbox);
                                }
                                else if (k->GetTypes() == TileTypes::ENEMYSPAWN)
                                {

                                    this->collisionbox.setFillColor(Color(24, 188, 214, 100));
                                    target.draw(this->collisionbox);
                                }
                                else if (k->GetTypes() == TileTypes::DOOR)
                                {

                                    this->collisionbox.setFillColor(Color(49, 153, 132, 100));
                                    target.draw(this->collisionbox);
                                    
                                }

                                target.draw(text);
                              
                            }
                        }
                    }
                }
            }
        }


       
    }
}

void TileMap::renderOverlappingTiles(RenderTarget& target
, Shader* shader , Vector2f Position)
{
    while (!this->overlappingTiles.empty())
    {
        if(shader)
            this->overlappingTiles.top()->render(target, shader, Position);
        else
            this->overlappingTiles.top()->render(target);
        this->overlappingTiles.pop();
    }
}

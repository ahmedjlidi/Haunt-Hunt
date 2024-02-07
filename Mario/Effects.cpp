#include "stdafx.h"
#include "Effects.h"

Effects::Effects()
{
}

void Effects::render(RenderTarget& target, Tile& tile, Shader* shader)
{
    shader->setUniform("hasTexture", true);
    shader->setUniform("lightPos", tile.GetPosition());//position is player center

    tile.render(target, shader, tile.GetPosition());

}

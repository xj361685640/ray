// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#include <ray/physics_character_component.h>
#include <ray/physics_character.h>
#include <ray/physics_features.h>
#include <ray/game_server.h>

_NAME_BEGIN

__ImplementSubClass(PhysicsCharacterComponent, PhysicsShapeComponent)

PhysicsCharacterComponent::PhysicsCharacterComponent() noexcept
{
    _character = std::make_shared<PhysicsCharacter>();
}

PhysicsCharacterComponent::~PhysicsCharacterComponent() noexcept
{
}

void
PhysicsCharacterComponent::setRadius(float radius) noexcept
{
    _character->setRadius(radius);
}

void
PhysicsCharacterComponent::setHeight(float height) noexcept
{
    _character->setHeight(height);
}

void
PhysicsCharacterComponent::setMovePosition(const Vector3& pos) noexcept
{
    _character->setMovePosition(pos);
}

void
PhysicsCharacterComponent::setWalkDirection(const Vector3& direction) noexcept
{
    _character->setWalkDirection(direction);
}

const Vector3&
PhysicsCharacterComponent::getWalkDirection() const noexcept
{
    return _character->getWalkDirection();
}

const Vector3&
PhysicsCharacterComponent::getMovePosition() const noexcept
{
    return _character->getMovePosition();
}

bool
PhysicsCharacterComponent::canJumping() const noexcept
{
    return _character->canJumping();
}

void
PhysicsCharacterComponent::jump(float speed) noexcept
{
    _character->jump(speed);
}

void
PhysicsCharacterComponent::onActivate() noexcept
{
    auto physics = this->getGameObject()->getGameServer()->getFeature<PhysicFeatures>();
    if (physics)
    {
        auto physicsScene = physics->getPhysicsScene(this->getGameObject()->getGameScene());
        if (physicsScene)
        {
            _character->setup();
            _character->setMovePosition(this->getGameObject()->getTranslate());
            _character->setPhysicsScene(physicsScene.get());
        }
    }
}

void
PhysicsCharacterComponent::onDeactivate() noexcept
{
    _character->close();
}

void
PhysicsCharacterComponent::onFrameEnd() noexcept
{
    auto& position = _character->getMovePosition();
    if (position != this->getGameObject()->getTranslate())
    {
        auto lookat = this->getGameObject()->getLookAt();
        auto translate = this->getGameObject()->getTranslate();
        lookat = lookat - translate;

        this->getGameObject()->setTranslate(position);
        this->getGameObject()->setLookAt(position + lookat);
    }
}

GameComponentPtr
PhysicsCharacterComponent::clone() const noexcept
{
    return nullptr;
}

PhysicsShapePtr
PhysicsCharacterComponent::getCollisionShape() noexcept
{
    return nullptr;
}

_NAME_END
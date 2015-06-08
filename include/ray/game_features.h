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
#ifndef _H_GAME_FEATURES_H_
#define _H_GAME_FEATURES_H_

#include <ray/game_types.h>

_NAME_BEGIN

class EXPORT GameFeature
{
public:
    GameFeature() noexcept;
    virtual ~GameFeature() noexcept;

    void setName(const std::string& name) noexcept;
    const std::string& getName() const noexcept;

    virtual void setActive(bool active)  noexcept;
    virtual bool getActive() noexcept;

    GameServer* getGameServer() noexcept;

    void sendMessage(const std::string& method, const Variant* data...);

protected:

    virtual void onActivate() except;
    virtual void onDeactivate() except;

    virtual void onOpenScene(GameScenePtr scene) except;
    virtual void onCloseScene(GameScenePtr scene) except;

    virtual void onReset() except;

    virtual void onFrameBegin() except;
    virtual void onFrame() except;
    virtual void onFrameEnd() except;

    virtual void onEvent(const AppEvent& event) except;

    virtual GameComponentPtr onSerialization(XMLReader* reader) except;

    virtual void onMessage(const std::string& method, const Variant* data...) except;

private:
    friend GameServer;
    void _setGameServer(GameServer* server) noexcept;

private:
    GameFeature(const GameFeature&) noexcept = delete;
    GameFeature& operator=(const GameFeature&) noexcept = delete;

private:

    bool _isActive;

    std::string _name;

    GameServer* _server;
};

_NAME_END

#endif
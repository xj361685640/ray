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
#ifndef _H_GAME_APPLICATION_H_
#define _H_GAME_APPLICATION_H_

#include <ray/game_types.h>

_NAME_BEGIN

class EXPORT GameApplication final : public EvtHandler
{
public:
    GameApplication() noexcept;
    ~GameApplication() noexcept;

    bool open() except;
    void close() noexcept;

    void start() except;
    void stop() noexcept;

    bool isQuitRequest() const noexcept;

    bool openScene(GameScenePtr scene) except;
    bool openScene(const std::string& name) except;
    void closeScene(GameScenePtr name) noexcept;
    void closeScene(const std::string& name) noexcept;
    GameScenePtr findScene(const std::string& name) noexcept;

    void addFeatures(GameFeaturePtr feature) except;
    void removeFeatures(GameFeaturePtr feature) noexcept;
    GameFeaturePtr getFeature(const std::string& name) noexcept;

    void setFileService(bool enable) noexcept;
    void setFileServicePath(const std::string& path) noexcept;
    void setResDownloadURL(const std::string& path) noexcept;

    void sendEvent(const AppEvent& event) noexcept;

    void update() except;

private:
    GameApplication(const GameApplication&) noexcept = delete;
    GameApplication& operator=(const GameApplication&) noexcept = delete;

private:

    bool _isInitialize;
    bool _isQuitRequest;

    std::string _engineDir;
    std::string _resourceBaseDir;
    std::string _downloadURL;

    GameServerPtr _gameServer;

    IoServer* _ioServer;
    IoInterface* _ioInterface;
};

_NAME_END

#endif
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
#ifndef _H_CAMERA_COMPONENT_H_
#define _H_CAMERA_COMPONENT_H_

#include <ray/game_component.h>
#include <ray/camera.h>

_NAME_BEGIN

class EXPORT CameraComponent final : public GameComponent
{
    __DeclareSubClass(CameraComponent, GameComponent)
public:
    CameraComponent() noexcept;
    ~CameraComponent() noexcept;

    void makeLookAt(const Vector3& pos, const Vector3& lookat, const Vector3& up) noexcept;
    void makeOrtho(float left, float right, float bottom, float top, float znear, float zfar) noexcept;
    void makePerspective(float aperture, float ratio, float znear, float zfar) noexcept;

    float getAperture() const noexcept;
    float getRatio() const noexcept;
    float getNear() const noexcept;
    float getFar() const noexcept;

    const Matrix4x4& getProject() const noexcept;
    const Matrix4x4& getViewProject() const noexcept;
    const Matrix4x4& getProjectInverse() const noexcept;
    const Matrix4x4& getViewProjectInverse() const noexcept;

    Vector3 project(const Vector3& pos) const noexcept;
    Vector3 unproject(const Vector3& pos) const noexcept;

    void setViewport(const Viewport& viewport) noexcept;
    const Viewport&  getViewport() const noexcept;

    void setCameraType(CameraType type) noexcept;
    void setCameraOrder(CameraOrder order) noexcept;

    CameraType getCameraType() const noexcept;
    CameraOrder getCameraOrder() const noexcept;

    virtual GameComponentPtr clone() const noexcept;

private:

    void onActivate() noexcept;
    void onDeactivate() noexcept;

    void onMoveAfter() noexcept;

private:
    CameraComponent(const CameraComponent&) noexcept = delete;
    CameraComponent& operator=(const CameraComponent&) noexcept = delete;

private:

    CameraPtr _camera;
};

_NAME_END

#endif
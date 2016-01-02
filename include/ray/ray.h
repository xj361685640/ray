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
#ifndef _H_RAY_H_
#define _H_RAY_H_

#ifndef RAY_C_LINKAGE
#	ifdef __cplusplus
#		define RAY_C_LINKAGE extern "C"
#	else
#		define RAY_C_LINKAGE extern
#	endif
#endif

#if defined(_BUILD_PLATFORM_WINDOWS)
#	ifndef __WIN32__
#		define __WIN32__ 1
#	endif

#	if defined(_BUILD_DLL_EXPORT)
#		define RAY_EXPORT
#		define RAY_EXPORT_WINONLY
#	else
#		define RAY_EXPORT
#		define RAY_EXPORT_WINONLY
#	endif

#	ifndef  RAY_CALL
#		define RAY_CALL __stdcall
#	endif

#elif defined(_BUILD_PLATFORM_ANDROID)
#include <jni.h>

#	ifndef RAY_EXPORT
#		define RAY_EXPORT JNIEXPORT
#		define RAY_EXPORT_WINONLY
#	endif

#	ifndef  RAY_CALL
#		define RAY_CALL JNICALL
#	endif

#endif

RAY_C_LINKAGE RAY_EXPORT void RAY_CALL rayInit(const char* gamedir, const char* scenename) noexcept;
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL rayTerminate() noexcept;

RAY_C_LINKAGE RAY_EXPORT bool RAY_CALL rayOpenWindow(const char* title, int w, int h) noexcept;
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL rayCloseWindow() noexcept;

RAY_C_LINKAGE RAY_EXPORT bool RAY_CALL rayIsQuitRequest() noexcept;
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL rayUpdate() noexcept;

#if defined(_BUILD_PLATFORM_ANDROID)

RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeConfig(JNIEnv*  env, jobject thiz, jstring gamedir, jstring scenename, jboolean bShader);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeStorage(JNIEnv*  env, jobject thiz, jint type, jstring pakagename, jstring apklocation);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeOpen(JNIEnv*  env, jobject thiz, jint w, jint h, jfloat dpiw, jfloat dpih, jobject assetManager);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeClose(JNIEnv* env, jobject thiz);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeRender(JNIEnv* env, jobject obj);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeOnPause(JNIEnv* env, jobject obj);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeOnResume(JNIEnv* env, jobject obj);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeOnStop(JNIEnv* env, jobject obj);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeTouchesBegin(JNIEnv* env, jobject obj, jint pIDs, jfloat pXs, jfloat pYs);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeTouchesMove(JNIEnv* env, jobject obj, jintArray pIDs, jfloatArray pXs, jfloatArray pYs);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeTouchesEnd(JNIEnv* env, jobject obj, jint pIDs, jfloat pXs, jfloat pYs);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeTouchesCancel(JNIEnv* env, jobject obj, jintArray pIDs, jfloatArray pXs, jfloatArray pYs);
RAY_C_LINKAGE RAY_EXPORT void RAY_CALL Java_org_ray_lib_Ray3DRenderer_nativeKeyPress(JNIEnv* env, jobject obj, jint pKeyCode);

#endif

#endif
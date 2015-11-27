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
#if defined(_BUILD_MYGUI)
#include <ray/mygui_widget.h>
#include <ray/mygui_button.h>
#include <ray/mygui_window.h>
#include <ray/mygui_textbox.h>

_NAME_BEGIN

__ImplementSubInterface(MyGuiWidget, GuiWidget, "MyGuiWidget")

MyGuiWidget::MyGuiWidget() noexcept
	: _widget(nullptr)
{
}

MyGuiWidget::~MyGuiWidget() noexcept
{
}

void 
MyGuiWidget::destroy() noexcept
{
	MyGUI::Gui::getInstance().destroyWidget(_widget);
}

void 
MyGuiWidget::setName(const std::string& name) noexcept
{
	assert(_widget);
	_widget->setName(name);
}

const std::string& 
MyGuiWidget::getName() noexcept
{
	assert(_widget);
	return _widget->getName();
}

void 
MyGuiWidget::setAlign(GuiWidgetAlign align) noexcept
{
	assert(_widget);
	_widget->setAlign(GuiAlignToMyGui(align));
}

GuiWidgetAlign 
MyGuiWidget::getAlign() noexcept
{
	return MyGuiToGuiAlign(_widget->getAlign());
}

void 
MyGuiWidget::setSkin(const std::string& skin) noexcept
{
	assert(_widget);
	_widget->changeWidgetSkin(skin);
}

const std::string& 
MyGuiWidget::getSkin() const noexcept
{
	assert(_widget);
	return _widget->getSkinName();
}

void 
MyGuiWidget::setViewport(const Viewport& view) noexcept
{
	assert(_widget);
	MyGUI::IntCoord coord;
	coord.left = view.left;
	coord.top = view.top;
	coord.width = view.width;
	coord.height = view.height;
	_widget->setCoord(coord);
}

void
MyGuiWidget::getViewport(Viewport& viewport) const noexcept
{
	assert(_widget);
	MyGUI::IntCoord coord = _widget->getCoord();
	viewport.left = coord.left;
	viewport.top = coord.top;
	viewport.width = coord.width;
	viewport.height = coord.height;
}

GuiWidgetPtr
MyGuiWidget::createWieght(const rtti::Rtti* rtti) except
{
	assert(rtti->isDerivedFrom(GuiWidget::getRtti()));

	GuiWidgetPtr widget;
	if (rtti == GuiButton::getRtti())
		widget = std::make_shared<MyGuiButton>(_widget);
	else if (rtti == GuiWindow::getRtti())
		widget = std::make_shared<MyGuiWindow>(_widget);
	else if (rtti == GuiTextBox::getRtti())
		widget = std::make_shared<MyGuiTextBox>(_widget);
	else
	{
		assert(false);
	}
	
	return widget;
}

void 
MyGuiWidget::setWidget(MyGUI::Widget* widget) noexcept
{
	_widget = widget;
}

MyGUI::Widget* 
MyGuiWidget::getWidget() const noexcept
{
	return _widget;
}

MyGUI::Align 
MyGuiWidget::GuiAlignToMyGui(GuiWidgetAlign align) noexcept
{
	switch (align.getValue())
	{
	case GuiWidgetAlign::Left:
		return MyGUI::Align::Left;
	case GuiWidgetAlign::Right:
		return MyGUI::Align::Top;
	case GuiWidgetAlign::Top:
		return MyGUI::Align::Right;
	case GuiWidgetAlign::Bottom:
		return MyGUI::Align::Bottom;
	case GuiWidgetAlign::Center:
		return MyGUI::Align::Center;
	case GuiWidgetAlign::Default:
		return MyGUI::Align::Default;
	case GuiWidgetAlign::HStretch:
		return MyGUI::Align::HStretch;
	case GuiWidgetAlign::VStretch:
		return MyGUI::Align::VStretch;
	case GuiWidgetAlign::Stretch:
		return MyGUI::Align::Stretch;
	default:
		assert(false);
		return MyGUI::Align::Default;
	}
}

GuiWidgetAlign 
MyGuiWidget::MyGuiToGuiAlign(MyGUI::Align align) noexcept
{
	switch (align.getValue())
	{
	case MyGUI::Align::Left:
		return GuiWidgetAlign::Left;
	case MyGUI::Align::Right:
		return GuiWidgetAlign::Top;
	case MyGUI::Align::Top:
		return GuiWidgetAlign::Right;
	case MyGUI::Align::Bottom:
		return GuiWidgetAlign::Bottom;
	case MyGUI::Align::Center:
		return GuiWidgetAlign::Center;
	case MyGUI::Align::Default:
		return GuiWidgetAlign::Default;
	case MyGUI::Align::HStretch:
		return GuiWidgetAlign::HStretch;
	case MyGUI::Align::VStretch:
		return GuiWidgetAlign::VStretch;
	case MyGUI::Align::Stretch:
		return GuiWidgetAlign::Stretch;
	default:
		assert(false);
		return GuiWidgetAlign::Default;
	}
}

_NAME_END
#endif
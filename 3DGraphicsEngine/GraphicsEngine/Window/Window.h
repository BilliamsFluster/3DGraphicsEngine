#pragma once
#include "Core/WinDef.h"
#include "Core/ErrorHandling/Exception.h"
#include "Core/Events/Keyboard.h"
#include "Core/Events/Mouse.h"
#include "Core/DirectX/Graphics.h"
#include <memory>
#include <optional>

class Window
{
public:
	class WinException : public Exception
	{
		using Exception::Exception;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrException : public WinException
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException : public WinException
	{
	public:
		using WinException::WinException;
		const char* GetType() const noexcept override;
	};
private:
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator =(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "William's Direct X 3D Engine";
		static WindowClass wndClass;
		HINSTANCE hInst;

	};
public:
	Window(int width, int height, const char* name) ;
	~Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
	Graphics& Gfx();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kbd;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};



#ifndef CP_UTF8
#define CP_UTF8 65001
#endif


#pragma once

#include "ZiggyX/Events/Event.h"
#include <string>
#include <functional>
#include <Windows.h>

namespace ZiggyX
{
	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width = 1600;
		uint32_t Height = 900;
		bool IsResizeable = true;

		using EventCallbackFn = std::function<void(Event&)>;
		EventCallbackFn EventCallback;
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowSpecification& specification = WindowSpecification());
		virtual ~Window();

		void Create();
		void Destroy();

		void Update();

	private:
		class WindowClass
		{
		public:
			static const wchar_t* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;
		private:
			WindowClass() noexcept;
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const wchar_t* wndClassName = L"ZiggyX";
			static WindowClass wndClass;
			HINSTANCE hInst;
		};

	private:
		WindowSpecification m_Specification;
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandlMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		HWND hWnd;
	};
}
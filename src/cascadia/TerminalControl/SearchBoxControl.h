/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- SearchBoxControl.cpp

Abstract:
- the search dialog component used in Terminal Search

Author(s):
- Kaiyu Wang (kawa) 11-27-2019

--*/

#pragma once

#include "SearchBoxControl.g.h"

namespace winrt::Microsoft::Terminal::Control::implementation
{
    struct SearchBoxControl : SearchBoxControlT<SearchBoxControl>
    {
        static constexpr int32_t MaximumTotalResultsToShowInStatus = 999;
        static constexpr std::wstring_view TotalResultsTooHighStatus = L"999+";
        static constexpr std::wstring_view CurrentIndexTooHighStatus = L"?";
        static constexpr std::wstring_view StatusDelimiter = L"/";

        SearchBoxControl();

        winrt::Windows::Foundation::Rect ContentClipRect() const noexcept;
        double OpenAnimationStartPoint() const noexcept;

        void TextBoxKeyDown(const winrt::Windows::Foundation::IInspectable& /*sender*/, const winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs& e);
        void Open(std::function<void()> callback);
        void Close();

        void SetFocusOnTextbox();
        void PopulateTextbox(const winrt::hstring& text);
        bool ContainsFocus();
        void SetStatus(int32_t totalMatches, int32_t currentMatch);
        void ClearStatus();
        bool NavigationEnabled();
        void NavigationEnabled(bool enabled);

        void GoBackwardClicked(const winrt::Windows::Foundation::IInspectable& /*sender*/, const winrt::Windows::UI::Xaml::RoutedEventArgs& /*e*/);
        void GoForwardClicked(const winrt::Windows::Foundation::IInspectable& /*sender*/, const winrt::Windows::UI::Xaml::RoutedEventArgs& /*e*/);
        void CloseClick(const winrt::Windows::Foundation::IInspectable& /*sender*/, const winrt::Windows::UI::Xaml::RoutedEventArgs& e);

        void TextBoxTextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void CaseSensitivityButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void SearchBoxPointerPressedHandler(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void SearchBoxPointerReleasedHandler(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);

        WINRT_CALLBACK(PropertyChanged, winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler);
        WINRT_CALLBACK(Search, SearchHandler);
        WINRT_CALLBACK(SearchChanged, SearchHandler);
        TYPED_EVENT(Closed, Control::SearchBoxControl, Windows::UI::Xaml::RoutedEventArgs);

    private:
        std::unordered_set<winrt::Windows::Foundation::IInspectable> _focusableElements;
        winrt::Windows::Foundation::Rect _contentClipRect{ 0, 0, 0, 0 };
        double _openAnimationStartPoint = 0;
        winrt::Windows::UI::Xaml::FrameworkElement::Loaded_revoker _initialLoadedRevoker;
        bool _initialized = false;
        std::function<void()> _initializedCallback;

        void _Initialize();
        void _UpdateSizeDependents();
        void _ContentClipRect(const winrt::Windows::Foundation::Rect& rect);
        void _OpenAnimationStartPoint(double y);
        void _PlayOpenAnimation();
        void _PlayCloseAnimation();
        bool _AnimationEnabled();

        static winrt::hstring _FormatStatus(int32_t totalMatches, int32_t currentMatch);
        static double _TextWidth(winrt::hstring text, double fontSize);
        double _GetStatusMaxWidth();

        bool _GoForward();
        bool _CaseSensitive();
        void _KeyDownHandler(const winrt::Windows::Foundation::IInspectable& sender, const winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs& e);
        void _CharacterHandler(const winrt::Windows::Foundation::IInspectable& /*sender*/, const winrt::Windows::UI::Xaml::Input::CharacterReceivedRoutedEventArgs& e);
    };
}

namespace winrt::Microsoft::Terminal::Control::factory_implementation
{
    BASIC_FACTORY(SearchBoxControl);
}

// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::ContextMenuMWE::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        const auto my_flyout {
            myPanel().Resources().TryLookup(box_value(L"myFlyout")).as<Controls::MenuFlyout>()
        };

        for (int i = 0; i < 5; ++i)
        {
            const auto child { Controls::Button() };
	        const auto label { Controls::TextBlock() };
            label.Text(L"Child " + to_hstring(i+1));
            child.Content(label);
            child.ContextFlyout(my_flyout);
            myPanel().Children().Append(child);
        }
    }

    void MainWindow::myFlyout_Click(IInspectable const& sender, RoutedEventArgs const&)
    {
        const auto my_flyout {
            myPanel().Resources().TryLookup(box_value(L"myFlyout")).as<Controls::MenuFlyout>()
        };

	    const auto item { sender.as<Controls::MenuFlyoutItem>() };
        const auto cmd { unbox_value<hstring>(item.Tag()) };
        const auto target { my_flyout.Target().as<Controls::Button>() };
        uint32_t index;
        myPanel().Children().IndexOf(target, index);

        if (cmd == L"insert")
        {
	        const auto child { Controls::Button() };
	        const auto label { Controls::TextBlock() };
            label.Text(L"Child New");
            child.Content(label);
            child.ContextFlyout(my_flyout);
            myPanel().Children().InsertAt(index+1, child);
        }
        else if (cmd == L"delete")
        {
	        myPanel().Children().RemoveAt(index);
        }
    }
}

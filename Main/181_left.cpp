/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：181_left.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年08月27日
*   描    述：
*   版    本: Version 1.00
================================================================*/

#include <iostream>

using namespace std;


enum eGrpActiveInfoMask {
        eGrpActiveInfoMask_null                 = 0,

        eGrpActiveInfoMask_active               = 0x00000001 << 0,      // 活动状态
        eGrpActiveInfoMask_mic_mode             = 0x00000001 << 1,      // 麦序模式
        eGrpActiveInfoMask_ctrl_mask            = 0x00000001 << 2,      // 场控掩码
        eGrpActiveInfoMask_chat_mask            = 0x00000001 << 3,      // 聊天掩码
        eGrpActiveInfoMask_mic_time             = 0x00000001 << 4,      // 麦序时间
        eGrpActiveInfoMask_lecturer             = 0x00000001 << 5,      // 授课者
        eGrpActiveInfoMask_ppt_userid           = 0x00000001 << 6,      // ppt演示者ID
        eGrpActiveInfoMask_wb_userid            = 0x00000001 << 7,      // 白板演示者ID
        eGrpActiveInfoMask_vs_userid            = 0x00000001 << 8,      // 视频演示者ID
        eGrpActiveInfoMask_ds_userid            = 0x00000001 << 9,      // 屏幕分享演示者ID
        eGrpActiveInfoMask_ac_userid            = 0x00000001 << 10,     // 答题卡演示者ID
        eGrpActiveInfoMask_ci_mask              = 0x00000001 << 11,     // 聊天间隔掩码
        eGrpActiveInfoMask_ci_time              = 0x00000001 << 12,     // 聊天时间间隔
        eGrpActiveInfoMask_vp_userid            = 0x00000001 << 13,     // 视频播放演示者ID
        eGrpActiveInfoMask_multi_task           = 0x00000001 << 14,     // 多任务信息
        eGrpActiveInfoMask_live_info            = 0x00000001 << 15,     // 直播信息
        eGrpActiveInfoMask_vr_userid            = 0x00000001 << 16,     // 转播信息
        eGrpActiveInfoMask_mp_userid            = 0x00000001 << 17,     // 音乐播放演示者ID
        eGrpActiveInfoMask_ls_userid            = 0x00000001 << 18,     // 直播售卖者ID
        eGrpActiveInfoMask_is_inner             = 0x00000001 << 19,     // 是否近场
};

enum WindowType {
        Widget = 0x00000000,
        Window = 0x00000001,
        Dialog = 0x00000002 | Window,
        Sheet = 0x00000004 | Window,
        Drawer = Sheet | Dialog,
        Popup = 0x00000008 | Window,
        Tool = Popup | Dialog,
        ToolTip = Popup | Sheet,
        SplashScreen = ToolTip | Dialog,
        Desktop = 0x00000010 | Window,
        SubWindow = 0x00000012,
        ForeignWindow = 0x00000020 | Window,
        CoverWindow = 0x00000040 | Window,

        WindowType_Mask = 0x000000ff,
        MSWindowsFixedSizeDialogHint = 0x00000100,
        MSWindowsOwnDC = 0x00000200,
        BypassWindowManagerHint = 0x00000400,
        X11BypassWindowManagerHint = BypassWindowManagerHint,
        FramelessWindowHint = 0x00000800,
        WindowTitleHint = 0x00001000,
        WindowSystemMenuHint = 0x00002000,
        WindowMinimizeButtonHint = 0x00004000,
        WindowMaximizeButtonHint = 0x00008000,
        WindowMinMaxButtonsHint = WindowMinimizeButtonHint | WindowMaximizeButtonHint,
        WindowContextHelpButtonHint = 0x00010000,
        WindowShadeButtonHint = 0x00020000,
        WindowStaysOnTopHint = 0x00040000,
        WindowTransparentForInput = 0x00080000,
        WindowOverridesSystemGestures = 0x00100000,
        WindowDoesNotAcceptFocus = 0x00200000,
        MaximizeUsingFullscreenGeometryHint = 0x00400000,

        CustomizeWindowHint = 0x02000000,
        WindowStaysOnBottomHint = 0x04000000,
        WindowCloseButtonHint = 0x08000000,
        MacWindowToolBarButtonHint = 0x10000000,
        BypassGraphicsProxyWidget = 0x20000000,
        NoDropShadowWindowHint = 0x40000000,
        WindowFullscreenButtonHint = 0x80000000,

        // The following enums have overlapping values with other enums.
        // This was not intentional, but it's too late to change now.
        WindowOkButtonHint = 0x00080000, // WindowTransparentForInput
        WindowCancelButtonHint = 0x00100000 // WindowOverridesSystemGestures
};

void testLeft()
{
	cout << __func__ << " 1 << 20: " << (1 << 20) << endl;
}

void test_windowFlags()
{	
	cout << "WindowStaysOnTopHint: " << WindowStaysOnTopHint << endl;
	cout << "Widget: " << Widget << endl;
	cout << "Window: " << Window << endl;
	cout << "Dialog: " << Dialog << endl;
	cout << "Sheet: " << Sheet << endl;
	cout << "Drawer: " << Drawer << endl;
	cout << "Popup: " << Popup << endl;
	cout << "Tool: " << Tool << endl;
	cout << "ToolTip: " << ToolTip << endl;
	cout << "SplashScreen: " << SplashScreen << endl;
	cout << "Desktop: " << Desktop << endl;
	cout << "SubWindow: " << SubWindow << endl;
	cout << "BypassWindowManagerHint: " << BypassWindowManagerHint << endl;
	cout << "FramelessWindowHint: " << FramelessWindowHint << endl;
	cout << "WindowTitleHint: " << WindowTitleHint << endl;
	cout << "WindowSystemMenuHint: " << WindowSystemMenuHint << endl;
	cout << "WindowMinimizeButtonHint: " << WindowMinimizeButtonHint << endl;
	cout << "WindowMaximizeButtonHint: " << WindowMaximizeButtonHint << endl;
	cout << "WindowMinMaxButtonsHint: " << WindowMinMaxButtonsHint << endl;
	cout << "WindowContextHelpButtonHint: " << WindowContextHelpButtonHint << endl;
	cout << "WindowShadeButtonHint: " << WindowShadeButtonHint << endl;
	cout << "WindowTransparentForInput: " << WindowTransparentForInput << endl;
	cout << "WindowOverridesSystemGestures: " << WindowOverridesSystemGestures << endl;
	cout << "WindowDoesNotAcceptFocus: " << WindowDoesNotAcceptFocus << endl;
	cout << "MaximizeUsingFullscreenGeometryHint: " << MaximizeUsingFullscreenGeometryHint << endl;
	cout << "CustomizeWindowHint: " << CustomizeWindowHint << endl;
	cout << "WindowStaysOnBottomHint: " << WindowStaysOnBottomHint << endl;
	cout << "WindowCloseButtonHint: " << WindowCloseButtonHint << endl;
	cout << "WindowStaysOnTopHint: " << WindowStaysOnTopHint << endl;
	cout << "MacWindowToolBarButtonHint: " << MacWindowToolBarButtonHint << endl;
	cout << "BypassGraphicsProxyWidget: " << BypassGraphicsProxyWidget << endl;
	cout << "NoDropShadowWindowHint: " << NoDropShadowWindowHint << endl;
	cout << "WindowFullscreenButtonHint: " << WindowFullscreenButtonHint << endl;
	cout << "WindowOkButtonHint: " << WindowOkButtonHint << endl;
	cout << "WindowCancelButtonHint: " << WindowCancelButtonHint << endl;

	cout << "-----------------------------" << endl;
	cout << "WindowStaysOnTopHint | Tool: " << (WindowStaysOnTopHint | Tool) << endl;
	
}


int main()
{
	cout << "eGrpActiveInfoMask_active: " << eGrpActiveInfoMask_active << endl;

	for (int i = 0; i < 20; i++) {
		long ret = 0x00000001 << i;
		cout << "i = " << i << " 0x00000001 << " << i << " = " << ret << endl;
	}

	// ********
	testLeft();


	// 测试window属性 qt
	test_windowFlags();
	return 0;
}

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

void testLeft()
{
	cout << __func__ << " 1 << 20: " << (1 << 20) << endl;
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

	return 0;
}

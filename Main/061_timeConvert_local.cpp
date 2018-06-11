/*================================================================
*   Copyright (C) 2018 Renleilei. All rights reserved.
*   
*   文件名称：046_timeConvert_local.cpp
*   创 建 者：Renleilei (renleilei@foxmail.com)
*   创建日期：2018年06月08日
*   描    述：
*   版    本: Version 1.00
================================================================*/



int32_t nCurYear = 0;
		int32_t nCurDay = 0;
		struct tm* pCurTime = _localtime64((__time64_t*)&curTime);
		if (pCurTime)
		{
			nCurYear = pCurTime->tm_year;
			nCurDay = pCurTime->tm_yday;
		}

		NCString strDate;
		NCString strBeginHour;
		uint64_t u64BeginTime = (uint64_t)beginTime;
		uint64_t u64EndTime = (uint64_t)endTime;
		struct tm* pBeginTime = _localtime64((__time64_t*)&u64BeginTime);
		if (pBeginTime)
		{
			if (nCurYear == pBeginTime->tm_year && pBeginTime->tm_yday == nCurDay)
			{
				strDate = _T("今天");
			}
			else if (nCurYear == pBeginTime->tm_year)
			{
				strDate.Format(_T("%02d-%02d"), pBeginTime->tm_mon + 1, pBeginTime->tm_mday);
			}
			else
			{
				strDate.Format(_T("%d-%02d-%02d"), pBeginTime->tm_year + 1900, pBeginTime->tm_mon + 1, pBeginTime->tm_mday);
			}

			strBeginHour.Format(_T(" %02d:%02d"), pBeginTime->tm_hour, pBeginTime->tm_min);
		}

		NCString strEndHour;
		if (endTime != 0)
		{
			struct tm* pEndTime = _localtime64((__time64_t*)&u64EndTime);
			if (pEndTime)
			{
				strEndHour.Format(_T("-%02d:%02d"), pEndTime->tm_hour, pEndTime->tm_min);
			}
		}

		strResult = strDate + strBeginHour + strEndHour;

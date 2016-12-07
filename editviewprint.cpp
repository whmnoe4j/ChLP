UINT CEditView::PrintInsideRect(CDC* pDC, RECT& rectLayout,
	UINT nIndexStart, UINT nIndexStop)
	// 参数：设备，矩形，字符串起点、终点
	// 该函数仅在本类成员函数OnPrint( )中调用
	// 为了用原始文本格式显示分词文本、词性标注文本，可以加一个
	// 矩形显示函数PrintInsideRectText( )
	// 可重载OnPrint( )，加一个参数，以决定调用哪个矩形显示函数
	// 需要时调用CMyView::OnDraw( )
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	BOOL bWordWrap = (GetStyle() & ES_AUTOHSCROLL) == 0;
	// 是否词回绕

	// 以下获取字符串缓冲区、实际的起点和终点
	UINT nLen = GetBufferLength(); // 缓冲区长度
	if (nIndexStart >= nLen)	return nLen;
	// 如果起点大于缓冲区长度则返回
	LPCTSTR lpszText = LockBuffer(); // 锁定缓冲区，得到字符指针
	if (nIndexStop > nLen)	nIndexStop = nLen;
	// 如果终点大于缓冲区长度，则置终点为缓冲区末尾
	ASSERT(nIndexStart < nLen); // 确保起点小于缓冲区长度

	// 计算文本和制表符的几何特征
	TEXTMETRIC tm;  // 文本几何特征
	pDC->GetTextMetrics(&tm);
	int cyChar = tm.tmHeight + tm.tmExternalLeading; // 字符高度
#ifndef _MAC
	int nTabStop = m_nTabStops *
		pDC->GetTabbedTextExtent(_T("\t"), 1, 0, NULL).cx / 8 / 4;
#else
	int nTabStop = pDC->GetTextExtent(_T("\t"), 1).cx;
#endif
	int aCharWidths[256]; // 字符宽度数组
	pDC->GetCharWidth(0, 255, aCharWidths); // 获取所有字符的宽度

	int y = rectLayout.top; // 矩形的上部坐标
	UINT cx = rectLayout.right - rectLayout.left; // 矩形宽度
	UINT nIndex = nIndexStart;  // 从字符串起点开始

	VERIFY(pDC->SaveDC() != 0);
	BOOL bLayoutOnly = pDC->IntersectClipRect(&rectLayout) == NULLREGION;
	// 是否只显示矩形之内的字符
	do
	{
		UINT nIndexEnd = EndOfLine(lpszText, nIndexStop, nIndex);
		// 计算行尾字符的序号
		if (nIndex == nIndexEnd) // 如果到达行尾
		{
			y += cyChar;   // 增加一行，y表示当前输出的纵坐标
		}
		else if (bWordWrap)  // 如果必须词回绕
		{
			// word-wrap printing
			do
			{
				UINT nIndexWrap = ClipLine(pDC, aCharWidths,
					cx, nTabStop, lpszText, nIndex, nIndexEnd);
				// 计算词回绕时行尾字符的序号
				UINT nIndexWord = nIndexWrap; // 用另一变量保存这个值
				if (nIndexWord != nIndexEnd) // 如果行尾字符序号不等于行尾序号
				{
					while (nIndexWord > nIndex &&
					  !isspace(lpszText[nIndexWord]))
					{ // 如果行尾字符序号大于当前字符序号并且行尾字符序号不是空白
						nIndexWord--;  // 行尾字符序号往左移
					}
					if (nIndexWord == nIndex) // 如果移到当前字符
						nIndexWord = nIndexWrap; // 仍然以原先计算的行尾字符序号为准
				}
				CRect rect(rectLayout.left, y, rectLayout.right, y+cyChar);
				// 当前行作为一个矩形
				if (!bLayoutOnly && pDC->RectVisible(rect))
				{ // 如果只输出矩形内的字符并且当前行是可见的
#ifndef _MAC
					pDC->TabbedTextOut(rect.left, y,
						(LPCTSTR)(lpszText+nIndex), nIndexWord-nIndex, 1,
						&nTabStop, rect.left);
#else
					pDC->TextOut(rect.left, y,
						(LPCTSTR)(lpszText+nIndex), nIndexWord-nIndex);
					// 将一个词（若干个字符）输出在这一行上
#endif
				}
				y += cyChar; // 加一行
				nIndex = nIndexWord; // 字符序号右移
				while (nIndex < nIndexEnd && isspace(lpszText[nIndex]))
					nIndex++; // 跳过换行符之前的空白字符
			} while (nIndex < nIndexEnd && y+cyChar <= rectLayout.bottom);
				
			nIndexEnd = nIndex;
		}
		else
		{ // 如果不必词回绕，就要简单、快得多
			CRect rect(rectLayout.left, y, rectLayout.right, y+cyChar);
			if (!bLayoutOnly && pDC->RectVisible(rect))
			{
				UINT nIndexClip = ClipLine(pDC, aCharWidths, cx, nTabStop,
					lpszText, nIndex, nIndexEnd);
				if (nIndexClip < nIndexEnd)
				{
					if (_istlead(*(lpszText+nIndexClip)))
						nIndexClip++;
					nIndexClip++;
				}
#ifndef _MAC
				pDC->TabbedTextOut(rect.left, y,
					(LPCTSTR)(lpszText+nIndex), nIndexClip-nIndex, 1,
					&nTabStop, rect.left);
#else
				pDC->TextOut(rect.left, y,
					(LPCTSTR)(lpszText+nIndex), nIndexClip-nIndex);
#endif
			}
			y += cyChar;
		}
		nIndex = NextLine(lpszText, nIndexStop, nIndexEnd);
		// 下一行开头字符
	}
	while (nIndex < nIndexStop && y+cyChar <= rectLayout.bottom);

	pDC->RestoreDC(-1);
	UnlockBuffer();  // 释放字符串缓冲区
	ASSERT_VALID(this);

	rectLayout.bottom = y;
	return nIndex;
}

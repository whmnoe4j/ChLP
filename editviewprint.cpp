UINT CEditView::PrintInsideRect(CDC* pDC, RECT& rectLayout,
	UINT nIndexStart, UINT nIndexStop)
	// �������豸�����Σ��ַ�����㡢�յ�
	// �ú������ڱ����Ա����OnPrint( )�е���
	// Ϊ����ԭʼ�ı���ʽ��ʾ�ִ��ı������Ա�ע�ı������Լ�һ��
	// ������ʾ����PrintInsideRectText( )
	// ������OnPrint( )����һ���������Ծ��������ĸ�������ʾ����
	// ��Ҫʱ����CMyView::OnDraw( )
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	BOOL bWordWrap = (GetStyle() & ES_AUTOHSCROLL) == 0;
	// �Ƿ�ʻ���

	// ���»�ȡ�ַ�����������ʵ�ʵ������յ�
	UINT nLen = GetBufferLength(); // ����������
	if (nIndexStart >= nLen)	return nLen;
	// ��������ڻ����������򷵻�
	LPCTSTR lpszText = LockBuffer(); // �������������õ��ַ�ָ��
	if (nIndexStop > nLen)	nIndexStop = nLen;
	// ����յ���ڻ��������ȣ������յ�Ϊ������ĩβ
	ASSERT(nIndexStart < nLen); // ȷ�����С�ڻ���������

	// �����ı����Ʊ���ļ�������
	TEXTMETRIC tm;  // �ı���������
	pDC->GetTextMetrics(&tm);
	int cyChar = tm.tmHeight + tm.tmExternalLeading; // �ַ��߶�
#ifndef _MAC
	int nTabStop = m_nTabStops *
		pDC->GetTabbedTextExtent(_T("\t"), 1, 0, NULL).cx / 8 / 4;
#else
	int nTabStop = pDC->GetTextExtent(_T("\t"), 1).cx;
#endif
	int aCharWidths[256]; // �ַ��������
	pDC->GetCharWidth(0, 255, aCharWidths); // ��ȡ�����ַ��Ŀ��

	int y = rectLayout.top; // ���ε��ϲ�����
	UINT cx = rectLayout.right - rectLayout.left; // ���ο��
	UINT nIndex = nIndexStart;  // ���ַ�����㿪ʼ

	VERIFY(pDC->SaveDC() != 0);
	BOOL bLayoutOnly = pDC->IntersectClipRect(&rectLayout) == NULLREGION;
	// �Ƿ�ֻ��ʾ����֮�ڵ��ַ�
	do
	{
		UINT nIndexEnd = EndOfLine(lpszText, nIndexStop, nIndex);
		// ������β�ַ������
		if (nIndex == nIndexEnd) // ���������β
		{
			y += cyChar;   // ����һ�У�y��ʾ��ǰ�����������
		}
		else if (bWordWrap)  // �������ʻ���
		{
			// word-wrap printing
			do
			{
				UINT nIndexWrap = ClipLine(pDC, aCharWidths,
					cx, nTabStop, lpszText, nIndex, nIndexEnd);
				// ����ʻ���ʱ��β�ַ������
				UINT nIndexWord = nIndexWrap; // ����һ�����������ֵ
				if (nIndexWord != nIndexEnd) // �����β�ַ���Ų�������β���
				{
					while (nIndexWord > nIndex &&
					  !isspace(lpszText[nIndexWord]))
					{ // �����β�ַ���Ŵ��ڵ�ǰ�ַ���Ų�����β�ַ���Ų��ǿհ�
						nIndexWord--;  // ��β�ַ����������
					}
					if (nIndexWord == nIndex) // ����Ƶ���ǰ�ַ�
						nIndexWord = nIndexWrap; // ��Ȼ��ԭ�ȼ������β�ַ����Ϊ׼
				}
				CRect rect(rectLayout.left, y, rectLayout.right, y+cyChar);
				// ��ǰ����Ϊһ������
				if (!bLayoutOnly && pDC->RectVisible(rect))
				{ // ���ֻ��������ڵ��ַ����ҵ�ǰ���ǿɼ���
#ifndef _MAC
					pDC->TabbedTextOut(rect.left, y,
						(LPCTSTR)(lpszText+nIndex), nIndexWord-nIndex, 1,
						&nTabStop, rect.left);
#else
					pDC->TextOut(rect.left, y,
						(LPCTSTR)(lpszText+nIndex), nIndexWord-nIndex);
					// ��һ���ʣ����ɸ��ַ����������һ����
#endif
				}
				y += cyChar; // ��һ��
				nIndex = nIndexWord; // �ַ��������
				while (nIndex < nIndexEnd && isspace(lpszText[nIndex]))
					nIndex++; // �������з�֮ǰ�Ŀհ��ַ�
			} while (nIndex < nIndexEnd && y+cyChar <= rectLayout.bottom);
				
			nIndexEnd = nIndex;
		}
		else
		{ // ������شʻ��ƣ���Ҫ�򵥡���ö�
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
		// ��һ�п�ͷ�ַ�
	}
	while (nIndex < nIndexStop && y+cyChar <= rectLayout.bottom);

	pDC->RestoreDC(-1);
	UnlockBuffer();  // �ͷ��ַ���������
	ASSERT_VALID(this);

	rectLayout.bottom = y;
	return nIndex;
}

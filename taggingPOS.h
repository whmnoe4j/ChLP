// taggingPOS.h

#define  uchar  unsigned char

class CCoMatrix : public CObject
{
	DECLARE_SERIAL(CCoMatrix)
private:
  int CorpusSize;	//  ���Ϲ�ģ
  int *TagFreqs;   //  ÿ�ִ��Ա�ǵĳ��ִ�����һά����
  int *Matrix; 	    //  ����Ƶ�Ⱦ�����һά������ģ���ά����
public:
	CStringArray *pTags; // ���Ա�Ǽ�
	CStringArray *pOpenTags; // ���ű�Ǽ�
	BOOL Modified;  // �Ƿ��޸Ĺ����Ա�Ǽ������Ͽ�
	CString FileName;  // ������������ݵ��ļ���
	CCoMatrix( ) {TagFreqs=NULL; Matrix=NULL;} 	// ���캯��
	~CCoMatrix( ) { Clean( ); }  	// ��������
	BOOL Ready( ) { return CorpusSize>0; } // �Ƿ��Ѿ�������Ա�Ǽ���ѵ������
	double GetCoProb(uchar tag1, uchar tag2); // ��ȡ���ת�Ƹ���
	double GetWordProb(double wtFreq, uchar tag);  // ��ȡ�������
	void Create(CStdioFile& tagFile);  // ������Ǽ�������
	void Clean( ); // ���ԭ������
	void AddCorpus(CStdioFile& trainFile); // ����ѵ������
	virtual void Serialize(CArchive& ar);  // ���л�����
	uchar GetIndexOf(CString tag);	// �����Ա��ת��Ϊ���
	CString GetTagOf(uchar i);	// �����ת��Ϊ���Ա��
	int GetTagFreq(uchar i); // ��ĳ�ֱ�ǵ�Ƶ�� 
};

class CSpan
{
private:
  CString Words[20];	//	���20����
  uchar Tags[20][10];		// ÿ���ʵ�ÿ��������
  double Freqs[20][10];	// ÿ���ʵ�ÿ����ǵĳ��ִ���
  char GoodPrev[20][10];	// ÿ���ʵ�ÿ����ǵ����ǰ�����
  char CurLength;	// ��ǰ�ʴ���ʵ�ʳ���
public:
  CSpan( ) {  // ���캯��
	Tags[0][0]=0;	Tags[0][1]=0; // ��0������������
	Freqs[0][0]=0.0; CurLength=1; }
  ~CSpan( ) {} // ��������
  void GetFrom(CString& s);	// ���ַ�����ȡ���ɸ���
  void GuessTag(char i);	    // �²��i���ʵĴ��Ա��
  void Disamb( );	            // �ų��������壬���д��Ա�ע
  void WriteTo(CStdioFile out); // ������/��Ǵ�д������ļ���ȥ
  void Reset( );	// ���ø������ԣ��Ա��ע��һ���ʴ�
};

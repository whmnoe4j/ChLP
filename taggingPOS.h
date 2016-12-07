// taggingPOS.h

#define  uchar  unsigned char

class CCoMatrix : public CObject
{
	DECLARE_SERIAL(CCoMatrix)
private:
  int CorpusSize;	//  语料规模
  int *TagFreqs;   //  每种词性标记的出现次数，一维数组
  int *Matrix; 	    //  共现频度矩阵，用一维数组来模拟二维数组
public:
	CStringArray *pTags; // 词性标记集
	CStringArray *pOpenTags; // 开放标记集
	BOOL Modified;  // 是否修改过词性标记集或语料库
	CString FileName;  // 存放这个类的数据的文件名
	CCoMatrix( ) {TagFreqs=NULL; Matrix=NULL;} 	// 构造函数
	~CCoMatrix( ) { Clean( ); }  	// 构析函数
	BOOL Ready( ) { return CorpusSize>0; } // 是否已经读入词性标记集和训练语料
	double GetCoProb(uchar tag1, uchar tag2); // 获取标记转移概率
	double GetWordProb(double wtFreq, uchar tag);  // 获取词语概率
	void Create(CStdioFile& tagFile);  // 创建标记集、矩阵
	void Clean( ); // 清除原有内容
	void AddCorpus(CStdioFile& trainFile); // 增加训练语料
	virtual void Serialize(CArchive& ar);  // 序列化函数
	uchar GetIndexOf(CString tag);	// 将词性标记转换为序号
	CString GetTagOf(uchar i);	// 将序号转换为词性标记
	int GetTagFreq(uchar i); // 求某种标记的频度 
};

class CSpan
{
private:
  CString Words[20];	//	最多20个词
  uchar Tags[20][10];		// 每个词的每个标记序号
  double Freqs[20][10];	// 每个词的每个标记的出现次数
  char GoodPrev[20][10];	// 每个词的每个标记的最佳前趋标记
  char CurLength;	// 当前词串的实际长度
public:
  CSpan( ) {  // 构造函数
	Tags[0][0]=0;	Tags[0][1]=0; // 第0个标记是虚设的
	Freqs[0][0]=0.0; CurLength=1; }
  ~CSpan( ) {} // 构析函数
  void GetFrom(CString& s);	// 从字符串获取若干个词
  void GuessTag(char i);	    // 猜测第i个词的词性标记
  void Disamb( );	            // 排除词性歧义，进行词性标注
  void WriteTo(CStdioFile out); // 将词语/标记串写到输出文件中去
  void Reset( );	// 重置各项属性，以便标注下一个词串
};

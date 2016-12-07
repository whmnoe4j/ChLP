// parsing.h 自动句法分析所需要的数据结构，包括规则、局部分析等。
class CRule: public CObject
{
public:
	CString Ls, Rs1, Rs2; // 规则的左部符号、右部符号
	CRule( ) { }
	CRule(CString Line); // 从一文本行读入一条规则
};

class CEdge: public CObject
{
public:
	CString Root;  // 局部分析的"根"，包括词语
	int First, Last, Sub1, Sub2;	// 局部分析的起点、终点和构成成分
	CEdge( ) { }
	CEdge(CString wt, int wid);	// 为一个词语建立一个局部分析
	CEdge(CEdge *p, int pid, CString r);	// 运用提升规则建立一个局部分析
	CEdge(CEdge *p1, CEdge *p2, int pid1, int pid2, CString r);
		// 运用捆绑规则建立一个局部分析
	CString GetRoot( ) {  // 返回根的符号（不包括词语）
		int i=Root.Find('(');	
		if(i<0) return Root;  else return Root.Left(i); 
  }
};

CString Parsing(CString s); // 分析一个句子
void Expanding( );	// 根据规则增加局部分析
BOOL GetRule(CString& ls, CString rs1, CString rs2=""); // 查找规则
CString GetTrees(int wid);	// 返回若干个分析树
CString GetOneTree(CEdge *e); // 返回一个局部分析所代表的子树（递归调用）
	
////////

class CProbRule: public CRule
{
public:
  double Prob, DesireCount; // 规则的概率，期望次数
  CProbRule(CString Line); // 重写构造函数
};

class CProbEdge: public CEdge
{
public:
  int RuleId; // 所用规则的序号
  CString Parent; // 更大局部分析的序号集
  double InsideProb, InProbAddUp, OutsideProb; 
  // 内部概率，内部概率之和，外部概率
  CProbEdge(CString wt, int wid):CEdge(wt, wid) 
    { InsideProb=InProbAddUp=1.0; 
		  RuleId=-1;	OutsideProb=0.0;  Parent="";	
    } 
	CProbEdge(CProbEdge *p, int pid, int Rid); 
	CProbEdge(CProbEdge *p1, CProbEdge *p2, int pid1, int pid2, int Rid);
};

CString ProbParsing(CString s, double& sProb);
void GetRuleNewProb( );
void InsertEdges(int first, int last);
void GetOutsideProb(int wn);
void GetDesireCount(double sProb);
int  GetProbRule(CString rs1, CString rs2="");
CString GetProbTrees(int wid);
CString GetOneProbTree(CProbEdge *e);

// parsing.h �Զ��䷨��������Ҫ�����ݽṹ���������򡢾ֲ������ȡ�
class CRule: public CObject
{
public:
	CString Ls, Rs1, Rs2; // ������󲿷��š��Ҳ�����
	CRule( ) { }
	CRule(CString Line); // ��һ�ı��ж���һ������
};

class CEdge: public CObject
{
public:
	CString Root;  // �ֲ�������"��"����������
	int First, Last, Sub1, Sub2;	// �ֲ���������㡢�յ�͹��ɳɷ�
	CEdge( ) { }
	CEdge(CString wt, int wid);	// Ϊһ�����ｨ��һ���ֲ�����
	CEdge(CEdge *p, int pid, CString r);	// ��������������һ���ֲ�����
	CEdge(CEdge *p1, CEdge *p2, int pid1, int pid2, CString r);
		// �������������һ���ֲ�����
	CString GetRoot( ) {  // ���ظ��ķ��ţ����������
		int i=Root.Find('(');	
		if(i<0) return Root;  else return Root.Left(i); 
  }
};

CString Parsing(CString s); // ����һ������
void Expanding( );	// ���ݹ������Ӿֲ�����
BOOL GetRule(CString& ls, CString rs1, CString rs2=""); // ���ҹ���
CString GetTrees(int wid);	// �������ɸ�������
CString GetOneTree(CEdge *e); // ����һ���ֲ�������������������ݹ���ã�
	
////////

class CProbRule: public CRule
{
public:
  double Prob, DesireCount; // ����ĸ��ʣ���������
  CProbRule(CString Line); // ��д���캯��
};

class CProbEdge: public CEdge
{
public:
  int RuleId; // ���ù�������
  CString Parent; // ����ֲ���������ż�
  double InsideProb, InProbAddUp, OutsideProb; 
  // �ڲ����ʣ��ڲ�����֮�ͣ��ⲿ����
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

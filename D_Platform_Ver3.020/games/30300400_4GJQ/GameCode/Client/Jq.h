#pragma once

class CJq
{
public:
	int m_iPs;
	bool IsValidateJq()
	{
		return true;
	}
	///void ShowAJq(CDC* pDC,CPoint ptStart);
public:
	CJq(void);
	CJq(int ps);
	CJq(int hs,int pd);
	~CJq(void);
};


class CPStack
{
public:
	CPtrList List;
	void operator=(const CPStack & pStack)
	{
		memcpy(&List, &pStack.List, sizeof(List));
	}

	bool GetTop(int& i,int& j)
	{
		if(List.IsEmpty ())return false;
		CPoint *p=(CPoint *)List.GetHead  ();
		i=p->x ;
		j=p->y;
		return true;
	}

	void Push(int i,int j)
	{
		CPoint *p=new CPoint();
		p->x =i;
		p->y = j;
		List.AddHead (p);
	}
	bool Pop(int& i,int& j)
	{
		if(List.IsEmpty ())return false;
		CPoint *p=(CPoint *)List.RemoveHead ();
		i=p->x ;
		j=p->y;
		delete p;
		p=NULL;
		return true;
	}
	BOOL IsEmpty()
	{
		return List.IsEmpty () ;
	}
	void Empty()
	{
		while(!List.IsEmpty ())
		{
			CPoint *p=(CPoint *)List.RemoveHead ();
			delete p;
			p=NULL;
		}
		List.RemoveAll ();
	}
	CPStack(){}
	~CPStack()
	{
		Empty();
	}

};



class   CStaticGlbJq
{	
public:
	void  ShowACross(CDC* pDC,CPoint& destCenterPt,int angle);
	void  ShowPath(CDC* pDC, CPoint& destCenterPt, int iDirection, int angle,int x, int y);
	void  ShowAPisa(int ps,CDC* pDC,CPoint& destCenterPt,int angle,bool showback,bool bDraw);
	CRect  GetJqSrcRect(int ps,int angle,bool showback);
	void Init();
	CStaticGlbJq(void)
	{
		p_hp_AllQiZi = NULL;
		Init();
	}
    ~CStaticGlbJq(void)
	{
		if(p_hp_AllQiZi)delete p_hp_AllQiZi;
//		if(p_hp_AllOther)delete p_hp_AllOther;
		p_hp_AllQiZi =NULL;
	}

	CSize  mSzSrcQiZi,mSzGrade;

private:
	CGameImageHelper*		p_hp_AllQiZi;
	///CGameImageHelper* p_hp_AllOther;
	CGameImage  	m_bit_AllQiZi_1024;//,m_bit_AllOther_1024;
	CGameImage  	m_bit_Path;

	CGameImage  m_btOther;

};



extern CStaticGlbJq   g_CStaticGlbMj;


	/*CBitmap* GetAPisa(int ps);

	CBitmap  
				m_bit_jq_r_sl,
				m_bit_jq_r_jz,
				m_bit_jq_r_sz,
				m_bit_jq_r_liz,
				m_bit_jq_r_tz,
				m_bit_jq_r_yz,
				m_bit_jq_r_lianz,
				m_bit_jq_r_pz,
				m_bit_jq_r_gb,
				m_bit_jq_r_dl,
				m_bit_jq_r_jq,
				m_bit_jq_r_zd,
   
				m_bit_jq_b_sl,
				m_bit_jq_b_jz,
				m_bit_jq_b_sz,
				m_bit_jq_b_liz,
				m_bit_jq_b_tz,
				m_bit_jq_b_yz,
				m_bit_jq_b_lianz,
				m_bit_jq_b_pz,
				m_bit_jq_b_gb,
				m_bit_jq_b_dl,
				m_bit_jq_b_jq,
				m_bit_jq_b_zd,


				m_bit_jq_k_sl,
				m_bit_jq_k_jz,
				m_bit_jq_k_sz,
				m_bit_jq_k_liz,
				m_bit_jq_k_tz,
				m_bit_jq_k_yz,
				m_bit_jq_k_lianz,
				m_bit_jq_k_pz,

				m_bit_jq_k_gb,

				m_bit_jq_k_dl,
				m_bit_jq_k_jq,
				m_bit_jq_k_zd,
								
				
				m_bit_jq_g_sl,
				m_bit_jq_g_jz,
				m_bit_jq_g_sz,
				m_bit_jq_g_liz,
				m_bit_jq_g_tz,
				m_bit_jq_g_yz,
				m_bit_jq_g_lianz,
				m_bit_jq_g_pz,

				m_bit_jq_g_gb,

				m_bit_jq_g_dl,
				m_bit_jq_g_jq,
				m_bit_jq_g_zd
				;

				*/


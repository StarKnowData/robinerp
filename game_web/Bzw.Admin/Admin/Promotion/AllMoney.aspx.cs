using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Bzw.Data;
using BCST.Common;

public partial class Admin_Promotion_AllMoney : AdminBasePage
{    
    //public string a, b, c, d,TGUserName;
	public string TGUserName = string.Empty;//推广员用户名。
	public string TGIncome = string.Empty;//有效推广的收入（即被推广玩家的推广度达到100%后，奖励给推广员的金币数。）
	public string TGPayIncome = string.Empty;//推广员抽取被推广玩家充值提成。
	public string TGBalanceMoney = string.Empty;//推广员已结账金币总数。
	public string TGMoneyCount = string.Empty;//推广员未结账的推广收入总数（即TuiGuang.MoneyCount字段值）。
	BLL.Promotion promo = new BLL.Promotion();

    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("13");
		string param = CommonManager.Web.Request("params", "");
		if (string.IsNullOrEmpty(param) || !CommonManager.String.IsInteger(param))
			return;
        if (!IsPostBack)
        {
			string cmdTex = "select isnull(a.MoneyCount,0) as MoneyCount ,b.UserName from Web_TuiGuang a inner join TUsers b on a.UserID=b.UserID where a.UserID=@UserID";
			DataTable dt = DbSession.Default.FromSql(cmdTex)
				.AddInputParameter ("@UserID",DbType.Int32 ,param)
				.ToDataTable();
			if (dt.Rows.Count > 0)
			{
				TGUserName = dt.Rows[0]["UserName"].ToString();
				TGMoneyCount = dt.Rows[0]["MoneyCount"].ToString();
			}
			TGIncome = promo.GetTGIncomeMoney(param);
			TGPayIncome = promo.GetTGPayIncomeMoney(param);
			TGBalanceMoney = promo.GetTGBalancedMoney(param);
			
            /*a = getWp_ClearingLog(Request["id"].ToString());
            c = getWp_TGclearingRecord(Request["id"].ToString());
            d = getWp_TGPayRecord(Request["id"].ToString());
            b = getWp_TuiGuangLog(Request["id"].ToString());
			TGUserName = DbSession.Default.FromSql( "select TGUserName from Web_VTGLog where TG_UserID=" + Request["id"].ToString() ).ToScalar().ToString();
			 */
        }
	}

	#region old
	/*
	/// <summary>
    /// 推广员结账的日志
	/// 
    /// </summary>
    /// <param name="Userid"></param>
    /// <returns></returns>
    public string getWp_ClearingLog(string Userid)
    {
        if (Userid != "")
        {
            string sql = "select sum(Money) as Moneys from Web_ClearingLog where UserID = " + Userid + "";
			dt = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
            if (dt.Rows[0]["Moneys"].ToString() == "" || dt.Rows[0]["Moneys"].ToString() == null)
            {
                return "0";
            }
            else
            {
                return dt.Rows[0]["Moneys"].ToString();
            }
        }
        else
        {
            return null;
        }
    }

    /// <summary>
    /// 得到推广员推广用户记录表的推广员总金额
    /// </summary>
    /// <param name="Userid"></param>
    /// <returns></returns>
    public string getWp_TuiGuangLog(string Userid)
    {
        if (Userid != "")
        {
            string sql = "select sum(GetMoney) as Moneys from Web_TuiGuangLog where TG_UserID = " + Userid + "";
			dt = DbSession.Default.FromSql( sql ).ToDataTable(); 
            if (dt.Rows[0]["Moneys"].ToString() == "" || dt.Rows[0]["Moneys"].ToString() == null)
            {
                return "0";
            }
            else
            {
                return dt.Rows[0]["Moneys"].ToString();
            }
        }
        else
        {
            return null;
        }
    }

    /// <summary>
    /// 推广员抽取被推广玩家充值的提成日志表
    /// </summary>
    /// <param name="Userid"></param>
    /// <returns></returns>
    public string getWp_TGclearingRecord(string Userid)
    {
        if (Userid != "")
        {
            string sql = "select sum(GetMoney) as Moneys from Web_TGclearingRecord where TGUserID = " + Userid + "";
			dt = DbSession.Default.FromSql( sql ).ToDataTable(); 
            if (dt.Rows[0]["Moneys"].ToString() == "" || dt.Rows[0]["Moneys"].ToString() == null)
            {
                return "0";
            }
            else
            {
                return dt.Rows[0]["Moneys"].ToString();
            }
        }
        else
        {
            return null;
        }
    }


    /// <summary>
    /// 得到充值上级得到金币数
    /// </summary>
    /// <param name="Userid"></param>
    /// <returns></returns>
    public string getWp_TGPayRecord(string Userid)
    {
        if (Userid != "")
        {
            string sql = "select sum(GetMoney) as Moneys from Web_TGPayRecord where TGUserID = " + Userid + "";
			dt = DbSession.Default.FromSql( sql ).ToDataTable(); 
            if (dt.Rows[0]["Moneys"].ToString() == "" || dt.Rows[0]["Moneys"].ToString() == null)
            {
                return "0";
            }
            else
            {
                return dt.Rows[0]["Moneys"].ToString();
            }
        }
        else
        {
            return null;
        }
	}*/
	#endregion
}

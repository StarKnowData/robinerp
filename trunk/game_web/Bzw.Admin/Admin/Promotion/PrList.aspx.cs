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

public partial class Admin_Promotion_PrList : AdminBasePage
{
    DataTable dt = new DataTable();
    public int TableID;

    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("13");
		string where = "";
		string urlp = CommonManager.Web.RequestUrlDecode("un", "");
		if (!string.IsNullOrEmpty(urlp))
			where += " and UserName='" + urlp + "'";
		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
				.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
				.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
				.AddInputParameter( "@Columns", DbType.String, "*" )
				.AddInputParameter( "@TableName", DbType.String, "Web_VTuiGuang" )
				.AddInputParameter( "@Wheres", DbType.String, where )
				.AddInputParameter( "@KeyName", DbType.String, "Id" )
				.AddInputParameter( "@OrderBy", DbType.String, "Id desc" )
				.ToDataSet();

		if( ds.Tables.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			if( ds.Tables[1].Rows.Count > 0 )
			{
				OkPrList.Visible = true;
				NoPrList.Visible = false;
				OkPrList.DataSource = ds.Tables[1];
				OkPrList.DataBind();
			}
			else
			{
				OkPrList.Visible = false;
				NoPrList.Visible = true;
			}
		}
	}

	public int GetTGIncome(string userid)
	{
		string tgIncome = new BLL.Promotion().GetTGIncomeMoney(userid);
		string tgPayIncome = new BLL.Promotion().GetTGPayIncomeMoney(userid);
		return (Convert.ToInt32(tgIncome) + Convert.ToInt32(tgPayIncome));
	}
	#region old
	/*
	/// <summary>
    /// 得到记录推广用户申请结算的记录
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
    /// 得到推广员结算后抽水记录表
    /// </summary>
    /// <param name="Userid"></param>
    /// <returns></returns>
    public string getWp_TGclearingRecord(string Userid)
    {
        if (Userid != "")
        {
            string sql = "select sum(GetMoney) as Moneys from Web_TGclearingRecord where TGUserID = " + Userid + "";
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
    /// 得到充值上级得到金币数
    /// </summary>
    /// <param name="Userid"></param>
    /// <returns></returns>
    public string getWp_TGPayRecord(string Userid)
    {
        if (Userid != "")
        {
            string sql = "select sum(GetMoney) as Moneys from Web_TGPayRecord where TGUserID = " + Userid + "";
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
	}*/
	#endregion
}

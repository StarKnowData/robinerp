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
using System.Text;

public partial class Admin_Pay_Pay : AdminBasePage
{
	protected string typepay
	{
		get
		{
			string tmp = CommonManager.Web.Request("pay","");
			if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
				return "1";
			return tmp;
		}
	}
	protected string moneys
	{
		get
		{
			string tmp = CommonManager.Web.Request( "money", "" );
			if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
				return "";
			return tmp;
		}
	}
	protected string bd
	{
		get
		{
			string tmp = CommonManager.Web.Request( "bd", "" );
			if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsDateTime( tmp ) )
				return "";
			return tmp;
		}
	}
	protected string ed
	{
		get
		{
			string tmp = CommonManager.Web.Request( "ed", "" );
			if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsDateTime( tmp ) )
				return "";
			return tmp;
		}
	}

	protected string un
	{
		get
		{
			string tmp = CommonManager.Web.Request( "un", "" );
			if( string.IsNullOrEmpty( tmp ) )
				return "";
			return tmp;
		}
	}

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "05" );
        BatchDelete();
        NoUseDel();
        UsedDel();
        if (!IsPostBack)
        {
            DataTable dt = DbSession.Default.FromSql("select jine as Money from Web_Card group by jine order by jine desc").ToDataTable();
            if (dt.Rows.Count > 0)
            {
                rptMoneyList.DataSource = dt;
                rptMoneyList.DataBind();
            }

            StringBuilder sqlW = new StringBuilder();

            sqlW.Append(" and Pay=" + typepay);
            sqlW.Append(" and ToPoint<>1");
            bool isSearch = false;

            if (!string.IsNullOrEmpty(moneys))
            {
                sqlW.Append(" and jine=" + moneys);
                isSearch = true;
            }
            if (!string.IsNullOrEmpty(un))
            {
                sqlW.Append(" and player='" + Server.UrlDecode(un) + "'");
                isSearch = true;
            }
            if (!string.IsNullOrEmpty(bd))
            {
                sqlW.Append(" and tm>='" + bd + " 00:00:00'");
                isSearch = true;
            }
            if (!string.IsNullOrEmpty(ed))
            {
                sqlW.Append(" and tm<='" + ed + " 23:59:59'");
                isSearch = true;
            }

            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                    .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                    .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                    .AddInputParameter("@Columns", DbType.String, "*")
                    .AddInputParameter("@TableName", DbType.String, "Web_Card")
                    .AddInputParameter("@Wheres", DbType.String, sqlW.ToString())
                    .AddInputParameter("@KeyName", DbType.String, "ID")
                    .AddInputParameter("@OrderBy", DbType.String, "tm desc,ID desc")
                    .ToDataSet();

            if (ds.Tables.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;

                if (ds.Tables[1].Rows.Count > 0)
                {
                    rptDataList.Visible = true;
                    ltNonData.Visible = false;
                    rptDataList.DataSource = ds.Tables[1];
                    rptDataList.DataBind();
                }
                else
                {
                    rptDataList.Visible = false;
                    ltNonData.Visible = true;
                }
            }

            if (isSearch)
            {
                //按条件统计
                int summoney = DbSession.Default.FromSql("select isnull(sum(jine),0) as AllMoney from Web_Card where 1=1 " + sqlW.ToString()).ToScalar<int>();
                ltSumInfo.Text = "符合您搜索条件的数据，充值金额共计：<strong style='color:red;'>" + summoney.ToString("C0") + "</strong>元。";
            }
            else
            {
                //总统计
                int summoney = DbSession.Default.FromSql("select isnull(sum(jine),0) as SumMoney from Web_Card where Pay=1 and ToPoint<>1 ").ToScalar<int>();
                ltSumInfo.Text = "总充值金额共计：<strong style='color:red;'>" + summoney.ToString("C0") + "</strong>元。";
            }
        }
	}
    //批量删除
    public void BatchDelete()
    { 
          string act = Utility.Common.GetStringOfUrl("batchaction");
        string id = Utility.Common.GetStringOfUrl("uid");
        if (act.ToLower() == "batchdel")
        {
            DbSession.Default.FromSql("Delete from Web_Card where id in ("+id+")").Execute();
            Response.Write("<script>alert('温馨提示：\\n\\n批量删除操作成功！');location.href='" + Request.Url.ToString().Substring(0, Request.Url.ToString().IndexOf("batchaction")) + "'; </script>");
        }
        
    }
    //删除全部未充值点卡
    public void NoUseDel()
    { 
       
          string act = Utility.Common.GetStringOfUrl("batchaction");
        string id = Utility.Common.GetStringOfUrl("uid");
        if (act.ToLower() == "nousedel")
        {
            DbSession.Default.FromSql("Delete from Web_Card where pay=0").Execute();
            Response.Write("<script>alert('温馨提示：\\n\\n删除全部未充值点卡操作成功！');</script>");
        }
    }

    //删除全部充值了的点卡
    public void UsedDel()
    { 
    
          string act = Utility.Common.GetStringOfUrl("batchaction");
        string id = Utility.Common.GetStringOfUrl("uid");
        if (act.ToLower() == "usedel")
        {
            DbSession.Default.FromSql("Delete from Web_Card where pay=1").Execute();
            Response.Write("<script>alert('温馨提示：\\n\\n删除全部充值了的点卡操作成功！');</script>");
        }
    }
}

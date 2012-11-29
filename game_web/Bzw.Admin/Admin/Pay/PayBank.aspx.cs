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
using BCST.Common;
using Bzw.Data;

public partial class Admin_Pay_PayBank : AdminBasePage
{
    public string lbState = "成功";
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("05");

		#region oldcode
		//DataTable sd = new DataTable();
		//string para = "";
		//string[] sql = new string[2];
		//sql[0] = "select * from web_RMBCost order by payid desc";
		//sql[1] = "select count(*) from web_RMBCost";
		//string url = "PayBank.aspx";
		//PageLink page_set = new PageLink(url, 20, 10, para, sql);
		//page_set.paraLinkType = paraLinkShow.middling.ToString();
		//sd = page_set.get_table();
		//if (sd.Rows.Count > 0)
		//{
		//    Repeater Vista = (Repeater)Page.FindControl("PayBankList");
		//    Vista.DataSource = sd;
		//    Vista.DataBind();
		//    this.pageList.Text = page_set.pageList();
		//}
		//else
		//    this.NoPayBank.Visible = true;
		//sd.Clear();
		#endregion

        string payState = string.Empty;
        string where = " AND InSuccess=1 AND PaySuccess=1 ";
        string ps = CommonManager.Web.Request("ps", "");
        if (ps == "failed")
        {
            where = " AND InSuccess=0 AND PaySuccess=0 ";
            lbState = "失败";
        }
        string userid = CommonManager.Web.Request("un", "");
        if (userid != "")
        {
            where += " and users_ids="+userid;
            
        }
        //if (Request.QueryString["PayState"] != null && Request.QueryString["PayState"].ToString().Length > 0)
        //{
        //    payState = Request.QueryString["PayState"].ToString();
        //}
        //if (payState.Equals("Failed"))
        //{
        //    where = " AND InSuccess=0 AND PaySuccess=0 ";
        //    lbState = "失败";
        //}
        string ord = Utility.Common.GetStringOfUrl("ord");
        string orderTtype = Utility.Common.GetStringOfUrl("ordType");
        if (string.IsNullOrEmpty(ord))
        {
            ord = "PayID";
            orderTtype = " desc ";
        }
		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
			.AddInputParameter( "@Columns", DbType.String, "*" )
			.AddInputParameter( "@TableName", DbType.String, "Web_RMBCost" )
			.AddInputParameter( "@Wheres", DbType.String, where)
			.AddInputParameter( "@KeyName", DbType.String, ord )
			.AddInputParameter( "@OrderBy", DbType.String, ord+" " +orderTtype )
			.ToDataSet();

		if( ds.Tables.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			if( ds.Tables[1].Rows.Count > 0 )
			{
				rptDataList.Visible = true;
				rptDataList.DataSource = ds.Tables[1];
				rptDataList.DataBind();
				ltNonData.Visible = false;
                lblSumMoney.Text = "总金额：" + DbSession.Default.FromSql("  SELECT SUM(PayMoney) FROM  Web_RMBCost where 1=1 "+where).ToScalar();
			}
			else
			{
				ltNonData.Visible = true;
				rptDataList.Visible = false;
			}
		}
    }
}

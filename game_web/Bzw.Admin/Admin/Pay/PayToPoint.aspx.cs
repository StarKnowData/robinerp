using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;

 
    public partial class Admin_Pay_PayToPoint : AdminBasePage
    {
        public string lbState = "成功";
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("05");
            if (!string.IsNullOrEmpty(Request.QueryString["act"]) && CommonManager.Web.Request("id", "")!="")
            {
                DelLog();
            }
            string payState = string.Empty;
            string where="" ;
            string ps = CommonManager.Web.Request("ps", "");
            if (ps == "failed")
            {
                where = " AND InSuccess=0 AND PaySuccess=0 ";
                lbState = "失败";
            }
            else
            {
                where = " AND InSuccess=1 AND PaySuccess=1 ";
                lbState = "成功";
            }
            string userid = CommonManager.Web.Request("un", "");
            if (userid != "")
            {
                where += " and UserID=" + userid;

            }
            string ord = Utility.Common.GetStringOfUrl("ord");
            string orderTtype = Utility.Common.GetStringOfUrl("ordType");
            if (string.IsNullOrEmpty(ord))
            {
                ord = "ID";
                orderTtype = " desc ";
            }
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
            .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
            .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
            .AddInputParameter("@Columns", DbType.String, "*")
            .AddInputParameter("@TableName", DbType.String, "Web_PointChangeLog")
            .AddInputParameter("@Wheres", DbType.String, where)
            .AddInputParameter("@KeyName", DbType.String, ord)
            .AddInputParameter("@OrderBy", DbType.String, ord + " " + orderTtype)
            .ToDataSet();

            if (ds.Tables.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;

                if (ds.Tables[1].Rows.Count > 0)
                {
                    rptDataList.Visible = true;
                    rptDataList.DataSource = ds.Tables[1];
                    rptDataList.DataBind();
                    ltNonData.Visible = false;
                    lblSumMoney.Text = "总金额：" + DbSession.Default.FromSql("  SELECT SUM(PayMoney) FROM  Web_PointChangeLog where 1=1 " + where).ToScalar();
                }
                else
                {
                    ltNonData.Visible = true;
                    rptDataList.Visible = false;
                }
            }
        }
        public void DelLog()
        {
            string tmp = CommonManager.Web.Request("id", "");
            if (string.IsNullOrEmpty(tmp) || !CommonManager.String.IsInteger(tmp))
            {
                Alert("请勿非法操作！", null);
                return;
            }
            string sql = "delete from Web_PointChangeLog where ID=" + tmp + "";
           
            DbSession.Default.FromSql(sql).Execute();
            Response.Write("<script>alert('删除操作成功！');location.href='PayToPoint.aspx';</script>");
        }
    }
 

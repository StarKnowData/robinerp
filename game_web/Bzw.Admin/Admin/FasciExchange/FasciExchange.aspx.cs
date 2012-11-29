using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Bzw.Data;
using System.Data;
using BCST.Common;

 
    public partial class Admin_FasciExchange_FasciExchange : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                AdminPopedom.IsHoldModel("16");
                DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
               .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
               .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
               .AddInputParameter("@Columns", DbType.String, "*")
               .AddInputParameter("@TableName", DbType.String, "Web_VCharmExchange")
               .AddInputParameter("@Wheres", DbType.String, "")
               .AddInputParameter("@KeyName", DbType.String, "PropID")
               .AddInputParameter("@OrderBy", DbType.String, "PropID desc")
               .ToDataSet();

                if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
                {
                    anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                    anpPageIndex.CurrentPageIndex = PageIndex;

                    rptDataList.DataSource = ds.Tables[1];
                    rptDataList.DataBind();
                    rptDataList.Visible = true;
                    ltNonData.Visible = false;
                }
                else
                {
                    rptDataList.Visible = false;
                    ltNonData.Visible = true;
                }
                if (CommonManager.Web.Request("act", "") == "del")
                {
                    DelCharmExchange();
                }
            }
        }
        private void DelCharmExchange()
        {
            string id = CommonManager.Web.Request("id", "0");
          
            DbSession.Default.FromSql("delete from TCharmExchange where id=" + id).Execute();
            CommonManager.Web.RegJs(this, "alert('删除成功！');location.href='FasciExchange.aspx';", false);
        }
    }
 

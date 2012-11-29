using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;

 
    public partial class Admin_Lotter_PrUserList : AdminBasePage
    {
        public int TableIds;
        protected void Page_Load(object sender, EventArgs e)
        {
             AdminPopedom.IsHoldModel("18");
             if (!IsPostBack)
             {
                 if (CommonManager.Web.Request("act", "") == "")
                 {
                     DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                          .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                          .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                          .AddInputParameter("@Columns", DbType.String, "*")
                          .AddInputParameter("@TableName", DbType.String, "Web_VLotterSpecial")
                          .AddInputParameter("@Wheres", DbType.String, "")
                          .AddInputParameter("@KeyName", DbType.String, "ID")
                          .AddInputParameter("@OrderBy", DbType.String, "ID desc")
                          .ToDataSet();

                     if (ds.Tables.Count > 0)
                     {
                         anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                         anpPageIndex.CurrentPageIndex = PageIndex;

                         if (ds.Tables[1].Rows.Count > 0)
                         {
                             PrizesList.Visible = true;
                             NoPrizesList.Visible = false;
                             PrizesList.DataSource = ds.Tables[1];
                             PrizesList.DataBind();
                         }
                         else
                         {
                             PrizesList.Visible = false;
                             NoPrizesList.Visible = true;
                         }
                     }
                     ds.Clear();
                 }
                 else
                 {
                     DeleteLog();
                 }
             }
        }
        private void DeleteLog()
        {
            string id = CommonManager.Web.Request("id", "");
            if (id != "")
                DbSession.Default.FromSql("delete from Web_LotterSpecial where id=" + id).Execute();
            CommonManager.Web.RegJs(this, "PrUserList.aspx");
        }
    }
 

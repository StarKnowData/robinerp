using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;

 
    public partial class Admin_Lotter_LotterLog : AdminBasePage
    {
        public int TableIds;
        protected void Page_Load(object sender, EventArgs e)
        {

            AdminPopedom.IsHoldModel("18");
            if (!IsPostBack)
            {
                if (Request.QueryString["act"] == null )
                {
                    BindList();
                }
                else if (Request.QueryString["act"] == "del")
                {
                    DeleteLog();
                }
                else  if(  Request.QueryString["act"]=="edit")
                { 
                EditLotterLog();
                }
            }
        }
        private void BindList()
        {
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                               .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                               .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                               .AddInputParameter("@Columns", DbType.String, "*")
                               .AddInputParameter("@TableName", DbType.String, "Web_VLotterLog")
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
        private void DeleteLog()
        {
            string logid = CommonManager.Web.Request("id", "");
            if (logid != "")
                DbSession.Default.FromSql("delete from Web_LotterLog where id=" + logid).Execute();
            CommonManager.Web.RegJs(this, "alert('操作成功！');", false);
            BindList();
        }
        private void EditLotterLog()
        {
            string logid = CommonManager.Web.Request("id", "");
            string sta = CommonManager.Web.Request("sta", "0");
            string strstatus =( (sta.Equals("0")) ? "1" : "0");
          
            if (logid != "")
                DbSession.Default.FromSql("update  Web_LotterLog set [status]="+strstatus+"  where id=" + logid).Execute();
            CommonManager.Web.RegJs(this, "alert('操作成功！');", false);
            BindList();
        }
    }
 

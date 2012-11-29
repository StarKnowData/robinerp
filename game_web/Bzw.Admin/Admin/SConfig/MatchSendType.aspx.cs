using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;


public partial class Admin_SConfig_MatchSendType : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("18");
            if (!IsPostBack)
            {
                DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                    .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                    .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                    .AddInputParameter("@Columns", DbType.String, "*")
                    .AddInputParameter("@TableName", DbType.String, "Web_MatchSendType")
                    .AddInputParameter("@Wheres", DbType.String, "")
                    .AddInputParameter("@KeyName", DbType.String, "ID")
                    .AddInputParameter("@OrderBy", DbType.String, "ID DESC")
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
            }

            string action = CommonManager.Web.Request("action", "");
            if (string.IsNullOrEmpty(action))
                return;
            switch (action)
            {
                case "edit":
                    EditInfo();
                    break;
                case "del":
                    DelInfo();
                    return;
                default:
                    break;
            }
        }
        private void EditInfo()
        {
             
            string aid = CommonManager.Web.Request("params", "");
            if (IsPostBack || !CommonManager.String.IsInteger(aid))
                return;
            DataTable dt = DbSession.Default.FromSql("select * from Web_MatchSendType where ID=" + aid).ToDataTable();
            if (dt.Rows.Count <= 0 || IsPostBack)
                return;
            DataRow row = dt.Rows[0];
            txtName.Text = row["Name"].ToString();
           
            btnSubmit.Text = " 修 改 ";
        }

        private void DelInfo()
        {
            string aid = CommonManager.Web.Request("params", "");
            if (!CommonManager.String.IsInteger(aid))
                return;
            DbSession.Default.FromSql("delete Web_MatchSendType where ID=" + aid).Execute();
            CommonManager.Web.RegJs(this, "alert('刪除成功！');location.href='MatchSendType.aspx';", true);
        }

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            if (!CommonManager.Web.CheckPostSource())
                return;
            if (!IsValid)
                return;
     
            string ID = CommonManager.Web.Request("params", "0"); 
            string sql = "";
            if (!CommonManager.String.IsInteger(ID) || int.Parse(ID) <= 0)
            {

                sql = "insert into Web_MatchSendType (Name) values (@Name)";
            }
            else
            {
                sql = "update Web_MatchSendType set name=@Name where ID=@ID";
            }

            string reurl = CommonManager.Web.RequestHtmlDecode("reurl", "");
            string location = string.Empty;
            if (!string.IsNullOrEmpty(location))
                location = reurl;
            else
                location = Request.Url.AbsoluteUri;

            DbSession.Default.FromSql(sql)
                .AddInputParameter("@Name", DbType.Int32, txtName.Text.Trim()) 
                .AddInputParameter("@ID", DbType.Int32, ID)
                .Execute();
 
            CommonManager.Web.RegJs(this.Page, "alert('操作成功！');location.href='" + location + "';", true);
        }
    }
 

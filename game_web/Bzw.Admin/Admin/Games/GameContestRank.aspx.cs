using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;

 
    public partial class Admin_Games_GameContestRank : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
        //    string contestid = "0";
            if (Request.QueryString["id"] == null)
            {
                return;
            }
    
         
                BindList();
         
          
        }

        public void BindList()
        {
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                 .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                 .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                 .AddInputParameter("@Columns", DbType.String, "*")
                 .AddInputParameter("@TableName", DbType.String, "Web_VMatchLog")
                 .AddInputParameter("@Wheres", DbType.String, " and contestid=" + Request.QueryString["id"])
                 .AddInputParameter("@KeyName", DbType.String, "ContestID")
                 .AddInputParameter("@OrderBy", DbType.String, "ContestScore desc")
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
            ds.Clear();
        }
        //生成排行榜
        protected void btnAddRank_Click(object sender, EventArgs e)
        {
            DbSession.Default.FromProc("Web_pMatchRank").AddInputParameter("@ContestID", DbType.Int32, Request.QueryString["id"]).Execute();
            Alert("操作成功！", "GameContestRooms.aspx");
        }
    }
 

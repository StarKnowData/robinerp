using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;
using Utility;
using System.Text.RegularExpressions;

 
    public partial class Admin_Games_GameContestRooms : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("06");

            string action = CommonManager.Web.Request("action", "");
            if (!string.IsNullOrEmpty(action))
            {
                //处理页面指令
                switch (action)
                {
                    case "del":
                        //删除
                        Del();
                        break;
                    default:
                        break;
                }
            }
            BindList();
        }
        private void BindList()
        {
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                .AddInputParameter("@Columns", DbType.String, "*")
                .AddInputParameter("@TableName", DbType.String, "Web_VTContestRoom")
                .AddInputParameter("@Wheres", DbType.String, "")
                .AddInputParameter("@KeyName", DbType.String, "ContestID")
                .AddInputParameter("@OrderBy", DbType.String, "ContestID")
                .ToDataSet();

            if (ds.Tables.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;

                if (ds.Tables[1].Rows.Count > 0)
                {
                    rptDataList.Visible = true;
                    lbNonData.Visible = false;
                    rptDataList.DataSource = ds.Tables[1];
                    rptDataList.DataBind();
                }
                else
                {
                    rptDataList.Visible = false;
                    lbNonData.Visible = true;
                }
            }
            ds.Clear();
          
        }
        private void Del()
        {
            string id = CommonManager.Web.Request("params", "");
            if (string.IsNullOrEmpty(id) || !CommonManager.String.IsInteger(id))
                return;

            DbSession.Default.FromSql("delete from TContestInfo where contestid=" + id + "  update TGameRoomBase set ContestID=0 where ContestID=" + id).Execute();
            DbSession.Default.FromSql("delete from TContestUserRecord where  ContestID=" + id ).Execute();
 
            string adminName = AdminInfo["UserName"].ToString();
            string descript = "删除一个比赛场信息，ID号：" + id + ";删除比赛记录排行。";
            string system = Utility.Common.GetOS;
            new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 1);
            string url = Regex.Replace(Request.Url.AbsoluteUri, "[?&]{1}action=del&params=[\\d+|,]+&?", "");
            CommonManager.Web.ResponseEnd(url, true);
        }
    }
 

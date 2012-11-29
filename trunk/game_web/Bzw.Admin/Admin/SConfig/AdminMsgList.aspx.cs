using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;

 
    public partial class Admin_SConfig_AdminMsgList : AdminBasePage
    {
        public int TableID;
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("18");
            int counts;
            if (!IsPostBack)
            {
                if (Request.QueryString["act"] != null && Request.QueryString["act"] == "Del")
                {
                    DeleteMsg();
                }
                else
                {
                    DataTable sd = Utility.SqlHelper.ExecuteDataPager("Web_AdminEmail", "MsgID", "*", "MsgID", 1, WebPager1.PageSize, PageIndex, out counts, "");

                    if (sd.Rows.Count > 0)
                    {
                        this.NoDataList.Visible = false;
                        Messagelist.DataSource = sd;
                        Messagelist.DataBind();
                    }
                    else
                    {

                        this.NoDataList.Visible = true;
                    }
                    sd.Clear();
                }
            }
        }
        protected void DeleteMsg()
        {
            DbSession.Default.FromSql("delete from Web_AdminEmail where msgid=" + Request.QueryString["id"]).Execute();
            CreateHtml ch = new CreateHtml();
            ch.DeleteHtml(Server.MapPath("/Html/Msg/MsgHtml" + Request.QueryString["id"] + ".html"));
            Alert("删除成功！", "AdminMsgList.aspx");
        }

    }
 

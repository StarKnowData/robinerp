using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;


public partial class Admin_Users_GameMoneyList : AdminBasePage
    {
    protected string UserID
    {
        get
        {
            return CommonManager.Web.RequestUrlDecode("params", "");
        }
    }
    public string uname;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(UserID))
            {
                CommonManager.Web.RegJs(this, "history.back();", false);
                return;
            }
            if (!IsPostBack)
            {
                ltUserName.Text = new BLL.Member().GetUserName(UserID);
                dataBindList();
            }
        }
        public void dataBindList()
        {
            string where = " and userid='" + UserID + "'";
            int counts;
            DataTable dt = Utility.SqlHelper.ExecuteDataPager("Web_VuserGameMoney", "GameID", "*", "GameID", 1, WebPager1.PageSize, WebPager1.CurrentPageIndex, out counts, where);
            WebPager1.RecordCount = counts;

            if (dt.Rows.Count > 0)
            {
                rptPayBankList.DataSource = dt;
                rptPayBankList.DataBind();

                ltNoRecord.Visible = false;
                WebPager1.Visible = true;
            }
            else
            {
                ltNoRecord.Visible = true;
                WebPager1.Visible = false;
            }

        }
        protected void WebPager1_PageChanging(object src, Wuqi.Webdiyer.PageChangingEventArgs e)
        {
            this.WebPager1.CurrentPageIndex = e.NewPageIndex;
            dataBindList();
        }
    }
 

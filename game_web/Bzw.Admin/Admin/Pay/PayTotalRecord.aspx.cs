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
using System.Data.SqlClient;
using BCST.Common;
using Bzw.Data;


public partial class Admin_Pay_PayTotalRecord : AdminBasePage
{
    public int Userids = 0;
    public int totalCardMoney = 0;
    public int totalMoney = 0;
    protected string UserName
    {
        get
        {
            return CommonManager.Web.RequestUrlDecode("params", "");
        }
    }
    protected void Page_Load(object sender, EventArgs e)
    {   
        if (string.IsNullOrEmpty(UserName))
        {
            CommonManager.Web.RegJs(this, "history.back();", false);
            return;
        }
        if (!IsPostBack)
        {
            ltUserName.Text = UserName;
            dataBindList();    
        }
    }
    public void dataBindList()
    {  
        string where = " and UserName='" + UserName + "'";    
        int counts;
        DataTable dt = Utility.SqlHelper.ExecuteDataPager("web_VPayTotalRecord", "OperationNum", "*", "AddTime", 1, WebPager1.PageSize, WebPager1.CurrentPageIndex, out counts, where);
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
    /*
    public void GetTotalMoney(string where)
    {
        string sqlPay = "Select isnull(Sum(Account),0) as AccountTotalByType from web_VPayTotalRecord where 1=1 " + where;
        //Response.Write(sqlPay);
        //Response.End();
        DataTable dt = DbSession.Default.FromSql(sqlPay).ToDataTable();
        if (dt.Rows.Count > 0)
        {
            totalMoney = Convert.ToInt32(dt.Rows[0]["AccountTotalByType"]);
        }
        string sqlPay1 = "Select isnull(Sum(Account),0) as AccountTotalByType from web_VPayTotalRecord where PayType=0 " + where;

        DataTable dt1 = DbSession.Default.FromSql(sqlPay1).ToDataTable();
        if (dt1.Rows.Count > 0)
        {
            totalCardMoney = Convert.ToInt32(dt1.Rows[0]["AccountTotalByType"]);
        }        
    }*/
}

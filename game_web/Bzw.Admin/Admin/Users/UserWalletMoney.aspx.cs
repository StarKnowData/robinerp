using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;


public partial class Admin_Users_UserWalletMoney : AdminBasePage
{
    public string UserID;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("04");
        if (Request["UserID"] != "")
        {
            UserID = Request["UserID"].ToString();
        }
        BindList();
    }
    protected void BindList()
    {
        if (UserID!=null &&  UserID != "")
        { 
        
       
        DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                .AddInputParameter("@Columns", DbType.String, "*")
                .AddInputParameter("@TableName", DbType.String, "Web_VUserGameMoney")
                .AddInputParameter("@Wheres", DbType.String, " and Userid="+UserID)
                .AddInputParameter("@KeyName", DbType.String, "GameID")
                .AddInputParameter("@OrderBy", DbType.String, "GameID desc")
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
        }
    }
}

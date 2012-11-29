using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;


public partial class Admin_SConfig_ReceiveMoneyEdit : AdminBasePage
{
    int rid = 0;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("12");
        if (!IsPostBack)
        {
           
            if (Request.QueryString["id"] != null && Request.QueryString["id"] != "")
            {
                rid = Convert.ToInt32(Request.QueryString["id"]);
                DataTable dt = DbSession.Default.FromSql("select * from TReceiveMoneyDefind where id=" + rid).ToDataTable();
                if (dt.Rows.Count > 0)
                {
                    txtMinMoney.Text = dt.Rows[0]["MinMoney"].ToString();
                    txtReceiveMoney.Text = dt.Rows[0]["ReceiveMoney"].ToString();
                    txtSpaceTime.Text = dt.Rows[0]["SpaceTime"].ToString();
                }
            }

        }
    }

    protected void ReceiveMoneyEdit(object sender, EventArgs e)
    {
        string strMoney = txtReceiveMoney.Text.Trim();
        rid = Convert.ToInt32(Request.QueryString["id"]);
        if (!CommonManager.String.IsInteger(strMoney) || Convert.ToInt32(strMoney) < 0)
        {
            CommonManager.Web.RegJs(this.Page, "alert('领取金币数请输入大于或等于0的整数！');", true);
            return;
        }
        if (!CommonManager.String.IsInteger(txtMinMoney.Text.Trim()) || Convert.ToInt32(txtMinMoney.Text.Trim()) < 0)
        {
            CommonManager.Web.RegJs(this.Page, "alert('领取金币的底线金币数请输入大于或等于0的整数！');", true);
            return;
        }
        if (!CommonManager.String.IsInteger(txtSpaceTime.Text.Trim()) || Convert.ToInt32(txtSpaceTime.Text.Trim()) < 0)
        {
            CommonManager.Web.RegJs(this.Page, "alert('时间间隔请输入大于或等于0的整数！');", true);
            return;
        }
    
        int SqlState = DbSession.Default.FromSql("update TreceiveMoneyDefind  set ReceiveMoney=@ReceiveMoney,MinMoney=@MinMoney,SpaceTime=@SpaceTime where id="+rid)
            .AddInputParameter("@ReceiveMoney", DbType.Int32, txtReceiveMoney.Text.Trim())
            .AddInputParameter("@MinMoney", DbType.Int32, txtMinMoney.Text.Trim())
            .AddInputParameter("@SpaceTime", DbType.String, txtSpaceTime.Text) 
            .Execute();

        if (SqlState > 0)
            CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n设置修改成功！');location.href='ReceiveMoneySettings.aspx'", true);
        else
            CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n设置修改失败！');", true);
    }
     
}

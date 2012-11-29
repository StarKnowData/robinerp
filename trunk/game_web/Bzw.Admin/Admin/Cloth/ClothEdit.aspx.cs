using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;


public partial class Admin_Cloth_ClothEdit : AdminBasePage
{
    string Cid;
    public string Price, LogName, SendLotteries, Descript, ImgSrc;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("20");
        Cid = CommonManager.Web.Request("id", "");
        if (!CommonManager.String.IsInteger(Cid))
            CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n请勿非法操作！');history.back();", false);

        DataTable sd = DbSession.Default.FromSql("select *  from Web_Clothes where ID=@ID")
            .AddInputParameter("@ID", DbType.Int32, Cid)
            .ToDataTable();
        if (sd.Rows.Count > 0)
        {
       
            Price = sd.Rows[0]["Price"].ToString();
            LogName = sd.Rows[0]["LogName"].ToString();
            SendLotteries = sd.Rows[0]["SendLotteries"].ToString();
            Descript = sd.Rows[0]["Descript"].ToString();
            ImgSrc = "/Image/Users/" + ((sd.Rows[0]["Sex"].ToString() == "True") ? "b_" + (Convert.ToInt32(sd.Rows[0]["LogID"].ToString()) + 1) + ".png" : "g_" + (Convert.ToInt32(sd.Rows[0]["LogID"].ToString()) + 1) + ".png");
        }
        sd.Clear();
    }

    protected void btnSumbit_Click(object sender, EventArgs e)
    {
        string sqlLogName, sqlPrice, sqlSendLotteries, sqlDesc;
        sqlLogName = CommonManager.Web.RequestForm("LogName", "");
        sqlPrice = CommonManager.Web.RequestForm("Price", "0");
        sqlSendLotteries = CommonManager.Web.RequestForm("SendLotteries", "0");
        sqlDesc = CommonManager.Web.RequestForm("Descript", "");
        if (sqlSendLotteries.Trim().Length > 25)
        {
            CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\描述的字数不能超过500！');location.href=location.href;", false);
            return;
        }
        DbSession.Default.FromSql("UpDate Web_Clothes set LogName=@LogName,Price=@Price,SendLotteries=@SendLotteries,Descript=@Descript where ID=@ID")
                                .AddInputParameter("@ID", DbType.Int32, Cid)
                                 .AddInputParameter("@LogName", DbType.String, sqlLogName)
                                 .AddInputParameter("@Price", DbType.Int64, sqlPrice)
                                 .AddInputParameter("@SendLotteries", DbType.Int32, sqlSendLotteries)
                                 .AddInputParameter("@Descript", DbType.String, sqlDesc)
                                 .Execute();
        CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n修改成功！');location.href=location.href;", false);
    }
}

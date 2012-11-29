using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;


public partial class Admin_SConfig_ReceiveMoneyConfig : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
             AdminPopedom.IsHoldModel("12");
            
        }

        protected void ReceiveMoneyEdit(object sender, EventArgs e)
        {
            string strMoney = txtReceiveMoney.Text.Trim();
            string strID = DbSession.Default.FromSql("select isnull(max(ID),0) from TreceiveMoneyDefind").ToScalar().ToString();
        
                strID = (Convert.ToInt32(strID) + 1).ToString();
            
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
            
            int SqlState = DbSession.Default.FromSql("insert into TreceiveMoneyDefind(ID,ReceiveMoney,MinMoney,SpaceTime) values(@ID,@ReceiveMoney,@MinMoney,@SpaceTime)")
                .AddInputParameter("@ReceiveMoney", DbType.Int32, txtReceiveMoney.Text.Trim())
                .AddInputParameter("@MinMoney", DbType.Int32, txtMinMoney.Text.Trim())
                .AddInputParameter("@SpaceTime", DbType.String, txtSpaceTime.Text)
                .AddInputParameter("@ID",DbType.Int32,strID)
                .Execute();

            if (SqlState > 0)
                CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n设置成功！');location.href='ReceiveMoneySettings.aspx'", true);
            else
                CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n设置失败！！');", true);
        }

    }


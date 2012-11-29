using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using Bzw.Data;
using System.Data;

 
    public partial class Admin_FasciExchange_FasciPrizeAdd : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("16");
        }

        protected void PrCsEdit(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("16");
            string PrizeName, FasciNum, PropCount;
            PrizeName = CommonManager.Web.Request("PrizeName", "");
            if (PrizeName == "")
            {
                CommonManager.Web.RegJs(this, "alert('奖品名称不能为空！');location.href=location.href;", false);      
            }
            if (Convert.ToInt32(DbSession.Default.FromSql("select count(0) from TPropDefine where propname='" + PrizeName.Trim() + "'").ToScalar()) > 0)
            {
                CommonManager.Web.RegJs(this, "alert('奖品名称已存在！');location.href=location.href;", false);      
            }
            FasciNum = CommonManager.Web.Request("FasciNum", "0");

            if (!CommonManager.String.IsInteger(FasciNum) || Convert.ToInt32(FasciNum)<=0)
            {
                CommonManager.Web.RegJs(this, "alert('魅力值数必须为大于0的整数！');location.href=location.href;", false);
            }

            PropCount = CommonManager.Web.Request("PropCount", "0");

            if (!CommonManager.String.IsInteger(PropCount) || Convert.ToInt32(PropCount) <= 0)
            {
                CommonManager.Web.RegJs(this, "alert('道具数必须为大于0的整数！');location.href=location.href;", false);
            }
            
            //插入奖品数据到道具表中,并且添加魅力兑换设置
       int sqlStatus=     DbSession.Default.FromProc("Web_pPropAdd").AddInputParameter("@PrizeName",DbType.String,PrizeName)
                .AddInputParameter("@FasicNum", DbType.Int32, FasciNum)
                .AddInputParameter("@PropCount",DbType.Int32,PropCount)
                .Execute();
       if (sqlStatus > 0)
           CommonManager.Web.RegJs(this, "alert('设置成功！');location.href='FasciExchange.aspx';", false);
       else
           CommonManager.Web.RegJs(this, "alert('设置失败！');history.go(-1);", false);
        }
    }
 

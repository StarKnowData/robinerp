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

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_VipApply : UiCommon.ManageBasePage
    {
        /// <summary>
        /// Head1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

        /// <summary>
        /// webmeta1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webmeta1;

        /// <summary>
        /// webtop1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webtop1;

        /// <summary>
        /// Left1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl Left1;

        /// <summary>
        /// webuserlogin1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webuserlogin1;

        /// <summary>
        /// lblVipState 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal lblVipState;

        /// <summary>
        /// Form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm Form1;

        /// <summary>
        /// lblMsg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Label lblMsg;

        /// <summary>
        /// ddlVipType 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.DropDownList ddlVipType;

        /// <summary>
        /// button5 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputSubmit button5;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        public int MoneyToViptimeDay = 0;
        public int MoneyToViptimeWeek = 0;
        public int MoneyToViptimeMonth = 0;
        public int MoneyToViptimeHYear = 0;
        public int MoneyToViptimeYear = 0;

        public string VipTime2 = "";

        protected void Page_Load(object sender, EventArgs e)
        {
            DataRow dr = BLL.Config.GetInfoOfVip();
            if (dr != null)
            {
                MoneyToViptimeDay = Convert.ToInt32(dr["MoneyToViptimeDay"]);
                MoneyToViptimeWeek = Convert.ToInt32(dr["MoneyToViptimeWeek"]);
                MoneyToViptimeMonth = Convert.ToInt32(dr["MoneyToViptimeMonth"]);
                MoneyToViptimeHYear = Convert.ToInt32(dr["MoneyToViptimeHYear"]);
                MoneyToViptimeYear = Convert.ToInt32(dr["MoneyToViptimeYear"]);
            }

            BindVip();
        }

        public void BindVip()
        {
            DataRow dr = new BLL.Member().GetInfoInTUserInfo(UiCommon.UserLoginInfo.UserID);
            if (dr != null)
            {
                VipTime2 = dr["VipTime2"].ToString();
                DateTime dtInit = new DateTime(1970, 01, 01, 08, 00, 00);
                DateTime dtNow = DateTime.Now;
                lblVipState.Text = "您还没有申请过VIP";
                if (Convert.ToDateTime(VipTime2) > dtInit)
                {
                    if (dtNow > Convert.ToDateTime(VipTime2))
                    {
                        lblVipState.Text = "您的VIP已经过期";
                    }
                    else
                    {
                        lblVipState.Text = "您的VIP到期时间为" + Convert.ToDateTime(VipTime2).ToString("yyyy-MM-dd");
                    }
                }
            }
        }
        protected void button5_ServerClick(object sender, EventArgs e)
        {
            int iDay = Convert.ToInt32(ddlVipType.SelectedValue);
            int oneVipTime = iDay * 60 * 60 * 24;
            int buyMoney = 0;
            switch (iDay)
            {
                case 7: buyMoney = MoneyToViptimeWeek;
                    break;
                case 30: buyMoney = MoneyToViptimeMonth;
                    break;
                case 180: buyMoney = MoneyToViptimeHYear;
                    break;
                case 360: buyMoney = MoneyToViptimeYear;
                    break;
            }

            //判断银行的钱是否足够
            Int64 bankMoney = new BLL.Member().GetBankMoney(UiCommon.UserLoginInfo.UserID);
            if (bankMoney < buyMoney)
            {
                lblMsg.Text = "您银行中的" + UiCommon.StringConfig.MoneyName + "不足，请充值后再购买！";
                return;
            }

            int buyVipTime = 0;
            DateTime dtVip = Convert.ToDateTime(VipTime2);
            DateTime dtNow = DateTime.Now;
            if (dtNow > dtVip)
            {
                TimeSpan nowtime = dtNow - dtVip;
                int nDays = nowtime.Days + iDay;
                buyVipTime = nDays * 24 * 60 * 60;
            }
            else
            {
                buyVipTime = iDay * 24 * 60 * 60;
            }
			long sumMoney = new BLL.Member().GetAllMoney( UiCommon.UserLoginInfo.UserID );
            int iRows = new BLL.Member().BuyVipTime(UiCommon.UserLoginInfo.UserID, buyMoney, buyVipTime, oneVipTime);
            if (iRows > 0)
            {
				BLL.Member.WriteMoneyExChangeLog( UiCommon.UserLoginInfo.UserID, sumMoney, -buyMoney, (int)Library.MoneyChangeType.购买VIP, "" );
                lblMsg.Text = "VIP申请成功，您可以享受VIP的尊贵待遇了！" + DateTime.Now;
                ddlVipType.SelectedIndex = 0;
                BindVip();
            }
            else
            {
                lblMsg.Text = "抱歉，VIP申请失败，可能是服务器繁忙，请稍候再试！";
                BindVip();
            }
        }
    }
}

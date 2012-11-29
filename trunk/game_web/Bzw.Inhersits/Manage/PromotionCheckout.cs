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
using BCST.Common;
using Bzw.Data;
using System.Collections.Generic;

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_PromotionCheckout : UiCommon.ManageBasePage
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
        /// lteTrueName 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal lteTrueName;

        /// <summary>
        /// lteTgMoney 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal lteTgMoney;

        /// <summary>
        /// txtMoney 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtMoney;

        /// <summary>
        /// button5 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputSubmit button5;

        /// <summary>
        /// lteCon_MinClearingMoney 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal lteCon_MinClearingMoney;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                BindTgInfo();
            }
        }

        public void BindTgInfo()
        {
            DataRow dr = new BLL.Promotion().GetInfo(UiCommon.UserLoginInfo.UserID);
            if (dr != null)
            {
                lteTrueName.Text = dr["TrueName"].ToString();
                lteTgMoney.Text = UiCommon.StringConfig.AddZeros(dr["MoneyCount"]);
            }

            DataRow dr2 = BLL.Config.GetInfoOfPromotion();
            if (dr2 != null)
            {
                //推广收入结账最低要达到的金币数
                lteCon_MinClearingMoney.Text = UiCommon.StringConfig.AddZeros(dr2["Con_MinClearingMoney"]);

            }
        }

        protected void button5_ServerClick(object sender, EventArgs e)
        {
            if (!BCST.Common.CommonManager.Web.CheckPostSource())
            {
                return;
            }
            string mgs = string.Empty;
            //Con_MinClearingMoney 推广账户收入最低要达到XX金币，才能够结算
            int Con_MinClearingMoney = Convert.ToInt32(lteCon_MinClearingMoney.Text.Trim());
            int tgMoney = Convert.ToInt32(lteTgMoney.Text.Trim());
            if (tgMoney < Con_MinClearingMoney)
            {
                mgs = "抱歉，推广收入最低要达到" + Con_MinClearingMoney + UiCommon.StringConfig.MoneyName+"，才可以进行结账！";
                CommonManager.Web.RegJs(this, "alert('" + mgs + "');location.href=location.href;", true);
                return;
            }

            int jzMoney = Convert.ToInt32(txtMoney.Text.Trim());


            if (jzMoney > tgMoney)
            {
                mgs = "抱歉，您输入的结账" + UiCommon.StringConfig.MoneyName + "数不能大于您的推广收入！";
                CommonManager.Web.RegJs(this, "alert('" + mgs + "');location.href=location.href;", true);
                return;
            }
            //jzMoney少于零，则说明输入的金额比配置的倍数小。输入的金额至少要达到倍数的额数。2010-01-26
            jzMoney = Convert.ToInt32(UiCommon.StringConfig.RemoveZeros(jzMoney));
            if (jzMoney <= 0)
            {
                lblMsg.Text = "抱歉，结账金额必须大于或等于" + UiCommon.StringConfig.GetMultiple();
                return;
            }

            //存入银行TUserInfo、保存推广结账日志Web_ClearingLog
            //int iRows = new BLL.Member().TuiguangCheckout(UiCommon.UserLoginInfo.UserID, jzMoney, Utility.Common.RequestIP);
            Dictionary<string, object> dic = new Dictionary<string, object>();
            DbSession.Default.FromProc("Web_pTuiguangCheckout")
                .AddInputParameter("@UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID)
                .AddInputParameter("@OPerateMoney", DbType.Int32, jzMoney)
                .AddInputParameter("@OperateIP", DbType.String, Utility.Common.RequestIP)
                .AddOutputParameter("@Result", DbType.Int32, 4)
                .Execute(out dic);
            if (dic.Count > 0 && (int)dic["Result"] == 0)
            {
                mgs = "结账成功，结账" + UiCommon.StringConfig.MoneyName + "数为" + UiCommon.StringConfig.AddZeros(jzMoney) +UiCommon.StringConfig.MoneyName+ "！" + DateTime.Now;
                CommonManager.Web.RegJs(this, "alert('" + mgs + "');location.href=location.href;", true);
            }
            else if (dic.Count > 0 && (int)dic["Result"] == 1)
            {
                mgs = "抱歉，您的推广收入" + UiCommon.StringConfig.MoneyName + "不足！";
                CommonManager.Web.RegJs(this, "alert('" + mgs + "');location.href=location.href;", true);
            }
            else
            {
                mgs = "抱歉，结账操作失败，可能是服务器繁忙，请稍候再试！";
                CommonManager.Web.RegJs(this, "alert('" + mgs + "');location.href=location.href;", true);
            }
        }
    }
}

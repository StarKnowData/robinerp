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

namespace Bzw.Inhersits.Manage.Pay._99bill.PhonePay
{
    public partial class Manage_Pay_99bill_PhonePay_Show : UiCommon.BasePage
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
        /// webuserlogin1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webuserlogin1;

        /// <summary>
        /// webservice1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webservice1;

        /// <summary>
        /// form2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm form2;

        /// <summary>
        /// Lab_orderId 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal Lab_orderId;

        /// <summary>
        /// Lab_orderAmount 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal Lab_orderAmount;

        /// <summary>
        /// Lab_msg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal Lab_msg;

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
            //非法操作时重定向的URL地址
            string toUrl = "/Manage/Pay/99bill/PhonePay/Default.aspx";

            if (Request["orderId"] == null)
            {
                Response.Redirect(toUrl);
            }
            string Orderid = Request["orderId"].ToString().Trim();

            if (Request["payAmount"] == null)
            {
                Response.Redirect(toUrl);
            }
            string payAmount = Request["payAmount"].ToString().Trim();

            //以下输出订单提示
            //订单编号
            Lab_orderId.Text = Orderid;
            //订单金额，把分转换成元
            int bMoney = Convert.ToInt32(Double.Parse(payAmount) / 100);
            Lab_orderAmount.Text = bMoney.ToString();//得到实际充值的金额

            if (Request["msg"] == null)
            {
                Response.Redirect(toUrl);
            }
            string success = Request["msg"].ToString();

            if (success.Trim().ToLower() == "success")
            {
                Lab_msg.Text = "恭喜您，充值成功！";

                /*
                BLL.Member member = new BLL.Member();
                if (!member.IsPaySuccess(Orderid)) //防止重复刷新页面而带来的问题
                {
                    member.Update3PayOrder(string.Empty, bMoney, Orderid);
                }*/
            }
            else if (success.Trim().ToLower() == "false") //success = false
            {
                Lab_msg.Text = "对不起，充值失败，请稍后再继续尝试！回到<a href=\"" + toUrl + "\"><b>全国移动手机短信充值</b></a>页面";
            }
            else //success = error
            {
                Lab_msg.Text = "对不起，发生支付错误，导致充值失败，如果您确认钱已支付，请及时向我们反馈此问题！";
            }

        }
    }
}

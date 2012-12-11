using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Gateway;
using BCST.Common;
using Bzw.WebLibrary;
using System.Data.SqlClient;
using Utility;

namespace Bzw.Inhersits.Manage.Pay.Alipay
{
    public partial class Manage_Pay_Alipay_Default : UiCommon.BasePage
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
        /// webtop1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webtop1;

        /// <summary>
        /// form2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm form2;

        /// <summary>
        /// txtUserName 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtUserName;

        /// <summary>
        /// txtUserName2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtUserName2;

        /// <summary>
        /// PayMoney 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox PayMoney;

        /// <summary>
        /// Button1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Button Button1;

        /// <summary>
        /// Control1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl Control1;
        protected string  MoneyRate = string.Empty;
        protected string CouponRate = string.Empty;

        protected void Page_Load(object sender, EventArgs e)
        {
            SeoSetting(SeoConfig.Config.PaySeo);
            if (UiCommon.UserLoginInfo.IsLogin)
            {
                txtUserName.Text = UiCommon.UserLoginInfo.UserName;
                txtUserName2.Text = UiCommon.UserLoginInfo.UserName;
                CouponRate = GetCouponRate();
                
            }
            MoneyRate = BLL.Config.GetInfoOfCard()["Con_MoneyChangeRate"].ToString();
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            /*
            show_url          ="www.xiaohhgame.com"                   '网站的网址
            seller_email		= "672561@qq.com"				'请设置成您自己的支付宝帐户
            partner			= "2088102335433231"					'支付宝的账户的合作者身份ID
            key			    = "7a7kaee4ogm8lwywepjgpgkcek9pcnl3"	'支付宝的安全校验码

            notify_url			= "http://www.xiaohhgame.com/alipay/Alipay_Notify.asp"	'付完款后服务器通知的页面 要用 http://格式的完整路径
            return_url			= "http://www.xiaohhgame.com/alipay/return_Alipay_Notify.asp"	'付完款后跳转的页面 要用 http://格式的完整路径
            */


            //商品名称（商户）
            string companyName = UiCommon.StringConfig.CompanyNameOfPay;

            //支付人
            string userName = txtUserName.Text.Trim();
            BLL.Member mem = new BLL.Member();
            if (!mem.ExistName(userName))
            {
                CommonManager.Web.RegJs(this, "alert('找不到您输入的用户，请重新核对。');history.back();", false);
                return;
            }

            //支付金额
            string payMoney = PayMoney.Text.Trim();
            if (string.IsNullOrEmpty(payMoney) || !CommonManager.String.IsInteger(payMoney) || int.Parse(payMoney) <= 0)
            {
                CommonManager.Web.RegJs(this, "alert('金额只能输入大于0的整数。');history.back();", false);
                return;
            }
            int otherPayMoney = mem.UserTodayOtherPayMoney(userName.Trim());
            //是否超出今天充值限制额
            if (Convert.ToInt32(payMoney) > otherPayMoney)
            {
            
                CommonManager.Web.RegJs(this, "alert(''您今天能充值金额数不能大于" + otherPayMoney + "。');history.back();", false);
                return;
            }
            //支付类型 Web_RMBCost.PayType
            int payTypeLog = 4;

            //类型信息 Web_RMBCost.Typeinfo
            string typeInfoLog = "支付宝在线支付";

            //*****************业务参数赋值*****************************************************************
            //订单号(按时构造)
            /*System.DateTime currentTime = new System.DateTime();
            currentTime = System.DateTime.Now;
            string out_trade_no = currentTime.ToString("g");
            out_trade_no = out_trade_no.Replace("-", "");
            out_trade_no = out_trade_no.Replace(":", "");
            out_trade_no = out_trade_no.Replace(" ", "");*/
            string out_trade_no = DateTime.Now.ToString("yyyyMMddHHmmssfffffff");

            //支付接口　https://www.alipay.com/cooperate/gateway.do?
            string gateway = UiCommon.StringConfig.AlipayNotifyURL;

            //服务参数
            string service = "create_direct_pay_by_user";

            //partner 合作伙伴ID(保留字段)
            string partner = UiCommon.StringConfig.AlipayPartnerID;// "2088102335433231"; 

            //加密类型
            string sign_type = "MD5";

            //subject 商品名称
            string subject = companyName;

            //body 商品描述

            // [modify] jeffery
            //string body = "游戏" + UiCommon.StringConfig.MoneyName;

            double poupon = Convert.ToDouble(CouponRate) * Convert.ToDouble(PayMoney.Text);
            if (poupon < 0)
                poupon = 0;

            string body = "游戏" + UiCommon.StringConfig.MoneyName +
                "!@#" + userName + "!@#" + Convert.ToInt32(poupon).ToString();
            // ---end

            //支付类型
            string payment_type = "1";

            //总金额 0.01～50000.00      	
            string total_fee = payMoney;

            //网站的网址
            string show_url = UiCommon.StringConfig.WebSiteName;// 支付宝页面显示<a href="www.xiaohhgame.com" target="_blank">商品名称</a> ;

            //卖家账号
            string seller_email = UiCommon.StringConfig.AlipayAccount; //"672561@qq.com";

            //partner账户的支付宝安全校验码   
            string key = UiCommon.StringConfig.AlipayKey; //"7a7kaee4ogm8lwywepjgpgkcek9pcnl3";

            //服务器通知返回接口，这个页面可以展示给客户看,只有付款成功才会跳转到这个页面
            string return_url = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/Alipay/Alipay_Return.aspx";

            //服务器通知返回接口
            string notify_url = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/Alipay/Alipay_Notify.aspx";

            string _input_charset = "utf-8";


            //支付成功前， 插入支付的订单日志
            mem.Add3PayOrder(userName, Convert.ToInt32(payMoney), payTypeLog, typeInfoLog, out_trade_no);


            //把支付数据提交到支付宝服务器
            AliPay ap = new AliPay();
            string aliay_url = ap.CreatUrl(
                gateway,
                service,
                partner,
                sign_type,
                out_trade_no,
                subject,
                body,
                payment_type,
                total_fee,
                show_url,
                seller_email,
                key,
                return_url,
                _input_charset,
                notify_url
                );

            Response.Redirect(aliay_url);

        }

        private string GetCouponRate()
        {
            string strsql = "select top 1 CouponRate from TRechargeCouponType where Way=@way";
            DataTable table = SqlHelper.ExecuteDataset(
                CommandType.Text,
                strsql,
                new SqlParameter[]{
                    new SqlParameter("@way",4)
                }
                ).Tables[0];
            if (table.Rows.Count > 0)
            {
                return table.Rows[0]["CouponRate"].ToString();
            }
            return "";
        }
    }
}

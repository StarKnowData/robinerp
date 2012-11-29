using System;
using BCST.Common;
using Bzw.Data;
using Gateway;

namespace Bzw.Web.Manage.Pay.AlipayTest
{
    public partial class Default2 : UiCommon.BasePage
    {
        
      

        protected string MoneyRate = string.Empty;

        /// <summary>
        /// 页面初始化加载事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load(object sender, EventArgs e)
        {
            //如果用户已经登录，则将已登录用户的用户名显示到页面
            if (UiCommon.UserLoginInfo.IsLogin)
            {
                txtUserName.Text = UiCommon.UserLoginInfo.UserName;
                txtUserName2.Text = UiCommon.UserLoginInfo.UserName;
            }

            //货币利率
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


            //商品名称（商户）（此参数可以后台配置的）
            string companyName = UiCommon.StringConfig.CompanyNameOfPay;

            //支付人（也就是登录的用户账号）
            string userName = txtUserName.Text.Trim();
            BLL.Member mem = new BLL.Member();
            if (!mem.ExistName(userName))//验证用户名是否存在
            {
                CommonManager.Web.RegJs(this, "alert('找不到您输入的用户，请重新核对。');history.back();", false);
                return;
            }

            //支付金额
            string payMoney = PayMoney.Text.Trim();//从前台得到支付的金额
            if (string.IsNullOrEmpty(payMoney) || !CommonManager.String.IsInteger(payMoney) || int.Parse(payMoney) <= 0)//验证金额的合法性
            {
                CommonManager.Web.RegJs(this, "alert('金额只能输入大于0的整数。');history.back();", false);
                return;
            }

            //支付类型 Web_RMBCost.PayType  此值固定
            int payTypeLog = 4;

            //类型信息 Web_RMBCost.Typeinfo  此值固定
            string typeInfoLog = "支付宝在线支付";

            //*****************业务参数赋值*****************************************************************
            //订单号(按时构造)
            /*System.DateTime currentTime = new System.DateTime();
            currentTime = System.DateTime.Now;
            string out_trade_no = currentTime.ToString("g");
            out_trade_no = out_trade_no.Replace("-", "");
            out_trade_no = out_trade_no.Replace(":", "");
            out_trade_no = out_trade_no.Replace(" ", "");*/
            string out_trade_no = DateTime.Now.ToString("yyyyMMddHHmmssfffffff");//此值固定

            //支付接口　https://www.alipay.com/cooperate/gateway.do?
            string gateway = UiCommon.StringConfig.AlipayNotifyURL;//此值在web.config中配置

            //服务参数
            string service = "create_direct_pay_by_user";//此值固定

            //partner 合作伙伴ID(保留字段)
            string partner = UiCommon.StringConfig.AlipayPartnerID;//此值在web.config中配置

            //加密类型
            string sign_type = "MD5";//此值固定

            //subject 商品名称
            string subject = companyName;

            //body 商品描述
            string body = "游戏金币";//此值可以自定义

            //支付类型
            string payment_type = "1";//此值固定

            //总金额 0.01～50000.00      	
            string total_fee = payMoney;

            //网站的网址
            string show_url = UiCommon.StringConfig.WebSiteName;// 支付宝页面显示<a href="www.xiaohhgame.com" target="_blank">商品名称</a> ;

            //卖家账号
            string seller_email = UiCommon.StringConfig.AlipayAccount; //此值在web.config中配置

            //partner账户的支付宝安全校验码   
            string key = UiCommon.StringConfig.AlipayKey; //此值在web.config中配置

            //服务器通知返回接口，这个页面可以展示给客户看,只有付款成功才会跳转到这个页面
            string return_url = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/Alipay/Alipay_Return.aspx";

            //服务器通知返回接口  这个页面是支付宝发过来确定信息后网站更新数据，然后再给支付宝发送确定信息

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
    }
}

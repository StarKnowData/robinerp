using System;
using System.Collections.Generic;
using System.Text;
using BCST.Common;
using Bzw.Data;

namespace Bzw.Inhersits.Manage.Pay.IPS
{
   public partial class Manage_Pay_IPS_OrderPay:UiCommon.BasePage
    {

        /// <summary>
        /// Mer_code 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden Mer_code;

        /// <summary>
        /// Billno 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden Billno;

        /// <summary>
        /// Amount 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden Amount;

        /// <summary>
        /// Date 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden Date;

        /// <summary>
        /// Currency_Type 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden Currency_Type;

        /// <summary>
        /// Gateway_Type 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden Gateway_Type;

        /// <summary>
        /// Lang 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden Lang;

        /// <summary>
        /// MerchantUrl 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden MerchantUrl;

        /// <summary>
        /// failUrl 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden failUrl;

        /// <summary>
        /// ErrorUrl 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden ErrorUrl;

        /// <summary>
        /// Attach 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden Attach;

        /// <summary>
        /// OrderEncodeType 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden OrderEncodeType;

        /// <summary>
        /// RetEncodeType 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden RetEncodeType;

        /// <summary>
        /// Rettype 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden Rettype;

        /// <summary>
        /// ServerUrl 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden ServerUrl;

        /// <summary>
        /// signMD5 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden signMD5;

        /// <summary>
        /// DoCredit 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden DoCredit;

        /// <summary>
        /// Bankco 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden Bankco;


       protected void Page_Load(object sender, EventArgs e)
       {
           //string toServerURL = "https://pay.ips.com.cn/ipayment.aspx";//IPS支付接口路径

           //string toServerURLTest = "https://pay.ips.net.cn/ipayment.aspx"; //IPS支付接口测试路径

           //frmPay.Action = toServerURLTest;

           string errorUrl = "/Manage/Pay/IPS/Default.aspx"; //出错跳转地址

           BLL.Member mem = new BLL.Member();

           string txtUserName = Utility.Common.GetStringOfForm("txtUserName"); //用户名

           if (!mem.ExistName(txtUserName.Trim()))
           {
               Response.Write("<script>alert('找不到您要充值的用户帐号，请检查输入是否有误');location.href='" + errorUrl + "';</script>");
               Response.End();
           }
            
           // [add] jeffery
           //string strCouponNum = Utility.Common.GetStringOfForm("CouponNum"); //获取应赠送奖劵数量
           //Attach.Value = txtUserName + "!@#" + strCouponNum;
           // --- end
           
         //支付金额
            string payMoney = Utility.Common.GetStringOfForm("PayMoney"); 

            if (string.IsNullOrEmpty(payMoney) || !CommonManager.String.IsInteger(payMoney) || int.Parse(payMoney) <= 0)
            {
                CommonManager.Web.RegJs(this, "alert('金额只能输入大于0的整数。');history.back();", false);
                return;
            }
            int otherPayMoney = mem.UserTodayOtherPayMoney(txtUserName.Trim());
            //是否超出今天充值限制额
            if (Convert.ToInt32(payMoney) > otherPayMoney)
            { 
                Response.Write("<script>alert('您今天能充值金额数不能大于"+otherPayMoney+"。');location.href='" + errorUrl + "';</script>");
                Response.End();
            }
            int payTypeLog = 6;
          
           Currency_Type.Value = "RMB";  //支付币种

           Amount.Value = payMoney + ".00";  //订单金额


           Mer_code.Value = UiCommon.StringConfig.IPS_Mer_code; //商户编号


           Billno.Value = DateTime.Now.ToString("yyyyMMddHHmmssfffffff"); //商户定单编号

           Date.Value = DateTime.Now.ToString("yyyyMMdd");  //订单日期

           MerchantUrl.Value = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/IPS/OrderReturn.aspx"; //支付成功通知的URL

           failUrl.Value = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/IPS/OrderReturn.aspx"; //支付失败通知的URL 


           signMD5.Value = Utility.Common.md5("billno" + Billno.Value + "currencytype" + Currency_Type.Value + "amount" + Amount.Value + "date" + Date.Value + "orderencodetype" + OrderEncodeType.Value + UiCommon.StringConfig.IPS_Letter);   //MD5加密签名

              //如果是神舟卡
           if (Utility.Common.GetStringOfForm("Type") == "phone")
           {
               DoCredit.Value = "1";//直连神舟行
               Bankco.Value = "00077";//神州行代码
               Rettype.Value = "1";
               ServerUrl.Value = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/IPS/IPS_Server.aspx"; 
               //支付成功前， 插入支付的订单日志 
               mem.Add3PayOrder(txtUserName, Convert.ToInt32(payMoney), payTypeLog, "环迅-神州行充值", Billno.Value); 
           }
           else
           {
               //支付成功前， 插入支付的订单日志 
               mem.Add3PayOrder(txtUserName, Convert.ToInt32(payMoney), payTypeLog, "环迅充值", Billno.Value); 
           }
             
       }
    }
}

using System;
using System.Collections.Generic;
using System.Text;
using BCST.Common;
using Gateway;

namespace Bzw.Inhersits.Manage.Pay._15173Pay
{
    public partial class Manage_Pay_15173Pay_Send : UiCommon.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string toUrl = "/Manage/Pay/15173pay/Default.aspx";
            //支付人
            string userName = Utility.Common.GetStringOfForm("txtUserName");
            BLL.Member mem = new BLL.Member();
            if (!mem.ExistName(userName))
            {
                CommonManager.Web.RegJs(this, "alert('找不到您输入的用户，请重新核对。');history.back();", false);
                return;
            }

            //支付金额
            string payMoney = Utility.Common.GetStringOfForm("PayMoney"); 
            if (string.IsNullOrEmpty(payMoney) || !CommonManager.String.IsInteger(payMoney) || int.Parse(payMoney) <= 0)
            {
                CommonManager.Web.RegJs(this, "alert('金额只能输入大于0的整数。');history.back();", false);
                return;
            }
            int otherPayMoney = mem.UserTodayOtherPayMoney(userName.Trim());
            //是否超出今天充值限制额
            if (Convert.ToInt32(payMoney) > otherPayMoney)
            {
                Response.Write("<script>alert('您今天能充值金额数不能大于" + otherPayMoney + "。');location.href='" + toUrl + "';</script>");
                Response.End();
            }
            Pay15173 pays = new Pay15173();
            //商户ID
            pays.Bargainor_id = UiCommon.StringConfig.Pay15173ID;

            //商户密钥
            pays.Key = UiCommon.StringConfig.Pay15173Key;

            //商户订单号
            string out_trade_no = DateTime.Now.ToString("yyyyMMddHHmmssfffffff");

            pays.Sp_billno = out_trade_no;

            pays.Total_fee = Convert.ToDecimal(payMoney);
            //充值类型
            string payType = System.Web.HttpContext.Current.Request.Form["rdPayType"].ToString().Trim();

            pays.Pay_type = payType;

            //返回页面
            pays.Return_url = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/15173pay/Return.aspx";

            //交易单备注,留空
            pays.Attach = "CC";

            string typeInfoLog = string.Empty;

            switch (payType)
            {
                case "a":
                    typeInfoLog = "15173神州行卡支付";
                    break;
                case "b":
                    typeInfoLog = "15173俊网一卡通支付";
                    break;
                case "c":
                    typeInfoLog = "15173盛大卡支付";
                    break;
                case "d":
                    typeInfoLog = "15173征途游戏卡支付";
                    break;
                case "m":
                    typeInfoLog = "15173网易一卡通支付";
                    break;
                case "n":
                    typeInfoLog = "15173搜狐一卡通支付";
                    break;
                case "q":
                    typeInfoLog = "15173久游一卡通支付";
                    break;
                case "u":
                    typeInfoLog = "15173完美一卡通支付";
                    break;
                case "x":
                    typeInfoLog = "15173联通全国充值卡支付";
                    break;
                case "y":
                    typeInfoLog = "15173中国电信付费充值卡支付";
                    break;
                case "f":
                    typeInfoLog = "15173金山一卡通支付";
                    break;
                case "g":
                    typeInfoLog = "15173光宇一卡通支付";
                    break;
                case "e":
                    typeInfoLog = "15173纵游一卡通支付";
                    break;

            }
            int payTypeLog = 5;
            mem.Add3PayOrder(userName, Convert.ToInt32(payMoney), payTypeLog, typeInfoLog, out_trade_no);
            string url = "";
            if (!pays.GetPayUrl(out url))
            {
                Utility.Common.OutMsgBox(url, toUrl);
            }
            else
            {
                Response.Redirect(url);
            }
        }
    }
}

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

using System.Security;
using System.Security.Cryptography;
using System.Web.Configuration;

namespace Bzw.Inhersits 
{
    public partial class Manage_Pay_Baofoo_pay_post : UiCommon.BasePage
    {
        protected string strMerchantID;
        protected string strPayID;
        protected string strTradeDate;
        protected string strTransID;
        protected string strProductName;
        protected string strAmount;
        protected string payMoney;
        protected string strProductLogo;
        protected string strUsername;
        protected string strEmail;
        protected string strMobile;
        protected string strAdditionalInfo;
        protected string strMerchant_url;
        protected string strReturn_url;
        protected string strMd5Sign;
        protected string strNoticeType;

        protected string strCouponNum;

        protected void Page_Load(object sender, EventArgs e)
        {

            string errorUrl,strMd5Key, txtUserName;
            int intPayType, intBankID, intCardID; 

            
            errorUrl = "/Manage/Pay/Baofoo/Default.aspx"; //出错跳转地址
            strMerchant_url = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/Baofoo/return_url.aspx"; //客户端跳转地址
            strReturn_url = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/Baofoo/merchant_url.aspx";//服务器端返回地址
            strMerchantID = ConfigurationManager.AppSettings["baofoo_memberid"]; //商户号
            strMd5Key = ConfigurationManager.AppSettings["baofoo_key"]; //密钥 双方约定
            txtUserName = Utility.Common.GetStringOfForm("txtUserName"); //用户名
            payMoney = Utility.Common.GetIntOfForm("PayMoney").ToString(); //支付金额

            strCouponNum = Utility.Common.GetStringOfForm("CouponNum");

            strTradeDate = DateTime.Now.ToString("yyyyMMddHHmmss"); //交易日期

            //strPayID = Request.Params["SPayID"];//神州行卡充值是1

            intPayType = Utility.Common.GetIntOfForm("pay_type"); //支付方式
            intBankID = Utility.Common.GetIntOfForm("bankid");  //银行对应的ID
            intCardID = Utility.Common.GetIntOfForm("cardid");  //点卡对应的ID

            if (intPayType == 1) //银行支付
            {
                strPayID = intBankID.ToString();
                strTransID = DateTime.Now.ToString("yyyyMMddHHmmssffff"); //商户订单号（交易流水号）8-20位：必须唯一，推荐：前6位为商户号，后10位为用户流水号，string类型
            }
            else //点卡支付
            {
                strPayID = intCardID.ToString();
                strTransID = "ka" + DateTime.Now.ToString("yyMMddHHmmssffff"); 
            }


            BLL.Member mem = new BLL.Member();
            //判断用户帐号是否正常
            if (!mem.ExistName(txtUserName.Trim()))
            {
                Response.Write("<script>alert('找不到您要充值的用户帐号，请检查输入是否有误');location.href='" + errorUrl + "';</script>");
                Response.End();
            }

            if (mem.IsInRoomOrGame(txtUserName.Trim()))
            {
                Response.Write("<script>alert('要充值的帐号正在游戏中，请先退出游戏再进行充值。');location.href='" + errorUrl + "';</script>");
                Response.End();
            }

            
            
            strProductName = "";//商品名称
            strAmount = "1";//商品数量，为1
            strProductLogo = "";//商品图片地址
            strUsername = "";
            strEmail = "";
            strMobile = "";

            // [modify] jeffery
            strAdditionalInfo = "";
            //strAdditionalInfo = txtUserName + "!@#" + strCouponNum;
            // ---end

            strNoticeType = "1";//0 不跳转 1 会跳转

            //商户保存订单信息.....
            //SaveOrderInfo();
            //支付成功前， 插入支付的订单日志
            
            mem.Add3PayOrder(txtUserName.Trim(),
                Convert.ToInt32(payMoney),
                8, "宝付充值", strTransID);

            payMoney = (Convert.ToInt32(payMoney) * 100).ToString();
          
            strMd5Sign = GetMd5Sign(strMerchantID, strPayID, strTradeDate,
                strTransID, payMoney, strMerchant_url, strReturn_url, strNoticeType, strMd5Key);





        }


        //md5签名
        private string GetMd5Sign(string _MerchantID, string _PayID, string _TradeDate, string _TransID,
            string _OrderMoney, string _Merchant_url, string _Return_url, string _NoticeType, string _Md5Key)
        {
            string str = _MerchantID + _PayID + _TradeDate + _TransID + _OrderMoney + _Merchant_url + _Return_url + _NoticeType + _Md5Key;
            return Helper.Md5Encrypt(str);

        }

        /// <summary>
        /// 保存订单信息
        /// </summary>
        private void SaveOrderInfo()
        {



        }

    }
}

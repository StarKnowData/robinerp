using System;
using System.Configuration;
using System.Collections.Generic;
using System.Data;
using System.Text;
using System.Net;
using System.IO;
using System.Web.Security;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using BCST.Common;
using Bzw.Data;


namespace Bzw.Inhersits
{
    public partial class Manage_Pay_JFTpay_Send : UiCommon.BasePage 
    {
        protected void Page_Load(object sender, EventArgs e)
        {

            string errorUrl = "/Manage/Pay/JFTpay/Default.aspx"; //出错跳转地址
            string BackUrl = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/JFTpay/Receive.aspx";


            string PayType = Request.Form["pay_type"]; //支付类型（1是网银，2为点卡）
            string txtUserName = Utility.Common.GetStringOfForm("txtUserName"); //用户名
            string payMoney = Utility.Common.GetIntOfForm("PayMoney").ToString(); //支付金额
            string txtCardNo = Utility.Common.GetStringOfForm("txtCardNo"); //卡号 
            string txtCardPass = Utility.Common.GetStringOfForm("txtCardPass"); //卡密 
            string OrderNo;

            //string strCouponNum = Utility.Common.GetStringOfForm("CouponNum");

            //1,支付类型
            if (PayType == "1")  
            {
                OrderNo = DateTime.Now.ToString("yyyyMMddHHmmssffffff");

            }
            else   
            {
                OrderNo = "ka" + DateTime.Now.ToString("yyyyMMddHHmmssffff");

            }

            //2, 验证用户名
            BLL.Member mem = new BLL.Member();
            if (!mem.ExistName(txtUserName))
            {
                Response.Write("<script>alert('找不到您要充值的用户帐号，请检查输入是否有误');location.href='" + errorUrl + "';</script>");
                Response.End();
            }

            if (mem.IsInRoomOrGame(txtUserName))
            {
                Response.Write("<script>alert('要充值的帐号正在游戏中，请先退出游戏再进行充值。');location.href='" + errorUrl + "';</script>");
                Response.End();
            }



            //4, 插入支付的订单日志
            mem.Add3PayOrder(txtUserName.Trim(), Convert.ToInt32(payMoney), 9, "聚付通充值", OrderNo);

            payMoney = payMoney + ".00";



            //5, 跳转到支付平台
            jftpay(OrderNo, BackUrl, payMoney,txtUserName,"");


        }



        /// <summary>
        /// 聚付通
        /// </summary>
        /// <param name="orderid">订单号</param>
        /// <param name="callBackurl">返回地址</param>
        private void jftpay(String orderid, String callBackurl, String amount,string userName,string couponNum)
        {
            //商户信息
            String shop_id = UiCommon.StringConfig.JFTpay_MemberID;  //商户ID
            String key = UiCommon.StringConfig.JFTpay_MemberKey; //商户密钥

            // [add] jeffery
            //Session["CouponInfo"] = userName + "!@#" + couponNum;
            // ---end

            //组织接口发送。
            if (Request.Form["pay_type"] == "1")
            {


                //银行提交获取信息
                String bank_Type = Request.Form["rtype"];//银行类型
                String bank_gameAccount = Request.Form["txtUserName"];//充值账号
                String bank_payMoney = amount;//充值金额
                //银行卡支付
                String param = String.Format("parter={0}&type={1}&value={2}&orderid={3}&callbackurl={4}", shop_id, bank_Type, bank_payMoney, orderid, callBackurl);
                String PostUrl = String.Format("http://do.jftpay.net/chargebank.aspx?{0}&sign={1}", param, FormsAuthentication.HashPasswordForStoringInConfigFile(param + key, "MD5").ToLower());
                Response.Redirect(PostUrl);//转发URL地址
            }
            else
            {

                #region  //点卡支付
                String card_No = Request.Form["cardNo"];//卡号
                String card_pwd = Request.Form["cardPwd"];//卡密
                String card_account = Request.Form["txtUserNameCard"];//充值账号
                String card_type = Request.Form["sel_card"];//卡类型
                String card_payMoney = amount.Replace(".00", "");//充值金额
                String restrict = "0";//使用范围
                if (Request.Form["sel_card"].Split(',').Length > 1)
                {
                    restrict = Request.Form["sel_card"].Split(',')[1];
                }
                //卡类支付
                String param = String.Format("type={0}&parter={1}&cardno={2}&cardpwd={3}&value={4}&restrict={5}&orderid={6}&callbackurl={7}", card_type, shop_id, card_No, card_pwd, card_payMoney, restrict, orderid, callBackurl);
                String PostUrl = String.Format("http://do.jftpay.net/cardReceive.aspx?{0}&sign={1}", param, FormsAuthentication.HashPasswordForStoringInConfigFile(param + key, "MD5").ToLower());
                //Response.Write(PostUrl);
                HttpWebRequest httpWebRequest = (HttpWebRequest)WebRequest.Create(PostUrl);
                //获取响应结果 此过程大概需要5秒
                HttpWebResponse httpWebResponse = (HttpWebResponse)httpWebRequest.GetResponse();
                //获取响应流
                Stream stream = httpWebResponse.GetResponseStream();
                //用指定的字符编码为指定的流初始化 StreamReader 类的一个新实例。
                using (StreamReader streamReader = new StreamReader(stream, Encoding.UTF8))
                {
                    string useResult = streamReader.ReadToEnd();
                    streamReader.Dispose();
                    streamReader.Close();
                    httpWebResponse.Close();

                    if (useResult.Trim() == "opstate=0")
                    {
                        Response.Write("已经记录该卡，正在等待被使用.");
                    }
                    if (useResult.Trim() == "opstate=-1")
                    {
                        Response.Write("请求参数无效。");
                    }
                    if (useResult.Trim() == "opstate=-2")
                    {
                        Response.Write("签名错误。");
                    }
                    if (useResult.Trim() == "opstate=-3")
                    {
                        Response.Write("提交的卡密为重复提交，系统不进行消耗并进入下行流程。");
                    }
                    if (useResult.Trim() == "opstate=-4")
                    {
                        Response.Write("卡已经使用。");
                        //这里把定单状态改为失败。
                    }
                    if (useResult.Trim() == "opstate=-5")
                    {
                        Response.Write("失败(网络原因、具体原因不明确等)。");
                        ////这里把定单状态改为失败。
                    }

                }
                #endregion
            }



        }


    }
}

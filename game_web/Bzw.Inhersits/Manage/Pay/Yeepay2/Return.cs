using System;
using System.Collections.Generic;
using System.Text;
using UiCommon;
using com.yeepay;

namespace Bzw.Inhersits.Manage.Pay.Yeepay2
{
  public  class Manage_Pay_Yeepay2_Return:UiCommon.BasePage
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
        /// Lab_msg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal Lab_msg;

        /// <summary>
        /// Control1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl Control1;
        /// <summary>
        /// created by sunzhizhi 2006.5.21,sunzhizhi@msn.com。
        /// </summary>
        /// 

        public string PayResult = string.Empty;
        public string PayMoney = string.Empty;
        public string PayOrderID = string.Empty;
        protected string p1_MerId;
        protected string keyValue;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                //p1_MerId = "10000432521";                                     // 商家ID
                //keyValue = "8UPp0KE8sq73zVP370vko7C39403rtK1YwX40Td6irH216036H27Eb12792t";  // 商家密钥

                p1_MerId = StringConfig.YeepayMerID;// 商家ID
                keyValue = StringConfig.YeepayKey;  // 商家密钥

                // 校验返回数据包
                BuyCallbackResult result = Buy.VerifyCallback(p1_MerId, keyValue, Buy.GetQueryString("r0_Cmd"), Buy.GetQueryString("r1_Code"), Buy.GetQueryString("r2_TrxId"),
                    Buy.GetQueryString("r3_Amt"), Buy.GetQueryString("r4_Cur"), Buy.GetQueryString("r5_Pid"), Buy.GetQueryString("r6_Order"), Buy.GetQueryString("r7_Uid"),
                    Buy.GetQueryString("r8_MP"), Buy.GetQueryString("r9_BType"), Buy.GetQueryString("rp_PayDate"), Buy.GetQueryString("hmac"));
                PayOrderID = result.R6_Order;
                PayMoney = result.R3_Amt;

                

                if (string.IsNullOrEmpty(result.ErrMsg))
                {
                    if (result.R1_Code == "1")
                    {
                        if (result.R9_BType == "1")
                        {
                            //  callback方式:浏览器重定向
                            UpdateDB(result);
                            PayResult = "恭喜您，充值成功！";
                            //Response.Write("支付成功！<br />充值金额：" + result.R5_Pid + "<br />支付金额：" + result.R3_Amt + "<br><a href='/Manage/' title='返回会员中心'>返回会员中心</a>");
                        }
                        else if (result.R9_BType == "2")
                        {
                            UpdateDB(result);
                            // * 如果是服务器返回或者电话支付返回(result.R9_BType==2 or result.R9_BType==3)则需要回应一个特定字符串'SUCCESS',且在'SUCCESS'之前不可以有任何其他字符输出,保证首先输出的是'SUCCESS'字符串
                            Response.Write("SUCCESS");
                        }
                        else if (result.R9_BType == "3")
                        {
                            UpdateDB(result);
                            // * 如果是服务器返回或者电话支付返回(result.R9_BType==2 or result.R9_BType==3)则需要回应一个特定字符串'SUCCESS',且在'SUCCESS'之前不可以有任何其他字符输出,保证首先输出的是'SUCCESS'字符串
                            Response.Write("SUCCESS");
                        }
                    }
                    else
                    {
                         PayResult = "充值失败!";
                    }
                }
                else
                {
                  PayResult= "交易签名无效!";
                }
            }
        }

        private void UpdateDB(BuyCallbackResult result)
        {
            if (result == null)
                return;

            //订单流水号
            string Orderid = result.R6_Order;
            //支付金额
            string payAmount = result.R3_Amt;

            BLL.Member member = new BLL.Member();
            //金币充值
            if (result.R8_MP == "0")
            {
                if (!member.IsPaySuccess(Orderid)) //防止重复刷新页面而带来的问题
                {
                    //更新订单信息为完成状态

                    if (Orderid.ToLower().Contains("ka"))
                        member.Update3PayOrder2((int)(float.Parse(payAmount)), Orderid);
                    else
                        member.Update3PayOrder((int)(float.Parse(payAmount)), Orderid);


                }
            }
            else//积分充值
            {
                if (!member.IsPaySuccess2(Orderid)) //防止重复刷新页面而带来的问题
                {
                    //更新订单信息为完成状态
                    if (Orderid.ToLower().Contains("ka"))//点卡
                    {
                         member.UpdatePayPointOrder((int)(float.Parse(payAmount)), Orderid, 1);
                    }
                    else
                    {
                        member.UpdatePayPointOrder((int)(float.Parse(payAmount)), Orderid, 0);
                    }
                }
            }
        }
    }
}

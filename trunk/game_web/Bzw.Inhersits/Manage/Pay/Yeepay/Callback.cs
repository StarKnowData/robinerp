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
using com.yeepay;
using UiCommon;
namespace Bzw.Inhersits.Manage.Pay.Yeepay
{
    public partial class Manage_Pay_Yeepay_Callback : UiCommon.BasePage
    {
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

                if (string.IsNullOrEmpty(result.ErrMsg))
                {
                    if (result.R1_Code == "1")
                    {
                        if (result.R9_BType == "1")
                        {
                            //  callback方式:浏览器重定向
                            UpdateDB(result);
                            Response.Write("支付成功！<br />充值金额：" + result.R5_Pid + "<br />支付金额：" + result.R3_Amt + "<br><a href='/Manage/' title='返回会员中心'>返回会员中心</a>");
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
                        Response.Write("支付失败!");
                    }
                }
                else
                {
                    Response.Write("交易签名无效!");
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
            if (!member.IsPaySuccess(Orderid)) //防止重复刷新页面而带来的问题
            {
                //更新订单信息为完成状态
                member.Update3PayOrder((int)(float.Parse(payAmount)), Orderid);
            }
        }
    }
}

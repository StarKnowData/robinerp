using System;
using System.Collections.Generic;
using System.Text;
using BLL;

namespace Bzw.Inhersits.Manage.Pay.IPS
{
    public partial class Manage_Pay_IPS_IPS_Server : UiCommon.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string billno = Utility.Common.GetStringOfUrl("billno"); //订单编号

            string amount = Utility.Common.GetStringOfUrl("amount");  //订单金额

            string date = Utility.Common.GetStringOfUrl("date"); //订单日期

            string succ = Utility.Common.GetStringOfUrl("succ"); //成功标志

            string ipsbillno = Utility.Common.GetStringOfUrl("ipsbillno"); //IPS订单编号

            string currency_Type = Utility.Common.GetStringOfUrl("Currency_type");  //币种

            string signature = Utility.Common.GetStringOfUrl("signature").ToLower(); //MD5签名

            string retencodetype = Utility.Common.GetStringOfUrl("retencodetype");//交易返回签名方式

           

            if (string.IsNullOrEmpty(billno) || string.IsNullOrEmpty(amount) || string.IsNullOrEmpty(date) ||
                string.IsNullOrEmpty(succ) || string.IsNullOrEmpty(ipsbillno) || string.IsNullOrEmpty(currency_Type) || string.IsNullOrEmpty(signature))
            {
                Server.Transfer("Default.aspx");
            }



            if (succ.Equals("Y"))
            {
                //交易成功

                if (currency_Type == null || currency_Type == "")
                {
                    currency_Type = "RMB";
                }
                string signatureVal = Utility.Common.md5("billno" + billno + "currencytype" + currency_Type + "amount" + amount + "date" + date + "succ" + succ + "ipsbillno" + ipsbillno + "retencodetype" + retencodetype + UiCommon.StringConfig.IPS_Letter).ToLower();

                if (signature.Equals(signatureVal.ToLower()))
                {
                    Member mem = new Member();
                    if (!mem.IsPaySuccess(billno))
                    {
                        mem.Update3PayOrder((int)(float.Parse(amount)), billno);
                      
                    }
                }
                else
                {

                }


            }
            else
            {
                //交易失败
                //  lblMsg.Text = "充值失败，请稍后再试！";
            }
        }
    }
}
